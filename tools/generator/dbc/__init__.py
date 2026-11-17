# SSAS - Simple Smart Automotive Software
# Copyright (C) 2021 Parai Wang <parai@foxmail.com>

__all__ = ["dbc"]

from . import ascyacc


def get_period(p, msg):
    CycleTime, FirstTime = None, None
    id = msg["id"]
    for ba in p.get("baList", []):
        if (ba[1] == '"GenMsgCycleTime"') and (ba[2] == "BO_"):
            if ba[3] == id:
                CycleTime = ba[4]
        if (ba[1] == '"GenMsgDelayTime"') and (ba[2] == "BO_"):
            if ba[3] == id:
                FirstTime = ba[4]
    return CycleTime, FirstTime


def get_init(p, msg, sig):
    """DBC-02：初值必须同时匹配报文 ID 与信号名。

    只比信号名的话，两条报文有同名信号（矩阵里非常常见，比如每条报文
    都有一个 State）时，先解析到的初值会串给后一条 —— 错得很安静。
    BA_ 里 SG_ 条目的结构是 [?, attr, "SG_", boId, sigName, value]，
    boId 与此处 msg["id"] 同源（post_process_init 跑在 post_process_id_type
    之前，两边都是原始数值 ID，可直接比较）。
    """
    name = sig["name"]
    id = msg["id"]
    for ba in p.get("baList", []):
        if (ba[1] == '"GenSigStartValue"') and (ba[2] == "SG_"):
            if (ba[3] == id) and (ba[4] == name):
                return ba[5]
    return None


def get_comment(p, msg, sig):
    """DBC-02 同因：注释的 SG_ 条目 [?, "SG_", boId, sigName, text] 也要匹配报文。"""
    name = sig["name"]
    id = msg["id"]
    for cm in p.get("cmList", []):
        if (cm[1] == "SG_") and (cm[2] == id) and (cm[3] == name):
            return cm[4]
    return None


def post_process_period(p):
    for msg in p["messages"]:
        CycleTime, FirstTime = get_period(p, msg)
        if CycleTime != None:
            msg.update({"CycleTime": CycleTime})
        if FirstTime != None:
            msg.update({"FirstTime": FirstTime})

def post_process_init(p):
    for msg in p["messages"]:
        for sig in msg["signals"]:
            init = get_init(p, msg, sig)
            if init != None:
                # DBC-01：统一叫 InitialValue（Com.py 的消费名）。
                # 旧名 InitValue 是"写的人一个名、读的人另一个名"，非零初值
                # 永远进不了生成配置；改名后由 Com.py 的 sig_initial_value()
                # 兼容旧输入并拒绝冲突值。
                sig.update({"InitialValue": init})
            comment = get_comment(p, msg, sig)
            if comment != None:
                sig.update({"comment": comment})


def post_process_id_type(p):
    for msg in p["messages"]:
        id = msg["id"]
        if id > 0x7FF:
            id |= 0x80000000
            msg["id"] = id


def reject_unsupported(file, data):
    """DBC-05：解析前显式拒绝本链路不支持的语言特性。

    不做这一步的后果：ascyacc 的 SG_ 语法根本不认 mux 令牌，多路复用的
    DBC 会在 yacc 里抛出"Invalid syntax"级别的晦涩错误；更糟的是某些
    形式可能被静默漏解析 —— 信号丢了但生成照样"成功"，产出半套配置。
    这里宁可拒绝也不带病生成。
    """
    import re
    # 先剔除 NS_ 段：它只是关键字声明表，里面的 SIG_VALTYPE_ 等词条
    # 与真正的语句同名，不剔除会把每份正常 DBC 都误杀
    lines = []
    in_ns = False
    for line in data.splitlines():
        s = line.strip()
        if s.startswith("NS_"):
            in_ns = True
            continue
        if in_ns:
            if s.startswith("BS_"):
                in_ns = False
            continue
        lines.append(s)
    for i, s in enumerate(lines, 1):
        # 多路复用信号：`SG_ name mN : ...` / `SG_ name M : ...`
        if re.match(r"^SG_\s+\S+\s+(m\d*|M)\s*:", s):
            raise Exception("%s:%d: multiplexed signal not supported: %s"
                            % (file, i, s.split()[1]))
        # 扩展多路复用
        if s.startswith("SG_MUL_VAL_"):
            raise Exception("%s:%d: SG_MUL_VAL_ (extended multiplexing) not supported"
                            % (file, i))
        # 浮点/64 位信号类型（0=float32 1=float64 2=reserved 3=double）
        if s.startswith("SIG_VALTYPE_"):
            raise Exception("%s:%d: SIG_VALTYPE_ (float/64bit signal) not supported"
                            % (file, i))


def parse(file):
    print(f"DBC: {file}")
    fp = open(file, "r")
    data = fp.read()
    fp.close()
    reject_unsupported(file, data)
    p = ascyacc.parse(data)
    post_process_period(p)
    post_process_init(p)
    post_process_id_type(p)
    return p


def dbc(path):
    p = parse(path)
    return p["messages"]
