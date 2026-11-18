# -*- coding: utf-8 -*-
"""从 `Board.json` 的 `rte` 段生成 `Rte_Ports.h`（RTE 端口枚举 + 表初始化列表）。

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

## 校验（每条失败都终止生成，不产半份配置）

E1 端口名唯一且是合法标识符 / E2 kind 已知 / E3 type·dir 与 kind 一致 /
E4 io 引用的通道必须存在于 `io` 四表 / E5 com 引用必须是合法 C 标识符
（存在性由编译器检查）/ E6 同一 (kind, ref) 不得被两个端口绑定

@author binbina
"""

import os
import re

from .helper import GenHeader, toMacro
from .IoHwAb import Tables

__all__ = ["Gen_Rte"]

_IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")

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

	return []
