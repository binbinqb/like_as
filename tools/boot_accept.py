#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    boot_accept.py
@brief   22.3 上板验收自动化：H3 / H3' / H4（串口抓取 + J-Link 复位 + UDS 注入）

@details @section WHY 为什么要有这个脚本

          这三条用例原来都要人"敲一条命令 + 按一次复位 + 盯一眼串口"，问题是：

          - **复位时机**决定判据。H4 要求 boot 进 UDS 之后**30 s 内没有任何诊断请求**，
            人手按复位、顺手再连一下工具，那条超时永远不会触发（实际踩过）。
          - **§20 秒级的等待**靠人盯容易漏行，粘贴时又容易串窗口。

          所以把"复位 → 等某一行日志 → 断言"整条链自动化。J-Link 的 `r;g`
          等价于按复位键，串口独占读取等价于那个终端窗口。

          @section CASES 三条用例

          | 编号 | 现场 | 判据 |
          |------|------|------|
          | H4 | App 收到 `10 02` → 复位进 UDS → **30 s 不连诊断仪** | 出现 `resume normal boot after idle timeout` 且随后 `jump to slot A` |
          | H3 | `bootfault meta-blank` 后复位（开发版 Boot） | 出现 `no valid meta, fallback to vector table probe` → 跳 A |
          | H3' | `bootfault meta-crc` + 刷量产 Boot 后复位 | 出现 `image rejected (production build)`，**不**跳坏镜像 |

          @warning H3' 与恢复都要**重编 Boot**（开发/量产两个变体），每次约 40 s。
          脚本默认跑完 H3' 会恢复开发版 Boot —— 不恢复的话板子停在 UDS。

@note    串口必须独占：跑之前关掉你自己的串口终端，否则 `SerialException`。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：H4 / H3 / H3' + 恢复 |
"""

import argparse
import os
import subprocess
import sys
import tempfile
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import can  # noqa: E402
import serial  # noqa: E402

from isotp_lite import Isotp  # noqa: E402

PYTHON = sys.executable
JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"

BOOT_ELF = os.path.join(ROOT, "build", "nt", "CM4GCC", "Boot", "Boot.exe")
APP_ELF = os.path.join(ROOT, "build", "nt", "CM4GCC", "App", "App.exe")

results = []


def note(name, ok, detail=""):
	results.append((name, bool(ok), detail))
	print("  [%s] %s%s" % ("PASS" if ok else "FAIL", name,
	                      ("  (%s)" % detail) if detail else ""))


# ============================ [ 串口抓取 ] ============================


class Console:
	"""独占串口，后台线程持续收字符，提供 `wait_for(pattern, timeout)`。"""

	def __init__(self, port, baud):
		self.ser = serial.Serial(port, baud, timeout=0.1)
		self.buf = ""
		self.all = ""          # 全程原文（不清空），最后落盘当证据
		self.lock = threading.Lock()
		self.stop = False
		self.t = threading.Thread(target=self._run, daemon=True)
		self.t.start()

	def _run(self):
		while not self.stop:
			try:
				d = self.ser.read(4096)
			except Exception:
				break
			if d:
				txt = d.decode("utf-8", "replace")
				with self.lock:
					self.buf += txt
					self.all += txt

	def text(self):
		with self.lock:
			return self.buf

	def clear(self):
		with self.lock:
			self.buf = ""

	def wait_for(self, pattern, timeout=5.0):
		"""等到出现 pattern（自 clear 起算），返回 (ok, 耗时秒)。"""
		t0 = time.time()
		while (time.time() - t0) < timeout:
			if pattern in self.text():
				return True, time.time() - t0
			time.sleep(0.02)
		return False, time.time() - t0

	def wait_all(self, patterns, timeout=5.0):
		"""按顺序等若干个 pattern。

		@return (ok, 耗时秒, 未命中的 pattern 或空串)
		"""
		t0 = time.time()
		for p in patterns:
			left = timeout - (time.time() - t0)
			if left <= 0:
				return False, time.time() - t0, p
			ok, _ = self.wait_for(p, left)
			if not ok:
				return False, time.time() - t0, p
		return True, time.time() - t0, ""

	def send_line(self, line):
		self.ser.write((line + "\r\n").encode("ascii"))

	def dump(self, path):
		"""把全程原文写盘（证据用）。"""
		os.makedirs(os.path.dirname(path), exist_ok=True)
		with open(path, "w", encoding="utf-8", newline="\n") as f:
			f.write(self.text_all())

	def text_all(self):
		with self.lock:
			return self.all

	def close(self):
		self.stop = True
		try:
			self.ser.close()
		except Exception:
			pass


# ============================ [ 外部动作 ] ============================


def jlink_reset(timeout=60):
	"""J-Link 复位并运行（等价于按复位键）。"""
	script = os.path.join(tempfile.gettempdir(), "_as_boot_accept.jlink")
	with open(script, "w", encoding="ascii") as f:
		f.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	p = subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
	                   capture_output=True, text=True, timeout=timeout,
	                   stdin=subprocess.DEVNULL)
	return p.returncode == 0, (p.stdout or "") + (p.stderr or "")


def build(target, prod=False):
	cmd = [PYTHON, "-m", "SCons", "--cpl=CM4GCC", "--app=%s" % target]
	if prod:
		cmd.append("--prod")
	env = dict(os.environ)
	env.setdefault("PYTHON", PYTHON)
	env.setdefault("ARMGCC", r"C:\soft\gcc\10.3.1")
	env.setdefault("ARMGCC_VERSION", "10.3.1")
	env["PATH"] = env.get("ARMGCC", "") + r"\bin;" + env.get("PATH", "")
	p = subprocess.run(cmd, cwd=ROOT, env=env, capture_output=True, text=True)
	tail = "\n".join((p.stdout or "").splitlines()[-3:])
	return p.returncode == 0, tail


def flash(args):
	p = subprocess.run([PYTHON, os.path.join(HERE, "flash.py")] + args,
	                   cwd=ROOT, capture_output=True, text=True)
	return p.returncode == 0, "\n".join((p.stdout or "").splitlines()[-3:])


def uds_once(req, channel, bitrate, timeout=2.0):
	"""发一条 UDS 请求，收到响应就关闭总线（**不保持连接**，H4 靠这一点）。"""
	bus = can.Bus(interface="kvaser", channel=channel, bitrate=bitrate)
	try:
		tp = Isotp(bus, 0x7E0, 0x7E8)
		return tp.request(req, timeout)
	finally:
		try:
			bus.shutdown()
		except Exception:
			pass


# ============================ [ 用例 ] ============================


def case_h4(con, a):
	"""10 02 → 自动复位进 UDS → 30 s 无诊断请求 → 自动回退正常启动。"""
	print("\n=== H4：刷写请求后不连接，30 s 自动回退 ===")

	ok, _ = jlink_reset()
	if not ok:
		note("H4 J-Link 复位", False, "JLink 执行失败")
		return
	con.clear()
	ok, _ = con.wait_for("sh 1.0.0 ready", 8.0)
	if not ok:
		note("H4 App 已运行", False, "8 s 内未见 shell 就绪")
		return
	note("H4 App 已运行", True)

	con.clear()
	resp = uds_once(b"\x10\x02", a.channel, a.bitrate)
	note("H4 10 02 响应 50 02", (resp is not None) and (resp[:2] == b"\x50\x02"),
	     resp.hex(" ").upper() if resp else "超时")

	ok, _ = con.wait_for("[app] programming session", 3.0)
	note("H4 App 请求交棒", ok)

	# App 自己复位 → boot 读标志 → 进 UDS
	ok, dt, miss = con.wait_all(["[boot] flash requested by app",
	                             "[boot] entering UDS flash mode"], 8.0)
	note("H4 boot 进入 UDS", ok, ("%.1f s" % dt) if ok else ("缺：%s" % miss))

	# ★ 关键：从这一刻起不再有任何诊断请求，等 boot 的 30 s 空闲超时
	con.clear()
	ok, dt = con.wait_for("[boot] resume normal boot after idle timeout",
	                     a.idle_timeout + 15.0)
	note("H4 30 s 空闲后自动回退", ok, "%.1f s" % dt)

	ok, _ = con.wait_for("[boot] jump to slot", 5.0)
	note("H4 回退后正常启动", ok)


def case_h3(con, a):
	"""meta-blank + 开发版 Boot：向量表兜底启动。"""
	print("\n=== H3：无 meta（开发版 Boot 向量表兜底）===")

	ok, _ = jlink_reset()
	if not ok:
		note("H3 J-Link 复位", False)
		return
	con.clear()
	ok, _ = con.wait_for("sh 1.0.0 ready", 8.0)
	if not ok:
		note("H3 App 已运行", False)
		return

	con.clear()
	con.send_line("bootfault meta-blank")
	ok, _ = con.wait_for("<+0, both slots' meta erased", 3.0)
	note("H3 meta-blank 已执行", ok)
	if not ok:
		return

	con.clear()
	ok, _ = jlink_reset()
	time.sleep(0.2)
	ok, dt, miss = con.wait_all(["[boot] no valid meta, fallback to vector table probe",
	                             "[boot] jump to slot"], 10.0)
	note("H3 开发版向量表兜底并启动", ok,
	     ("%.1f s" % dt) if ok else ("缺：%s" % miss))


def case_h3p(con, a):
	"""meta-crc + 量产 Boot：拒绝坏镜像，不跳。"""
	print("\n=== H3'：量产 Boot 拒绝坏镜像 ===")

	ok, _ = jlink_reset()
	if not ok:
		note("H3' J-Link 复位", False)
		return
	con.clear()
	ok, _ = con.wait_for("sh 1.0.0 ready", 8.0)
	if not ok:
		note("H3' App 已运行", False)
		return

	con.clear()
	con.send_line("bootfault meta-crc")
	ok, _ = con.wait_for("<+0, slot", 3.0)
	note("H3' meta-crc 已注入", ok)
	if not ok:
		return

	ok, tail = build("Boot", prod=True)
	note("H3' 编出量产 Boot", ok, "" if ok else tail[-160:])
	if not ok:
		return

	ok, tail = flash(["--elf", BOOT_ELF, "--run"])
	note("H3' 刷入量产 Boot", ok, "" if ok else tail[-160:])
	if not ok:
		return

	con.clear()
	ok, dt, miss = con.wait_all(["[boot] slot A image rejected (production build)",
	                             "unusable, try slot"], 12.0)
	note("H3' 量产拒绝坏镜像并试图换槽", ok,
	     ("%.1f s" % dt) if ok else ("缺：%s" % miss))


def restore_dev(con, a):
	"""恢复：编开发版 Boot + 刷 Boot/App，保证板子回到可运行状态。"""
	print("\n=== 恢复开发版 ===")
	ok, tail = build("Boot", prod=False)
	note("恢复：编出开发版 Boot", ok, "" if ok else tail[-160:])
	ok2, tail2 = flash(["--boot", "--force", "--run"])
	note("恢复：刷 Boot + App 并复位", ok2, "" if ok2 else tail2[-160:])
	time.sleep(0.3)
	con.clear()
	ok3, _ = con.wait_for("sh 1.0.0 ready", 12.0)
	note("恢复：App 正常起来", ok3)


# ============================ [ 入口 ] ============================


def main():
	ap = argparse.ArgumentParser(description="22.3 上板验收（H4 / H3 / H3'）")
	ap.add_argument("--port", default="COM2")
	ap.add_argument("--baud", type=int, default=115200)
	ap.add_argument("--channel", type=int, default=0, help="Kvaser 通道（接 CAN0/CAN1）")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--idle-timeout", type=float, default=30.0, help="boot 的空闲超时秒数")
	ap.add_argument("--cases", default="H4,H3,H3p", help="要跑的用例，逗号分隔")
	ap.add_argument("--no-restore", action="store_true", help="跑完不恢复开发版 Boot")
	ap.add_argument("--dump", default=os.path.join(ROOT, "build", "boot_accept.log"),
	                help="全程串口原文落盘路径（默认 build/boot_accept.log，该目录已 gitignore）")
	a = ap.parse_args()

	print("== 22.3 上板验收 ==")
	print("串口 %s @ %d，Kvaser ch%d @ %d" % (a.port, a.baud, a.channel, a.bitrate))

	try:
		con = Console(a.port, a.baud)
	except Exception as e:
		print("[ERROR] 打不开串口 %s：%s" % (a.port, e))
		print("        先把串口终端关掉（本脚本要独占）")
		return 2

	try:
		want = [x.strip() for x in a.cases.split(",") if x.strip()]
		if "H4" in want:
			case_h4(con, a)
		if "H3" in want:
			case_h3(con, a)
		if "H3p" in want:
			case_h3p(con, a)
		if not a.no_restore:
			restore_dev(con, a)
	finally:
		try:
			con.dump(a.dump)
			print("\n串口原文已存：%s" % a.dump)
		except Exception as e:
			print("[WARN] 落盘失败：%s" % e)
		con.close()

	fail = sum(1 for _n, ok, _d in results if not ok)
	print("\n-- %d 项断言，%d 项失败" % (len(results), fail))
	return 0 if fail == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
