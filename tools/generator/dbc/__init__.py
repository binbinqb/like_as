# SSAS - Simple Smart Automotive Software
# Copyright (C) 2021 Parai Wang <parai@foxmail.com>

__all__ = ["dbc"]

from . import ascyacc

#: 解析/后处理语义版本。字段名、单位、后处理规则一改就 +1：
#: `database.py` 把它放进缓存键，否则同一进程里旧结果会被当成新结果。
PARSER_VERSION = 1


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
    """给每条消息补一个明确的帧类型字段 `ext`（02.4）。

    背景：DBC 用 **ID 的 bit31** 表示扩展帧（`0x80000000 | CAN_ID`）。
    原实现只按"数值大于 0x7FF 就补标记"处理，**没有把帧类型单独存下来**，
    于是下游只能靠 `id > 0x7FF` 反推 —— 扩展帧 ID 恰好是 0x123 时就会
    判成标准帧。这是规范明确禁止的推断方式。

    这里保留原来的补标记行为（兼容没写 bit31 但 ID 超过标准帧范围的
    DBC），同时把 `ext` 落成独立字段，下游一律读 `msg["ext"]`。

    @note `id` 仍然带 bit31（CanIf 生成时再 `& 0x1FFFFFFF`），这样现有
    产物逐字节不变；`can_id` 是去掉标记后的总线 ID，给新代码用。
    """
    for msg in p["messages"]:
        id = msg["id"]
        if id > 0x7FF:
            id |= 0x80000000
            msg["id"] = id
        msg["ext"] = True if (id & 0x80000000) else False
        msg["can_id"] = id & 0x1FFFFFFF
        # CAN 规范里扩展帧最大 0x1FFFFFFF。超过说明 DBC 的 ID 本身写错了
        # （例如把 0x20000000 当成普通 ID），这种"看起来能解析"的错误
        # 必须在解析期拒绝，否则会生成一个永远匹配不上的过滤器。
        if msg["can_id"] > 0x1FFFFFFF:
            raise Exception("DBC: invalid CAN ID 0x%X (>0x1FFFFFFF) in message %s"
                            % (msg["can_id"], msg.get("name", "?")))


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


def parse_content(data, label="<memory>"):
    """从**已读入的内容**解析。

    单独拆出来是为了让缓存层能"哈希哪份字节就解析哪份字节"：
    如果先哈希、再让解析器自己去 open 一次，中间文件被改就会得到
    "用旧键缓存了新内容"的错配。
    """
    reject_unsupported(label, data)
    p = ascyacc.parse(data)
    post_process_period(p)
    post_process_init(p)
    post_process_id_type(p)
    return p


def parse(file):
    print(f"DBC: {file}")
    with open(file, "r", encoding="utf-8", errors="replace") as fp:
        data = fp.read()
    return parse_content(data, file)


def dbc(path):
    p = parse(path)
    return p["messages"]
