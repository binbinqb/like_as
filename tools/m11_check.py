#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    m11_check.py
@brief   M11 验收：EcuM 三阶段启动 + ComM/CanSM 标准通信链路

@details @section M11_WHAT 验什么（协议侧，需要 Kvaser）

          M11 把"启动顺序"和"通信开关"从 `main.c` 里搬进了标准模块：

          @code
          EcuM（三张表）→ ComM（仲裁）→ CanSM（控制器/收发器）→ CanIf
          @endcode

          所以本脚本验的是**链路行为**，不是某个函数：

          | 组 | 断言 |
          |---|---|
          | 启动 | 横幅 + `[ecum] RUN`，`EcuM_Init` 里三阶段都跑过（NVM 那条横幅证明 Two 跑过） |
          | 状态 | `!q` → RUN(2)；`!m` → `comm=FULL_COM` + `cannm=NORMAL_OPERATION` |
          | 自动通信 | **没有任何手工 `Init`**，0x123 / 0x500 / 0x200 全都在发 |
          | POST_RUN | `!u` → mode=3，NM 停发（≤2.5 s 内 0 帧） |
          | 回 RUN | `!U` → mode=2，报文恢复 |
          | 控制器可逆 | `!s`/`!g`：这就是 CanSM 做 bus-off 恢复时走的同一条路径 |
          | 诊断回归 | `10 03` 仍正常（链路切换没踩坏 CanTp/Dcm） |

@warning **"bus-off 自动恢复"没有在总线上真的造出来。**
         M5 已经确认实验室单节点造不出 bus-off（ISO 11898-1 §7.1.3：
         error passive 下 ACK 错误不再累加 TEC，见 README「M5 的三个硬事实」①）。
         所以这里验的是**恢复所用的那条路径**（STOPPED→STARTED 可逆），
         而不是"真的 bus-off 之后自己回来"。两者差别必须在文档里写清楚。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-11 | binbina | 首版：EcuM 三阶段 / ComM→CanSM 链路 / RUN↔POST_RUN / 控制器可逆 |
"""

import argparse
import re
import sys
import time

import can
import serial

sys.path.insert(0, "tools")
from isotp_lite import Isotp

PORT = "COM2"
BAUD = 115200
BITRATE = 500000

ID_HB = 0x123          # 应用心跳
ID_NM = 0x500          # 网络管理
ID_SIG = 0x200         # Com 信号
ID_DIAG_REQ = 0x7E0

# EcuM 模式（`EcuM_ModeType`）
ECUM_OFF = 0
ECUM_STARTUP = 1
ECUM_RUN = 2
ECUM_POST_RUN = 3
ECUM_SLEEP = 5

RE_ECUM = re.compile(r"\[ecum\] mode=(\d+)")
RE_NM = re.compile(r"comm=([A-Z_]+)\((\d+)\)\s+cannm=([A-Z_]+)\((\d+)\)")


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--channel", type=int, default=0)
	ap.add_argument("--bitrate", type=int, default=BITRATE)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	ser = serial.Serial(a.port, BAUD, timeout=0.2)
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	def read_for(seconds):
		t0 = time.time()
		buf = ""
		while (time.time() - t0) < seconds:
			buf += ser.read(8192).decode("utf-8", "replace")
		return buf

	def send(cmd, wait=0.25):
		ser.reset_input_buffer()
		ser.write(cmd.encode())
		time.sleep(wait)
		return ser.read(8192).decode("utf-8", "replace")

	def drain(sec=0.4):
		t = time.time()
		while (time.time() - t) < sec:
			bus.recv(0.02)

	def count(seconds, want=None):
		t0 = time.time()
		n = 0
		while (time.time() - t0) < seconds:
			m = bus.recv(0.02)
			if (m is not None) and ((want is None) or (m.arbitration_id == want)):
				n += 1
		return n

	def ecum_mode():
		out = send("!q", 0.2)
		m = RE_ECUM.search(out)
		return int(m.group(1)) if m else None

	def link_state():
		out = send("!m", 0.2)
		m = RE_NM.search(out)
		if m is None:
			return None
		return (m.group(1), int(m.group(2)), m.group(3), int(m.group(4)))

	def wait_mode(want, timeout):
		t0 = time.time()
		last = None
		while (time.time() - t0) < timeout:
			last = ecum_mode()
			if last == want:
				return True, time.time() - t0, last
			time.sleep(0.1)
		return False, time.time() - t0, last

	def wait_traffic(arb_id, timeout):
		"""等到该 ID 出现一帧，返回 (ok, 用时)。"""
		t0 = time.time()
		while (time.time() - t0) < timeout:
			m = bus.recv(0.05)
			if (m is not None) and (m.arbitration_id == arb_id):
				return True, time.time() - t0
		return False, time.time() - t0

	# ---------- 0) 复位启动 ----------
	if not a.no_reset:
		ser.reset_input_buffer()
		import subprocess
		import tempfile
		import os
		script = os.path.join(tempfile.gettempdir(), "_m11_run.jlink")
		with open(script, "w", encoding="ascii") as f:
			f.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
		subprocess.run([r"C:\Program Files\SEGGER\JLink\JLink.exe", "-ExitOnError", "1",
		                "-CommanderScript", script],
		               capture_output=True, text=True, timeout=60, stdin=subprocess.DEVNULL)
		boot = read_for(1.8)
	else:
		boot = read_for(0.6)

	note("启动: 横幅正常", ("bring-up" in boot) and ("CVM0146" in boot))
	note("启动: 三阶段都跑过（NVM 横幅来自 DriverInitTwo）",
	     "nvm   : DFlash" in boot,
	     ([l.strip() for l in boot.splitlines() if "nvm   :" in l] or ["(无)"])[0][:64])
	note("启动: 进入 RUN", "[ecum] RUN" in boot)
	note("启动: 无 PCC 时钟/Configure 超时",
	     ("PCC 时钟使能失败" not in boot) and ("Configure 握手超时" not in boot))

	# ---------- 1) EcuM 模式 ----------
	note("!q: 当前是 RUN", ecum_mode() == ECUM_RUN, "mode=%s" % ecum_mode())

	# ---------- 2) 链路状态 ----------
	st = link_state()
	note("!m: ComM 已进入 FULL_COM", (st is not None) and (st[0] == "FULL_COM_NETWORK_REQUESTED"),
	     st[0] if st else "(无)")
	note("!m: CanNm 在 NORMAL_OPERATION", (st is not None) and (st[2] == "NORMAL_OPERATION"),
	     st[2] if st else "(无)")

	# ---------- 3) 自动通信（没有任何手工 Init） ----------
	drain(0.5)
	ok_hb, _ = wait_traffic(ID_HB, 1.5)
	ok_nm, _ = wait_traffic(ID_NM, 1.5)
	ok_sig, _ = wait_traffic(ID_SIG, 1.5)
	note("自动通信: 心跳 0x123 在发", ok_hb)
	note("自动通信: NM 0x500 在发（ComM 请求到了 CanNm）", ok_nm)
	note("自动通信: 信号 0x200 在发（ComM → Com 分组已启动）", ok_sig)

	# ---------- 4) 诊断回归（进 RUN 之后链路没坏） ----------
	tp = Isotp(bus)
	r = tp.request([0x10, 0x03], 2.0)
	note("回归: 诊断 10 03 正常", (r is not None) and (r[:2] == b"\x50\x03"),
	     r.hex(" ") if r else "(无响应)")

	# ---------- 5) 控制器停止/启动可逆（CanSM 的 bus-off 恢复路径） ----------
	send("!s", 0.3)
	drain(0.6)
	n_sig_stop = count(1.0, ID_SIG)
	note("!s: 控制器停止后信号报文停发", n_sig_stop == 0, "%d 帧 / 1.0 s" % n_sig_stop)

	send("!g", 0.3)
	drain(0.6)
	n_sig_go = count(1.0, ID_SIG)
	note("!g: 控制器启动后信号报文恢复", n_sig_go >= 5, "%d 帧 / 1.0 s" % n_sig_go)

	# ---------- 6) RUN → POST_RUN ----------
	send("!u", 0.25)
	ok_pr, dt_pr, last = wait_mode(ECUM_POST_RUN, 2.0)
	note("!u: EcuM 进入 POST_RUN", ok_pr, "%.1f s, mode=%s" % (dt_pr, last))

	# POST_RUN 之后 ComM 释放网络 → NM 走 ReadySleep → 停发
	drain(0.5)
	alive = 0
	t0 = time.time()
	while (time.time() - t0) < 2.5:
		m = bus.recv(0.05)
		if (m is not None) and (m.arbitration_id == ID_NM):
			alive += 1
	note("POST_RUN: NM 报文已停发", alive == 0, "%d 帧 / 2.5 s" % alive)

	# ---------- 7) POST_RUN → RUN ----------
	send("!U", 0.25)
	ok_run, dt_run, last = wait_mode(ECUM_RUN, 2.0)
	note("!U: EcuM 回到 RUN", ok_run, "%.1f s, mode=%s" % (dt_run, last))

	drain(0.4)
	ok_nm2, dt_nm2 = wait_traffic(ID_NM, 2.5)
	note("!U: NM 报文恢复", ok_nm2, "%.1f s" % dt_nm2)
	ok_sig2, dt_sig2 = wait_traffic(ID_SIG, 2.5)
	note("!U: 信号报文恢复（Com 分组由 ComM 重新启动）", ok_sig2, "%.1f s" % dt_sig2)

	# ---------- 8) 收尾：留在 RUN，别影响下一条验收 ----------
	send("!a", 0.2)

	bus.shutdown()
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
