#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""A9 验收：业务骨架端到端（输入 → 决策 → 输出 → 健康状态）。

## 这条判据在证明什么

框架能不能用，不看"每个模块都跑得起来"，而看**一条业务能不能从总线输入
走到总线输出**，并且中间每一档异常都有确定的处置。本用例走：
`CCVS.ParkingBrakeSwitch`（0x18FEF121） → 决策 → `BCM_LCSF.BrakelightST`
（0x18FE4021）。

## 判据为什么落在"总线字节"上

`bcm all on` 能改 Com 缓冲，那只能证明绑定层；要证明**决策逻辑真的驱到了
输出**，必须看总线上那一帧有没有变。制动灯在 `BCM_LCSF` 的 bit46..47，
即 **byte5 的 bit6..7**：

| 制动灯语义 | raw | byte5 |
|---|---|---|
| OFF | 0 | `0x00` |
| ON | 1 | `0x40` |

## 覆盖的六条规则

| 输入 | 期望输出 | 期望 health |
|---|---|---|
| 未收到（刚 `biz on`） | OFF | `INIT` |
| raw=1（ParkingBrakeSet） | ON | `OK` |
| raw=0（NotSet） | OFF | `OK` |
| raw=2（Error） | OFF | `PEER_ERROR` |
| raw=3（NotAvailable） | **保持 ON**（先给 ON 再发 3） | `INVALID` |
| 停发 > 3 s 去抖 | OFF | `LOST` |

`INVALID` 那条是"保持"而不是"关"——这是刻意设计（见 `bcm_biz.c` 的
@ref BIZC_WHYHOLD）：值不可用 ≠ 值是 0。

## 前置

- 板子在跑含 A9 的固件（`bcm biz` 命令存在）；
- Kvaser ch1 接 CAN1（500 kbps）；COM2 串口。

用法：
	python tools/a9_biz_check.py

@author binbina
"""

import argparse
import re
import sys
import time

import can
import serial

CCVS_ID = 0x18FEF121
LCSF_ID = 0x18FE4021
BRAKE_SHIFT = 2        # ParkingBrakeSwitch: 2|2@1+（byte0 bit2..3）
LCSF_CYCLE_S = 0.05
DEBOUNCE_S = 3.0

RE_HEALTH = re.compile(r"health = (\w+)")
RE_INPUT = re.compile(r"input = (\w+) / (\w+)")
RE_ENABLED = re.compile(r"brake-follow-park = (\w+)")


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--channel", type=int, default=1, help="接 CAN1 的 Kvaser 通道")
	ap.add_argument("--bitrate", type=int, default=500000)
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))
		print("  [%s] %s%s" % ("PASS" if ok else "FAIL", name,
		                       ("   (%s)" % detail) if detail else ""))

	ser = serial.Serial(a.port, a.baud if hasattr(a, "baud") else 115200, timeout=0.2)
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	def cmd(text, wait=0.35):
		ser.reset_input_buffer()
		if not text.endswith("\n"):
			text += "\n"
		ser.write(text.encode())
		ser.flush()
		time.sleep(wait)
		return ser.read(65536).decode("utf-8", "replace")

	def send_raw(raw, count=3):
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
		time.sleep(0.05)      # 等主函数搬进 shadow

	def drain(sec=0.25):
		t = time.time()
		while time.time() - t < sec:
			bus.recv(0.02)

	def brake_byte(sec=0.5):
		"""抓一帧 LCSF，取 byte5（制动灯所在字节）；抓不到返回 None。"""
		t = time.time()
		b5 = None
		while time.time() - t < sec:
			msg = bus.recv(0.05)
			if msg is not None and msg.arbitration_id == LCSF_ID:
				b5 = msg.data[5]
		return b5

	def health():
		out = cmd("bcm biz", 0.3)
		m = RE_HEALTH.search(out)
		return m.group(1) if m else None

	try:
		print("=" * 78)
		print("A9 验收：业务骨架（驻车制动 → 制动灯）")
		print("=" * 78)

		# ---------- 0. 默认不接管 ----------
		print("\n--- 0 默认状态 ---")
		cmd("bcm biz off", 0.25)
		cmd("bcm all off", 0.25)
		out = cmd("bcm biz", 0.3)
		note("上电默认不接管（不与 bcm all 抢信号）",
		     RE_ENABLED.search(out) is not None and
		     RE_ENABLED.search(out).group(1) == "off",
		     out.strip().splitlines()[0] if out.strip() else "无输出")

		# ---------- 1. 接管后 INIT ----------
		print("\n--- 1 bcm biz on：INIT，灯灭 ---")
		cmd("bcm biz on", 0.25)
		time.sleep(0.15)
		drain(0.2)
		b5 = brake_byte()
		note("接管后 health = INIT", health() == "INIT", "读到 %s" % health())
		note("接管后制动灯 OFF（byte5 = 0x00）", b5 == 0x00,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		# ---------- 2. 有效输入驱动输出 ----------
		print("\n--- 2 有效输入：ON / OFF 跟随 ---")
		send_raw(1)
		drain(0.2)
		b5 = brake_byte()
		note("raw 1 → health = OK", health() == "OK", "读到 %s" % health())
		note("raw 1 → 制动灯 ON（byte5 = 0x40）", b5 == 0x40,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		send_raw(0)
		drain(0.2)
		b5 = brake_byte()
		note("raw 0 → 制动灯 OFF（byte5 = 0x00）", b5 == 0x00,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		# ---------- 3. 对方报错：关灯但不算"值不可用" ----------
		print("\n--- 3 raw=2（对方报错）：PEER_ERROR + 关灯 ---")
		send_raw(2)
		drain(0.2)
		b5 = brake_byte()
		note("raw 2 → health = PEER_ERROR", health() == "PEER_ERROR",
		     "读到 %s" % health())
		note("raw 2 → 制动灯 OFF", b5 == 0x00,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		# ---------- 4. 值不可用：保持上一次输出 ----------
		print("\n--- 4 raw=3（值不可用）：INVALID + **保持** ON ---")
		send_raw(1)           # 先把灯点亮
		time.sleep(0.1)
		send_raw(3)           # 再发"不可用"
		# 先查、再抓帧：`bcm biz` 一次就把 health 与 input 都打出来了。
		# 顺序反了会踩到 300 ms 的输入超时（抓帧本身要 0.5 s）——
		# 这会把 INVALID 读成 TIMEOUT，是本用例第一版真实踩到的假失败。
		m = RE_INPUT.search(cmd("bcm biz", 0.2))
		note("raw 3 → health = INVALID", health() == "INVALID", "读到 %s" % health())
		note("raw 3 → 输入有效性 INVALID",
		     m is not None and m.group(2) == "INVALID",
		     m.group(0) if m else "读不到")
		b5 = brake_byte()
		note("raw 3 → 制动灯保持 ON（不因读不懂就灭灯）", b5 == 0x40,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		# ---------- 5. 通信丢失：去抖 3 s ----------
		print("\n--- 5 停发：先去抖保持，超过 3 s 才 LOST ---")
		# 先恢复一帧有效值，把"丢失计时"从零开始 ——
		# 否则上面几步已经耗掉 1 s 多，去抖窗口早就过了，测的就不是去抖。
		send_raw(1)
		drain(0.2)
		b5 = brake_byte()     # 此刻 age ≈ 0.7 s：已过输入超时，但未过去抖
		h1 = health()
		note("停发 1 s 内仍保持 ON（去抖）", b5 == 0x40,
		     "byte5=0x%02X health=%s" % (b5 if b5 is not None else 0, h1))
		note("停发 1 s 内 health 仍不是 LOST", h1 != "LOST", "读到 %s" % h1)

		time.sleep(DEBOUNCE_S)     # 累计超过 3 s
		drain(0.2)
		b5 = brake_byte()
		h2 = health()
		note("停发 > 3 s → health = LOST", h2 == "LOST", "读到 %s" % h2)
		note("停发 > 3 s → 制动灯 OFF", b5 == 0x00,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		# ---------- 6. 恢复 ----------
		print("\n--- 6 恢复发帧：回到 OK ---")
		send_raw(1)
		drain(0.2)
		b5 = brake_byte()
		note("恢复后 health = OK", health() == "OK", "读到 %s" % health())
		note("恢复后制动灯 ON", b5 == 0x40,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

		# ---------- 7. 关掉接管后不再抢信号 ----------
		print("\n--- 7 bcm biz off：不再写制动灯 ---")
		cmd("bcm biz off", 0.25)
		cmd("bcm all on", 0.25)
		time.sleep(0.15)
		b5 = brake_byte()
		note("关掉接管后 bcm all on 生效（byte5 = 0x50）", b5 == 0x50,
		     "byte5=0x%02X" % b5 if b5 is not None else "没抓到帧")

	finally:
		cmd("bcm biz off", 0.2)
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
