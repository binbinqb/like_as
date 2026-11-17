#!/usr/bin/env python3
# /**
#  * @file    dbc_init_check.py
#  * @brief   DBC-01/02 验收：初值与注释的报文归属、字段名统一、兼容与冲突拒绝
#  *
#  * @details 依据《like_as CAN 协议栈与 DBC 配置链推进指南》批次 C 前置任务：
#  *          为 DBC-01/02 添加最小合成输入，再一起修复。
#  *
#  *          合成 DBC `tools/syn_dbc/syn_init.dbc` 构造了真实矩阵里没有的
#  *          边界：两条报文同名信号 State 带不同非零初值、同名注释、
#  *          一条无初值信号。真实 can0/can1.dbc 里 GenSigStartValue 为 0 条，
#  *          所以修复不会改变现有生成产物 —— 这一点由 a4_gen_check.py
#  *          的幂等检查另行保证，本脚本只对解析层与 Com 消费层负责。
#  *
#  *          检查项：
#  *          - B1  DBC-02：两条报文同名信号各自拿到自己的初值（不再串用）
#  *          - B2  DBC-02：注释同样按报文归属
#  *          - B3  DBC-01：解析输出的字段名统一为 InitialValue（不再是 InitValue）
#  *          - B4  无 GenSigStartValue 的信号解析结果不含初值键（走默认 0）
#  *          - B5  Com.sig_initial_value() 兼容旧字段名 InitValue
#  *          - B6  Com.sig_initial_value() 冲突值必须报错，不能静默挑一个
#  *          - B7  真实矩阵 can1.dbc 解析回归（修复不破坏既有输入）
#  *
#  * @author  binbina
#  * @note    运行：python tools/dbc_init_check.py（PC 侧，无需硬件）
#  */
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))

from generator.dbc import dbc  # noqa: E402

results = []


def note(name, ok, detail):
    results.append((name, ok, detail))


def parse_syn():
    root = os.path.dirname(os.path.abspath(__file__))
    return dbc(os.path.join(root, "syn_dbc", "syn_init.dbc"))


def sig_of(msgs, boId, name):
    for m in msgs:
        if m["id"] == boId:
            for s in m["signals"]:
                if s["name"] == name:
                    return s
    return None


def check_b1_b4(msgs):
    """解析层：按报文归属的初值/注释/字段名。"""
    a = sig_of(msgs, 512, "State")
    b = sig_of(msgs, 513, "State")
    aCnt = sig_of(msgs, 512, "Cnt")
    cRaw = sig_of(msgs, 514, "Raw")

    note("B1a 同名信号 A.State 初值 = 170",
         a is not None and a.get("InitialValue") == 170,
         "读到 %r" % (a.get("InitialValue") if a else None))
    note("B1b 同名信号 B.State 初值 = 85（不再串用 A 的）",
         b is not None and b.get("InitialValue") == 85,
         "读到 %r" % (b.get("InitialValue") if b else None))
    note("B2a A.State 注释按报文归属",
         a is not None and "MessageA" in (a.get("comment") or ""),
         "读到 %r" % (a.get("comment") if a else None))
    note("B2b B.State 注释按报文归属",
         b is not None and "MessageB" in (b.get("comment") or ""),
         "读到 %r" % (b.get("comment") if b else None))
    note("B3 解析输出统一用 InitialValue，不残留 InitValue 键",
         all(("InitValue" not in s) and ("InitialValue" in s)
             for m in msgs for s in m["signals"] if "InitialValue" in s),
         "任一信号残留 InitValue 即失败")
    note("B4 无 GenSigStartValue 的信号没有初值键（默认 0 由消费方补）",
         aCnt is not None and "InitialValue" not in aCnt
         and cRaw is not None and "InitialValue" not in cRaw,
         "Cnt/Raw 不该带 InitialValue")


def check_b5_b6():
    """消费层：Com.sig_initial_value 的兼容与冲突拒绝。"""
    from generator.Com import sig_initial_value

    r1 = sig_initial_value({"InitialValue": 170}, "s1")
    note("B5a 新字段名直接生效", r1 == 170, "读到 %r" % r1)
    r2 = sig_initial_value({"InitValue": 85}, "s2")
    note("B5b 旧字段名 InitValue 兼容", r2 == 85, "读到 %r" % r2)
    r3 = sig_initial_value({"InitialValue": 7, "InitValue": 7}, "s3")
    note("B5c 两字段同值不报错", r3 == 7, "读到 %r" % r3)

    try:
        sig_initial_value({"InitialValue": 170, "InitValue": 85}, "s4")
        note("B6 冲突值必须报错", False, "没有抛异常，静默挑了一个")
    except Exception as e:
        note("B6 冲突值必须报错", "170" in str(e) and "85" in str(e),
             "异常：%s" % e)


def check_b7():
    """真实矩阵回归：修复不改变既有输入的解析结果。"""
    path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..",
                        "app", "platform", "cvm0146", "src", "config", "dbc", "can1.dbc")
    if not os.path.isfile(path):
        note("B7 真实矩阵 can1.dbc 解析", False, "本地无客户 DBC，SKIP")
        return
    msgs = dbc(path)
    n = sum(len(m["signals"]) for m in msgs)
    bad = [s["name"] for m in msgs for s in m["signals"] if "InitValue" in s]
    note("B7 真实矩阵 can1.dbc 解析（%d 报文 / %d 信号）"
         % (len(msgs), n), len(bad) == 0,
         "残留 InitValue：%s" % bad[:5] if bad else "无异常")


def check_b8():
    """DBC-05：不支持的特性必须报清晰错误，且错误里指认到具体行。"""
    root = os.path.dirname(os.path.abspath(__file__))
    path = os.path.join(root, "syn_dbc", "syn_mux.dbc")
    try:
        dbc(path)
        note("B8 多路复用信号必须报清晰错误", False, "解析竟然成功了（静默丢信号风险）")
        return
    except Exception as e:
        msg = str(e)
        ok = ("multiplexed" in msg) and ("syn_mux.dbc" in msg)
        note("B8 多路复用信号必须报清晰错误", ok, "异常：%s" % msg[:120])


def main():
    msgs = parse_syn()
    check_b1_b4(msgs)
    check_b5_b6()
    check_b7()
    check_b8()

    fails = 0
    for name, ok, detail in results:
        mark = "PASS" if ok else "FAIL"
        if not ok:
            fails += 1
        print("[%s] %-44s %s" % (mark, name, "" if ok else detail))

    print("-" * 70)
    print("%d/%d PASS" % (len(results) - fails, len(results)))
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
