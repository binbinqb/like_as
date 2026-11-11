#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M8 验收（第一段）：多扩展帧接收能力 —— CanNm / Com 的前置条件。

验收判据：
	1. **多邮箱并行**：4 个不同 PGN 的 29 位扩展帧，分别落到 PDU 6~9；
	2. **掩码分组**：同一 PGN（0xFF01）、不同源地址（0x00 和 0xAB）都进同一个 PDU 5，
	   证明"一条过滤项匹配一组报文"成立；
	3. **负例过滤**：同 PGN 段但不同 PGN（0xFF02）收不到 —— 证明是**真过滤**
	   而不是"所有扩展帧都放进来"；
	4. **标准帧不受影响**：0x321 仍走 PDU 0；
	5. **诊断链路不受影响**：`10 03` 仍正常（新加的邮箱没抢诊断的邮箱）。

## 为什么单独做这一段

原计划里记着一条"RX mailbox 只支持标准帧"的结论，它被列为
「Foton 49 条 29-bit 报文」的硬阻塞，也卡着 CanNm / Com / J1939Tp。
本次实测**推翻了**这个结论：

- `FlexCanDrv_SetMsgId()`（`flexcan_drv.c:164`）对 `isExt` 分支
  正确置了 `CS.IDE | CS.SRR`，29 位 ID 写进 `ID` 字（mask `0x1FFFFFFF`）；
- 容量够：`canRamNum=3` × 512 字节 ÷ 16 = **96 个邮箱**（CAN0），
  CAN1 是 64 个，49 条报文远未到上限。

所以真正需要验证的不是"能不能收扩展帧"（M2 就验过一条），
而是**多邮箱并行 + 掩码分组** —— 这两件才是 Foton 场景的实际用法。

## 两个硬约束（配表时必须遵守，否则静默失效）

**① CanIf 表必须按 `canid` 升序**

`CanIf_RxDispatch()`（`CanIf.c:104`）用的是**二分查找**，
靠 `var->canid` 与来帧 ID 比较收缩区间。乱序会让某些项永远搜不到。

**② 掩码项必须排在所有精确项之后**

掩码项代表一个 ID 区间，夹在精确项中间会让二分在一个方向上判错。
本工程的掩码项（0x18FF0100 / mask 0x1FFFFF00）是全表 `canid` 最大的一条，
天然在末尾。

这两条都不会报错，症状只是"某条报文收不到"。

前置：
	- 板子在跑 M8 固件；
	- Kvaser ch0 接 CAN0（500 kbps）；
	- COM2 串口。

用法：
	python tools/m8_check.py

@author binbina
"""

import argparse
import re
import sys
import time

try:
	import can
	import serial
except ImportError:
	raise SystemExit("需要 python-can / pyserial：pip install python-can pyserial")

from isotp_lite import Isotp

PORT = "COM2"
BAUD = 115200

# 串口打印格式：`[can] rx #3 pdu=6 (CAN0 0x18FEF100(ext)) dlc=8 data=11 22 ...`
RE_RX = re.compile(r"\[can\] rx #(\d+) pdu=(\d+) \((.+?)\) dlc=(\d+)")

# 期望：ID → (PDU 编号, 说明)
CASES = [
	(0x18FF0100, 5, "掩码组 源地址 0x00"),
	(0x18FF01AB, 5, "掩码组 源地址 0xAB"),
	(0x18FEF100, 6, "PGN 0xFEF1"),
	(0x18FEC100, 7, "PGN 0xFEC1"),
	(0x18FEB100, 8, "PGN 0xFEB1"),
	(0x18FEA100, 9, "PGN 0xFEA1"),
]

# 负例：同 PGN 段、不同 PGN，必须收不到
NEGATIVE = [(0x18FF0200, "PGN 0xFF02（不在过滤表里）")]

DATA = [0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88]


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--channel", type=int, default=0)
	ap.add_argument("--bitrate", type=int, default=500000)
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	print("=" * 72)
	print(" M8 验收（第一段）：多扩展帧接收能力")
	print("=" * 72)

	ser = serial.Serial(a.port, BAUD, timeout=0.2)
	ser.reset_input_buffer()
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	# 清掉启动日志
	time.sleep(0.5)
	ser.read(16384)

	def send_ext(cid, ext=True):
		bus.send(can.Message(arbitration_id=cid, is_extended_id=ext,
							 data=DATA, dlc=8))

	# ---------- 1) 多扩展帧 ----------
	ser.reset_input_buffer()
	for cid, _, _ in CASES:
		send_ext(cid)
		time.sleep(0.12)
	time.sleep(0.5)
	out = ser.read(16384).decode("utf-8", "replace")
	got = [(int(m.group(2)), m.group(3)) for m in RE_RX.finditer(out)]

	note("7 帧扩展帧：收到 6 帧", len(got) == 6, "实际 %d 帧" % len(got))

	# 逐条核对 PDU 编号（按发送顺序）
	for i, (cid, pdu, name) in enumerate(CASES):
		if i < len(got):
			note("0x%08X → PDU %d（%s）" % (cid, pdu, name),
				 got[i][0] == pdu, "实际 PDU %d" % got[i][0])
		else:
			note("0x%08X → PDU %d（%s）" % (cid, pdu, name), False, "(未收到)")

	# ---------- 2) 掩码分组：两个源地址进同一个 PDU ----------
	src_pdus = [g[0] for i, g in enumerate(got) if i < 2]
	note("掩码分组：两个源地址都进 PDU 5",
		 len(src_pdus) == 2 and src_pdus[0] == 5 and src_pdus[1] == 5,
		 "实际 %s" % src_pdus)

	# ---------- 3) 负例 ----------
	ser.reset_input_buffer()
	for cid, _ in NEGATIVE:
		send_ext(cid)
		time.sleep(0.15)
	time.sleep(0.4)
	out = ser.read(8192).decode("utf-8", "replace")
	note("负例：0x18FF0200 被过滤（收不到）",
		 len(RE_RX.findall(out)) == 0,
		 "收到 %d 帧" % len(RE_RX.findall(out)))

	# ---------- 4) 标准帧回归 ----------
	ser.reset_input_buffer()
	send_ext(0x321, ext=False)
	time.sleep(0.4)
	out = ser.read(8192).decode("utf-8", "replace")
	m = RE_RX.search(out)
	note("回归：标准帧 0x321 仍走 PDU 0", (m is not None) and (m.group(2) == "0"),
		 m.group(0)[:40] if m else "(未收到)")

	# ---------- 5) 诊断链路回归 ----------
	tp = Isotp(bus)
	r = tp.request([0x10, 0x03])
	note("回归：0x10 03 仍正常", (r is not None) and (r[:2] == b"\x50\x03"),
		 r.hex(" ") if r else "(无响应)")

	bus.shutdown()
	ser.close()

	print()
	ok_n = 0
	for name, ok, detail in results:
		mark = "PASS" if ok else "FAIL"
		if ok:
			ok_n += 1
		line = "  [%s] %s" % (mark, name)
		if detail:
			line += "   (%s)" % detail
		print(line)

	fail = len(results) - ok_n
	print()
	print("%d 项，通过 %d，失败 %d" % (len(results), ok_n, fail))
	print("=" * 72)
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
