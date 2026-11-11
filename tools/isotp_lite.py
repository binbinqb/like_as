#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""最小 ISO-TP（ISO 15765-2）实现，供 M3 / M6 的验收脚本共用。

为什么手写而不是用 `can-isotp`：
	`isotp.CanStack` 在这块 Kvaser 上实测收不到响应帧（板子确实回了 0x7E8，
	库的 `process()` 就是不返回数据）。排查这个库的时间成本高于自己写一个 ——
	而且测试脚本里每一帧都显式可控，定位问题时反而更直接。

支持：
	- 单帧收发（SF）
	- 多帧发送（FF + CF + 等 FC）
	- 多帧接收（FF → 发 FC → 收 CF）
	- **NRC 0x78 (responsePending)**：自动继续等，直到拿到最终响应

不支持（本工程用不到）：
	- 流控 WAIT / OVFLW
	- CAN FD
	- 扩展寻址 / 功能寻址

@author binbina
"""

import time

import can

# 物理寻址：诊断仪发 0x7E0，ECU 回 0x7E8
REQ_ID = 0x7E0
RES_ID = 0x7E8

# 填充字节。UDS 规定未用字节由 OEM 定义，本工程用 0xCC（与 Dcm_Cfg 的 txBuffer 初值一致）
PAD = 0xCC


class Isotp:
	"""手写的最小 ISO-TP 实现。"""

	def __init__(self, bus, req_id=REQ_ID, res_id=RES_ID):
		self.bus = bus
		self.req_id = req_id
		self.res_id = res_id

	# ---------------- 底层 ----------------

	def _tx(self, frame8):
		self.bus.send(can.Message(arbitration_id=self.req_id, data=bytes(frame8),
								  is_extended_id=False, dlc=8))

	def _wait(self, pred, timeout):
		"""在响应 ID 上等一帧满足 pred 的数据，超时返回 None。"""
		t_end = time.time() + timeout
		while time.time() < t_end:
			left = t_end - time.time()
			m = self.bus.recv(timeout=min(0.05, max(0.001, left)))
			if m is not None and m.arbitration_id == self.res_id:
				d = bytes(m.data)
				if pred(d):
					return d
		return None

	# ---------------- 发送 ----------------

	def _send_long(self, payload):
		"""多帧发送：FF → 等 FC → 按 FC 的 BS/STmin 发 CF。

		⚠ **必须遵守 FC 里的 BlockSize**。踩过的坑：最初发完 FF 就把所有 CF
		一次性推出去，而板子的 FC 是 `30 08 00`（BS=8）—— ECU 收满 8 帧就停下
		等下一个 FC，等不到就按 N_Cr 超时丢弃整包。
		现象极具迷惑性：**FF 发出去了、FC 也回来了、CF 全发出去了，
		然后没有任何响应**，看起来像 ECU 死了，其实是协议层在等流控。

		另外 STmin 也要等：板子配的是 0（不限速），但真车 ECU 常见 10~20 ms，
		不等的话接收端会因为帧太密丢帧。
		"""
		n = len(payload)
		# FF：PCI=0x1，低 4 位是长度高 4 位
		frame = bytes([0x10 | ((n >> 8) & 0x0F), n & 0xFF]) + payload[:6]
		self._tx(frame.ljust(8, bytes([PAD])))

		fc = self._wait_fc(1.0)
		if fc is None:
			return False

		idx = 6
		sn = 1
		bs = fc[1]        # BlockSize：0 表示"后面不再发流控"
		stmin = fc[2]     # 相邻 CF 的最小间隔（ms），0x00-0x7F
		in_block = 0

		while idx < n:
			chunk = payload[idx:idx + 7]
			self._tx((bytes([0x20 | (sn & 0x0F)]) + chunk).ljust(8, bytes([PAD])))
			idx += 7
			sn = (sn + 1) & 0x0F
			in_block += 1

			if stmin > 0:
				time.sleep(stmin / 1000.0)

			if (bs > 0) and (in_block >= bs) and (idx < n):
				in_block = 0
				fc = self._wait_fc(1.0)
				if fc is None:
					return False
				bs = fc[1]
				stmin = fc[2]

		return True

	def _wait_fc(self, timeout):
		"""等一个可用的流控帧，跳过 WAIT(0x31)；OVFLW(0x32) 直接判失败。"""
		t_end = time.time() + timeout
		while time.time() < t_end:
			fc = self._wait(lambda d: (d[0] & 0xF0) == 0x30,
							max(0.001, t_end - time.time()))
			if fc is None:
				return None
			status = fc[0] & 0x0F
			if status == 0x00:      # CTS
				return fc
			if status == 0x01:      # WAIT：ECU 还没准备好，继续等
				continue
			return None             # 0x02 OVFLW 及其它：放弃
		return None

	# ---------------- 接收 ----------------

	def _recv_long(self, first, timeout):
		n = ((first[0] & 0x0F) << 8) | first[1]
		out = bytearray(first[2:8])
		# 回 FC：CTS、BS=0（后面不再发流控）、STmin=0
		self._tx(bytes([0x30, 0x00, 0x00]).ljust(8, bytes([PAD])))
		while len(out) < n:
			cf = self._wait(lambda d: (d[0] & 0xF0) == 0x20, timeout)
			if cf is None:
				return None
			out += cf[1:8]
		return bytes(out[:n])

	def _recv_response(self, timeout):
		d = self._wait(lambda _: True, timeout)
		if d is None:
			return None
		pci = d[0] >> 4
		if pci == 0x0:
			return d[1:1 + (d[0] & 0x0F)]
		if pci == 0x1:
			return self._recv_long(d, timeout)
		return None       # 0x2/0x3 不该出现在响应首帧

	# ---------------- 对外 ----------------

	def flush_rx(self):
		"""丢掉总线上残留的响应帧。

		@note  为什么必须有：两条请求挨得很近时（比如 `2E` 写完紧接着 `22` 读回），
		        上一轮如果有多帧响应，剩下的 CF 帧还挂在驱动缓冲里。
		        不清掉的话，`_recv_response()` 会把**上一条的尾巴**当成
		        本条的首帧解析 —— 现象是"请求串位"：
		        读 VIN 拿到的是上一条写的值、或者干脆解析出 `?`。
		        这比不响应难查得多，因为每一条单独发都是对的。
		"""
		for _ in range(256):
			if self.bus.recv(timeout=0.001) is None:
				break

	def request(self, payload, timeout=2.0):
		"""发一条诊断请求，返回**最终**响应；超时返回 None。

		@note  会吞掉中间所有 `7F xx 78`（responsePending）。
		        0x14 清故障码要等 NvM 写完，板子会先回 0x78 再回 0x54 ——
		        不处理的话，第 2 次查询会读到上一条命令的尾巴，
		        现象是"命令串位"，极难定位。
		"""
		payload = bytes(payload)

		# 发之前先清干净 RX，避免读到上一条请求的残留帧（见 flush_rx 的说明）
		self.flush_rx()

		if len(payload) <= 7:
			self._tx((bytes([len(payload)]) + payload).ljust(8, bytes([PAD])))
		else:
			if not self._send_long(payload):
				return None

		r = self._recv_response(timeout)
		guard = 0
		while (r is not None) and (len(r) >= 3) and (r[0] == 0x7F) and (r[2] == 0x78):
			guard += 1
			if guard > 20:               # 最多等 20 次 pending，防止死循环
				return None
			r = self._recv_response(timeout)
		return r
