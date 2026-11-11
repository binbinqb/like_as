#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M5 验收：CAN bus-off 检测 + 故障快照持久化。

验收判据：
	1. 启动横幅正常，存储块初始化没有 TIMEOUT；
	2. `!b` 初始为空 —— 上一轮验收留下的记录已被 `!B` 清掉；
	3. **bus-off 中断已使能**：`!e` 读回 `BOFFMSK=1`
	   （这是"检测机制就绪"的唯一硬证据，光看代码不算）；
	4. `!e` 能读出 `TEC/REC/FLTCONF`，寄存器通道是通的；
	5. **故障注入**：`!i` 后 `!b` 出现 1 条 `C00100`（U0001），
	   通道 0、次数 1、`err=0x04`（ACK 错）、`flt=2`（bus-off）；
	6. **次数累加**：再注入一次，同一条记录 `cnt` 变成 2（不新增槽位）；
	7. **掉电保持**：复位后记录仍在，且 `cnt` / `firstBoot` 不变；
	8. **清除**：`!B` 后 `!b` 为空；
	9. **清除也落盘**：复位后仍为空；
	10. 心跳照常（记录链路没把主循环卡死）；
	11. CAN 报文仍在发（Kvaser 收到 0x123）—— 新加的中断没破坏收发。

## 为什么用故障注入而不是真造一次 bus-off

这是个刻意做的决定，不是省事：

**单节点实验室造不出 bus-off，是 CAN 协议决定的：**

1. 最直觉的路径"对端不应答"只能把 TEC 推到 **128**（error passive）。
   ISO 11898-1 §7.1.3 规定 **error passive 状态下 ACK 错误不再累加 TEC**，
   于是 TEC 死死卡在 128，永远到不了 256 的 bus-off 门槛。
   实测：断开 Kvaser（无节点应答）跑 60 秒，`TEC=128` 一动不动。
2. 想越过 128 只能靠位错误 / 格式错误，需要对端用**同一 ID、不同数据**
   精确地同时发送。实测用 Kvaser 连发 1.7 万帧去撞，TEC 只涨到 1~7：
   要么对端赢仲裁（板子根本没发出去），要么板子发完了对端才撞上。

所以真 bus-off 的触发条件交给硬件（`BOFFMSK` + `BOFFINT` 已在驱动层配好，
本脚本第 3 项就验这个），**记录链路**用注入验证。
这比"造不出就不验"实在 —— 链路上每一个环节（分配槽位、累加、落盘、掉电保持）
都是本工程写的代码，都值得验。

真要做物理 bus-off，把 CAN_H 对地短接几秒即可（短路制造持续显性位 → 位错误），
需要动硬件，不适合放进自动脚本。

前置：
	- 板子在跑 H:/as 的 M5 固件；
	- 只需要 COM2；加 `--with-can` 才需要 Kvaser ch0。

用法：
	python tools/m5_check.py                # 全量验收（约 12 s）
	python tools/m5_check.py --with-can     # 额外验证报文收发未受影响
	python tools/m5_check.py --no-reset     # 不复位（跳过掉电保持项）

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
PORT = "COM2"
BAUD = 115200

# 故障码：U0001 高速 CAN 通信总线（3 字节 = 0xC00100）
DTC_U0001 = "C00100"
# 错误位图：bit2 = ACK 错
ERR_ACK = 0x04

RE_BOOT = re.compile(r"^\s*nvm\s+:\s+DFlash\s+([0-9]+)x([0-9]+)\s*KB.*boot\s+#(\d+)")
RE_TIMEOUT = re.compile(r"\[nvm\]\s+TIMEOUT")
RE_HB = re.compile(r"\[\s*(\d+) ms\] alive #(\d+)")
RE_REG = re.compile(
	r"\[canreg\]\s+TEC=(\d+)\s+REC=(\d+)\s+FLTCONF=(\d+)\s+"
	r"BOFFINT=(\d+)\s+BOFFMSK=(\d+)\s+ERRMSK=(\d+)")
RE_DTC_HEAD = re.compile(r"\[dtc\]\s+(\d+)\s+条已记录")
# 格式：`[dtc] 0: C00100 ch=0 st=0x8f cnt=2 boot #92..#92 err=0x04 flt=2`
# `st=` 是 M6 接 Dem 后新增的 UDS 状态字节
RE_DTC_ENTRY = re.compile(
	r"\[dtc\]\s+(\d+):\s+([0-9A-F]{6})\s+ch=(\d+)\s+st=0x([0-9a-f]{2})\s+"
	r"cnt=(\d+)\s+boot\s+#(\d+)\.\.#(\d+)\s+err=0x([0-9a-f]{2})\s+flt=(\d+)")


def reset_run():
	"""J-Link 复位并运行。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


def read_for(ser, seconds):
	t_end = time.time() + seconds
	buf = ""
	while time.time() < t_end:
		buf += ser.read(8192).decode("utf-8", "replace")
	return buf


def boot_and_read(ser, seconds=1.6):
	ser.reset_input_buffer()
	p = reset_run()
	if p.returncode != 0:
		raise SystemExit("[FAIL] J-Link 复位失败")
	return read_for(ser, seconds)


def send_cmd(ser, cmd, seconds=0.8):
	ser.reset_input_buffer()
	ser.write(cmd.encode())
	return read_for(ser, seconds)


def parse_boot(text):
	for line in text.splitlines():
		m = RE_BOOT.search(line)
		if m:
			return int(m.group(3))
	return None


def parse_regs(text):
	m = RE_REG.search(text)
	if not m:
		return None
	return {
		"tec": int(m.group(1)), "rec": int(m.group(2)),
		"fltconf": int(m.group(3)), "boffint": int(m.group(4)),
		"boffmsk": int(m.group(5)), "errmsk": int(m.group(6)),
	}


def parse_dtc(text):
	"""返回 (记录条数, [条目字典...])。"""
	n = None
	m = RE_DTC_HEAD.search(text)
	if m:
		n = int(m.group(1))

	entries = []
	for line in text.splitlines():
		m = RE_DTC_ENTRY.search(line)
		if m:
			entries.append({
				"idx": int(m.group(1)), "code": m.group(2),
				"ch": int(m.group(3)), "st": int(m.group(4), 16),
				"cnt": int(m.group(5)),
				"first_boot": int(m.group(6)), "last_boot": int(m.group(7)),
				"err": int(m.group(8), 16), "flt": int(m.group(9)),
			})
	return n, entries


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--no-reset", action="store_true",
					help="不复位（跳过掉电保持类判据）")
	ap.add_argument("--with-can", action="store_true",
					help="额外用 Kvaser 验证报文收发未受影响")
	args = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	print("=" * 68)
	print(" M5 验收：CAN bus-off 检测 + 故障快照持久化")
	print("=" * 68)

	ser = serial.Serial(args.port, BAUD, timeout=0.2)

	# ---------- 1) 启动 + 清空 ----------
	if args.no_reset:
		ser.reset_input_buffer()
		boot = read_for(ser, 1.0)
	else:
		boot = boot_and_read(ser, 1.8)

	boot_cnt = parse_boot(boot)
	note("启动横幅: 存储已初始化", boot_cnt is not None,
		 "boot #%s" % boot_cnt if boot_cnt else "(未找到)")
	note("启动横幅: 没有 nvm TIMEOUT", RE_TIMEOUT.search(boot) is None, "")

	# 上一轮可能留了记录，先清干净再开始
	send_cmd(ser, "!B", 0.6)
	d = send_cmd(ser, "!b", 0.6)
	n0, _ = parse_dtc(d)
	note("基线: 清除后故障表为空", n0 == 0, "条数=%s" % n0)

	# ---------- 2) 检测机制是否就绪 ----------
	r = send_cmd(ser, "!e", 0.6)
	regs = parse_regs(r)
	note("寄存器: !e 可读", regs is not None,
		 str(regs) if regs else "(解析失败)")
	if regs:
		note("bus-off 中断已使能 (BOFFMSK=1)", regs["boffmsk"] == 1,
			 "BOFFMSK=%d BOFFINT=%d" % (regs["boffmsk"], regs["boffint"]))
		note("错误中断未开 (ERRMSK=0，避免中断风暴)", regs["errmsk"] == 0,
			 "ERRMSK=%d" % regs["errmsk"])
	else:
		note("bus-off 中断已使能 (BOFFMSK=1)", False, "寄存器不可读")
		note("错误中断未开 (ERRMSK=0，避免中断风暴)", False, "寄存器不可读")

	# ---------- 3) 故障注入 ----------
	out = send_cmd(ser, "!i", 0.5)
	note("注入: 命令被接受", "injected" in out, out.strip().splitlines()[0][:60]
		 if out.strip() else "(无输出)")

	d = send_cmd(ser, "!b", 0.6)
	n1, e1 = parse_dtc(d)
	note("注入: 故障表有 1 条", n1 == 1 and len(e1) == 1, "条数=%s" % n1)

	if e1:
		e = e1[0]
		note("注入: DTC = U0001 (C00100)", e["code"] == DTC_U0001, e["code"])
		note("注入: 通道 = 0", e["ch"] == 0, "ch=%d" % e["ch"])
		note("注入: ACK 错误位已置", (e["err"] & ERR_ACK) != 0,
			 "err=0x%02x" % e["err"])
		note("注入: FLTCONF = 2 (bus-off)", e["flt"] == 2, "flt=%d" % e["flt"])
		note("注入: 次数 = 1", e["cnt"] == 1, "cnt=%d" % e["cnt"])
		if boot_cnt is not None:
			note("注入: 首次启动序号 = 本次 boot",
				 e["first_boot"] == (boot_cnt & 0xFFFF),
				 "记录 #%d / 实际 #%d" % (e["first_boot"], boot_cnt & 0xFFFF))
	else:
		for name in ("注入: DTC = U0001 (C00100)", "注入: 通道 = 0",
					 "注入: ACK 错误位已置", "注入: FLTCONF = 2 (bus-off)",
					 "注入: 次数 = 1"):
			note(name, False, "(无记录)")

	# ---------- 4) 累加而不是新增 ----------
	send_cmd(ser, "!i", 0.5)
	d = send_cmd(ser, "!b", 0.6)
	n2, e2 = parse_dtc(d)
	note("累加: 仍然只有 1 条（占用同一槽位）", n2 == 1, "条数=%s" % n2)
	note("累加: 次数变成 2", bool(e2) and e2[0]["cnt"] == 2,
		 "cnt=%d" % e2[0]["cnt"] if e2 else "(无记录)")

	# ---------- 5) 掉电保持 ----------
	if not args.no_reset:
		time.sleep(0.6)          # 留一次 10 ms 节拍让脏数据落盘
		boot2 = boot_and_read(ser, 1.6)
		cnt2 = parse_boot(boot2)
		note("复位: 启动计数 +1", (boot_cnt is not None) and (cnt2 == boot_cnt + 1),
			 "#%s -> #%s" % (boot_cnt, cnt2))

		d = send_cmd(ser, "!b", 0.6)
		n3, e3 = parse_dtc(d)
		note("掉电保持: 复位后记录仍在", n3 == 1, "条数=%s" % n3)
		note("掉电保持: 次数没被清零", bool(e3) and e3[0]["cnt"] == 2,
			 "cnt=%d" % e3[0]["cnt"] if e3 else "(无记录)")
		if e3:
			note("掉电保持: 首次启动序号未变",
				 e3[0]["first_boot"] == (boot_cnt & 0xFFFF),
				 "记录 #%d" % e3[0]["first_boot"])

	# ---------- 6) 清除 + 清除的持久化 ----------
	out = send_cmd(ser, "!B", 0.6)
	note("清除: 命令被接受", "cleared" in out, "")
	d = send_cmd(ser, "!b", 0.6)
	n4, _ = parse_dtc(d)
	note("清除: 故障表为空", n4 == 0, "条数=%s" % n4)

	if not args.no_reset:
		time.sleep(0.6)
		boot_and_read(ser, 1.4)
		d = send_cmd(ser, "!b", 0.6)
		n5, _ = parse_dtc(d)
		note("清除已落盘: 复位后仍为空", n5 == 0, "条数=%s" % n5)

	# ---------- 7) 主循环没被卡 ----------
	hb = read_for(ser, 2.2)
	beats = [int(m.group(2)) for m in RE_HB.finditer(hb)]
	note("主循环: 心跳还在走", len(beats) >= 2,
		 "2 s 内 %d 拍" % len(beats))

	# ---------- 8) CAN 收发未受影响（可选） ----------
	if args.with_can:
		try:
			import can
			bus = can.Bus(interface="kvaser", channel=0, bitrate=500000)
			ser.reset_input_buffer()
			t_end = time.time() + 2.0
			seen = []
			while time.time() < t_end:
				m = bus.recv(0.1)
				if m:
					seen.append(m.arbitration_id)
			bus.shutdown()
			note("CAN: 仍在发 0x123", 0x123 in seen,
				 "2 s 内收到 %d 帧，ID=%s" % (len(seen), sorted(set(seen))[:4]))
		except Exception as exc:                 # noqa: BLE001
			note("CAN: 仍在发 0x123", False, "Kvaser 不可用：%s" % exc)

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
	print("=" * 68)
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
