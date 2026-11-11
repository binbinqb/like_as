#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M0 验收：启动横幅 + printf 自检 + 心跳节拍 + 串口回显。

为什么要有这个脚本：
	M0 的每一项（链接脚本、ECC 启动、SysTick 时钟、UART 时钟源、格式化层）
	出问题时都表现为"串口上看到的东西不对"，肉眼很难区分是哪一层。
	这里把**每一项的期望输出**写成断言，一次跑完给出判定表，
	以后改平台层就能立刻知道有没有把已验证的东西弄坏。

验收判据（对应 README 的 M0 表格）：
	1. 启动横幅 —— 向量表、.data/.bss 搬运、SRAM ECC 初始化、时钟全部正常；
	2. printf 自检 —— 宽度/对齐/补零/精度/符号/INT32_MIN/字符串截断；
	3. 心跳 —— 相邻两条间隔 1000 ms（±30），序号连续递增；
	4. 回显 —— 发送的字节原样返回（含 52 字符长串）。

⚠ 心跳和回显会**打在同一行**：回显不带换行，紧接着的心跳直接接在后面。
	所以校验回显时必须在**原始字节流**里找子串，不能按行切分后再找
	（按行过滤 `alive #` 会把回显一起丢掉，制造假阴性——第一版就踩了）。

用法：
	python tools/m0_check.py                 # 复位 + 验收（假定已烧好）
	python tools/m0_check.py --flash         # 先烧再验收
	python tools/m0_check.py --port COM5     # 换串口
	python tools/m0_check.py --no-reset      # 不复位，直接抓当前运行

@author binbina
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

try:
	import serial
except ImportError:
	raise SystemExit("需要 pyserial：pip install pyserial")

JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"

# 启动横幅必须出现的行（顺序无关，逐条子串匹配）
BANNER = [
	"AS / CVM0146  bring-up",   # 不绑里程碑号：M1 起横幅会变成 (M1)
	"core  : PLL 120 MHz",
	"uart  : UART2 115200 8N1  (PC: COM2)",
]

# printf 自检：每条是 (名称, 期望出现在输出里的片段)
# 片段按 `|` 分段写，命中即认为该字段排布正确。
FMT_CASES = [
	("宽度·右对齐", "|    42|"),
	("宽度·左对齐", "|42    |"),
	("补零·十进制", "|000042|"),
	("补零·十六进制", "|0000beef|"),
	("前缀·小写", "|0xbeef|"),
	("前缀·大写", "|0XBEEF|"),
	("负数·右对齐", "|    -7|"),
	("正号标志", "|+7|"),
	("空格标志", "| 7|"),
	("精度·最少位数", "|042|"),
	("精度+宽度", "|     042|"),
	("精度0·值为0", "prec 0 of 0    ||"),
	("INT32_MIN", "|-2147483648|"),
	("字符串·左对齐", "|abc     |"),
	("字符串·截断", "|abc|"),
	("字符", "|X|"),
	("百分号转义", "|100%|"),
]

# 回显用例：短串 + 长串（长串用来暴露 RX FIFO 溢出/丢字符）
ECHO_CASES = [
	"hello",
	"0123456789ABCDEF",
	"AS-echo-test-0123456789-abcdefghijklmnopqrstuvwxyz",
]

RE_HB = re.compile(rb"\[\s*(\d+) ms\] alive #(\d+)")


def reset_run():
	"""通过 J-Link 复位并运行（不碰 Flash，不需要 FLM）。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


def read_for(ser, seconds):
	"""在 seconds 秒内尽量多地收字节。"""
	buf = bytearray()
	t0 = time.time()
	while time.time() - t0 < seconds:
		buf += ser.read(8192)
	return bytes(buf)


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--baud", type=int, default=115200)
	ap.add_argument("--flash", action="store_true", help="先烧写再验收")
	ap.add_argument("--no-reset", action="store_true", help="不复位，直接抓当前输出")
	ap.add_argument("--seconds", type=float, default=3.0, help="抓取时长")
	a = ap.parse_args()

	if a.flash:
		here = os.path.dirname(os.path.abspath(__file__))
		rc = subprocess.run([sys.executable, os.path.join(here, "flash.py")],
							stdin=subprocess.DEVNULL).returncode
		if rc != 0:
			raise SystemExit("烧写失败，先解决问题再验收")

	# 先开串口再复位：否则启动横幅在 open() 之前就打完了（实测会整段丢失）
	ser = serial.Serial(a.port, a.baud, timeout=0.2)
	ser.reset_input_buffer()

	if not a.no_reset:
		p = reset_run()
		if p.returncode != 0:
			print("[FAIL] J-Link 复位失败：")
			print(p.stdout[-800:] or p.stderr[-800:])
			return 1

	raw = read_for(ser, a.seconds)
	text = raw.decode("utf-8", "replace")

	results = []

	# 1) 启动横幅
	for line in BANNER:
		results.append(("横幅: " + line.strip()[:38], line in text))

	# 2) printf 自检
	for name, frag in FMT_CASES:
		results.append(("printf: " + name, frag in text))

	# 3) 心跳：间隔与序号
	# 串口在 open() 时就开始了接收，而 J-Link 复位还要 ~0.5 s —— 这段时间里板子
	# 按"复位前"的计时继续发心跳（ms 可能已到几万）。这些旧行会紧挨在复位后的
	# `alive #1` 前面，直接解析就得到负的时间差和"序号不连续"。
	# 所以心跳只取**最后一次横幅之后**的部分。
	hb_raw = raw
	_mark = hb_raw.rfind(b"bring-up")
	if _mark > 0:
		hb_raw = hb_raw[_mark:]
	hbs = RE_HB.findall(hb_raw)
	if len(hbs) < 2:
		results.append(("心跳: 至少两条", False))
	else:
		results.append(("心跳: 至少两条 (%d 条)" % len(hbs), True))
		ms = [int(m) for m, _ in hbs]
		seq = [int(s) for _, s in hbs]
		deltas = [b - a2 for a2, b in zip(ms, ms[1:])]
		bad_d = [d for d in deltas if abs(d - 1000) > 30]
		results.append(("心跳: 周期 1000 ms (实测 %s)" % (deltas[:4],), not bad_d))
		bad_s = [i for i in range(1, len(seq)) if seq[i] != seq[i - 1] + 1]
		results.append(("心跳: 序号连续递增", not bad_s))

	# 4) 回显（在原始字节流里找，不按行切分）
	for case in ECHO_CASES:
		ser.write(case.encode())
		time.sleep(0.4)
		got = read_for(ser, 0.3)
		results.append(("回显: %s" % (case[:28] + ("..." if len(case) > 28 else "")),
						case.encode() in got))

	ser.close()

	# ---- 判定表 ----
	w = max(len(n) for n, _ in results) + 2
	print()
	print("=" * (w + 14))
	print("  M0 验收 —— %s @ %d" % (a.port, a.baud))
	print("=" * (w + 14))
	fail = 0
	for name, ok in results:
		print("  %-*s %s" % (w, name, "[ OK ]" if ok else "[FAIL]"))
		if not ok:
			fail += 1
	print("=" * (w + 14))
	print("  %d 项，通过 %d，失败 %d" % (len(results), len(results) - fail, fail))
	print("=" * (w + 14))

	if fail:
		print("\n---- 原始输出（前 2500 字节）----")
		print(text[:2500])
		return 1
	return 0


if __name__ == "__main__":
	sys.exit(main())
