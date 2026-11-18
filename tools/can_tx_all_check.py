#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""全部 TX 邮箱的实时覆盖：12 个邮箱必须都能**反复**发出帧。

## 为什么按"邮箱"而不是按"报文"验

2026-11-18 的教训（D-CAN-TXINT）：mb11/mb13 的 `intEnable=false` 时，
每个邮箱都能发出**第一帧**，之后永久 `CAN_BUSY`。按报文看只测一次是绿的，
按"重复次数"看才暴露。所以本脚本对每个 TX 邮箱都设了**下限帧数**。

## 覆盖矩阵

| 通道 | 邮箱 | 报文 | 触发方式 | 期望周期 |
|---|---|---|---|---|
| CAN0 | mb0  | 0x123      | `can auto on` | 500 ms |
| CAN0 | mb3  | 0x18FF0002 | `can auto on` | 1000 ms |
| CAN0 | mb4  | 0x7E8      | 诊断 `10 02` | 事件 |
| CAN0 | mb11 | 0x500      | CanNm 周期 | 200 ms |
| CAN0 | mb13 | 0x200      | Com 周期 | 100 ms |
| CAN1 | mb0  | 0x124      | `can auto on` | 500 ms |
| CAN1 | mb2~7 | 六条矩阵  | Com 周期 | 50/100/100/200/100/1000 ms |

用法：
	python tools/can_tx_all_check.py
	python tools/can_tx_all_check.py --window 6

@author binbina
"""

import argparse
import sys
import threading
import time

import can
import serial

# (通道, 报文 ID, 名称, 窗口秒数内的最小帧数)
# 下限按"标称速率的 ~75%"取，容忍采样边界与调度抖动；触发方式见文件头。
EXPECT = [
	(0, 0x123,      "CAN0 mb0  HEARTBEAT", 3),
	(0, 0x18FF0002, "CAN0 mb3  EXT_TX   ", 2),
	(0, 0x7E8,      "CAN0 mb4  DIAG_RESP", 1),
	(0, 0x500,      "CAN0 mb11 NM_TX    ", 12),
	(0, 0x200,      "CAN0 mb13 COM_TX   ", 30),
	(1, 0x124,      "CAN1 mb0  TEST_TX  ", 3),
	(1, 0x18FE4021, "CAN1 mb2  TX_LCSF  ", 55),
	(1, 0x18FF0C21, "CAN1 mb3  TX_CTRL  ", 28),
	(1, 0x0CFDCC21, "CAN1 mb4  TX_OEL   ", 28),
	(1, 0x18FDCD21, "CAN1 mb5  TX_OWW   ", 12),
	(1, 0x18FE4E21, "CAN1 mb6  TX_DOOR  ", 28),
	(1, 0x18FECA21, "CAN1 mb7  TX_DM1   ", 2),
]


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--baud", type=int, default=115200)
	ap.add_argument("--ch0", type=int, default=0)
	ap.add_argument("--ch1", type=int, default=1)
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--window", type=float, default=6.0)
	a = ap.parse_args()

	ser = serial.Serial(a.port, a.baud, timeout=0.2)
	bus = {
		0: can.Bus(interface="kvaser", channel=a.ch0, bitrate=a.bitrate),
		1: can.Bus(interface="kvaser", channel=a.ch1, bitrate=a.bitrate),
	}

	# 先把自测帧关掉再开：确保 0x123/0x124/0x18FF0002 是本次命令打开的，
	# 而不是上一轮遗留状态（否则"覆盖"是假的）。
	ser.write(b"can auto off\r")
	time.sleep(0.3)
	(ser.read(8192))
	ser.write(b"can auto on\r")
	time.sleep(0.3)
	(ser.read(8192))

	print("== 全 TX 邮箱覆盖：窗口 %.1f s ==" % a.window)
	cnt = {}
	lock = threading.Lock()
	stop = threading.Event()

	def reader(ch, b):
		"""每路一个线程：单线程轮询两路会把 100 ms 报文的采样率吃掉一半
		（首版实测 25/60，误报 5 个 FAIL）。"""
		local = {}
		while not stop.is_set():
			m = b.recv(0.05)
			if m is not None:
				local[m.arbitration_id] = local.get(m.arbitration_id, 0) + 1
		with lock:
			for k, v in local.items():
				cnt[(ch, k)] = cnt.get((ch, k), 0) + v

	threads = [threading.Thread(target=reader, args=(ch, b), daemon=True)
	           for ch, b in bus.items()]
	for t in threads:
		t.start()

	t0 = time.time()
	diag_sent = False
	while time.time() - t0 < a.window:
		if (not diag_sent) and (time.time() - t0 >= 1.0):
			# 触发 0x7E8：用 `3E 00`（TesterPresent），**不要用 `10 02`**。
			# `10 02` = programming session，本工程的 App 会把控制权交给 Boot，
			# 于是整块板子进刷写模式、Com/NM 全停，等上位机超时才恢复 ——
			# 首版因此把所有 TX 邮箱都误判成"不发"（串口证据见
			# doc/设计评审/Com发送模式与缺口.md）。
			bus[0].send(can.Message(arbitration_id=0x7E0, is_extended_id=False,
			                        data=[0x02, 0x3E, 0x00, 0, 0, 0, 0, 0]))
			diag_sent = True
		time.sleep(0.01)

	stop.set()
	for t in threads:
		t.join(timeout=1.0)
	ser.write(b"can auto off\r")

	for b in bus.values():
		b.shutdown()
	ser.close()

	print()
	print("  %-22s %-10s %8s %8s" % ("邮箱", "报文", "实测帧数", "下限"))
	fail = 0
	for ch, mid, name, need in EXPECT:
		got = cnt.get((ch, mid), 0)
		ok = got >= need
		print("  %-22s 0x%08X %8d %8d  %s"
		      % (name, mid, got, need, "[ OK ]" if ok else "[FAIL]"))
		if not ok:
			fail += 1

	print("-- %d 个 TX 邮箱，%d 个未达下限" % (len(EXPECT), fail))
	return 1 if fail else 0


if __name__ == "__main__":
	sys.exit(main())
