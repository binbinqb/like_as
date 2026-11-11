# -*- coding: utf-8 -*-
"""DBC 解析（最小实现，只取本项目需要的字段）

为什么自己写而不用 `cantools`：这里只需要"报文 ID / 名称 / 周期 / 信号布局"
这几项，装一个依赖只为读 42 条报文不划算；而且 cantools 对中文注释的
处理与 Vector 原版 DBC 偶有出入，自己解析能保证与原始文件逐字对得上。

@note 只支持 Motorola/Intel 两种字节序与 +/- 两种符号，够覆盖本项目的 42 条报文。
"""

import io
import re


def parse(path):
    """解析一个 DBC，返回 (nodes, msgs, text)。"""
    txt = io.open(path, encoding="utf-8", errors="replace").read()

    nodes = []
    m = re.search(r"^BU_:(.*)$", txt, re.M)
    if m:
        nodes = m.group(1).split()

    msgs = []
    cur = None
    for ln in txt.splitlines():
        mb = re.match(r"^BO_ (\d+) (\S+):\s*(\d+)\s*(\S+)", ln)
        if mb:
            cur = {
                "dbc_id": int(mb.group(1)),
                "id": int(mb.group(1)) & 0x1FFFFFFF,
                "name": mb.group(2),
                "dlc": int(mb.group(3)),
                "tx": mb.group(4),
                "sigs": [],
                "comment": "",
            }
            msgs.append(cur)
            continue

        sg = re.match(
            r"^\s+SG_ (\S+)\s*:\s*(\d+)\|(\d+)@([01])([+-])\s*"
            r"\(([^)]*)\)\s*\[([^]]*)\]\s*(\"[^\"]*\"|\S+)\s*(\S*)", ln)
        if sg and cur is not None:
            fac, off = [x.strip() for x in sg.group(6).split(",")]
            lo, hi = [x.strip() for x in sg.group(7).split("|")]
            cur["sigs"].append({
                "name": sg.group(1),
                "start": int(sg.group(2)),
                "len": int(sg.group(3)),
                "le": sg.group(4) == "1",
                "signed": sg.group(5) == "-",
                "factor": float(fac),
                "offset": float(off),
                "min": float(lo),
                "max": float(hi),
                "unit": sg.group(8).strip('"'),
                "rx": sg.group(9),
            })
            continue

        cm = re.match(r'^CM_ BO_ (\d+) "(.*)";', ln)
        if cm and cur is not None:
            cur["comment"] = cm.group(2)
            continue
        cm2 = re.match(r'^CM_ SG_ (\d+) (\S+) "(.*)";', ln)
        if cm2 and cur is not None:
            for s in cur["sigs"]:
                if s["name"] == cm2.group(2):
                    s["comment"] = cm2.group(3)

    cyc = dict((int(a), int(b)) for a, b in
               re.findall(r'BA_ "GenMsgCycleTime" BO_ (\d+) (\d+);', txt))
    for mg in msgs:
        mg["cycle"] = cyc.get(mg["dbc_id"], 0)

    # VAL_ 枚举表：{msg_id: {sig_name: {value: label}}}
    vals = {}
    for mid, sname, body in re.findall(r'^VAL_ (\d+) (\S+) (.*);$', txt, re.M):
        d = {}
        for v, lab in re.findall(r'(\d+)\s+"([^"]*)"', body):
            d[int(v)] = lab
        vals.setdefault(int(mid), {})[sname] = d
    for mg in msgs:
        for s in mg["sigs"]:
            s["vals"] = vals.get(mg["dbc_id"], {}).get(s["name"], {})

    return nodes, msgs, txt


if __name__ == "__main__":
    import sys

    for f in sys.argv[1:]:
        nodes, msgs, _ = parse(f)
        print("=" * 80)
        print("%s   nodes=%s   messages=%d   signals=%d"
              % (f, nodes, len(msgs), sum(len(m["sigs"]) for m in msgs)))
        print("-" * 80)
        for m in sorted(msgs, key=lambda x: x["id"]):
            ext = "EXT" if m["dbc_id"] > 0x7FF else "STD"
            print("  0x%08X %-3s %-26s dlc=%d tx=%-9s cyc=%5dms sigs=%2d"
                  % (m["id"], ext, m["name"], m["dlc"], m["tx"],
                     m["cycle"], len(m["sigs"])))
