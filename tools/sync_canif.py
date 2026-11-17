# -*- coding: utf-8 -*-
"""
把生成器产出的 CAN1 配置**注入**手写的 CanIf_Cfg.c / CanIf_Cfg.h。

## 为什么是"注入"而不是"整体替换"

`CanIf_Cfg.c` 里有两类内容：

  | 部分 | 来源 | 变动频率 |
  |------|------|----------|
  | CAN0（M1~M14 的测试/诊断/NM/Com） | 手写，261 项回归依赖它 | 几乎不变 |
  | CAN1（Foton 真实矩阵 34 RX） | 通信矩阵，随矩阵版本更新 | 每次更新 |

整体替换会把 CAN0 的 23 条也拖进 JSON —— 等于给已完成的验证付二次成本，
而且 `rxPduId` 编号一变，M2/M8/M14 三个脚本的期望值全要改。

所以用标记注入：**只有 `@generated` 区块由本脚本改写，其余一字不动。**

## 三件脚本自动做对的事

1. **编号偏移**：CAN0 已占 `CANIF_RX_* = 0~22`，CAN1 的 34 条从 **23** 开始，
   保证 `PduIdType` 全局唯一 —— 上游打印时不会把两路的 PDU 混在一起。
2. **hoh 回填**：生成器给的 `hoh` 恒为 0（它的 `hrh` 是每网络递增、不是每报文）。
   RX 路径上 `hoh` 是死字段（`CanIf_RxDispatch()` 只用 `canid & mask` 二分），
   但填 0 会让人误以为"34 条共用邮箱 0"。这里按 PF 段回填真实邮箱号。
3. **格式**：生成器输出 `0xcf00400`（小写无前导零）、2 空格缩进；
   本工程用 `0x0CF00400u` + Tab。

## 用法

    python tools/sync_canif.py            # 生成并注入
    python tools/sync_canif.py --dry-run  # 只打印，不写文件

@author binbina
"""

import io
import json
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.join(ROOT, "tools"))

CFG_DIR = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config")
GEN_DIR = os.path.join(CFG_DIR, "CanIf", "GEN")
HDR = os.path.join(CFG_DIR, "CanIf_Cfg.h")
SRC = os.path.join(CFG_DIR, "CanIf_Cfg.c")

# 项目参数从 Can.json 读（02.5）。原来这些常量写死在脚本里，换项目就要改
# 工具本身 —— 那正是"项目参数混进通用脚本"的典型症状。
CAN_JSON = os.path.join(CFG_DIR, "Can", "Can.json")
with io.open(CAN_JSON, encoding="utf-8") as _f:
    _CAN = json.load(_f)

# 编号起点不在这里定义：它由 `CanIf.json` 的 `rxPduIdBase` 决定、生成器已经
# 编进宏值里。原来 Can.json 还另有一份 `canIfPduIdBase`，两处必然分叉 ——
# 02.6 方案 A 收掉，现在这里只从生成物读实际编号。

# 上层回调：M22 起 CAN1 的 34 条统一走 PduR → Com（信号解包）。
#
# 但 `App_CanIfRxIndication` 不能直接撤 —— 它是 `!k` 的"pdu 计数"来源，
# M19 的 34 项验收全靠它判"CanIf 软件过滤有没有把帧丢掉或投错项"。
# 所以每条报文生成一个 3 行 shim：先喂调试计数（保留可观测性），
# 再交给 PduR。把统计放在 shim 里而不是删掉，是因为"能看见"比"干净"重要。
# 前缀来自 `CanIf.json` 的 `shimPrefixRx/Tx`，**不含网络名**：网络名由下面拼，
# 这样多网络时自动正确，也不会把 "CAN1" 写死在模板里（02.6 方案 B）。
CANIF_JSON = os.path.join(CFG_DIR, "CanIf", "CanIf.json")
with io.open(CANIF_JSON, encoding="utf-8") as _f:
    _CANIF = json.load(_f)
_NET = _CANIF["networks"][0]

SHIM_PREFIX_RX = _NET.get("shimPrefixRx", "CanIfCfg_RxPduR_") + _NET["name"] + "_"
SHIM_PREFIX_TX = _NET.get("shimPrefixTx", "CanIfCfg_TxPduR_") + _NET["name"] + "_"

# CAN1 发送报文 → (shim 后缀, CanIf TX PDU 宏, PduR 路径宏)
# 后缀与 `CANIF_TX_MAP`（tools/sync_pdur.py）保持一致的短名，
# 这样两个脚本生成的回调名与 PduR 宏名能对得上眼。
#
# 02.6 起 `canIfMacro` 的唯一来源是 **Can.json 的邮箱表**（TX 条目），
# `txPdus` 只留 `short`。按 `TX_<short>` 去查，查不到就报错 ——
# 三处各写一份宏名的话，改一处忘一处会生成指向错误 PDU 的 shim。
_CANIF_TX_OF = {}
for _ch in _CAN.get("channels", []):
	for _e in _ch["mailboxes"]:
		if _e["dir"] == "TX" and "canIfMacro" in _e:
			_CANIF_TX_OF[_e["name"]] = _e["canIfMacro"]

TX_MAP = {}
for _e in _CAN["txPdus"]:
	_key = "TX_" + _e["short"]
	if _key not in _CANIF_TX_OF:
		raise SystemExit("Can.json: txPdus 的 %s 找不到对应 TX 邮箱 %s"
		                 % (_e["dbc"], _key))
	TX_MAP[_e["dbc"]] = (_e["short"], _CANIF_TX_OF[_key], _e["pdurMacro"])

BEGIN_MARK = "/* @generated BEGIN: CAN1 real matrix */"
END_MARK = "/* @generated END: CAN1 real matrix */"



def generate():
    """跑一遍 as-master 的生成器，刷新 GEN/ 目录。"""
    from generator import Generate
    buf = io.StringIO()
    old = sys.stdout
    sys.stdout = buf
    try:
        Generate([os.path.join(CFG_DIR, "CanIf", "CanIf.json")], force=True)
    finally:
        sys.stdout = old
    txt = buf.getvalue()
    if "Error" in txt or "Traceback" in txt:
        raise SystemExit("生成器报错：\n" + txt)


def collect():
    """返回 (宏列表, 表体文本)。

    @note 02.6 方案 A 之后，生成器已经按项目约定产出：宏名 `CANIF_RX_CAN1_*`、
          编号从 `rxPduIdBase`（23）起、`hoh` 是真实邮箱号、`canid` 8 位定宽。
          所以这里**不再重命名 / 偏移编号 / 查 PF 表**，只做两件仍然必须的事：

          | 事 | 为什么留在这里 |
          |----|----------------|
          | 缩进从 2 空格改成 Tab | 产物要入库，风格要与手写的 CAN0 段一致 |
          | 生成 shim 函数体 | 它调 `App_CanIfRxIndication`（`!k` 的计数源）再转 PduR，是**跨模块知识**，不属于 CanIf 生成器 |

          好处不只是少几十行：原来用正则**啃生成器的 C 文本**（抓 5 行固定格式），
          生成器改一个空格就静默失配。现在抓的是"语义已正确"的字段，格式变了
          只会让正则不匹配、直接报错，不会算出错的值。
    """
    h = io.open(os.path.join(GEN_DIR, "CanIf_Cfg.h"), encoding="utf-8").read()
    c = io.open(os.path.join(GEN_DIR, "CanIf_Cfg.c"), encoding="utf-8").read()

    macros = []
    for m in re.finditer(
            r"^#define (CANIF_RX_CAN1_\w+)\s+(\d+)u /\* CAN1 id=(0x[0-9A-F]+) \*/$", h, re.M):
        macros.append({"name": m.group(1), "num": int(m.group(2)),
                       "id": int(m.group(3), 16)})
    if not macros:
        raise SystemExit("GEN/CanIf_Cfg.h 里没有 CANIF_RX_CAN1_* 宏")

    i = c.index("static const CanIf_RxPduType CanIf_RxPdus_CAN1[] = {")
    j = c.index("\n};", i) + 3
    raw = c[i:j]

    blocks = re.findall(
        r"\{\s*\n\s*(CanIfCfg_RxPduR_\w+),\s*\n"
        r"\s*(CANIF_RX_\w+),\s*\n"
        r"\s*(0x[0-9A-F]+), /\* canid \*/\s*\n"
        r"\s*(0x[0-9A-F]+), /\* mask \*/\s*\n"
        r"\s*(\d+), /\* hoh \*/", raw)
    if len(blocks) != len(macros):
        raise SystemExit("表体解析出 %d 条，与宏数量 %d 不符（生成器格式变了？）"
                         % (len(blocks), len(macros)))

    out = ["static const CanIf_RxPduType CanIf_RxPdus_CAN1[] = {"]
    shims = []
    for shim, canif_macro, canid_s, mask_s, hoh_s in blocks:
        name = canif_macro[len("CANIF_RX_CAN1_"):]
        canid = int(canid_s, 16)
        pf = (canid >> 16) & 0xFF
        mask = int(mask_s, 16)

        # 每条一个 shim：`RxPduType` 只有函数指针、没有 context 字段，
        # pathId 只能靠「每条一个函数」带进去。
        shims.append(
            "static void %s(PduIdType RxPduId, const PduInfoType *PduInfoPtr)\n"
            "{\n"
            "\tApp_CanIfRxIndication(RxPduId, PduInfoPtr);   /* `!k` 的 pdu 计数（M19 判据） */\n"
            "\tPduR_CanIfRxIndication((PduIdType)PDUR_CAN1_%s_RX, PduInfoPtr);\n"
            "}" % (shim, name))

        out.append("\t{")
        out.append("\t\t%s,\t/* rxInd */" % shim)
        out.append("\t\t%s," % canif_macro)
        out.append("\t\t0x%08Xu,\t\t\t/* canid：PF=0x%02X */" % (canid, pf))
        if mask == 0x1FFFFFFF:
            out.append("\t\t0x1FFFFFFFu,\t/* mask：精确匹配，忽略源地址 */")
        else:
            out.append("\t\t0x%08Xu,\t/* mask */" % mask)
        out.append("\t\t%su,\t\t\t/* hoh：mb%s（PF=0x%02X 段） */" % (hoh_s, hoh_s, pf))
        out.append("\t},")
    out.append("};")

    tx_shims = []
    for dbc_name, (short, canif_macro, pdur_macro) in TX_MAP.items():
        tx_shims.append(
            "static void %s%s(PduIdType TxPduId, Std_ReturnType result)\n"
            "{\n"
            "\tApp_CanIfTxConfirmation(TxPduId, result);      /* `!b` burst 的确认计数 */\n"
            "\tPduR_CanIfTxConfirmation((PduIdType)%s, result);\n"
            "} /* %s → %s */" % (SHIM_PREFIX_TX, short, pdur_macro, dbc_name, canif_macro))

    head = ["/* ---- PduR 回调 shim（M22）----", " *",
            " * 每条报文一个：`CanIf_RxPduType` / `CanIf_TxPduType` 只有函数指针、",
            " * 没有 context 字段，所以 pathId 只能靠「每条一个函数」带进去。",
            " * 先调 App 的统计回调再进 PduR —— 统计是 `!k` / `!b` 的数据源。",
            " */"]
    body = "\n".join(head + tx_shims + [""] + shims + [""] + out)
    return macros, body


def build_header(macros):
    out = [BEGIN_MARK,
           "/* 由 tools/sync_canif.py 从 can1.dbc 生成，请勿手改。",
           " * 编号从 %d 开始：CAN0 已占用 0~%d。 */"
           % (macros[0]["num"], macros[0]["num"] - 1)]
    # 编号直接用生成器给的（它按 `rxPduIdBase` 从 23 起编），不再本地 +k
    _PRE = "CANIF_RX_CAN1_"
    for x in sorted(macros, key=lambda y: y["num"]):
        # 沿用与手写 CAN0 段**完全相同**的模板（前缀 + %-44s + 空格 + 编号），
        # 这样 34 行宏的列宽一字不差。不要试图"算总列宽"——我试过，
        # 把 `%-44s` 换成整行的 `%-66s` 差了 2 列，产出 34 行纯空白 diff。
        assert x["name"].startswith(_PRE), x["name"]
        out.append("#define %s%-44s (%du)  /**< 0x%08X */"
                   % (_PRE, x["name"][len(_PRE):], x["num"], x["id"]))
    out.append("#define CANIF_RX_CAN1_NUM                           (%du)" % len(macros))
    out.append(END_MARK)
    return "\n".join(out)


def main():
    dry = "--dry-run" in sys.argv

    generate()
    print("generator: ok")
    macros, body = collect()
    total = macros[-1]["num"] + 1
    hdr = build_header(macros)

    if dry:
        print("\n=== 头文件将写入（前 6 / 末 2）===")
        lines = hdr.splitlines()
        print("\n".join(lines[:6]))
        print("...")
        print("\n".join(lines[-2:]))
        print("\n=== 表体前 16 行 ===")
        print("\n".join(body.splitlines()[:16]))
        print("...")
        print("\nCANIF_RX_PDU_NUM 将改为 %d" % total)
        return 0

    # 头文件
    hs = io.open(HDR, encoding="utf-8").read()
    if BEGIN_MARK in hs:
        a = hs.index(BEGIN_MARK)
        b = hs.index(END_MARK) + len(END_MARK)
        hs = hs[:a] + hdr + hs[b:]
    else:
        anchor = "/* ============================ [ TX PDU 编号 ] ============================ */"
        if anchor not in hs:
            raise SystemExit("头文件里找不到插入锚点")
        hs = hs.replace(anchor, hdr + "\n\n" + anchor, 1)
    hs = re.sub(r"#define CANIF_RX_PDU_NUM\s+\(\d+u\)",
                "#define CANIF_RX_PDU_NUM            (%du)" % total, hs, count=1)
    io.open(HDR, "w", encoding="utf-8", newline="\n").write(hs)
    print("header: %d 条，编号 %d~%d，CANIF_RX_PDU_NUM = %d"
          % (len(macros), macros[0]["num"], total - 1, total))

    # 源文件
    cs = io.open(SRC, encoding="utf-8").read()
    if BEGIN_MARK in cs:
        a = cs.index(BEGIN_MARK)
        b = cs.index(END_MARK) + len(END_MARK)
        cs = cs[:a] + BEGIN_MARK + "\n" + body + "\n" + END_MARK + cs[b:]
    else:
        anchor = "static const CanIf_RxPduType CanIf_RxPdus_CAN1[] = {"
        if anchor not in cs:
            raise SystemExit("源文件里找不到 CanIf_RxPdus_CAN1")
        a = cs.index(anchor)
        b = cs.index("\n};", a) + 3
        cs = cs[:a] + BEGIN_MARK + "\n" + body + "\n" + END_MARK + cs[b:]
    io.open(SRC, "w", encoding="utf-8", newline="\n").write(cs)
    print("source: 注入 %d 条 RX" % len(macros))
    return 0


if __name__ == "__main__":
    sys.exit(main())
