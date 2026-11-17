#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    hardcode_check.py
@brief   02.5 的守卫：项目参数不许再写回通用脚本

@details @section HC_WHY 为什么要专门写个检查
         `PF_TO_MB` / `TX_MAP` / `ID_BASE` / `"BCM"` 这些常量已经从
         `sync_canif.py` / `sync_pdur.py` 搬进 `config/Can/Can.json`。
         但"搬走"和"不会再搬回来"是两件事：下一个人加一条发送报文时，
         最省事的做法就是在脚本里再写一个 dict。

         这个脚本做两件事：

         1. **字面量守卫**：通用脚本里出现"数字常量表"或写死的节点名 → 失败
         2. **配置与产物对账**：`Can.json` 里列的每个宏必须在生成头文件里真实存在
            （防止 JSON 与生成物脱节，那比没有配置更糟）

@note    测试脚本（`*_check.py`、`m*.py`）允许出现项目常量：它们本来就是
         针对这个项目的期望值，不是通用工具。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：字面量守卫 + 宏存在性对账 |
"""

import io
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
CAN_JSON = os.path.join(CFG, "Can", "Can.json")

#: 通用工具：这些文件里不许出现项目常量
GUARDED = [
	"tools/sync_canif.py",
	"tools/sync_pdur.py",
]

PASS = 0
FAIL = 0


def check(cond, what, detail=""):
	global PASS, FAIL
	if cond:
		PASS += 1
		print("  PASS  %s" % what)
	else:
		FAIL += 1
		print("  FAIL  %s   %s" % (what, detail))


def read(rel):
	with io.open(os.path.join(ROOT, rel), encoding="utf-8") as f:
		return f.read()


def main():
	print("== 02.5 硬编码守卫 ==")

	# 1) 字面量守卫
	bad = []
	for rel in GUARDED:
		s = read(rel)
		# 数字键的字典 = 项目映射表（允许从 JSON 推导的推导式）
		if re.search(r"PF_TO_MB\s*=\s*\{\s*(0x[0-9A-Fa-f]+|\d+)\s*:", s):
			bad.append((rel, "PF_TO_MB 数字表"))
		if re.search(r"ID_BASE\s*=\s*\d+", s):
			bad.append((rel, "ID_BASE 数字常量"))
		if re.search(r'"BCM"', s):
			bad.append((rel, "写死节点名 BCM"))
		if re.search(r"CANIF_TX_MAP\s*=\s*\{\s*\"", s):
			bad.append((rel, "CANIF_TX_MAP 字面表"))

	check(not bad, "通用脚本无项目常量",
	      "；".join("%s:%s" % x for x in bad))

	# 2) Can.json 结构
	if not os.path.isfile(CAN_JSON):
		check(False, "Can.json 存在", CAN_JSON)
		print("\n%d passed, %d failed" % (PASS, FAIL))
		return 1

	cfg = json.load(io.open(CAN_JSON, encoding="utf-8"))
	for key in ("canIfPduIdBase", "pdurIdBase", "txPdus", "channels"):
		check(key in cfg, "Can.json 含 %s" % key)

	# 3) 宏存在性：JSON 说的名字必须真在生成头里
	canif_h = read("app/platform/cvm0146/src/config/CanIf_Cfg.h")
	pdur_h = read("app/platform/cvm0146/src/config/PduR_Cfg.h")
	miss = []
	for e in cfg.get("txPdus", []):
		if ("#define %s" % e["canIfMacro"]) not in canif_h:
			miss.append(e["canIfMacro"])
		if ("#define %s" % e["pdurMacro"]) not in pdur_h:
			miss.append(e["pdurMacro"])
	check(not miss, "txPdus 的宏都在生成头里", ", ".join(miss))

	# 4) 邮箱号必须真实存在于 Can_Cfg.c 的邮箱表
	can_c = read("app/platform/cvm0146/src/config/Can_Cfg.c")
	miss_mb = []
	# PF 标签的邮箱号必须在 Can_Cfg.c 的 CAN1 邮箱表里真实存在
	pf_mbs = [(e["pf"], e["mb"]) for c in cfg.get("channels", []) if c.get("index") == 1
	          for e in c["mailboxes"] if "pf" in e]
	miss_mb = ["%s->mb%d" % (pf, mb) for pf, mb in pf_mbs
	           if not re.search(r"\{\s*%du,.*?CAN_HW_MB_RX" % mb, can_c)]
	check(not miss_mb, "PF 标签的邮箱号都在 Can_Cfg.c 的 CAN1 表里", ", ".join(miss_mb))
	check(len(pf_mbs) == 7, "CAN1 有 7 个 PF 段邮箱", str(len(pf_mbs)))

	# 5) 波特率唯一来源：Can_Cfg 不许再有自己的一份 define
	can_h = read("app/platform/cvm0146/src/config/Can_Cfg.h")
	can_c = read("app/platform/cvm0146/src/config/Can_Cfg.c")
	check("#define CAN_CFG_BAUDRATE" not in can_h, "Can_Cfg.h 无重复波特率定义")
	check("BOARD_CAN0_BITRATE" in can_c and "BOARD_CAN1_BITRATE" in can_c,
	      "Can_Cfg.c 使用 Board.json 生成的波特率")

	print("\n%d passed, %d failed" % (PASS, FAIL))
	return 0 if FAIL == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
