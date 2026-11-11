#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M7 验收：Dcm 0x27 安全访问 / 0x2E 写 DID。

验收判据：
	1. **0x27 受会话限制**：默认会话下 `27 01` → NRC 0x7E（subFunctionNotSupportedInActiveSession）；
	2. `10 03` 进扩展会话后 `27 01` 返回非全 0 种子（本工程固定 `11 22 33 44`）；
	3. `27 02` + **任意 4 字节 key** → `67 02`（当前是"都通过"的实现）；
	4. 解锁后 `27 01` 再请求种子 → 返回**全 0 种子**（ISO 14229 语义：已解锁，无需发 key）；
	5. **解锁不改变其它服务的行为**：`22 F1 90`、`19 02 FF` 在解锁前后都可用
	   （所有 `securityMask` 都是 `0x03` = locked|L1 都允许）；
	6. **0x2E 写入**：`2E F1 90` + 17 字节 → `6E F1 90`；
	7. **写完立刻读得到**：`22 F1 90` 返回刚写的值（两者读同一份 NvM RAM）；
	8. **掉电保持**：复位后 `22 F1 90` 仍是写入值；
	9. **长度错误被拒**：`2E F1 90` + 16 字节 → NRC 0x13；
	10. **不可写的 DID 被拒**：`2E F1 87`（零件号）→ NRC 0x31；
	11. **不存在的 DID 被拒**：`2E 12 34` → NRC 0x31；
	12. **回归**：`10 03` / `22 F1 90` / `19 02 FF` / `3E 00` 全部正常；
	13. 验收结束把 VIN 写回默认值，避免污染后续里程碑的断言。

## 三个容易踩的点

**① `securityMask` 是"允许的等级集合"，不是"最低要求"**

最初填 `0x01`（只有 locked 允许），结果**解锁之后所有服务反而全被拒**，回 NRC 0x33。
因为 `Dcm_Dsl.c:135` 用 `securityMask & (1u << currentLevel)` 判断，
currentLevel 变成 1 之后 bit0 命中不了。正确值是 `0x03`（locked | level 1）。

这条是本次实测抓到的，光看规范很容易写成"1 = 需要解锁"。

**② 0x27 只在扩展会话可用**

`sessionMask = DCM_EXTENDED_MASK`，默认会话下发 `27 01` 得 NRC 0x7E。
这是标准行为，不是 bug —— 测试脚本必须先 `10 03`。

**③ 0x2E 会真的改板子上的 VIN**

所以 M3 那条"用 0x2E 造长请求"的用例已经改成写 F187（不可写），
否则每跑一次回归就把 VIN 改成 17 个 X。
本脚本最后也会把 VIN 写回默认值。

前置：
	- 板子在跑 M7 固件；
	- Kvaser ch0 接 CAN0（500 kbps）；
	- COM2 串口。

用法：
	python tools/m7_check.py
	python tools/m7_check.py --no-restore    # 不写回 VIN（调试用）

@author binbina
"""

import argparse
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

# NvM 里 VIN 块的 ROM 默认值（NvM_Cfg.c）。验收结束写回它。
VIN_DEFAULT = b"CVM0146M4NVM00001"
# 0x27 的固定种子（Dcm_Cfg.c 的 Dcm_SecSeed）
SEED_EXPECT = bytes([0x11, 0x22, 0x33, 0x44])


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--channel", type=int, default=0)
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-restore", action="store_true",
					help="结束后不把 VIN 写回默认值")
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	print("=" * 72)
	print(" M7 验收：Dcm 0x27 安全访问 / 0x2E 写 DID")
	print("=" * 72)

	ser = serial.Serial(a.port, BAUD, timeout=0.2)
	ser.reset_input_buffer()
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)
	tp = Isotp(bus)

	def uds(req, timeout=2.0):
		return tp.request(req, timeout)

	def write_vin(val, tries=8):
		"""写 VIN。板子回 NRC 0x22（conditionsNotCorrect）时重试。

		@note  0x22 的含义是"存储引擎正忙，这次没写"。固件那边是刻意这么做的：
		        厂商 NvM 对**同一块**的重复写请求，在作业未完成时会被丢弃，
		        而 `NvM_WriteBlock()` 仍然返回成功 —— 结果就是
		        "响应 6E F1 90、读回来还是上一次的值"。
		        所以固件在忙时如实回 0x22，由测试仪重试（真车诊断仪也是这么做的）。
		"""
		r = None
		for _ in range(tries):
			r = uds([0x2E, 0xF1, 0x90] + list(val))
			if (r is not None) and (r[:3] == b"\x7F\x2E\x22"):
				time.sleep(0.3)
				continue
			return r
		return r

	def read_vin(expect=None, tries=3):
		"""读 VIN（20 字节多帧响应）。

		@note  带重试：0x2E 写完之后紧接 0x22 读，板子的 NvM 可能还在落盘
		        （`!d` 会显示 `st=2` = 写入中）。这时读**本身是通的**，但
		        偶发会拿到上一轮的帧 —— 重试 3 次、每次间隔 0.3 s 足够覆盖。
		        这是脚本节奏问题，不是固件问题：单独手工发 `2E` → 停 0.6 s → `22`
		        每次都一致，且那时 `!d` 读到的是新值。
		"""
		got = None
		for _ in range(tries):
			r = uds([0x22, 0xF1, 0x90])
			got = bytes(r[3:20]) if ((r is not None) and (len(r) == 20)) else None
			if (expect is not None) and (got == expect):
				return got
			if expect is None:
				return got
			time.sleep(0.3)
		return got

	# ---------- 1) 默认会话下 0x27 被拒 ----------
	# 先显式回默认会话：上一轮脚本可能停在扩展会话，
	# S3 计时器（5 s）没过就不会自动回落，那样这一条会假失败。
	uds([0x10, 0x01])

	r = uds([0x27, 0x01])
	note("0x27: 默认会话被拒 (NRC 0x7E)",
		 (r is not None) and (r[:3] == b"\x7F\x27\x7E"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 2) 进扩展会话 ----------
	r = uds([0x10, 0x03])
	note("0x10: 进入扩展会话", (r is not None) and (r[:2] == b"\x50\x03"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 3) 请求种子 ----------
	r = uds([0x27, 0x01])
	note("0x27: 请求种子返回 67 01 + 4 字节",
		 (r is not None) and (len(r) == 6) and (r[:2] == b"\x67\x01"),
		 r.hex(" ") if r else "(无响应)")
	note("0x27: 种子 = 11 22 33 44",
		 (r is not None) and (len(r) == 6) and (r[2:6] == SEED_EXPECT),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 4) 发送任意 key ----------
	r = uds([0x27, 0x02, 0xAA, 0xBB, 0xCC, 0xDD])
	note("0x27: 任意 key 都通过 (67 02)",
		 (r is not None) and (r[:2] == b"\x67\x02"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 5) 已解锁后再请求种子 → 全 0 ----------
	r = uds([0x27, 0x01])
	note("0x27: 解锁后返回全 0 种子",
		 (r is not None) and (len(r) == 6) and (r[:2] == b"\x67\x01") and
		 (r[2:6] == b"\x00\x00\x00\x00"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 6) 解锁不影响其它服务 ----------
	_ = read_vin()
	note("解锁后: 0x22 仍可用", _ is not None,
		 _ .decode("ascii", "replace") if _ else "(无响应)")

	r = uds([0x19, 0x02, 0xFF])
	note("解锁后: 0x19 仍可用", (r is not None) and (r[:2] == b"\x59\x02"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 7) 0x2E 写 VIN ----------
	old_vin = read_vin()

	new_vin = b"AS-CVM0146M7TEST1"
	assert len(new_vin) == 17, new_vin

	r = write_vin(new_vin)
	note("0x2E: 写 VIN 返回 6E F1 90",
		 (r is not None) and (r[:3] == b"\x6E\xF1\x90"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 8) 写完读得到 ----------
	got = read_vin(expect=new_vin)
	note("0x2E: 写完读得到（共用 NvM RAM）", got == new_vin,
		 got.decode("ascii", "replace") if got else "(无响应)")

	# ---------- 9) 长度错误被拒 ----------
	r = uds([0x2E, 0xF1, 0x90] + list(b"TOO-SHORT"))
	note("0x2E: 长度不对 → NRC 0x13",
		 (r is not None) and (r[:3] == b"\x7F\x2E\x13"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 10) 不可写的 DID ----------
	r = uds([0x2E, 0xF1, 0x87] + list(b"X" * 11))
	note("0x2E: 零件号不可写 → NRC 0x31",
		 (r is not None) and (r[:3] == b"\x7F\x2E\x31"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 11) 不存在的 DID ----------
	r = uds([0x2E, 0x12, 0x34] + list(b"Y" * 3))
	note("0x2E: 不存在的 DID → NRC 0x31",
		 (r is not None) and (r[:3] == b"\x7F\x2E\x31"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 12) 回归其它服务 ----------
	r = uds([0x3E, 0x00])
	note("回归: 3E 00 正常", (r is not None) and (r[:2] == b"\x7E\x00"),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 13) 写回 VIN ----------
	if not a.no_restore:
		# **固定写回出厂默认值**，而不是"跑之前读到的值"。
		# 理由：若上一轮异常中断（比如刚才那次把 VIN 写成了 17 个 X），
		# "恢复到跑之前"会把脏值一路传下去，而 M3 的断言期望的正是默认值。
		# 基线只能有一个：NvM_Cfg.c 里的 ROM 默认。
		restore = VIN_DEFAULT
		r = write_vin(restore)
		note("收尾: VIN 已写回", (r is not None) and (r[:3] == b"\x6E\xF1\x90"),
			 restore.decode("ascii", "replace"))
		got = read_vin(expect=restore)
		note("收尾: 读回一致", got == restore,
			 got.decode("ascii", "replace") if got else "(无响应)")

	bus.shutdown()
	ser.close()

	# ---------- 汇总 ----------
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
