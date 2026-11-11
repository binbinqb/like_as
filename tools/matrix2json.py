# -*- coding: utf-8 -*-
"""福田通信矩阵 xlsx → 结构化 JSON

@details 矩阵的排布方式：**报文头只出现在第一行**，后续信号行的 A~H 列为空
         （或只有备注），需要"向下填充"。这是手工维护的矩阵最常见的形态，
         不填充就会把 90% 的信号丢掉。

@note 列号按表头文字匹配，不硬编码 —— 矩阵会升版（V0.4 → V0.5），
      列一旦插入/删除，硬编码就会静默错位，而这类错误不看表头根本发现不了。

用法：
    python tools/matrix2json.py <xlsx> <out.json>
"""

import json
import os
import re
import sys

import openpyxl

# 表头关键词 → 内部字段名。用"包含"匹配，容忍表头里的换行与英文后缀。
COLS = [
    ("msgName",     "Msg Name"),
    ("msgType",     "Msg Type"),
    ("msgId",       "Msg ID"),
    ("pgn",         "PGN"),
    ("priority",    "Msg priority"),
    ("sendType",    "Msg Send Type"),
    ("cycleMs",     "Msg Cycle Time (ms)"),
    ("dlc",         "Msg Length"),
    ("sigName",     "Signal Name"),
    ("sigDesc",     "Signal Description"),
    ("byteOrder",   "Byte Order"),
    ("startByte",   "Start Byte"),
    ("startBit",    "Start Bit"),
    ("bitLen",      "Bit Length"),
    ("spn",         "SPN"),
    ("dataType",    "Date Type"),      # 原表就是 "Date Type"（笔误）
    ("resolution",  "Resolution"),
    ("offset",      "Offset"),
    ("minPhys",     "Signal Min. Value (phys)"),
    ("maxPhys",     "Signal Max. Value (phys)"),
    ("minHex",      "Signal Min. Value (Hex)"),
    ("maxHex",      "Signal Max. Value (Hex)"),
    ("initHex",     "Initial Value"),
    ("invalidHex",  "Invalid Value"),
    ("errorHex",    "Error Value"),
    ("inactiveHex", "Inactive Value"),
    ("unit",        "Unit"),
    ("valueDesc",   "Signal Value Description"),
    ("cycleFastMs", "Msg Cycle Time Fast"),
    ("nrOfRepeat",  "Msg Nr. Of Reption"),
    ("delayMs",     "Msg Delay Time"),
    ("remark",      "Remark"),
]

# 表头文字里带 "(" 的会产生正则元字符，这里只做去空白处理
def norm(s):
    return re.sub(r"\s+", " ", str(s or "")).strip()


def build_colmap(ws, hdr_row, maxc):
    """按表头文字定位列号。返回 {字段名: 列号} 与"每 ECU 一列"的映射。"""
    heads = {}
    env = {}
    for c in range(1, maxc + 1):
        h = norm(ws.cell(row=hdr_row, column=c).value)
        if not h:
            continue
        heads[c] = h
        for key, kw in COLS:
            if key in env:
                continue
            if kw.lower() in h.lower():
                env[key] = c
                break
    return heads, env


def cell(ws, r, c):
    if c is None:
        return None
    v = ws.cell(row=r, column=c).value
    if v is None:
        return None
    if isinstance(v, str):
        v = v.strip()
        return v if v else None
    return v


def num(v):
    if v is None:
        return None
    if isinstance(v, (int, float)):
        return v
    s = str(v).strip()
    try:
        if s.lower().startswith("0x"):
            return int(s, 16)
        return int(float(s))
    except ValueError:
        try:
            return float(s)
        except ValueError:
            return None


def parse_sheet(ws, ecu_col_names):
    maxc = 0
    for row in ws.iter_rows(min_row=1, max_row=min(ws.max_row, 40)):
        for c in row:
            if c.value not in (None, ""):
                maxc = max(maxc, c.column)

    heads, env = build_colmap(ws, 1, maxc)

    # 每个 ECU 一列（表头是 ECU 名）——这些列只在报文首行有 T/R 标记
    ecu_cols = {}
    for c, h in heads.items():
        if c in env.values():
            continue
        if h in ecu_col_names:
            ecu_cols[h] = c

    msgs = []
    cur = None
    for r in range(2, ws.max_row + 1):
        mid = cell(ws, r, env.get("msgId"))
        sname = cell(ws, r, env.get("sigName"))

        if mid:
            cur = {
                "id": mid,
                "name": cell(ws, r, env.get("msgName")),
                "type": cell(ws, r, env.get("msgType")),
                "pgn": num(cell(ws, r, env.get("pgn"))),
                "prio": num(cell(ws, r, env.get("priority"))),
                "sendType": cell(ws, r, env.get("sendType")),
                "cycleMs": num(cell(ws, r, env.get("cycleMs"))),
                "dlc": num(cell(ws, r, env.get("dlc"))),
                "cycleFastMs": num(cell(ws, r, env.get("cycleFastMs"))),
                "nrOfRepeat": num(cell(ws, r, env.get("nrOfRepeat"))),
                "delayMs": num(cell(ws, r, env.get("delayMs"))),
                "remark": cell(ws, r, env.get("remark")),
                "ecus": {},
                "sigs": [],
            }
            for nm, c in ecu_cols.items():
                v = cell(ws, r, c)
                if v:
                    cur["ecus"][nm] = str(v)
            msgs.append(cur)
            # 报文首行也可能直接带信号（矩阵里常见）
        elif cur is None:
            continue

        if not sname:
            continue

        sig = {
            "name": sname,
            "desc": cell(ws, r, env.get("sigDesc")),
            "byteOrder": cell(ws, r, env.get("byteOrder")),
            "startByte": num(cell(ws, r, env.get("startByte"))),
            "startBit": num(cell(ws, r, env.get("startBit"))),
            "bitLen": num(cell(ws, r, env.get("bitLen"))),
            "spn": num(cell(ws, r, env.get("spn"))),
            "dataType": cell(ws, r, env.get("dataType")),
            "res": num(cell(ws, r, env.get("resolution"))),
            "offset": num(cell(ws, r, env.get("offset"))),
            "minPhys": num(cell(ws, r, env.get("minPhys"))),
            "maxPhys": num(cell(ws, r, env.get("maxPhys"))),
            "initHex": cell(ws, r, env.get("initHex")),
            "invalidHex": cell(ws, r, env.get("invalidHex")),
            "errorHex": cell(ws, r, env.get("errorHex")),
            "inactiveHex": cell(ws, r, env.get("inactiveHex")),
            "unit": cell(ws, r, env.get("unit")),
            "valueDesc": cell(ws, r, env.get("valueDesc")),
            "remark": cell(ws, r, env.get("remark")),
        }
        cur["sigs"].append(sig)

    return msgs, heads, env, ecu_cols


def main():
    xlsx, out = sys.argv[1], sys.argv[2]
    wb = openpyxl.load_workbook(xlsx, data_only=True)
    result = {}
    for ws in wb.worksheets:
        # 先粗扫一遍表头，收集 ECU 名（表头里除固定字段以外的列名）
        maxc = 0
        for row in ws.iter_rows(min_row=1, max_row=2):
            for c in row:
                if c.value not in (None, ""):
                    maxc = max(maxc, c.column)
        heads, env = build_colmap(ws, 1, maxc)
        known = set(env.values())
        ecu_names = [h for c, h in heads.items() if c not in known]
        msgs, h2, env2, ecu_cols = parse_sheet(ws, ecu_names)
        result[ws.title] = {
            "ecus": ecu_names,
            "msgCount": len(msgs),
            "sigCount": sum(len(m["sigs"]) for m in msgs),
            "msgs": msgs,
        }
        print("%-16s mesgs=%-4d sigs=%-4d ecus=%s"
              % (ws.title, len(msgs), sum(len(m["sigs"]) for m in msgs),
                 ",".join(ecu_names)))
    wb.close()

    with open(out, "w", encoding="utf-8") as fh:
        json.dump(result, fh, ensure_ascii=False, indent=1)
    print("written:", out, os.path.getsize(out), "bytes")


if __name__ == "__main__":
    main()
