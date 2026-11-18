#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M3 验收：PduR + CanTp + Dcm 最小集（ISO 15765-2 物理寻址 0x7E0/0x7E8）。

验收判据：
	1. 启动横幅有 diag 行；
	2. `10 03` → `50 03 ...`（进扩展会话），串口出现 `[dcm] session 1 -> 3`；
	3. `22 F1 90` → `62 F1 90` + 17 字节 VIN —— **响应 20 字节，必须走多帧**，
	   证 明 TX 侧 FF/CF 分段正常；
	4. `22 F1 87` → `62 F1 87` + 11 字节零件号（单帧，走 SF 路径）；
	5. `3E 00` → `7E 00`（TesterPresent 保活）；
	6. `22 12 34`（未配置 DID）→ `7F 22 31`（requestOutOfRange）；
	7. `12 34 56`（未实现服务）→ `7F 12 11`（serviceNotSupported）；
	   另测 `31 01` 无安全访问 → `7F 31 33`（securityAccessDenied）。
	   注意 0x31 是**已启用**服务（RoutineControl，用于校验/切槽），
	   它的 0x33 检查先于"例程是否存在"，所以不能再拿它当
	   "未实现服务"的例子 —— 这条断言 2026-11-16 才改正；
	8. `2E F1 87` + 11 字节（13 字节长请求）→ `7F 2E 31`（不可写 DID）——
	   **证明 RX 侧 FF/CF 重组正常**：重组失败就一个字节都不会回。
	   注意别用 F190 当例子：M7 起 0x2E 真能写 VIN，会改掉板子上的值；
	9. 静默 6.5 s → 串口出现 `[dcm] session 3 -> 1 (S3 timeout)`，
	   证明 S3Server 计时与自动回默认会话生效。

前置：
	- 板子跑 M3 固件；Kvaser ch0 接 CAN0 @500 kbps，接 120 Ω 终端电阻；
	- 需要 python-can、can-isotp、pyserial：
	  `pip install python-can can-isotp pyserial`

用法：
	python tools/m3_check.py
	python tools/m3_check.py --channel 0 --no-reset

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

from isotp_lite import Isotp, PAD
from _can_keeper import Keeper

REQ_ID = 0x7E0     # 测试仪 → ECU
RES_ID = 0x7E8     # ECU → 测试仪

# M7 起 VIN 的唯一数据源是 NvM 的 VIN 块（0x22 与 0x2E 共用），
# 所以这里断言的是 NvM_Cfg.c 里的 ROM 默认值，不再是 Dcm_Cfg.c 的常量。
VIN = b"CVM0146M4NVM00001"
PART = b"AS-CVM0146A"

def reset_run():
	"""J-Link 复位并运行。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


def uds(tp, data, timeout=1.5):
	"""发一条诊断请求，返回完整响应（bytes）；超时返回 None。"""
	return tp.request(data, timeout)


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--channel", type=int, default=0, help="接 CAN0 的 Kvaser 通道")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	ser = serial.Serial(a.port, 115200, timeout=0.2)
	ser.reset_input_buffer()
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)
	# 另一路必须有人 ACK：否则对端 Com 报文 bus-off 会刷屏并拖慢整机
	kp = Keeper(1 - a.channel, a.bitrate)

	# ISO-TP 物理寻址：txid=0x7E0（我们发），rxid=0x7E8（板子回）
	tp = Isotp(bus, REQ_ID, RES_ID)

	if not a.no_reset:
		p = reset_run()
		if p.returncode != 0:
			print("[FAIL] J-Link 复位失败")
			return 1

	results = []
	log = ""

	def note(name, ok):
		results.append((name, bool(ok)))

	# ---- 1) 横幅 ----
	time.sleep(0.5)
	boot = ser.read(16384).decode("utf-8", "replace")
	log += boot
	note("横幅: diag 0x7E0 -> 0x7E8", "diag  : 0x7E0 -> 0x7E8" in boot)

	# ---- 2) 10 03 进扩展会话 ----
	r = uds(tp, [0x10, 0x03])
	note("0x10: 10 03 收到响应", r is not None)
	note("0x10: 正响应 50 03", r is not None and r[:2] == b"\x50\x03")
	time.sleep(0.3)
	ser_log = ser.read(4096).decode("utf-8", "replace")
	log += ser_log
	note("0x10: 串口记录 session 1 -> 3", "session 1 -> 3" in ser_log)

	# ---- 3) 22 F1 90 读 VIN（多帧响应）----
	r = uds(tp, [0x22, 0xF1, 0x90])
	note("0x22: F190 收到响应", r is not None)
	if r is not None:
		note("0x22: F190 正响应 62 F1 90", r[:3] == b"\x62\xF1\x90")
		note("0x22: F190 数据 = %r" % (r[3:],), r[3:] == VIN)
		# 20 字节响应 > 7，必须走 FF+CF，能收到就证明分段正常
		note("0x22: F190 多帧响应完整 (%d 字节)" % len(r), len(r) == 3 + len(VIN))

	# ---- 4) 22 F1 87 读零件号（单帧响应）----
	r = uds(tp, [0x22, 0xF1, 0x87])
	note("0x22: F187 收到响应", r is not None)
	if r is not None:
		note("0x22: F187 正响应 62 F1 87", r[:3] == b"\x62\xF1\x87")
		note("0x22: F187 数据 = %r" % (r[3:],), r[3:] == PART)

	# ---- 5) 3E 00 保活 ----
	r = uds(tp, [0x3E, 0x00])
	note("0x3E: 3E 00 正响应 7E 00", r is not None and r[:2] == b"\x7E\x00")

	# ---- 6) 未知 DID → 7F 22 31 ----
	r = uds(tp, [0x22, 0x12, 0x34])
	note("NRC: 未知 DID → 7F 22 31",
		 r is not None and r[:3] == b"\x7F\x22\x31")

	# ---- 7) 未实现服务 → 7F xx 11 ----
	# 注意：不要用 0x31 当"未实现服务"的例子。0x31 RoutineControl 是
	# **已启用**的（Dcm_Cfg.h 的 DCM_USE_SERVICE_ROUTINE_CONTROL，用于
	# 校验 / 请求切槽），未做 0x27 安全访问时它回 NRC 0x33
	# （securityAccessDenied）—— 这是正确行为，0x33 的检查先于"例程是否存在"。
	# 所以这里换成真正未启用的 0x12（ReadDataByIdentifier 之外的任意未实现服务）。
	r = uds(tp, [0x12, 0x34, 0x56])
	note("NRC: 未实现服务 0x12 → 7F 12 11",
		 r is not None and r[:3] == b"\x7F\x12\x11")
	# 顺带把 0x31 的当前语义钉住：无安全访问必须回 0x33，不是 0x31/0x11。
	# 将来给 0x31 加安全访问门控时，这条断言会保护"别忘了门控"。
	r = uds(tp, [0x31, 0x01])
	note("NRC: 0x31 无安全访问 → 7F 31 33",
		 r is not None and r[:3] == b"\x7F\x31\x33")

	# ---- 8) 长请求 → 证明 RX 多帧重组 ----
	# 用 0x2E 写 **F187（零件号）**：13 字节请求，必须 FF+CF 才能送到 Dcm。
	# 能收到响应（哪怕是 NRC）就说明重组成功；重组失败会完全静默。
	#
	# 为什么不写 F190：M7 起 0x2E 真的能写 VIN 了，拿它当"未实现服务"的
	# 例子会让这条验收**改掉板子上的 VIN**。F187 只读、不在可写表里，
	# 所以既能验 RX 重组、又不会留下副作用。
	long_req = bytes([0x2E, 0xF1, 0x87]) + b"X" * 11
	r = uds(tp, long_req, timeout=2.0)
	note("RX 多帧: 13 字节长请求得到响应", r is not None)
	note("RX 多帧: 不可写 DID → 7F 2E 31",
		 r is not None and r[:3] == b"\x7F\x2E\x31")

	# ---- 9) S3 超时自动回默认会话 ----
	# 所有请求都刷新 S3 计时，所以这项必须放最后，且要真的静默等
	t_end = time.time() + 7.0
	while time.time() < t_end:
		log += ser.read(2048).decode("utf-8", "replace")
		time.sleep(0.05)
	note("S3: 静默 6.5 s 后回默认会话", "session 3 -> 1 (S3 timeout)" in log)

	kp.close()
	bus.shutdown()
	ser.close()

	# ---- 判定表 ----
	w = max(len(n) for n, _ in results) + 2
	print()
	print("=" * (w + 16))
	print("  M3 验收 —— %s @ %d / Kvaser ch%d / ISO-TP 0x%X -> 0x%X"
		  % (a.port, 115200, a.channel, REQ_ID, RES_ID))
	print("=" * (w + 16))
	fail = 0
	for name, ok in results:
		print("  %-*s %s" % (w, name, "[ OK ]" if ok else "[FAIL]"))
		if not ok:
			fail += 1
	print("=" * (w + 16))
	print("  %d 项，通过 %d，失败 %d" % (len(results), len(results) - fail, fail))
	print("=" * (w + 16))

	if fail:
		print("\n---- 串口原文 ----")
		print(boot[:1200])
		return 1
	return 0


if __name__ == "__main__":
	sys.exit(main())
