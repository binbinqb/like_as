#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    led_loop_check.py
@brief   上板验收：LED 闭环（10.6）—— 启动/停止/无效/超时/恢复 + 闪烁时序 + 上报周期

@details 链路（双向都验）：
          ```
          CAN1 0x18FEF121 (CCVS, 100 ms)  → CanIf → PduR → Com → BcmSig → RTE
                                          → LedBiz → RTE → IoHwAb → LED
          CAN0 0x200 (100 ms)             ← Com ← BcmSig ← RTE ← LedBiz
          ```
          CAN1 上的控制复用了 CCVS 的 `ParkingBrakeSwitch`（bit 2|2，小端）：
          raw 0 = 停止并熄灭、raw 1 = 启动闪烁、raw 2/3 = 无效。

          | 用例 | 断言 |
          |---|---|
          | 启动 | 模式=闪烁(1)，相位在 1.0 s 内出现 0/1 两态 |
          | 闪烁时序 | 相邻相位跳变间隔 ≈ 500 ms（±150 ms） |
          | 停止 | 模式=已停止(0)，灯输出=0，相位=0 |
          | 无效命令 | 命令无效故障位=1，模式不变，超时位=0 |
          | 超时 | 停发 700 ms 后：模式=0、灯输出=0、超时位=1 |
          | 恢复 | 重新发有效命令：两个故障位清零、模式=1 |
          | 上报周期 | 0x200 间隔 100 ms（80~130 ms） |

@note    `LED_OUT` 是"驱动成功提交"的状态，不是电气反馈；本脚本不读灯电流。
@note    需要 Kvaser 两路：ch0=CAN0（500 k）、ch1=CAN1（500 k）。
@note    默认上板手工运行：`python tools/led_loop_check.py`；
          `--static` 只打印报文/位布局，不打开总线（离线核对配置用）。

@author  binbina
@version V1.0.0
"""

import argparse
import sys
import time

# 报文与位布局（与 Com.json 一一对应；改了配置必须同步改这里）
CTRL_ID = 0x18FEF121          # CAN1 RX：CCVS
CTRL_ID_EXT = True
CTRL_PERIOD = 0.1             # 100 ms
CTRL_PARK_BIT = 2             # bit 2, 2 bit, little-endian

STATUS_ID = 0x200             # CAN0 TX
STATUS_PERIOD = 0.1
STATUS_DLC = 8

CH_CAN0 = 0
CH_CAN1 = 1
BITRATE = 500000

results = []


def check(name, cond, detail=""):
	results.append((name, bool(cond), detail))
	print(("  PASS  " if cond else "  FAIL  ") + name
	      + (("   " + detail) if (detail and not cond) else ""))


def build_ctrl(raw):
	"""组一帧 CCVS：只填 ParkingBrakeSwitch，其余 0。"""
	data = bytearray(8)
	data[0] = (raw & 0x3) << CTRL_PARK_BIT
	return data


def decode_status(data):
	"""解析 0x200 的 5 个状态位（小端位布局）。"""
	b1 = data[1] if len(data) > 1 else 0
	return {
		"mode": (b1 >> 2) & 0x3,      # LedRunMode  10|2
		"out": (b1 >> 4) & 0x1,       # LedOut      12|1
		"phase": (b1 >> 5) & 0x1,     # LedBlinkPhase 13|1
		"fault_to": (b1 >> 6) & 0x1,  # LedFaultTimeout 14|1
		"fault_cmd": (b1 >> 7) & 0x1  # LedFaultCmd  15|1
	}


class Bus:
	def __init__(self):
		import can
		self.can = can
		self.ch0 = can.Bus(interface="kvaser", channel=CH_CAN0, bitrate=BITRATE)
		self.ch1 = can.Bus(interface="kvaser", channel=CH_CAN1, bitrate=BITRATE)
		self.t0 = time.time()
		self.next_ctrl = 0.0

	def send_ctrl(self, raw):
		msg = self.can.Message(arbitration_id=CTRL_ID, is_extended_id=CTRL_ID_EXT,
		                       data=build_ctrl(raw), dlc=8)
		self.ch1.send(msg)

	def pump(self, raw, duration, collect=False):
		"""按 100 ms 发控制帧，同时收 CAN0；返回 [(t, status_dict)]。"""
		frames = []
		end = time.time() + duration
		while time.time() < end:
			now = time.time()
			if now >= self.next_ctrl:
				self.send_ctrl(raw)
				self.next_ctrl = now + CTRL_PERIOD
			msg = self.ch0.recv(timeout=0.005)
			if msg is not None and (msg.arbitration_id & 0x1FFFFFFF) == STATUS_ID:
				frames.append((time.time() - self.t0, decode_status(bytes(msg.data))))
		return frames

	def close(self):
		self.ch0.shutdown()
		self.ch1.shutdown()


def last(frames, key, default=None):
	return frames[-1][1][key] if frames else default


def phase_edges(frames):
	"""相位跳变时刻（秒）。"""
	edges = []
	prev = None
	for t, s in frames:
		if prev is not None and s["phase"] != prev:
			edges.append(t)
		prev = s["phase"]
	return edges


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--static", action="store_true", help="只打印布局，不打开总线")
	args = ap.parse_args()

	print("== LED 闭环上板验收（10.6）==")
	print("  控制：CAN1 0x%08X CCVS.ParkingBrakeSwitch  bit %d|2  raw 0/1/2"
	      % (CTRL_ID, CTRL_PARK_BIT))
	print("  状态：CAN0 0x%03X  mode@10|2 out@12|1 phase@13|1 to@14|1 cmd@15|1"
	      % (STATUS_ID))
	if args.static:
		print("  --static：不打开总线，退出。")
		return 0

	bus = Bus()
	try:
		# ---- 1. 启动 + 闪烁时序 ----
		f = bus.pump(1, 1.6, collect=True)
		check("启动后收到 CAN0 0x200 状态帧", len(f) >= 5, "帧数=%d" % len(f))
		check("启动：模式=闪烁(1)", last(f, "mode") == 1, "mode=%s" % last(f, "mode"))
		edges = phase_edges(f)
		check("闪烁：出现相位跳变", len(edges) >= 1, "跳变=%s" % edges)
		if len(edges) >= 2:
			d = (edges[-1] - edges[0]) / (len(edges) - 1)
			check("闪烁半周期 ≈ 500 ms（±150）", 0.35 <= d <= 0.65,
			      "实测 %.0f ms" % (d * 1000.0))

		# ---- 2. 停止 ----
		f = bus.pump(0, 0.6, collect=True)
		check("停止：模式=已停止(0)", last(f, "mode") == 0, "mode=%s" % last(f, "mode"))
		check("停止：灯输出=0、相位=0",
		      (last(f, "out") == 0) and (last(f, "phase") == 0),
		      "out=%s phase=%s" % (last(f, "out"), last(f, "phase")))

		# ---- 3. 无效命令（帧仍在发，值非法）----
		f = bus.pump(2, 0.35, collect=True)
		check("无效命令：故障位=1", last(f, "fault_cmd") == 1,
		      "fault_cmd=%s" % last(f, "fault_cmd"))
		check("无效命令：不误报超时", last(f, "fault_to") == 0,
		      "fault_to=%s" % last(f, "fault_to"))
		check("无效命令：模式不变(0)", last(f, "mode") == 0,
		      "mode=%s" % last(f, "mode"))

		# ---- 4. 超时（先有效启动，再停发 700 ms）----
		bus.pump(1, 0.5, collect=False)
		# 纯收窗口：不发任何控制帧
		f = []
		end = time.time() + 0.75
		while time.time() < end:
			msg = bus.ch0.recv(timeout=0.01)
			if msg is not None and (msg.arbitration_id & 0x1FFFFFFF) == STATUS_ID:
				f.append((time.time() - bus.t0, decode_status(bytes(msg.data))))
		check("超时：模式=已停止(0)", last(f, "mode") == 0, "mode=%s" % last(f, "mode"))
		check("超时：灯输出=0、相位=0",
		      (last(f, "out") == 0) and (last(f, "phase") == 0),
		      "out=%s phase=%s" % (last(f, "out"), last(f, "phase")))
		check("超时：超时故障位=1", last(f, "fault_to") == 1,
		      "fault_to=%s" % last(f, "fault_to"))

		# ---- 5. 通信恢复 ----
		f = bus.pump(1, 0.6, collect=True)
		check("恢复：模式=闪烁(1)", last(f, "mode") == 1, "mode=%s" % last(f, "mode"))
		check("恢复：两个故障位清零",
		      (last(f, "fault_to") == 0) and (last(f, "fault_cmd") == 0),
		      "to=%s cmd=%s" % (last(f, "fault_to"), last(f, "fault_cmd")))

		# ---- 6. 上报周期 ----
		if len(f) >= 5:
			ts = [t for t, _ in f]
			gaps = [b - a for a, b in zip(ts, ts[1:])]
			avg = sum(gaps) / len(gaps)
			check("上报周期 ≈ 100 ms（80~130）", 0.08 <= avg <= 0.13,
			      "实测 %.0f ms" % (avg * 1000.0))
		else:
			check("上报周期 ≈ 100 ms（80~130）", False, "帧数不足")

		# ---- 7. 收尾：停止 ----
		bus.pump(0, 0.4, collect=False)
	finally:
		bus.close()

	failed = [r for r in results if not r[1]]
	print("-- %d 项断言，%d 项失败" % (len(results), len(failed)))
	return 0 if not failed else 1


if __name__ == "__main__":
	sys.exit(main())
