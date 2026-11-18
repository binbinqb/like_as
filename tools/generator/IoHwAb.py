# -*- coding: utf-8 -*-
"""从 `Board.json` 的 `io` 段生成 `IoHwAb_Cfg.{h,c}`。

## 为什么放在 Board.py 里调、代码单独一个文件

`io` 段描述的是"这块板有哪些逻辑 IO、接到哪里"，与 `pins` / `dioChannels`
同源 —— 分成两个 JSON 反而要解决"谁先谁后"。但生成逻辑（校验、命名、表结构）
必须独立：V1.1 加 devices/selectBuses 时只改本文件，不碰 Board.py。

## V1.0 支持的 source

| source | 含义 | Target 行为 |
|---|---|---|
| `direct` | MCU 直连（Dio/Adc/Pwm） | 调 HAL |
| `host` | Host 模拟通道 | 用 `IoHwAb_Host*Ops`；在 Target 上是返回 E_NOT_OK 的桩 |

**同一份配置同时服务 Target 与 Host**：ID 空间一致，测试里用的枚举在板上也成立，
只是 Host 通道在板上恒为不可用（不伪造值）。

## 校验（每条失败都终止生成，不产半份配置）

R1 名称唯一 / R2 直连 pin 存在 / R3 dir 匹配 / R4 电平合法 / R5 消抖拍数 /
R6 ADC 组范围 / R7 PWM 参数 / R8 物理资源不重复绑定 / R9 超时拍数 / R10 安全值缺省

@author binbina
"""

import os

from .helper import GenHeader, toMacro

__all__ = ["Gen_Io"]

LEVEL = {"HIGH": 1, "LOW": 0}


def _die(msg):
	raise Exception("[IoHwAb] " + msg)


def _ticks(e, key, default, name):
	"""把毫秒配置换算成 10 ms 拍数，并按 R9 校验。"""
	ms = int(e.get(key, default))
	if ms < 10 or ms % 10:
		_die("R9 %s.%s=%d（必须是 10 的整数倍且 ≥10）" % (name, key, ms))
	return ms // 10


def _norm(cfg, pins, dio_channels, adc_groups, pwm_channels):
	"""校验并展开四张表，返回 dict。"""
	io = cfg.get("io", {})
	seen = {}
	used_pin = {}
	used_adc = {}
	used_pwm = {}

	def name_of(e, kind):
		n = e.get("name", "")
		if not n:
			_die("%s 有通道缺 name" % kind)
		if n in seen:
			_die("R1 通道名重复：%s（%s 与 %s）" % (n, seen[n], kind))
		seen[n] = kind
		return n

	def src_of(e, kind):
		s = e.get("source", "direct")
		if s not in ("direct", "host"):
			_die("%s.source 非法：%s（只允许 direct/host）" % (kind, s))
		return s

	out = {"din": [], "ain": [], "dout": [], "pwm": []}

	# ---- DIN ----
	for e in io.get("din", []):
		n = name_of(e, "din")
		src = src_of(e, "din")
		lvl = e.get("activeLevel", "LOW")
		if lvl not in LEVEL:
			_die("R4 %s.activeLevel=%s" % (n, lvl))
		db = int(e.get("debounceMs", 20))
		if db < 10 or db % 10:
			_die("R5 %s.debounceMs=%d（必须是 10 的整数倍且 ≥10）" % (n, db))
		stale = _ticks(e, "staleMs", 500, n)
		ch = int(e.get("channel", 0))
		if src == "direct":
			pin = e.get("pin", "")
			if pin not in pins:
				_die("R2 %s.pin=%s 不在 pins[]" % (n, pin))
			if pins[pin].get("dir") != "IN":
				_die("R3 %s 直连 DIN 需要 dir=IN，实际 %s"
				     % (n, pins[pin].get("dir")))
			if pin not in dio_channels:
				_die("R2 %s.pin=%s 不在 dioChannels[]（Dio 没有该通道）" % (n, pin))
			ch = dio_channels.index(pin)
			if pin in used_pin:
				_die("R8 %s 与 %s 绑定同一 pin %s" % (n, used_pin[pin], pin))
			used_pin[pin] = n
		out["din"].append({
			"name": n, "src": src, "ch": ch, "lvl": LEVEL[lvl],
			"db_ticks": db // 10, "stale": stale,
		})

	# ---- AIN ----
	for e in io.get("ain", []):
		n = name_of(e, "ain")
		src = src_of(e, "ain")
		grp = int(e.get("adcGroup", 0))
		ch = int(e.get("channel", 0))
		if src == "direct":
			if grp < 0 or grp >= adc_groups:
				_die("R6 %s.adcGroup=%d 越界（0..%d）" % (n, grp, adc_groups - 1))
			key = (grp, ch)
			if key in used_adc:
				_die("R8 %s 与 %s 绑定同一 ADC 组/通道 %s"
				     % (n, used_adc[key], key))
			used_adc[key] = n
		shift = int(e.get("filterShift", 0))
		if shift < 0 or shift > 8:
			_die("%s.filterShift 允许 0..8" % n)
		fs = int(e.get("factor", 1000))
		off = int(e.get("offset", 0))
		stale = _ticks(e, "staleMs", 200, n)
		out["ain"].append({
			"name": n, "src": src, "grp": grp, "ch": ch, "shift": shift,
			"factor": fs, "offset": off, "stale": stale,
		})

	# ---- DOUT ----
	for e in io.get("dout", []):
		n = name_of(e, "dout")
		src = src_of(e, "dout")
		lvl = e.get("activeLevel", "LOW")
		if lvl not in LEVEL:
			_die("R4 %s.activeLevel=%s" % (n, lvl))
		if "safeLevel" not in e:
			print("  [IoHwAb] R10 %s 未写 safeLevel，按 false" % n)
		safe = 1 if e.get("safeLevel", False) else 0
		ch = int(e.get("channel", 0))
		if src == "direct":
			pin = e.get("pin", "")
			if pin not in pins:
				_die("R2 %s.pin=%s 不在 pins[]" % (n, pin))
			if pins[pin].get("dir") != "OUT":
				_die("R3 %s 直连 DOUT 需要 dir=OUT，实际 %s"
				     % (n, pins[pin].get("dir")))
			if pin not in dio_channels:
				_die("R2 %s.pin=%s 不在 dioChannels[]" % (n, pin))
			ch = dio_channels.index(pin)
			if pin in used_pin:
				_die("R8 %s 与 %s 绑定同一 pin %s" % (n, used_pin[pin], pin))
			used_pin[pin] = n
		out["dout"].append({
			"name": n, "src": src, "ch": ch, "lvl": LEVEL[lvl], "safe": safe,
		})

	# ---- PWM ----
	for e in io.get("pwm", []):
		n = name_of(e, "pwm")
		src = src_of(e, "pwm")
		ch = int(e.get("channel", 0))
		freq = int(e.get("freqHz", 100))
		if freq <= 0:
			_die("R7 %s.freqHz 必须为正" % n)
		duty = int(e.get("safeDuty", 0))
		if duty < 0 or duty > 10000:
			_die("R7 %s.safeDuty 越界（0..10000）" % n)
		if src == "direct":
			if ch < 0 or ch >= pwm_channels:
				_die("R7 %s.channel=%d 越界（0..%d）"
				     % (n, ch, pwm_channels - 1))
			if ch in used_pwm:
				_die("R8 %s 与 %s 绑定同一 PWM 通道 %d"
				     % (n, used_pwm[ch], ch))
			used_pwm[ch] = n
		out["pwm"].append({
			"name": n, "src": src, "ch": ch, "duty": duty,
		})

	return out, cfg.get("adc", {}).get("groups", 0)


_OPS = {
	("din", "direct"): "IoHwAb_GpioDinOps",
	("din", "host"): "IoHwAb_HostDinOps",
	("ain", "direct"): "IoHwAb_AdcOps",
	("ain", "host"): "IoHwAb_HostAinOps",
	("dout", "direct"): "IoHwAb_GpioDoutOps",
	("dout", "host"): "IoHwAb_HostDoutOps",
	("pwm", "direct"): "IoHwAb_PwmOps",
	("pwm", "host"): "IoHwAb_HostPwmOps",
}


def Gen_Tables(board_cfg, dir):
	"""真正的生成入口：`board_cfg` 是已解析的 Board.json 字典。"""
	pins = {p["name"]: p for p in board_cfg.get("pins", [])}
	dio_channels = board_cfg.get("dioChannels", [])
	adc_groups = board_cfg.get("adc", {}).get("groups", 0)
	pwm_channels = board_cfg.get("pwm", {}).get("channels", 0)

	t, _ = _norm(board_cfg, pins, dio_channels, adc_groups, pwm_channels)

	h = open(os.path.join(dir, "IoHwAb_Cfg.h"), "w", newline="\n")
	GenHeader(h)
	h.write("#ifndef IOHWAB_CFG_H\n#define IOHWAB_CFG_H\n\n")
	h.write("/* 由 tools/generator/IoHwAb.py 从 Board.json 的 io 段生成，勿手改 */\n\n")

	for kind, prefix in (("din", "DIN"), ("ain", "AIN"),
	                     ("dout", "DOUT"), ("pwm", "PWM")):
		items = t[kind]
		h.write("/** @brief %s 逻辑通道（匿名枚举：ID 类型由 iohwab.h 统一 typedef） */\n" % prefix)
		h.write("enum {\n")
		if not items:
			h.write("\tIOHWAB_%s_NONE = 0,   /**< 本板无此类通道 */\n" % prefix)
		for i, e in enumerate(items):
			h.write("\tIOHWAB_%s_%-20s = %d%s\n"
			        % (prefix, toMacro(e["name"]), i,
			           "," if i < len(items) - 1 else ""))
		h.write("};\n\n")
		h.write("#define IOHWAB_%s_COUNT   (%du)\n\n" % (prefix, len(items)))

	h.write("#endif /* IOHWAB_CFG_H */\n")
	h.close()

	c = open(os.path.join(dir, "IoHwAb_Cfg.c"), "w", newline="\n")
	GenHeader(c)
	c.write('#include "iohwab.h"\n#include "IoHwAb_Cfg.h"\n\n')
	c.write("/* ============================ [ DIN ] ============================ */\n")
	if t["din"]:
		c.write("const IoHwAb_DinCfgType IoHwAb_DinCfgs[IOHWAB_DIN_COUNT] = {\n")
		for e in t["din"]:
			c.write("\t{ IOHWAB_SOURCE_%s, &%s, %du, %du, %du, %du },  /**< %s */\n"
			        % (e["src"].upper(), _OPS[("din", e["src"])], e["ch"],
			           e["lvl"], e["db_ticks"], e["stale"], e["name"]))
		c.write("};\n")
	else:
		c.write("const IoHwAb_DinCfgType IoHwAb_DinCfgs[1] = { { IOHWAB_SOURCE_DIRECT, NULL, 0u, 0u, 0u, 1u } };\n")

	c.write("\n/* ============================ [ AIN ] ============================ */\n")
	if t["ain"]:
		c.write("const IoHwAb_AinCfgType IoHwAb_AinCfgs[IOHWAB_AIN_COUNT] = {\n")
		for e in t["ain"]:
			c.write("\t{ IOHWAB_SOURCE_%s, &%s, %du, %du, %du, %d, %d, %du },  /**< %s */\n"
			        % (e["src"].upper(), _OPS[("ain", e["src"])], e["grp"],
			           e["ch"], e["shift"], e["factor"], e["offset"],
			           e["stale"], e["name"]))
		c.write("};\n")
	else:
		c.write("const IoHwAb_AinCfgType IoHwAb_AinCfgs[1] = { { IOHWAB_SOURCE_DIRECT, NULL, 0u, 0u, 0u, 1000, 0, 1u } };\n")

	c.write("\n/* ============================ [ DOUT ] ============================ */\n")
	if t["dout"]:
		c.write("const IoHwAb_DoutCfgType IoHwAb_DoutCfgs[IOHWAB_DOUT_COUNT] = {\n")
		for e in t["dout"]:
			c.write("\t{ IOHWAB_SOURCE_%s, &%s, %du, %du, %du },  /**< %s */\n"
			        % (e["src"].upper(), _OPS[("dout", e["src"])], e["ch"],
			           e["lvl"], e["safe"], e["name"]))
		c.write("};\n")
	else:
		c.write("const IoHwAb_DoutCfgType IoHwAb_DoutCfgs[1] = { { IOHWAB_SOURCE_DIRECT, NULL, 0u, 1u, 0u } };\n")

	c.write("\n/* ============================ [ PWM ] ============================ */\n")
	if t["pwm"]:
		c.write("const IoHwAb_PwmCfgType IoHwAb_PwmCfgs[IOHWAB_PWM_COUNT] = {\n")
		for e in t["pwm"]:
			c.write("\t{ IOHWAB_SOURCE_%s, &%s, %du, %du },  /**< %s */\n"
			        % (e["src"].upper(), _OPS[("pwm", e["src"])], e["ch"],
			           e["duty"], e["name"]))
		c.write("};\n")
	else:
		c.write("const IoHwAb_PwmCfgType IoHwAb_PwmCfgs[1] = { { IOHWAB_SOURCE_DIRECT, NULL, 0u, 0u } };\n")

	c.close()
	return [os.path.join(dir, "IoHwAb_Cfg.c")]
