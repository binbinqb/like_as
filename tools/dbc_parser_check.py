#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    dbc_parser_check.py
@brief   02.4 的 Parser 判据：标准帧/扩展帧、节点筛选、缓存、异常

@details @section DBCCHK_WHY 为什么不用客户矩阵当输入
         公开仓库不能带 OEM DBC（见 `.gitignore`），所以判据全部跑在
         `tools/tests/fixtures/` 下的**合成 DBC**上：节点名是 ECU_A/B/C，
        信号是编的，与客户数据无关。

         覆盖（编号沿用设计文档 §3.9）：
         DBC-01~06 帧类型与 ID 边界 · 07 非法 ID · 08~11 节点筛选 ·
         12~17 信号属性（Intel/Motorola/有符号/factor/初值/同名信号）·
         18~22 缓存行为 · 23 文件异常 · 24 不支持特性拒绝。
         DBC-25（四模块联合生成）不在这里重复：它由
         `tools/config.py generate` + 产物哈希对比覆盖，见提交说明。

@note    这里**不**验证 CanIf 运行时能否区分"同值不同帧类型"。解析层能给出
         `ext`，但当前 `CanIf_RxPduType` 没有 ext 字段 —— 这是已知边界，
         在 02.4 里只记录不修（改结构体会动到生成物与回归基线）。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：24 条判据 |
"""

import os
import shutil
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
ROOT = os.path.dirname(TOOLS)
FIX = os.path.join(HERE, "tests", "fixtures")
MIXED = os.path.join(FIX, "mixed_can.dbc")

sys.path.insert(0, TOOLS)
from generator.dbc.database import DbcDatabase, classify  # noqa: E402

PASS = 0
FAIL = 0


def check(cond, tag, what, detail=""):
	global PASS, FAIL
	if cond:
		PASS += 1
		print("  PASS  %-7s %s" % (tag, what))
	else:
		FAIL += 1
		print("  FAIL  %-7s %s   %s" % (tag, what, detail))


def raises(fn, tag, what):
	try:
		fn()
	except Exception as e:  # noqa: BLE001  —— 这里就是要"任何异常都算拒绝"
		check(True, tag, what, "")
		return str(e)
	check(False, tag, what, "没有抛异常")
	return ""


def main():
	db = DbcDatabase()
	msgs = db.get_messages(MIXED)
	by = {m["name"]: m for m in msgs}
	print("== DBC Parser 判据：%d 条报文 ==" % len(msgs))

	# ---------- 帧类型与边界 ----------
	check(by["S_123"]["can_id"] == 0x123 and by["S_123"]["ext"] is False,
	      "DBC-01", "标准帧 0x123")
	check(by["S_7FF"]["can_id"] == 0x7FF and by["S_7FF"]["ext"] is False,
	      "DBC-02", "标准帧上边界 0x7FF")
	check(by["E_123"]["can_id"] == 0x123 and by["E_123"]["ext"] is True,
	      "DBC-03", "扩展帧 0x123（数值与标准帧相同）")
	check(by["E_Big"]["can_id"] == 0x18FEF100 and by["E_Big"]["ext"] is True,
	      "DBC-04", "扩展帧 0x18FEF100")
	check(by["E_Max"]["can_id"] == 0x1FFFFFFF and by["E_Max"]["ext"] is True,
	      "DBC-05", "扩展帧上边界 0x1FFFFFFF")
	check(by["S_123"]["can_id"] == by["E_123"]["can_id"]
	      and by["S_123"]["ext"] != by["E_123"]["ext"],
	      "DBC-06", "同数值 ID 靠 ext 区分，不靠 id>0x7FF")
	raises(lambda: db.get_messages(os.path.join(FIX, "invalid_id.dbc")),
	       "DBC-07", "非法 CAN ID 被拒绝")

	# ---------- 节点筛选 ----------
	a = classify(msgs, "ECU_A")
	name_dir = {m["name"]: m["dir"] for m in a}
	check(name_dir.get("S_123") == "TX" and name_dir.get("S_7FF") == "TX",
	      "DBC-08", "发送方是本节点 → TX")
	check(name_dir.get("E_Big") == "RX" and name_dir.get("E_Max") == "RX",
	      "DBC-09", "接收方含本节点 → RX")
	check("E_123" not in name_dir and "Other" not in name_dir,
	      "DBC-10", "与本节点无关的报文被排除")
	both = [m for m in a if m["name"] == "Both"][0]
	check(both["dir"] == "RX" and both["dirSpecified"] is True,
	      "DBC-11", "多接收节点（ECU_A,ECU_B）→ RX")

	# ---------- 信号属性 ----------
	sig = {s["name"]: s for s in by["E_Big"]["signals"]}
	check(sig["Speed"]["endian"] == "little", "DBC-12", "Intel 字节序")
	check(sig["Mot"]["endian"] == "big", "DBC-13", "Motorola 字节序")
	check(sig["Temp"]["sign"] == "-", "DBC-14", "有符号信号")
	check(abs(sig["Speed"]["factor"] - 0.01) < 1e-9 and sig["Speed"]["offset"] == 0,
	      "DBC-15", "Factor / Offset")
	check(sig["Speed"].get("InitialValue") == 1500,
	      "DBC-16", "非零初始值进入 InitialValue")
	s1 = [s for s in by["Both"]["signals"] if s["name"] == "SharedName"][0]
	s2 = [s for s in by["Both2"]["signals"] if s["name"] == "SharedName"][0]
	check(s1.get("InitialValue") == 7 and s2.get("InitialValue") == 9,
	      "DBC-17", "跨报文同名信号不串用", "%r / %r" % (s1.get("InitialValue"), s2.get("InitialValue")))

	# ---------- 缓存 ----------
	db2 = DbcDatabase()
	db2.get_messages(MIXED)
	db2.get_messages(MIXED)
	db2.get_messages(MIXED)
	check(db2.parses == 1 and db2.hits == 2, "DBC-18", "相同内容只解析一次",
	      "parses=%d hits=%d" % (db2.parses, db2.hits))

	# 改内容 → 失效
	tmp = tempfile.mkdtemp(prefix="likeas_dbc_")
	try:
		copy = os.path.join(tmp, "a.dbc")
		shutil.copyfile(MIXED, copy)
		before = db2.parses
		# 用"改一个值"而不是"追加一段"：追加可能落在文件尾的 BA_ 之后，
		# 语法上不合法，测试会因为解析器报错而不是因为缓存失效而"通过"。
		txt = open(copy, encoding="utf-8").read().replace("1500", "1600")
		open(copy, "w", encoding="utf-8", newline="\n").write(txt)
		db2.get_messages(copy)
		check(db2.parses == before + 1, "DBC-19", "内容变化后缓存失效",
		      "parses=%d" % db2.parses)

		# 改返回对象不污染缓存
		m = db2.get_messages(MIXED)
		m[0]["name"] = "MUTATED"
		m2 = db2.get_messages(MIXED)
		check(m2[0]["name"] != "MUTATED", "DBC-20", "修改返回对象不污染缓存")

		# 不同路径、相同内容 → 命中
		same = os.path.join(tmp, "b.dbc")
		shutil.copyfile(MIXED, same)
		before = db2.parses
		db2.get_messages(same)
		check(db2.parses == before, "DBC-21", "不同路径相同内容共享缓存")

		# 顺序无关：新库按相反顺序取，结果一致
		db3 = DbcDatabase()
		db3.get_messages(same)
		r1 = db3.get_messages(MIXED)
		db4 = DbcDatabase()
		r2 = db4.get_messages(MIXED)
		check(r1 == r2, "DBC-22", "调用顺序不影响结果")
	finally:
		shutil.rmtree(tmp, ignore_errors=True)

	# ---------- 异常 ----------
	raises(lambda: db.get_messages(os.path.join(FIX, "no_such.dbc")),
	       "DBC-23", "缺失文件报错")
	raises(lambda: db.get_messages(os.path.join(FIX, "broken.dbc")),
	       "DBC-23b", "损坏文件报错")
	raises(lambda: db.get_messages(os.path.join(FIX, "unsupported_mux.dbc")),
	       "DBC-24", "多路复用被明确拒绝")

	print("\n%d passed, %d failed" % (PASS, FAIL))
	print("注：DBC-25（四模块联合生成）由 config.py generate + 产物哈希对比覆盖")
	return 0 if FAIL == 0 else 1


if __name__ == "__main__":
	sys.exit(main())
