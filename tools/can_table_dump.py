#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    can_table_dump.py
@brief   把 `Can_Cfg.c` 里手写的邮箱表 / HTH 表解析成结构化 JSON

@details 用途有两个，顺序不能反：

          1. **迁移工具**：02.6 要把手写表搬进 `Can.json`。手抄 30 条 × 8 字段
             必然出错，而错一个字节的表现是"某条报文收不到"——上板才发现。
             所以从 C 源码机械提取，人只负责核对语义。
          2. **等价性判据**：`can_table_check.py` 用它解析**生成后**的
             `Can_Cfg.c`，与 `Can.json` 逐字段比对。生成器写错了，
             这里必须报出来（而不是生成器自己说自己对）。

@note    宏展开用的是本文件内置的表，不是 C 预处理器：`Can_Cfg.c` 的条目里
          只出现 `CAN_HW_*` 这一族数值宏和两个方向枚举，范围可控。
          真接了预处理器反而会把 SDK 头全展进来，输出几千行没法比。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：邮箱表 + HTH 表提取 |
"""

import io
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
# 允许指向别处：自测脚本用临时副本构造"有缺陷的配置"来证明判据能抓到问题。
CFG = os.environ.get("LIKEAS_CAN_CFG_DIR") or os.path.join(
	ROOT, "app", "platform", "cvm0146", "src", "config")
HWCFG_H = os.path.join(CFG, "Can_HwCfg.h")
CFG_C = os.path.join(CFG, "Can_Cfg.c")

#: 方向枚举 → 字符串（`CanHw_MbDirType` 的成员，不是宏）
DIRS = {"CAN_HW_MB_TX": "TX", "CAN_HW_MB_RX": "RX"}


def strip_comments(text):
	"""去掉 `/* */` 与 `//`，保留字符串字面量里的内容（本文件没有字符串，从简）。"""
	text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
	text = re.sub(r"//[^\n]*", " ", text)
	return text


def load_macros(path):
	"""从 `Can_HwCfg.h` 收集 `#define CAN_HW_* (数值)` 与 `#define CAN_CFG_*`。"""
	out = {}
	if not os.path.isfile(path):
		return out
	text = strip_comments(io.open(path, encoding="utf-8", errors="replace").read())
	for m in re.finditer(r"#define\s+([A-Z][A-Z0-9_]*)\s+\(?\s*(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*\)?", text):
		out[m.group(1)] = int(m.group(2), 0)
	return out


def expand(token, macros):
	"""把一个字段文本变成整数：支持宏、十进制/十六进制字面量、`0u` 后缀。"""
	token = token.strip()
	# 先查宏表再剥后缀：宏名本身可能以 L 结尾（`CAN_HW_ID_TX_CTRL`），
	# 无条件 rstrip("uUlL") 会把它变成 `CAN_HW_ID_TX_CTR`（踩过）。
	if token in macros:
		return macros[token]
	token = token.rstrip("uUlL")
	if token in DIRS:
		# 方向字段不走这里（调用方单独判），走到这说明表结构变了
		raise KeyError("方向枚举出现在数值位置：%s" % token)
	if re.fullmatch(r"0[xX][0-9A-Fa-f]+", token) or re.fullmatch(r"\d+", token):
		return int(token, 0)
	raise KeyError("无法展开的字段：%r" % token)


def expand_bool(token):
	token = token.strip()
	if token in ("true", "TRUE", "1", "1u"):
		return True
	if token in ("false", "FALSE", "0", "0u"):
		return False
	raise KeyError("无法判定的布尔值：%r" % token)


def split_fields(body):
	"""按顶层逗号切分一个 `{...}` 的内容（这里没有嵌套花括号，但保留括号深度判断）。"""
	fields, depth, cur = [], 0, []
	for ch in body:
		if ch == "(":
			depth += 1
		elif ch == ")":
			depth -= 1
		if ch == "," and depth == 0:
			fields.append("".join(cur).strip())
			cur = []
		else:
			cur.append(ch)
	if "".join(cur).strip():
		fields.append("".join(cur).strip())
	return fields


def parse_table(text, name, macros):
	"""解析 `static const CanHw_MsgCfgType <name>[] = { ... };` 的每个条目。"""
	i = text.find(name)
	if i < 0:
		raise SystemExit("找不到表：%s" % name)
	i = text.find("{", i)
	j = text.find("};", i)
	if 0 < i < j:
		body = text[i + 1:j]
	else:
		raise SystemExit("表 %s 的花括号不配对" % name)

	rows = []
	# 每个条目是一对花括号；用非贪婪匹配到 `}` 后跟逗号或空白
	for m in re.finditer(r"\{([^{}]*)\}", body, re.S):
		f = split_fields(m.group(1))
		if len(f) != 8:
			raise SystemExit("表 %s 有 %d 个字段的条目（应为 8）：%s"
			                 % (name, len(f), m.group(1).strip()[:60]))
		rows.append({
			"mb":         expand(f[0], macros),
			"len":        expand(f[1], macros),
			"id":         expand(f[2], macros),
			"ext":        expand_bool(f[3]),
			"dir":        DIRS[f[4].strip()],
			"dlc":        expand(f[5], macros),
			"int":        expand_bool(f[6]),
			"mask":       expand(f[7], macros),
		})
	return rows


def parse_hohs(text, macros):
	"""解析 `const CanHw_HohType CanHw_Hohs[...] = { ... };`，顺序即 HTH 编号。"""
	i = text.find("CanHw_Hohs[")
	i = text.find("{", i)
	j = text.find("};", i)
	body = text[i + 1:j]
	rows = []
	for m in re.finditer(r"\{([^{}]*)\}", body, re.S):
		f = split_fields(m.group(1))
		if len(f) != 4:
			raise SystemExit("HOH 条目字段数 %d（应为 4）" % len(f))
		rows.append({
			"hth":        len(rows),
			"controller": expand(f[0], macros),
			"mb":         expand(f[1], macros),
			"id":         expand(f[2], macros),
			"dlc":        expand(f[3], macros),
		})
	return rows


def dump():
	macros = load_macros(HWCFG_H)
	text = strip_comments(io.open(CFG_C, encoding="utf-8", errors="replace").read())

	ch0 = parse_table(text, "CanHw_MsgCfgs0[", macros)
	ch1 = parse_table(text, "CanHw_MsgCfgs1[", macros)
	hohs = parse_hohs(text, macros)

	# HTH 反挂到对应通道的邮箱条目上（生成侧要写成同一个 JSON）
	for h in hohs:
		tbl = ch0 if h["controller"] == 0 else ch1
		hit = [r for r in tbl if r["mb"] == h["mb"] and r["dir"] == "TX"]
		if len(hit) != 1:
			raise SystemExit("HTH%d 指向 ctrl%d mb%d，但表里有 %d 条匹配的 TX 邮箱"
			                 % (h["hth"], h["controller"], h["mb"], len(hit)))
		if hit[0]["id"] != h["id"]:
			raise SystemExit("HTH%d 的 ID 0x%X 与邮箱 mb%d 的 0x%X 不一致"
			                 % (h["hth"], h["id"], h["mb"], hit[0]["id"]))
		hit[0]["hth"] = h["hth"]

	return {
		"source": os.path.relpath(CFG_C, ROOT).replace("\\", "/"),
		"channels": [
			{"index": 0, "mailboxes": ch0},
			{"index": 1, "mailboxes": ch1},
		],
	}


def main():
	data = dump()
	out = json.dumps(data, ensure_ascii=False, indent=1)
	if "--out" in sys.argv:
		p = sys.argv[sys.argv.index("--out") + 1]
		io.open(p, "w", encoding="utf-8", newline="\n").write(out + "\n")
		print("wrote %s" % p)
	else:
		print(out)
	return 0


if __name__ == "__main__":
	sys.exit(main())
