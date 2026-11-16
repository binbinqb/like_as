#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    a3_isolation_check.py
@brief   A3「测试隔离」验收：自测帧默认不发，只能被命令打开

@details 判据（全部上板实测，不看代码）：
          1. 复位后 3 s 内，CAN0 总线上**没有** 0x123；
             CAN1 总线上**没有** 0x124
          2. 同期 CAN1 上**有** Com 驱动的真实矩阵报文（0x18FE4021 等）
             —— 这一半同样重要：证明"没发"是因为开关关着，
             不是因为整条发送链路坏了
          3. `can` 命令回读 `selftest auto-tx=off`
          4. `can auto on` 之后 0x123 出现（开关真的能打开）
          5. `can auto off` 之后 0x123 消失（开关真的能关掉）

@note   第 2 条是本脚本和"只 grep 代码"的关键区别。只证明"没发 0x123"
        太弱了 —— 把 Can 控制器停了也能满足。必须同时证明"真实报文在发"。

@note   第 4/5 条构成开关的双向证明。只验"默认不发"无法区分
        "开关有效"和"这个开关根本没接上"。

@author  binbina
@version V1.0.0
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

ID_SELFTEST_CAN0 = 0x123   # 驱动层自测（CAN0）
ID_SELFTEST_CAN1 = 0x124   # 驱动层自测（CAN1）
ID_REAL_MATRIX = 0x18FE4021  # BCM_LCSF，Com 周期 50 ms，真矩阵报文

results = []


def note(name, ok, detail=""):
	results.append((name, ok, detail))


def reset_run():
	script = os.path.join(tempfile.gettempdir(), "_a3_run.jlink")
	with open(script, "w", encoding="ascii") as f:
		f.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
	                      capture_output=True, text=True, timeout=60,
	                      stdin=subprocess.DEVNULL)


def count_ids(buses, seconds, ids):
	"""在给定总线上统计指定 ID 的帧数，返回 {id: n}。"""
	got = {i: 0 for i in ids}
	t0 = time.time()
	while (time.time() - t0) < seconds:
		for b in buses:
			m = b.recv(0.02)
			if (m is not None) and (m.arbitration_id in got):
				got[m.arbitration_id] += 1
	return got


def drain(buses, quiet=0.35, max_wait=3.0):
	"""一直读，直到**连续 quiet 秒读不到任何帧**（或超过 max_wait）。

	@note  固定时长排空不够用：Kvaser 驱动会把报文缓存起来，
	        实测复位前那批 0x123/0x124 会一直压在缓冲里，
	        计时器一到就漏进"上电 3 s 内的帧数"，造成假失败。
	        判据必须是"总线真的静了"，而不是"我读了 0.3 秒"。
	"""
	t_end = time.time() + max_wait
	last_seen = time.time()
	while time.time() < t_end:
		got = False
		for b in buses:
			if b.recv(0.02) is not None:
				got = True
		if got:
			last_seen = time.time()
		elif (time.time() - last_seen) >= quiet:
			return


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--ch0", type=int, default=0, help="CAN0 通道（0x123 在这）")
	ap.add_argument("--ch1", type=int, default=1, help="CAN1 通道（0x124/矩阵在这）")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true")
	a = ap.parse_args()

	ser = serial.Serial(a.port, 115200, timeout=0.2)
	bus0 = can.Bus(interface="kvaser", channel=a.ch0, bitrate=a.bitrate)
	bus1 = can.Bus(interface="kvaser", channel=a.ch1, bitrate=a.bitrate)
	buses = [bus0, bus1]

	def send(cmd, wait=0.25):
		ser.reset_input_buffer()
		ser.write((cmd + "\n").encode())
		ser.flush()
		time.sleep(wait)
		return ser.read(8192).decode("utf-8", "replace")

	# 打开总线后先把驱动缓冲里可能压着的旧帧（上一次测试留下的）读干净。
	# 这一步不能省：Kvaser 的接收缓冲跨进程保留，不清就会在
	# "上电后 3 s 内有没有 0x123" 这个判据上直接给出假数据。
	drain(buses)

	if not a.no_reset:
		p = reset_run()
		if p.returncode != 0:
			print("[FAIL] J-Link 复位失败")
			return 1
		# 复位瞬间板子还在跑旧状态（可能刚执行过 `can auto on`），
		# 那几帧也会进缓冲，所以要再排一次。
		time.sleep(0.2)
		drain(buses)
	else:
		drain(buses)

	# ---------- 1) 上电默认状态：自测帧必须不发 ----------
	# 复位后要等 Com/CanSM 起来（约 0.5~1 s 才 ONLINE），所以窗口取 3 s，
	# 足够 0x123（500 ms 周期）出现 6 次、0x124 出现 6 次。
	got = count_ids(buses, 3.0, [ID_SELFTEST_CAN0, ID_SELFTEST_CAN1, ID_REAL_MATRIX])
	note("上电: CAN0 无自测帧 0x123", got[ID_SELFTEST_CAN0] == 0,
	     "实收 %d 帧" % got[ID_SELFTEST_CAN0])
	note("上电: CAN1 无自测帧 0x124", got[ID_SELFTEST_CAN1] == 0,
	     "实收 %d 帧" % got[ID_SELFTEST_CAN1])
	# 这条是"没发"的对照组：真实矩阵报文必须在发，否则上面的 0 帧
	# 可能只是整条链路没起来。
	note("上电: 真实矩阵报文 0x18FE4021 仍在发（对照组）",
	     got[ID_REAL_MATRIX] >= 10,
	     "实收 %d 帧 / 3.0 s（期望 >=10，50 ms 周期）" % got[ID_REAL_MATRIX])

	# ---------- 2) 命令回读 ----------
	out = send("can", 0.3)
	note("`can` 回读 selftest auto-tx=off", "selftest auto-tx=off" in out,
	     ([l.strip() for l in out.splitlines() if "auto-tx" in l] or ["(无该行)"])[0][:70])

	# ---------- 3) 打开 → 必须开始发 ----------
	drain(buses)
	out = send("can auto on", 0.3)
	note("`can auto on` 回显 ON", "auto-tx: ON" in out,
	     ([l.strip() for l in out.splitlines() if "auto-tx" in l] or ["(无该行)"])[0][:70])
	got = count_ids(buses, 2.0, [ID_SELFTEST_CAN0, ID_SELFTEST_CAN1])
	note("auto on 后: 0x123 出现", got[ID_SELFTEST_CAN0] >= 2,
	     "实收 %d 帧 / 2.0 s（期望 >=2，500 ms 周期）" % got[ID_SELFTEST_CAN0])
	note("auto on 后: 0x124 出现", got[ID_SELFTEST_CAN1] >= 1,
	     "实收 %d 帧 / 2.0 s" % got[ID_SELFTEST_CAN1])

	# ---------- 4) 关掉 → 必须停发 ----------
	out = send("can auto off", 0.3)
	note("`can auto off` 回显 OFF", "auto-tx: OFF" in out,
	     ([l.strip() for l in out.splitlines() if "auto-tx" in l] or ["(无该行)"])[0][:70])
	time.sleep(0.6)   # 等一个发送周期走完，避免"刚发完一帧"被算进去
	drain(buses)
	got = count_ids(buses, 1.5, [ID_SELFTEST_CAN0, ID_SELFTEST_CAN1])
	note("auto off 后: 0x123 停发", got[ID_SELFTEST_CAN0] == 0,
	     "实收 %d 帧 / 1.5 s" % got[ID_SELFTEST_CAN0])
	note("auto off 后: 0x124 停发", got[ID_SELFTEST_CAN1] == 0,
	     "实收 %d 帧 / 1.5 s" % got[ID_SELFTEST_CAN1])

	bus0.shutdown()
	bus1.shutdown()
	ser.close()

	# ---------- 汇总 ----------
	print()
	print("=" * 78)
	fail = 0
	for name, ok, detail in results:
		tag = " OK " if ok else "FAIL"
		print("  [%s] %-42s %s" % (tag, name, detail))
		if not ok:
			fail += 1
	n = len(results)
	print("=" * 78)
	print("%s %d / %d" % ("PASS" if fail == 0 else "FAIL", n - fail, n))
	if fail:
		print("  失败 %d 项" % fail)
	print("=" * 78)
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
