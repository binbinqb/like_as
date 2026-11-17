#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    pdu_selftest.py
@brief   证明 `config.py check-pdu` 真的能抓到问题（判据的判据）

@details 一个检查器如果永远返回 PASS，它和没有是一样的。这里复制真实配置到
         临时目录，注入三类已知缺陷，要求 check-pdu **必须**失败：

         | 注入 | 期望报出 |
         |------|----------|
         | 复制一条 CanIf RX 表项 | duplicate / id-conflict |
         | 删掉一个 COM_ 宏定义 | dangling |
         | 改错 PDUR_CAN1_PATHS | index-mismatch |

@note    只读真实配置：所有改动都在临时副本上做，跑完删除。

@author  binbina
@version V1.0.0
"""

import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
FILES = ["Com_Cfg.h", "CanIf_Cfg.h", "CanIf_Cfg.c", "PduR_Cfg.c", "PduR_Cfg.h"]


def run_check(cfg_dir):
	env = dict(os.environ, LIKEAS_CFG_DIR=cfg_dir)
	proc = subprocess.run([sys.executable, os.path.join(HERE, "config.py"), "check-pdu", "--warn"],
	                      cwd=ROOT, env=env, capture_output=True, text=True)
	return proc.stdout


def case(tmp, name, mutate, expect):
	work = os.path.join(tmp, name)
	os.makedirs(work)
	for f in FILES:
		shutil.copyfile(os.path.join(CFG, f), os.path.join(work, f))
	mutate(work)
	out = run_check(work)
	ok = (("共" in out) and (expect in out))
	print("  %s  %s → %s" % ("PASS" if ok else "FAIL", name,
	                        "报出 %s" % expect if ok else "没报出（检查器漏了）"))
	return ok


def dup_rx(work):
	p = os.path.join(work, "CanIf_Cfg.c")
	s = open(p, encoding="utf-8").read()
	m = re.search(r"\t\{\n\t\tCanIfCfg_RxPduR_CAN1_EOI,.*?\n\t\},\n", s, re.S)
	s = s[:m.end()] + m.group(0) + s[m.end():]
	open(p, "w", encoding="utf-8", newline="\n").write(s)


def drop_com(work):
	p = os.path.join(work, "Com_Cfg.h")
	s = open(p, encoding="utf-8").read()
	s = s.replace("#define COM_CAN1_BCM_LCSF_TX 0", "#define COM_CAN1_BCM_LCSF_TX_REMOVED 0")
	open(p, "w", encoding="utf-8", newline="\n").write(s)


def bad_paths(work):
	p = os.path.join(work, "PduR_Cfg.h")
	s = open(p, encoding="utf-8").read()
	s = re.sub(r"#define PDUR_CAN1_PATHS\s+\(\d+u?\)", "#define PDUR_CAN1_PATHS (1u)", s)
	open(p, "w", encoding="utf-8", newline="\n").write(s)


def main():
	tmp = tempfile.mkdtemp(prefix="likeas_pdu_")
	try:
		results = [
			case(tmp, "dup-rx", dup_rx, "duplicate"),
			case(tmp, "drop-com", drop_com, "dangling"),
			case(tmp, "bad-paths", bad_paths, "index-mismatch"),
		]
		print("\n%d/%d cases detected" % (sum(1 for r in results if r), len(results)))
		return 0 if all(results) else 1
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
	sys.exit(main())
