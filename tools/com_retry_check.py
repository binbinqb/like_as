#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Com 发送重试用例：控制器停用 → 恢复，验证 bTxRetry 路径。

## 为什么单独一个脚本

`Com_MainFunctionTx()` 在 `PduR_ComTransmit()` 失败时会：

	timer = CycleTime;  bTxRetry = TRUE;

之后由 `Com_MainFunction_Fast()`（同 10 ms 拍）负责重发。这条路径平时跑不到 ——
只有 CAN 控制器停用 / 总线无 ACK / 邮箱全忙时才会触发。**它一旦坏了，
现象是"某条报文发过一次就再也不发"**，与 M10 的周期断言完全不同的失效模式。

## 怎么制造"发送失败"

`can ctrl stop` → `CanIf_SetControllerMode(STOPPED)` → `Can_Write()` 失败 →
`PduR_ComTransmit` 返回 E_NOT_OK → Com 置 `bTxRetry`。
`can ctrl start` 之后，下一拍 Fast 就应该把积压的那一帧补发出去。

## 断言

| # | 断言 | 判据 |
|---|---|---|
| R1 | 基线速率 | 1.5 s 内 12~18 帧（100 ms 周期 ±20%） |
| R2 | 停用期间不发 | `can ctrl stop` 后 1 s 内 0 帧 |
| R3 | 恢复及时 | `can ctrl start` 后 0.5 s 内出现首帧 |
| R4 | 恢复后速率 | 2 s 内 18~24 帧 |
| R5 | 计数器连续 | 恢复后首帧的 cnt 比停用前末帧大 ≥5（时间照走，不是重启） |

用法：
	python tools/com_retry_check.py
	python tools/com_retry_check.py --port COM2 --channel 0

@author binbina
"""

import argparse
import re
import sys
import time

import can
import serial

MSG_ID = 0x200


def drain(bus, sec):
	"""收集 sec 秒内的 0x200，返回 [(timestamp, tx_counter)]。"""
	t0 = time.time()
	out = []
	while time.time() - t0 < sec:
		m = bus.recv(0.05)
		if m is not None and m.arbitration_id == MSG_ID:
			out.append((m.timestamp, int(m.data[0])))
	return out


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--baud", type=int, default=115200)
	ap.add_argument("--channel", type=int, default=0)
	ap.add_argument("--bitrate", type=int, default=500000)
	a = ap.parse_args()

	ser = serial.Serial(a.port, a.baud, timeout=0.2)
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	print("== Com 重试用例（0x%03X） ==" % MSG_ID)

	base = drain(bus, 1.5)
	n_base = len(base)
	last_cnt = base[-1][1] if base else None
	print("  基线：%d 帧/1.5 s，末帧 cnt=%s" % (n_base, last_cnt))

	ser.write(b"can ctrl stop\r")
	time.sleep(0.4)
	(ser.read(4096))
	time.sleep(0.6)
	gap = drain(bus, 1.0)
	print("  停用期间：%d 帧" % len(gap))

	ser.write(b"can ctrl start\r")
	t_start = time.time()
	time.sleep(0.2)
	(ser.read(4096))
	rec = drain(bus, 2.0)
	t_first = (rec[0][0] - t_start) if rec else None

	# 速率必须按**帧时间戳**算：`drain()` 的墙钟窗口会把 start 前积压在
	# CanIf 队列里的帧一并收进来（首帧可能是停用期间的旧值），
	# 用帧数/墙钟会把速率算高，2026-11-18 首版就在这里误报过。
	rate = 0.0
	if len(rec) >= 2:
		span = rec[-1][0] - rec[0][0]
		rate = (len(rec) - 1) / span if span > 0 else 0.0
	deltas = [((rec[i + 1][1] - rec[i][1]) & 0xFF) for i in range(len(rec) - 1)]
	print("  恢复：首帧 %.2f s，2 s 内 %d 帧，速率 %.1f 帧/s，cnt 前 3 = %s"
	      % (t_first if t_first is not None else -1, len(rec), rate,
	         [x[1] for x in rec[:3]]))
	print("  计数器增量：min=%s max=%s" % (min(deltas) if deltas else None,
	                                     max(deltas) if deltas else None))

	bus.shutdown()
	ser.close()

	res = []
	res.append(("R1 基线速率 9~11.5 帧/s",
	            len(base) >= 2 and 9.0 <= (len(base) - 1) / (base[-1][0] - base[0][0]) <= 11.5,
	            "%.1f 帧/s" % ((len(base) - 1) / (base[-1][0] - base[0][0])
	                           if len(base) >= 2 else 0)))
	res.append(("R2 停用期间不发", len(gap) == 0, "%d 帧" % len(gap)))
	res.append(("R3 恢复后 0.5 s 内出首帧",
	            t_first is not None and t_first <= 0.5,
	            "%s" % ("无首帧" if t_first is None else "%.2f s" % t_first)))
	res.append(("R4 恢复后速率 9~11.5 帧/s", 9.0 <= rate <= 11.5,
	            "%.1f 帧/s" % rate))
	# 正常稳态每帧 +1；停用那段时间计数器照走，恢复后会出现一次大跳变 ——
	# 这正是"时间连续、没有重启"的证据。用**增量分布**判，而不是首帧差值：
	# 首帧可能是 CanIf 队列里停用前压着的旧值（实测 132 → 153）。
	res.append(("R5 计数器单调且含停用跳变（min=1, max≥5）",
	            bool(deltas) and min(deltas) == 1 and max(deltas) >= 5
	            and max(deltas) < 128,
	            "min=%s max=%s" % (min(deltas) if deltas else None,
	                               max(deltas) if deltas else None)))

	print()
	fail = 0
	w = max(len(n) for n, _, _ in res) + 2
	for name, ok, detail in res:
		print("  %-*s %s (%s)" % (w, name, "[ OK ]" if ok else "[FAIL]", detail))
		if not ok:
			fail += 1
	print("-- %d 项，%d 失败" % (len(res), fail))
	return 1 if fail else 0


if __name__ == "__main__":
	sys.exit(main())
