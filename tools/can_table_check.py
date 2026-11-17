#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    can_table_check.py
@brief   校验 `Can.json` 与 `Can_Cfg.c` 的邮箱表 / HTH 表逐字段等价

@details 这个脚本存在的原因是 **生成器自己说自己对不算证据**。

          02.6 的迁移要求"与现有手写配置逐项等价"，所以比对必须独立于生成器：
          它解析的是 `Can_Cfg.c` 的**最终文本**（不管这些字节是手写的还是生成的），
          与 `Can.json` 对账。于是它同时能证明两件事：

          | 阶段 | 跑一次 check 证明 |
          |------|-------------------|
          | 迁移前（C 仍手写） | JSON 忠实反映了现状 —— 迁移没漏条目、没抄错数 |
          | 迁移后（C 由生成器写） | 生成物与 JSON 一致 —— 生成器没写错 |

@note    刻意不做"文本 diff"：手写表用 `CAN_HW_ID_PF_EB` 宏、生成物用 `0x18EB0000u`，
          文本必然不同。**要等价的是字段值，不是字节**。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：邮箱表 + HTH 表 |
"""

import io
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

from can_table_dump import (CFG_C, HWCFG_H, load_macros, parse_hohs,  # noqa: E402
                            parse_table, strip_comments)

CAN_JSON = os.environ.get("LIKEAS_CAN_JSON") or os.path.join(
	ROOT, "app", "platform", "cvm0146", "src", "config", "Can", "Can.json")

PASS = 0
FAIL = 0


def check(ok, what, detail=""):
	global PASS, FAIL
	if ok:
		PASS += 1
		print("  [ OK ] %s" % what)
	else:
		FAIL += 1
		print("  [FAIL] %s%s" % (what, ("  <- " + detail) if detail else ""))


def c_side():
	"""解析 `Can_Cfg.c` 的当前内容，返回 (两张邮箱表, HTH 表)。"""
	macros = load_macros(HWCFG_H)
	text = strip_comments(io.open(CFG_C, encoding="utf-8", errors="replace").read())
	return (parse_table(text, "CanHw_MsgCfgs0[", macros),
	        parse_table(text, "CanHw_MsgCfgs1[", macros),
	        parse_hohs(text, macros))


def main():
	with io.open(CAN_JSON, encoding="utf-8") as f:
		cfg = json.load(f)

	c0, c1, hohs_c = c_side()

	print("== 邮箱表：Can.json vs Can_Cfg.c ==")
	for ch, ctab in ((0, c0), (1, c1)):
		jtab = [e for c in cfg["channels"] if c["index"] == ch for e in c["mailboxes"]]
		jmap = {e["mb"]: e for e in jtab}
		cmap = {e["mb"]: e for e in ctab}

		check(set(jmap) == set(cmap),
		      "CAN%d 邮箱号集合一致" % ch,
		      "仅 JSON %s / 仅 C %s" % (sorted(set(jmap) - set(cmap)),
		                                sorted(set(cmap) - set(jmap))))

		for mb in sorted(set(jmap) & set(cmap)):
			j, c = jmap[mb], cmap[mb]
			want = {
				"id":   int(j["id"], 0),
				"ext":  bool(j["ext"]),
				"dir":  j["dir"],
				"len":  j.get("len", 1),
				"dlc":  j.get("dlc", 8),
				"int":  bool(j.get("int", True)),
				"mask": int(j["mask"], 0) if "mask" in j
				        else (0xFFFFFFFF if j["dir"] == "RX" else 0),
			}
			bad = {k: (c[k], v) for k, v in want.items() if c[k] != v}
			check(not bad, "CAN%d mb%-2u %-12s 字段一致" % (ch, mb, j.get("name", "")),
			      "; ".join("%s: C=%r JSON=%r" % (k, a, b) for k, (a, b) in bad.items()))

	print("\n== HTH 表：Can.json vs Can_Cfg.c ==")
	jh = []
	for c in cfg["channels"]:
		for e in c["mailboxes"]:
			if e["dir"] == "TX":
				jh.append((e["hth"], c["index"], e["mb"], int(e["id"], 0),
				           e.get("dlc", 8)))
	jh.sort()
	ch_ = [(h["hth"], h["controller"], h["mb"], h["id"], h["dlc"]) for h in hohs_c]

	check(len(jh) == len(ch_), "HTH 条目数一致", "JSON %d / C %d" % (len(jh), len(ch_)))
	for a, b in zip(jh, ch_):
		check(a == b, "HTH%-2u 一致（CAN%u mb%u 0x%X）" % (a[0], a[1], a[2], a[3]),
		      "C=%r" % (b,))

	print("\n== 交叉校验 ==")
	# 1) 每条 txPdus 都要有一个对应的 TX 邮箱（按短名匹配 name 的后缀）
	tx_names = {e.get("name", "") for c in cfg["channels"] for e in c["mailboxes"]
	            if e["dir"] == "TX"}
	for t in cfg.get("txPdus", []):
		want = "TX_" + t["short"]
		check(want in tx_names, "txPdus %-12s 有对应 TX 邮箱 %s" % (t["dbc"], want),
		      "现有 TX 邮箱：%s" % sorted(tx_names))

	# 2) CAN1 的 RX 段邮箱带的 pf 标签，必须覆盖 sync_canif 需要的全部 PF
	pfs = {e["pf"] for c in cfg["channels"] if c["index"] == 1
	       for e in c["mailboxes"] if "pf" in e}
	check(len(pfs) == 7, "CAN1 RX 段 PF 标签 7 个", str(sorted(pfs)))

	# 3) Can_HwCfg.h 里仍存在的 ID 宏，值必须与 JSON 对应条目一致
	macros = load_macros(HWCFG_H)
	id_by_name = {}
	for c in cfg["channels"]:
		for e in c["mailboxes"]:
			id_by_name[e.get("name", "")] = int(e["id"], 0)
	mismatch = []
	for name, cid in id_by_name.items():
		macro = "CAN_HW_ID_" + name
		if macro in macros and macros[macro] != cid:
			mismatch.append("%s: 宏 0x%X / JSON 0x%X" % (macro, macros[macro], cid))
	check(not mismatch, "Can_HwCfg.h 的 ID 宏与 JSON 不冲突", "; ".join(mismatch))

	# 4) CAN_HW_HOH_NUM 必须等于 TX 邮箱条数。偏大不会报错——数组尾部补 0，
	#    而 0 条目正好是 {ctrl0, mb0, id0}，等于把 HTH0 覆盖成空邮箱。
	n_tx = sum(1 for c in cfg["channels"] for e in c["mailboxes"] if e["dir"] == "TX")
	import re as _re
	m = _re.search(r"#define\s+CAN_HW_HOH_NUM\s+\((\d+)u?\)",
	               io.open(HWCFG_H, encoding="utf-8", errors="replace").read())
	check(m is not None and int(m.group(1)) == n_tx,
	      "CAN_HW_HOH_NUM == TX 邮箱数（%d）" % n_tx,
	      "宏里写的是 %s" % (m.group(1) if m else "找不到"))

	print("\n%d passed, %d failed" % (PASS, FAIL))
	return 0 if FAIL == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
