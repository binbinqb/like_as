# -*- coding: utf-8 -*-
"""从 `Board.json` 生成 `IoHwAb_Cfg.{h,c}` 与 `Mux_Cfg.{h,c}`。

## 为什么放在 Board.py 里调、代码单独一个文件

`io` 段描述的是"这块板有哪些逻辑 IO、接到哪里"，与 `pins` / `dioChannels`
同源 —— 分成两个 JSON 反而要解决"谁先谁后"。但生成逻辑（校验、命名、表结构）
必须独立：加器件类型时只改本文件，不碰 Board.py。

## 支持的 source

| source | 含义 | Target 行为 |
|---|---|---|
| `direct` | MCU 直连（Dio/Adc/Pwm） | 调 HAL |
| `host` | Host 模拟通道 | 用 `IoHwAb_Host*Ops`；在 Target 上是返回 E_NOT_OK 的桩 |
| `mux` | 经 SelectBus 选通的 MUX（RS2260 等） | 用 `IoHwAb_Mux*Ops`，查 MuxManager 已发布样本 |

**同一份配置同时服务 Target 与 Host**：ID 空间一致，测试里用的枚举在板上也成立，
只是 Host 通道在板上恒为不可用（不伪造值）。

`mux` 通道的 `channel` 编码为 `(设备索引 << 8) | Y`，与 `IOHWAB_MUX_CH()` 一致；
设备索引按 `devices[]` 的顺序。这样生成表是一张扁平数组，运行期不做字符串查找。

## 校验（每条失败都终止生成，不产半份配置）

R1 名称唯一 / R2 直连 pin 存在 / R3 dir 匹配 / R4 电平合法 / R5 消抖拍数 /
R6 ADC 组范围 / R7 PWM 参数 / R8 物理资源不重复绑定 / R9 超时拍数 / R10 安全值缺省 /
R11 SelectBus 定义 / R12 设备定义 / R13 mux 通道引用 / R14 设备至少有一个通道 /
R15 ADC 组所有权唯一

@author binbina
"""

import os

from .helper import GenHeader, toMacro

__all__ = ["Gen_Tables"]

LEVEL = {"HIGH": 1, "LOW": 0}
COM = {"GPIO": 0, "ADC": 1}


def _die(msg):
	raise Exception("[IoHwAb] " + msg)


def _ticks(e, key, default, name, allow_zero=False):
	"""把毫秒配置换算成 10 ms 拍数，并按 R9 校验。"""
	ms = int(e.get(key, default))
	if allow_zero and ms == 0:
		return 0
	if ms < 10 or ms % 10:
		_die("R9 %s.%s=%d（必须是 10 的整数倍%s）"
		     % (name, key, ms, "，或 0" if allow_zero else "且 ≥10"))
	return ms // 10


def _mux(cfg, dio_channels, adc_groups):
	"""解析 selectBuses / devices，返回 (buses, devices, dev_idx)。"""
	buses = []
	bus_idx = {}
	for b in cfg.get("selectBuses", []):
		name = b.get("name", "")
		if not name:
			_die("R11 selectBus 缺 name")
		if name in bus_idx:
			_die("R11 selectBus 重名：%s" % name)
		pins = b.get("pins", [])
		if len(pins) != 3:
			_die("R11 %s.pins 必须是 [A, B, C]" % name)
		for p in pins:
			if p not in dio_channels:
				_die("R11 %s.pins 里的 %s 不在 dioChannels[]" % (name, p))
		bus_idx[name] = len(buses)
		buses.append({
			"name": name,
			"pins": [dio_channels.index(p) for p in pins],
			"settle": _ticks(b, "settleMs", 0, name, allow_zero=True),
			"adc_tmo": _ticks(b, "adcTimeoutMs", 30, name),
			"mask": 0,
		})

	devices = []
	dev_idx = {}
	for d in cfg.get("devices", []):
		name = d.get("name", "")
		if not name:
			_die("R12 设备缺 name")
		if name in dev_idx:
			_die("R12 设备重名：%s" % name)
		bus_name = d.get("selectBus", "")
		if bus_name not in bus_idx:
			_die("R12 %s.selectBus=%s 未定义（先建 selectBuses）" % (name, bus_name))
		ct = d.get("comType", "")
		if ct not in COM:
			_die("R12 %s.comType=%s（只允许 GPIO/ADC）" % (name, ct))
		if ct == "GPIO":
			pin = d.get("comPin", "")
			if pin not in dio_channels:
				_die("R12 %s.comPin=%s 不在 dioChannels[]" % (name, pin))
			com_ch = dio_channels.index(pin)
		else:
			grp = int(d.get("adcGroup", 0))
			ch = int(d.get("channel", 0))
			if (grp < 0) or (grp >= adc_groups) or (ch < 0):
				_die("R12 %s.adcGroup/channel 越界（组 0..%d）"
				     % (name, adc_groups - 1))
			com_ch = (grp << 8) | ch
		inh_ch = 0xFF
		inh_lvl = 0
		inh = d.get("inh")
		if inh:
			pin = inh.get("pin", "")
			if pin not in dio_channels:
				_die("R12 %s.inh.pin=%s 不在 dioChannels[]" % (name, pin))
			lvl = inh.get("activeLevel", "HIGH")
			if lvl not in LEVEL:
				_die("R12 %s.inh.activeLevel=%s" % (name, lvl))
			inh_ch = dio_channels.index(pin)
			inh_lvl = LEVEL[lvl]
		dev_idx[name] = len(devices)
		devices.append({
			"name": name, "bus": bus_idx[bus_name], "com": COM[ct],
			"com_ch": com_ch, "inh_ch": inh_ch, "inh_lvl": inh_lvl,
			"mask": 0,
		})
	return buses, devices, dev_idx


def _norm(cfg, pins, dio_channels, adc_groups, pwm_channels):
	"""校验并展开四张表，返回 (tables, buses, devices)。"""
	io = cfg.get("io", {})
	seen = {}
	used_pin = {}
	used_adc = {}
	used_pwm = {}
	used_mux = {}
	used_adc_groups = set()   # 直连 AIN 占用的组（R15 用）

	buses, devices, dev_idx = _mux(cfg, dio_channels, adc_groups)

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
		if s not in ("direct", "host", "mux"):
			_die("%s.source 非法：%s（只允许 direct/host/mux）" % (kind, s))
		if s == "mux" and kind not in ("din", "ain"):
			_die("%s 不支持 source=mux（只有输入能力经 MUX）" % kind)
		return s

	def mux_of(e, kind, n):
		"""解析 source=mux 的通道：返回编码后的 channel。"""
		dname = e.get("device", "")
		if dname not in dev_idx:
			_die("R13 %s.device=%s 未定义" % (n, dname))
		y = int(e.get("channel", 0))
		if (y < 0) or (y >= 8):
			_die("R13 %s.channel=%d 越界（Y 只允许 0..7）" % (n, y))
		dev = devices[dev_idx[dname]]
		want = COM["GPIO"] if kind == "din" else COM["ADC"]
		if dev["com"] != want:
			_die("R13 %s 与设备 %s 的 COM 类型不符（%s 需要 %s）"
			     % (n, dname, kind,
			        "GPIO" if kind == "din" else "ADC"))
		key = (dname, y)
		if key in used_mux:
			_die("R13 %s 与 %s 绑定同一设备通道 %s.Y%d"
			     % (n, used_mux[key], dname, y))
		used_mux[key] = n
		dev["mask"] |= (1 << y)
		return (dev_idx[dname] << 8) | y

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
		if src == "mux":
			ch = mux_of(e, "din", n)
		elif src == "direct":
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
		if src == "mux":
			ch = mux_of(e, "ain", n)
			grp = 0
		elif src == "direct":
			if grp < 0 or grp >= adc_groups:
				_die("R6 %s.adcGroup=%d 越界（0..%d）" % (n, grp, adc_groups - 1))
			key = (grp, ch)
			if key in used_adc:
				_die("R8 %s 与 %s 绑定同一 ADC 组/通道 %s"
				     % (n, used_adc[key], key))
			used_adc[key] = n
			used_adc_groups.add(grp)
			# 统一编码：channel = (group << 8) | slot，ops 只收 channel
			ch = (grp << 8) | ch
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

	# R14：设备没被任何通道引用 → 会白扫描，提示但不失败
	for dev in devices:
		if dev["mask"] == 0:
			print("  [IoHwAb] R14 设备 %s 未被任何通道引用，扫描掩码为 0"
			      % dev["name"])
	for bus in buses:
		for dev in devices:
			if dev["bus"] == buses.index(bus):
				bus["mask"] |= dev["mask"]

	# R15：一个 ADC 组只能有一个驱动者（AdcSampler 或 MuxManager）
	for dev in devices:
		if dev["com"] != COM["ADC"]:
			continue
		g = (dev["com_ch"] >> 8) & 0xFF
		if g in used_adc_groups:
			_die("R15 设备 %s 的 ADC 组 %d 已被直连 AIN 占用；"
			     "同一组只能有一个驱动者" % (dev["name"], g))

	return out, buses, devices


_OPS = {
	("din", "direct"): "IoHwAb_GpioDinOps",
	("din", "host"): "IoHwAb_HostDinOps",
	("din", "mux"): "IoHwAb_MuxDinOps",
	("ain", "direct"): "IoHwAb_AdcOps",
	("ain", "host"): "IoHwAb_HostAinOps",
	("ain", "mux"): "IoHwAb_MuxAinOps",
	("dout", "direct"): "IoHwAb_GpioDoutOps",
	("dout", "host"): "IoHwAb_HostDoutOps",
	("pwm", "direct"): "IoHwAb_PwmOps",
	("pwm", "host"): "IoHwAb_HostPwmOps",
}


def _gen_mux(buses, devices, dir):
	"""生成 Mux_Cfg.{h,c}；没有设备时也产一份"零设备"定义。"""
	h = open(os.path.join(dir, "Mux_Cfg.h"), "w", newline="\n")
	GenHeader(h)
	h.write("#ifndef MUX_CFG_H\n#define MUX_CFG_H\n\n")
	h.write("/* 由 tools/generator/IoHwAb.py 从 Board.json 的 selectBuses/devices 生成，勿手改 */\n\n")
	h.write("enum {\n")
	if not buses:
		h.write("\tMUX_BUS_NONE = 0,\n")
	for i, b in enumerate(buses):
		h.write("\tMUX_BUS_%-20s = %d,\n" % (toMacro(b["name"]), i))
	h.write("};\n\n")
	h.write("enum {\n")
	if not devices:
		h.write("\tMUX_DEV_NONE = 0,\n")
	for i, d in enumerate(devices):
		h.write("\tMUX_DEV_%-20s = %d,\n" % (toMacro(d["name"]), i))
	h.write("};\n\n")
	h.write("#define MUX_BUS_COUNT      (%du)\n" % len(buses))
	h.write("#define MUX_DEVICE_COUNT   (%du)\n\n" % len(devices))
	h.write("#endif /* MUX_CFG_H */\n")
	h.close()

	c = open(os.path.join(dir, "Mux_Cfg.c"), "w", newline="\n")
	GenHeader(c)
	c.write('#include "mux.h"\n\n')
	if buses:
		c.write("const Mux_BusCfgType Mux_BusCfgs[%d] = {\n" % len(buses))
		for b in buses:
			c.write("\t{ %du, %du, %du, %du, %du, 0x%02Xu },  /**< %s */\n"
			        % (b["pins"][0], b["pins"][1], b["pins"][2],
			           b["settle"], b["adc_tmo"], b["mask"], b["name"]))
		c.write("};\n")
	else:
		c.write("const Mux_BusCfgType Mux_BusCfgs[1] = { { 0u, 0u, 0u, 0u, 1u, 0u } };\n")

	if devices:
		c.write("\nconst Mux_DeviceCfgType Mux_DeviceCfgs[%d] = {\n" % len(devices))
		for d in devices:
			c.write("\t{ %du, %du, 0x%04Xu, %du, %du, 0x%02Xu },  /**< %s */\n"
			        % (d["bus"], d["com"], d["com_ch"], d["inh_ch"],
			           d["inh_lvl"], d["mask"], d["name"]))
		c.write("};\n")
	else:
		c.write("const Mux_DeviceCfgType Mux_DeviceCfgs[1] = "
		        "{ { 0u, 0u, 0u, MUX_NO_CHANNEL, 0u, 0u } };\n")

	c.write("\nconst uint8 Mux_BusCount = %du;\n" % len(buses))
	c.write("const uint8 Mux_DeviceCount = %du;\n" % len(devices))
	c.close()
	return [os.path.join(dir, "Mux_Cfg.c")]


def Tables(board_cfg):
	"""供其它生成器复用：返回 (io 四表, 总线表, 设备表)。

	Rte 生成器要按名字校验端口引用，必须拿到与 IoHwAb 完全相同的解析结果，
	否则两处规则会漂移。
	"""
	pins = {p["name"]: p for p in board_cfg.get("pins", [])}
	return _norm(board_cfg, pins, board_cfg.get("dioChannels", []),
	             board_cfg.get("adc", {}).get("groups", 0),
	             board_cfg.get("pwm", {}).get("channels", 0))


def Gen_Tables(board_cfg, dir):
	"""真正的生成入口：`board_cfg` 是已解析的 Board.json 字典。"""
	pins = {p["name"]: p for p in board_cfg.get("pins", [])}
	dio_channels = board_cfg.get("dioChannels", [])
	adc_groups = board_cfg.get("adc", {}).get("groups", 0)
	pwm_channels = board_cfg.get("pwm", {}).get("channels", 0)

	t, buses, devices = _norm(board_cfg, pins, dio_channels,
	                          adc_groups, pwm_channels)

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
	return [os.path.join(dir, "IoHwAb_Cfg.c")] + _gen_mux(buses, devices, dir)
