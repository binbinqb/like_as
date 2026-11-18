#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    rte_cfg_check.py
@brief   RTE 端口配置规则自测（E1~E6）：合法配置能过、非法配置必须失败

@details @section WHY 为什么要单独测

          E1~E6 只在**配错**时才起作用。当前 `Board.json` 的端口表是对的，
          也就是说这些规则在日常构建里一次都不会触发。等新项目配错时才发现
          规则写错，代价是排查生成物。所以用合成配置直接喂生成器。

          验证两件事：
          1. 合法配置生成的**具体符号**（端口枚举、ref 展开）；
          2. 每条规则在对应缺陷下确实失败，且错误信息可检索（E1..E6）。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-18 | binbina | 首版：1 组合法 + 6 组缺陷注入 |
"""

import io
import os
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import generator.BcmRte as R  # noqa: E402

results = []


def check(name, cond, detail=""):
	results.append((name, bool(cond), detail))
	print(("  PASS  " if cond else "  FAIL  ") + name
	      + (("   " + detail) if (detail and not cond) else ""))


def base_cfg():
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
			"ports": [
				{"name": "DOOR", "kind": "io_din", "ref": "DOOR_FL"},
				{"name": "VBAT_MV", "kind": "io_ain_phys", "ref": "VBAT"},
				{"name": "LAMP", "kind": "com_tx", "ref": "BCM_SIG_LOW_BEAM"},
			]
		},
	}


def gen(cfg, d):
	R.Gen_Rte(cfg, d)
	return io.open(os.path.join(d, "Rte_Ports.h"), encoding="utf-8").read()


def expect_die(name, mutate, needle):
	cfg = base_cfg()
	mutate(cfg)
	try:
		with tempfile.TemporaryDirectory() as d:
			gen(cfg, d)
		check(name, False, "未失败（漏检）")
	except Exception as e:  # noqa: BLE001
		check(name, needle in str(e), "错误信息=%s" % str(e))


def main():
	print("== RTE 端口配置规则自测 ==")

	# ---- 1) 合法配置 ----
	with tempfile.TemporaryDirectory() as d:
		h = gen(base_cfg(), d)
	check("生成端口枚举 RTE_PORT_DOOR = 0", "RTE_PORT_DOOR" in h and "= 0," in h)
	check("生成计数 RTE_PORT_NUM = (3u)", "#define RTE_PORT_NUM     (3u)" in h)
	check("io 引用展开为 IOHWAB_DIN_DOOR_FL", "IOHWAB_DIN_DOOR_FL" in h)
	check("io 引用展开为 IOHWAB_AIN_VBAT", "IOHWAB_AIN_VBAT" in h)
	check("com 引用原样输出 BCM_SIG_LOW_BEAM", "BCM_SIG_LOW_BEAM" in h)
	check("表项字段为 {dir, kind, ref}", "RTE_DIR_IN, RTE_KIND_DIN" in h)

	# ---- 2) 缺陷注入 ----
	expect_die("E1 端口名重复",
	           lambda c: c["rte"]["ports"].append(
	               {"name": "DOOR", "kind": "io_din", "ref": "DOOR_FL"}), "E1")
	expect_die("E1 端口名非法（不是 C 标识符）",
	           lambda c: c["rte"]["ports"][0].update({"name": "1DOOR"}), "E1")
	expect_die("E2 kind 未知",
	           lambda c: c["rte"]["ports"][0].update({"kind": "io_pwm"}), "E2")
	expect_die("E3 显式 type 与 kind 矛盾",
	           lambda c: c["rte"]["ports"][1].update({"type": "BOOL"}), "E3")
	expect_die("E3 显式 dir 与 kind 矛盾",
	           lambda c: c["rte"]["ports"][2].update({"dir": "in"}), "E3")
	expect_die("E4 io 引用不存在",
	           lambda c: c["rte"]["ports"][0].update({"ref": "DOOR_X"}), "E4")
	expect_die("E5 com 引用非法标识符",
	           lambda c: c["rte"]["ports"][2].update({"ref": "BCM-SIG"}), "E5")
	expect_die("E6 同一 kind+ref 被两个端口绑定",
	           lambda c: c["rte"]["ports"].append(
	               {"name": "DOOR2", "kind": "io_din", "ref": "DOOR_FL"}), "E6")

	failed = [r for r in results if not r[1]]
	print("-- %d 项断言，%d 项失败" % (len(results), len(failed)))
	return 0 if not failed else 1


if __name__ == "__main__":
	sys.exit(main())
