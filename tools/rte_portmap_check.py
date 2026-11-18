#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    rte_portmap_check.py
@brief   验证"换 BCM 项目只改 Board.json"这条承诺（P1~P5）

@details @section WHY 为什么要专门验这件事

          `RTE V0.2` 的卖点是：端口绑到哪条报文、哪个 IO 通道，全在
          `Board.json` 的 `rte.ports` 里，业务代码不动。这句话很容易在
          文档里成立、在代码里不成立 —— 只要有人在业务文件里写了一次
          `BcmSig_*`，换项目就得改业务。

          所以这里用四条互相独立的证据：

          | 项 | 断言 | 证伪方式 |
          |---|---|---|
          | P1 | 业务文件（去掉注释后）不出现下层标识符 | 往 bcm_biz.c 加一行 `BcmSig_RxRead(...)` 即失败 |
          | P2 | 业务引用的 `RTE_PORT_*` 都在生成头里 | 删掉 Board.json 里一个端口即失败 |
          | P3 | 用**变体配置**生成的端口表，业务源仍能编译 | 业务里写死端口号而非端口名即失败 |
          | P4 | 变体确实改变了绑定与索引 | 若变体与真实配置相同，P3 就成了空转 |
          | P5 | 目标文件只引用 `Rte_*` / `Platform_*` | 业务直接调 `BcmSig_*` 时 `nm -u` 会多出符号 |

          P3 之所以用"变体配置"而不是"真实配置"：真实配置下业务当然能编过，
          证明不了任何事。变体把驻车制动改成**本地开关**、把制动灯改成
          **本地输出**，索引也整体移位 —— 这正是"另一个 BCM 项目"的样子。

@note    P3/P5 需要 `gcc` 与 `nm`（与 `tools/host_build.py` 同一套 mingw）。

@author  binbina
@version V1.0.0

@par 修改记录
| 版本   | 日期       | 作者    | 变更说明 |
|--------|------------|---------|----------|
| V1.0.0 | 2026-11-18 | binbina | 首版：P1~P5 |
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

BOARD_JSON = os.path.join(ROOT, "app", "platform", "cvm0146", "src",
                          "config", "Board", "Board.json")
GEN_H = os.path.join(ROOT, "app", "platform", "cvm0146", "src",
                     "config", "Board", "GEN", "Rte_Ports.h")
BIZ_C = os.path.join(ROOT, "app", "app", "src", "bcm_biz.c")
BIZ_H = os.path.join(ROOT, "app", "app", "src", "bcm_biz.h")

CC = "C:/soft/mingw64/bin/gcc.exe"
NM = "C:/soft/mingw64/bin/nm.exe"

# 业务层**禁止**出现的下层符号前缀（P1）
FORBIDDEN = [
	"BCM_SIG_", "BcmSig_", "Bcm_SwStateType", "Bcm_SigValidityType",
	"IOHWAB_", "IoHwAb_",
	"Com_", "CanIf_", "Can_", "PduR_", "CanNm_", "Dcm_", "Dem_",
]
# 业务层**禁止** include 的头（P1）
FORBIDDEN_INC = [
	"bcm_sig.h", "iohwab.h", "mux.h", "Com.h", "CanIf.h", "Can.h",
	"PduR.h", "CanNm.h", "Dcm.h", "Dem.h", "adc_sampler.h",
]
# 业务目标文件允许引用的外部符号（P5）
ALLOWED_UNDEF = {"Rte_Read", "Rte_Write", "Platform_NowMs"}

results = []


def check(name, cond, detail=""):
	results.append((name, bool(cond), detail))
	print(("  PASS  " if cond else "  FAIL  ") + name
	      + (("   " + detail) if (detail and not cond) else ""))


def read(p):
	return io.open(p, encoding="utf-8").read()


def strip_comments(src):
	"""去掉 // 与 /* */ 注释，保留字符串字面量（避免误伤 "..." 里的字符）。

	只用于 P1 的源码扫描：文档注释里提到 `bcm_sig.h` 是正常且必要的，
	不能因为注释里出现就判违规。
	"""
	out = []
	i = 0
	n = len(src)
	while i < n:
		c = src[i]
		nc = src[i + 1] if (i + 1) < n else ""
		if (c == "/") and (nc == "/"):
			while (i < n) and (src[i] != "\n"):
				i += 1
		elif (c == "/") and (nc == "*"):
			i += 2
			while (i + 1 < n) and not ((src[i] == "*") and (src[i + 1] == "/")):
				i += 1
			i += 2
		elif c == '"':
			out.append(c)
			i += 1
			while (i < n) and (src[i] != '"'):
				if src[i] == "\\":
					out.append(src[i])
					i += 1
				if i < n:
					out.append(src[i])
					i += 1
			if i < n:
				out.append(src[i])
				i += 1
		else:
			out.append(c)
			i += 1
	return "".join(out)


def gen_header(cfg, d):
	# 生成器会往 stdout 打 "GEN <path>"；自测里不需要，免得混进断言输出
	with contextlib.redirect_stdout(io.StringIO()):
		R.Gen_Rte(cfg, d)
	return read(os.path.join(d, "Rte_Ports.h"))


def port_ids(hdr):
	"""解析生成的端口定义：{名字: 值}"""
	out = {}
	for m in re.finditer(r"RTE_PORT_([A-Z0-9_]+)\s*=\s*(\d+)\s*,", hdr):
		out[m.group(1)] = int(m.group(2))
	return out


def port_refs(hdr):
	"""解析表初始化列表：[(名字, dir, kind, ref)]"""
	names = []
	for m in re.finditer(r"RTE_PORT_([A-Z0-9_]+)\s*=\s*(\d+)\s*,", hdr):
		names.append((int(m.group(2)), m.group(1)))
	names.sort()
	body = hdr.split("RTE_PORT_CFG_LIST", 1)[-1]
	rows = re.findall(r"\{\s*(RTE_DIR_\w+),\s*(RTE_KIND_\w+),\s*\(uint16\)(\w+)\s*\}", body)
	out = []
	for i, (d, k, ref) in enumerate(rows):
		name = names[i][1] if i < len(names) else "?%d" % i
		out.append((name, d, k, ref))
	return out


def compile_obj(src, incs, obj, syntax_only=False):
	cmd = [CC, "-std=c99", "-Wall", "-Wextra"]
	if syntax_only:
		cmd.append("-fsyntax-only")
	for i in incs:
		cmd += ["-I", i]
	cmd.append(src)
	if not syntax_only:
		cmd += ["-c", "-o", obj]
	p = subprocess.run(cmd, capture_output=True, text=True)
	msg = (p.stdout + p.stderr).strip()
	return p.returncode == 0, msg


def undef_syms(obj):
	p = subprocess.run([NM, "-u", obj], capture_output=True, text=True)
	out = set()
	for line in p.stdout.splitlines():
		parts = line.split()
		if len(parts) >= 2:
			out.add(parts[-1])
	return out


def main():
	print("== RTE 端口映射：换项目可行性验证 ==")

	biz_src = read(BIZ_C) + "\n" + read(BIZ_H)
	biz_code = strip_comments(biz_src)

	# ---- P1 业务层不碰下层 ----
	hits = []
	for tok in FORBIDDEN:
		# 只看标识符出现，不区分大小写容易误伤，这里精确匹配
		if re.search(r"\b" + re.escape(tok), biz_code):
			hits.append(tok)
	check("P1 业务文件（去注释）不含下层标识符", not hits, "命中=%s" % hits)

	bad_inc = [h for h in FORBIDDEN_INC if h in biz_code]
	check("P1 业务文件不 include 下层头", not bad_inc, "命中=%s" % bad_inc)

	# ---- P1b 端口实参必须是 RTE_PORT_* 标识符，不能写死数字 ----
	# 写死数字时 P2/P3/P5 都会"通过"（因为压根没引用端口名），
	# 但换项目后它会指向另一个端口，而且编译期毫无提示。
	lit = re.findall(r"Rte_(?:Read|ReadU16|ReadS32|Write)\(\s*([^,)]+)",
	                 biz_code)
	bad_lit = [a.strip() for a in lit
	           if not a.strip().startswith("RTE_PORT_")]
	check("P1b 端口实参都是端口名（无写死数字）",
	      not bad_lit, "可疑实参=%s" % bad_lit)

	# ---- P2 业务引用的端口都在生成头里 ----
	hdr = read(GEN_H)
	defined = set(re.findall(r"RTE_PORT_([A-Z0-9_]+)\b", hdr))
	used = set(re.findall(r"RTE_PORT_([A-Z0-9_]+)\b", biz_code))
	# RTE_PORT_NUM 是计数宏，不是端口
	used.discard("NUM")
	missing = sorted(used - defined)
	check("P2 业务引用的端口全部存在于 Rte_Ports.h",
	      (not missing) and (len(used) > 0),
	      "缺失=%s 引用=%s" % (missing, sorted(used)))

	# ---- P3/P4 变体配置：改绑定 + 改索引 ----
	cfg = json.loads(read(BOARD_JSON))
	variant = json.loads(json.dumps(cfg))   # 深拷贝
	ports = variant["rte"]["ports"]
	# 1) 去掉会被"复用"的独立端口，避免 E6（同 kind+ref 重复绑定）
	ports = [p for p in ports if p["name"] not in ("DOOR_FL", "LED_R")]
	# 2) 驻车制动从 CAN 输入改为本地开关；制动灯从 CAN 输出改为本地输出
	for p in ports:
		if p["name"] == "PARK_BRAKE":
			p["kind"] = "io_din"
			p["ref"] = "DOOR_FL"
		elif p["name"] == "BRAKE_LAMP":
			p["kind"] = "io_dout"
			p["ref"] = "LED_R"
	# 3) 末尾端口挪到最前：所有索引整体移位
	ports.insert(0, ports.pop())
	variant["rte"]["ports"] = ports

	real_ids = port_ids(hdr)
	real_refs = {n: (d, k, r) for (n, d, k, r) in port_refs(hdr)}

	with tempfile.TemporaryDirectory() as d:
		vh = gen_header(variant, d)
		var_ids = port_ids(vh)
		var_refs = {n: (d, k, r) for (n, d, k, r) in port_refs(vh)}

		# 变体必须仍覆盖业务用到的端口名（否则 P3 无意义）
		cover = sorted(used - set(var_ids))
		check("P4a 变体配置仍包含业务用到的端口名", not cover, "缺失=%s" % cover)

		# 绑定与索引都必须真的变了，否则 P3 是空转
		chg_bind = [n for n in ("PARK_BRAKE", "BRAKE_LAMP")
		            if n in real_refs and n in var_refs
		            and real_refs[n] != var_refs[n]]
		chg_idx = [n for n in used
		           if n in real_ids and n in var_ids
		           and real_ids[n] != var_ids[n]]
		check("P4b 变体改变了绑定（PARK_BRAKE/BRAKE_LAMP → 本地 IO）",
		      len(chg_bind) == 2,
		      "变化=%s 原=%s 新=%s" % (chg_bind,
		                              real_refs.get("PARK_BRAKE"),
		                              var_refs.get("PARK_BRAKE")))
		check("P4c 变体改变了端口索引（证明不是同一份表）",
		      len(chg_idx) >= 1, "变化=%s" % chg_idx)

		# ---- P3 同一份业务源，用变体头编译 ----
		incs = [os.path.join(ROOT, "app", "include"),
		        os.path.join(ROOT, "app", "app", "src"),
		        os.path.join(ROOT, "infras", "include"),
		        d]
		ok, msg = compile_obj(BIZ_C, incs, None, syntax_only=True)
		check("P3a 业务源在变体配置下能编译（换项目不改业务）", ok,
		      msg.splitlines()[-1] if msg else "")

		# ---- P5 目标文件只引用 Rte_*/Platform_* ----
		obj = os.path.join(d, "bcm_biz.o")
		ok2, msg2 = compile_obj(BIZ_C, incs, obj)
		check("P5a 业务能编出目标文件", ok2,
		      msg2.splitlines()[-1] if msg2 else "")
		if ok2:
			extra = sorted(undef_syms(obj) - ALLOWED_UNDEF)
			check("P5b 目标文件只引用 Rte_* / Platform_*",
			      not extra, "多出符号=%s" % extra)
		else:
			check("P5b 目标文件只引用 Rte_* / Platform_*", False, "未产出 .o")

	# ---- P5 生成头自洽：条目数 == 计数，索引连续 ----
	ids = sorted(real_ids.values())
	check("P5c Rte_Ports.h 条目数 == RTE_PORT_NUM",
	      ("#define RTE_PORT_NUM     (%du)" % len(ids)) in hdr,
	      "条目=%d" % len(ids))
	check("P5d 端口索引 0..N-1 连续无空洞", ids == list(range(len(ids))),
	      "索引=%s" % ids)

	failed = [r for r in results if not r[1]]
	print("-- %d 项断言，%d 项失败" % (len(results), len(failed)))
	return 0 if not failed else 1


if __name__ == "__main__":
	sys.exit(main())
