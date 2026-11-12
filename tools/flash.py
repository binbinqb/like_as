#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""烧写 CVM0146（Flash）—— 走 IAR CSpyBat + J-Link，与 Bcm_Frame 台架同一路径。

为什么不用 J-Link 直接 loadfile：
	本机 J-Link 安装目录缺 `Devices/CVA_BLUE_WHALE/`，内置 CVM0146 条目的 FLM
	路径落空（报 "Error while loading flash algo ELF file"）。IAR 自带同一套
	FLM + DDF，CSpyBat 能正常烧写 —— 这也是 Bcm_Frame `scripts/bench/probe.py`
	已验证的做法，这里把它固化成 H:/as 自己的入口。

做法：
	1) `iarbuild <参考 ewp> -cspybat_cmds Debug -output_type bat` 生成
	   `*.general.xcl` / `*.driver.xcl`（只为拿"器件 + FLM + J-Link 脚本"这组参数，
	   不编译任何 IAR 源码）；
	2) driver.xcl 补 `--jlink_script_file`（IAR 自带的 CVM0146.JLinkScript）；
	3) `CSpyBat --download_only --debug_file=<我们的 ELF>`。

⚠ `--download_only` 只写 Flash，不复位运行；要跑用 `--run`（J-Link r + g）。

用法：
	python tools/flash.py                          # 烧 build/nt/CM4GCC/App/App.exe
	python tools/flash.py --elf <path> --run       # 指定 ELF 并复位运行

@author binbina
"""

import argparse
import glob
import os
import shutil
import subprocess
import sys
import tempfile

IAR = r"C:\iar\ewarm-9.60.3"
CSPYBAT = os.path.join(IAR, "common", "bin", "CSpyBat.exe")
IARBUILD = os.path.join(IAR, "common", "bin", "iarbuild.exe")
JLINK = r"C:\Program Files\SEGGER\JLink\JLink.exe"
JLINK_SCRIPT = os.path.join(IAR, "arm", "bin", "Devices", "CVA_BLUE_WHALE",
							"CVM01xx", "CVM0146.JLinkScript")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# 只用来"借参数"的参考工程：器件 CVM0146、Debug 配置、J-Link 驱动
# ⚠ 指向芯片资料区的厂商原件，不再从本仓库的 refs/ 里取：
#   refs/vendor 下那份是同一套例程的副本，删掉也不影响烧写。
REF_EWP = r"H:\chip-doc\MCU\曦华科技-水木蓝鲸CVM014x\CVA_MCU_SDK_M01xx++IAR" \
          r"\CVA_MCU_SDK_M01xx_2-2\examples\CVM0146\driver_examples" \
          r"\uart_polling_rx_tx\uart_polling_rx_tx.ewp"


def _gen_xcl(tmpdir):
	"""由参考 ewp 生成 cspybat 参数文件，返回 (general.xcl, driver.xcl)。"""
	base = os.path.join(tmpdir, "cspy")
	subprocess.run([IARBUILD, REF_EWP, "-cspybat_cmds", "Debug",
					"-output_type", "bat", "-output", base],
				   check=True, capture_output=True, text=True,
				   timeout=180, stdin=subprocess.DEVNULL)
	gen = glob.glob(os.path.join(tmpdir, "*.general.xcl"))
	drv = glob.glob(os.path.join(tmpdir, "*.driver.xcl"))
	if not gen or not drv:
		raise RuntimeError("cspybat 参数生成失败：找不到 *.general.xcl / *.driver.xcl")
	return gen[0], drv[0]


def flash(elf, tmpdir=None, quiet=True):
	"""把 ELF 写进 Flash。返回 CSpyBat 的 (rc, log)。"""
	tmpdir = tmpdir or tempfile.mkdtemp(prefix="as_flash_")
	gen, drv = _gen_xcl(tmpdir)

	# 驱动参数里补 J-Link 脚本（IAR 生成的 driver.xcl 默认不带）
	text = open(drv, encoding="utf-8", errors="replace").read()
	if "jlink_script_file" not in text:
		text += "\n--jlink_script_file=%s\n" % JLINK_SCRIPT.replace("\\", "/")
		drv_jl = os.path.join(tmpdir, "_drv_jlink.xcl")
		open(drv_jl, "w", encoding="utf-8").write(text)
		drv = drv_jl

	cmd = [CSPYBAT, "-f", gen, "--download_only", "--silent",
		   "--debug_file=%s" % elf, "--backend", "-f", drv]
	p = subprocess.run(cmd, capture_output=True, text=True, timeout=240,
					   stdin=subprocess.DEVNULL)
	log = (p.stdout or "") + (p.stderr or "")
	if not quiet:
		sys.stdout.write(log)
	return p.returncode, log


def reset_run():
	"""复位并运行（不碰 Flash，不需要 FLM）。"""
	script = os.path.join(tempfile.gettempdir(), "_as_run.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nr\ng\nexit\n")
	return subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
						  capture_output=True, text=True, timeout=60,
						  stdin=subprocess.DEVNULL)


# ---- A/B 分区：判断 ELF 链接在哪个槽 + 让另一个槽失效 ----------------------

# 与 app/platform/cvm0146/include/boot_flash_map.h 保持一致。
# 不在 Python 里 include 那个头文件，所以改分区时这两处都要改
# （tools/uds_flash.py 也是同样的做法）。
SLOT_BASE = {"A": 0x00020000, "B": 0x00090000}   # D1：boot 扩到 128 KB 后顺移
SLOT_SIZE = 0x00070000
SLOT_META_SIZE = 0x00001000        # 主备各一个 2 KB 扇区


def elf_link_base(elf):
	"""从 ELF 的 `.interrupts` 段取链接基址（= 镜像所在槽的起始地址）。"""
	out = subprocess.run(["arm-none-eabi-objdump", "-h", elf],
						 capture_output=True, text=True, timeout=60,
						 stdin=subprocess.DEVNULL).stdout
	for line in out.splitlines():
		parts = line.split()
		if len(parts) >= 4 and parts[1] == ".interrupts":
			return int(parts[3], 16)
	return None


def jlink_read_words(addr, count):
	"""用 J-Link Commander 读 Flash/内存里的若干 32 位字，返回列表（失败返回 None）。"""
	script = os.path.join(tempfile.gettempdir(), "_as_read.jlink")
	with open(script, "w", encoding="ascii") as fh:
		fh.write("device Cortex-M4\nsi SWD\nspeed 4000\nconnect\nhalt\n"
				 "mem32 0x%08X, %d\nexit\n" % (addr, count))
	p = subprocess.run([JLINK, "-ExitOnError", "1", "-CommanderScript", script],
					   capture_output=True, text=True, timeout=60,
					   stdin=subprocess.DEVNULL)
	words = []
	for line in p.stdout.splitlines():
		if "=" in line and line.strip().startswith("%08X" % addr):
			for tok in line.split("=", 1)[1].split():
				try:
					words.append(int(tok, 16))
				except ValueError:
					pass
	return words if words else None


def invalidate_slot_meta(slot, tmpdir, quiet=True):
	"""把指定槽的 meta 区**整段写成 0**，让 boot 认为该槽没有有效元数据。

	为什么需要这一步：J-Link/CSpyBat 只写镜像、不动 meta，于是
	"刚烧进去的新镜像"和"meta 里记的旧 rollingCounter"对不上 ——
	boot 仍然会去启动计数更大的那个槽，新固件永远没机会跑。
	症状是"烧写成功、串口输出还是老版本"，极容易误判成编译没生效。

	@warning **必须用 `ld` 生成 ELF，不能用 `objcopy -I binary`。**
	         `objcopy` 造出来的 ELF **没有程序头（PHDR）**，CSpyBat 只按
	         程序头下载，于是它什么都不烧、rc 还返回 0 ——
	         实测踩过：报告"清零成功"，回读 meta 一个字都没变。
	         所以本函数末尾**强制回读校验**，不复信退出码。
"""
	addr = SLOT_BASE[slot] + SLOT_SIZE - SLOT_META_SIZE
	bindir = os.path.join(tmpdir, "meta")
	os.makedirs(bindir, exist_ok=True)

	binpath = os.path.join(bindir, "meta_blank.bin")
	with open(binpath, "wb") as fh:
		fh.write(b"\x00" * SLOT_META_SIZE)

	ldpath = os.path.join(bindir, "meta.ld")
	with open(ldpath, "w", encoding="ascii") as fh:
		fh.write("ENTRY(_start)\nSECTIONS\n{\n  . = 0x%08X;\n  .blob : { *(.data) }\n}\n"
				 % addr)

	elfpath = os.path.join(bindir, "meta_blank.elf")
	subprocess.run(["arm-none-eabi-ld", "-T", ldpath,
					"--oformat", "elf32-littlearm",
					# 默认按 64 KB 页对齐会把 LOAD 段撑成 0xF0000 起、64 KB 长 ——
					# 那会连带擦掉大半个预留区。压到 4 KB 才能精确到单个扇区。
					"-z", "max-page-size=0x1000",
					"-o", elfpath, "-b", "binary", binpath],
				   check=True, capture_output=True, text=True, timeout=60,
				   stdin=subprocess.DEVNULL)

	rc, log = flash(elfpath, tmpdir=tmpdir, quiet=quiet)
	if rc != 0:
		return rc, log, addr

	# 回读校验：meta 区头 8 个字必须全 0，否则视为失败（不让调用方误以为成功）
	words = jlink_read_words(addr, 8)
	if words is None or any(w != 0 for w in words):
		return 1, "verify failed: %s" % ("读不到" if words is None else
										"回读 %s" % " ".join("%08X" % w for w in words)), addr
	return 0, log, addr


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--elf", default=os.path.join(
		ROOT, "build", "nt", "CM4GCC", "App", "App.exe"))
	ap.add_argument("--boot", action="store_true",
					help="先烧 Boot（0x0）再烧 App（A/B 分区首次部署用）")
	ap.add_argument("--run", action="store_true", help="烧完复位运行")
	ap.add_argument("--force", action="store_true",
					help="烧完把**另一个槽**的 meta 清零，保证这次烧的镜像一定会跑。\n"
						 "J-Link 只写镜像不动 meta，不这么做的话 boot 可能仍去启动"
						 "计数更大的旧槽，表现为\"烧写成功但串口还是老版本\"")
	ap.add_argument("--verbose", action="store_true")
	a = ap.parse_args()

	if not os.path.isfile(a.elf):
		raise SystemExit("找不到 ELF：%s（先跑 build.bat）" % a.elf)

	tmpdir = tempfile.mkdtemp(prefix="as_flash_")

	# A/B 分区之后，"能跑起来"需要两个镜像同时在位：
	#   boot 在 0x0（选槽/校验/跳转/刷写服务），app 在 0x20000（slot A）。
	# 只烧 app 会得到一个"没有任何东西负责跳转到它"的板子 —— 上电停在 0x0
	# 的旧 boot（或者干脆是空 Flash，直接 HardFault）。
	# 所以首次部署、或者改过 boot 之后，一律用 --boot。
	if a.boot:
		boot_elf = os.path.join(ROOT, "build", "nt", "CM4GCC", "Boot", "Boot.exe")
		if not os.path.isfile(boot_elf):
			raise SystemExit("找不到 Boot：%s（先跑 build.bat --app=Boot）" % boot_elf)
		rc, log = flash(boot_elf, tmpdir=tmpdir, quiet=not a.verbose)
		print("flash rc=%d  (%s)" % (rc, os.path.basename(boot_elf)))
		for line in log.splitlines():
			if "rror" in line or "FAIL" in line:
				print("  |", line.strip())
		if rc != 0:
			return rc

	rc, log = flash(a.elf, tmpdir=tmpdir, quiet=not a.verbose)
	print("flash rc=%d  (%s)" % (rc, os.path.basename(a.elf)))
	for line in log.splitlines():
		if "rror" in line or "FAIL" in line:
			print("  |", line.strip())
	if rc != 0:
		return rc

	if a.force:
		base = elf_link_base(a.elf)
		slot = None
		for name, b in SLOT_BASE.items():
			if base == b:
				slot = name
				break
		if slot is None:
			print("--force: 无法从 ELF 判断槽位（.interrupts 基址=%s），跳过"
				  % ("?" if base is None else "0x%X" % base))
		else:
			other = "B" if slot == "A" else "A"
			rc2, log2, addr = invalidate_slot_meta(other, tmpdir, quiet=not a.verbose)
			print("invalidate slot %s meta @0x%05X rc=%d  (保证 slot %s 这次一定被选中)"
				  % (other, addr, rc2, slot))
			if rc2 != 0:
				for line in log2.splitlines():
					if "rror" in line or "FAIL" in line:
						print("  |", line.strip())
				return rc2

	if a.run:
		p = reset_run()
		print("reset+run rc=%d" % p.returncode)
	shutil.rmtree(tmpdir, ignore_errors=True)
	return 0


if __name__ == "__main__":
	sys.exit(main())
