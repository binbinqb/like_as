#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""A2 验收：接收信号的四态有效性（NEVER_RECEIVED / VALID / INVALID / TIMEOUT）。

## 为什么四态必须分别构造

以前只有一个维度（`Bcm_SwStateType`），于是"对方没说"和"对方说了无效"
必然撞在同一个值 `UNKNOWN` 上。判据因此必须能**分别复现四态**，
而且每种状态的 `*st` 也要对：

| 构造方式 | 期望有效性 | 期望值 |
|---|---|---|
| 复位后一帧都不发 | `NEVER` | `UNKNOWN` |
| 发 raw=1（ParkingBrakeSet） | `VALID` | `ON` |
| 发 raw=0（NotSet） | `VALID` | `OFF` |
| 发 raw=2（Error） | `VALID` | `FAULT` |
| 发 raw=3（NotAvailable） | `INVALID` | `UNKNOWN` |
| 发过之后停发 > 300 ms | `TIMEOUT` | `UNKNOWN` |
| 超时后再发一帧 | `VALID` | 随 raw |

`raw=2` 那一条是整套判据的分水岭：它证明 `FAULT`（对方明确报错）
**不会**被误判成 `INVALID`（值不可用）。这两者的处置不同 ——
前者要报 DTC 并关输出，后者只是不要用这个值。

## 前置

- 板子在跑含 A2 的 App 固件（`bcm rx` 命令存在）；
- Kvaser ch1 接 CAN1（500 kbps），本机扮 `CCVS` 的发送方（0x18FEF121）；
- COM2 串口（板级 shell）；
- J-Link 已连接（用于复位，`--no-reset` 可跳过）。

用法：
	python tools/a2_validity_check.py
	python tools/a2_validity_check.py --no-reset

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
	import can
except ImportError:
	raise SystemExit("需要 python-can：pip install python-can")

try:
	import serial
except ImportError:
	raise SystemExit("需要 pyserial：pip install pyserial")

JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"

CCVS_ID = 0x18FEF121
# ParkingBrakeSwitch：`2|2@1+`，位于 byte0 的 bit2..3
BRAKE_SHIFT = 2
# 与 bcm_sig_cfg.c 的门限一致（CCVS 周期 100 ms × 3）
TIMEOUT_MS = 300
# 判超时前多等的时间：主函数 10 ms 一拍 + 串口往返，留 200 ms 余量
TIMEOUT_WAIT_S = (TIMEOUT_MS / 1000.0) + 0.2

# `bcm rx` 的输出：`  bcm rx park brake = OFF     [VALID   age=123 ms]`
RE_RX = re.compile(r"park brake = (\w+)\s+\[(\w+)\s+age=(--|\d+)")


def reset_run():
	"""J-Link 复位并运行（`r` 复位、`g` 运行）。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run_a2.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
	                      capture_output=True, text=True, timeout=60,
	                      stdin=subprocess.DEVNULL)


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--baud", type=int, default=115200)
	ap.add_argument("--channel", type=int, default=1, help="接 CAN1 的 Kvaser 通道")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true",
	                help="不复位（此时 NEVER_RECEIVED 一项必然失败，除非刚上电）")
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))
		print("  [%s] %s%s" % ("PASS" if ok else "FAIL", name,
		                       ("   (%s)" % detail) if detail else ""))

	ser = serial.Serial(a.port, a.baud, timeout=0.2)
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	def send_raw(raw, count=3):
		"""按 raw 值构造一帧 CCVS 并发 `count` 次。"""
		data = bytearray(8)
		data[0] = (raw & 0x03) << BRAKE_SHIFT
		msg = can.Message(arbitration_id=CCVS_ID, data=bytes(data),
		                  is_extended_id=True, dlc=8)
		for _ in range(count):
			try:
				bus.send(msg)
			except can.CanError:
				pass
			time.sleep(0.02)
		# 等主函数把新值搬进 shadow（10 ms 一拍，留 3 拍余量）
		time.sleep(0.05)

	def drain(sec=0.2):
		t = time.time()
		while time.time() - t < sec:
			bus.recv(0.02)

	def cmd(text, wait=0.3):
		ser.reset_input_buffer()
		if not text.endswith("\n"):
			text += "\n"
		ser.write(text.encode())
		ser.flush()
		time.sleep(wait)
		return ser.read(65536).decode("utf-8", "replace")

	def read_rx():
		"""(state, validity, age) —— age 为 None 表示 `--`。"""
		out = cmd("bcm rx", 0.3)
		m = RE_RX.search(out)
		if m is None:
			return None
		age = None if m.group(3) == "--" else int(m.group(3))
		return m.group(1), m.group(2), age

	try:
		print("=" * 78)
		print("A2 验收：接收信号四态有效性")
		print("=" * 78)

		# ---------- 1. NEVER_RECEIVED ----------
		print("\n--- 1 复位后一帧不发：NEVER ---")
		if not a.no_reset:
			p = reset_run()
			if p.returncode != 0:
				print("  [FAIL] J-Link 复位失败")
				return 1
			time.sleep(1.2)      # 等 Banner 与 EcuM 起来
		drain(0.3)               # 清掉复位前的残留帧（Kvaser 驱动会缓存）
		cmd("bcm rx", 0.2)       # 丢掉第一条（可能还在打印 Banner）

		r = read_rx()
		note("复位后无帧 → NEVER", r is not None and r[1] == "NEVER",
		     "读到 %s" % (r,))
		note("NEVER 时值为 UNKNOWN", r is not None and r[0] == "UNKNOWN",
		     "读到 %s" % (r,))
		note("NEVER 时 age 打 `--`（不是 0）", r is not None and r[2] is None,
		     "读到 %s" % (r,))

		# ---------- 2. VALID：三个有意义的值 ----------
		print("\n--- 2 发帧：VALID 且语义对 ---")
		for raw, exp_state in ((1, "ON"), (0, "OFF"), (2, "FAULT")):
			send_raw(raw)
			r = read_rx()
			note("raw %d → VALID / %s" % (raw, exp_state),
			     r is not None and r[1] == "VALID" and r[0] == exp_state,
			     "读到 %s" % (r,))

		# ---------- 3. INVALID：raw=3 是"对方说不可用" ----------
		print("\n--- 3 raw=3：INVALID（不是 TIMEOUT，也不是 FAULT）---")
		send_raw(3)
		r = read_rx()
		note("raw 3 → INVALID", r is not None and r[1] == "INVALID", "读到 %s" % (r,))
		note("INVALID 时值为 UNKNOWN", r is not None and r[0] == "UNKNOWN",
		     "读到 %s" % (r,))
		note("INVALID 与 FAULT 不混淆（上一段 raw 2 是 VALID）",
		     r is not None and r[1] != "VALID", "读到 %s" % (r,))

		# ---------- 4. TIMEOUT ----------
		print("\n--- 4 停发 %.0f ms：TIMEOUT ---" % (TIMEOUT_WAIT_S * 1000))
		send_raw(1)                     # 先给一个有效值，证明是"后来断的"
		r0 = read_rx()
		note("超时前是 VALID", r0 is not None and r0[1] == "VALID", "读到 %s" % (r0,))
		time.sleep(TIMEOUT_WAIT_S)
		r = read_rx()
		note("停发后 → TIMEOUT", r is not None and r[1] == "TIMEOUT", "读到 %s" % (r,))
		note("TIMEOUT 时值为 UNKNOWN（不返回旧值）",
		     r is not None and r[0] == "UNKNOWN", "读到 %s" % (r,))
		note("TIMEOUT 的 age > %d ms" % TIMEOUT_MS,
		     r is not None and r[2] is not None and r[2] > TIMEOUT_MS,
		     "age=%s" % (r[2] if r else "?"))

		# ---------- 5. 恢复 ----------
		print("\n--- 5 超时后再发一帧：回到 VALID ---")
		send_raw(2)
		r = read_rx()
		note("恢复后 → VALID / FAULT",
		     r is not None and r[1] == "VALID" and r[0] == "FAULT",
		     "读到 %s" % (r,))
		note("恢复后 age 重新变小（< 100 ms）",
		     r is not None and r[2] is not None and r[2] < 100,
		     "age=%s" % (r[2] if r else "?"))

		# ---------- 6. 隔离性：别的报文不能刷新这个信号的年龄 ----------
		print("\n--- 6 隔离：同总线的 LCSF 不能刷新 CCVS 的年龄 ---")
		time.sleep(TIMEOUT_WAIT_S)
		r_before = read_rx()
		# 读一次 dump 期间 LCSF 一直在发（50 ms 周期），年龄仍在增长
		time.sleep(0.15)
		r_after = read_rx()
		note("LCSF 在发但 CCVS 仍判 TIMEOUT",
		     r_after is not None and r_after[1] == "TIMEOUT",
		     "读到 %s" % (r_after,))
		note("年龄单调增长（证明确实按 PDU 计）",
		     r_before is not None and r_after is not None
		     and r_before[2] is not None and r_after[2] is not None
		     and r_after[2] > r_before[2],
		     "%s → %s" % (r_before[2] if r_before else "?",
		                  r_after[2] if r_after else "?"))

		# ---------- 7. 回归：dump 与灯控未被破坏 ----------
		print("\n--- 7 回归 ---")
		out = cmd("bcm", 0.35)
		note("`bcm` 仍列出 11 个灯", out.count("  ") > 0 and
		     len(re.findall(r"^\s{3}[a-z]+\s{2,}(?:UNKNOWN|OFF|ON|FAULT)\s*$",
		                    out, re.M)) == 11,
		     "行数 %d" % len(re.findall(
			     r"^\s{3}[a-z]+\s{2,}(?:UNKNOWN|OFF|ON|FAULT)\s*$", out, re.M)))
		cmd("bcm all on", 0.25)
		out = cmd("bcm", 0.35)
		note("`bcm all on` 仍生效", "ON" in out, "")

	finally:
		cmd("bcm all off", 0.2)
		bus.shutdown()
		ser.close()

	ok = sum(1 for _, o, _ in results if o)
	total = len(results)
	print("\n" + "=" * 78)
	if ok == total:
		print("PASS %d / %d" % (ok, total))
	else:
		print("FAIL %d / %d" % (total - ok, total))
		for name, o, detail in results:
			if not o:
				print("  - %s   %s" % (name, detail))
	print("=" * 78)
	return 0 if ok == total else 1


if __name__ == "__main__":
	sys.exit(main())
