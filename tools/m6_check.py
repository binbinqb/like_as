#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""M6 验收：Dcm 0x19 读故障码 / 0x14 清故障码。

验收判据：
	1. **服务被支持**：`19 02 FF` 与 `14 FF FF FF` 都不是 NRC 0x11(serviceNotSupported)；
	2. `19 01 FF` 空表时返回 `59 01 8F 01 00 00`（0 条，UDS 格式标识符=1）；
	3. `19 0A` 空表时返回 `59 0A 8F`（只有头，没有 DTC）；
	4. **注入后能读到**：`19 02 FF` → `59 02 8F C0 01 00 8F`
	   （U0001、状态 0x8F = TF|TFTOC|PDTC|CDTC|WIR）；
	5. `19 01 FF` 数量变 1；`19 0A` 也列出这条；
	6. **状态掩码真的在过滤**：`19 02 10`（只查 TNCSLC，本工程不置）读不到，
	   `19 02 01`（查 TF，已置）读得到 —— 掩码不生效的话两者都会返回；
	7. **0x14 清除**：`14 FF FF FF` → `54`（中间会有 NRC 0x78，由 ISO-TP 层吞掉）；
	8. 清完 `19 02 FF` 变成空表；
	9. **串口与 UDS 一致**：`!b` 显示的条数与 0x19 读到的条数相同
	   （两者走同一个 Dem 后端，不一致就说明有两条数据通路）；
	10. **掉电保持**：注入 → 复位 → 0x19 仍能读到；
	11. **不破坏原有服务**：`10 03`、`22 F1 90` 仍然正常。

## 两个容易踩的点

**① 0x14 会先回 NRC 0x78**

`Dcm_DspClearDTC` 在 `USE_NVM` 下返回 `DCM_E_RESPONSE_PENDING`，
要等 NvM 把 DTC 块写完才给最终响应。测试脚本必须把 `7F 14 78` 当成
"还在处理"而不是"失败" —— 否则第 2 条命令会读到上一条的尾巴，
现象是"命令串位"，比不响应还难查。
`isotp_lite.Isotp.request()` 已经内置这段处理。

**② 状态可用掩码是 0x8F，不是 0xFF**

`DEM_CFG_STATUS_AVAILABILITY_MASK` 只声明本工程真的会置的位。
谎报 0xFF 会让测试仪等一个永远不会来的 testNotCompletedSinceLastClear。

前置：
	- 板子在跑 M6 固件；
	- Kvaser ch0 接 CAN0（500 kbps）；
	- COM2 串口。

用法：
	python tools/m6_check.py
	python tools/m6_check.py --no-reset     # 不复位（跳过掉电保持项）

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
	'!b': 'dtc dump',
	'!i': 'dtc inject',
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

JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"
PORT = "COM2"
BAUD = 115200

# DTC：U0001 = C0 01 00（3 字节，高位在前）
DTC_U0001 = bytes([0xC0, 0x01, 0x00])
# 状态可用掩码：TF|TFTOC|PDTC|CDTC|WIR
AVAIL_MASK = 0x8F
# 首次失败的 UDS 状态字节
STATUS_FAILED = 0x8F

# 注意不要写 `^`：这里是搜索**整段**文本而不是逐行，
# 不加 re.MULTILINE 时 `\^` 只匹配文本开头，横幅永远匹配不到。
RE_BOOT = re.compile(r"nvm\s+:\s+DFlash\s+[0-9]+x[0-9]+\s*KB.*boot\s+#(\d+)")
RE_DTC_HEAD = re.compile(r"\[dtc\]\s+(\d+)\s+条已记录")


def reset_run():
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


def send_cmd(ser, cmd, seconds=0.7):
	ser.reset_input_buffer()
	ser.write(xlate(cmd).encode())
	return read_for(ser, seconds)


def parse_serial_dtc_count(text):
	m = RE_DTC_HEAD.search(text)
	return int(m.group(1)) if m else None


def parse_dtc_payload(r):
	"""从 `59 0x <avail> {DTC[3] status}*` 里取出 [(dtc_bytes, status), ...]。"""
	if (r is None) or (len(r) < 3):
		return []
	out = []
	i = 3
	while i + 3 < len(r):
		out.append((bytes(r[i:i + 3]), r[i + 3]))
		i += 4
	return out


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default=PORT)
	ap.add_argument("--channel", type=int, default=0)
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	results = []

	def note(name, ok, detail=""):
		results.append((name, ok, detail))

	print("=" * 72)
	print(" M6 验收：Dcm 0x19 读故障码 / 0x14 清故障码")
	print("=" * 72)

	ser = serial.Serial(a.port, BAUD, timeout=0.2)
	ser.reset_input_buffer()
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)
	tp = Isotp(bus)

	# ---------- 复位 + 清干净 ----------
	if not a.no_reset:
		# 复位前必须清缓冲：上一轮残留的日志会让"启动横幅"那一条误判
		ser.reset_input_buffer()
		p = reset_run()
		if p.returncode != 0:
			raise SystemExit("[FAIL] J-Link 复位失败")

	boot = read_for(ser, 1.6)
	m = RE_BOOT.search(boot)
	note("启动: 存储已初始化", m is not None,
		 "boot #%s" % (m.group(1) if m else "?"))

	# 先把上一轮可能留下的 DTC 清掉（0x14 走 pending，isotp 层会等）
	r = tp.request([0x14, 0xFF, 0xFF, 0xFF], timeout=3.0)
	note("0x14: 空表清除也返回 54", r == b"\x54",
		 r.hex(" ") if r else "(无响应)")

	# ---------- 1) 服务被支持 ----------
	r = tp.request([0x19, 0x02, 0xFF])
	note("0x19: 服务被支持（非 NRC 0x11）",
		 (r is not None) and not (r[0] == 0x7F and r[2] == 0x11),
		 r.hex(" ") if r else "(无响应)")

	r = tp.request([0x14, 0xFF, 0xFF, 0xFF], timeout=3.0)
	note("0x14: 服务被支持（非 NRC 0x11）",
		 (r is not None) and not (r[0] == 0x7F and r[2] == 0x11),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 2) 空表 ----------
	r = tp.request([0x19, 0x02, 0xFF])
	d = parse_dtc_payload(r)
	note("空表: 19 02 只有 3 字节头", (r is not None) and (len(r) == 3),
		 r.hex(" ") if r else "(无响应)")
	note("空表: 可用掩码 = 0x%02X" % AVAIL_MASK,
		 (r is not None) and (r[1] == 0x02) and (r[2] == AVAIL_MASK),
		 "实际 0x%02X" % r[2] if (r is not None and len(r) > 2) else "?")

	r = tp.request([0x19, 0x01, 0xFF])
	note("空表: 19 01 数量 = 0",
		 (r is not None) and (len(r) == 6) and (r[:2] == b"\x59\x01") and
		 (r[3] == 0x01) and (r[4] == 0x00) and (r[5] == 0x00),
		 r.hex(" ") if r else "(无响应)")

	r = tp.request([0x19, 0x0A])
	note("空表: 19 0A 只有头", (r is not None) and (len(r) == 3),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 3) 注入并读取 ----------
	send_cmd(ser, "!i", 0.4)

	r = tp.request([0x19, 0x02, 0xFF])
	d = parse_dtc_payload(r)
	note("注入后: 读到 1 条", len(d) == 1, "%d 条" % len(d))
	if d:
		note("注入后: DTC = U0001 (C0 01 00)", d[0][0] == DTC_U0001,
			 d[0][0].hex(" ").upper())
		note("注入后: 状态 = 0x8F（TF|TFTOC|PDTC|CDTC|WIR）",
			 d[0][1] == STATUS_FAILED, "st=0x%02X" % d[0][1])
	else:
		note("注入后: DTC = U0001 (C0 01 00)", False, "(无 DTC)")
		note("注入后: 状态 = 0x8F（TF|TFTOC|PDTC|CDTC|WIR）", False, "(无 DTC)")

	r = tp.request([0x19, 0x01, 0xFF])
	note("注入后: 19 01 数量 = 1",
		 (r is not None) and (len(r) == 6) and (r[4] == 0x00) and (r[5] == 0x01),
		 r.hex(" ") if r else "(无响应)")

	r = tp.request([0x19, 0x0A])
	note("注入后: 19 0A 列出该 DTC",
		 (r is not None) and (len(r) == 7) and (bytes(r[3:6]) == DTC_U0001),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 4) 状态掩码过滤 ----------
	r = tp.request([0x19, 0x02, 0x01])       # 只查 TF，已置
	note("掩码: 19 02 01（查 TF）读得到",
		 (r is not None) and (len(r) == 7),
		 r.hex(" ") if r else "(无响应)")

	r = tp.request([0x19, 0x02, 0x10])       # 只查 TNCSLC，本工程不置
	note("掩码: 19 02 10（查 TNCSLC）读不到",
		 (r is not None) and (len(r) == 3),
		 r.hex(" ") if r else "(无响应)")

	# ---------- 5) 串口与 UDS 一致 ----------
	ser_txt = send_cmd(ser, "!b", 0.6)
	ser_cnt = parse_serial_dtc_count(ser_txt)
	r = tp.request([0x19, 0x01, 0xFF])
	uds_cnt = r[5] if (r is not None and len(r) == 6) else None
	note("一致性: 串口 !b 条数 == 0x19 条数",
		 (ser_cnt is not None) and (uds_cnt is not None) and (ser_cnt == uds_cnt),
		 "串口=%s / UDS=%s" % (ser_cnt, uds_cnt))

	# ---------- 6) 0x14 清除 ----------
	r = tp.request([0x14, 0xFF, 0xFF, 0xFF], timeout=3.0)
	note("0x14: 清除返回 54", r == b"\x54", r.hex(" ") if r else "(无响应)")

	r = tp.request([0x19, 0x02, 0xFF])
	note("清除后: 19 02 空表", (r is not None) and (len(r) == 3),
		 r.hex(" ") if r else "(无响应)")

	ser_txt = send_cmd(ser, "!b", 0.6)
	note("清除后: 串口 !b 也为空", parse_serial_dtc_count(ser_txt) == 0,
		 "条数=%s" % parse_serial_dtc_count(ser_txt))

	# ---------- 7) 掉电保持 ----------
	if not a.no_reset:
		send_cmd(ser, "!i", 0.4)
		time.sleep(0.6)               # 留一拍让 Dem 落盘
		ser.reset_input_buffer()
		reset_run()
		read_for(ser, 1.6)

		r = tp.request([0x19, 0x02, 0xFF])
		d = parse_dtc_payload(r)
		note("掉电保持: 复位后 0x19 仍读到",
			 len(d) == 1 and d[0][0] == DTC_U0001,
			 r.hex(" ") if r else "(无响应)")

	# ---------- 8) 不破坏原有服务 ----------
	r = tp.request([0x10, 0x03])
	note("回归: 10 03 仍正常", (r is not None) and (r[:2] == b"\x50\x03"),
		 r.hex(" ") if r else "(无响应)")

	r = tp.request([0x22, 0xF1, 0x90])
	note("回归: 22 F1 90 仍正常（多帧）",
		 (r is not None) and (r[:3] == b"\x62\xF1\x90"),
		 "%d 字节" % len(r) if r else "(无响应)")

	r = tp.request([0x3E, 0x00])
	note("回归: 3E 00 仍正常", (r is not None) and (r[:2] == b"\x7E\x00"),
		 r.hex(" ") if r else "(无响应)")

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
