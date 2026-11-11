#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M1 验收：MCAL（Port/Dio/Can）驱动真实 CAN 收发。

验收判据：
	1. 启动横幅是 M1，且打印了 CAN 配置行；
	2. **TX**：Kvaser ch0 收到 `0x123`，DLC=8，标准帧，数据**逐帧 +1**
	   （只看到"有帧"不够 —— 数据不动说明发的是同一份缓冲，可能根本没刷新）；
	3. **RX**：Kvaser 发 `0x321`，板子收到并通过 COM2 打印出来；
	4. 心跳仍在走（证明 Can 初始化没有把主循环卡住）。

前置：
	- 板子在跑 H:/as 的 M1 固件；
	- Kvaser **通道 0** 接板子 CAN0（实测 ch0=CAN0，ch1=CAN1，见 tools/can_probe.py）。

用法：
	python tools/m1_check.py                 # 复位 + 验收
	python tools/m1_check.py --no-reset      # 不复位，抓当前运行
	python tools/m1_check.py --channel 1     # 换 Kvaser 通道

@author binbina
"""

# 注（M2）：固件横幅已改为 (M2)，RX 打印格式已改为 `pdu=N (0x...)`，
# 所以本脚本里"横幅 in (M1)"和"id=0x321"两条断言不再成立。
# M2 验收请用 tools/m2_check.py —— 它覆盖 M1 的全部判据，并额外验证
# 扩展帧收发与 CanIf 的 TX 确认回调。本脚本保留作为 M1 的历史记录。

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

TX_ID = 0x123      # 板子发的
RX_ID = 0x321      # 板子收的（要在 CanAc.c 的邮箱表里，否则收不到）

RE_HB = re.compile(rb"\[\s*(\d+) ms\] alive #(\d+)")


def reset_run():
	"""J-Link 复位并运行。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--channel", type=int, default=0, help="Kvaser 通道号（0=CAN0）")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	ser = serial.Serial(a.port, 115200, timeout=0.2)
	ser.reset_input_buffer()
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	if not a.no_reset:
		p = reset_run()
		if p.returncode != 0:
			print("[FAIL] J-Link 复位失败")
			return 1

	results = []

	# ---- 1) 启动横幅 ----
	time.sleep(0.4)
	boot = ser.read(16384).decode("utf-8", "replace")
	results.append(("横幅: bring-up (M1)", "(M1)" in boot))
	results.append(("横幅: CAN 配置行", "can   : CAN0 500 kbps" in boot))

	# ---- 2) TX：0x123 且数据逐帧 +1 ----
	# 先把 Kvaser 缓冲里的旧帧读掉：复位前那批帧的序号与复位后接不上，
	# 混在一起会让"递增"判据误判（实测收到 9 帧，而 3 s 内板子只该发 6 帧）。
	t_flush = time.time()
	while time.time() - t_flush < 0.8:
		bus.recv(timeout=0.05)

	frames = []
	t0 = time.time()
	while time.time() - t0 < 3.0:
		m = bus.recv(timeout=0.2)
		if m is not None and m.arbitration_id == TX_ID:
			frames.append(m)

	results.append(("TX: 3 s 内收到 >=4 帧 0x123 (实收 %d)" % len(frames), len(frames) >= 4))

	if len(frames) >= 2:
		ok_dlc = all(f.dlc == 8 for f in frames)
		ok_ext = all(not f.is_extended_id for f in frames)
		results.append(("TX: DLC 均为 8", ok_dlc))
		results.append(("TX: 均为标准帧", ok_ext))

		# 板子每发一帧就把整个缓冲 +1。判据取"相邻两帧所有字节的增量相同"，
		# 而不是死磕 ==1：Kvaser 偶发丢帧时增量会是 2/3，那仍然证明
		# "数据是每帧新组的"，而不是"一直在发同一份缓冲"。
		inc_ok = True
		deltas = []
		for i in range(1, len(frames)):
			prev, cur = frames[i - 1].data, frames[i].data
			if len(prev) != len(cur):
				inc_ok = False
				break
			d = {((c - p) & 0xFF) for p, c in zip(prev, cur)}
			if len(d) != 1:
				inc_ok = False
				break
			k = d.pop()
			deltas.append(k)
			if not (1 <= k <= 20):
				inc_ok = False
				break
		results.append(("TX: 数据逐帧递增 (增量 %s)" % (sorted(set(deltas)) or "-"), inc_ok))
	else:
		results.append(("TX: 至少两帧才能验证递增", False))

	# ---- 3) RX：发 0x321，看板子打印 ----
	ser.reset_input_buffer()
	payload = [0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x02, 0x03, 0x04]
	bus.send(can.Message(arbitration_id=RX_ID, data=payload,
						 is_extended_id=False, dlc=8))
	time.sleep(0.5)
	resp = ser.read(16384).decode("utf-8", "replace")

	results.append(("RX: 板子打印 [can] rx", "[can] rx" in resp))
	results.append(("RX: ID 为 0x321", "id=0x321" in resp))
	results.append(("RX: 数据 8 字节全部正确",
					"de ad be ef 01 02 03 04" in resp.lower()))

	# ---- 4) 心跳仍在走 ----
	# 心跳 1 s 一次，窗口必须 >2 s 才可能看到两条
	hb_buf = bytearray(resp.encode())
	t_hb = time.time()
	while time.time() - t_hb < 2.5:
		hb_buf += ser.read(4096)
	hbs = RE_HB.findall(bytes(hb_buf))
	results.append(("心跳: 至少两条 (实收 %d)" % len(hbs), len(hbs) >= 2))

	bus.shutdown()
	ser.close()

	# ---- 判定表 ----
	w = max(len(n) for n, _ in results) + 2
	print()
	print("=" * (w + 14))
	print("  M1 验收 —— %s @ %d / Kvaser ch%d @ %d"
		  % (a.port, 115200, a.channel, a.bitrate))
	print("=" * (w + 14))
	fail = 0
	for name, ok in results:
		print("  %-*s %s" % (w, name, "[ OK ]" if ok else "[FAIL]"))
		if not ok:
			fail += 1
	print("=" * (w + 14))
	print("  %d 项，通过 %d，失败 %d" % (len(results), len(results) - fail, fail))
	print("=" * (w + 14))

	if fail:
		print("\n---- 串口原文 ----")
		print(boot[:900])
		print(resp[:900])
		return 1
	return 0


if __name__ == "__main__":
	sys.exit(main())
