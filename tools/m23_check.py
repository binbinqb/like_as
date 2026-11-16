#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M23 验收：车身信号绑定层（业务语义 ↔ 总线 raw 的双向翻译）。

## 为什么这一层的验收必须"对字节"

绑定层的全部价值在于映射方向没搞反。而方向搞反了**编译不报错、运行不报错**：

| 若映射写反 | 现象 |
|---|---|
| `ON` 翻译成 raw 2 | 业务说"灯亮"，总线上是"故障"，仪表点故障灯 |
| `raw 2` 翻成 `ON` | 对方报故障，BCM 当"正常亮着"，实际回路已失效 |
| 位偏移错 1 位 | 近光灯的位落到远光灯上，两个灯互相顶 |
| 位序搞反 | 11 个灯全是乱的，但每个值都在合法域 0..3 内，无任何告警 |

所以判据不是"有帧发出来"，而是**整帧 8 字节精确相等**。四个状态各一组
期望值，全部手算（推导见 `app/app/src/cmd/bcm_cmd.c` 的 BCMCMD_EXPECT）。

## 手算依据

`BCM_LCSF` 0x18FE4021，11 个信号全为 2 bit 小端，位偏移
4/6/8/12/14/24/30/32/44/46/48。raw 值 = 业务语义（默认映射表）：

| 语义 | raw | 二进制（2 bit） |
|---|---|---|
| OFF | 0 | `00` |
| ON | 1 | `01` |
| FAULT | 2 | `10` |
| UNKNOWN | 3 | `11` |

于是全设同一状态时：

| 命令 | 期望 8 字节 |
|---|---|
| `bcm all off` | `00 00 00 00 00 00 00 00` |
| `bcm all on` | `50 51 00 41 01 50 01 00` |
| `bcm all fault` | `A0 A2 00 82 02 A0 02 00` |
| `bcm all unknown` | `F0 F3 00 C3 03 F0 03 00` |
| `bcm low on` | `10 00 00 00 00 00 00 00` |
| `bcm brake fault` | `00 00 00 00 00 80 00 00` |

## 前置

- 板子在跑含 M23 的 App 固件；
- Kvaser ch1 接 CAN1（500 kbps）；
- COM2 串口（板级 shell）。

用法：
	python tools/m23_check.py

@author binbina
"""

import argparse
import re
import sys
import time

import can
import serial

PORT = "COM2"
BAUD = 115200
LCSF_ID = 0x18FE4021
TX_CYCLE_S = 0.05          # BCM_LCSF 周期 50 ms

# 期望帧（见文件头的手算表）
EXPECT = {
	"off": bytes([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),
	"on": bytes([0x50, 0x51, 0x00, 0x41, 0x01, 0x50, 0x01, 0x00]),
	"fault": bytes([0xA0, 0xA2, 0x00, 0x82, 0x02, 0xA0, 0x02, 0x00]),
	"unknown": bytes([0xF0, 0xF3, 0x00, 0xC3, 0x03, 0xF0, 0x03, 0x00]),
}
EXPECT_SINGLE = {
	("low", "on"): bytes([0x10, 0, 0, 0, 0, 0, 0, 0]),
	("brake", "fault"): bytes([0, 0, 0, 0, 0, 0x80, 0, 0]),
}

# shell 里 `bcm` 输出的字节行：`  LCSF(0x18FE4021) buf = 50 51 00 ...`
RE_BUF = re.compile(r"LCSF\(0x18FE4021\) buf =((?:\s+[0-9A-F]{2})+)")
# `bcm` dump 的灯状态行：`   low    ON`
# @note 必须带 re.M：`^`/`$` 默认只匹配整串首尾，不加就一条都匹配不到，
#       而 findall 返回空列表又会让 `all(...)` 假通过 —— 这个坑实际踩到过。
RE_LAMP = re.compile(r"^\s{3}([a-z]+)\s{2,}(UNKNOWN|OFF|ON|FAULT)\s*$", re.M)

LAMP_ORDER = ["low", "high", "fogf", "turnr", "turnl", "drl",
              "pos", "fogr", "rev", "brake", "int"]


def xlate(cmd):
	"""保证命令以换行结尾（letter-shell 靠换行切命令，不发就一直等）。

	@note 早先漏了补换行，shell 收到了字符但没有结束符 —— 现象是
	      "命令打进去毫无反应，只有心跳在刷"，很容易误判成命令没注册。
	"""
	c = cmd.strip()
	if not c.endswith("\n"):
		c += "\n"
	return c


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--baud", type=int, default=BAUD)
	ap.add_argument("--channel", type=int, default=1, help="Kvaser 通道（1=CAN1）")
	ap.add_argument("--bitrate", type=int, default=500000)
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))
		print("  [%s] %s%s" % ("PASS" if ok else "FAIL", name,
		                       ("   (%s)" % detail) if detail else ""))

	ser = serial.Serial(a.port, a.baud, timeout=0.2)
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)

	def drain(sec=0.3):
		"""丢掉驱动缓冲里的历史帧（Kvaser 会缓存，不清会算进下一段统计）。"""
		t = time.time()
		while time.time() - t < sec:
			bus.recv(0.02)

	def cmd(text, wait=0.35):
		ser.reset_input_buffer()
		ser.write(xlate(text).encode())
		ser.flush()
		time.sleep(wait)
		return ser.read(65536).decode("utf-8", "replace")

	def shell_bytes(text):
		"""从 shell 输出里取 Com 发送缓冲的字节（`dumpLcsfBytes` 打的）。"""
		m = RE_BUF.search(text)
		if m is None:
			return None
		return bytes(int(x, 16) for x in m.group(1).split())

	def last_frame(sec=0.8):
		"""抓一帧 LCSF（取窗口内最后一帧，最接近当前设置）。"""
		t = time.time()
		frame = None
		while time.time() - t < sec:
			msg = bus.recv(0.05)
			if msg is not None and msg.arbitration_id == LCSF_ID:
				frame = bytes(msg.data)
		return frame

	try:
		print("=" * 78)
		print("M23 验收：信号绑定层（语义 ↔ raw）")
		print("=" * 78)

		# ---------- 1. 结构检查：dump 能列出 11 个灯 ----------
		print("\n--- 1 绑定表结构 ---")
		out = cmd("bcm", 0.4)
		lamps = RE_LAMP.findall(out)
		got = [n for n, _ in lamps]
		note("dump 列出 11 个灯", len(lamps) == 11, "实际 %d 个" % len(lamps))
		note("灯名顺序与绑定表一致", got == LAMP_ORDER,
		     " ".join(got) if got else "无输出")
		note("上电初值全为 OFF",
		     len(lamps) == 11 and all(s == "OFF" for _, s in lamps),
		     " ".join(sorted(set(s for _, s in lamps))))

		# ---------- 2. 四个状态各自的整帧 ----------
		print("\n--- 2 整帧对拍（11 个灯同设一档）---")
		for st in ("off", "on", "fault", "unknown"):
			cmd("bcm all %s" % st, 0.25)
			time.sleep(TX_CYCLE_S * 2)      # 等两拍，保证新值已经发出去
			drain(0.15)

			sh = shell_bytes(cmd("bcm", 0.3))
			exp = EXPECT[st]
			note("bcm all %s → Com 缓冲" % st, sh == exp,
			     "%s / 期望 %s" % (sh.hex(" ") if sh else "读不到", exp.hex(" ")))

			frame = last_frame()
			note("bcm all %s → 总线帧" % st, frame == exp,
			     "%s / 期望 %s" % (frame.hex(" ") if frame else "没抓到", exp.hex(" ")))

		# ---------- 3. 单个灯：只动自己那几位 ----------
		print("\n--- 3 单灯粒度（不能碰到邻居）---")
		for (lamp, st), exp in EXPECT_SINGLE.items():
			# 每个用例前先全灭：否则上一个用例留下的状态会串到这一个里
			# （实测踩过：`bcm low on` 之后测 `brake fault`，byte0 还是 0x10）
			cmd("bcm all off", 0.25)
			cmd("bcm %s %s" % (lamp, st), 0.25)
			time.sleep(TX_CYCLE_S * 2)
			drain(0.15)
			frame = last_frame()
			note("bcm %s %s → 只改该信号的位" % (lamp, st), frame == exp,
			     "%s / 期望 %s" % (frame.hex(" ") if frame else "没抓到", exp.hex(" ")))

		# ---------- 4. 业务侧回读：设什么读到什么 ----------
		print("\n--- 4 业务侧回读（TxGet 与设置值一致）---")
		cmd("bcm all on", 0.25)
		out = cmd("bcm", 0.35)
		lamps = RE_LAMP.findall(out)
		note("bcm all on 后 11 个灯都读到 ON",
		     len(lamps) == 11 and all(s == "ON" for _, s in lamps),
		     " ".join("%s=%s" % (n, s) for n, s in lamps))

		cmd("bcm all fault", 0.25)
		out = cmd("bcm", 0.35)
		lamps = RE_LAMP.findall(out)
		note("bcm all fault 后 11 个灯都读到 FAULT",
		     len(lamps) == 11 and all(s == "FAULT" for _, s in lamps),
		     " ".join("%s=%s" % (n, s) for n, s in lamps))

		# ---------- 5. 非法输入要被挡住 ----------
		print("\n--- 5 非法输入拦截 ---")
		cmd("bcm all off", 0.25)
		out = cmd("bcm all bogus", 0.3)
		note("非法状态被拒（提示合法取值）",
		     "on | off | fault | unknown" in out, repr(out[-60:]))
		# 拒绝之后状态不能被改坏
		out = cmd("bcm", 0.35)
		lamps = RE_LAMP.findall(out)
		note("非法输入不改变已有状态",
		     len(lamps) == 11 and all(s == "OFF" for _, s in lamps),
		     " ".join("%s=%s" % (n, s) for n, s in lamps))

		out = cmd("bcm nolamp on", 0.3)
		note("非法灯名被拒（列出合法灯名）",
		     "lamp must be" in out, repr(out[-60:]))

		# ---------- 6. 接收侧：手刹开关 ----------
		print("\n--- 6 接收侧语义翻译（注入 0x18FEF121）---")
		# ParkingBrakeSwitch 在 2|2@1+，即 byte0 bit2-3
		cases = [(0, "OFF"), (1, "ON"), (2, "FAULT"), (3, "UNKNOWN")]
		for raw, exp_state in cases:
			data = bytearray(8)
			data[0] = (raw & 0x03) << 2
			msg = can.Message(arbitration_id=0x18FEF121, data=bytes(data),
			                  is_extended_id=True, dlc=8)
			for _ in range(3):
				try:
					bus.send(msg)
				except can.CanError:
					pass
				time.sleep(0.02)
			time.sleep(0.08)
			out = cmd("bcm", 0.3)
			m = re.search(r"park brake = (UNKNOWN|OFF|ON|FAULT)", out)
			note("raw %d → %s" % (raw, exp_state),
			     m is not None and m.group(1) == exp_state,
			     m.group(1) if m else "读不到")

		# ---------- 7. 不破坏既有功能 ----------
		print("\n--- 7 回归：M22 的 PDU 状态仍正常 ---")
		out = cmd("com can1", 0.5)
		note("com can1 仍有 6 条 TX 报文",
		     out.count("pdu=") >= 6, "匹配 %d 行" % out.count("pdu="))
		note("无发送重试卡死（retry=0）",
		     "retry=1" not in out, "出现 retry=1" if "retry=1" in out else "全 0")

	finally:
		cmd("bcm all off", 0.2)
		bus.shutdown()
		ser.close()

	# ---------- 汇总 ----------
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
