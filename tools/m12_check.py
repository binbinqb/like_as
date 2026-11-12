#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    m12_check.py
@brief   M12 验收：唤醒源识别 + EcuM 唤醒接口 + STOP 模式睡眠

@details @section M12_WHAT 验什么（纯串口，不需要 Kvaser）

          M12 把"睡眠/唤醒"从口号变成了可观测的行为。分三层验：

          | 层 | 断言 |
          |---|---|
          | **唤醒源识别** | 冷启动横幅是 `wake : NONE (255) [cold boot]`；读的是 PMC 的真实标志，不是软件猜的 |
          | **EcuM 接口** | `!z` 之后 `EcuM_CheckWakeup` 被调用，且**如实报告** `hw=NONE`（tick 唤醒不是 CAN 唤醒） |
          | **真的睡过** | `!z` 报告 `tick +1`，而节拍被临时放大到 100 ms —— 说明 CPU 确实停在 WFI 里，不是空转 |
          | 不睡死 | `!z` 一定能返回，且返回后心跳继续（100 ms 兜底唤醒） |

@warning **本脚本不验"低功耗电流"。**
         `!z` 走的是 Cortex-M **Sleep**（`SCB->SCR` 清 SLEEPDEEP + WFI），
         外设时钟没关、SysTick 还在跑（100 ms），电流不会明显下降。
         测电流必须等真正的 DeepSleep/Standby + 端口唤醒（M13）。
         把"能睡"和"省电"混为一谈是这类项目最常见的自欺。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-11 | binbina | 首版：唤醒源上报 / CheckWakeup 如实报告 / STOP 睡眠可返回 / 不睡死 |
"""

import argparse
import re
import subprocess
import sys
import tempfile
import os
import time

# ── 旧 `!x` → 新 shell 命令（M-Shell 迁移；旧兼容桥已删）─────────────
CMD_MAP = {
	'!z': 'ecum sleep',
	'!q': 'ecum',
}


def xlate(cmd):
	"""旧单字符命令翻译成新命令；其它原样透传。保证以换行结尾。"""
	c = CMD_MAP.get(cmd.strip(), cmd.strip())
	if not c.endswith("\n"):
		c += "\n"
	return c



import serial

PORT = "COM2"
BAUD = 115200

RE_WAKE = re.compile(r"wake\s+:\s+([A-Z]+)\s+\((\d+)\)\s+\[(.+?)\]")
RE_SLEEP_DONE = re.compile(r"\[sleep\] 醒来: tick \+(\d+) \(约 (\d+) ms\), 唤醒源=([A-Z]+)\((\d+)\)")
RE_CHECK_WAKEUP = re.compile(r"CheckWakeup req=0x([0-9a-fA-F]+) hw=([A-Z]+)")
RE_ALIVE = re.compile(r"alive #(\d+)")


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	ser = serial.Serial(a.port, BAUD, timeout=0.2)

	def read_for(seconds):
		t0 = time.time()
		buf = ""
		while (time.time() - t0) < seconds:
			buf += ser.read(8192).decode("utf-8", "replace")
		return buf

	def send(cmd, wait=0.4):
		ser.reset_input_buffer()
		ser.write(xlate(cmd).encode())
		time.sleep(wait)
		return ser.read(8192).decode("utf-8", "replace")

	# ---------- 0) 复位启动 ----------
	if not a.no_reset:
		ser.reset_input_buffer()
		script = os.path.join(tempfile.gettempdir(), "_m12_run.jlink")
		with open(script, "w", encoding="ascii") as f:
			f.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
		subprocess.run([r"C:\Program Files\SEGGER\JLink\JLink.exe", "-ExitOnError", "1",
		                "-CommanderScript", script],
		               capture_output=True, text=True, timeout=60, stdin=subprocess.DEVNULL)
		boot = read_for(1.8)
	else:
		boot = read_for(0.6)

	# ---------- 1) 冷启动的唤醒源 ----------
	m = RE_WAKE.search(boot)
	note("启动: 打印了唤醒源", m is not None,
	     m.group(0).strip() if m else "(无这一行)")
	note("启动: 冷启动报 NONE + [cold boot]",
	     (m is not None) and (m.group(1) == "NONE") and ("cold" in m.group(3)),
	     m.group(0).strip() if m else "(无)")
	note("启动: 三阶段与 RUN 正常",
	     ("nvm   : DFlash" in boot) and ("[ecum] RUN" in boot))

	# ---------- 2) 睡一次 ----------
	out = send("!z", 1.2)

	note("!z: 进睡眠前提示", "[sleep] 进 STOP" in out)
	note("!z: 走 EcuM 接口使能唤醒源", "wakeup sources = 0x0100" in out,
	     ([l.strip() for l in out.splitlines() if "wakeup sources" in l] or ["(无)"])[0][:56])

	d = RE_SLEEP_DONE.search(out)
	note("!z: 睡眠后能返回（不会睡死）", d is not None,
	     d.group(0).strip() if d else "(没有醒来这一行)")

	if d is not None:
		ticks = int(d.group(1))
		approx_ms = int(d.group(2))
		src_name = d.group(3)
		note("!z: tick 只前进了 1（证明 CPU 真的停在 WFI）", ticks == 1,
		     "tick +%d" % ticks)
		note("!z: 折算时长 ≈ 100 ms（兜底节拍）", 80 <= approx_ms <= 130,
		     "%d ms" % approx_ms)
		note("!z: 唤醒源如实报 NONE（tick 唤醒不是 CAN 唤醒）", src_name == "NONE",
		     src_name)

	# ---------- 3) EcuM 唤醒链路 ----------
	c = RE_CHECK_WAKEUP.search(out)
	note("!z: 调用了 EcuM_CheckWakeup", c is not None,
	     c.group(0).strip() if c else "(无)")
	note("!z: CheckWakeup 如实报告 hw=NONE（没有假报 CAN 唤醒）",
	     (c is not None) and (c.group(2) == "NONE"),
	     c.group(0).strip() if c else "(无)")
	note("!z: 没走 ComM 唤醒分支（无 '-> CAN0 wakeup'）",
	     "-> CAN0 wakeup" not in out)

	# ---------- 4) 睡眠之后系统仍正常 ----------
	tail = read_for(1.5)
	note("睡眠后: 心跳继续", RE_ALIVE.search(tail) is not None,
	     (RE_ALIVE.search(tail).group(0) if RE_ALIVE.search(tail) else "(无心跳)"))
	note("睡眠后: 无异常日志",
	     ("TIMEOUT" not in tail) and ("超时" not in tail) and ("fail" not in tail))

	mode = send("!q", 0.25)
	note("睡眠后: EcuM 仍是 RUN", "mode=2" in mode,
	     ([l.strip() for l in mode.splitlines() if "mode=" in l] or ["(无)"])[0][:48])

	ser.close()

	print()
	ok_n = 0
	for name, ok, detail in results:
		print("  %s %s%s" % ("[ OK ]" if ok else "[FAIL]", name,
		                    ("   " + detail) if detail else ""))
		if ok:
			ok_n += 1
	print()
	print("%d 项，通过 %d，失败 %d" % (len(results), ok_n, len(results) - ok_n))
	return 0 if ok_n == len(results) else 1


if __name__ == "__main__":
	sys.exit(main())
