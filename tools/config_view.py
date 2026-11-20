#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
@file    config_view.py
@brief   配置可视化面板：把 JSON + 生成物渲染成一张离线 HTML（只读）

@details 数据来源**都是真源**，面板不引入第二份配置：

          | 面板区块 | 数据来源 |
          |---|---|
          | 总览 | 各文件计数汇总 |
          | RTE 端口 | `Board.json` 的 `rte.ports` + `GEN/Rte_Ports.h`（索引/类型） |
          | 调度表 | `GEN/Rte_Schedule.h` |
          | CAN 邮箱 | `Can/Can.json` 的 `channels[].mailboxes` |
          | 信号矩阵 | `Com_Cfg.h`（网络/报文/信号位布局，生成物即真源） |
          | IO 通道 | `Board.json` 的 `io` 段 |
          | 引脚 | `Board.json` 的 `pins` 段 |

          @note 为什么只读：配置的真源是 JSON/DBC，任何"表单写回"都要先回答
          "谁是唯一写者、生成物与真源冲突怎么办"。第一版先把"看清楚"解决，
          编辑仍走 `tools/config.py generate`。

@note    启动：
          ```
          python tools/config_view.py           # 生成 build/config_view.html
          python tools/config_view.py --open    # 生成并用默认浏览器打开
          ```

@author  binbina
@version V1.0.0
"""

import argparse
import html
import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CFG = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
GEN = os.path.join(CFG, "Board", "GEN")

# kind -> (方向, 中文说明)
KIND_CN = {
	"COM_TX": ("out", "Com 发送（BcmSig 影子 → Com 信号）"),
	"COM_RX": ("in", "Com 接收（Com 信号 → BcmSig 语义）"),
	"DIN": ("in", "数字输入（IoHwAb 消抖）"),
	"AIN_RAW": ("in", "模拟输入-原始值（IoHwAb）"),
	"AIN_PHYS": ("in", "模拟输入-物理量×1000（IoHwAb）"),
	"DOUT": ("out", "数字输出（IoHwAb → 驱动）"),
}


def read(p):
	if not os.path.isfile(p):
		return ""
	return io.open(p, encoding="utf-8", errors="replace").read()


def load_json(p):
	if not os.path.isfile(p):
		return {}
	with io.open(p, encoding="utf-8") as f:
		return json.load(f)


def esc(s):
	return html.escape(str(s), quote=True)


# ============================ [ 解析 ] ============================

def parse_rte_ports():
	"""Board.json 的端口名 + GEN 头里的索引/类型。"""
	board = load_json(os.path.join(CFG, "Board", "Board.json"))
	ports = board.get("rte", {}).get("ports", [])
	hdr = read(os.path.join(GEN, "Rte_Ports.h"))

	idx = {}
	for m in re.finditer(r"RTE_PORT_([A-Z0-9_]+)\s*=\s*(\d+)\s*,", hdr):
		idx[m.group(1)] = int(m.group(2))

	cfg = re.findall(r"\{\s*RTE_DIR_(IN|OUT),\s*(RTE_KIND_\w+),\s*\(uint16\)(\w+)\s*\}", hdr)
	out = []
	for i, p in enumerate(ports):
		k = cfg[i][1].replace("RTE_KIND_", "") if i < len(cfg) else "?"
		ref = cfg[i][2] if i < len(cfg) else "?"
		d = cfg[i][0] if i < len(cfg) else "?"
		out.append({
			"idx": idx.get(p.get("name", ""), i),
			"name": p.get("name", ""),
			"dir": d,
			"kind": k,
			"ref": ref,
			"note": KIND_CN.get(k, ("", "?"))[1],
		})
	return board, out


def parse_schedule():
	"""GEN/Rte_Schedule.h：顺序、函数、周期。"""
	hdr = read(os.path.join(GEN, "Rte_Schedule.h"))
	rows = []
	for m in re.finditer(r"\{\s*(\d+)u,\s*(\w+)\s*\}[^/]*/\*\s*(\d+)\s*ms\s*\*/", hdr):
		ticks, fn, ms = int(m.group(1)), m.group(2), int(m.group(3))
		rows.append({"fn": fn, "ms": ms, "ticks": ticks})
	return rows


def parse_can_mailboxes():
	can = load_json(os.path.join(CFG, "Can", "Can.json"))
	out = []
	for ch in can.get("channels", []):
		for mb in ch.get("mailboxes", []):
			out.append({
				"ch": ch.get("index", "?"),
				"mb": mb.get("mb", "?"),
				"name": mb.get("name", ""),
				"id": mb.get("id", ""),
				"dir": mb.get("dir", ""),
				"ext": "扩展" if mb.get("ext") else "标准",
				"mask": mb.get("mask", ""),
				"hth": mb.get("hth", ""),
			})
	return out


def parse_com_signals():
	""""Com_Cfg.h：按报文分组，取信号位布局与 PDU 号。"""
	hdr = read(os.path.join(CFG, "Com_Cfg.h"))
	pdu_ids = {}
	for m in re.finditer(r"#define\s+(COM_[A-Z0-9_]+)\s+(\d+)\s*$", hdr, re.M):
		pdu_ids[m.group(1)] = int(m.group(2))

	msgs = []
	cur = None
	sec = re.compile(r"signals for network (\w+) message (\w+): id=0x([0-9a-fA-F]+) dlc=(\d+), dir=(\w+)")
	sig = re.compile(r"#define\s+COM_SID_(\w+)\s+(\d+)\s*/\*\s*(\w+)\s+(\d+)@(\d+)\s*\*/")
	for line in hdr.splitlines():
		m = sec.search(line)
		if m:
			cur = {
				"net": m.group(1), "msg": m.group(2),
				"id": "0x%08X" % (int(m.group(3), 16) & 0x1FFFFFFF),
				"dlc": int(m.group(4)), "dir": m.group(5),
				"pdu": pdu_ids.get("COM_%s_%s" % (m.group(1), m.group(2)), ""),
				"sigs": [],
			}
			msgs.append(cur)
			continue
		if cur is not None:
			s = sig.search(line)
			if s:
				cur["sigs"].append({
					"name": s.group(1), "sid": int(s.group(2)),
					"endian": "小端" if s.group(3) == "little" else "大端",
					"size": int(s.group(4)), "start": int(s.group(5)),
				})
	return msgs


# ============================ [ HTML ] ============================

CSS = """
:root{--bg:#0f1115;--panel:#161b22;--line:#2a2f3a;--fg:#e6edf3;--dim:#8b949e;--acc:#58a6ff;--ok:#3fb950;--warn:#d29922}
*{box-sizing:border-box}
body{margin:0;background:var(--bg);color:var(--fg);font:14px/1.6 "Segoe UI",system-ui,sans-serif}
header{position:sticky;top:0;z-index:5;background:rgba(15,17,21,.95);border-bottom:1px solid var(--line);padding:14px 22px}
h1{margin:0 0 6px;font-size:18px;font-weight:600}
.sub{color:var(--dim);font-size:12px}
nav a{color:var(--acc);text-decoration:none;margin-right:14px;font-size:13px}
nav a:hover{text-decoration:underline}
main{padding:18px 22px 60px;max-width:1500px}
section{margin:26px 0 34px}
h2{font-size:15px;font-weight:600;border-left:3px solid var(--acc);padding-left:8px;margin:0 0 10px}
table{width:100%;border-collapse:collapse;background:var(--panel);border:1px solid var(--line);border-radius:6px;overflow:hidden}
th,td{padding:7px 10px;border-bottom:1px solid var(--line);text-align:left;vertical-align:top}
th{position:sticky;top:0;background:#1c2330;color:var(--dim);font-weight:600;font-size:12px;text-transform:uppercase;letter-spacing:.04em}
tr:last-child td{border-bottom:none}
tr:hover td{background:#1b2230}
code,.mono{font-family:Consolas,"Cascadia Mono",monospace;font-size:12.5px}
.pill{display:inline-block;padding:1px 7px;border-radius:999px;font-size:11px;border:1px solid var(--line)}
.p-in{color:#79c0ff;border-color:#1f4a6e}.p-out{color:#7ee787;border-color:#2b5a34}
.dim{color:var(--dim)}
#q{width:320px;padding:6px 10px;background:#0d1117;border:1px solid var(--line);border-radius:6px;color:var(--fg);outline:none}
#q:focus{border-color:var(--acc)}
.stats{display:flex;gap:14px;flex-wrap:wrap}
.card{background:var(--panel);border:1px solid var(--line);border-radius:8px;padding:12px 16px;min-width:140px}
.card b{display:block;font-size:22px;color:var(--acc)}
.note{color:var(--dim);font-size:12px}
"""

JS = """
const q=document.getElementById('q');
q.addEventListener('input',()=>{
  const v=q.value.trim().toLowerCase();
  document.querySelectorAll('table tbody tr').forEach(tr=>{
    tr.style.display=(v===''||tr.innerText.toLowerCase().includes(v))?'':'none';
  });
});
"""


def table(headers, rows, cls=""):
	out = ['<table class="%s"><thead><tr>' % cls]
	out += ["<th>%s</th>" % esc(h) for h in headers]
	out.append("</tr></thead><tbody>")
	for r in rows:
		out.append("<tr>" + "".join("<td>%s</td>" % c for c in r) + "</tr>")
	out.append("</tbody></table>")
	return "\n".join(out)


def build_html():
	board, ports = parse_rte_ports()
	sched = parse_schedule()
	mbs = parse_can_mailboxes()
	msgs = parse_com_signals()

	io = board.get("io", {})
	n_sig = sum(len(m["sigs"]) for m in msgs)

	parts = []
	parts.append("<!DOCTYPE html><html lang='zh-CN'><head><meta charset='utf-8'>")
	parts.append("<title>like_as 配置视图</title><style>%s</style></head><body>" % CSS)
	parts.append("<header><h1>like_as 配置视图 <span class='dim' style='font-size:12px'>（只读）</span></h1>")
	parts.append("<div class='sub'>真源：Board.json / Can.json / Com_Cfg.h / Rte_Ports.h / Rte_Schedule.h ｜ "
	             "编辑后执行 <code>python tools/config.py generate</code></div>")
	parts.append("<div style='margin-top:10px'><input id='q' placeholder='过滤任意表格…（端口/信号/ID/函数）'>")
	parts.append("<nav style='margin-top:8px'><a href='#ov'>总览</a><a href='#rte'>RTE 端口</a>"
	             "<a href='#sched'>调度表</a><a href='#can'>CAN 邮箱</a><a href='#sig'>信号矩阵</a>"
	             "<a href='#io'>IO 通道</a><a href='#pin'>引脚</a></nav></div></header><main>")

	# 总览
	parts.append("<section id='ov'><h2>总览</h2><div class='stats'>")
	for label, val in (("RTE 端口", len(ports)), ("runnable", len(sched)),
	                   ("CAN 邮箱", len(mbs)), ("报文", len(msgs)), ("信号", n_sig),
	                   ("IO 通道", sum(len(io.get(k, [])) for k in ("din", "ain", "dout", "pwm")))):
		parts.append("<div class='card'><b>%s</b><span class='note'>%s</span></div>" % (val, label))
	parts.append("</div>")
	cans = board.get("can", [])
	parts.append("<p class='note' style='margin-top:10px'>CAN 通道：" +
	             "、".join("CAN%s @ %s kbps" % (c.get("instance"), int(c.get("bitrate", 0)) // 1000) for c in cans) +
	             " ｜ 板卡：%s / %s</p>" % (esc(board.get("boardName", "?")), esc(board.get("mcu", "?"))))
	parts.append("</section>")

	# RTE 端口
	rows = []
	for p in ports:
		d = p["dir"].lower()
		rows.append([
			"<code>%d</code>" % p["idx"],
			"<code>%s</code>" % esc(p["name"]),
			"<span class='pill p-%s'>%s</span>" % (d, "输入" if d == "in" else "输出"),
			"<code>%s</code>" % esc(p["kind"]),
			"<code>%s</code>" % esc(p["ref"]),
			"<span class='dim'>%s</span>" % esc(p["note"]),
		])
	parts.append("<section id='rte'><h2>RTE 端口（Board.json → Rte_Ports.h）</h2>")
	parts.append(table(["#", "端口名", "方向", "类型", "绑定 ref", "后端含义"], rows))
	parts.append("<p class='note'>业务只允许出现左三列；<code>ref</code> 是绑定层/IO 层的事，换项目只改这里。</p></section>")

	# 调度表
	rows = [["<code>%d</code>" % i, "<code>%s</code>" % esc(s["fn"]), "%d ms" % s["ms"],
	         "<span class='dim'>reload=%d 拍</span>" % s["ticks"]]
	        for i, s in enumerate(sched)]
	parts.append("<section id='sched'><h2>Runnable 调度表（Board.json → Rte_Schedule.h）</h2>")
	parts.append(table(["执行序", "runnable", "周期", "分频"], rows))
	parts.append("<p class='note'>表序 = 同一拍内的执行顺序；跨周期依赖不允许。</p></section>")

	# CAN 邮箱
	rows = []
	for m in mbs:
		rows.append([
			"CAN%s" % m["ch"], "<code>mb%s</code>" % m["mb"], esc(m["name"]),
			"<code>%s</code>" % esc(m["id"]), m["dir"], m["ext"],
			"<code>%s</code>" % esc(m["mask"]), "<code>%s</code>" % esc(m["hth"]),
		])
	parts.append("<section id='can'><h2>CAN 邮箱（Can.json）</h2>")
	parts.append(table(["通道", "邮箱", "名称", "ID", "方向", "帧型", "掩码", "HTH"], rows))
	parts.append("</section>")

	# 信号矩阵
	parts.append("<section id='sig'><h2>信号矩阵（Com_Cfg.h 生成物）</h2>")
	for m in msgs:
		parts.append("<h3 style='font-size:13px;margin:16px 0 6px'>"
		             "<code>%s</code> <span class='dim'>%s · %s · DLC %d · %s · PDU %s</span></h3>"
		             % (esc(m["msg"]), esc(m["net"]), esc(m["id"]), m["dlc"], esc(m["dir"]), esc(m["pdu"] or "-")))
		rows = []
		for s in m["sigs"]:
			rows.append(["<code>%s</code>" % esc(s["name"]), "<code>%d</code>" % s["sid"],
			             s["start"], s["size"], s["endian"],
			             "<span class='dim'>bit %d..%d</span>" % (s["start"], s["start"] + s["size"] - 1)])
		parts.append(table(["信号", "COM_SID", "起始位", "长度", "字节序", "位区间"], rows))
	parts.append("</section>")

	# IO 通道
	parts.append("<section id='io'><h2>IO 通道（Board.json io 段）</h2>")
	for kind, title in (("din", "数字输入"), ("ain", "模拟输入"), ("dout", "数字输出"), ("pwm", "PWM")):
		items = io.get(kind, [])
		if not items:
			continue
		keys = []
		for it in items:
			for k in it.keys():
				if k not in keys:
					keys.append(k)
		rows = []
		for it in items:
			rows.append(["<code>%s</code>" % esc(it.get(k, "")) if k == "name" else esc(it.get(k, "")) for k in keys])
		parts.append("<h3 style='font-size:13px;margin:16px 0 6px'>%s <span class='dim'>%d 路</span></h3>" % (title, len(items)))
		parts.append(table([esc(k) for k in keys], rows))
	parts.append("</section>")

	# 引脚
	pins = board.get("pins", [])
	rows = []
	for p in pins:
		rows.append(["<code>%s</code>" % esc(p.get("name", "")),
		             esc(p.get("mode", "")), esc(p.get("dir", "")),
		             "%s%s" % (esc(p.get("port", "")), esc(p.get("pin", ""))),
		             esc(p.get("mux", "")), esc(p.get("level", ""))])
	parts.append("<section id='pin'><h2>引脚（Board.json pins 段）</h2>")
	parts.append(table(["名称", "模式", "方向", "端口/脚", "MUX", "初始电平"], rows))
	parts.append("<p class='note'>引脚总数 %d；PCB 网络名与这里对不上时，先改 Board.json 再生成。</p></section>" % len(pins))

	parts.append("</main><script>%s</script></body></html>" % JS)
	return "\n".join(parts)


def main():
	ap = argparse.ArgumentParser(description="生成只读的配置可视化面板（单文件 HTML）")
	ap.add_argument("--out", default=os.path.join(ROOT, "build", "config_view.html"))
	ap.add_argument("--open", action="store_true", help="生成后用默认浏览器打开")
	args = ap.parse_args()

	out = os.path.abspath(args.out)
	os.makedirs(os.path.dirname(out), exist_ok=True)
	html_text = build_html()
	with io.open(out, "w", encoding="utf-8", newline="\n") as f:
		f.write(html_text)
	print("生成：%s（%.1f KB）" % (out, len(html_text.encode("utf-8")) / 1024.0))

	if args.open:
		if sys.platform.startswith("win"):
			os.startfile(out)  # noqa: S606 —— 本地只读面板，打开默认浏览器
		else:
			import webbrowser
			webbrowser.open("file://" + out)
	return 0


if __name__ == "__main__":
	sys.exit(main())
