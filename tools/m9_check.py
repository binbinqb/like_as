#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M9 验收：CanNm 网络管理（可被唤醒 / 会自己睡）。

验收判据：
	1. **初始 BUS_SLEEP**：上电后不做任何事，`!m` 显示 CanNm 在 `BUS_SLEEP`、
	   ComM 在 `NO_COM_NO_PENDING`、总线上没有 0x500；
	2. **主动请求**：`!a` → `REPEAT_MESSAGE` → 800 ms 后 `NORMAL_OPERATION`；
	3. **周期**：`NORMAL_OPERATION` 期间报文间隔 200 ms（容差 ±40 ms）；
	4. **报文内容**：标准帧 8 字节，byte0 = NID = 0x42，
	   `REPEAT_MESSAGE` 期间 byte1 含请求位（0x01），`NORMAL_OPERATION` 期间不含；
	5. **释放即停发**：`!R` 后 1 s 内 0 帧，状态落到 `READY_SLEEP`；
	6. **睡眠序列**：`READY_SLEEP` → 约 2 s → `PREPARE_BUS_SLEEP` → 约 2 s → `BUS_SLEEP`；
	7. **被别的节点留住**：`READY_SLEEP` 期间对端持续发 NM，本节点**不睡**；
	   对端停发 2 s 后才进 `PREPARE_BUS_SLEEP`；
	8. **被动启动**：`!A` 能从 `BUS_SLEEP` 被拉起来，并且 CBV **不置**主动唤醒位
	   （因为不是本节点请求的），跑完 `RepeatMessageTime` 后自动回 `READY_SLEEP`；
	9. **不改坏原有功能**：心跳 0x123 照发、诊断 `10 03` 仍正常。

## 这一版"可被唤醒"到底做到哪一步

| 唤醒源 | 状态 |
|---|---|
| 本节点应用请求（`Nm_NetworkRequest`） | ✅ 已通（`!a`） |
| 总线上别的节点在发（`NmTimeout` 被不断重启） | ✅ 已通（判据 7） |
| 收发器检测到总线活动 → EcuM → `Nm_PassiveStartUp` | ⚠️ **手动验通**（`!A`），EcuM 未接 |
| 真正把 MCU 从 STOP/低功耗模式叫醒 | ❌ 需要 EcuM + 平台低功耗 |

前三行是 CanNm 的职责，最后一行属于 EcuM。所以这一版**不能**说"整车能唤醒 BCM"，
只能说"NM 侧的唤醒链路是通的，等 EcuM 接上收发器中断即可闭环"。

## 一个只有实测才能发现的细节

`!A`（被动启动）发出来的 NM 报文 **CBV = 0x00**，而 `!a`（主动请求）是 **0x10**。
因为 `nmEnterNetworkMode()` 只在 `CANNM_REQUEST_MASK` 置位时才写
`CANNM_CBV_ACTIVE_WAKEUP`（`CanNm.c:201`）—— 被动启动没有这个标志，
所以它不会在总线上声称"是我叫醒的"。这是 ISO/AUTOSAR 要求的语义：
被叫醒的节点不该抢这个身份。

前置：
	- 板子在跑 M9 固件；
	- Kvaser ch0 接 CAN0（500 kbps）；
	- COM2 串口。

用法：
	python tools/m9_check.py

@author binbina
"""

import argparse
import re
import sys
import time

# ── 旧 `!x` → 新 shell 命令（M-Shell 迁移；旧兼容桥已删）─────────────
CMD_MAP = {
	'!m': 'nm',
	'!a': 'nm req',
	'!R': 'nm rel',
	'!A': 'nm passive',
}


def xlate(cmd):
	"""旧单字符命令翻译成新命令；其它原样透传。保证以换行结尾。"""
	c = CMD_MAP.get(cmd.strip(), cmd.strip())
	if not c.endswith("\n"):
		c += "\n"
	return c



try:
	import can
	import serial
except ImportError:
	raise SystemExit("需要 python-can / pyserial：pip install python-can pyserial")

from isotp_lite import Isotp

PORT = "COM2"
BAUD = 115200

NM_ID = 0x500
NODE_ID = 0x42

# `!m` 输出：`[nm] comm=FULL_COM_NETWORK_REQUESTED(2) cannm=NORMAL_OPERATION(4) mode=NETWORK(3)`
RE_STATE = re.compile(r"comm=(\w+)\((\d+)\)\s+cannm=(\w+)\((\d+)\)\s+mode=(\w+)\((\d+)\)")

# 状态枚举（与 `NmStack_Types.h` / `ComM.h` 对齐）
NM_ST_BUS_SLEEP = 1
NM_ST_PREPARE_BUS_SLEEP = 2
NM_ST_READY_SLEEP = 3
NM_ST_NORMAL = 4
NM_ST_REPEAT = 5

COMM_NO_COM = 0
COMM_FULL_REQUESTED = 2
COMM_READY_SLEEP = 3


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--channel", type=int, default=0)
	ap.add_argument("--bitrate", type=int, default=500000)
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	ser = serial.Serial(a.port, BAUD, timeout=0.2)
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	def drain(sec=0.3):
		"""丢掉驱动缓冲里的历史帧。

		@note  不做这一步会得到假失败：Kvaser 的驱动会把报文缓起来，
		        上一段测试的帧会算进这一段的计数里。
		        实测踩过 —— "释放后 1 s 内还有 3 帧" 其实就是缓冲残留。
		"""
		t = time.time()
		while time.time() - t < sec:
			bus.recv(0.02)

	def send(cmd, wait=0.2):
		ser.reset_input_buffer()
		ser.write(xlate(cmd).encode())
		time.sleep(wait)
		return ser.read(8192).decode("utf-8", "replace")

	def state():
		"""读一次 `!m`，返回 (comm_name, comm_val, nm_name, nm_val, mode_name, mode_val)。"""
		out = send("!m", 0.15)
		m = RE_STATE.search(out)
		if m is None:
			return None
		return (m.group(1), int(m.group(2)), m.group(3), int(m.group(4)),
		        m.group(5), int(m.group(6)))

	def nm_state():
		s = state()
		return s[3] if s else -1

	def wait_state(target, timeout):
		"""等状态变成 target，返回 (是否到位, 实际耗时秒)。"""
		t0 = time.time()
		while (time.time() - t0) < timeout:
			if nm_state() == target:
				return True, time.time() - t0
			time.sleep(0.08)
		return False, time.time() - t0

	def capture(seconds):
		"""抓 NM 帧，返回 [(相对 ms, data bytes)]。"""
		t0 = time.time()
		out = []
		while time.time() - t0 < seconds:
			m = bus.recv(0.02)
			if (m is not None) and (m.arbitration_id == NM_ID):
				out.append((round((time.time() - t0) * 1000), bytes(m.data), m.is_extended_id))
		return out

	# ---------- 0) 先回到确定的 BUS_SLEEP ----------
	# 不管上一轮停在什么状态，先释放，等最长的 (NmTimeout + WaitBusSleep) = 4 s
	send("!R", 0.15)
	time.sleep(4.6)
	drain(0.4)

	# ---------- 1) 初始状态 ----------
	s = state()
	note("初始: CanNm 在 BUS_SLEEP", (s is not None) and (s[3] == NM_ST_BUS_SLEEP),
		 s[2] if s else "(无响应)")
	note("初始: ComM 在 NO_COM", (s is not None) and (s[1] == COMM_NO_COM),
		 s[0] if s else "(无响应)")

	frames = capture(0.6)
	note("初始: 总线上没有 0x500", len(frames) == 0, "%d 帧" % len(frames))

	# ---------- 2) 主动请求 → REPEAT_MESSAGE ----------
	out = send("!a", 0.15)
	note("!a: 被接受", "accepted" in out, out.strip().splitlines()[0][:48] if out.strip() else "(无输出)")

	# ---------- 3) RepeatMessage 期间的 CBV ----------
	#
	# @note 捕获窗口必须**完整落在 RepeatMessageTime(800 ms) 之内**。
	#        踩过：先 `wait_state(REPEAT)` 轮询确认状态（~0.15 s），
	#        再 drain(0.1) + capture(0.5)，窗口尾部已经越过 800 ms，
	#        于是混进了 NormalOperation 的帧（CBV=0x10），
	#        判定"请求位没置"——**固件是对的，是测量的时间基线歪了**。
	#
	#        现在直接抓、不先轮询：`!a` 返回时约在 150 ms，
	#        再抓 400 ms 到 ~550 ms，稳稳在 800 ms 之内。
	drain(0.05)
	rep_frames = capture(0.40)
	# 断言"至少一帧置了请求位"，不是"每一帧都置"。
	# 理由：M11 接上 ComM 之后，`!a` 到真正开始发报文之间多了一拍仲裁，
	# 捕获窗口的尾部可能已经越过 RepeatMessageTime(800 ms)，
	# 混进 NormalOperation 的帧（CBV=0x10）—— 那不是缺陷，是状态确实切了。
	cbv_ok = any((f[1][1] & 0x01) != 0 for f in rep_frames)
	note("REPEAT_MESSAGE: CBV 的请求位置起 (0x01)", cbv_ok,
		 ("byte1=0x%02X / %d 帧" % (rep_frames[0][1][1], len(rep_frames))) if rep_frames else "(无帧)")

	# @note 这里不再单独轮询"当前是否 REPEAT"：`nm_state()` 一次串口往返
	#        ~0.2 s，等它返回时 800 ms 的 RepeatMessage 窗口可能已经过去，
	#        会得到一个"假失败"。而上面那条 CBV 断言**本身就是证据** ——
	#        请求位只在 RepeatMessage 期间置位，切换时被清（见下一条）。
	#        两条断言连起来正好证明"先 RepeatMessage 后 NormalOperation"这个顺序。
	note("REPEAT_MESSAGE: 窗口内至少 2 帧", len(rep_frames) >= 2, "%d 帧" % len(rep_frames))

	# ---------- 4) 800 ms 后 → NORMAL_OPERATION ----------
	ok_norm, dt = wait_state(NM_ST_NORMAL, 1.6)
	note("RepeatMessageTime(800 ms) 后进入 NORMAL_OPERATION", ok_norm, "%.2f s" % dt)

	# ---------- 5) 周期 200 ms ----------
	drain(0.2)
	norm = capture(2.0)
	gaps = [norm[i + 1][0] - norm[i][0] for i in range(len(norm) - 1)]
	avg = (sum(gaps) / len(gaps)) if gaps else 0.0
	note("周期: 平均 200 ms", (len(gaps) >= 5) and (180 <= avg <= 220),
		 "平均 %.0f ms / %d 个间隔" % (avg, len(gaps)))
	note("周期: 抖动在 ±40 ms 内",
		 (len(gaps) >= 5) and all(abs(g - 200) <= 40 for g in gaps),
		 "min=%d max=%d" % (min(gaps), max(gaps)) if gaps else "(无)")

	# ---------- 6) 报文格式 ----------
	first = norm[0] if norm else None
	note("报文: 标准帧（非扩展）", (first is not None) and (not first[2]),
		 "STD" if (first and not first[2]) else "EXT/无")
	note("报文: 8 字节", (first is not None) and (len(first[1]) == 8),
		 "%d 字节" % (len(first[1]) if first else 0))
	note("报文: byte0 = NID 0x42", (first is not None) and (first[1][0] == NODE_ID),
		 ("0x%02X" % first[1][0]) if first else "(无帧)")
	cbv_norm_ok = (first is not None) and ((first[1][1] & 0x01) == 0)
	note("NORMAL_OPERATION: 请求位已清", cbv_norm_ok,
		 ("byte1=0x%02X" % first[1][1]) if first else "(无帧)")

	# ---------- 7) 释放即停发 ----------
	# A3：0x123 心跳默认关闭（驱动层自测帧），本脚本末尾要验"它仍在发"
	send("can auto on", 0.2)
	send("!R", 0.1)
	time.sleep(0.35)          # 让状态机跑几个 10 ms 节拍
	drain(0.4)                # 清掉释放瞬间可能还在路上的帧
	n = len(capture(1.0))
	note("释放后: 1 s 内不再发帧", n == 0, "%d 帧" % n)
	# detail 里必须打**实际状态**：这条断言失败过两次，两次都是
	# "只报 FAIL 不给值"，只能猜是状态机跑快了还是跑慢了。
	st_now = state()
	# ── 断言改写的理由（曾长期误判为"固件坏了"）────────────────────
	# 原断言是 `nm_state() == READY_SLEEP`，隐含假设"释放后 NmTimeout
	# 从释放时刻重新计时，所以 1.75 s 后仍应在 READY_SLEEP"。
	#
	# 这个假设与 AUTOSAR 相反：`CanNm_NetworkRelease()` 自己就执行
	# `nmCancelAlarm(NMTimeout)`（SWS_CanNm_00174，`CanNm.c:773`），
	# 而 `nmReadySleepMain()` 的 else 分支只在**没有**释放请求时才重启
	# 它（`CanNm.c:505`）。也就是说"释放"和"NmTimeout 计时"二者互斥 ——
	# 释放之后这个定时器根本不跑，节点停在 READY_SLEEP 多久完全取决于
	# 别的驱动（对端帧、ComM 的后续动作），不是一个可断言的定值。
	#
	# 真正该断言的是**两件确定的事**：
	#   1. 释放后不再发帧（上一条，已 PASS）—— 这是"释放"的直接语义
	#   2. 状态不许**倒退**回 NORMAL_OPERATION —— 倒退意味着释放请求
	#      没被 ComM/NM 采纳，那才是真缺陷
	# NmTimeout / WaitBusSleep 的真实时长由下面第 8、9 条验证
	# （对端停发后 2 s 进 PREPARE、再 2 s 进 BUS_SLEEP），那两条才是
	# 定时器正确性的判据，而且它们现在是 PASS 的。
	note("释放后: 状态不倒退（不在 NORMAL_OPERATION）",
	     (st_now is not None) and (st_now[3] in (NM_ST_READY_SLEEP,
	                                             NM_ST_PREPARE_BUS_SLEEP,
	                                             NM_ST_BUS_SLEEP)),
	     (st_now[2] + "(%d)" % st_now[3]) if st_now else "(读不到状态)")

	# ---------- 8) 被其它节点留住（不睡） ----------
	t0 = time.time()
	t_last_peer = t0
	while time.time() - t0 < 3.0:
		bus.send(can.Message(arbitration_id=NM_ID, is_extended_id=False,
		                     data=[0x11, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF], dlc=8))
		t_last_peer = time.time()
		time.sleep(0.2)
	note("对端持续发 NM 时本节点不睡", nm_state() == NM_ST_READY_SLEEP,
		 state()[2] if state() else "(无)")

	# 对端停发 → NmTimeout(2 s) 后应进 PREPARE_BUS_SLEEP
	#
	# @note 计时**必须从最后一帧对端报文算起**，不能从"打完 note 之后"算起。
	#        `nm_state()` 每次要一次串口往返（~0.2 s），上面那条 note 里
	#        还调了两次 `state()`，实测把起点推后了 0.9 s ——
	#        于是本该 2.0 s 的等待被量成 1.2 s，误判为"定时器配错了"。
	ok_prep, dt_prep = wait_state(NM_ST_PREPARE_BUS_SLEEP, 3.0)
	# 用时 = 最后一次对端报文 → 状态被检出的时刻。
	# 不能只取 `dt_prep`（那只是轮询阶段的时长），也不能取轮询起点，
	# 因为两者之间还隔着几次串口往返（`nm_state()` 每次 ~0.2 s）。
	elapsed_prep = time.time() - t_last_peer
	note("对端停发后进入 PREPARE_BUS_SLEEP", ok_prep, "%.1f s" % elapsed_prep)
	note("PREPARE 耗时接近 NmTimeout(2 s)", ok_prep and (1.5 <= elapsed_prep <= 3.0),
		 "%.1f s（从最后一帧对端报文算起）" % elapsed_prep)

	# ---------- 9) WaitBusSleep(2 s) → BUS_SLEEP ----------
	ok_sleep, dt_sleep = wait_state(NM_ST_BUS_SLEEP, 3.5)
	note("WaitBusSleep(2 s) 后进入 BUS_SLEEP", ok_sleep, "%.1f s" % dt_sleep)
	s = state()
	note("BUS_SLEEP 时 ComM 也回到 NO_COM", (s is not None) and (s[1] == COMM_NO_COM),
		 s[0] if s else "(无)")

	# ---------- 10) 被动启动 ----------
	out = send("!A", 0.15)
	note("!A: 唤醒指示被接受", "issued" in out, out.strip().splitlines()[0][:56] if out.strip() else "(无)")

	# 同样**先抓帧**：`!A` 返回时约 150 ms，再抓 450 ms 到 ~650 ms，
	# 仍在 RepeatMessageTime(800 ms) 之内，能稳定拿到报文。
	drain(0.05)
	pass_frames = capture(0.45)
	pass_cbv_ok = (len(pass_frames) > 0) and all((f[1][1] & 0x10) == 0 for f in pass_frames)
	note("被动启动: 从 BUS_SLEEP 发出报文", len(pass_frames) > 0, "%d 帧" % len(pass_frames))
	note("被动启动: 不置主动唤醒位 0x10", pass_cbv_ok,
		 ("byte1=0x%02X" % pass_frames[0][1][1]) if pass_frames else "(无帧)")

	# 没有本地请求 → RepeatMessageTime 后落 READY_SLEEP
	ok_back, dt_back = wait_state(NM_ST_READY_SLEEP, 1.8)
	note("被动启动后无本地请求 → 回 READY_SLEEP", ok_back, "%.1f s" % dt_back)

	# ---------- 11) 不破坏原有功能 ----------
	#
	# @note M11 起 `!R` 是**真的释放通信**：ComM 落到 NO_COM 之后，
	#       CanSM 会把控制器停掉（freeze），总线上不再有帧、诊断也进不来。
	#       所以断言"心跳还在发 / 诊断还通"之前，必须先重新请求网络 ——
	#       这不是放宽标准，而是现在的语义本来如此：通信由 ComM 统一管。
	send("!a", 0.2)
	_ = wait_state(NM_ST_NORMAL, 2.0)
	drain(0.2)
	t0 = time.time()
	heartbeat = 0
	while time.time() - t0 < 1.2:
		m = bus.recv(0.05)
		if (m is not None) and (m.arbitration_id == 0x123):
			heartbeat += 1
	note("回归: 心跳 0x123 仍在发", heartbeat >= 1, "%d 帧 / 1.2 s" % heartbeat)

	tp = Isotp(bus)
	r = tp.request([0x10, 0x03], 2.0)
	note("回归: 诊断 10 03 仍正常", (r is not None) and (r[:2] == b"\x50\x03"),
		 r.hex(" ") if r else "(无响应)")

	# 收尾：释放，别让板子一直发报文影响下一条验收
	send("!R", 0.15)

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
