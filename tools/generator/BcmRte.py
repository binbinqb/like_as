# -*- coding: utf-8 -*-
"""从 `Board.json` 的 `rte` 段生成 `Rte_Ports.h`（端口枚举 + 表初始化列表）
与 `Rte_Schedule.h`（runnable 调度表初始化列表）。

## 为什么端口表也放在 Board.json

RTE 端口绑定的是"这块板上有什么 IO、这台车有哪些信号"，与 `io` 段同源；
换一个 BCM 项目就是换一份 `Board.json`。等配置复杂到需要独立评审时再拆
`Rte.json` —— 现在拆只会多一条同步链。

## 端口 model

```json
"rte": {
  "ports": [
    {"name": "LIGHT_LOW", "kind": "com_tx", "ref": "BCM_SIG_LOW_BEAM"},
    {"name": "DOOR_FL",   "kind": "io_din", "ref": "DOOR_FL"},
    {"name": "VBAT_MV",   "kind": "io_ain_phys", "ref": "VBAT_ADC"}
  ]
}
```

`dir` / `type` 可省略（按 kind 推），写了就必须与 kind 一致 —— 允许显式写是
为了让配置**自解释**，但写错要报错，不能"以写错的为准"。

## 调度表 model（10.5）

```json
"rte": {
  "schedule": [
    {"func": "BcmSig_MainFunction", "period_ms": 10},
    {"func": "IoHwAb_MainFunction", "period_ms": 20}
  ]
}
```

**数组顺序 = 同一拍内的执行顺序**。依赖关系靠表序表达（BcmSig 在 BcmBiz
之前、AdcSampler 在 IoHwAb 之前）；跨周期的依赖不允许 —— 周期不同的两个
runnable 不会每拍都同拍执行，靠"跨周期顺序"表达依赖必然偶发失效。
周期由 `rte_sched.c` 按基准拍（10 ms）分频实现，表里折算成拍数。

## 校验（每条失败都终止生成，不产半份配置）

E1 端口名唯一且是合法标识符 / E2 kind 已知 / E3 type·dir 与 kind 一致 /
E4 io 引用的通道必须存在于 `io` 四表 / E5 com 引用必须是合法 C 标识符
（存在性由编译器检查）/ E6 同一 (kind, ref) 不得被两个端口绑定

S1 调度 func 是合法 C 标识符（存在性由编译器检查）/
S2 period_ms 为 10 的倍数且 ≥10 / S3 同一 func 不得出现两次
（出现两次 = 该 runnable 每拍跑两次，时间基准减半 —— A1 事故的调度表版）/
S4 schedule 段缺省或为空 → 合法，生成一张只有 NULL 占位的空表

@author binbina
"""

import os
import re

from .helper import GenHeader, toMacro
from .IoHwAb import Tables

__all__ = ["Gen_Rte"]

_IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")

# 调度基准拍（ms）：必须与 main.c 的 BSW_PERIOD_MS 一致，
# runnable 的 period_ms 是它的倍数，表里折算成拍数
SCHED_BASE_MS = 10

# kind -> (方向, 类型, 后端枚举名, io 表名或 None)
KINDS = {
	"com_tx":      ("out", "BOOL", "RTE_KIND_COM_TX", None),
	"com_rx":      ("in",  "BOOL", "RTE_KIND_COM_RX", None),
	"io_din":      ("in",  "BOOL", "RTE_KIND_DIN", "din"),
	"io_ain_raw":  ("in",  "U16",  "RTE_KIND_AIN_RAW", "ain"),
	"io_ain_phys": ("in",  "S32",  "RTE_KIND_AIN_PHYS", "ain"),
	"io_dout":     ("out", "BOOL", "RTE_KIND_DOUT", "dout"),
}

_IO_PREFIX = {"din": "IOHWAB_DIN_", "ain": "IOHWAB_AIN_", "dout": "IOHWAB_DOUT_"}


def _die(msg):
	raise Exception("[Rte] " + msg)


def _gen_schedule(board_cfg, dir):
	"""校验 rte.schedule（S1~S4）并生成 Rte_Schedule.h。

	返回生成的文件路径列表。表体只含 {拍数, 函数名}，函数存在性由
	编译器检查（与端口的 com ref 同一策略）。
	"""
	sched = board_cfg.get("rte", {}).get("schedule", [])
	entries = []
	seen_fn = {}

	for e in sched:
		fn = e.get("func", "")
		if (not fn) or (not _IDENT.match(fn)):
			_die("S1 调度 func 非法：%r（必须是 C 标识符）" % fn)
		if fn in seen_fn:
			_die("S3 调度 func 重复：%s（%s 也在表里）—— 同一 runnable "
			     "每拍会执行两次，时间基准减半" % (fn, seen_fn[fn]))
		seen_fn[fn] = fn

		p = e.get("period_ms", None)
		if (not isinstance(p, int)) or (p < SCHED_BASE_MS) or (p % SCHED_BASE_MS != 0):
			_die("S2 %s.period_ms=%r（必须是 %d 的倍数且 ≥%d）"
			     % (fn, p, SCHED_BASE_MS, SCHED_BASE_MS))
		entries.append({"fn": fn, "ticks": p // SCHED_BASE_MS, "ms": p})

	# 只生成**头**：与端口表同一策略，表体由 app 层 rte_sched.c 展开，
	# 避免平台库反向依赖应用层。
	h = open(os.path.join(dir, "Rte_Schedule.h"), "w", newline="\n")
	GenHeader(h)
	h.write("#ifndef RTE_SCHEDULE_H\n#define RTE_SCHEDULE_H\n\n")
	h.write("/* 由 tools/generator/BcmRte.py 从 Board.json 的 rte.schedule 生成，勿手改 */\n")
	h.write("/* 展开处（rte_sched.c）必须先 include rte_cfg.h（Rte_SchedFunc 类型） */\n\n")
	h.write("#define RTE_SCHED_BASE_MS  (%du)\n\n" % SCHED_BASE_MS)
	h.write("#define RTE_SCHED_NUM      (%du)\n\n" % max(len(entries), 1))

	# runnable 原型：表体直接引用函数名，声明必须与表同头 —— 否则
	# 每换一个项目（增删 runnable）都要在 rte_sched.c 手工补 include，
	# "换项目只改 Board.json"就不成立。
	if entries:
		h.write("/* runnable 原型（定义在各自的组件 .c 里） */\n")
		for e in entries:
			h.write("extern void %s(void);\n" % e["fn"])
		h.write("\n")

	h.write("/** @brief 调度表初始化列表（由 rte_sched.c 展开为 const 数组，顺序即执行顺序） */\n")
	h.write("#define RTE_SCHEDULE_LIST { \\\n")
	if not entries:
		# S4：空表合法。占一行 NULL，rte_sched.c 跳过；占位是为了零长度数组不可移植
		h.write("\t{ 1u, ((Rte_SchedFunc)0) } \\\n")
	for i, e in enumerate(entries):
		sep = "," if i < len(entries) - 1 else ""
		h.write("\t{ %du, %s }%s \t/* %d ms */ \\\n"
		        % (e["ticks"], e["fn"], sep, e["ms"]))
	h.write("}\n\n")
	h.write("#endif /* RTE_SCHEDULE_H */\n")
	h.close()

	return [os.path.join(dir, "Rte_Schedule.h")]


def Gen_Rte(board_cfg, dir):
	"""生成 Rte_Cfg.h / Rte_Cfg.c；无端口时也产一份"空表"定义。"""
	io, _buses, _devices = Tables(board_cfg)
	ports = board_cfg.get("rte", {}).get("ports", [])

	seen = {}
	used_ref = {}
	out = []

	for e in ports:
		name = e.get("name", "")
		if (not name) or (not _IDENT.match(name)):
			_die("E1 端口名非法：%r（必须是 C 标识符）" % name)
		if name in seen:
			_die("E1 端口名重复：%s" % name)
		seen[name] = True

		kind = e.get("kind", "")
		if kind not in KINDS:
			_die("E2 %s.kind=%s（只允许 %s）"
			     % (name, kind, "/".join(sorted(KINDS))))
		dir_, type_, kind_enum, table = KINDS[kind]

		# 写了就必须对；没写按 kind 推
		if ("dir" in e) and (e["dir"] != dir_):
			_die("E3 %s.dir=%s，但 %s 必须是 %s"
			     % (name, e["dir"], kind, dir_))
		if ("type" in e) and (e["type"] != type_):
			_die("E3 %s.type=%s，但 %s 必须是 %s"
			     % (name, e["type"], kind, type_))

		ref = e.get("ref", "")
		if not ref:
			_die("E4 %s 缺 ref" % name)

		if table is not None:
			names = {it["name"] for it in io[table]}
			if ref not in names:
				_die("E4 %s.ref=%s 不在 io.%s 里（可用：%s）"
				     % (name, ref, table, ", ".join(sorted(names)) or "空"))
			ref_c = "%s%s" % (_IO_PREFIX[table], toMacro(ref))
		else:
			if not _IDENT.match(ref):
				_die("E5 %s.ref=%r 不是合法 C 标识符" % (name, ref))
			ref_c = ref

		key = (kind, ref)
		if key in used_ref:
			_die("E6 %s 与 %s 绑定同一 %s/%s"
			     % (name, used_ref[key], kind, ref))
		used_ref[key] = name

		out.append({
			"name": name, "dir": dir_, "type": type_,
			"kind": kind, "kind_enum": kind_enum, "ref": ref, "ref_c": ref_c,
		})

	# 只生成**头**：端口表由 `bcm_rte.c` 展开。
	# 若生成 .c，它会被编进平台库，而平台库的 include 路径里没有 app 头
	# （`bcm_sig.h`）—— 那会让平台层反向依赖应用层。头方案没有这个问题，
	# 也不引入额外的构建顺序依赖。
	h = open(os.path.join(dir, "Rte_Ports.h"), "w", newline="\n")
	GenHeader(h)
	h.write("#ifndef RTE_PORTS_H\n#define RTE_PORTS_H\n\n")
	h.write("/* 由 tools/generator/BcmRte.py 从 Board.json 的 rte 段生成，勿手改 */\n\n")
	h.write("enum {\n")
	if not out:
		h.write("\tRTE_PORT_NONE = 0,   /**< 本板无端口 */\n")
	for i, e in enumerate(out):
		h.write("\tRTE_PORT_%-24s = %d,\n" % (toMacro(e["name"]), i))
	h.write("};\n\n")
	h.write("#define RTE_PORT_NUM     (%du)\n\n" % len(out))

	h.write("/** @brief 端口表初始化列表（由 rte_cfg.c 展开为 const 数组） */\n")
	h.write("#define RTE_PORT_CFG_LIST { \\\n")
	if not out:
		h.write("\t{ RTE_DIR_IN, RTE_KIND_DIN, 0u } \\\n")
	for i, e in enumerate(out):
		sep = "," if i < len(out) - 1 else ""
		h.write("\t{ RTE_DIR_%s, %s, (uint16)%s }%s \\\n"
		        % (e["dir"].upper(), e["kind_enum"], e["ref_c"], sep))
	h.write("}\n\n")
	h.write("#endif /* RTE_PORTS_H */\n")
	h.close()

	# 返回值固定为空：本生成器只产**头文件**（Rte_Ports.h / Rte_Schedule.h）。
	# 返回路径会被 building.py 的 Generate() 当成编译源注册（PkgGlob 会为
	# 每个 .h 写一条 `Glob('Xxx.h')`，SCons 直接报"不知道怎么编 .h"）。
	# 头文件对构建不可见没关系 —— 它们在 GEN/ 目录里，靠 include 路径生效。
	_gen_schedule(board_cfg, dir)
	return []
