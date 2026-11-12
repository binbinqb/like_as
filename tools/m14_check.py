#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M14 验收：通信矩阵承载能力压测（20+ 条报文 / 邮箱分组 / 软件过滤 / 丢帧率）。

设计意图
--------
不是"验证某条报文能收到"，而是回答三个会决定架构的问题：

  1. **段掩码够不够用**：`0x18FFxxxx` 一个邮箱真的能扛住十几条 J1939 报文吗？
  2. **软件过滤有没有坑**：二分查找在 20 项、含掩码项时会不会漏？
  3. **丢帧率是多少**：500 kbps 下连续注入，硬件邮箱和主循环谁先撑不住？

做法分两轮，**两轮的判据完全不同**：

  轮 1（逐条）   每条发 5 帧、间隔 10 ms。判据是"对应邮箱计数**精确** +5"。
                 这一轮慢，但能抓出"某条报文被掩码区间吃掉"这类静默错误 ——
                 这类错误在混合压测里只会表现为"少了 1%"，看不出是哪条。

  轮 2（混合）   所有报文交替发、不加延时。判据是"总丢帧率 < 阈值"。
                 这一轮才测得出真实承载能力。

为什么必须从 `!k` 的**按邮箱**计数读，而不是只看"应用层收到多少"
------------------------------------------------------------------------
应用层看到的是 CanIf 过滤**之后**的结果，而丢帧可能发生在三个位置：

  | 位置 | `!k` 的 total | 应用层 | 说明 |
  |------|---------------|--------|------|
  | 硬件掩码没放行 | 不涨 | 不涨 | 帧根本没进邮箱 |
  | 邮箱满/总线错误 | 不涨 | 不涨 | 同上，但 `!e` 能看到 TEC/REC |
  | CanIf 软件过滤 | **涨** | 不涨 | 表序或掩码配错了 |

只看应用层，这三种情况长得一模一样。

用法
----
    python tools/flash.py --boot --run         # 先烧进去
    python tools/m14_check.py                  # 跑压测

@author binbina
"""

import argparse
import re
import sys
import time

# ── 旧 `!x` → 新 shell 命令（M-Shell 迁移；旧兼容桥已删）─────────────
CMD_MAP = {
	'!k': 'can counters',
	'!K': 'can counters clear',
	'!f': 'can burst',
}


def xlate(cmd):
	"""旧单字符命令翻译成新命令；其它原样透传。保证以换行结尾。"""
	c = CMD_MAP.get(cmd.strip(), cmd.strip())
	if not c.endswith("\n"):
		c += "\n"
	return c



import can

# Kvaser 的发送缓冲溢出属于 `CANLIBOperationError`，它的基类是 `CanlibError`，
# 与 `can.CanError` 没有继承关系，必须分开捕。
TRANSIENT_ERRORS = (can.CanError,)
try:
	from can.interfaces.kvaser.canlib import CanlibError
	TRANSIENT_ERRORS = TRANSIENT_ERRORS + (CanlibError,)
except Exception:
	pass
import serial

# ============================ [ 被测报文清单 ] ============================
#
# 与 `CanIf_Cfg.c` 的 RX 表严格对应。改表时必须同步改这里，
# 否则压测会"验证一个不存在的配置"而且全部通过 —— 比失败更危险。
#
# (canid, is_ext, mailbox, 期望落到哪个 PDU, 名字)
CASES = [
	# ---- 标准帧段（邮箱 15/16/17）----
	(0x0A0, False, 7, 12, "std fast  0x0A0"),
	(0x0A1, False, 7, 12, "std fast  0x0A1"),
	(0x0A2, False, 7, 12, "std fast  0x0A2"),
	(0x100, False, 8, 13, "std light 0x100"),
	(0x101, False, 8, 13, "std light 0x101"),
	(0x102, False, 8, 13, "std light 0x102"),
	(0x110, False, 9, 14, "std body  0x110"),

	# ---- 核心回归项 ----
	(0x321, False, 1, 0, "regress   0x321"),

	# ---- J1939 段 0xFExx（邮箱 6）----
	(0x18FEA100, True, 6, 9, "j1939     PGN FEA1"),
	(0x18FEB100, True, 6, 8, "j1939     PGN FEB1"),
	(0x18FEC100, True, 6, 7, "j1939     PGN FEC1"),
	(0x18FEE000, True, 6, 21, "j1939     PGN FEE0 里程"),
	(0x18FEF100, True, 6, 6, "j1939     PGN FEF1 车速"),

	# ---- J1939 段 0xFFxx（邮箱 2）----
	(0x18FF0001, True, 2, 1, "j1939     PGN FF00 SA1"),
	(0x18FF0102, True, 2, 5, "j1939     PGN FF01 灯光"),
	(0x18FF0203, True, 2, 16, "j1939     PGN FF02 门锁"),
	(0x18FF0304, True, 2, 17, "j1939     PGN FF03 雨刮"),
	(0x18FF0401, True, 2, 18, "j1939     PGN FF04 SA1"),
	(0x18FF0402, True, 2, 18, "j1939     PGN FF04 SA2"),
	(0x18FF0405, True, 2, 18, "j1939     PGN FF04 SA5"),
	(0x18FF0501, True, 2, 19, "j1939     PGN FF05 报警"),
	(0x18FF0610, True, 2, 20, "j1939     PGN FF06 高频"),
	(0x18FFFF00, True, 2, 22, "j1939     PGN FFFF 段内最大"),
]

# 判据阈值。轮 1 必须 100% 精确；轮 2 允许极少量丢（总线上还有别的流量）。
ROUND1_LOSS_MAX = 0
ROUND2_LOSS_MAX = 0.02      # 2%


def die(msg):
	print("\n[FAIL] %s" % msg)
	sys.exit(1)


class Dut:
	"""被测板：串口读计数 + CAN 注入。"""

	def __init__(self, port, baud, channel, bitrate):
		self.ser = serial.Serial(port, baud, timeout=0.2)
		self.ser.reset_input_buffer()
		self.bus = can.Bus(interface="kvaser", channel=channel, bitrate=bitrate)
		self.tx_frames = 0
		self.bitrate = bitrate

	def cmd(self, text, wait=0.25):
		"""发一条串口命令并读回显（用于 `!K` 这类只输出一行的）。"""
		self.ser.reset_input_buffer()
		self.ser.write(xlate(text).encode("ascii"))
		self.ser.flush()
		time.sleep(wait)
		return self.ser.read(65536).decode("utf-8", "replace")

	def read_counters(self):
		"""发 `!k`，解析成（按邮箱、按通道总/中断、**按 PDU**）三组计数。"""
		raw = self.cmd("!k", wait=0.35)
		per_ch = {}
		total = {}
		isr = {}

		per_pdu = {}

		for line in raw.splitlines():
			line = line.strip()
			m = re.match(r"CAN(\d)\s+total=(\d+)\s+isr=(\d+)", line)
			if m:
				ch = int(m.group(1))
				total[ch] = int(m.group(2))
				isr[ch] = int(m.group(3))
				per_ch.setdefault(ch, {})
				continue
			m = re.match(r"pdu\s+(\d+)\s*=\s*(\d+)", line)
			if m:
				per_pdu[int(m.group(1))] = int(m.group(2))
				continue
			m = re.match(r"mb(\d+)\s*=\s*(\d+)", line)
			if m:
				mb = int(m.group(1))
				n = int(m.group(2))
				per_ch.setdefault(0, {})[mb] = n
		return per_ch, total, isr, per_pdu

	def send(self, canid, is_ext, data=None, gap=0.0):
		if data is None:
			data = bytes([0x5A] * 8)
		msg = can.Message(arbitration_id=canid, data=data,
						  is_extended_id=is_ext, dlc=8)
		# Kvaser 的发送缓冲很浅：全速推 2000+ 帧会抛
		# `CANLIBOperationError: Transmit buffer overflow`。
		# 这里重试三次而不是简单加延时 —— 延时加多了测不出真实上限，
		# 重试则让"缓冲瞬时满"不影响最终计数（总帧数仍然精确）。
		# ⚠ Kvaser 溢出抛的是 `CANLIBOperationError`，它继承自 `CanlibError(Exception)`，
		#   **不是** `can.CanError`。只捕 CanError 时这个重试形同不存在 ——
		#   现象是"压测刚开始就崩在 send 上"。
		for attempt in range(8):
			try:
				self.bus.send(msg)
				break
			except TRANSIENT_ERRORS:
				if attempt == 7:
					raise
				time.sleep(0.002 * (attempt + 1))
		self.tx_frames += 1
		if gap > 0.0:
			time.sleep(gap)

	def close(self):
		try:
			self.bus.shutdown()
		except Exception:
			pass
		try:
			self.ser.close()
		except Exception:
			pass


def round1_per_case(dut):
	"""轮 1：逐条注入，验证每条报文都进得了它该进的邮箱。

	判据是"该邮箱计数精确增加 PER_CASE 帧" —— 不是"大于 0"。
	大于 0 的判断会漏掉"发 5 帧只收了 1 帧"这种，而那种情况在
	真实场景里就是 80% 丢包。
	"""
	PER_CASE = 5
	print("\n" + "=" * 72)
	print(" 轮 1：逐条验证（每条 %d 帧，间隔 5 ms）" % PER_CASE)
	print("=" * 72)

	dut.cmd("!K", wait=0.3)
	base, _, _, _ = dut.read_counters()
	base_mb = base.get(0, {})

	fails = []
	for canid, is_ext, mb, pdu, name in CASES:
		# 一次 `!k` 同时拿到邮箱和 PDU 两组计数 —— 每条用例读两次而不是四次，
		# 每条 `!k` 有 0.35 s 的等待，23 条用例省下约 15 秒。
		per_ch_b, _, _, pdu_b = dut.read_counters()
		before = per_ch_b.get(0, {}).get(mb, 0)
		for _ in range(PER_CASE):
			dut.send(canid, is_ext)
			time.sleep(0.005)
		time.sleep(0.15)
		per_ch_a, _, _, pdu_a = dut.read_counters()
		after = per_ch_a.get(0, {}).get(mb, 0)
		got = after - before
		# 同时验**软件层**：这几帧必须落到本用例声明的那一个 PDU 上。
		# 只验邮箱计数的话，"过滤表投错 PDU"和"被前一项截走"测不出来 ——
		# 那两种错在邮箱计数上看起来完全是正常的。
		pdu_got = pdu_a.get(pdu, 0) - pdu_b.get(pdu, 0)
		ok = (got == PER_CASE) and (pdu_got == got)
		print("  %-24s mb%-2u pdu%-2u  tx=%d  rx=%d  %s"
			  % (name, mb, pdu, PER_CASE, got,
			     "ok" if ok else
			     ("**FAIL** mb=%d pdu=%d" % (got, pdu_got))))
		if not ok:
			fails.append("%s: expected %d got mb=%d pdu=%d"
						 % (name, PER_CASE, got, pdu_got))

	if fails:
		print("\n  失败 %d 条：" % len(fails))
		for f in fails:
			print("    - %s" % f)
	return len(fails) == 0


def round2_stress(dut, per_msg):
	"""轮 2：全速混合注入，测丢帧率。

	所有报文交替发（不是一条发完再发下一条），模拟真实总线上的
	"多 ID 交织" —— 那才是邮箱和主循环真正要承受的负载。
	"""
	print("\n" + "=" * 72)
	print(" 轮 2：混合压测（%d 条 × %d 帧 = %d 帧，不加延时）"
		  % (len(CASES), per_msg, len(CASES) * per_msg))
	print("=" * 72)

	dut.cmd("!K", wait=0.3)
	_, base_total, _, _ = dut.read_counters()
	t0 = time.time()
	dut.tx_frames = 0

	for _ in range(per_msg):
		for canid, is_ext, mb, pdu, name in CASES:
			dut.send(canid, is_ext)

	elapsed = time.time() - t0
	time.sleep(0.4)                     # 等尾部帧落地

	per_ch, total, isr, per_pdu = dut.read_counters()
	rx = total.get(0, 0) - base_total.get(0, 0)
	tx = dut.tx_frames
	lost = tx - rx
	loss = (float(lost) / tx * 100.0) if tx else 0.0
	isr_n = isr.get(0, 0)
	per_isr = (float(rx) / isr_n) if isr_n else 0.0

	# 主机侧 elapsed 是"Python 循环跑完"的时间，**不是总线时间** ——
	# Kvaser 的发送缓冲会把帧排队，循环可以先跑完。所以这里另算一个
	# "理想位长总线时间"作为对照，两者的差距本身就能说明是否已满线注入。
	n_std = sum(1 for c in CASES if not c[1]) * per_msg
	n_ext = sum(1 for c in CASES if c[1]) * per_msg
	# 8 字节数据帧（含 3 bit 帧间隔、不含位填充）：
	#   标准帧 44 + 64 = 108 → 111；扩展帧 67 + 64 = 131 → 134
	wire_s = (n_std * 111.0 + n_ext * 134.0) / float(dut.bitrate)

	print("  注入      : %d 帧（标准 %d / 扩展 %d）" % (tx, n_std, n_ext))
	print("  主机耗时  : %.2f s —— **这是主机排队时间，不是总线时间**" % elapsed)
	print("  总线占用  : >= %.2f s（按理想位长 111/134 bit 估算，%d kbps）"
		  % (wire_s, dut.bitrate // 1000))
	if elapsed < wire_s * 0.9:
		print("  满线状态  : 是（主机比总线快 %.1f 倍 → Kvaser 在内部排队，"
			  "实际是背靠背满线注入）" % (wire_s / elapsed))
	print("  接收      : %d 帧" % rx)
	print("  丢失      : %d 帧  (%.2f%%)" % (lost, loss))
	print("  邮箱中断  : %d 次  (每次平均 %.2f 帧)" % (isr_n, per_isr))

	print("\n  按邮箱分布：")
	for mb in sorted(per_ch.get(0, {}).keys()):
		exp = sum(1 for c in CASES if c[2] == mb) * per_msg
		got = per_ch[0][mb]
		flag = "" if got == exp else "   <-- 差异 %+d" % (got - exp)
		print("    mb%-2u  expect=%-6d got=%-6d%s" % (mb, exp, got, flag))

	# 软件过滤后的分布。这一组与上面必须**逐项一致**：
	# 邮箱对、PDU 不对，说明过滤表配错（canid/mask/顺序），而总线完全正常。
	print("\n  按 PDU 分布（CanIf 软件过滤后）：")
	pdu_bad = 0
	for pdu in sorted(set(c[3] for c in CASES)):
		exp = sum(1 for c in CASES if c[3] == pdu) * per_msg
		got = per_pdu.get(pdu, 0)
		flag = "" if got == exp else "   <-- 差异 %+d" % (got - exp)
		if got != exp:
			pdu_bad += 1
		print("    pdu%-2u  expect=%-6d got=%-6d%s" % (pdu, exp, got, flag))

	return loss, per_isr, pdu_bad


def main():
	ap = argparse.ArgumentParser(description="M14 通信矩阵压测")
	ap.add_argument("--port", default="COM2", help="串口（板子的控制台）")
	ap.add_argument("--baud", type=int, default=115200)
	ap.add_argument("--channel", type=int, default=0, help="Kvaser 通道")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--per-msg", type=int, default=100,
					help="轮 2 每条报文发几帧（默认 100 → 总 2300 帧）")
	ap.add_argument("--skip-round1", action="store_true")
	a = ap.parse_args()

	print("=" * 72)
	print(" M14 验收：通信矩阵承载能力")
	print("=" * 72)
	print("  报文数    : %d 条（标准帧 %d / 扩展帧 %d）"
		  % (len(CASES),
			 sum(1 for c in CASES if not c[1]),
			 sum(1 for c in CASES if c[1])))
	print("  邮箱数    : %d 个（%s）"
		  % (len(set(c[2] for c in CASES)),
			 ", ".join("mb%d" % m for m in sorted(set(c[2] for c in CASES)))))

	dut = Dut(a.port, a.baud, a.channel, a.bitrate)
	results = []
	try:
		if not a.skip_round1:
			ok1 = round1_per_case(dut)
			results.append(("轮1 逐条验证", ok1, ""))

		loss, per_isr, pdu_bad = round2_stress(dut, a.per_msg)
		ok2 = loss <= (ROUND2_LOSS_MAX * 100.0)
		results.append(("轮2 丢帧率", ok2, "%.2f%%" % loss))
		# perISR 的判据是**越小越好**（每帧一次中断 = ISR 即时响应、无积压）。
		# 最初写成 `>= 1.0` 是反的：1.00 在丢帧为 0 时恰恰是健康状态，
		# 而 >1.5 才说明帧在邮箱里排队、中断被推迟处理。
		results.append(("轮2 中断无积压", per_isr <= 1.5, "%.2f 帧/中断" % per_isr))
		results.append(("轮2 PDU 路由", pdu_bad == 0, "%d 项不符" % pdu_bad))
	finally:
		dut.close()

	print("\n" + "=" * 72)
	print(" 结论")
	print("=" * 72)
	allOk = True
	for name, ok, detail in results:
		print("  [%s] %-16s %s" % ("ok" if ok else "FAIL", name, detail))
		allOk = allOk and ok

	print("\n  判据说明：")
	print("    - 轮 1 要求每条报文精确收到 5/5 —— 差 1 帧都说明掩码区间有问题")
	print("    - 轮 2 丢帧率阈值 %.0f%%；超过说明需要开包池或降低中断频率"
		  % (ROUND2_LOSS_MAX * 100))
	print("    - 每中断帧数 ≈ 1.0 = 每帧一次中断、ISR 即时响应（健康）；"
	      " > 1.5 说明帧在邮箱里排队、中断被推迟（CPU 忙或被长时间屏蔽）")

	return 0 if allOk else 1


if __name__ == "__main__":
	sys.exit(main())
