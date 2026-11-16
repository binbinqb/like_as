#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""A1 运行期判据：实测 S3Server 超时，反推 BSW 主函数的真实调用频率。

静态检查（`tools/a1_sched_check.py`）只能证明"代码里没有重复调用"，
不能证明"运行时真的每拍一次"（比如调度表的 `numOfMain` 算错、
或者 `EcuM_BswService()` 被调两次，静态都看不出来）。本脚本补这一半。

原理
----
`Dcm_Cfg.c:764` 配的 S3Server = 5000 ms，而 Dcm 的定时器是
**"每次 MainFunction 递减一次"**（不是读时钟），按
`DCM_MAIN_FUNCTION_PERIOD = 10 ms` 折算成 500 拍。

	主函数每 10 ms 跑 1 次 → 500 × 10 ms = **5.0 s**
	主函数每 10 ms 跑 2 次 → 250 × 10 ms = **2.5 s**

所以"进扩展会话后多久掉回默认会话"这一个数字，就能反推调用频率。
这是纯外部观测：不改固件、不加计数器、不需要调试器。

判定
----
	4.5 ~ 5.5 s（±0.5 s，覆盖 10 ms 节拍与串口延迟）  PASS  每拍 1 次
	2.2 ~ 2.8 s                                      FAIL  每拍 2 次（A1 回归）
	其它                                             FAIL  节拍或配置异常

用法
----
	python tools/a1_s3_check.py                 # J-Link 复位后测（推荐）
	python tools/a1_s3_check.py --no-reset      # 测当前正在跑的固件
	python tools/a1_s3_check.py --channel 0 --port COM2

@author binbina
"""

import argparse
import os
import subprocess
import sys
import tempfile
import time

try:
	import can
except ImportError:
	raise SystemExit("需要 python-can：pip install python-can")

try:
	import serial
except ImportError:
	raise SystemExit("需要 pyserial：pip install pyserial")

JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"

from isotp_lite import Isotp

REQ_ID = 0x7E0
RES_ID = 0x7E8

# S3Server 的配置值（ms），与 Dcm_Cfg.c:764 保持一致
S3_MS = 5000
# 判定窗口（ms）
WIN_OK = (4500, 5500)
WIN_DOUBLE = (2200, 2800)


def reset_run():
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
	                      capture_output=True, text=True, timeout=60,
	                      stdin=subprocess.DEVNULL)


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--channel", type=int, default=0, help="接 CAN0 的 Kvaser 通道")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true", help="不复位，测当前正在跑的固件")
	ap.add_argument("--timeout", type=float, default=9.0, help="等 S3 的上限（秒）")
	a = ap.parse_args()

	ser = serial.Serial(a.port, 115200, timeout=0.05)
	ser.reset_input_buffer()
	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)
	tp = Isotp(bus, REQ_ID, RES_ID)

	if not a.no_reset:
		p = reset_run()
		if p.returncode != 0:
			print("[FAIL] J-Link 复位失败")
			return 1
		time.sleep(0.8)

	print("=" * 70)
	print("A1 运行期判据：实测 S3Server 超时")
	print("=" * 70)
	print("配置 S3 = %d ms，Dcm 主函数周期 10 ms → 期望 %d 拍" % (S3_MS, S3_MS // 10))

	# ---- 清零：先回默认会话，确保起始状态干净 ----
	r = tp.request([0x10, 0x01], timeout=1.5)
	if r is None or r[:2] != b"\x50\x01":
		print("[FAIL] 10 01 未得到正响应：%r" % (r,))
		return 1
	time.sleep(0.3)
	ser.reset_input_buffer()

	# ---- 进扩展会话，以正响应收到的时刻为 t0 ----
	r = tp.request([0x10, 0x03], timeout=1.5)
	if r is None or r[:2] != b"\x50\x03":
		print("[FAIL] 10 03 未得到正响应：%r" % (r,))
		return 1
	t0 = time.monotonic()
	print("已进扩展会话，开始计时（此后不发任何请求，等 S3 自动超时）")

	# ---- 轮询串口，抓 S3 timeout 的那一行 ----
	buf = ""
	elapsed = None
	deadline = t0 + a.timeout
	while time.monotonic() < deadline:
		chunk = ser.read(4096)
		if chunk:
			buf += chunk.decode("utf-8", "replace")
			if "S3 timeout" in buf:
				elapsed = time.monotonic() - t0
				break
		else:
			time.sleep(0.01)

	ser.close()
	bus.shutdown()

	if elapsed is None:
		print("[FAIL] %.1f s 内没有看到 S3 超时（串口没打印？会话没进？）" % a.timeout)
		print("       串口最后 400 字符：%r" % buf[-400:])
		return 1

	ms = elapsed * 1000.0
	print("实测 S3 超时 = %.3f s (%d ms)" % (elapsed, int(ms)))
	print("")

	if WIN_OK[0] <= ms <= WIN_OK[1]:
		print("PASS  每拍 1 次调用（%d ms / 10 ms = %d 拍，与配置一致）"
		      % (int(ms), int(round(ms / 10.0))))
		print("A1 PASS  调度唯一性在运行期成立")
		return 0

	if WIN_DOUBLE[0] <= ms <= WIN_DOUBLE[1]:
		print("FAIL  每拍 2 次调用：%d ms ≈ %d / 2。"
		      % (int(ms), S3_MS))
		print("      说明 EcuM_BswService() 之外还有一处直接调用 CanTp/Dcm，")
		print("      或 numOfMain 被算成两倍。跑 tools/a1_sched_check.py 定位。")
		return 1

	print("FAIL  实测 %.0f ms 既不是 %d 也不是 %d，节拍或 S3 配置异常"
	      % (ms, S3_MS, S3_MS // 2))
	return 1


if __name__ == "__main__":
	sys.exit(main())
