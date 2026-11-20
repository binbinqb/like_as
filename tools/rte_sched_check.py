#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    rte_sched_check.py
@brief   RTE 调度表规则自测（S1~S4）+ 变体配置运行验证（多周期 / 顺序可配）

@details @section WHY 为什么要单独测

          S1~S3 只在**配错**时才起作用，当前 Board.json 的调度表是对的，
          日常构建一次都不触发；等新项目配错时才发现规则写错就晚了。
          所以用合成配置直接喂生成器（与 rte_cfg_check.py 同一策略）。

          变体运行验证钉住两件事：
          | 断言 | 钉住什么 |
          |------|----------|
          | 变体周期 10/20/30 ms，6 拍内分别执行 6/3/2 次 | 分频语义（reload = period/10） |
          | 变体顺序变了，一拍内执行顺序跟着变 | "表序即执行序"是配置的一部分 |
          | 同一份 rte_sched.c 不改一个字 | 换项目真的只改 Board.json |

          变体是"另一个 BCM 项目"的样子：runnable 名字、数量、周期、
          顺序全变 —— 比真实配置的"全 10ms"覆盖面宽得多。

@note    变体运行需要 `gcc`（与 host_build.py 同一套 mingw）。

@author  binbina
@version V1.0.0
"""

import contextlib
import io
import json
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

import generator.BcmRte as R  # noqa: E402

CC = "C:/soft/mingw64/bin/gcc.exe"

results = []


def check(name, cond, detail=""):
	results.append((name, bool(cond), detail))
	print(("  PASS  " if cond else "  FAIL  ") + name
	      + (("   " + detail) if (detail and not cond) else ""))


def base_cfg(sched):
	"""合法的最小配置：io 段只为让端口校验通过，schedule 由调用者给。"""
	return {
		"pins": [{"name": "LED_R", "dir": "OUT"}],
		"dioChannels": ["LED_R"],
		"adc": {"groups": 2},
		"pwm": {"channels": 4},
		"selectBuses": [],
		"devices": [],
		"io": {
			"din": [{"name": "DOOR_FL", "source": "host", "channel": 0,
			         "activeLevel": "LOW", "debounceMs": 20, "staleMs": 500}],
			"ain": [{"name": "VBAT", "source": "host", "channel": 0,
			         "filterShift": 3, "factor": 33, "staleMs": 200}],
			"dout": [{"name": "LED_R", "source": "direct", "pin": "LED_R",
			          "activeLevel": "LOW", "safeLevel": False}],
			"pwm": [],
		},
		"rte": {
			"ports": [{"name": "DOOR", "kind": "io_din", "ref": "DOOR_FL"}],
			"schedule": sched,
		},
	}


def gen(cfg, d):
	"""生成到临时目录，返回 Rte_Schedule.h 文本。"""
	with contextlib.redirect_stdout(io.StringIO()):
		R.Gen_Rte(cfg, d)
	return io.open(os.path.join(d, "Rte_Schedule.h"), encoding="utf-8").read()


def expect_die(name, mutate, needle):
	cfg = base_cfg([])
	if callable(mutate):
		mutate(cfg)
	else:
		cfg["rte"]["schedule"] = mutate
	try:
		with tempfile.TemporaryDirectory() as d:
			gen(cfg, d)
	except Exception as e:  # noqa: BLE001 —— 生成器的报错通道就是异常
		msg = str(e)
		check(name, needle in msg, "报错=%s" % msg)
		return
	check(name, False, "没有报错（生成器放行了非法配置）")


# 变体 runnable 的替身 + 断言主体：A 10ms / B 20ms / C 30ms
VAR_TEST_C = r"""
#include <stdio.h>
#include "rte.h"
#include "Rte_Schedule.h"

static int s_cntA, s_cntB, s_cntC;
static int s_order[64], s_n;

void A_Task(void) { s_cntA++; if (s_n < 64) { s_order[s_n++] = 'A'; } }
void B_Task(void) { s_cntB++; if (s_n < 64) { s_order[s_n++] = 'B'; } }
void C_Task(void) { s_cntC++; if (s_n < 64) { s_order[s_n++] = 'C'; } }

static int s_bad;
static void Chk(const char *name, int cond, int v)
{
	printf("  %s  %s (v=%d)\n", cond ? "PASS" : "FAIL", name, v);
	if (!cond) { s_bad++; }
}

int main(void)
{
	int i;
	/* 6 拍 = 60 ms：A 应 6 次、B 3 次、C 2 次 */
	for (i = 0; i < 6; i++) { Rte_MainFunction(); }
	Chk("A(10ms) 6 拍执行 6 次", s_cntA == 6, s_cntA);
	Chk("B(20ms) 6 拍执行 3 次", s_cntB == 3, s_cntB);
	Chk("C(30ms) 6 拍执行 2 次", s_cntC == 2, s_cntC);
	Chk("第 1 拍顺序 == 配置顺序 B->C->A（配置里 B 在最前）",
	    (s_order[0] == 'B') && (s_order[1] == 'C') && (s_order[2] == 'A'), s_order[0]);
	Chk("第 2 拍只有 A（多周期不同拍）",
	    (s_n >= 4) && (s_order[3] == 'A'), s_n);
	printf("-- sched_var: %s\n", (s_bad == 0) ? "全部通过" : "有失败项");
	return (s_bad == 0) ? 0 : 1;
}
"""


def main():
	print("== RTE 调度表规则自测（S1~S4）+ 变体运行验证 ==")

	# ---- 合法配置：生成物的具体符号 ----
	ok_cfg = base_cfg([
		{"func": "BcmSig_MainFunction", "period_ms": 10},
		{"func": "IoHwAb_MainFunction", "period_ms": 20},
	])
	with tempfile.TemporaryDirectory() as d:
		hdr = gen(ok_cfg, d)
		check("合法配置生成 RTE_SCHED_NUM == 2", "#define RTE_SCHED_NUM      (2u)" in hdr)
		check("period 20ms 折算成 2 拍", bool(re.search(r"\{ 2u, IoHwAb_MainFunction \}", hdr)))
		check("runnable 原型随表生成",
		      ("extern void BcmSig_MainFunction(void);" in hdr)
		      and ("extern void IoHwAb_MainFunction(void);" in hdr))

	# ---- 缺陷注入：每条规则在对应缺陷下确实失败 ----
	expect_die("S1 func 非法标识符被拒",
	           [{"func": "1Bad", "period_ms": 10}], "S1")
	expect_die("S2 period=7（不是 10 的倍数）被拒",
	           [{"func": "A", "period_ms": 7}], "S2")
	expect_die("S2 period=0 被拒",
	           [{"func": "A", "period_ms": 0}], "S2")
	expect_die("S2 period 缺失被拒",
	           [{"func": "A"}], "S2")
	expect_die("S3 同一 func 出现两次被拒",
	           [{"func": "A_Task", "period_ms": 10},
	            {"func": "A_Task", "period_ms": 20}], "S3")

	# ---- S4：schedule 段缺省 → 空表合法 ----
	cfg_no_sched = base_cfg([])
	del cfg_no_sched["rte"]["schedule"]
	with tempfile.TemporaryDirectory() as d:
		hdr = gen(cfg_no_sched, d)
		check("S4 缺省 schedule → 空表占位（NUM=1 且 func=NULL）",
		      ("#define RTE_SCHED_NUM      (1u)" in hdr)
		      and ("((Rte_SchedFunc)0)" in hdr))

	# ---- 变体运行：同一份 rte_sched.c，不同配置 ----
	var_cfg = base_cfg([
		{"func": "B_Task", "period_ms": 20},   # 故意把 B 放最前：顺序必须跟着配置走
		{"func": "C_Task", "period_ms": 30},
		{"func": "A_Task", "period_ms": 10},
	])
	with tempfile.TemporaryDirectory() as d:
		gen(var_cfg, d)
		test_c = os.path.join(d, "sched_var_test.c")
		exe = os.path.join(d, "sched_var.exe")
		with io.open(test_c, "w", encoding="utf-8", newline="\n") as f:
			f.write(VAR_TEST_C)   # 替身 runnable（A/B/C_Task）与断言都在这里
		inc = ["-I", d, "-I", os.path.join(ROOT, "app", "app", "src"),
		       "-I", os.path.join(ROOT, "app", "include"),
		       "-I", os.path.join(ROOT, "infras", "include")]
		p = subprocess.run([CC, "-std=c99", "-Wall", "-Wextra"] + inc
		                   + [os.path.join(ROOT, "app", "app", "src", "rte_sched.c"),
		                      test_c, "-o", exe],
		                   capture_output=True, text=True)
		ok = (p.returncode == 0)
		check("变体配置下同一份 rte_sched.c 能编译", ok,
		      (p.stdout + p.stderr).strip().splitlines()[-1] if (p.stdout + p.stderr).strip() else "")
		if ok:
			r = subprocess.run([exe], capture_output=True, text=True)
			print(r.stdout.rstrip())
			check("变体运行：多周期分频 + 顺序跟随配置", r.returncode == 0)

	failed = [x for x in results if not x[1]]
	print("-- %d 项断言，%d 项失败" % (len(results), len(failed)))
	return 0 if not failed else 1


if __name__ == "__main__":
	sys.exit(main())
