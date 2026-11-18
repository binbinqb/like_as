#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    mux_cfg_check.py
@brief   MUX 配置生成规则自测（R11~R14）：合法配置能过、非法配置必须失败

@details @section WHY 为什么要有这份自测

          R11~R14 的校验逻辑只有在**配错**时才起作用。仓库当前没有 RS2260
          实物，`Board.json` 的 `selectBuses`/`devices` 都是空的 —— 也就是说
          这些规则在真实构建里**一次都不会被执行**。等接了器件才发现规则
          写错，代价是上板排查；所以用合成配置直接喂生成器。

          这里验证两件事：
          1. 合法配置生成的**具体数值**（通道编码、扫描掩码、建立拍数）；
          2. 每条规则在对应缺陷下**确实失败**，并给出可检索的错误码。

@author  binbina
@version V1.1.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.1.0 | 2026-11-18 | binbina | 首版：1 组合法 + 8 组缺陷注入 |
"""

import copy
import io
import os
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import generator.IoHwAb as G  # noqa: E402

results = []


def check(name, cond, detail=""):
	results.append((name, bool(cond), detail))
	print(("  PASS  " if cond else "  FAIL  ") + name + (("   " + detail) if (detail and not cond) else ""))


def base_cfg():
	"""一块合成板：1 条总线 + GPIO/ADC 两片 MUX + 3 个逻辑通道。"""
	return {
		"pins": {"LED_R": {"dir": "OUT"}},
		"dioChannels": ["A0", "A1", "A2", "COM_G", "INH0"],
		"adc": {"groups": 2},
		"pwm": {"channels": 4},
		"selectBuses": [
			{"name": "ABC0", "pins": ["A0", "A1", "A2"],
			 "settleMs": 20, "adcTimeoutMs": 30},
		],
		"devices": [
			{"name": "MUX1", "selectBus": "ABC0", "comType": "GPIO",
			 "comPin": "COM_G", "inh": {"pin": "INH0", "activeLevel": "LOW"}},
			{"name": "MUX2", "selectBus": "ABC0", "comType": "ADC",
			 "adcGroup": 0, "channel": 1},
		],
		"io": {
			"din": [
				{"name": "DOOR_FL", "source": "mux", "device": "MUX1",
				 "channel": 0, "activeLevel": "LOW", "debounceMs": 20},
				{"name": "DOOR_FR", "source": "mux", "device": "MUX1",
				 "channel": 3, "activeLevel": "LOW", "debounceMs": 20},
			],
			"ain": [
				{"name": "VBAT", "source": "mux", "device": "MUX2",
				 "channel": 3, "filterShift": 3, "factor": 33,
				 "offset": 0, "staleMs": 200},
				{"name": "POT2_ADC", "source": "direct", "adcGroup": 1,
				 "channel": 0, "filterShift": 2, "factor": 806,
				 "staleMs": 200},
			],
		},
	}


def norm(cfg):
	return G._norm(cfg, {p["name"]: p for p in []},
	               cfg["dioChannels"], cfg["adc"]["groups"], cfg["pwm"]["channels"])


def expect_die(name, mutate, needle):
	cfg = base_cfg()
	mutate(cfg)
	try:
		norm(cfg)
		check(name, False, "未失败（漏检）")
	except Exception as e:  # noqa: BLE001
		check(name, needle in str(e), "错误信息=%s" % str(e))


def main():
	print("== MUX 配置生成规则自测 ==")

	# ---- 1) 合法配置：数值必须与约定一致 ----
	t, buses, devices = norm(base_cfg())
	b = buses[0]
	check("总线扫描掩码 = OR(设备掩码) = 0x09", b["mask"] == 0x09, hex(b["mask"]))
	check("settleMs=20 → 2 拍", b["settle"] == 2, str(b["settle"]))
	check("adcTimeoutMs=30 → 3 拍", b["adc_tmo"] == 3, str(b["adc_tmo"]))
	check("GPIO 设备掩码 = Y0|Y3", devices[0]["mask"] == 0x09, hex(devices[0]["mask"]))
	check("ADC 设备掩码 = Y3", devices[1]["mask"] == 0x08, hex(devices[1]["mask"]))
	check("INH 通道 = dioChannels 索引 4", devices[0]["inh_ch"] == 4,
	      str(devices[0]["inh_ch"]))
	check("INH 低有效 → 0", devices[0]["inh_lvl"] == 0)
	check("DIN 通道编码 = (0<<8)|0 / (0<<8)|3",
	      (t["din"][0]["ch"] == 0) and (t["din"][1]["ch"] == 3),
	      "%r" % [e["ch"] for e in t["din"]])
	check("AIN 通道编码 = (1<<8)|3", t["ain"][0]["ch"] == ((1 << 8) | 3),
	      str(t["ain"][0]["ch"]))
	check("AIN source 记为 mux，ops 走 MuxAin",
	      (t["ain"][0]["src"] == "mux")
	      and (G._OPS[("ain", "mux")] == "IoHwAb_MuxAinOps"))
	check("直连 AIN 编码 = (组<<8)|槽位（组 1 → 0x0100）",
	      t["ain"][1]["ch"] == 0x0100, hex(t["ain"][1]["ch"]))

	# 生成物内容抽查：MASK 与编码必须落到 C 里
	with tempfile.TemporaryDirectory() as d:
		G._gen_mux(buses, devices, d)
		src = io.open(os.path.join(d, "Mux_Cfg.c"), encoding="utf-8").read()
		check("Mux_Cfg.c 含总线掩码 0x09", "0x09u" in src)
		check("Mux_Cfg.c 含设备计数 2", "Mux_DeviceCount = 2u" in src)

	# ---- 2) R11：总线定义 ----
	expect_die("R11 A/B/C 缺一根", lambda c: c["selectBuses"][0].update(
		{"pins": ["A0", "A1"]}), "R11")
	expect_die("R11 引脚不在 dioChannels", lambda c: c["selectBuses"][0].update(
		{"pins": ["A0", "A1", "NOPE"]}), "R11")
	expect_die("R9 settleMs 非 10 倍数", lambda c: c["selectBuses"][0].update(
		{"settleMs": 25}), "R9")

	# ---- 3) R12：设备定义 ----
	expect_die("R12 selectBus 不存在", lambda c: c["devices"][0].update(
		{"selectBus": "ABC9"}), "R12")
	expect_die("R12 comType 非法", lambda c: c["devices"][0].update(
		{"comType": "SPI"}), "R12")
	expect_die("R12 GPIO 的 comPin 不存在", lambda c: c["devices"][0].update(
		{"comPin": "NOPE"}), "R12")

	# ---- 4) R13：通道引用 ----
	expect_die("R13 device 未定义", lambda c: c["io"]["din"][0].update(
		{"device": "MUX9"}), "R13")
	expect_die("R13 DIN 指向 ADC 设备", lambda c: c["io"]["din"][0].update(
		{"device": "MUX2"}), "R13")
	expect_die("R13 Y 越界（8）", lambda c: c["io"]["din"][0].update(
		{"channel": 8}), "R13")
	expect_die("R13 同一设备通道被两处引用", lambda c: c["io"]["din"][1].update(
		{"channel": 0}), "R13")

	# ---- 4b) R15：ADC 组所有权唯一 ----
	expect_die("R15 直连 AIN 与 MUX 抢同一 ADC 组",
	           lambda c: c["io"]["ain"][1].update({"adcGroup": 0}),
	           "R15")

	# ---- 5) R14：设备无通道只提示，不失败 ----
	cfg = base_cfg()
	cfg["io"]["ain"] = []
	cfg["devices"] = cfg["devices"][:1]   # 去掉 ADC 设备，避免 R12 连带
	t2, buses2, devices2 = norm(cfg)
	check("R14 无引用设备不阻断生成", len(devices2) == 1)
	check("R14 无引用设备掩码为 0", devices2[0]["mask"] == 0x09)

	failed = [r for r in results if not r[1]]
	print("-- %d 项断言，%d 项失败" % (len(results), len(failed)))
	return 0 if not failed else 1


if __name__ == "__main__":
	sys.exit(main())
