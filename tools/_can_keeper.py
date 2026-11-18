#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""CAN 通道"保持者"：占住一路总线只为 ACK，防止对端 bus-off。

## 为什么需要

台架上只有一块板 + 一块 Kvaser。某个用例只打开 ch0（诊断）时，CAN1 上的
6 条 Com 报文没有节点 ACK → TEC 打满 → bus-off；而 `Fault_PollBusOff()` 会
**持续打印**并在下一拍重试，几千行串口输出把主循环拖慢，后续用例全部受影响
（2026-11-18 回归套件就因此在 com_retry 上误报 4 项 FAIL）。

Kvaser 在正常模式下收到帧会自动 ACK，所以"打开并持续 recv"就等于保持者。
Kvaser CANlib 同一通道不允许多进程/多句柄同时打开，因此保持者必须由
**当前用例进程**自己开，而不是 runner 另起进程。

## 用法

	from _can_keeper import Keeper
	k = Keeper(other_channel)      # 失败也不抛：单通道台架照常跑
	...
	k.close()

@author binbina
"""

import threading

import can


class Keeper(object):
	"""后台持续 recv 的旁观通道；构造失败时返回一个空壳（`ok=False`）。"""

	def __init__(self, channel, bitrate=500000):
		self.ok = False
		self.bus = None
		self._stop = threading.Event()
		self._th = None
		try:
			self.bus = can.Bus(interface="kvaser", channel=channel, bitrate=bitrate)
		except Exception:
			# 单通道台架 / 通道被占用：不阻塞用例，只是回到"有 bus-off 风险"的旧行为
			return
		self.ok = True
		self._th = threading.Thread(target=self._run, daemon=True)
		self._th.start()

	def _run(self):
		while not self._stop.is_set():
			try:
				if self.bus.recv(0.05) is None:
					continue
			except Exception:
				return

	def close(self):
		self._stop.set()
		if self._th is not None:
			self._th.join(timeout=1.0)
		if self.bus is not None:
			try:
				self.bus.shutdown()
			except Exception:
				pass
