#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    config.py
@brief   配置工具链统一入口：import-dbc / validate / generate

@details @section CFGTOOL_WHY 为什么要有这个入口
         V1 时代配置链是散的：`matrix2json.py` 导矩阵、`sync_canif.py` /
         `sync_pdur.py` 注入、`a4_gen_check.py` 校验幂等、`mat_report.py`
         对账。每个脚本各有一套参数与输出格式，新人要读五个文件才知道
         "改一条报文到底要跑什么"。

         这里把**常用三件事**收成一条命令，其余脚本保持原样可单独调用：

         | 子命令 | 做什么 | 会不会写文件 |
         |--------|--------|--------------|
         | `import-dbc` | 解析 DBC 并统计，核对三份 JSON 的引用 | 只读 |
         | `validate` | 矩阵 vs 硬件邮箱 vs CanIf 过滤 vs Hoh 对账 | 只读 |
         | `generate` | 跑生成器 + 注入 + 拷入 config，再用 a4 静态断言复核 | **会写** |

         @note @section CFGTOOL_GAPS `validate` 判据的来源
         判定逻辑**不在本文件**，而是复用 `mat_report.analyze_channel()`：
         报告和校验必须是同一套规则，否则会出现"报告说没问题、校验说有缺口"。
         拆函数时已验证 `mat_report.py` 的输出逐字节不变。

         缺口分三类（都能落到具体报文，不是"覆盖率"这种模糊指标）：
         - `rx-not-in-canif`：DBC 说该收，CanIf 软件过滤表没条目 → 业务收不到
         - `rx-hw-blocked`：软件配了，硬件邮箱掩码不放行 → 白配
         - `tx-no-hoh`：DBC 说本节点发，Hoh 表没有 → 发不出去

@warning 客户 DBC 不入库（见 `.gitignore`）。缺 DBC 时 `validate` 返回 2
         并打印补齐方法，**不会**退回"跳过=通过"——那是最危险的假绿。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：validate / generate / import-dbc |
"""

import argparse
import os
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")

sys.path.insert(0, HERE)
import mat_report as mr  # noqa: E402  （同一目录下的对账实现，复用而不是复制）

PYTHON = sys.executable

DBC1 = os.path.join(CFG, "dbc", "can1.dbc")
DBC0 = os.path.join(CFG, "dbc", "can0.dbc")

# 生成链固定顺序：Com 是唯一"生成后拷入 config"的模块（A4 结论）
GEN_JSON = [
	os.path.join(CFG, "CanIf", "CanIf.json"),
	os.path.join(CFG, "PduR", "PduR.json"),
	os.path.join(CFG, "Com", "Com.json"),
]
GEN_COPY = [  # (GEN 目录, 目标目录)
	(os.path.join(CFG, "Com", "GEN"), CFG),
]


def rel(p):
	"""把绝对路径显示成相对仓库根的路径（输出稳定，便于比对）。"""
	try:
		return os.path.relpath(p, ROOT).replace(os.sep, "/")
	except ValueError:
		return p


# ============================== [ validate ] ==============================


def load_all():
	"""一次性读三张表（邮箱 / 过滤 / Hoh），失败返回 None。"""
	mbtab = mr.parse_mb_tables(os.path.join(CFG, "Can_Cfg.c"))
	rxlist = mr.parse_canif_rx(os.path.join(CFG, "CanIf_Cfg.c"))
	txtab = mr.parse_hoh_tx(os.path.join(CFG, "Can_Cfg.c"))
	return mbtab, rxlist, txtab


def cmd_validate(args):
	print("== 配置校验：通信矩阵 vs 硬件邮箱 vs CanIf 过滤 vs Hoh ==")
	print("工程根：%s\n" % rel(ROOT))

	missing = [p for p in (DBC1, DBC0) if not os.path.isfile(p)]
	if missing:
		print("[BLOCKED] 客户 DBC 未入库，缺失：")
		for p in missing:
			print("  - %s" % rel(p))
		print("\n补齐方法（见 .gitignore「客户（OEM）资料」一段）：")
		print("  把通信矩阵导出的 can0.dbc / can1.dbc 放到 %s" % rel(os.path.join(CFG, "dbc")))
		print("\n注意：缺输入**不等于**校验通过。本命令按失败返回（exit 2）。")
		return 2

	mbtab, rxlist, txtab = load_all()
	print("硬件邮箱条目 %d 组 / CanIf RX 条目 %d 条 / TX Hoh %d 条"
	      % (len(mbtab), len(rxlist), len(txtab)))

	all_gaps = []
	for ch, name, path in ((1, "CAN1", DBC1), (0, "CAN0", DBC0)):
		msgs = mr.load_dbc(path)
		res = mr.analyze_channel(ch, msgs, mbtab, rxlist, txtab)
		if res["skip"]:
			print("\n[%s] %s → 缺失，跳过" % (name, rel(path)))
			continue
		print("\n[%s] %s：报文 %d 条，缺口 %d 条"
		      % (name, rel(path), len(res["rows"]), len(res["gaps"])))
		for g in res["gaps"]:
			all_gaps.append((name, g))

	if all_gaps:
		print("\n| 通道 | 类型 | ID | 报文 | 说明 |")
		print("|---|---|---|---|---|")
		for ch_name, g in all_gaps:
			print("| %s | %s | %s | %s | %s |"
			      % (ch_name, g["kind"], g["id"], g["name"], g["detail"]))
		print("\n[FAIL] 共 %d 处覆盖缺口。这些报文在总线上真实收不到/发不出。" % len(all_gaps))
		print("       补法只有两种：补 CanIf 过滤条目（并在 Can_Cfg.c 给邮箱掩码），")
		print("       或确认该报文不由本节点收发后写进 JSON 的 ignore 列表。")
		return 0 if args.warn else 1

	print("\n[PASS] 三张表对得上，没有覆盖缺口。")
	return 0


# ============================== [ generate ] ==============================


def cmd_generate(args):
	print("== 配置生成：JSON(+DBC) → C ==")
	for p in GEN_JSON:
		if not os.path.isfile(p):
			print("[ERROR] 缺少配置源：%s" % rel(p))
			return 2

	# 生成器在 import 时才加载，避免 validate 也被迫依赖它
	sys.path.insert(0, HERE)
	from generator import Generate  # noqa: E402

	print("\n[1/4] 生成（force=%s）" % args.force)
	for p in GEN_JSON:
		Generate([p], force=args.force)
		print("  - %s" % rel(p))

	print("\n[2/4] 注入手写配置的 @generated 区块")
	for name in ("sync_canif.py", "sync_pdur.py"):
		script = os.path.join(HERE, name)
		if not os.path.isfile(script):
			print("  [SKIP] %s 不存在" % name)
			continue
		rc = subprocess.run([PYTHON, script], cwd=ROOT).returncode
		print("  - %s rc=%d" % (name, rc))
		if rc != 0:
			print("[ERROR] %s 失败，停止" % name)
			return 3

	print("\n[3/4] 把 Com 产物拷入 config/（唯一“生成后入库”的模块）")
	for src_dir, dst_dir in GEN_COPY:
		for fn in ("Com_Cfg.c", "Com_Cfg.h"):
			src = os.path.join(src_dir, fn)
			dst = os.path.join(dst_dir, fn)
			if not os.path.isfile(src):
				print("[ERROR] 缺少产物 %s" % rel(src))
				return 3
			shutil.copyfile(src, dst)
			print("  - %s → %s" % (rel(src), rel(dst)))

	print("\n[4/4] 静态复核（幂等标记 / 无时间戳 / 副本一致）")
	chk = os.path.join(HERE, "a4_gen_check.py")
	rc = subprocess.run([PYTHON, chk, "--static"], cwd=ROOT).returncode
	if rc != 0:
		print("[FAIL] a4 静态断言未通过，产物不可信")
		return 1

	print("\n[PASS] 生成完成且通过静态断言。下一步：cmd //c \"build.bat --app=App\"")
	return 0


# ============================= [ import-dbc ] =============================


def cmd_import(args):
	path = args.dbc
	if not os.path.isfile(path):
		print("[BLOCKED] DBC 不存在：%s" % path)
		print("客户文件不入库，需要从通信矩阵导出后放到 config/dbc/ 下。")
		return 2

	msgs = mr.load_dbc(path)
	if msgs is None:
		print("[ERROR] 解析失败：%s" % path)
		return 3

	n_ext = sum(1 for m in msgs if m["ext_gen"])
	n_cyc = sum(1 for m in msgs if m["cycle"])
	n_tx = sum(1 for m in msgs if m["tx"] == mr.ME)
	n_sig = sum(m["nSigs"] for m in msgs)
	nodes = sorted({m["tx"] for m in msgs if m["tx"]})

	print("== DBC 概览：%s ==" % rel(path))
	print("报文 %d 条（扩展帧 %d / 标准帧 %d），信号 %d 个"
	      % (len(msgs), n_ext, len(msgs) - n_ext, n_sig))
	print("本节点（%s）发送 %d 条，接收 %d 条" % (mr.ME, n_tx, len(msgs) - n_tx))
	print("带周期（GenMsgCycleTime）%d 条；发送节点：%s"
	      % (n_cyc, ", ".join(nodes) if nodes else "（DBC 里没有 BO_ 发送节点）"))

	print("\n各通道引用核对：")
	ok = True
	for label, p in (("CanIf", os.path.join(CFG, "CanIf", "CanIf.json")),
	                 ("PduR", os.path.join(CFG, "PduR", "PduR.json")),
	                 ("Com", os.path.join(CFG, "Com", "Com.json"))):
		ref = _json_dbc_ref(p)
		if ref is None:
			print("  - %-5s 未引用 DBC（可能内联信号）" % label)
			continue
		resolved = ref if os.path.isfile(ref) else os.path.join(os.path.dirname(p), ref)
		same = os.path.isfile(resolved) and os.path.samefile(resolved, path)
		print("  - %-5s → %s %s" % (label, ref, "（与本次一致）" if same else "（**不是这份**）"))
		ok = ok and same

	if not ok:
		print("\n[WARN] 生成的输入与你给的 DBC 不是同一份，validate/generate 会用到另一份。")
		return 1

	print("\n[PASS] 三份 JSON 都指向这份 DBC。")
	return 0


def _json_dbc_ref(cfg_path):
	"""读 JSON 里第一个 network 的 dbc 字段（与生成器同一取法）。"""
	import json
	if not os.path.isfile(cfg_path):
		return None
	with open(cfg_path, encoding="utf-8") as f:
		cfg = json.load(f)
	for n in cfg.get("networks", []):
		if "dbc" in n:
			return n["dbc"]
	return None


# ================================ [ 入口 ] ================================


def main():
	ap = argparse.ArgumentParser(
		description="like_as 配置工具链入口（validate 只读，generate 会写文件）")
	sub = ap.add_subparsers(dest="cmd", required=True)

	v = sub.add_parser("validate", help="矩阵 vs 邮箱 vs CanIf vs Hoh 对账")
	v.add_argument("--warn", action="store_true", help="有缺口也返回 0（只用于人工预览）")
	v.set_defaults(func=cmd_validate)

	g = sub.add_parser("generate", help="生成 + 注入 + 拷入 + 静态复核")
	g.add_argument("--force", action="store_true", help="忽略缓存强制重新生成")
	g.set_defaults(func=cmd_generate)

	i = sub.add_parser("import-dbc", help="解析 DBC 并核对 JSON 引用（只读）")
	i.add_argument("--dbc", default=DBC1, help="DBC 路径，默认 can1.dbc")
	i.set_defaults(func=cmd_import)

	a = ap.parse_args()
	return a.func(a)


if __name__ == "__main__":
	sys.exit(main())
