#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    sync_can.py
@brief   把 `Can/Can.json` 的邮箱表 / HTH 表注入 `Can_Cfg.c` 的 `@generated` 区块

@details 与 `sync_canif.py` / `sync_pdur.py` 同一套做法：**只改标记之间的内容**，
          其余一字不动。理由见那两个脚本的文件头——整文件生成会把人工写的
          设计说明（M14 的掩码教训、邮箱分组原理）冲掉。

@note    没有 `@generated` 标记时**直接报错**，不尝试"智能插入"。
          自动插入要猜位置，猜错一次就是半张表被覆盖。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-17 | binbina | 首版：CAN0/CAN1 邮箱表 + HTH 表 |
"""

import io
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

from generator.Can import gen_all  # noqa: E402

CFG_DIR = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
CAN_JSON = os.path.join(CFG_DIR, "Can", "Can.json")
CAN_C = os.path.join(CFG_DIR, "Can_Cfg.c")


def inject(text, name, body):
	"""替换 `/* @generated BEGIN: <name> */` 与 `END` 之间的内容。"""
	begin = "/* @generated BEGIN: %s */" % name
	end = "/* @generated END: %s */" % name
	i = text.find(begin)
	j = text.find(end)
	if (i < 0) or (j < 0) or (j < i):
		raise SystemExit("Can_Cfg.c 找不到标记对：%s" % name)
	return text[:i + len(begin)] + "\n" + body + "\n" + text[j:]


def main():
	dry = "--dry-run" in sys.argv
	with io.open(CAN_JSON, encoding="utf-8") as f:
		cfg = json.load(f)

	blocks, stats = gen_all(cfg)

	with io.open(CAN_C, encoding="utf-8") as f:
		text = f.read()

	for name in ("CAN0 mailboxes", "CAN1 mailboxes", "HTH table"):
		text = inject(text, name, blocks[name])

	if dry:
		print("\n\n".join(blocks[k] for k in ("CAN0 mailboxes", "CAN1 mailboxes", "HTH table")))
		print("\n[dry-run] 不写文件")
		return 0

	with io.open(CAN_C, "w", encoding="utf-8", newline="\n") as f:
		f.write(text)

	print("Can_Cfg.c 已更新：%s" % ", ".join("%s %d 条" % (k, v) for k, v in stats.items()))
	return 0


if __name__ == "__main__":
	sys.exit(main())
