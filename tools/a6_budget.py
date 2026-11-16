#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""A6 验收：资源预算（Flash / RAM / 栈水位 / 调度延迟）是否还有余量。

## 为什么要有阈值，而不是"看着不大就行"

"还有 200 KB 空着"听上去很安全，但真正决定能不能上车的不是空闲量，
而是**最坏情况下的余量**。所以这里的每个数字都配一条阈值，超了就 FAIL：

| 项 | 阈值 | 理由 |
|---|---|---|
| Flash（m_text） | ≤ 85% | 留 15% 给下一个功能；A/B 两个槽都要塞得下 |
| SRAM（data+bss+heap+stack） | ≤ 70% | 中断栈与调试期临时缓冲要从剩余里出 |
| 栈水位 | ≤ 60% | 留 40% 给"最深路径还没跑到"的余量（水位只反映这次上电） |
| 单拍 BSW 耗时 | ≤ 5 ms（节拍的 50%） | 超过就说明这一拍挤占了下一拍 |
| SysTick 最坏迟到 | ≤ 1000 µs（节拍的 10%） | 迟到的是"关中断/高优先级 ISR"的时间，直接影响 CAN 收帧 |

## 两种采样窗口，必须分开看

启动阶段有 Flash 擦写与 NvM 读盘，峰值（实测 6.2 ms）**真实但不代表稳态**。
所以脚本先 `mem clear` 清掉启动峰值，静置 3 s 再读 —— 稳态才是长期运行的
真实水平。启动峰值单独打出来当参考，不参与判定。

## 前置

- 板子在跑含 `mem` 命令的 App 固件；
- COM2 串口。

用法：
	python tools/a6_budget.py
	python tools/a6_budget.py --no-board     # 只看静态尺寸（不连板）

@author binbina
"""

import argparse
import os
import re
import subprocess
import sys
import time

try:
	import serial
except ImportError:
	serial = None

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
ELF = os.path.join(ROOT, "build", "nt", "CM4GCC", "App", "App.exe")
LD = os.path.join(ROOT, "app", "platform", "cvm0146", "sdk", "linker",
                  "CVM0146_app_a.ld")
OBJDUMP = r"C:\soft\gcc\10.3.1\bin\arm-none-eabi-objdump.exe"

# 阈值（见文件头表格）
TH_FLASH = 0.85
TH_RAM = 0.70
TH_STACK = 0.60
TH_BSW_US = 5000
TH_LATE_US = 1000

# `mem` 输出解析
RE_RW = re.compile(r"data (\d+) B \+ bss (\d+) B")
RE_STACK = re.compile(r"used (\d+) / (\d+) B")
RE_TICK = re.compile(r"late max (\d+) cyc / (\d+) us \| bsw max (\d+) cyc / (\d+) us")


def parse_ld():
	"""从链接脚本 MEMORY 段取出各区域大小（唯一权威是 .ld）。"""
	txt = open(LD, encoding="utf-8").read()
	body = txt.split("MEMORY", 1)[1].split("}", 1)[0]
	regions = {}
	for m in re.finditer(r"(\w+)\s*\([^)]*\)\s*:\s*ORIGIN\s*=\s*(\w+),\s*LENGTH\s*=\s*(\w+)", body):
		regions[m.group(1)] = int(m.group(3), 16)
	return regions


def parse_sections():
	"""{段名: 字节数}（用 objdump 而不是 size：size 的 bss 会把 heap/stack 混进来）。"""
	out = subprocess.run([OBJDUMP, "-h", ELF], capture_output=True, text=True)
	secs = {}
	for line in out.stdout.splitlines():
		m = re.match(r"\s*\d+\s+(\.\S+)\s+([0-9a-f]{8})", line)
		if m:
			secs[m.group(1)] = int(m.group(2), 16)
	return secs


def shell_read_mem(ser, clear_first):
	"""读一次 `mem`；clear_first 时先清零并静置 3 s（稳态窗口）。"""
	def cmd(text, wait=0.4):
		ser.reset_input_buffer()
		ser.write((text + "\n").encode())
		ser.flush()
		time.sleep(wait)
		return ser.read(65536).decode("utf-8", "replace")

	boot = cmd("mem", 0.5)
	if not clear_first:
		return boot, None

	cmd("mem clear", 0.3)
	time.sleep(3.0)
	steady = cmd("mem", 0.5)
	return boot, steady


def sample(text):
	"""把一段 `mem` 输出解析成 dict；缺字段返回 None。"""
	if text is None:
		return None
	rw = RE_RW.search(text)
	st = RE_STACK.search(text)
	tk = RE_TICK.search(text)
	if not (rw and st and tk):
		return None
	return {
		"data": int(rw.group(1)),
		"bss": int(rw.group(2)),
		"stack_used": int(st.group(1)),
		"stack_total": int(st.group(2)),
		"late_cyc": int(tk.group(1)),
		"late_us": int(tk.group(2)),
		"bsw_cyc": int(tk.group(3)),
		"bsw_us": int(tk.group(4)),
	}


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--no-board", action="store_true", help="只看静态尺寸")
	a = ap.parse_args()

	for p in (ELF, LD):
		if not os.path.isfile(p):
			print("找不到 %s（先 build.bat --app=App）" % p)
			return 1

	regions = parse_ld()
	secs = parse_sections()

	flash_cap = regions.get("m_text", 0) + regions.get("m_interrupts", 0)
	ram_cap = regions.get("m_data", 0) + regions.get("m_data_2", 0)
	flash_used = secs.get(".text", 0) + secs.get(".interrupts", 0)
	ram_static = (secs.get(".interrupts_ram", 0) + secs.get(".data", 0) +
	              secs.get(".bss", 0) + secs.get(".heap", 0) + secs.get(".stack", 0))

	results = []

	def note(name, ok, detail):
		results.append((name, ok, detail))
		print("  [%s] %-26s %s" % ("PASS" if ok else "FAIL", name, detail))

	print("=" * 78)
	print("A6 资源预算")
	print("=" * 78)

	print("\n--- 1 静态尺寸（.ld + objdump）---")
	print("  flash : %7d / %7d B  (%.1f%%)" % (flash_used, flash_cap,
	                                          100.0 * flash_used / flash_cap))
	print("  ram   : %7d / %7d B  (%.1f%%)  = ram_vec %d + data %d + bss %d + heap %d + stack %d"
	      % (ram_static, ram_cap, 100.0 * ram_static / ram_cap,
	         secs.get(".interrupts_ram", 0), secs.get(".data", 0),
	         secs.get(".bss", 0), secs.get(".heap", 0), secs.get(".stack", 0)))
	note("Flash ≤ %.0f%%" % (TH_FLASH * 100), flash_used <= flash_cap * TH_FLASH,
	     "余 %d B" % (flash_cap - flash_used))
	note("SRAM ≤ %.0f%%" % (TH_RAM * 100), ram_static <= ram_cap * TH_RAM,
	     "余 %d B" % (ram_cap - ram_static))

	if a.no_board:
		print("\n（--no-board：跳过栈水位与调度延迟）")
		return summary(results)

	if serial is None:
		print("需要 pyserial：pip install pyserial")
		return 1

	ser = serial.Serial(a.port, 115200, timeout=0.2)
	try:
		time.sleep(0.3)
		boot, steady = shell_read_mem(ser, clear_first=True)
	finally:
		ser.close()

	s0 = sample(boot)
	s = sample(steady)
	if s is None:
		print("  [FAIL] 读不到 `mem` 输出（固件里没有 mem 命令？）")
		return 1

	print("\n--- 2 栈水位（本次上电以来最深）---")
	print("  stack : %d / %d B  (%.1f%%)" % (s["stack_used"], s["stack_total"],
	                                        100.0 * s["stack_used"] / s["stack_total"]))
	note("栈水位 ≤ %.0f%%" % (TH_STACK * 100),
	     s["stack_used"] <= s["stack_total"] * TH_STACK,
	     "余 %d B" % (s["stack_total"] - s["stack_used"]))

	print("\n--- 3 调度延迟（清峰值后静置 3 s 的稳态）---")
	print("  steady: late max %d cyc / %d us | bsw max %d cyc / %d us"
	      % (s["late_cyc"], s["late_us"], s["bsw_cyc"], s["bsw_us"]))
	if s0 is not None:
		print("  before: late max %d cyc / %d us | bsw max %d cyc / %d us"
		      "   （上一次清零以来的最大值，仅供参考，不判定）"
		      % (s0["late_cyc"], s0["late_us"], s0["bsw_cyc"], s0["bsw_us"]))
	# 迟到量以周期为准：120 MHz 下 1 us = 120 cyc，整数微秒会把几十周期舍成 0
	note("稳态迟到 ≤ %d us" % TH_LATE_US, s["late_us"] <= TH_LATE_US,
	     "%d cyc ≈ %d us" % (s["late_cyc"], s["late_us"]))
	note("稳态单拍 ≤ %d us" % TH_BSW_US, s["bsw_us"] <= TH_BSW_US,
	     "%d cyc ≈ %d us" % (s["bsw_cyc"], s["bsw_us"]))

	# 交叉检查：`mem` 报的 data/bss 必须与 ELF 一致，否则说明固件与 .exe 不是同一份
	note("固件与 ELF 同一版本（data/bss 对得上）",
	     s["data"] == secs.get(".data", -1) and s["bss"] == secs.get(".bss", -1),
	     "固件 data=%d bss=%d / ELF data=%d bss=%d"
	     % (s["data"], s["bss"], secs.get(".data", -1), secs.get(".bss", -1)))

	return summary(results)


def summary(results):
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
