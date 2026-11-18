#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M10 验收：Com 信号层（打包 / 解包 / 信号超时 / 分组启停）。

**这一版刻意不接灯光、门锁、雨刮等业务信号** —— 那些信号的位布局来自
整车通信矩阵，现在还没有。先用两个测试报文把 Com 的**机制**钉死：

	1. **周期发送**：0x200 每 100 ms 一帧，标准帧 8 字节；
	2. **字节对齐打包**：byte0 = TX_COUNTER，每帧 +1；
	3. **非字节对齐的单 bit**：TX_FLAG 起始位 9 → byte1 = 0x02（只置 bit1）；
	4. **跨字节但不占满**：TX_LEVEL = 0xABC、12 位 → byte2=0xBC、byte3=0x0A，
	   且 byte3 高 4 位必须是 0（写成 16 位就会变成 0x?BC）；
	5. **接收解包**：注入 0x201 → `!v` 读到的 cnt / temp 与注入值一致；
	6. **Motorola 大端**：byte2=0x01、byte3=0x23 → 291（不是 0x2301）；
	7. **信号超时替换**：对端停发 1 s 后，RX_COUNTER 读 0xEE（替换值）、
	   RX_TEMP 回 0（初值）；
	8. **分组启停**：`!y` 停 → 总线上 0 帧；再 `!y` → 恢复 100 ms；
	9. **不破坏原有功能**：心跳 0x123、诊断 `10 03`、NM 0x500 都还在。

## 为什么这些看起来"吹毛求疵"

Com 的三类错误**都不会报错**，只会让整车行为不对：

| 错误 | 现象 |
|---|---|
| 位偏移写错 1 位 | 某个灯永远不亮，或一直亮 —— 因为读到的永远是邻居那一位 |
| 12 位写成 16 位 | 值"大部分时候对"，偶尔多出 0x?000，实车表现为偶发抖动 |
| 大小端搞反 | 温度 25 ℃ 变成 8961 ℃，但**仍在合法数值范围内**，不会触发任何检查 |

所以这一层必须用具体的字节内容钉死，不能只验"有帧发出来"。

## 两个实测踩出来的坑

**① 大端信号的 `BitPosition` 是 7，不是 0**
填 0 时总线上 `01 23` 读回来是 `0x9180`（左移 7 位）。见 `Com_Cfg.c` 的 `@warning`。

**② TX/RX 不能共用一个 ID**
最初写成都用 0x200，结果**接收测试没法做**：板子每 100 ms 也在发 0x200，
Kvaser 一注入就撞车，抓到的帧内容互相污染。现在 TX=0x200 / RX=0x201。

前置：
	- 板子在跑 M10 固件；
	- Kvaser ch0 接 CAN0（500 kbps）；
	- COM2 串口。

用法：
	python tools/m10_check.py

@author binbina
"""

import argparse
import re
import sys
import time

# ── 旧 `!x` → 新 shell 命令（M-Shell 迁移；旧兼容桥已删）─────────────
CMD_MAP = {
	'!v': 'com sig',
	'!y': 'com group',
	'!a': 'nm req',
	'!R': 'nm rel',
	'!m': 'nm',
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
from _can_keeper import Keeper

PORT = "COM2"
BAUD = 115200

COM_TX_ID = 0x200
COM_RX_ID = 0x201

# `!v` 输出：
# `[com] tx cnt=40 flag=1 level=0xABC | rx cnt=238(ok) temp=0(ok) | grp=1`
RE_SIG = re.compile(
	r"\[com\] tx cnt=(\d+) flag=(\d+) level=0x([0-9A-Fa-f]+) \| "
	r"rx cnt=(\d+)\((\w+)\) temp=(\d+)\((\w+)\) \| grp=(\d)")

# 期望的 TX 信号值（与 main.c 的 `s_comTxFlag` / `s_comTxLevel` 一致）
EXPECT_FLAG = 1
EXPECT_LEVEL = 0xABC

# 信号超时配置为 1000 ms，留足余量
SIGNAL_TIMEOUT = 1.0
SUBST_COUNTER = 0xEE          # Com_SubstValue_RxCounter


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
	kp = Keeper(1 - a.channel, a.bitrate)

	def drain(sec=0.3):
		"""丢掉驱动缓冲里的历史帧。

		@note  不做这一步会得到假数据：Kvaser 驱动会把报文缓存起来，
		        上一段测试的帧会算进这一段的计数。实测踩过 ——
		        "1 秒内 19 帧" 其实就是缓冲里还压着上一条用例的帧。
		"""
		t = time.time()
		while time.time() - t < sec:
			bus.recv(0.02)

	def send(cmd, wait=0.2):
		ser.reset_input_buffer()
		ser.write(xlate(cmd).encode())
		time.sleep(wait)
		return ser.read(8192).decode("utf-8", "replace")

	def signals():
		"""读一次 `!v`，返回 dict 或 None。"""
		out = send("!v", 0.15)
		m = RE_SIG.search(out)
		if m is None:
			return None
		return {
			"tx_cnt": int(m.group(1)), "tx_flag": int(m.group(2)),
			"tx_level": int(m.group(3), 16),
			"rx_cnt": int(m.group(4)), "rx_flag": m.group(5),
			"rx_temp": int(m.group(6)), "rx_temp_flag": m.group(7),
			"grp": int(m.group(8)),
		}

	def capture(seconds, arb_id=COM_TX_ID):
		t0 = time.time()
		out = []
		while time.time() - t0 < seconds:
			m = bus.recv(0.02)
			if (m is not None) and (m.arbitration_id == arb_id):
				out.append((round((time.time() - t0) * 1000), bytes(m.data), m.is_extended_id))
		return out

	def inject(cnt, hi, lo, times=4, gap=0.09):
		"""注入 0x201：byte0=cnt，byte2=hi，byte3=lo（Motorola 高字节在前）。"""
		for _ in range(times):
			bus.send(can.Message(arbitration_id=COM_RX_ID, is_extended_id=False,
			                     data=[cnt, 0, hi, lo, 0, 0, 0, 0], dlc=8))
			time.sleep(gap)

	def wait_signal(pred, timeout):
		"""轮询 `!v` 直到 pred(值) 为真。"""
		t0 = time.time()
		last = None
		while (time.time() - t0) < timeout:
			last = signals()
			if (last is not None) and pred(last):
				return True, last, time.time() - t0
			time.sleep(0.05)
		return False, last, time.time() - t0

	# ---------- 0) 先把通道拉起来，再确保分组是开着的 ----------
	#
	# @note M11 起通信由 ComM 统一管理：`!R`（释放）会让 CanSM 真的把
	#       控制器停掉，总线上就没有帧、也不收帧。所以本脚本不能假设
	#       上一条验收留下的状态 —— 先请求网络，等到首帧出现为止。

	# A3：0x123 心跳是驱动层自测帧，默认关闭。本脚本末尾那条
	# "回归: 心跳 0x123 仍在发" 依赖它，所以显式打开。
	send("can auto on", 0.2)

	send("!a", 0.2)
	t0 = time.time()
	while time.time() - t0 < 2.0:
		if bus.recv(0.05) is not None:
			break

	s = signals()
	if (s is not None) and (s["grp"] == 0):
		send("!y", 0.2)      # 之前被停了，重新开
		time.sleep(0.3)
	drain(0.5)

	# ---------- 1) 周期 100 ms ----------
	frames = capture(1.2)
	gaps = [frames[i + 1][0] - frames[i][0] for i in range(len(frames) - 1)]
	avg = (sum(gaps) / len(gaps)) if gaps else 0.0
	note("周期: 100 ms", (len(gaps) >= 8) and (85 <= avg <= 115),
		 "平均 %.1f ms / %d 个间隔" % (avg, len(gaps)))
	note("周期: 抖动在 ±20 ms 内",
		 (len(gaps) >= 8) and all(abs(g - 100) <= 20 for g in gaps),
		 "min=%d max=%d" % (min(gaps), max(gaps)) if gaps else "(无)")

	# ---------- 2) 帧格式 ----------
	f0 = frames[0] if frames else None
	note("报文: 标准帧（非扩展）", (f0 is not None) and (not f0[2]),
		 "STD" if (f0 and not f0[2]) else "EXT/无")
	note("报文: 8 字节", (f0 is not None) and (len(f0[1]) == 8),
		 "%d 字节" % (len(f0[1]) if f0 else 0))

	# ---------- 3) byte0 每帧 +1 ----------
	cnts = [f[1][0] for f in frames]
	deltas = [(cnts[i + 1] - cnts[i]) & 0xFF for i in range(len(cnts) - 1)]
	note("byte0（TX_COUNTER）每帧 +1（模 256）",
		 (len(deltas) >= 5) and all(d == 1 for d in deltas),
		 "deltas=%s" % deltas[:8])

	# ---------- 4) 1 位信号在 byte1 的 bit1 ----------
	b1 = [f[1][1] for f in frames]
	note("byte1（TX_FLAG@bit9）恒为 0x02",
		 (len(b1) > 0) and all(v == (EXPECT_FLAG << 1) for v in b1),
		 "值集合=%s" % sorted(set(b1)))

	# ---------- 5) 12 位跨字节 ----------
	note("byte2（TX_LEVEL 低 8 位）= 0x%02X" % (EXPECT_LEVEL & 0xFF),
		 (len(frames) > 0) and all(f[1][2] == (EXPECT_LEVEL & 0xFF) for f in frames),
		 "值集合=%s" % sorted(set(f[1][2] for f in frames)))
	note("byte3（TX_LEVEL 高 4 位）= 0x%02X（高 4 位必须为 0）" % ((EXPECT_LEVEL >> 8) & 0x0F),
		 (len(frames) > 0) and all(f[1][3] == ((EXPECT_LEVEL >> 8) & 0x0F) for f in frames),
		 "值集合=%s" % sorted(set(f[1][3] for f in frames)))
	note("byte4~7 未被任何信号占用，应为 0",
		 (len(frames) > 0) and all(all(v == 0 for v in f[1][4:]) for f in frames))

	# ---------- 6) 应用侧信号值与总线一致 ----------
	s = signals()
	note("!v tx 与总线上最后一帧一致",
		 (s is not None) and (s["tx_flag"] == EXPECT_FLAG) and
		 (s["tx_level"] == EXPECT_LEVEL) and (abs(s["tx_cnt"] - cnts[-1]) <= 3),
		 s and "tx cnt=%d flag=%d level=0x%03X" % (s["tx_cnt"], s["tx_flag"], s["tx_level"]))

	# ---------- 7) 接收解包 + Motorola 大端 ----------
	cases = [
		(0x33, 0x01, 0x23, 0x33, 0x0123, "01 23 -> 291"),
		(0x40, 0xFF, 0xFF, 0x40, 0xFFFF, "FF FF -> 65535"),
		(0x50, 0x80, 0x00, 0x50, 0x8000, "80 00 -> 32768"),
	]
	for cnt, hi, lo, exp_cnt, exp_temp, desc in cases:
		inject(cnt, hi, lo)
		ok, st, _ = wait_signal(
			lambda v, e=exp_cnt, t=exp_temp: (v["rx_cnt"] == e) and (v["rx_temp"] == t), 1.0)
		note("RX %s" % desc, ok,
			 st and "cnt=%d temp=%d" % (st["rx_cnt"], st["rx_temp"]))

	# ---------- 8) 信号超时替换 ----------
	# 对端已停发，等过 1 s 超时
	ok_to, st, dt = wait_signal(
		lambda v: (v["rx_cnt"] == SUBST_COUNTER) and (v["rx_temp"] == 0),
		SIGNAL_TIMEOUT + 1.2)
	note("信号超时: RX_COUNTER 替换为 0xEE", ok_to,
		 st and "cnt=0x%02X temp=%d（%.1f s）" % (st["rx_cnt"], st["rx_temp"], dt))
	note("信号超时: RX_TEMP 回初值 0", (st is not None) and (st["rx_temp"] == 0),
		 st and "temp=%d" % st["rx_temp"])

	# ---------- 9) 分组启停 ----------
	drain(0.4)
	before = len(capture(1.0))
	out = send("!y", 0.2)
	time.sleep(0.3)
	drain(0.5)
	stopped = len(capture(1.0))
	s_stop = signals()
	note("!y: 分组停止后总线上 0 帧", stopped == 0,
		 "停止前 %d 帧 / 停止后 %d 帧" % (before, stopped))
	note("!y: 停止后 grp=0", (s_stop is not None) and (s_stop["grp"] == 0),
		 s_stop and "grp=%d" % s_stop["grp"])

	send("!y", 0.2)
	time.sleep(0.3)
	drain(0.5)
	resumed = len(capture(1.0))
	s_run = signals()
	note("!y: 恢复后回到 ~10 帧/秒", 8 <= resumed <= 12, "%d 帧 / 1.0 s" % resumed)
	note("!y: 恢复后 grp=1", (s_run is not None) and (s_run["grp"] == 1),
		 s_run and "grp=%d" % s_run["grp"])

	# ---------- 10) 不破坏原有功能 ----------
	drain(0.2)
	t0 = time.time()
	hb = 0
	while time.time() - t0 < 1.2:
		m = bus.recv(0.05)
		if (m is not None) and (m.arbitration_id == 0x123):
			hb += 1
	note("回归: 心跳 0x123 仍在发", hb >= 1, "%d 帧 / 1.2 s" % hb)

	# NM 默认在 BUS_SLEEP，**不请求就不发**（这是正确行为，不是故障）。
	# 所以要先 `!a` 把它拉起来再抓 —— 直接抓会得到 0 帧，
	# 那是"没请求"，和"NM 坏了"看起来一样。
	send("!a", 0.2)
	drain(0.3)
	nm = len(capture(1.2, 0x500))
	send("!R", 0.15)
	note("回归: NM 0x500 仍能发（M9）", nm >= 3, "%d 帧 / 1.2 s" % nm)

	tp = Isotp(bus)
	r = tp.request([0x10, 0x03], 2.0)
	note("回归: 诊断 10 03 仍正常", (r is not None) and (r[:2] == b"\x50\x03"),
		 r.hex(" ") if r else "(无响应)")

	kp.close()
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
