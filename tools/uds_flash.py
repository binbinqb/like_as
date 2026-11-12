#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""A/B 分区 UDS 刷写工具 —— 把镜像写进**非活动槽**，由 boot 在下次复位时接管。

为什么刷的是"非活动槽"而不是"应用区"：
	A/B 的核心就是"正在跑的那一份永远不被碰"。本工具从头到尾不会擦写
	当前运行的槽，所以整个过程任何时刻掉电，至少有一个槽是好的 ——
	这是"刷不死"的唯一来源。boot 上电比较两个槽的 rollingCounter，
	大的那个启动；0x37 写完 meta 时新槽的计数 +1，于是自动成为活动槽。

用法：
	python tools/uds_flash.py --elf build/nt/CM4GCC/AppB/AppB.exe
	python tools/uds_flash.py --elf <AppB.exe> --slot B --verify
	python tools/uds_flash.py --elf <App.exe>  --slot A     # A 坏了要救时

⚠ 镜像必须与目标槽**链接地址一致**：App（slot A）刷进 B 槽会跑飞，
	因为 Cortex-M4 没有 MMU，代码里的绝对地址在链接时就定死了。
	本工具会从 ELF 的向量表读出真实基址并与 `--slot` 对账，不一致直接拒绝。

@author binbina
"""

import argparse
import os
import subprocess
import sys
import tempfile
import time
import zlib

import can

from isotp_lite import Isotp

# ============================ [ 常量 ] ============================

# 与 app/platform/cvm0146/include/boot_flash_map.h 保持一致。
# 改分区时两边都要改；这里的数字只用于"算地址和校验范围"，
# 真正的权威永远是固件里的那份宏。
#
# ⚠ D1 起 boot 扩到 128 KB，两个槽整体后移 64 KB：
#   boot   0x00000 - 0x1FFFF（128 KB）
#   Slot A 0x20000 - 0x8FFFF（448 KB，尾部 4 KB = meta）
#   Slot B 0x90000 - 0xFFFFF（448 KB，尾部 4 KB = meta）
# 用旧地址（0x10000/0x80000）发 0x34 会被固件的 FlashLoader_MatchSlotBase()
# 拒绝（要求地址精确等于槽基址），表现是"34 请求收到 NRC 0x31"。
SLOT_BASE = {0: 0x00020000, 1: 0x00090000}
SLOT_SIZE = 0x00070000
SLOT_META_SIZE = 0x00001000
SLOT_IMAGE_MAX = SLOT_SIZE - SLOT_META_SIZE

SLOT_NAME = {0: "A", 1: "B"}
NAME_SLOT = {"A": 0, "B": 1}

# 0x36 每块字节数。与固件 FlashLoader.h 的 FLASH_LOADER_BLOCK_SIZE 一致：
# 120 是 8 的倍数，正好整 phrase 写，少一条"攒尾巴"的路径。
BLOCK = 120

OBJCOPY = r"C:\soft\gcc\10.3.1\bin\arm-none-eabi-objcopy.exe"

# 常用 NRC，只为把错误信息打成人话
NRC_TEXT = {
	0x10: "generalReject",
	0x11: "serviceNotSupported",
	0x12: "subFunctionNotSupported",
	0x13: "incorrectMessageLengthOrInvalidFormat",
	0x22: "conditionsNotCorrect (槽正在运行 / 存储忙)",
	0x24: "requestSequenceError (跳步了：擦除/下载顺序不对)",
	0x31: "requestOutOfRange (地址或长度不合法)",
	0x33: "securityAccessDenied (没解锁)",
	0x72: "generalProgrammingFailure (擦写失败)",
	0x78: "responsePending",
}


def die(msg):
	print("\n[FAIL] %s" % msg)
	sys.exit(1)


def be32(v):
	return [(v >> 24) & 0xFF, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF]


# ============================ [ 镜像提取 ] ============================

def elf_to_image(elf):
	"""把 ELF 转成从槽基址开始的裸镜像，返回 (镜像字节, 基址)。

	用 `--gap-fill 0xFF` 而不是默认的 0x00：镜像里如果有段间空隙，
	填 0xFF 才是 Flash 的擦除态，刷进未擦净区域时不会被误判成"有数据"；
	填 0 则会在 CRC 里引入一片假的 0，而现场看起来"校验通过"。
	"""
	if not os.path.isfile(elf):
		die("ELF not found: %s" % elf)

	out = os.path.join(tempfile.gettempdir(), "_as_uds_flash.bin")
	cmd = [OBJCOPY, "-O", "binary", "--gap-fill", "0xFF", elf, out]
	r = subprocess.run(cmd, capture_output=True, text=True)
	if r.returncode != 0:
		die("objcopy failed: %s" % (r.stderr.strip() or r.stdout.strip()))

	with open(out, "rb") as fh:
		data = fh.read()

	if len(data) < 8:
		die("image too small (%d bytes)" % len(data))

	# 向量表第二个字 = Reset_Handler，落在哪个槽就说明链接到了哪个槽
	pc = int.from_bytes(data[4:8], "little")
	base = None
	for idx, b in SLOT_BASE.items():
		if b <= (pc & ~1) < (b + SLOT_SIZE):
			base = b
			break
	if base is None:
		die("Reset_Handler 0x%08X 不在任何槽内，镜像链接地址不对" % (pc & ~1))

	return data, base


# ============================ [ UDS 封装 ] ============================

class Flash:
	def __init__(self, tp, verbose=False):
		self.tp = tp
		self.verbose = verbose

	def req(self, payload, timeout=10.0, what=""):
		payload = bytes(payload)
		if self.verbose:
			print("  TX %s" % payload.hex(" ").upper())
		r = self.tp.request(payload, timeout)
		if r is None:
			die("no response (%s)" % (what or payload[:2].hex().upper()))
		if self.verbose:
			print("  RX %s" % r.hex(" ").upper())
		if (len(r) >= 3) and (r[0] == 0x7F) and (r[1] == payload[0]):
			nrc = r[2]
			die("%s 被拒: NRC 0x%02X %s" % (what or "0x%02X" % payload[0], nrc,
										   NRC_TEXT.get(nrc, "")))
		return r

	def session(self, mode=0x03):
		r = self.req([0x10, mode], what="10 %02X" % mode)
		if r[0] != 0x50:
			die("10 %02X unexpected: %s" % (mode, r.hex()))

	def unlock(self):
		"""0x27 level 1。

		@note 固件当前的 `Dcm_CompareKey()` 恒通过，所以 key 随便填 4 字节 ——
		      但流程必须走完：0x31/0x34/0x36/0x37/0x11 的 securityMask 是 0x02，
		      只允许 level 1，不解锁会全部回 NRC 0x33。
		      换成真算法后，这里要按种子算 key（SWS 里的 0x27 算法）。
		"""
		r = self.req([0x27, 0x01], what="27 01 (requestSeed)")
		if r[0] != 0x67:
			die("27 01 unexpected: %s" % r.hex())
		seed = r[2:]
		print("  seed      : %s" % (seed.hex(" ").upper() if seed else "(empty)"))
		self.req([0x27, 0x02, 0x00, 0x00, 0x00, 0x00], what="27 02 (sendKey)")

	def erase(self, base, size):
		print("  erase     : 0x%06X .. 0x%06X (%d bytes, %d sectors)" %
			  (base, base + size - 1, size, (size + 2047) // 2048))
		t0 = time.time()
		r = self.req([0x31, 0x01, 0xFF, 0x00] + be32(base) + be32(size),
					 timeout=180.0, what="31 01 FF00 (eraseMemory)")
		if r[0] != 0x71:
			die("erase unexpected: %s" % r.hex())
		# 响应布局：71 <subFn> <RID_hi> <RID_lo> <status...>
		#                                   ↑ r[3]      ↑ r[4]
		# ⚠ 状态在 r[4]，不是 r[3] —— r[3] 是 RID 的低字节（0xFF00 → 0x00），
		# 读错位置时"失败"永远读成 0（成功），"成功"也永远读成 0，
		# 于是这个检查形同虚设，什么问题都发现不了。
		if len(r) < 5:
			die("erase response too short: %s" % r.hex())
		if r[4] != 0:
			die("erase routine reported failure (status=%d)" % r[4])
		print("  erased    : %.1f s" % (time.time() - t0))

	def download(self, base, size):
		r = self.req([0x34, 0x00, 0x44] + be32(base) + be32(size),
					 what="34 (requestDownload)")
		if r[0] != 0x74:
			die("34 unexpected: %s" % r.hex())
		# 74 <lenFmt> <blockLen...>
		length_fmt = r[1] >> 4
		block = int.from_bytes(r[2:2 + length_fmt], "big")
		print("  blockLen  : %d" % block)
		return block

	def transfer(self, data):
		seq = 1
		total = len(data)
		done = 0
		t0 = time.time()
		last_pct = -1
		while done < total:
			chunk = data[done:done + BLOCK]
			r = self.req(bytes([0x36, seq & 0xFF]) + chunk,
						 timeout=10.0, what="36 block %d" % seq)
			if r[0] != 0x76:
				die("36 unexpected: %s" % r.hex())
			if r[1] != (seq & 0xFF):
				die("36 序号回显不一致: sent %d got %d" % (seq & 0xFF, r[1]))
			done += len(chunk)
			seq += 1
			pct = done * 100 // total
			if pct != last_pct:
				el = time.time() - t0
				rate = done / el / 1024.0 if el > 0 else 0
				sys.stdout.write("\r  transfer  : %3d%%  %d/%d B  %.1f KB/s" %
								 (pct, done, total, rate))
				sys.stdout.flush()
				last_pct = pct
		print("")

	def exit(self):
		r = self.req([0x37], timeout=60.0, what="37 (requestTransferExit)")
		if r[0] != 0x77:
			die("37 unexpected: %s" % r.hex())

	def verify(self, base, size, crc):
		r = self.req([0x31, 0x01, 0xFF, 0x01] + be32(base) + be32(size) + be32(crc),
					 timeout=60.0, what="31 01 FF01 (checkIntegrity)")
		if r[0] != 0x71:
			die("check unexpected: %s" % r.hex())
		# 同 erase：状态在 r[4]
		if len(r) < 5:
			die("check response too short: %s" % r.hex())
		return r[4] == 0

	def reset(self):
		"""0x11 硬复位。

		@note **拿不到 `51 01` 不算失败**。固件在正响应发出后 500 ms 才真正复位，
		但刷写刚结束时主循环正忙（0x37 刚擦过两个 meta 扇区），偶尔会把响应
		挤到复位之后 —— 上位机看到的是超时，而 ECU 其实已经正常重启了。
		所以这里只等 1 秒，收到就打印，收不到也继续。
		"""
		r = self.tp.request(bytes([0x11, 0x01]), 1.0)
		if r is not None:
			print("  reset ack : %s" % r.hex(" ").upper())
		else:
			print("  reset ack : (none — 已复位，属正常)")


def main():
	ap = argparse.ArgumentParser(
		description="A/B 分区 UDS 刷写（写非活动槽）")
	ap.add_argument("--elf", required=True, help="要刷的 ELF（必须与目标槽链接地址一致）")
	ap.add_argument("--slot", default="auto", choices=["auto", "A", "B"],
					help="目标槽；auto = 挑一个不是镜像链接地址的槽")
	ap.add_argument("--channel", type=int, default=0, help="Kvaser 通道号")
	ap.add_argument("--bitrate", type=int, default=500000)
	ap.add_argument("--no-reset", action="store_true", help="刷完不复位")
	ap.add_argument("--verify", action="store_true", help="0x37 后用 31 01 FF01 复核 CRC")
	ap.add_argument("--dry-run", action="store_true", help="只打印计划，不连总线")
	ap.add_argument("-v", "--verbose", action="store_true")
	a = ap.parse_args()

	data, link_base = elf_to_image(a.elf)
	size = len(data)
	crc = zlib.crc32(data) & 0xFFFFFFFF
	link_slot = 0 if link_base == SLOT_BASE[0] else 1

	print("=" * 72)
	print(" A/B UDS 刷写")
	print("=" * 72)
	print("  elf       : %s" % os.path.basename(a.elf))
	print("  linked at : 0x%06X  (slot %s)" % (link_base, SLOT_NAME[link_slot]))
	print("  image     : %d bytes (%.1f KB)  crc32=%08X" % (size, size / 1024.0, crc))

	if size > SLOT_IMAGE_MAX:
		die("镜像 %d B 超过单槽上限 %d B" % (size, SLOT_IMAGE_MAX))

	# A/B 的镜像**只能刷进它链接的那个槽** —— 这不是策略选择，而是硬约束：
	# 代码里的绝对地址在链接时定死，AppB 刷进 A 槽会跳飞。
	# 所以"升级到 B"的正确做法是：编 AppB → 刷 B 槽（此时 A 在跑，B 是空闲的）。
	# 目标槽正好是活动槽时，固件会回 NRC 0x22 拒绝 —— 由 ECU 判，工具不猜。
	target = link_slot

	if (a.slot != "auto") and (NAME_SLOT[a.slot] != link_slot):
		die("镜像链接在 slot %s，却指定刷进 slot %s —— 两者必须一致，"
			"否则跳过去第一次解引用全局变量就会跑飞"
			% (SLOT_NAME[link_slot], a.slot))

	base = SLOT_BASE[target]
	print("  target    : slot %s @ 0x%06X" % (SLOT_NAME[target], base))
	print("  block     : %d B" % BLOCK)
	print("  meta      : 由 0x37 写入（rollingCounter = 另一槽 + 1）")

	if a.dry_run:
		print("\n[dry-run] 不做任何操作")
		return

	bus = can.Bus(interface="kvaser", channel=a.channel, bitrate=a.bitrate)
	tp = Isotp(bus)
	f = Flash(tp, a.verbose)

	try:
		print("\n-- 1/7 extended session")
		f.session(0x03)

		print("-- 2/7 security access (level 1)")
		f.unlock()

		print("-- 3/7 erase target slot")
		f.erase(base, size)

		print("-- 4/7 request download")
		block = f.download(base, size)
		if block < BLOCK:
			# 固件报告的块长比工具假设的小 → 按小的发，否则会超长
			print("  note      : 固件块长 %d < %d，按固件值发送" % (block, BLOCK))
			globals()["BLOCK"] = block

		print("-- 5/7 transfer data")
		f.transfer(data)

		print("-- 6/7 transfer exit (写 meta)")
		f.exit()

		if a.verify:
			print("-- 6b/7 check integrity")
			ok = f.verify(base, size, crc)
			print("  verify    : %s" % ("OK" if ok else "MISMATCH"))
			if not ok:
				die("CRC 复核失败")

		if not a.no_reset:
			print("-- 7/7 ecu reset")
			f.reset()
			print("  复位后 boot 应该跳 slot %s" % SLOT_NAME[target])
		else:
			print("-- 7/7 skipped (--no-reset)")

	finally:
		bus.shutdown()

	print("\n完成。串口应打印：")
	print('  [boot] active slot : %s (rolling counter)' % SLOT_NAME[target])
	print('  [boot] jump to slot %s  base=0x%06X' % (SLOT_NAME[target], base))


if __name__ == "__main__":
	main()
