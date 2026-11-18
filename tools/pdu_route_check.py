#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""PduR 路由表逐项核对：50 条路径的模块 / 句柄 / API / 索引。

## 为什么需要它

`PduR_Cfg.c` 的三张表是**按宏值下标对齐**的扁平数组：

	PduR_SrcPdu[PDUR_xxx]       发起方端点
	PduR_DstPdu[PDUR_xxx][1]    目的方端点（1 对 1）
	PduR_RoutingPaths[PDUR_xxx] 把上面两组指针绑在一起

`config.py check-pdu` 只保证"宏值不重复、索引不越界"。但**语义**仍然靠人：

- Src 的 `module` 与 `api` 表是否一致（写成 `PDUR_MODULE_COM` 却挂 `&PduR_CanIfApi`，
  编得过、跑起来调错函数）；
- TX 路径的 **Dest 句柄必须是 CanIf 的 PDU 号**，RX 路径的 **Dest 句柄必须是
  Com 的 IPdu 下标** —— 两套编号同形不同义，填错不报错、只表现为"发不出/解错包"。

本脚本把这三件事变成断言。它只读源码与配置，不编译、不上板。

## 检查项

| # | 断言 |
|---|---|
| C1 | 三张表条目数 == `PDUR_NUM_ROUTING_PATHS` == 宏个数 |
| C2 | 宏值覆盖 0..N-1，无空洞、无重复 |
| C3 | 每条路径 Src/Dst 的 `module` 与所挂 `&PduR_*Api` 一致 |
| C4 | 诊断/NM 前 6 条（0~5）的 Src/Dst 模块与句柄固定语义 |
| C5 | TX 路径：Src 句柄 == Com 的 `COM_<suffix>`，Dest 句柄 == CanIf 的 TX PDU 号 |
| C6 | RX 路径：Dest 句柄 == Com 的 `COM_<suffix>` |
| C7 | `PduR.json` 的 manualPaths 两条：句柄与配置里写的宏一致 |
| C8 | `RoutingPaths[i]` 引用的两个宏值都等于 i |

用法：
	python tools/pdu_route_check.py
	python tools/pdu_route_check.py --verbose

@author binbina
"""

import argparse
import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
PDUR_C = os.path.join(CFG, "PduR_Cfg.c")
PDUR_H = os.path.join(CFG, "PduR_Cfg.h")
COM_H = os.path.join(CFG, "Com_Cfg.h")
CANIF_H = os.path.join(CFG, "CanIf_Cfg.h")
CAN_JSON = os.path.join(CFG, "Can", "Can.json")
PDUR_JSON = os.path.join(CFG, "PduR", "PduR.json")

# module 枚举 → 该模块必须挂的 API 表名
API_OF_MODULE = {
	"PDUR_MODULE_CANTP": "PduR_CanTpApi",
	"PDUR_MODULE_DCM": "PduR_DcmApi",
	"PDUR_MODULE_CANIF": "PduR_CanIfApi",
	"PDUR_MODULE_CANNM": "PduR_CanNmApi",
	"PDUR_MODULE_COM": "PduR_ComApi",
}

# 诊断/NM 固定语义：(src_module, src_h, dst_module, dst_h)
FIXED_PATHS = {
	0: ("PDUR_MODULE_CANTP", 0, "PDUR_MODULE_DCM", 0),
	1: ("PDUR_MODULE_DCM", 0, "PDUR_MODULE_CANTP", 0),
	2: ("PDUR_MODULE_CANIF", 0, "PDUR_MODULE_CANTP", 0),
	3: ("PDUR_MODULE_CANTP", 0, "PDUR_MODULE_CANIF", 0),
	4: ("PDUR_MODULE_CANIF", 0, "PDUR_MODULE_CANNM", 0),
	5: ("PDUR_MODULE_CANNM", 0, "PDUR_MODULE_CANIF", 0),
}

results = []


def check(name, ok, detail=""):
	results.append((name, ok, detail))


def read(path):
	with io.open(path, encoding="utf-8") as f:
		return f.read()


def macros(path, prefix):
	"""读 `#define NAME (12u)` / `(12u)` / `12` 两种写法。"""
	out = {}
	pat = re.compile(r"^#define\s+(%s\w*)\s+\(?(\d+)u?\)?\s*$" % re.escape(prefix), re.M)
	for m in pat.finditer(read(path)):
		out[m.group(1)] = int(m.group(2))
	return out


def region(text, anchor):
	"""取 `anchor` 起始到下一个 `};` 之间的文本。"""
	i = text.index(anchor)
	j = text.index("\n};", i)
	return text[i:j]


def parse_src(text):
	"""SrcPdu：每项三个字段（module, handle, api）。"""
	reg = region(text, "static const PduR_PduType PduR_SrcPdu[")
	pat = re.compile(
		r"\{\s*(PDUR_MODULE_\w+)\s*,\s*(\(PduIdType\))?\s*([A-Za-z_]\w*|\d+u?)\s*,"
		r"\s*&(PduR_\w+Api)\s*\}")
	return [(m.group(1), m.group(3), m.group(4)) for m in pat.finditer(reg)]


def parse_dst(text):
	"""DstPdu：`{ { module, handle, api } },`"""
	reg = region(text, "static const PduR_PduType PduR_DstPdu[")
	pat = re.compile(
		r"\{\s*\{\s*(PDUR_MODULE_\w+)\s*,\s*(\(PduIdType\))?\s*([A-Za-z_]\w*|\d+u?)\s*,"
		r"\s*&(PduR_\w+Api)\s*\}\s*\}")
	return [(m.group(1), m.group(3), m.group(4)) for m in pat.finditer(reg)]


def parse_paths(text):
	"""RoutingPaths：每项里的 SrcPdu[...] / DstPdu[...] 宏名。"""
	reg = region(text, "static const PduR_RoutingPathType PduR_RoutingPaths[")
	blocks = reg.split("\t{")[1:]
	out = []
	for b in blocks:
		ms = re.search(r"&PduR_SrcPdu\[(\w+)\]", b)
		md = re.search(r"PduR_DstPdu\[(\w+)\]", b)
		if ms and md:
			out.append((ms.group(1), md.group(1)))
	return out


def resolve(expr, tables):
	"""把句柄表达式解析成整数。"""
	expr = expr.strip()
	if expr.endswith("u"):
		expr = expr[:-1]
	if expr.isdigit():
		return int(expr)
	for t in tables:
		if expr in t:
			return t[expr]
	return None


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--verbose", action="store_true", help="打印每条路径")
	a = ap.parse_args()

	text = read(PDUR_C)
	hdr = macros(PDUR_H, "PDUR_")
	com = macros(COM_H, "COM_")
	canif = macros(CANIF_H, "CANIF_")
	tables = (hdr, com, canif)

	src = parse_src(text)
	dst = parse_dst(text)
	paths = parse_paths(text)

	# 路径宏 = 除三个"计数/汇总"宏以外的 PDUR_*。
	# ⚠ 不能只按前缀筛：`PDUR_MANUAL_PATHS` 的值恰好也是 8，会把路径 8
	# （`PDUR_CAN1_BCM_LCSF_TX`）从反查表里挤掉，表现为"6 条 TX 只查到 5 条"。
	COUNTERS = ("PDUR_MANUAL_PATHS", "PDUR_CAN1_PATHS", "PDUR_NUM_ROUTING_PATHS")
	path_macros = {k: v for k, v in hdr.items()
	               if k.startswith("PDUR_") and k not in COUNTERS}
	n_macro = len(path_macros)
	n_total = hdr.get("PDUR_NUM_ROUTING_PATHS")
	if n_total is None:
		n_total = hdr.get("PDUR_MANUAL_PATHS", 0) + hdr.get("PDUR_CAN1_PATHS", 0)

	print("== PduR 路由表核对 ==")
	print("  宏 %d 个 / SrcPdu %d / DstPdu %d / RoutingPaths %d / 总数宏 %d"
	      % (n_macro, len(src), len(dst), len(paths), n_total))

	check("C1 三张表条目数与总数宏一致",
	      len(src) == len(dst) == len(paths) == n_total == n_macro,
	      "src=%d dst=%d paths=%d num=%s macro=%d"
	      % (len(src), len(dst), len(paths), n_total, n_macro))

	# 条目数不对时，后面的逐条断言没有意义：直接收工。
	# 曾在这里吃过 IndexError（注入缺陷把一条记录改坏），栈会盖掉"到底哪条坏了"的信息。
	if len(src) != len(dst):
		print("\n  表长不一致，跳过逐条核对")
		for name, ok, detail in results:
			print("  [%s] %s" % ("PASS" if ok else "FAIL", name))
		print("-- %d 项断言，1 项失败" % (len(results) + 1))
		return 1

	# C2：路径宏值覆盖 0..N-1
	path_ids = sorted(path_macros.values())
	check("C2 宏值覆盖 0..N-1 无空洞无重复",
	      path_ids == list(range(n_total)),
	      "缺失=%s 重复=%s"
	      % ([i for i in range(n_total) if i not in path_ids],
	         [v for v in set(path_ids) if path_ids.count(v) > 1]))

	# 反查：宏值 → 名字（只用路径宏，避免计数宏撞值）
	id2name = {}
	for k, v in path_macros.items():
		id2name.setdefault(v, []).append(k)

	# C3：module ↔ api
	bad = []
	for i, (mod, h, api) in enumerate(src):
		if API_OF_MODULE.get(mod) != api:
			bad.append("path%d src %s/%s" % (i, mod, api))
	for i, (mod, h, api) in enumerate(dst):
		if API_OF_MODULE.get(mod) != api:
			bad.append("path%d dst %s/%s" % (i, mod, api))
	check("C3 每条路径 module 与 &PduR_*Api 一致", not bad, "; ".join(bad[:4]))

	# C4：前 6 条固定语义
	bad = []
	for i, exp in FIXED_PATHS.items():
		if i >= len(src):
			bad.append("path%d 缺失" % i)
			continue
		smod, sh, dmod, dh = exp
		if src[i][0] != smod or resolve(src[i][1], tables) != sh:
			bad.append("path%d src %s/%s ≠ %s/%d"
			           % (i, src[i][0], src[i][1], smod, sh))
		if dst[i][0] != dmod or resolve(dst[i][1], tables) != dh:
			bad.append("path%d dst %s/%s ≠ %s/%d"
			           % (i, dst[i][0], dst[i][1], dmod, dh))
	check("C4 诊断/NM 六条路径语义固定", not bad, "; ".join(bad[:4]))

	# C5/C6：来自 Can.json 的 TX 清单与 Com/CanIf 宏对账
	with io.open(CAN_JSON, encoding="utf-8") as f:
		can_cfg = json.load(f)
	mbox_tx = {}
	for ch in can_cfg["channels"]:
		for e in ch["mailboxes"]:
			if e["dir"] == "TX" and "canIfMacro" in e:
				mbox_tx[e["name"]] = e["canIfMacro"]

	# PduR 宏 → 邮箱短名 的唯一映射在 `txPdus` 里：宏名来自 DBC 报文名
	# （`BCM_Ctrl` → `BCM_CTRL`），邮箱短名是工程约定（`CTRL`），两者不能机械互推。
	pdur2short = {}
	for e in can_cfg.get("txPdus", []):
		pdur2short[e["pdurMacro"]] = e["short"]

	bad_tx, bad_rx, checked_tx, checked_rx = [], [], 0, 0
	for i in range(n_total):
		name = id2name.get(i, ["?"])[0]
		if not name.startswith("PDUR_CAN1_"):
			continue
		suffix = name[len("PDUR_"):]          # CAN1_XXX_TX / CAN1_XXX_RX
		want_com = com.get("COM_" + suffix)
		if name.endswith("_TX"):
			checked_tx += 1
			# Src 必须是 Com 的该 IPdu
			if src[i][0] != "PDUR_MODULE_COM" or resolve(src[i][1], tables) != want_com:
				bad_tx.append("%d Src %s/%s ≠ COM/%s"
				              % (i, src[i][0], src[i][1], want_com))
			# Dest 必须是 CanIf 的 TX PDU（宏值按 Can.json 邮箱表配对）
			short = pdur2short.get(name)
			canif_macro = mbox_tx.get("TX_" + short) if short else None
			want_canif = canif.get(canif_macro) if canif_macro else None
			if short is None:
				bad_tx.append("%d %s 不在 txPdus 里" % (i, name))
			elif canif_macro is None:
				bad_tx.append("%d 找不到邮箱 TX_%s" % (i, short))
			elif dst[i][0] != "PDUR_MODULE_CANIF" or resolve(dst[i][1], tables) != want_canif:
				bad_tx.append("%d Dst %s/%s ≠ %s(%s)"
				              % (i, dst[i][0], dst[i][1], canif_macro, want_canif))
		else:
			checked_rx += 1
			if dst[i][0] != "PDUR_MODULE_COM" or resolve(dst[i][1], tables) != want_com:
				bad_rx.append("%d Dst %s/%s ≠ COM/%s"
				              % (i, dst[i][0], dst[i][1], want_com))
		if a.verbose:
			print("  %2d %-40s src=%s/%-24s dst=%s/%s"
			      % (i, name, src[i][0], src[i][1], dst[i][0], dst[i][1]))

	check("C5 CAN1 TX 路径：Src=Com 句柄、Dest=CanIf PDU 号（%d 条）" % checked_tx,
	      not bad_tx, "; ".join(bad_tx[:4]))
	check("C6 CAN1 RX 路径：Dest=Com IPdu 下标（%d 条）" % checked_rx,
	      not bad_rx, "; ".join(bad_rx[:4]))

	# C7：manualPaths 两条
	with io.open(PDUR_JSON, encoding="utf-8") as f:
		pcfg = json.load(f)
	manual = pcfg["networks"][0].get("manualPaths", {})
	bad = []
	for e in manual.get("tx", []):
		mid = hdr.get(e["path"])
		if mid is None:
			bad.append("%s 未定义" % e["path"])
			continue
		if src[mid][0] != "PDUR_MODULE_COM" or resolve(src[mid][1], tables) != com.get(e["com"]):
			bad.append("%s Src ≠ %s" % (e["path"], e["com"]))
		exp = canif.get(e["canIf"]) if e.get("canIf") else None
		if exp is None or dst[mid][0] != "PDUR_MODULE_CANIF" or resolve(dst[mid][1], tables) != exp:
			bad.append("%s Dst ≠ %s" % (e["path"], e.get("canIf")))
	for e in manual.get("rx", []):
		mid = hdr.get(e["path"])
		if mid is None:
			bad.append("%s 未定义" % e["path"])
			continue
		if dst[mid][0] != "PDUR_MODULE_COM" or resolve(dst[mid][1], tables) != com.get(e["com"]):
			bad.append("%s Dst ≠ %s" % (e["path"], e["com"]))
	check("C7 manualPaths 句柄与 PduR.json 一致（%d 条）"
	      % (len(manual.get("tx", [])) + len(manual.get("rx", []))),
	      not bad, "; ".join(bad[:4]))

	# C8：RoutingPaths[i] 引用的宏值 == i
	bad = []
	for i, (ms, md) in enumerate(paths):
		vs = hdr.get(ms)
		vd = hdr.get(md)
		if vs != i or vd != i:
			bad.append("paths[%d] → %s(%s)/%s(%s)" % (i, ms, vs, md, vd))
	check("C8 RoutingPaths 下标与引用宏值一致", not bad, "; ".join(bad[:4]))

	# ---- 汇总 ----
	print()
	fail = 0
	for name, ok, detail in results:
		print("  [%s] %s" % ("PASS" if ok else "FAIL", name))
		if not ok:
			print("         %s" % detail)
			fail += 1
	print("-- %d 项断言，%d 项失败" % (len(results), fail))
	return 1 if fail else 0


if __name__ == "__main__":
	sys.exit(main())
