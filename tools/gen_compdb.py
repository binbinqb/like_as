#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""生成 compile_commands.json，给 clangd / VSCode C++ 插件做全工程索引。

为什么需要它：
	本工程按 as-master 的 AC 分层组织 —— `infras/mcal/Port/Port.c` 只声明
	`PortAc_PinInit()`，实现在 `app/platform/cvm0146/src/PortAc.c`。
	这是**链接期绑定**（`U` 找 `T`），语义上"跳转"本来就只能到声明，
	所以靠 IDE 的 F12 会让人以为"代码不全"。

	有了 compile_commands.json，clangd 会索引整个工程：
	  - **Find all references** 能列出定义处与所有调用点（这是真正好用的那个功能）
	  - 补全、类型检查、宏展开都准确（包括 USE_PORT 这类平台宏）
	  - 悬停能看到宏展开后的真实代码

做法：
	SCons 没有现成的 compilation_db 可用（env 是在各个 Library/Application 里
	单独创建的，不在 DefaultEnvironment 上），所以走 `scons -n --verbose`
	打印出真实编译命令，再解析成 JSON。这也是 `compiledb` 这类工具的通用做法。

用法：
	python tools/gen_compdb.py              # 生成到仓库根
	python tools/gen_compdb.py --out d.json

	生成后 VSCode 里装 clangd 扩展即可；若报 "stdint.h not found"，
	见同目录 .clangd 里的 --query-driver 说明。

@author binbina
"""

import argparse
import json
import os
import re
import shlex
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# 匹配一行完整编译命令（gcc 路径 + 参数 + 末尾的 .c）
RE_CMD = re.compile(r"^(.+arm-none-eabi-gcc(?:\.exe)?)\s+(.+)$")
RE_SRC = re.compile(r"(\S+\.c)$")


def _scons(args, timeout=600):
	"""跑一次 scons，返回 stdout+stderr。"""
	env = dict(os.environ)
	env.setdefault("ARMGCC", r"C:\soft\gcc\10.3.1")
	env.setdefault("ARMGCC_VERSION", "10.3.1")
	cmd = [sys.executable, "-m", "SCons"] + args
	p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True,
					   env=env, timeout=timeout, stdin=subprocess.DEVNULL)
	return p.returncode, p.stdout + p.stderr


def run_scons(app, cpl):
	"""拿全部编译命令。

	⚠ 必须先清理再 dry-run：`scons -n` 只打印**将要执行**的动作，
	工程已经 up-to-date 时一条编译命令都不会打印（实测输出只有 1.8 KB 的
	"done building" 提示）。所以这里做三步：清理 → dry-run 抓命令 → 重建。
	`scons -c` 只删 build/ 下的产物，不碰源码。
	"""
	base = ["--app=%s" % app, "--cpl=%s" % cpl]

	sys.stderr.write("  [1/3] 清理构建产物 ...\n")
	_scons(base + ["-c"])

	sys.stderr.write("  [2/3] dry-run 抓编译命令 ...\n")
	_, out = _scons(base + ["-n", "--verbose"])

	sys.stderr.write("  [3/3] 重新构建（约 40 s）...\n")
	_scons(base)

	return out


def parse(text):
	"""从 scons -n --verbose 的输出里抽编译命令。"""
	entries = []
	for line in text.splitlines():
		line = line.strip()
		if "-c" not in line or not line.endswith(".c"):
			continue
		m = RE_CMD.match(line)
		if not m:
			continue
		rest = m.group(2)

		src = RE_SRC.search(rest)
		if not src:
			continue
		rel = src.group(1).replace("\\", "/")
		abs_src = os.path.normpath(os.path.join(ROOT, rel))

		entries.append({
			"directory": ROOT,
			# clangd 用 command 做真实解析，原样保留（含 -D/-I/--specs 等）
			"command": line,
			"file": abs_src,
		})
	return entries


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--app", default="App")
	ap.add_argument("--cpl", default="CM4GCC")
	ap.add_argument("--out", default=os.path.join(ROOT, "compile_commands.json"))
	a = ap.parse_args()

	out = run_scons(a.app, a.cpl)
	entries = parse(out)
	if not entries:
		raise SystemExit("没解析到编译命令。先确认 `build.bat` 能正常构建。")

	# 去重（同一文件可能在多个 variant_dir 里出现）
	seen = {}
	for e in entries:
		seen[e["file"]] = e
	entries = sorted(seen.values(), key=lambda x: x["file"])

	with open(a.out, "w", encoding="utf-8") as fh:
		json.dump(entries, fh, ensure_ascii=False, indent=1)

	print("已生成 %s" % a.out)
	print("  条目 %d 个（去重后）" % len(entries))

	# 抽两条看看路径是否合理，便于排查
	for e in entries[:3]:
		print("  - %s" % os.path.relpath(e["file"], ROOT).replace("\\", "/"))


if __name__ == "__main__":
	sys.exit(main())
