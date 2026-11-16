#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M2 验收：CanIf 接在 MCAL 之上，双通道（CAN0 + CAN1），含 29 位扩展帧。

验收判据：
	1. 启动横幅是 M2，且打印了两路 CAN 配置；
	2. **CAN0 TX 标准帧**：`0x123`，DLC=8，标准帧，8 个字节逐帧全 +1；
	3. **CAN0 TX 扩展帧**：`0x18FF0002`，**29 位**，后 7 字节恒 A5，首字节递增；
	4. **CAN0 RX 标准帧**：发 `0x321` → 串口 `pdu=0 (CAN0 0x321)`，数据回显正确；
	5. **CAN0 RX 扩展帧**：发 `0x18FF0001` → 串口 `pdu=1 (CAN0 0x18FF0001(ext))`；
	6. **CAN1 TX**：`0x124`，标准帧，首字节递增，其余恒 C3；
	7. **CAN1 RX**：发真实报文 `0x0CF00400` → 串口 `pdu=23`；
	8. **TX 确认**：心跳行 `txok` 在增长 —— 证明两个通道的邮箱中断都在调
	   `CanIf_TxConfirmation()`（这条最容易断：中断里漏处理 TX 分支，发送照样成功，
	   但 confirmation 永远不来，接 CanTp 后会永久卡在第一帧）；
	9. 心跳仍在走（证明 CanIf 初始化没把主循环卡住）。

前置：
	- 板子在跑 H:/as 的 M2 双通道固件；
	- Kvaser **ch0 → 板子 CAN0，ch1 → 板子 CAN1**，两路都 @500 kbps；
	- 两路都要接 120 Ω 终端电阻（板上 JP3/JP5/JP6/JP9），否则 ACK 错误、收不到帧。

用法：
	python tools/m2_check.py                 # 复位 + 验收
	python tools/m2_check.py --no-reset      # 不复位，抓当前运行
	python tools/m2_check.py --ch0 0 --ch1 1 # 指定两个通道号

@author binbina
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

# ── 旧 `!x` → 新 shell 命令（M-Shell 迁移；旧兼容桥已删）─────────────
CMD_MAP = {
	'!o': 'can pdu offline',
	'!n': 'can pdu online',
	'!s': 'can ctrl stop',
	'!g': 'can ctrl start',
	'!t': 'can trcv sleep',
	'!r': 'can trcv normal',
}


def xlate(cmd):
	"""旧单字符命令翻译成新命令；其它原样透传。保证以换行结尾。"""
	c = CMD_MAP.get(cmd.strip(), cmd.strip())
	if not c.endswith("\n"):
		c += "\n"
	return c



try:
	import can
except ImportError:
	raise SystemExit("需要 python-can：pip install python-can")

try:
	import serial
except ImportError:
	raise SystemExit("需要 pyserial：pip install pyserial")

JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"

# 报文 ID（与 Can_HwCfg.h 对应）
CAN0_TX_STD = 0x123
CAN0_TX_EXT = 0x18FF0002
CAN0_RX_STD = 0x321
CAN0_RX_EXT = 0x18FF0001
CAN1_TX_STD = 0x124
CAN1_RX_EEC1 = 0x0CF00400   # M19：CAN1 的真实报文（PF=0xF0 段）

RE_HB = re.compile(rb"\[\s*(\d+) ms\] alive #(\d+) txok=(\d+)")


def reset_run():
	"""J-Link 复位并运行。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


def drain(buses, seconds):
	"""把总线上的旧帧读掉，避免复位前后的序号接不上导致误判。"""
	t_end = time.time() + seconds
	while time.time() < t_end:
		for b in buses:
			b.recv(timeout=0.02)


def collect(bus, can_id, is_ext, seconds):
	"""收指定 ID 的帧。"""
	out = []
	t_end = time.time() + seconds
	while time.time() < t_end:
		m = bus.recv(timeout=0.2)
		if m is not None and m.arbitration_id == can_id and m.is_extended_id == is_ext:
			out.append(m)
	return out


def ascending(frames, first_byte_only=False):
	"""检查"数据每帧在变"。

	判据取"相邻两帧增量相同"（first_byte_only 时只看首字节），
	而不是死磕 ==1：Kvaser 偶发丢帧时增量会是 2/3，那仍然证明
	"数据是每帧新组的"，而不是"一直在发同一份缓冲"。
	"""
	if len(frames) < 2:
		return False, []
	deltas = []
	for i in range(1, len(frames)):
		prev, cur = frames[i - 1].data, frames[i].data
		if len(prev) != len(cur):
			return False, []
		pairs = list(zip(prev, cur))[:1] if first_byte_only else list(zip(prev, cur))
		d = {((c - p) & 0xFF) for p, c in pairs}
		if len(d) != 1:
			return False, deltas
		k = d.pop()
		deltas.append(k)
		if not (1 <= k <= 20):
			return False, deltas
	return True, sorted(set(deltas))


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--ch0", type=int, default=0, help="接 CAN0 的 Kvaser 通道（默认 0）")
	ap.add_argument("--ch1", type=int, default=1, help="接 CAN1 的 Kvaser 通道（默认 1）")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	ser = serial.Serial(a.port, 115200, timeout=0.2)
	ser.reset_input_buffer()
	bus0 = can.Bus(interface="kvaser", channel=a.ch0, bitrate=a.bitrate)
	bus1 = can.Bus(interface="kvaser", channel=a.ch1, bitrate=a.bitrate)

	if not a.no_reset:
		p = reset_run()
		if p.returncode != 0:
			print("[FAIL] J-Link 复位失败")
			return 1

	results = []

	# ---- 1) 启动横幅 ----
	time.sleep(0.4)
	boot = ser.read(16384).decode("utf-8", "replace")
	# 不绑里程碑号：M3/M4 起横幅会继续往后走，这里只验"是本工程的固件"
	results.append(("横幅: bring-up", ("bring-up" in boot) and ("CVM0146" in boot)))
	results.append(("横幅: CAN0 + CAN1 都在", "CAN0 + CAN1, 500 kbps" in boot))

	# ---- 1b) 打开自测帧自动发送（A3）----
	# 0x123 / 0x124 / 扩展帧现在是**默认关闭**的驱动层自测帧，
	# 量产固件不主动发（见 can_test.h 的 CanTest_SetAutoTx 说明）。
	# 本脚本测的正是这三条帧，必须显式打开。
	ser.write(b"can auto on\n")
	ser.flush()
	time.sleep(0.3)
	ser.read(4096)

	# ---- 2) CAN0 TX 标准帧 0x123 ----
	drain([bus0, bus1], 0.8)
	frames = collect(bus0, CAN0_TX_STD, False, 3.0)
	results.append(("CAN0 TX: 3 s 内 >=4 帧 0x123 (实收 %d)" % len(frames), len(frames) >= 4))
	if len(frames) >= 2:
		results.append(("CAN0 TX: 0x123 DLC 均为 8", all(f.dlc == 8 for f in frames)))
		ok, d = ascending(frames)
		results.append(("CAN0 TX: 0x123 数据逐帧递增 (增量 %s)" % (d or "-"), ok))
	else:
		results.append(("CAN0 TX: 至少两帧才能验证递增", False))

	# ---- 3) CAN0 TX 扩展帧 0x18FF0002 ----
	ext_frames = collect(bus0, CAN0_TX_EXT, True, 2.5)
	results.append(("CAN0 TX: 收到 >=2 帧扩展帧 0x18FF0002 (实收 %d)" % len(ext_frames),
					len(ext_frames) >= 2))
	if len(ext_frames) >= 2:
		results.append(("CAN0 TX: 扩展帧 DLC 均为 8", all(f.dlc == 8 for f in ext_frames)))
		results.append(("CAN0 TX: 扩展帧后 7 字节恒为 A5",
						all(bytes(f.data[1:8]) == bytes([0xA5] * 7) for f in ext_frames)))
		ok, d = ascending(ext_frames, first_byte_only=True)
		results.append(("CAN0 TX: 扩展帧首字节递增 (增量 %s)" % (d or "-"), ok))
	else:
		results.append(("CAN0 TX: 扩展帧至少要两帧", False))

	# ---- 4) CAN1 TX 0x124 ----
	# 先清 bus1 的接收队列：前面 6 s 的 CAN0 测试期间，CAN1 的帧一直在 Kvaser
	# 驱动里排队，不清的话这里会在"瞬间"把积压全部读出来（实测 17 帧），
	# 数字看着像"板子发快了"，实际是观测方法的问题。
	drain([bus1], 0.5)
	f1 = collect(bus1, CAN1_TX_STD, False, 2.5)
	results.append(("CAN1 TX: 收到 >=2 帧 0x124 (实收 %d)" % len(f1), len(f1) >= 2))
	if len(f1) >= 2:
		results.append(("CAN1 TX: 0x124 DLC 均为 8", all(m.dlc == 8 for m in f1)))
		results.append(("CAN1 TX: 0x124 后 7 字节恒为 C3",
						all(bytes(m.data[1:8]) == bytes([0xC3] * 7) for m in f1)))
		ok, d = ascending(f1, first_byte_only=True)
		results.append(("CAN1 TX: 0x124 首字节递增 (增量 %s)" % (d or "-"), ok))
	else:
		results.append(("CAN1 TX: 至少两帧才能验证递增", False))

	# ---- 5) CAN0 RX 标准帧 0x321 ----
	ser.reset_input_buffer()
	bus0.send(can.Message(arbitration_id=CAN0_RX_STD,
						  data=[0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x02, 0x03, 0x04],
						  is_extended_id=False, dlc=8))
	time.sleep(0.5)
	resp0 = ser.read(16384).decode("utf-8", "replace")
	results.append(("CAN0 RX: 板子打印 [can] rx", "[can] rx" in resp0))
	results.append(("CAN0 RX: 0x321 落到 pdu=0", "pdu=0" in resp0))
	results.append(("CAN0 RX: 0x321 数据 8 字节全部正确",
					"de ad be ef 01 02 03 04" in resp0.lower()))

	# ---- 6) CAN0 RX 扩展帧 0x18FF0001 ----
	ser.reset_input_buffer()
	bus0.send(can.Message(arbitration_id=CAN0_RX_EXT,
						  data=[0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88],
						  is_extended_id=True, dlc=8))
	time.sleep(0.5)
	resp1 = ser.read(16384).decode("utf-8", "replace")
	results.append(("CAN0 RX: 扩展帧落到 pdu=1", "pdu=1" in resp1))
	results.append(("CAN0 RX: 扩展帧标记为 ext", "0x18FF0001(ext)" in resp1))
	results.append(("CAN0 RX: 扩展帧数据 8 字节全部正确",
					"11 22 33 44 55 66 77 88" in resp1.lower()))

	# ---- 7) CAN1 RX：真实矩阵报文 ----
	#
	# @warning M19 之前这里发的是 0x322（CAN1 的测试标准帧）。接入 Foton 真实矩阵后，
	#          **CAN1 的过滤表整表换成了 34 条整车报文**，0x322 不再存在 ——
	#          它在 mb1 上仍能被硬件收到（`!k` 的 mb1 会涨），但 CanIf 找不到
	#          对应表项，静默丢弃。所以用例改成真实报文。
	#
	#          这也是"分层"的一个实证：**硬件收到 ≠ 软件收到**。
	ser.reset_input_buffer()
	bus1.send(can.Message(arbitration_id=CAN1_RX_EEC1,
						  data=[0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8],
						  is_extended_id=True, dlc=8))
	time.sleep(0.5)
	resp2 = ser.read(16384).decode("utf-8", "replace")
	results.append(("CAN1 RX: 0x0CF00400 落到 pdu=23", "pdu=23" in resp2))
	results.append(("CAN1 RX: 真实报文数据 8 字节全部正确",
					"a1 a2 a3 a4 a5 a6 a7 a8" in resp2.lower()))

	# ---- 8) 软件过滤：同 PF 段内、矩阵里没有的 PGN 必须被丢掉 ----
	#
	# 0x18FF0700 的 PF=0xFF，**硬件段邮箱 mb14 会放行**（掩码只匹配 PF），
	# 但 CanIf 的 34 条精确表里没有它 —— 所以是纯粹在验软件过滤层。
	# 这一条比"硬件就挡掉"更有价值。
	ser.reset_input_buffer()
	bus1.send(can.Message(arbitration_id=0x18FF0700,
						  data=[0xEE] * 8, is_extended_id=True, dlc=8))
	time.sleep(0.5)
	resp4 = ser.read(16384).decode("utf-8", "replace")
	results.append(("RX 过滤: 0x18FF0700 硬件放行但软件丢弃", "[can] rx" not in resp4))

	# ---- 9) 未匹配报文必须被静默丢弃 ----
	# 注：这条验的是"硬件 + 软件两层合计"的效果 —— 0x7FF 在 CAN0 的邮箱表里
	# 就没有对应邮箱，帧根本进不了 CPU。真正只测 CanIf 软件过滤的是上面
	# 0x18FF0200 那条（硬件放行、软件拒绝）。
	ser.reset_input_buffer()
	bus0.send(can.Message(arbitration_id=0x7FF, data=[0x55] * 8,
						  is_extended_id=False, dlc=8))
	time.sleep(0.5)
	resp5 = ser.read(16384).decode("utf-8", "replace")
	results.append(("过滤: 0x7FF 未配置 → 不投递", "[can] rx" not in resp5))

	# ---- 10) 短帧（DLC < 8）----
	ser.reset_input_buffer()
	bus0.send(can.Message(arbitration_id=CAN0_RX_STD,
						  data=[0x11, 0x22, 0x33, 0x44], is_extended_id=False, dlc=4))
	time.sleep(0.5)
	resp6 = ser.read(16384).decode("utf-8", "replace")
	results.append(("短帧: DLC=4 收到 dlc=4", "dlc=4" in resp6))
	results.append(("短帧: 4 字节内容正确", "11 22 33 44" in resp6.lower()))

	# ---- 11) 控制面：PDU 模式 / 控制器模式 / 收发器模式 ----
	# 判据统一为"命令下去后总线上 1.2 s 收不到 0x123，恢复命令后又能收到"。
	# 前置 drain 0.8 s（> 一个发送周期），避免把命令前已排队的帧算进来 → 假 FAIL。

	def tx_alive(bus, seconds=1.2):
		drain([bus], 0.8)
		return len(collect(bus, CAN0_TX_STD, False, seconds)) > 0

	def cmd(letter):
		ser.write(xlate("!" + letter).encode())
		ser.flush()
		time.sleep(0.35)
		return ser.read(4096).decode("utf-8", "replace")

	results.append(("控制面: 基线 0x123 在发", tx_alive(bus0)))

	r = cmd("o")
	results.append(("控制面: !o 回读 pduMode=0(OFFLINE)", "pduMode=0" in r))
	results.append(("控制面: OFFLINE 后总线上无 0x123", not tx_alive(bus0)))

	r = cmd("n")
	results.append(("控制面: !n 回读 pduMode=3(ONLINE)", "pduMode=3" in r))
	results.append(("控制面: ONLINE 后恢复发送", tx_alive(bus0)))

	r = cmd("s")
	results.append(("控制面: !s 回读 ctrlMode=2(STOPPED)", "ctrlMode=2" in r))
	results.append(("控制面: STOPPED 后总线上无 0x123", not tx_alive(bus0)))

	r = cmd("g")
	results.append(("控制面: !g 回读 ctrlMode=1(STARTED)", "ctrlMode=1" in r))
	results.append(("控制面: STARTED 后恢复发送", tx_alive(bus0)))

	r = cmd("t")
	results.append(("控制面: can trcv sleep 受理", "<+0" in r))
	results.append(("控制面: TRCV SLEEP 后总线上无 0x123", not tx_alive(bus0)))

	r = cmd("r")
	results.append(("控制面: !r 后恢复发送", tx_alive(bus0)))

	# ---- 12) 心跳 + TX 确认 ----
	hb_buf = (bytearray(resp0.encode()) + bytearray(resp1.encode())
			  + bytearray(resp2.encode()) + bytearray(resp6.encode()))
	t_hb = time.time()
	while time.time() - t_hb < 3.0:
		hb_buf += ser.read(4096)
	hbs = RE_HB.findall(bytes(hb_buf))
	results.append(("心跳: 至少两条 (实收 %d)" % len(hbs), len(hbs) >= 2))

	if len(hbs) >= 2:
		try:
			txok = [int(h[2]) for h in hbs]
			results.append(("TX 确认: txok 在增长 (%d -> %d)" % (txok[0], txok[-1]),
							txok[-1] > txok[0]))
		except (ValueError, IndexError):
			results.append(("TX 确认: txok 解析失败", False))
	else:
		results.append(("TX 确认: 心跳不足，无法判定", False))

	bus0.shutdown()
	bus1.shutdown()
	ser.close()

	# ---- 判定表 ----
	w = max(len(n) for n, _ in results) + 2
	print()
	print("=" * (w + 18))
	print("  M2 双通道验收 —— %s @ %d / Kvaser ch%d=CAN0, ch%d=CAN1 @ %d"
		  % (a.port, 115200, a.ch0, a.ch1, a.bitrate))
	print("=" * (w + 18))
	fail = 0
	for name, ok in results:
		print("  %-*s %s" % (w, name, "[ OK ]" if ok else "[FAIL]"))
		if not ok:
			fail += 1
	print("=" * (w + 18))
	print("  %d 项，通过 %d，失败 %d" % (len(results), len(results) - fail, fail))
	print("=" * (w + 18))

	if fail:
		print("\n---- 串口原文 ----")
		print(boot[:900])
		print(resp0[:600])
		print(resp1[:600])
		print(resp2[:600])
		return 1
	return 0


if __name__ == "__main__":
	sys.exit(main())
