#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    host_build.py
@brief   Host（PC）最小构建：把业务源码编成可执行文件并跑用例

@details @section HOSTBUILD_WHY 为什么不直接接 SCons
         building.py 的 `--cpl=MSVC` 对宿主编译器会强制追加 `Det` 库
         （`Application.__init__`：`IsBuildForHost()` 为真就 `LIBS += ["Det"]`），
         而 Host 应用到目前**不需要** DET，也不想为了它把整个 infras 拖进来。
         与其改公共构建脚本，不如先用一个 60 行的独立驱动把 26.1 跑通：
         判据是"同一份业务代码能在 PC 上编过并跑出预期"，不是"构建方式统一"。

         接 SCons 留给 02.7（生成幂等与 SCons 集成），那时再决定是给
         Host 应用单独开一个 compiler，还是让 Det 成为可选。

@note    编译器按优先级自动选：PATH 上的 gcc → MSVC（vcvars64.bat）。
         两个都没有就报错退出，不静默跳过——"测试没跑"必须显式。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：gcc/MSVC 双路径，编译 + 运行一体 |
"""

import glob
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT_DIR = os.path.join(ROOT, "build", "host")
EXE = os.path.join(OUT_DIR, "bcm_host_test.exe")

# 业务源码：**就是目标板上编的那几个文件**，一个字符都不改。
# 将来接 RTE，这里加 rte_*.c 即可；不要为了 Host 复制一份"能编的版本"，
# 那样测试和被交付的代码就是两份，等于没测。
SRCS = [
	"app/app/src/bcm_sig.c",
	"app/app/src/bcm_sig_cfg.c",
	"app/app/src/bcm_biz.c",
	"app/app/src/rx_mon.c",
]
SRCS += [p for p in sorted(glob.glob(os.path.join(ROOT, "app/platform/host/src/*.c")))]
SRCS += ["app/platform/host/test/test_bcm.c"]

INCLUDES = [
	"app/include",
	"app/app/src",
	"app/platform/host/include",
	"infras/include",
	"app/platform/cvm0146/src/config",
	"app/platform/cvm0146/src/config/CanIf",
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


def find_vcvars():
	"""定位 vcvars64.bat（VS 2017~2026 的目录结构都兼容）。"""
	patterns = [
		r"C:/Program Files*/Microsoft Visual Studio/*/*/VC/Auxiliary/Build/vcvars64.bat",
		r"C:/Program Files (x86)/Microsoft Visual Studio/*/*/VC/Auxiliary/Build/vcvars64.bat",
	]
	for pat in patterns:
		hits = glob.glob(pat)
		if hits:
			return hits[-1]
	return None


def run(cmd, cwd=ROOT, shell=False):
	"""跑一条命令并把输出直接透传给调用者（不被缓冲吞掉）。"""
	print("+ " + (cmd if isinstance(cmd, str) else " ".join(cmd)))
	proc = subprocess.run(cmd, cwd=cwd, shell=shell)
	return proc.returncode


def build_gcc(gcc):
	srcs = [os.path.join(ROOT, s) for s in SRCS]
	inc = []
	for i in INCLUDES:
		inc += ["-I", os.path.join(ROOT, i)]
	cmd = [gcc] + CFLAGS_COMMON + inc + srcs + ["-o", EXE]
	return run(cmd)


def build_msvc(vcvars):
	srcs = [os.path.join(ROOT, s).replace("/", "\\") for s in SRCS]
	inc = []
	for i in INCLUDES:
		inc.append("/I" + os.path.join(ROOT, i).replace("/", "\\"))
	# /utf-8：源码是 UTF-8 中文注释，不加会被按 GBK 解出 C4819
	cl = ["cl", "/nologo", "/std:c11", "/utf-8", "/W3",
	      "/Fe:" + EXE.replace("/", "\\"), "/Fd:" + OUT_DIR.replace("/", "\\") + "\\"] + inc + srcs

	# 必须写成批处理再执行：vcvars64.bat 内部是
	#   @call "%~dp0vcvarsall.bat" x64 %*
	# 直接用 `cmd /c call "..." && cl ...` 时嵌套引号会被 cmd 拆坏，
	# 报 '"...vcvarsall.bat"' 不是内部或外部命令（实测两次）。
	bat = os.path.join(OUT_DIR, "_build.bat")
	with open(bat, "w", encoding="ascii", newline="\r\n") as f:
		f.write("@echo off\r\n")
		f.write('call "%s" >nul\r\n' % vcvars.replace("/", "\\"))
		f.write("if errorlevel 1 exit /b 1\r\n")
		# ⚠ 只对路径做反斜杠转换，**不能**把整条命令行 replace("/", "\\") ——
		#   那样会把 cl 的 `/nologo` `/std:c11` 一起改成 `\nologo`（第一次就这么踩的）。
		f.write(subprocess.list2cmdline(cl) + "\r\n")
		f.write("exit /b %ERRORLEVEL%\r\n")

	return run(["cmd", "/c", bat])


def msvc_env_manual():
	"""在 vcvarsall.bat 缺失时，手工拼出 cl 需要的 PATH/INCLUDE/LIB。

	这台机器的 VS 安装不完整：`VC/Auxiliary/Build/` 下只有 vcvars64.bat
	和 vcvarsamd64_x86.bat，**没有它们要调用的 vcvarsall.bat**，所以
	`call vcvars64.bat` 必然失败。cl.exe 与 Windows SDK 都是齐的，
	只要把三条环境变量拼对就能编。
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
	# 连 cl 的绝对路径一起返回：subprocess 用 env=PATH 找可执行文件不可靠
	# （Windows 上 CreateProcess 的搜索路径未必读子进程 env），直接给全路径最稳。
	return env, cl


def build_msvc_manual(env, cl):
	srcs = [os.path.join(ROOT, s) for s in SRCS]
	inc = []
	for i in INCLUDES:
		inc.append("/I" + os.path.join(ROOT, i))
	cmd = [cl, "/nologo", "/std:c11", "/utf-8", "/W3",
	       "/Fe:" + EXE, "/Fd:" + OUT_DIR + "\\"] + inc + srcs
	print("+ cl (manual env)")
	return subprocess.run(cmd, cwd=ROOT, env=env).returncode


def main():
	os.makedirs(OUT_DIR, exist_ok=True)

	gcc = find_gcc()
	vcvars = find_vcvars()
	# vcvars64.bat 只有在同目录下还有 vcvarsall.bat 时才能用（它是前者唯一的依赖）。
	# 这台机器的 VS 装漏了 vcvarsall.bat，走手工环境变量分支。
	has_vcvars = bool(vcvars) and os.path.isfile(
		os.path.join(os.path.dirname(vcvars), "vcvarsall.bat"))

	if gcc:
		rc = build_gcc(gcc)
	elif has_vcvars:
		rc = build_msvc(vcvars)
	else:
		found = msvc_env_manual()
		if found is None:
			print("[ERROR] 找不到宿主编译器：PATH 上没有 gcc，也没有可用的 MSVC")
			return 2
		rc = build_msvc_manual(found[0], found[1])

	if rc != 0:
		print("[ERROR] 编译失败，rc=%d" % rc)
		return rc

	if not os.path.isfile(EXE):
		print("[ERROR] 编译返回 0 但没有产物：%s" % EXE)
		return 3

	return run([EXE])


if __name__ == "__main__":
	sys.exit(main())
