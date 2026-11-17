#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
mat_report.py —— 输出真实矩阵的「网络/帧类型/ID/方向/协议/PDU/路由/邮箱」清单。

《推进指南》第一轮任务单第 6 条。数据来自三处，交叉对账：
  1. DBC（报文与信号事实源）—— 客户文件不入库，本地缺失时明确 SKIP
  2. Can_Cfg.c 的邮箱表（CanHw_MsgCfgs0/1，硬件覆盖集合）
  3. CanIf_Cfg.c 的 RX 软件过滤表（软件需要集合）+ Hoh 表（TX 路径）

对账重点不是"列出来"，而是三类差异：
  - DBC 里有、CanIf 软件过滤表没覆盖的 RX 报文（业务收不到）
  - CanIf 能匹配、但硬件邮箱掩码不放行的（软件白配）
  - DBC 的"我发"报文与 Hoh 表（TX 路径）对不上的

已知限制（指南 §4.2 记录）：
  - 帧类型的扩展标志来自生成器的 `id > 0x7FF` 启发式，不是可靠事实，
    报告里两列都给（原始 ID 与生成器判定），方便人工核对
  - 协议分类按 ID 的 PF 段与报文名推断，最终以整车协议文档为准

用法：python tools/mat_report.py [--dbc 路径]（缺省跑 CAN0/CAN1 两份）
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tools"))

CFG = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..",
                   "app", "platform", "cvm0146", "src", "config")
ME = "BCM"


def strip_comments(text):
    """去掉 /* */ 与 // 注释再切字段：配置表里注释是常态，不能当字段。"""
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    return text


def parse_hw_defines(path):
    d = {}
    if os.path.isfile(path):
        for m in re.finditer(r"#define\s+(CAN_HW_[A-Z0-9_]+)\s+\(?((?:0x)?[0-9A-Fa-f]+u?)\)?",
                             open(path, encoding="utf-8", errors="replace").read()):
            try:
                d[m.group(1)] = int(m.group(2).rstrip("uUlL"), 0)
            except ValueError:
                pass
    return d


def resolve(tok, defines):
    """'CAN_HW_MASK_J1939_SEG_FE' / '0x1FFFFFFFu' / '0u' → int，失败 None。"""
    tok = tok.strip().rstrip("uU")
    if tok in defines:
        return defines[tok]
    try:
        return int(tok, 0)
    except ValueError:
        return None


def load_dbc(path):
    """DBC → [{id, name, dlc, tx, ext(gen), cycle, nSigs}]。文件缺失返回 None。"""
    if not os.path.isfile(path):
        return None
    from generator.dbc import dbc
    msgs = []
    for m in dbc(path):
        raw = m["id"]
        msgs.append({
            "id": raw & 0x1FFFFFFF,
            "name": m["name"],
            "dlc": m.get("dlc", 8),
            "tx": m.get("node", m.get("transmitter", "")),
            "ext_gen": bool(raw & 0x80000000),
            "cycle": m.get("CycleTime"),
            "nSigs": len(m["signals"]),
        })
    return msgs


def parse_hw_id_defines(path):
    return parse_hw_defines(path)


def parse_mb_tables(path):
    """Can_Cfg.c 的 CanHw_MsgCfgsN[] → {(ch, id): [entry]}。

    条目布局：{ mb, msgType, canId(宏或数字), isExt, dir 宏, dlc, intEnable, mask(宏) }
    """
    out = {}
    if not os.path.isfile(path):
        return out
    defines = parse_hw_defines(os.path.join(CFG, "Can_HwCfg.h"))
    text = open(path, encoding="utf-8", errors="replace").read()
    for ch, tbl in enumerate(("CanHw_MsgCfgs0[]", "CanHw_MsgCfgs1[]")):
        m = re.search(re.escape(tbl) + r"\s*=\s*\{(.*?)\n\};", text, re.S)
        if not m:
            continue
        body = strip_comments(m.group(1))
        for ent in re.finditer(r"\{([^{}]+)\}", body):
            f = [x.strip() for x in ent.group(1).split(",") if x.strip()]
            if len(f) < 8:
                continue
            try:
                mb = int(f[0].rstrip("uU"), 0)
                dlc = int(f[5].rstrip("uU"), 0)
            except ValueError:
                continue
            idv = resolve(f[2], defines)
            if idv is None:
                continue
            isext = "true" in f[3].lower()
            direction = "TX" if "MB_TX" in f[4] else "RX"
            mask = resolve(f[7], defines)
            if mask is None:
                mask = 0x1FFFFFFF if isext else 0x7FF
            out.setdefault((ch, idv), []).append(
                {"ch": ch, "mb": mb, "dir": direction, "ext_hw": isext,
                 "mask": mask, "dlc": dlc})
    return out


def parse_canif_rx(path):
    """CanIf_Cfg.c 的 RX 过滤表 → [{ch, canid, mask, pduId, rxInd, hoh}]。"""
    out = []
    if not os.path.isfile(path):
        return out
    text = open(path, encoding="utf-8", errors="replace").read()
    for ch, tbl in enumerate(("CanIf_RxPdus_CAN0[]", "CanIf_RxPdus_CAN1[]")):
        m = re.search(re.escape(tbl) + r"\s*=\s*\{(.*?)\n\};", text, re.S)
        if not m:
            continue
        body = strip_comments(m.group(1))
        for ent in re.finditer(r"\{([^{}]+)\}", body):
            f = [x.strip() for x in ent.group(1).split(",") if x.strip()]
            if len(f) < 5:
                continue
            canid = resolve(f[2], {})
            mask = resolve(f[3], {})
            hoh = resolve(f[4], {})
            if canid is None or mask is None or hoh is None:
                continue
            out.append({"ch": ch, "canid": canid, "mask": mask,
                        "pduId": f[1], "rxInd": f[0], "hoh": hoh})
    return out


def parse_hoh_tx(path):
    """CanHw_Hohs[] → [{ch, mb, id, dlc}]（TX 路径）。"""
    out = []
    if not os.path.isfile(path):
        return out
    defines = parse_hw_defines(os.path.join(CFG, "Can_HwCfg.h"))
    text = open(path, encoding="utf-8", errors="replace").read()
    m = re.search(r"CanHw_Hohs\[CAN_HW_HOH_NUM\]\s*=\s*\{(.*?)\n\};", text, re.S)
    if not m:
        return out
    for ent in re.finditer(r"\{([^{}]+)\}", strip_comments(m.group(1))):
        f = [x.strip().rstrip("uU") for x in ent.group(1).split(",") if x.strip()]
        if len(f) < 4:
            continue
        try:
            ch = int(f[0], 0)
            mb = int(f[1], 0)
            dlc = int(f[3], 0)
        except ValueError:
            continue
        idv = resolve(f[2], defines)
        if idv is None:
            continue
        out.append({"ch": ch, "mb": mb, "id": idv, "dlc": dlc})
    return out


def protocol_of(idv, ext, name=""):
    """按 ID 的 PF 段推断协议归属。PF=(id>>16)&0xFF，PGN 见 SAE J1939-81。"""
    n = name.upper()
    if idv in (0x7E0, 0x7E8) or "DIAG" in n:
        return "诊断 ISO-TP"
    if "NM" in n or idv == 0x500:
        return "网络管理"
    if ext:
        pf = (idv >> 16) & 0xFF
        if pf == 0xEC:
            return "J1939 TP.CM（多包传输控制）"
        if pf == 0xEB:
            return "J1939 TP.DT（多包传输数据）"
        if pf == 0xEE:
            return "J1939 地址声明（NAME）"
        if pf >= 0xF0:
            return "J1939 PDU2 业务 PGN=0x%04X" % ((idv >> 8) & 0xFFFF)
        return "J1939 PDU1 业务 PF=0x%02X" % pf
    return "业务（标准帧）"


def rx_target(rxind):
    if "RxPduR" in rxind:
        return "PduR"
    if "Diag" in rxind:
        return "CanTp→Dcm"
    if "Com" in rxind and "ComRx" not in rxind:
        return "Com"
    if "Nm" in rxind:
        return "Nm"
    return "App(shim)"


def fmt_hex(idv, ext):
    if ext:
        return "0x%08X" % idv
    return "0x%03X" % idv


def analyze_channel(ch, dbc_msgs, mbtab, rxlist, txtab):
	"""把一条通道的"DBC 事实 vs 硬件邮箱 vs 软件过滤"对成结构化结果。

	返回值（供 validate 与报告共用，避免两套判定各说各话）：
	  skip  : DBC 缺失
	  rows  : 每条报文一行（已格式化成报告要显示的字符串）
	  gaps  : 覆盖缺口，每项 {kind, id, name, detail}
	  extra : CanIf 表里有、DBC 没列的条目（测试/诊断入口）
	"""
	if dbc_msgs is None:
		return {"skip": True, "rows": [], "gaps": [], "extra": []}

	rows = []
	gaps = []

	for m in sorted(dbc_msgs, key=lambda x: x["id"]):
		is_me_tx = (m["tx"] == ME)
		direction = "TX" if is_me_tx else "RX"
		proto = protocol_of(m["id"], m["ext_gen"], m["name"])

		mbstr = "\u2014"
		rx_entry = None
		if direction == "RX":
			# 1) 软件过滤表：掩码能放行即算覆盖（不要求完全相等）
			for e in rxlist:
				if e["ch"] == ch and (m["id"] & e["mask"]) == (e["canid"] & e["mask"]):
					rx_entry = e
					break
			# 2) 硬件邮箱：段基址 & 掩码 == 报文 & 掩码 即放行
			for key in sorted(mbtab.keys()):
				if key[0] != ch:
					continue
				for b in mbtab[key]:
					if b["dir"] != "RX":
						continue
					if (m["id"] & b["mask"]) == (key[1] & b["mask"]):
						mbstr = "mb%u(基址 %s/掩码 0x%08X)" % (
							b["mb"], fmt_hex(key[1], b["ext_hw"]), b["mask"])
						break
				if mbstr != "\u2014":
					break
			if rx_entry and mbstr != "\u2014":
				pdu = rx_entry["pduId"].replace("CANIF_RX_", "")
				route = rx_target(rx_entry["rxInd"])
			elif rx_entry:
				pdu, route = rx_entry["pduId"].replace("CANIF_RX_", ""), "**硬件未放行**"
			else:
				pdu, route = "**未覆盖**", "**未覆盖**"

			if rx_entry is None:
				gaps.append({"kind": "rx-not-in-canif", "id": fmt_hex(m["id"], m["ext_gen"]),
				             "name": m["name"], "detail": "CanIf 软件过滤表没有能匹配它的条目"})
			elif mbstr == "\u2014":
				gaps.append({"kind": "rx-hw-blocked", "id": fmt_hex(m["id"], m["ext_gen"]),
				             "name": m["name"], "detail": "软件配了，但硬件邮箱掩码不放行"})
		else:
			for t in txtab:
				if t["ch"] == ch and t["id"] == m["id"]:
					mbstr = "mb%u" % t["mb"]
					break
			pdu, route = "TX shadow", "Com\u2192CanIf"
			if mbstr == "\u2014":
				gaps.append({"kind": "tx-no-hoh", "id": fmt_hex(m["id"], m["ext_gen"]),
				             "name": m["name"], "detail": "DBC 说本节点发，但 Hoh 表里没有"})

		rows.append({
			"frame": "扩展" if m["ext_gen"] else "标准",
			"id": fmt_hex(m["id"], m["ext_gen"]),
			"name": m["name"],
			"dir": direction,
			"proto": proto,
			"cycle": str(m["cycle"]) if m["cycle"] else "\u2014",
			"nsig": m["nSigs"],
			"mb": mbstr,
			"pdu": pdu,
			"route": route,
		})

	extra = [e for e in rxlist
	         if e["ch"] == ch and not any(mm["id"] == e["canid"] for mm in dbc_msgs)]
	return {"skip": False, "rows": rows, "gaps": gaps, "extra": extra}


def report_channel(ch, name, dbc_msgs, mbtab, rxlist, txtab):
	print("\n### %s（CAN%u）\n" % (name, ch))
	print("| 帧类型 | ID | DBC 报文 | 方向 | 协议 | 周期ms | 信号数 | 硬件邮箱 | CanIf PDU | 路由 |")
	print("|---|---|---|---|---|---|---|---|---|---|")

	res = analyze_channel(ch, dbc_msgs, mbtab, rxlist, txtab)
	if res["skip"]:
		print("| \u2014 | \u2014 | \u2014 | \u2014 | \u2014 | \u2014 | \u2014 | \u2014 | \u2014 | （DBC 缺失，SKIP） |")
		return

	for r in res["rows"]:
		print("| %s | %s | %s | %s | %s | %s | %u | %s | %s | %s |"
		      % (r["frame"], r["id"], r["name"], r["dir"], r["proto"],
		         r["cycle"], r["nsig"], r["mb"], r["pdu"], r["route"]))

	if res["extra"]:
		print("\nCanIf 表中存在但 DBC 未列的条目（测试/诊断入口）：")
		for e in res["extra"]:
			print("- %s 0x%08X mask=0x%08X \u2192 %s" % (e["pduId"], e["canid"], e["mask"],
			                                                rx_target(e["rxInd"])))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dbc1", default=os.path.join(CFG, "dbc", "can1.dbc"))
    ap.add_argument("--dbc0", default=os.path.join(CFG, "dbc", "can0.dbc"))
    a = ap.parse_args()

    mbtab = parse_mb_tables(os.path.join(CFG, "Can_Cfg.c"))
    rxlist = parse_canif_rx(os.path.join(CFG, "CanIf_Cfg.c"))
    txtab = parse_hoh_tx(os.path.join(CFG, "Can_Cfg.c"))

    print("# 真实矩阵清单（运行时生成，客户 DBC 不入库）\n")
    print("- 硬件邮箱表：%d 条；CanIf RX 过滤条目：%d 条；TX Hoh：%d 条"
          % (len(mbtab), len(rxlist), len(txtab)))
    print("- 帧类型的扩展标志来自生成器启发式（id>0x7FF），人工核对以本表为准")

    for ch, name, path in ((1, "CAN1 真实矩阵", a.dbc1), (0, "CAN0 控制面", a.dbc0)):
        msgs = load_dbc(path)
        if msgs is None:
            print("\n### %s：DBC 缺失（%s）→ SKIP" % (name, path))
            continue
        report_channel(ch, name, msgs, mbtab, rxlist, txtab)

    print("\n（生成时间戳刻意不加：本报告内容由输入决定，重跑应当逐字节相同）")


if __name__ == "__main__":
    main()
