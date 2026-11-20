#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    host_build.py
@brief   Host（PC）最小构建：把业务源码编成可执行文件并跑用例

@details @section HOSTBUILD_WHY 为什么不直接接 SCons
         building.py 的 `--cpl=MSVC` 对宿主编译器会强制追加 `Det` 库
         （`Application.__init__`：`IsBuildForHost()` 为真就 `LIBS += ["Det"]`），
         而 Host 应用到目前**不需要** DET，也不想为了它把整个 infras 拖进来。
         与其改公共构建脚本，不如先用一个独立驱动把 26.1 跑通：
         判据是"同一份业务代码能在 PC 上编过并跑出预期"，不是"构建方式统一"。

         接 SCons 留给 02.7（生成幂等与 SCons 集成），那时再决定是给
         Host 应用单独开一个 compiler，还是让 Det 成为可选。

@note    每个用例是**独立可执行文件**（各自一个 main、各自一份全局状态），
         不是一个进程里跑多个 suite：BcmSig / RTE 都有静态影子，
         同进程连续跑会互相污染，且失败时定位成本高得多。

@author  binbina
@version V0.2.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：gcc/MSVC 双路径，编译 + 运行一体 |
| V0.2.0 | 2026-11-17 | binbina | 拆成多用例（bcm / rte），各自独立可执行 |
"""

import glob
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT_DIR = os.path.join(ROOT, "build", "host")

# 业务与运行时源码：**就是目标板上编的那几个文件**，一个字符都不改。
# 将来新增业务模块在这里加；不要为了 Host 复制一份"能编的版本"，
# 那样测试和被交付的代码就是两份，等于没测。
APP_SRCS = [
	"app/app/src/bcm_sig.c",
	"app/app/src/bcm_sig_cfg.c",
	"app/app/src/bcm_biz.c",
	"app/app/src/rx_mon.c",
	"app/app/src/rte.c",
	"app/app/src/rte_cfg.c",
	# RTE 的 DIN/AIN/DOUT 端口直接走 IoHwAb，Host 侧用内存后端
	"app/app/src/iohwab.c",
	"app/platform/host/test/iohwab_host_ops.c",
	"app/platform/cvm0146/src/config/Board/GEN/IoHwAb_Cfg.c",
]

HOST_SRCS = sorted(glob.glob(os.path.join(ROOT, "app/platform/host/src/*.c")))

# (名称, 用例源文件, 附加源, 附加头文件目录, 附加 -D)
# 每个用例单独一个可执行文件；附加源/目录为空表示"用根目录的 APP_SRCS + HOST_SRCS"。
BOOT_SRCS = [
	"app/platform/cvm0146/src/BootMeta.c",
	"app/boot/src/boot_choice.c",
	"app/platform/host/test/boot_sim_flash.c",
	"infras/libraries/crc/src/Crc_32.c",
]
BOOT_INCS = ["app/platform/host/include/boot_sim", "app/platform/cvm0146/include", "app/boot/include"]

TESTS = [
	("bcm", "app/platform/host/test/test_bcm.c", [], [], []),
	("rte", "app/platform/host/test/test_rte.c", [], [], []),
	# 22.3 元数据/校验：真编译 BootMeta.c + 假 Flash
	("boot_meta", "app/platform/host/test/test_boot_meta.c", BOOT_SRCS, BOOT_INCS, []),
	# 22.3 选槽判定：同一份 boot_choice.c 编两次，分别验开发/量产策略
	("boot_dev", "app/platform/host/test/test_boot_choice.c", BOOT_SRCS, BOOT_INCS,
	 ["-DBOOT_MODE_PRODUCTION=0"]),
	("boot_prod", "app/platform/host/test/test_boot_choice.c", BOOT_SRCS, BOOT_INCS,
	 ["-DBOOT_MODE_PRODUCTION=1"]),
	# IoHwAb V1.0：Core 与目标板编同一份源码，后端换成内存模拟。
	# 依赖 Board 生成物（IoHwAb_Cfg.c），先跑一次 build 或 tools/config.py gen。
	("iohwab", "app/platform/host/test/test_iohwab.c",
	 ["app/app/src/iohwab.c",
	  "app/platform/host/test/iohwab_host_ops.c",
	  "app/platform/cvm0146/src/config/Board/GEN/IoHwAb_Cfg.c"],
	 ["app/platform/cvm0146/src/config/Board/GEN"], []),
	# ADC 采样调度：完成才发布/超时丢弃，Host 替身模拟转换延迟
	("adc_sampler", "app/platform/host/test/test_adc_sampler.c",
	 ["app/app/src/adc_sampler.c",
	  "app/platform/host/test/adc_sampler_host_ops.c"],
	 [], []),
	# MuxManager：状态机与 IoHwAb 胶水一起编，Host 替身模拟 ABC/COM/ADC 时序
	("mux", "app/platform/host/test/test_mux.c",
	 ["app/app/src/mux.c",
	  "app/app/src/iohwab_mux.c",
	  "app/platform/host/test/mux_host_ops.c"],
	 [], []),
	# 10.5 runnable 调度表：真实配置（Board.json rte.schedule）驱动替身 runnable，
	# 验证顺序与分频；多周期/变体配置在 tools/rte_sched_check.py
	("sched", "app/platform/host/test/test_sched.c",
	 ["app/app/src/rte_sched.c"],
	 ["app/platform/cvm0146/src/config/Board/GEN"], []),
]

# 这些用例**不**套用 APP_SRCS + HOST_SRCS：它们验证的是与宿主平台无关的
# 纯判定逻辑，源码集合由 TESTS 的第 3 项显式给出。
STANDALONE_TESTS = {"boot_meta", "boot_dev", "boot_prod", "iohwab", "mux", "adc_sampler", "sched"}

INCLUDES = [
	"app/include",
	"app/app/src",
	"app/platform/host/include",
	"infras/include",
	"app/platform/cvm0146/src/config",
	"app/platform/cvm0146/src/config/CanIf",
	# 生成的端口表 / 通道枚举（Rte_Ports.h、IoHwAb_Cfg.h）
	"app/platform/cvm0146/src/config/Board/GEN",
]

CFLAGS_COMMON = ["-std=c99", "-Wall", "-Wextra"]

# 宿主编译器候选路径：先 PATH，再本机约定目录。
# `C:/soft/mingw64` 与 `C:/soft/gcc/10.3.1`（ARM）放在一起，属于"工具链统一放
# C:/soft"的项目约定；不写进系统 PATH 也能用，避免影响其它工程的 gcc 选择。
GCC_CANDIDATES = [
	r"C:/soft/mingw64/bin/gcc.exe",
]


def find_gcc():
	"""返回可用的宿主编译器路径；没有返回 None。"""
	g = shutil.which("gcc")
	if g:
		return g
	for c in GCC_CANDIDATES:
		if os.path.isfile(c):
			return c
	return None


def run(cmd, cwd=ROOT, env=None):
	"""跑一条命令并把输出直接透传给调用者（不被缓冲吞掉）。"""
	print("+ " + (cmd if isinstance(cmd, str) else " ".join(cmd)))
	return subprocess.run(cmd, cwd=cwd, env=env).returncode


def build_gcc(gcc, srcs, exe, extra_incs=None, extra_defs=None):
	inc = []
	# 附加头文件目录排在**最前**：`boot_sim/platform_cvm0146.h` 要能遮蔽
	# 同名真实平台头，否则 Host 会去 include 厂商 SDK。
	for i in (extra_incs or []):
		inc += ["-I", os.path.join(ROOT, i)]
	for i in INCLUDES:
		inc += ["-I", os.path.join(ROOT, i)]
	cmd = [gcc] + CFLAGS_COMMON + inc + list(extra_defs or []) + srcs + ["-o", exe]
	return run(cmd)


def msvc_env_manual():
	"""在 vcvarsall.bat 缺失时，手工拼出 cl 需要的 PATH/INCLUDE/LIB。

	部分 VS 安装只有编译器二进制：`VC/Auxiliary/Build/` 下没有
	`vcvarsall.bat`，`VC/Tools/MSVC/<ver>/include` 也可能不存在。
	两者任一缺失都判不可用 —— 硬编下去只会在 `#include <stdint.h>` 处失败，
	报错信息离真正原因很远。
	"""
	cls = sorted(glob.glob(
		r"C:/Program Files*/Microsoft Visual Studio/*/*/VC/Tools/MSVC/*/bin/Hostx64/x64/cl.exe"))
	sdk_inc = sorted(glob.glob(r"C:/Program Files (x86)/Windows Kits/10/Include/*"))
	sdk_lib = sorted(glob.glob(r"C:/Program Files (x86)/Windows Kits/10/Lib/*"))
	if not cls or not sdk_inc or not sdk_lib:
		return None

	cl = cls[-1]
	vc_root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(cl))))
	inc_root = sdk_inc[-1]
	lib_root = sdk_lib[-1]

	# vcruntime.h 在 VC/Tools/MSVC/<ver>/include 下；没有这个目录说明只装了
	# 编译器、没装 C++ 工作负载（本机就是这样）。
	if not os.path.isdir(os.path.join(vc_root, "include")):
		return None

	env = dict(os.environ)
	env["PATH"] = os.path.dirname(cl) + os.pathsep + env.get("PATH", "")
	env["INCLUDE"] = os.pathsep.join([
		os.path.join(vc_root, "include"),
		os.path.join(inc_root, "ucrt"),
		os.path.join(inc_root, "shared"),
		os.path.join(inc_root, "um"),
	])
	env["LIB"] = os.pathsep.join([
		os.path.join(vc_root, "lib", "x64"),
		os.path.join(lib_root, "ucrt", "x64"),
		os.path.join(lib_root, "um", "x64"),
	])
	return env, cl


def build_msvc_manual(env, cl, srcs, exe, extra_incs=None, extra_defs=None):
	inc = []
	for i in (extra_incs or []):
		inc.append("/I" + os.path.join(ROOT, i))
	for i in INCLUDES:
		inc.append("/I" + os.path.join(ROOT, i))
	cmd = [cl, "/nologo", "/std:c11", "/utf-8", "/W3",
	       "/Fe:" + exe, "/Fd:" + OUT_DIR + "\\"] + inc
	cmd += [("/D" + d[2:]) if d.startswith("-D") else d for d in (extra_defs or [])]
	cmd += srcs
	print("+ cl (manual env)")
	return subprocess.run(cmd, cwd=ROOT, env=env).returncode


def build_and_run(gcc, msvc, name, test_src, extra_srcs=None, extra_incs=None, extra_defs=None):
	exe = os.path.join(OUT_DIR, "%s_test.exe" % name)
	if name in STANDALONE_TESTS:
		# 独立用例：源码集合完全由 TESTS 决定（见那里的注释）
		srcs = [os.path.join(ROOT, s) for s in (extra_srcs or [])]
	else:
		srcs = [os.path.join(ROOT, s) for s in APP_SRCS] + HOST_SRCS
		srcs += [os.path.join(ROOT, s) for s in (extra_srcs or [])]
	srcs.append(os.path.join(ROOT, test_src))

	print("\n=== build %s ===" % name)
	if gcc:
		rc = build_gcc(gcc, srcs, exe, extra_incs, extra_defs)
	else:
		rc = build_msvc_manual(msvc[0], msvc[1], srcs, exe, extra_incs, extra_defs)

	if rc != 0:
		print("[ERROR] %s 编译失败，rc=%d" % (name, rc))
		return rc
	if not os.path.isfile(exe):
		print("[ERROR] %s 返回 0 但没有产物：%s" % (name, exe))
		return 3

	print("--- run %s ---" % name)
	return run([exe])


def main():
	os.makedirs(OUT_DIR, exist_ok=True)

	gcc = find_gcc()
	msvc = None if gcc else msvc_env_manual()
	if (not gcc) and (msvc is None):
		print("[ERROR] 找不到宿主编译器：PATH 上没有 gcc，也没有可用的 MSVC")
		return 2

	bad = 0
	for name, src, extra_srcs, extra_incs, extra_defs in TESTS:
		rc = build_and_run(gcc, msvc, name, src, extra_srcs, extra_incs, extra_defs)
		if rc != 0:
			bad += 1
			print("[FAIL] %s rc=%d" % (name, rc))

	print("\n== %d/%d suites passed ==" % (len(TESTS) - bad, len(TESTS)))
	return 0 if bad == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
