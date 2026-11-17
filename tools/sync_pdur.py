# -*- coding: utf-8 -*-
"""把 CAN1 通信矩阵的路由**注入**手写的 PduR_Cfg.c / PduR_Cfg.h。

## 为什么是"注入"而不是"整体生成"

`PduR_Cfg.c` 里有两类路径，变动频率差一个数量级：

  | 路径 | 来源 | 变动 |
  |------|------|------|
  | 诊断 4 条（CanTp↔Dcm、含 N-PDU 与确认） | 手写，M3 的 39 项回归依赖 | 几乎不变 |
  | NM 2 条（CanIf↔CanNm） | 手写，M9 依赖 | 几乎不变 |
  | 测试 3 条（Com↔CanIf，0x200/0x201） | JSON（CANTEST 网络） | 几乎不变 |
  | CAN1 40 条（34 RX / 6 TX） | 通信矩阵 | 每次矩阵升版 |

整体生成会把诊断路径也拖进生成器，而 asar 生成器的命名（`PDUR_P2P_RX`）
与本工程已有语义名（`PDUR_CANTP_TO_DCM_RX`）不同，Dcm/CanIf 两侧都要跟着改，
等于给已完成的验证付二次成本。所以只生成 CAN1 的部分。

## 生成什么

对每条**接收**报文（`BO_` 的发送节点不是 BCM）：

    pdu:  CanIf --(PDUR_CAN1_<MSG>_RX)--> Com(COM_CAN1_<MSG>_RX)

对每条**发送**报文：

    pdu:  Com(COM_CAN1_<MSG>_TX) --(PDUR_CAN1_<MSG>_TX)--> CanIf(CANIF_TX_CAN1_<SHORT>)

`SrcPduRef->PduHandleId` 与 `DestPduRef->PduHandleId` **属于两套编号**，
这是本表最容易配错的地方，规则见 `PduR_Cfg.h` 的说明：
- Src 侧（发送路径）= Com 的 IPdu 号，`Com_TxConfirmation()` 拿它当下标；
- Dst 侧（接收路径）= Com 的 IPdu 号，`Com_RxIndication()` 拿它当下标；
- Dest 侧（发送路径）= CanIf 的 PDU 号，`CanIf_Transmit()` 拿它当下标。

## 用法

    python tools/sync_pdur.py            # 生成并注入
    python tools/sync_pdur.py --dry-run  # 只打印，不写文件

@author binbina
"""

import io
import json
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
CFG_DIR = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
HDR = os.path.join(CFG_DIR, "PduR_Cfg.h")
SRC = os.path.join(CFG_DIR, "PduR_Cfg.c")
DBC = os.path.join(CFG_DIR, "dbc", "can1.dbc")

BEGIN_MARK = "/* @generated BEGIN: CAN1 real matrix */"
END_MARK = "/* @generated END: CAN1 real matrix */"

# 项目参数从 Can.json 读（02.5）：编号起点、TX 宏映射。
sys.path.insert(0, os.path.join(ROOT, "tools"))
with io.open(os.path.join(CFG_DIR, "Can", "Can.json"), encoding="utf-8") as _f:
    _CAN = json.load(_f)

# 手写路径已占用 0~8（见 PduR_Cfg.h），生成段起点在 Can.json 里
ID_BASE = _CAN["pdurIdBase"]

# 本节点名来自网络配置，不写死 BCM
with io.open(os.path.join(CFG_DIR, "CanIf", "CanIf.json"), encoding="utf-8") as _f:
    _CANIF = json.load(_f)
ME = _CANIF["networks"][0]["me"]

# CAN1 发送报文 → CanIf 的 TX PDU 宏。
#
# 不能按"报文名去 BCM 前缀"自动推：`BCM_DoorCtrl` 在 CanIf_Cfg.h 里叫
# `CANIF_TX_CAN1_DOOR`（不是 DOOR_CTRL），自动推会拼出一个不存在的宏。
#
# 02.6 起 `canIfMacro` 的唯一来源是 **Can.json 的邮箱表**（`CanIf_TxPdus[]`
# 也由它生成）。`txPdus` 里只留 `short`，这里按 `TX_<short>` 去邮箱表查 ——
# 两处各写一份的话，改了邮箱表忘了改 txPdus 就会生成指向错误 PDU 的路由，
# 而 PduR 只按编号传递、不会报错。
_CANIF_TX_OF = {}
for _ch in _CAN.get("channels", []):
	for _e in _ch["mailboxes"]:
		if _e["dir"] == "TX" and "canIfMacro" in _e:
			_CANIF_TX_OF[_e["name"]] = _e["canIfMacro"]

CANIF_TX_MAP = {}
for _e in _CAN["txPdus"]:
	_key = "TX_" + _e["short"]
	if _key not in _CANIF_TX_OF:
		raise SystemExit("Can.json: txPdus 的 %s 找不到对应 TX 邮箱 %s（short 改名了？）"
		                 % (_e["dbc"], _key))
	CANIF_TX_MAP[_e["dbc"]] = _CANIF_TX_OF[_key]

# 本工程的"诊断/测试"报文不在 dbc 里，手工补两条 Com↔CanIf 路径。
# 它们的 Com PDU 宏来自 Com.json 的 CANTEST 网络（生成器保证同名）。
MANUAL_TX = [
	# (path 宏名, Com PDU 宏, CanIf TX PDU 宏, 注释)
	("PDUR_CANTEST_TX_TEST", "COM_CANTEST_TX_TEST", "CANIF_TX_COM_TEST",
	 "0x200 信号测试帧（M10）"),
]
MANUAL_RX = [
	("PDUR_CANTEST_RX_TEST", "COM_CANTEST_RX_TEST",
	 "0x201 信号测试帧（M10）"),
]


def to_macro(s):
	"""`BCM_DoorCtrl` → `BCM_DOOR_CTRL`（与 generator/Com.py 的 toMacro 一致）"""
	s = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", s)
	s = re.sub(r"[^0-9A-Za-z_]", "_", s)
	return s.upper()


def build():
	# 走共享解析（02.4）：同一份 DBC 与 Com/CanIf 用同一套解析与节点筛选，
	# 不再维护这个脚本自己的正则版 parse_dbc。
	from generator.dbc.database import DbcDatabase, classify
	msgs = classify(DbcDatabase().get_messages(DBC), ME)
	tx = [m for m in msgs if m["dir"] == "TX"]
	rx = [m for m in msgs if m["dir"] == "RX"]
	if not tx or not rx:
		raise SystemExit("dbc 解析异常：TX=%d RX=%d" % (len(tx), len(rx)))

	paths = []          # {"id":, "name":, "dir":, "com":, "canif":, "note":}
	pid = ID_BASE

	for m in tx:
		if m["name"] not in CANIF_TX_MAP:
			raise SystemExit(
				"发送报文 %s 没有对应的 CanIf TX PDU，请补 CANIF_TX_MAP"
				% m["name"])
		mac = to_macro(m["name"])
		paths.append({
			"id": pid, "dir": "TX",
			"name": "PDUR_CAN1_%s_TX" % mac,
			"com": "COM_CAN1_%s_TX" % mac,
			"canif": CANIF_TX_MAP[m["name"]],
			"note": "0x%08X %s（发送）" % (m["can_id"], m["name"]),
		})
		pid += 1

	for m in rx:
		mac = to_macro(m["name"])
		paths.append({
			"id": pid, "dir": "RX",
			"name": "PDUR_CAN1_%s_RX" % mac,
			"com": "COM_CAN1_%s_RX" % mac,
			"canif": None,
			"note": "0x%08X %s（接收，来自 %s）" % (m["can_id"], m["name"], m["node"]),
		})
		pid += 1

	for name, com, canif, note in MANUAL_TX:
		paths.append({"id": pid, "dir": "TX", "name": name, "com": com,
		              "canif": canif, "note": note})
		pid += 1
	for name, com, note in MANUAL_RX:
		paths.append({"id": pid, "dir": "RX", "name": name, "com": com,
		              "canif": None, "note": note})
		pid += 1

	return paths


def render_header(paths):
	out = [BEGIN_MARK]
	out.append("/*\n * CAN1 报文路由（由 tools/sync_pdur.py 从 dbc/can1.dbc 生成，勿手改）\n"
	           " *\n"
	           " * 每条报文一条路径：RX 是 CanIf→Com，TX 是 Com→CanIf。\n"
	           " * 路径号从 %du 起 —— 0~%du 归诊断/NM/测试（见文件前半部分）。\n"
	           " */" % (ID_BASE, ID_BASE - 1))
	for p in paths:
		out.append("/** @brief %s */" % p["note"])
		out.append("#define %-34s (%du)" % (p["name"], p["id"]))
	out.append("")
	out.append("/** @brief 生成段路径数（供 PDUR_NUM_ROUTING_PATHS 相加） */")
	out.append("#define PDUR_CAN1_PATHS         (%du)" % len(paths))
	out.append(END_MARK)
	return "\n".join(out)


def render_src(paths):
	out = [BEGIN_MARK]
	for p in paths:
		if p["dir"] == "TX":
			out.append("\t/* %d：%s */" % (p["id"], p["note"]))
			out.append("\t{ PDUR_MODULE_COM,   (PduIdType)%s, &PduR_ComApi  },"
			           % p["com"])
		else:
			out.append("\t/* %d：%s */" % (p["id"], p["note"]))
			out.append("\t{ PDUR_MODULE_CANIF, 0u, &PduR_CanIfApi },")
	out.append(END_MARK)
	return "\n".join(out)


def render_dst(paths):
	out = [BEGIN_MARK]
	for p in paths:
		if p["dir"] == "TX":
			out.append("\t/* %d：→ CanIf %s */" % (p["id"], p["canif"]))
			out.append("\t{ { PDUR_MODULE_CANIF, (PduIdType)%s, &PduR_CanIfApi } },"
			           % p["canif"])
		else:
			out.append("\t/* %d：→ Com %s */" % (p["id"], p["com"]))
			out.append("\t{ { PDUR_MODULE_COM, (PduIdType)%s, &PduR_ComApi } },"
			           % p["com"])
	out.append(END_MARK)
	return "\n".join(out)


def render_paths(paths):
	out = [BEGIN_MARK]
	for p in paths:
		out.append("\t/* %s */" % p["note"])
		out.append("\t{")
		out.append("\t\t&PduR_SrcPdu[%s]," % p["name"])
		out.append("\t\tPduR_DstPdu[%s]," % p["name"])
		out.append("\t\tNULL,                             /* DestTxBufferRef */")
		out.append("\t\tNULL,                             /* GwBuffer */")
		out.append("\t\t0u,                               /* GwBufferSize */")
		out.append("\t\t1u,                               /* numOfDestPdus */")
		out.append("\t},")
	out.append(END_MARK)
	return "\n".join(out)


def inject(text, body, nth):
	"""把第 nth 组 BEGIN~END 之间的内容替换成 body（nth 从 0 起）

	@note 必须按下标定位，不能"总找第一个"：body 自己也带 BEGIN/END 标记，
	      第一次替换完之后"第一个标记"还是刚写进去的那一组，
	      第二次就会把 DstPdu 的内容写进 SrcPdu 区（编出来的错误是
	      "PduR_DstPdu undeclared"——离真正原因隔了三层）。
	"""
	i = -1
	for _ in range(nth + 1):
		i = text.find(BEGIN_MARK, i + 1)
		if i < 0:
			raise SystemExit("文件里第 %d 组 @generated 标记找不到" % nth)
	j = text.find(END_MARK, i)
	if j < 0:
		raise SystemExit("第 %d 组 @generated 缺 END 标记" % nth)
	eol = j + len(END_MARK)
	return text[:i] + body + text[eol:]


def main():
	dry = "--dry-run" in sys.argv
	paths = build()
	bh = render_header(paths)
	bs = render_src(paths)
	bd = render_dst(paths)
	bp = render_paths(paths)

	if dry:
		sys.stdout.write(bh + "\n\n")
		sys.stdout.write(bs + "\n\n")
		sys.stdout.write(bd + "\n\n")
		sys.stdout.write(bp + "\n\n")
		return

	hs = io.open(HDR, encoding="utf-8").read()
	cs = io.open(SRC, encoding="utf-8").read()
	hs = inject(hs, bh, 0)
	# .c 里三个数组各有一组标记，按数组在文件里的顺序依次替换：
	# SrcPdu → DstPdu → RoutingPaths
	cs = inject(cs, bs, 0)
	cs = inject(cs, bd, 1)
	cs = inject(cs, bp, 2)

	io.open(HDR, "w", encoding="utf-8", newline="\n").write(hs)
	io.open(SRC, "w", encoding="utf-8", newline="\n").write(cs)
	print("注入完成：%d 条路径（%d RX / %d TX）"
	      % (len(paths),
	         sum(1 for p in paths if p["dir"] == "RX"),
	         sum(1 for p in paths if p["dir"] == "TX")))


if __name__ == "__main__":
	main()
