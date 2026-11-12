#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""板级 shell 设备：按**提示符**切命令边界，不靠 sleep 猜时长。

	原语只有三个：
	  write()      发原始文本（不发回车，交互式提示用）
	  read_until() 读到某个 token 或超时，返回累计文本（已去 ANSI）
	  cmd()        flush → 写一行 → 读到提示符，返回本次输出

	场景脚本在此之上组合。刻意不做"业务方法"（不做 `reboot()`、`enter_boot()`），
	因为那些是脚本的事，写进设备层就又变成一份需要同步的副本。

	端口发现：`--com auto` 或 `port="auto"` 时按 USB 描述关键字找（默认
	CVM014x 的 USB-SERIAL），找不到就列出**所有**可用端口再报错 —— 比只说
	"打不开 COM2" 省一轮排查。

@author binbina
"""

import re
import time

ANSI_RE = re.compile(r"\x1b\[[0-9;?]*[A-Za-z]")
DEFAULT_PROMPT = "CVM014x >> "
# 板子的 USB 串口芯片（本机实测描述：`USB-Enhanced-SERIAL CH343 (COM2)`）
DEFAULT_KEY = "CH343"


def find_port(key=DEFAULT_KEY):
	"""按 USB 描述关键字找串口；找不到返回 None（调用方决定是否报错）。

	key 可以是字符串或字符串序列（任一命中即可）。
	示例（本机）：`USB-Enhanced-SERIAL CH343 (COM2)` → key="CH343" 命中；
	`JLink CDC UART Port (COM3)` 故意不命中（那是调试口，不是板级 shell）。
	"""
	from serial.tools import list_ports

	keys = [key] if isinstance(key, str) else list(key)
	for item in list_ports.comports():
		port, desc = item.device, (item.description or "").upper()
		if any(k.upper() in desc for k in keys):
			return port
	return None


def list_ports_text():
	"""人类可读的端口清单，用于"找不到"时的报错。"""
	from serial.tools import list_ports

	rows = ["%s: %s" % (p.device, p.description or "") for p in list_ports.comports()]
	return "\n".join(rows) if rows else "(没有任何串口)"


class Shell:
	"""串口 shell 设备（上下文管理器，退出即关）。"""

	def __init__(self, port="auto", baud=115200, prompt=DEFAULT_PROMPT,
				 timeout=2.0, key=DEFAULT_KEY):
		self.prompt = prompt
		self.timeout = timeout
		self.key = key
		self.port = find_port(key) if port == "auto" else port
		if not self.port:
			raise RuntimeError(
				"找不到串口（关键字 '%s'）。当前可用端口：\n%s" % (key, list_ports_text()))
		import serial
		self.ser = serial.Serial(self.port, baud, timeout=0.1)
		self.ser.reset_input_buffer()
		self.pending = ""
		self.history = ""       # 本次会话收到的全部原文（证据用，不参与解析）""

	def __enter__(self):
		return self

	def __exit__(self, *exc):
		self.close()

	def close(self):
		try:
			self.ser.close()
		except Exception:
			pass

	def flush(self):
		"""丢掉尚未读走的字节（避免上一条命令的尾巴算进下一条）。"""
		self.ser.reset_input_buffer()
		self.pending = ""

	def write(self, text):
		self.ser.write(text.encode("utf-8"))

	def read_until(self, token, timeout=None):
		"""读到 token 出现；超时返回已收到的内容（不抛异常）。"""
		deadline = time.time() + (self.timeout if timeout is None else timeout)
		while time.time() < deadline:
			chunk = self.ser.read(256)
			if not chunk:
				continue
			text = chunk.decode("utf-8", "replace")
			self.pending += text
			self.history += text
			if token and token in self.pending:
				break
		out, self.pending = self.pending, ""
		return ANSI_RE.sub("", out)

	def read_some(self, seconds):
		"""给定时长内尽量多读（用于启动横幅这类"没有终止符"的输出）。"""
		deadline = time.time() + seconds
		while time.time() < deadline:
			chunk = self.ser.read(256)
			if chunk:
				text = chunk.decode("utf-8", "replace")
				self.pending += text
				self.history += text
		out, self.pending = self.pending, ""
		return ANSI_RE.sub("", out)

	def all_text(self):
		"""整段会话原文（含 ANSI）：排障时看"板子到底说了什么"。"""
		return self.history

	def cmd(self, line, timeout=None, prompt=True):
		"""发一行、读到提示符，返回本次输出（含回显）。

		prompt=False 用于 `pause`/`*RST` 这类不进提示符的命令。
		"""
		self.flush()
		self.write(line + "\r\n")
		return self.read_until(self.prompt if prompt else None, timeout)

	def lines(self, line, **kw):
		"""同 cmd()，但整理成"去掉空行/回显/提示符"的行列表。"""
		text = self.cmd(line, **kw)
		out = []
		for raw in text.splitlines():
			s = raw.strip().replace("\r", "")
			if not s or s == line.strip() or s == self.prompt:
				continue
			out.append(s)
		return out
