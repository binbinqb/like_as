#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""A1 调度唯一性静态检查（不需要硬件、不需要编译）。

验收门槛 A1：每一个 BSW 的 `*_MainFunction()` 在一个 10 ms 周期里
**只能被调用一次**。这条不成立时，所有时间相关的测试结论都不可信 ——
定时器按"每次调用递减一次"实现，调用两次 = 所有超时时间减半。

查三个方向，缺一不可：

	正向（重复调度）
		出现在调度表里的模块，不得再被 `main.c` 的 `main()` 直接调用。
		历史事故：CanTp / Dcm / NvM / Dem 各被调两次，S3 标称 5 s 实际
		2.5 s，而"静默 6.5 s 看是否掉会话"的测试**依然是绿的** ——
		它只断言掉没掉，不断言何时掉。

	反向（漏调度）
		定义了 `*_MainFunction()` 的模块必须有人调。历史事故：
		- `Com_MainFunction_Fast` 从未被调用 → `bTxRetry` 无人推进，
		  `PduR_ComTransmit` 失败一次后该报文永远停在"发过一次"；
		- `CanTp_MainFunction_Fast` 从未被调用 → `CANTP_RESEND_CF`
		  是死状态，TX 邮箱满时刷写直接失败（`CanTp.c:1119` 是
		  `CanTp_ReSend()` 的唯一内部调用点）。

	调用点登记
		非 `main.c` 的已注册模块调用必须落在白名单里。白名单只收
		**阻塞等待型**（同一处驱动同一模块、外部有超时兜底），
		按 `(文件, 所在函数)` 精确匹配 —— 不按函数名放行，否则同文件
		新增一处周期调用会被静默放过。

关于"定义了但不需要调用"的模块：不靠猜，用 `KNOWN_UNUSED` 显式登记，
每项必须写清原因和**复核条件**（什么改动之后必须回来重新看）。
登记项在报告里出 `WARN` 而不是 `PASS` —— 它们是"已知的缺口或取舍"，
不是"检查通过"。

用法：
	python tools/a1_sched_check.py            # 结论
	python tools/a1_sched_check.py -v         # 附全部调用点

退出码：0 = 无 FAIL；1 = 有 FAIL。

@author binbina
"""

import argparse
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# 调度表定义处（注册点，唯一允许出现被调度模块名的地方）
# - EcuM_Cfg.c：BSW 主函数表（A1 原始范围）
# - GEN/Rte_Schedule.h：应用 runnable 调度表（10.5，Board.json 生成）——
#   注册进去后，正向检查同样管住"应用 runnable 被写回 main.c 直接调"
SCHED_TABLES = [
	"app/app/src/EcuM_Cfg.c",
	"app/platform/cvm0146/src/config/Board/GEN/Rte_Schedule.h",
]

# 各注册点的表体模式：捕获组 1 = 表体文本
SCHED_PATTERNS = [
	re.compile(r"EcuM_DriverMain\w*List\[\]\s*=\s*\{(.*?)\n\};", re.S),
	re.compile(r"#define RTE_SCHEDULE_LIST \{(.*?)\n\}", re.S),
]

# 主循环文件 —— 这里的直接调用与调度表叠加即为重复调度
MAIN_FILE = "app/app/src/main.c"

# 允许的"等待型"调用：(相对路径, 所在函数)
# 收取条件：处于有超时的阻塞循环里，目的是推进同一模块，不是周期调度。
WAIT_LOOP_OK = {
	("app/app/src/can_test.c", "CanTest_Burst"),          # burst 期间推进存储，否则作业卡 1 s
	("app/app/src/storage_app.c", "Storage_WaitIdle"),    # 等空闲必须自己驱动引擎
	("app/app/src/ecum_callout.c", "EcuM_MemoryService"),  # 服务型，EcuM_EnsureMemoryIdle 用
	("app/boot/src/main.c", "Boot_NvmWaitIdle"),          # boot 的存储等待，同上
	("app/boot/src/main.c", "Boot_NvmRead"),              # boot 读块时轮询作业完成
	("app/boot/src/main.c", "Boot_UdsLoop"),              # boot 是阻塞式诊断循环，不走 EcuM 表
}

# 定义了 `*_MainFunction()` 但本工程不需要周期调用的模块。
# 第三项为告警级别："warn" = 已知缺口/配置矛盾；"ok" = 条件编译下为空，无害。
#
# ★ 改 CanIf / CanTp 的配置后必须回来重看这张表。
KNOWN_UNUSED = {
	"CanIf_MainFunction": (
		"warn",
		"`USE_CANSM` 全工程未定义 → `CanIf_MainFunction_TxTimeout()` 被预处理裁掉，"
		"函数体只剩 DET_VALIDATE。这是**配置矛盾**：GEN 的 CanIf_Cfg.h:60 已定义 "
		"`CANIF_USE_TX_TIMEOUT`，但没人定义 `USE_CANSM`，故 TX 超时监控整体缺失。"
		"复核条件：开 `USE_CANSM` 后须把它加进调度表，并核对 CanIf 结构体布局"
		"（CanIf_Priv.h:50/61 的字段随宏增减，会让 CanIf_Cfg.c 初始化错位）。",
	),
	"CanIf_MainFunction_Fast": (
		"ok",
		"`CANIF_RX_PACKET_POOL_SIZE` / `CANIF_TX_PACKET_POOL_SIZE` 均为 0"
		"（CanIf_Cfg.h:273/277），函数体只剩 DET_VALIDATE。"
		"复核条件：任一 pool 改为 >0 后必须加进调度表，否则收包永不投递。",
	),
}

RE_FUNC_DEF = re.compile(
	r"^\s*(?:static\s+)?"
	r"(?:void|bool|boolean|int|char|size_t|Std_ReturnType|"
	r"[us]?int(?:8|16|32|64)_t|MemIf_\w+|EcuM_\w+|NvM_\w+|Dem_\w+)\s+\**(\w+)\s*\(")
RE_MAIN_CALL = re.compile(r"\b(\w+_MainFunction(?:_Fast)?)\s*\(")


def read(rel):
	path = os.path.join(ROOT, rel)
	with io.open(path, encoding="utf-8", errors="replace") as f:
		return f.read().replace("\r\n", "\n").split("\n")


def walk(roots, ext):
	out = []
	for root in roots:
		base = os.path.join(ROOT, root)
		if not os.path.isdir(base):
			continue
		for dirpath, _dirnames, filenames in os.walk(base):
			if os.sep + "build" + os.sep in dirpath + os.sep:
				continue
			for fn in filenames:
				if fn.endswith(ext):
					out.append(os.path.relpath(os.path.join(dirpath, fn), ROOT).replace(os.sep, "/"))
	return sorted(out)


def parse_registered():
	"""从调度表里取出所有非 NULL 的注册项（表里还有 NULL 占位）。"""
	registered = set()
	for rel in SCHED_TABLES:
		text = "\n".join(read(rel))
		for pat in SCHED_PATTERNS:
			for m in pat.finditer(text):
				registered |= set(re.findall(r"\b(\w+_MainFunction(?:_Fast)?)\b", m.group(1)))
	return registered


def parse_definitions():
	"""找出 infras/ 里定义了 `*_MainFunction` 的模块（真 BSW 模块）。

	只认 infras/ 下的定义：app/ 下的 `BcmSig_MainFunction` 是应用层周期
	函数，本来就不该进 BSW 调度表，不能算"漏调度"。
	"""
	defs = {}
	for rel in walk(["infras"], ".c"):
		lines = read(rel)
		for i, ln in enumerate(lines):
			m = RE_FUNC_DEF.match(ln)
			if not m:
				continue
			name = m.group(1)
			if not re.match(r"\w+_MainFunction(_Fast)?$", name):
				continue
			if "{" not in "\n".join(lines[i:i + 4]):   # 排除纯声明
				continue
			defs[name] = (rel, i + 1)
	return defs


def parse_calls():
	"""收集全部调用点，带（文件、行号、所在函数）。"""
	calls = []
	for rel in walk(["app", "infras"], ".c"):
		lines = read(rel)
		cur = "<file-scope>"
		for i, ln in enumerate(lines):
			m = RE_FUNC_DEF.match(ln)
			if m:
				cur = m.group(1)
			s = ln.lstrip()
			# 注释里大量提到函数名，整行跳过可避免绝大多数误判
			if s.startswith("*") or s.startswith("/*") or s.startswith("//"):
				continue
			for cm in RE_MAIN_CALL.finditer(ln):
				name = cm.group(1)
				if m and m.group(1) == name:   # 定义行不是调用
					continue
				calls.append({"file": rel, "line": i + 1, "func": cur, "name": name})
	return calls


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("-v", "--verbose", action="store_true", help="列出全部调用点")
	args = ap.parse_args()

	registered = parse_registered()
	defs = parse_definitions()
	calls = parse_calls()

	warns = []

	def warn(msg):
		warns.append(msg)
		print("  WARN  " + msg)

	def fail(msg):
		print("  FAIL  " + msg)

	fails = []

	print("=" * 74)
	print("A1 调度唯一性静态检查")
	print("=" * 74)
	print("调度表注册 %d 项：%s" % (len(registered), ", ".join(sorted(registered))))
	print("infras 定义的 MainFunction %d 个" % len(defs))

	# ---------- 正向：注册过的不得在 main() 里再直接被调 ----------
	print("\n--- 正向：重复调度 ---")
	n = 0
	for c in calls:
		if c["name"] in registered and c["file"] == MAIN_FILE:
			n += 1
			fails.append("重复调度：%s 已注册，又被 %s:%d (%s) 直接调用"
			             % (c["name"], c["file"], c["line"], c["func"]))
	if n == 0:
		print("  PASS  %s 无已注册模块的直接调用" % MAIN_FILE)
	else:
		for f in fails:
			fail(f)

	# ---------- 反向：定义了必须有归属（注册 或 调用） ----------
	print("\n--- 反向：漏调度 ---")
	missing = 0
	for name, (rel, line) in sorted(defs.items()):
		if name in registered:
			continue
		if [c for c in calls if c["name"] == name]:
			continue
		if name in KNOWN_UNUSED:
			level, why = KNOWN_UNUSED[name]
			msg = "%s 无人调用 —— %s" % (name, why)
			if level == "warn":
				warn(msg)
			else:
				print("  PASS  %s 无需调用（条件编译下为空）" % name)
			continue
		missing += 1
		fails.append("漏调度：%s（定义于 %s:%d）找不到任何调用点，且未登记豁免"
		             % (name, rel, line))
		fail(fails[-1])
	if missing == 0:
		print("  PASS  所有需要的 MainFunction 都有归属")

	# ---------- 调用点登记：非 main.c 的调用必须在白名单内 ----------
	# Host 测试目录整体豁免：测试驱动器**本来就要**直接驱动被测模块
	# （按拍推进 BcmSig / IoHwAb / AdcSampler 制造确定性场景），
	# 不是固件调度，登记它没有意义 —— 固件调度只在 app/ 与 boot/ 的
	# 生产源码里，那才是 A1 要管的对象。
	print("\n--- 调用点登记 ---")
	extra = [c for c in calls
	         if c["name"] in registered
	         and c["file"] != MAIN_FILE
	         and not c["file"].startswith("app/platform/host/")
	         and (c["file"], c["func"]) not in WAIT_LOOP_OK]
	if not extra:
		print("  PASS  非 main.c 的已注册模块调用全部落在白名单内")
	else:
		for c in extra:
			fails.append("未登记调用点 %s:%d (%s) 调 %s"
			             % (c["file"], c["line"], c["func"], c["name"]))
			fail(fails[-1])

	if args.verbose:
		print("\n--- 全部已注册模块的调用点 ---")
		for c in calls:
			if c["name"] in registered:
				wl = "白名单" if (c["file"], c["func"]) in WAIT_LOOP_OK else "      "
				print("  [%s] %-40s:%-5d %-22s <- %s"
				      % (wl, c["file"], c["line"], c["name"], c["func"]))

	print("\n" + "=" * 74)
	if fails:
		print("A1 FAIL  (%d 项)" % len(fails))
		return 1
	if warns:
		print("A1 PASS（附 %d 条 WARN，需人工确认）" % len(warns))
	else:
		print("A1 PASS  调度唯一：%d 个模块各 1 处周期调用，0 漏调度" % len(registered))
	return 0


if __name__ == "__main__":
	sys.exit(main())
