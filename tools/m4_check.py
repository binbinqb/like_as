#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M4 验收：存储栈（厂商 NvM + FEE 引擎 + AUTOSAR 外观）跑在片内 DFlash 上。

验收判据：
	1. 启动横幅打印存储配置，且**没有** TIMEOUT；
	2. `!d` 四个块都在，长度是 8/32/17/64，状态合法；
	3. `BOOTCNT` 数据有效（st=0），且尾部魔数是 'BCM1'；
	4. **掉电保持**：复位一次，启动计数 +1；再复位一次，再 +1；
	5. `VIN` 从没写过，读到的是 ROM 默认值 `CVM0146M4NVM00001`；
	6. **延迟落盘**：`!w` 改 RAM → 标脏 → `WriteAll` 落盘，`st` 变 0；
	7. 复位后 `CONFIG[1]` 保留 —— 证明"改 RAM + WriteAll"这条路真的写进了 Flash；
	8. **DET**：`!x` 用非法块 id 触发 `[det] mod=20 api=0x0b err=0x0a`；
	9. **GC**：`!p` 连写 400 次（≈22 KB，写满 12 KB 扇区 1~2 次），不超时；
	10. GC 之后复位，`CONFIG[2]` 仍是 GC 完成时的值 —— **扇区搬完数据没丢**；
	11. 心跳还在走（存储没把主循环卡死）。

为什么把 GC 单列一条：
	FEE 是日志式存储，平时只往活动扇区尾部追加。写满后要走
	"搬备份扇区 → 擦活动扇区 → 翻活动扇区"这条路径，**平时一次都走不到**。
	它的错误表现是"跑几天/几周之后数据突然全丢"，只有在台上连写几百次才能暴露。
	本工程就是在这一条上抓到一个真实缺陷：FEE 的中转缓存按 demo 抄了 64 字节，
	而 GC 搬块要用它放下一整块（DTC 块 72 字节），越界 8 字节正好冲掉相邻的
	`NvM_Initialized` —— 前 210 次写全部正常，一进 GC 存储就整块哑掉，且不报错。

前置：
	- 板子在跑 H:/as 的 M4 固件；
	- 只需要 COM2，**不需要 Kvaser**（存储栈不碰 CAN）。

用法：
	python tools/m4_check.py                # 复位 + 全量验收（约 15 s）
	python tools/m4_check.py --no-reset     # 不复位，抓当前运行（跳过掉电保持项）
	python tools/m4_check.py --skip-gc      # 跳过 400 次写压测

@author binbina
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

try:
	import serial
except ImportError:
	raise SystemExit("需要 pyserial：pip install pyserial")

JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"

# 块顺序必须与 NvM_Cfg.h 的 NVM_CFG_ID_* 一致
BLOCK_ORDER = ["BOOTCNT", "CONFIG", "VIN", "DTC"]
BLOCK_LEN = {"BOOTCNT": 8, "CONFIG": 32, "VIN": 17, "DTC": 64}

VIN_DEFAULT = b"CVM0146M4NVM00001"
BOOTCNT_MAGIC = b"BCM1"

RE_DUMP = re.compile(r"^\s*(\d+)\s+(\w+)\s+len=(\d+)\s+st=(\d+)\s+data=((?:[0-9a-f]{2}\s*)*)$")
RE_BOOT = re.compile(r"^\s*nvm\s+:\s+DFlash\s+([0-9]+)x([0-9]+)\s*KB.*boot\s+#(\d+)")
RE_TIMEOUT = re.compile(r"\[nvm\]\s+TIMEOUT")
RE_HB = re.compile(r"\[\s*(\d+) ms\] alive #(\d+)")


def reset_run():
	"""J-Link 复位并运行。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


def read_for(ser, seconds):
	t_end = time.time() + seconds
	buf = ""
	while time.time() < t_end:
		buf += ser.read(8192).decode("utf-8", "replace")
	return buf


def boot_and_read(ser, seconds=1.6):
	"""复位，然后抓一段串口。"""
	ser.reset_input_buffer()
	p = reset_run()
	if p.returncode != 0:
		raise SystemExit("[FAIL] J-Link 复位失败")
	return read_for(ser, seconds)


def send_cmd(ser, cmd, seconds=0.8):
	ser.reset_input_buffer()
	ser.write(cmd.encode())
	return read_for(ser, seconds)


def send_cmd_until(ser, cmd, markers, timeout):
	"""发命令，一直读到出现 markers 之一或超时。返回 (文本, 耗时秒, 是否命中)。"""
	ser.reset_input_buffer()
	ser.write(cmd.encode())
	t0 = time.time()
	buf = ""
	while (time.time() - t0) < timeout:
		buf += ser.read(4096).decode("utf-8", "replace")
		if any(m in buf for m in markers):
			return buf, time.time() - t0, True
	return buf, time.time() - t0, False


def parse_dump(text):
	"""把 `!d` 的输出解析成 {块名: (len, st, bytes)}。"""
	out = {}
	for line in text.splitlines():
		m = RE_DUMP.match(line.rstrip())
		if m:
			name = m.group(2)
			data = bytes(int(x, 16) for x in m.group(5).split())
			out[name] = (int(m.group(3)), int(m.group(4)), data)
	return out


def parse_boot(text):
	"""取启动横幅里的 (扇区数, 扇区KB, 启动计数)。"""
	for line in text.splitlines():
		m = RE_BOOT.search(line)
		if m:
			return int(m.group(1)), int(m.group(2)), int(m.group(3))
	return None


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--no-reset", action="store_true")
	ap.add_argument("--skip-gc", action="store_true")
	a = ap.parse_args()

	ser = serial.Serial(a.port, 115200, timeout=0.2)
	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	# ---- 1) 启动横幅 + 启动计数 ----
	if a.no_reset:
		boot = read_for(ser, 0.5)
	else:
		boot = boot_and_read(ser)

	binfo = parse_boot(boot)
	note("横幅: 存储配置行", binfo is not None,
		 "" if binfo else "没找到 'nvm : DFlash NxM KB ... boot #k'")
	note("横幅: 初始化未超时", RE_TIMEOUT.search(boot) is None)
	if binfo:
		note("存储: 2 个扇区 x 12 KB", (binfo[0], binfo[1]) == (2, 12),
			 "实为 %dx%d KB" % (binfo[0], binfo[1]))

	boot_no = binfo[2] if binfo else -1

	# ---- 2) 块表 ----
	d = parse_dump(send_cmd(ser, "!d", 0.6))
	note("块表: 4 个块齐全", all(b in d for b in BLOCK_ORDER),
		 "实得 %s" % sorted(d.keys()))
	for b in BLOCK_ORDER:
		if b in d:
			note("块长 %s = %d" % (b, BLOCK_LEN[b]), d[b][0] == BLOCK_LEN[b],
				 "实为 %d" % d[b][0])

	if "BOOTCNT" in d:
		ln, st, dat = d["BOOTCNT"]
		note("BOOTCNT: 数据有效 (st=0)", st == 0, "st=%d" % st)
		note("BOOTCNT: 魔数 'BCM1'", dat[4:8] == BOOTCNT_MAGIC, dat.hex(" "))

	if "VIN" in d:
		# `!d` 只打前 8 字节，按实际长度比 —— 拿 17 字节去比 8 字节永远不相等
		got = d["VIN"][2]
		note("VIN: 未写过 -> ROM 默认值", got == VIN_DEFAULT[:len(got)],
			 "%s（期望前缀 %s）" % (got.hex(" "), VIN_DEFAULT[:len(got)].hex(" ")))

	# ---- 3) 掉电保持：连复位两次，计数必须每次 +1 ----
	if not a.no_reset and boot_no >= 0:
		b2 = parse_boot(boot_and_read(ser))
		note("掉电保持: 复位后计数 +1", b2 is not None and b2[2] == boot_no + 1,
			 "%d -> %s" % (boot_no, b2[2] if b2 else "?"))
		if b2:
			b3 = parse_boot(boot_and_read(ser))
			note("掉电保持: 再复位再 +1", b3 is not None and b3[2] == b2[2] + 1,
				 "%d -> %s" % (b2[2], b3[2] if b3 else "?"))

	# ---- 4) 延迟落盘：改 RAM -> 标脏 -> WriteAll ----
	before = parse_dump(send_cmd(ser, "!d", 0.5))
	r = send_cmd(ser, "!w", 1.2)
	note("延迟落盘: !w 受理", "marked dirty" in r, r.strip()[:60])
	after = parse_dump(send_cmd(ser, "!d", 0.6))
	if ("CONFIG" in before) and ("CONFIG" in after):
		v0 = before["CONFIG"][2][1]
		v1 = after["CONFIG"][2][1]
		note("延迟落盘: WriteAll 后 CONFIG 落盘 (st=0)", after["CONFIG"][1] == 0,
			 "st=%d" % after["CONFIG"][1])
		note("延迟落盘: CONFIG[1] 递增", v1 == (v0 + 1) & 0xFF, "%d -> %d" % (v0, v1))
		cfg1 = v1
	else:
		cfg1 = None

	# ---- 5) 复位后 CONFIG[1] 仍在 ----
	if (not a.no_reset) and (cfg1 is not None):
		boot_and_read(ser)
		d2 = parse_dump(send_cmd(ser, "!d", 0.6))
		note("延迟落盘: 复位后 CONFIG[1] 保持",
			 "CONFIG" in d2 and d2["CONFIG"][2][1] == cfg1,
			 "期望 %d，实为 %s" % (cfg1, d2.get("CONFIG", (0, 0, b"\0"))[2][1]))

	# ---- 6) DET 参数检查 ----
	r = send_cmd(ser, "!x", 0.6)
	note("DET: 非法块 id 上报 mod=20 api=0x0b err=0x0a",
		 "[det] mod=20 api=0x0b err=0x0a" in r, r.strip()[:80])

	# ---- 7) GC 压测 ----
	cfg2 = None
	if not a.skip_gc:
		pre = parse_dump(send_cmd(ser, "!d", 0.5))
		v_pre = pre["CONFIG"][2][2] if "CONFIG" in pre else None

		r, dt, hit = send_cmd_until(ser, "!p",
									("stress done", "stress TIMEOUT", "stress REJECTED"), 30.0)
		note("GC: 400 次写完成且未超时",
			 hit and ("stress done" in r) and (RE_TIMEOUT.search(r) is None),
			 r.strip().splitlines()[0][:80] if r.strip() else "(无输出)")

		m = re.search(r"config\[2\]=(\d+)", r)
		if (m is not None) and (v_pre is not None):
			note("GC: CONFIG[2] 与写入次数一致 (mod 256)",
				 int(m.group(1)) == (v_pre + 400) & 0xFF,
				 "起始 %d -> 实得 %s" % (v_pre, m.group(1)))
			cfg2 = int(m.group(1))
		note("GC: 耗时合理 (<10 s)", dt < 10.0, "%.2f s" % dt)

		# GC 之后复位，数据必须还在
		if (cfg2 is not None) and (not a.no_reset):
			boot_and_read(ser)
			d3 = parse_dump(send_cmd(ser, "!d", 0.6))
			note("GC: 复位后 CONFIG[2] 保持（扇区搬完没丢）",
				 "CONFIG" in d3 and d3["CONFIG"][2][2] == cfg2,
				 "期望 %d，实为 %s" % (cfg2, d3.get("CONFIG", (0, 0, b"\0\0\0"))[2][2]
									  if "CONFIG" in d3 else "?"))

	# ---- 8) 主循环还活着 ----
	r = read_for(ser, 2.2)
	hbs = RE_HB.findall(r)
	note("心跳: 存储栈没卡住主循环", len(hbs) >= 1, "收到 %d 条" % len(hbs))

	# ---- 汇总 ----
	print("")
	print("M4 存储栈验收 —— %s @115200" % a.port)
	print("=" * 62)
	fail = 0
	for name, ok, detail in results:
		print("  %-44s [%s]%s" % (name, " OK " if ok else "FAIL",
								  ("  " + detail) if (detail and not ok) else ""))
		if not ok:
			fail += 1
	print("=" * 62)
	print("  %d 项，通过 %d，失败 %d" % (len(results), len(results) - fail, fail))
	ser.close()
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
