# SSAS - Simple Smart Automotive Software
# Copyright (C) 2021 Parai Wang <parai@foxmail.com>

import pprint
import os
import json
from .helper import *

from .Com import get_messages
from .dbc.database import classify

__all__ = ["Gen"]


def Gen_CanIf(cfg, dir):
    modules = []
    for network in cfg["networks"]:
        for pdu in network["RxPdus"] + network["TxPdus"]:
            if pdu["up"] not in modules:
                modules.append(pdu["up"])
    H = open("%s/CanIf_Cfg.h" % (dir), "w")
    GenHeader(H)
    H.write("#ifndef CANIF_CFG_H\n")
    H.write("#define CANIF_CFG_H\n")
    H.write("/* ================================ [ INCLUDES  ] ============================================== */\n")
    H.write("/* ================================ [ MACROS    ] ============================================== */\n")
    ID = 0
    for network in cfg["networks"]:
        H.write("#define CANIF_CHL_%s %su\n" % (network["name"], ID))
        ID += 1
    H.write("\n")
    # 编号起始可由配置指定（项目里 CAN0 已占 0~22，CAN1 从 23 起）
    ID = cfg.get("rxPduIdBase", 0)
    for network in cfg["networks"]:
        for pdu in network["RxPdus"]:
            H.write("#define CANIF_%s %su /* %s id=0x%08X */\n"
                    % (pdu.get("pduIdName", pdu["name"]), ID, network["name"],
                       toNum(pdu["id"]) & 0x1FFFFFFF))
            ID += 1
    H.write("\n")
    ID = 0
    for network in cfg["networks"]:
        for pdu in network["TxPdus"]:
            H.write("#define CANIF_%s %su /* %s id=0x%x */\n" % (pdu["name"], ID, network["name"], toNum(pdu["id"])))
            ID += 1
    H.write("#ifndef CANIF_MAIN_FUNCTION_PERIOD\n")
    H.write("#define CANIF_MAIN_FUNCTION_PERIOD %su\n" % (cfg.get("MainFunctionPeriod", 10)))
    H.write("#endif\n")
    H.write("#define CANIF_CONVERT_MS_TO_MAIN_CYCLES(x) \\\n")
    H.write("  ((x + CANIF_MAIN_FUNCTION_PERIOD - 1u) / CANIF_MAIN_FUNCTION_PERIOD)\n\n")
    for netId, network in enumerate(cfg["networks"]):
        if network.get("TxTimeout", 100):
            H.write("#define CANIF_USE_TX_TIMEOUT\n\n")
            break
    H.write("%s#define CANIF_USE_PB_CONFIG\n\n" % ("" if cfg.get("UsePostBuildConfig", False) else "// "))
    H.write("%s#define CANIF_USE_TX_CALLOUT\n\n" % ("" if cfg.get("UseTxCallout", False) else "// "))
    H.write("%s#define CANIF_USE_RX_CALLOUT\n\n" % ("" if cfg.get("UseRxCallout", False) else "// "))
    H.write("#ifndef CANIF_RX_PACKET_POOL_SIZE\n")
    H.write("#define CANIF_RX_PACKET_POOL_SIZE %su\n" % (cfg.get("RxPacketPoolSize", 0)))
    H.write("#endif\n\n")
    H.write("#ifndef CANIF_TX_PACKET_POOL_SIZE\n")
    H.write("#define CANIF_TX_PACKET_POOL_SIZE %su\n" % (cfg.get("TxPacketPoolSize", 0)))
    H.write("#endif\n\n")
    H.write("#ifndef CANIF_RX_PACKET_DATA_SIZE\n")
    H.write("#define CANIF_RX_PACKET_DATA_SIZE %su\n" % (cfg.get("RxPacketDataSize", 64)))
    H.write("#endif\n\n")
    H.write("#ifndef CANIF_TX_PACKET_DATA_SIZE\n")
    H.write("#define CANIF_TX_PACKET_DATA_SIZE %su\n" % (cfg.get("TxPacketDataSize", 64)))
    H.write("#endif\n\n")
    H.write("/* ================================ [ TYPES     ] ============================================== */\n")
    H.write("/* ================================ [ DECLARES  ] ============================================== */\n")
    H.write("/* ================================ [ DATAS     ] ============================================== */\n")
    H.write("/* ================================ [ LOCALS    ] ============================================== */\n")
    H.write("/* ================================ [ FUNCTIONS ] ============================================== */\n")
    H.write("#endif /* CANIF_CFG_H */\n")
    H.close()

    C = open("%s/CanIf_Cfg.c" % (dir), "w")
    GenHeader(C)
    C.write("/* ================================ [ INCLUDES  ] ============================================== */\n")
    C.write('#include "CanIf.h"\n')
    C.write('#include "CanIf_Cfg.h"\n')
    C.write('#include "CanIf_Priv.h"\n')
    for mod in modules:
        if mod == "PduR":
            C.write('#include "PduR_CanIf.h"\n')
        elif mod[:4] == "User":
            pass
        else:
            C.write('#include "%s.h"\n' % (mod))
        if mod[:4] == "User":
            pass
        elif mod not in ["OsekNm", "CanNm", "CanTSyn", "Xcp"]:
            C.write('#include "%s_Cfg.h"\n' % (mod))
    C.write("/* ================================ [ MACROS    ] ============================================== */\n")
    C.write("/* ================================ [ TYPES     ] ============================================== */\n")
    C.write("/* ================================ [ DECLARES  ] ============================================== */\n")
    rxinds = []
    txinds = []
    for netId, network in enumerate(cfg["networks"]):
        for pdu in network["RxPdus"]:
            if pdu["up"][:4] == "User" and pdu["up"] not in rxinds:
                rxinds.append(pdu["up"])
                C.write("void %s_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);\n" % (pdu["up"]))
    for netId, network in enumerate(cfg["networks"]):
        for pdu in network["TxPdus"]:
            if pdu["up"][:4] == "User" and pdu["up"] not in txinds:
                txinds.append(pdu["up"])
                C.write("void %s_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);\n" % (pdu["up"]))
    C.write("/* ================================ [ DATAS     ] ============================================== */\n")
    for netId, network in enumerate(cfg["networks"]):
        if len(network["RxPdus"]) == 0:
            continue
        C.write("static const CanIf_RxPduType CanIf_RxPdus_%s[] = {\n" % (network["name"]))
        for pdu in network["RxPdus"]:
            for pdu_ in network["RxPdus"]:
                if pdu_ == pdu:
                    break
                canid = toNum(pdu["id"]) & 0x1FFFFFFF
                mask = toNum(pdu.get("mask", "0xFFFFFFFF")) & 0x1FFFFFFF
                canid_ = toNum(pdu_["id"]) & 0x1FFFFFFF
                mask_ = toNum(pdu_.get("mask", "0xFFFFFFFF")) & 0x1FFFFFFF
                if (canid & mask_) == (canid_ & mask_):
                    raise Exception(f"Duplicate Rx Pdus: {pdu} vs {pdu_}")
                if (canid & mask) == (canid_ & mask):
                    raise Exception(f"Duplicate Rx Pdus: {pdu} vs {pdu_}")
            C.write("  {\n")
            # rxInd：`rxIndName` 优先（项目用它挂 shim：先喂调试计数再转 PduR）。
            # 不提供时完全走上游原来的三选一，其它使用者不受影响。
            if pdu.get("rxIndName"):
                C.write("    %s,\n" % pdu["rxIndName"])
            elif pdu["up"] in ["PduR", "Xcp"]:
                C.write("    %s_CanIfRxIndication,\n" % (pdu["up"]))
            else:
                C.write("    %s_RxIndication,\n" % (pdu["up"]))
            # rxPduId：`pduIdName` 优先（项目命名是 CANIF_RX_<NET>_<MSG>）
            if pdu.get("pduIdName"):
                C.write("    CANIF_%s,\n" % pdu["pduIdName"])
            elif pdu["up"] in ["OsekNm", "CanNm", "CanTSyn", "Xcp"]:
                C.write("    %s, /* NetId */\n" % (netId))
            elif pdu["up"][:4] == "User":
                C.write("    CANIF_%s, /* rxPduId */\n" % (pdu["name"]))
            else:
                C.write("    %s_%s,\n" % (pdu["up"].upper(), pdu["name"]))
            # 0x%08X：项目要求 8 位定宽（`0x0CF00400u`），上游原样是 `0xcf00400`
            C.write("    0x%08X, /* canid */\n" % (toNum(pdu["id"]) & 0x1FFFFFFF))
            C.write("    0x%08X, /* mask */\n" % (toNum(pdu.get("mask", "0xFFFFFFFF")) & 0x1FFFFFFF))
            C.write("    %s, /* hoh */\n" % (pdu.get("hoh", 0)))
            C.write("  },\n")
        C.write("};\n\n")
    for netId, network in enumerate(cfg["networks"]):
        for pdu in network["TxPdus"]:
            if pdu.get("dynamic", False):
                C.write("static Can_IdType canidOf%s = %s;\n" % (pdu["name"], pdu["id"]))
    C.write("static const CanIf_TxPduType CanIf_TxPdus[] = {\n")
    for netId, network in enumerate(cfg["networks"]):
        for pdu in network["TxPdus"]:
            C.write("  {\n")
            if pdu["up"] in ["PduR", "Xcp"]:
                C.write("    %s_CanIfTxConfirmation,\n" % (pdu["up"]))
            else:
                C.write("    %s_TxConfirmation,\n" % (pdu["up"]))
            if pdu["up"] in ["OsekNm", "CanNm", "CanTSyn", "Xcp"]:
                C.write("    %s, /* NetId */\n" % (netId))
            elif pdu["up"][:4] == "User":
                C.write("    CANIF_%s, /* txPduId */\n" % (pdu["name"]))
            else:
                C.write("    %s_%s,\n" % (pdu["up"].upper(), pdu["name"]))
            C.write("    0x%x, /* canid */\n" % (toNum(pdu["id"])))
            if pdu.get("dynamic", False):
                C.write("    &canidOf%s, /* p_canid */\n" % (pdu["name"]))
            else:
                C.write("    NULL, /* p_canid */\n")
            C.write("    %s, /* hoh */\n" % (pdu.get("hoh", 0)))
            C.write("    %s, /* ControllerId */\n" % (netId))
            C.write("    #if CANIF_TX_PACKET_POOL_SIZE > 0\n")
            C.write("    %s, /* bUseTxPool */\n" % (str(pdu.get("UseTxPool", False)).upper()))
            C.write("    #endif\n")
            C.write("  },\n")
    C.write("};\n\n")
    C.write("static CanIf_CtrlContextType CanIf_CtrlContexts[%s];\n" % (len(cfg["networks"])))

    C.write("static const CanIf_CtrlConfigType CanIf_CtrlConfigs[] = {\n")
    for netId, network in enumerate(cfg["networks"]):
        C.write("  {\n")
        if len(network["RxPdus"]) == 0:
            C.write("    NULL,\n")
            C.write("    0u,\n")
        else:
            C.write("    CanIf_RxPdus_%s,\n" % (network["name"]))
            C.write("    ARRAY_SIZE(CanIf_RxPdus_%s),\n" % (network["name"]))
        C.write("    #if defined(CANIF_USE_TX_TIMEOUT) && defined(USE_CANSM)\n")
        C.write("    CANIF_CONVERT_MS_TO_MAIN_CYCLES(%su),\n" % (network.get("TxTimeout", 100)))
        C.write("    #endif\n")
        C.write("  },\n")
    C.write("};\n")

    C.write("const CanIf_ConfigType CanIf_Config = {\n")
    C.write("  CanIf_TxPdus,\n")
    C.write("  CanIf_CtrlContexts,\n")
    C.write("  CanIf_CtrlConfigs,\n")
    C.write("  ARRAY_SIZE(CanIf_TxPdus),\n")
    C.write("  ARRAY_SIZE(CanIf_CtrlContexts),\n")
    C.write("};\n\n")
    C.write("/* ================================ [ LOCALS    ] ============================================== */\n")
    C.write("/* ================================ [ FUNCTIONS ] ============================================== */\n")
    C.close()


def extract(cfg, dir):
    cfg_ = dict(cfg)
    cfg_["networks"] = []
    bNew = False
    hrh = 0
    hth = 0
    for network in cfg["networks"]:
        E2E = network.get("E2E", [])
        NumHrh = network.get("NumHrh", 1)
        NumHth = network.get("NumHth", 1)
        ignore = network.get("ignore", [])
        if "dbc" in network:
            network_ = dict(network)
            path = network["dbc"]
            del network_["dbc"]
            me = network["me"]
            name = network["name"]
            if not os.path.isfile(path):
                path = os.path.abspath(os.path.join(dir, "..", path))
            if not os.path.isfile(path):
                raise Exception("File %s not exists" % (path))
            # hoh：项目要的是**真实邮箱号**（按报文 PF 落到哪个段邮箱），
            # 不是生成器默认的"每网络递增"。查表来源由 `hohFrom` 声明 ——
            # 依赖是配置写出来的，不是生成器硬编码某个项目的路径。
            #
            # 不声明 hohFrom 时行为完全不变（仍用递增的 hrh），
            # 上游其它使用者不受影响。
            hoh_by_pf = {}
            if "hohFrom" in network:
                hp = os.path.join(dir, "..", network["hohFrom"])
                if not os.path.isfile(hp):
                    raise Exception("hohFrom 指向的文件不存在：%s" % hp)
                with open(hp) as _f:
                    _can = json.load(_f)
                for _ch in _can.get("channels", []):
                    for _e in _ch["mailboxes"]:
                        if "pf" in _e:
                            hoh_by_pf[int(_e["pf"], 0)] = _e["mb"]

            messages = classify(get_messages(path), me)
            for msg in messages:
                if msg["name"] in ignore:
                    continue
                rn = "%s_%s" % (name, toMacro(msg["name"]))
                rn = rn.upper()
                if msg["dir"] == "TX":
                    if "TX" not in rn:
                        rn += "_TX"
                    kl = "TxPdus"
                    UseTxPool = msg["name"] in E2E
                    pdu = {"name": rn, "id": msg["id"], "hoh": hth, "up": "PduR", "UseTxPool": UseTxPool}
                else:
                    if "RX" not in rn:
                        rn += "_RX"
                    kl = "RxPdus"

                    # hoh：有 pf 标签就查表，查不到退回递增（保持上游行为）
                    pf = (msg["id"] & 0x1FFFFFFF) >> 16 & 0xFF
                    hoh = hoh_by_pf.get(pf, hrh)

                    pdu = {"name": rn, "id": msg["id"], "hoh": hoh, "up": "PduR"}

                    # 项目的命名约定与上游不同，用两个可选覆盖表达：
                    #   pduIdName  → `#define CANIF_<pduIdName>` 与 rxPduId 字段
                    #   rxIndName  → 表里的回调名（项目要 shim，不是直连 PduR）
                    # 不给这两个参数时，下面模板会走原逻辑。
                    msg_macro = toMacro(msg["name"])
                    if network.get("rxPduNamePrefix"):
                        pdu["pduIdName"] = "%s%s_%s" % (network["rxPduNamePrefix"], name, msg_macro)
                    if network.get("rxIndicationShim"):
                        pdu["rxIndName"] = "%s%s_%s" % (
                            network.get("shimPrefixRx", "CanIfCfg_RxPduR_"), name, msg_macro)
                if kl not in network_:
                    network_[kl] = []
                network_[kl].append(pdu)
            cfg_["networks"].append(network_)
            bNew = True
        else:
            cfg_["networks"].append(network)
        hrh += NumHrh
        hth += NumHth
    if bNew:
        with open("%s/CanIf.json" % (dir), "w") as f:
            json.dump(cfg_, f, indent=2)
    hrh = 0
    hth = 0
    for network in cfg_["networks"]:
        NumHrh = network.get("NumHrh", 1)
        NumHth = network.get("NumHth", 1)
        network["RxPdus"].sort(key=lambda x: toNum(x["id"]) & 0x1FFFFFFF)
        network["TxPdus"].sort(key=lambda x: toNum(x["id"]) & 0x1FFFFFFF)
        for pdu in network["RxPdus"]:
            hh = pdu.get("hoh", hrh)
            if hh < hrh or hh > (hrh + NumHrh):
                raise Exception("Invalid hoh for: %s" % (pdu))
            pdu["hoh"] = hh
        for pdu in network["TxPdus"]:
            hh = pdu.get("hoh", hth)
            if hh < hth or hh > (hth + NumHth):
                raise Exception("Invalid hoh for: %s" % (pdu))
            pdu["hoh"] = hh
        hrh += NumHrh
        hth += NumHth
    return cfg_


def Gen(cfg):
    dir = os.path.join(os.path.dirname(cfg), "GEN")
    os.makedirs(dir, exist_ok=True)
    with open(cfg) as f:
        cfg = json.load(f)
    cfg_ = extract(cfg, dir)
    Gen_CanIf(cfg_, dir)
    return ["%s/CanIf_Cfg.c" % (dir)]
