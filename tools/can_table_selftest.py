#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    can_table_selftest.py
@brief   证明 `can_table_check.py` 真的能抓到错误（判据的判据）

@details 02.6 的等价性结论全部建立在 `can_table_check.py` 之上。如果它恒返回
          PASS，那"52 项通过"就是一句空话。所以这里把真实配置复制到临时目录，
          注入三类**已知会破坏硬件行为**的缺陷，要求检查器必须失败：

          | 注入 | 对应现场症状 | 期望报出 |
          |------|--------------|----------|
          | 改一个 RX 掩码 | 某个邮箱变成全收，后面的段全丢（M14 踩过） | 字段一致 |
          | 删一条 HTH | `Can_Write` 拿错邮箱 / 发不出去 | 条目数不一致 |
          | 改 CAN_HW_HOH_NUM | 数组尾部补 0 条目，覆盖 HTH0 | HOH_NUM 不等 |

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
FILES = ["Can_Cfg.c", "Can_HwCfg.h"]


def run_check(cfg_dir, json_path):
	env = dict(os.environ, LIKEAS_CAN_CFG_DIR=cfg_dir, LIKEAS_CAN_JSON=json_path)
	proc = subprocess.run([sys.executable, os.path.join(HERE, "can_table_check.py")],
	                      cwd=ROOT, env=env, capture_output=True, text=True)
	return proc.stdout + proc.stderr


def case(tmp, name, mutate_c, mutate_h, expect):
	work = os.path.join(tmp, name)
	cfgdir = os.path.join(work, "config")
	os.makedirs(cfgdir)
	for f in FILES:
		shutil.copyfile(os.path.join(CFG, f), os.path.join(cfgdir, f))

	# JSON 也要一份副本，保证自测不依赖真实文件的当前状态
	jsrc = os.path.join(CFG, "Can", "Can.json")
	jdst = os.path.join(work, "Can.json")
	shutil.copyfile(jsrc, jdst)

	if mutate_c:
		p = os.path.join(cfgdir, "Can_Cfg.c")
		s = open(p, encoding="utf-8").read()
		open(p, "w", encoding="utf-8", newline="\n").write(mutate_c(s))
	if mutate_h:
		p = os.path.join(cfgdir, "Can_HwCfg.h")
		s = open(p, encoding="utf-8").read()
		open(p, "w", encoding="utf-8", newline="\n").write(mutate_h(s))

	out = run_check(cfgdir, jdst)
	ok = ("[FAIL]" in out) and (expect in out)
	print("  %s  %s → %s" % ("PASS" if ok else "FAIL", name,
	                        ("报出 %s" % expect) if ok else "没报出（检查器漏了）"))
	return ok


def bad_mask(s):
	# mb2 的段掩码 0x1FFF0000 改成 0xFFFFFFFF：该邮箱会变成全收
	return s.replace("0x18FF0000u, true , CAN_HW_MB_RX, 8u, true ,  0x1FFF0000u",
	                 "0x18FF0000u, true , CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu", 1)


def drop_hth(s):
	# 删掉 HTH11（最后一行），条目数与 JSON 对不上
	return re.sub(r"\n\t\{ 1u,  7u,  0x18FECA21u.*?\n", "\n", s, count=1)


def bad_hoh_num(s):
	return re.sub(r"#define CAN_HW_HOH_NUM\s+\(12u\)",
	              "#define CAN_HW_HOH_NUM              (13u)", s)


def main():
	tmp = tempfile.mkdtemp(prefix="likeas_can_")
	try:
		results = [
			case(tmp, "bad-mask", bad_mask, None, "字段一致"),
			case(tmp, "drop-hth", drop_hth, None, "HTH 条目数一致"),
			case(tmp, "bad-hoh-num", None, bad_hoh_num, "CAN_HW_HOH_NUM"),
		]
		print("\n%d/%d cases detected" % (sum(1 for r in results if r), len(results)))
		return 0 if all(results) else 1
	finally:
		shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
	sys.exit(main())
