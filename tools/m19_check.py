# -*- coding: utf-8 -*-
"""
M19 验收：CAN1 真实通信矩阵（Foton L1）的接收链路。

## 验的是什么

不是"某条报文能收到"，而是**三层同时正确**：

  | 层 | 判据 | 错了会怎样 |
  |----|------|-----------|
  | 硬件邮箱 | `!k` 的 mb 计数 = 注入数 | PF 段掩码没放行 → 该 PF 下**所有**报文都收不到 |
  | 软件过滤 | `!k` 的 pdu 计数 = 邮箱计数 | canid/mask 配错或表序乱 → 投到别的 PDU 或被丢弃 |
  | 分组正确 | 每个 PDU 落到它自己的 PF 段邮箱 | 掩码重叠 → 被"编号最小的匹配邮箱"截走 |

## 为什么必须两套计数都看

只验一套时，三类错全都看不出来：

  | 现象 | 含义 |
  |------|------|
  | 邮箱涨、PDU 不涨 | CanIf 过滤表把帧丢了（canid/mask/顺序错） |
  | 邮箱涨、PDU 涨在**别的项** | 过滤表区间重叠，被前一项截走 |
  | 两套都不涨 | 硬件掩码没放行（PF 段或优先级位错） |

## 用法

    python tools/m19_check.py                 # 逐条 5 帧，全部 34 条
    python tools/m19_check.py --per-msg 20    # 每条 20 帧（压一压中断）
    python tools/m19_check.py --channel 1     # Kvaser 通道（默认 1 = CAN1）

@author binbina
"""

import argparse
import io
import os
import re
import sys
import time

# ── 旧 `!x` → 新 shell 命令（M-Shell 迁移；旧兼容桥已删）─────────────
CMD_MAP = {
	'!k': 'can counters',
	'!K': 'can counters clear',
	'!M': 'can matrix',
	'!e': 'can regs',
}


def xlate(cmd):
	"""旧单字符命令翻译成新命令；其它原样透传。保证以换行结尾。"""
	c = CMD_MAP.get(cmd.strip(), cmd.strip())
	if not c.endswith("\n"):
		c += "\n"
	return c



import can
import serial

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
HDR = os.path.join(ROOT, "app", "platform", "cvm0146", "src", "config", "CanIf_Cfg.h")

# PF → 硬件邮箱号（与 Can_Cfg.c 的 CanHw_MsgCfgs1[] 一致）
PF_TO_MB = {0xEB: 8, 0xEC: 9, 0xEE: 10, 0xF0: 11, 0xFD: 12, 0xFE: 13, 0xFF: 14}

# Kvaser 的发送缓冲溢出抛 CANLIBOperationError（基类 CanlibError，不是 can.CanError）
TRANSIENT = (can.CanError,)
try:
    from can.interfaces.kvaser.canlib import CanlibError
    TRANSIENT = TRANSIENT + (CanlibError,)
except Exception:
    pass


def load_cases():
    """从头文件解析 CAN1 的 34 条用例。"""
    s = io.open(HDR, encoding="utf-8").read()
    rows = []
    for m in re.finditer(
            r"^#define CANIF_RX_CAN1_(\w+)\s+\((\d+)u\)\s+/\*\*< (0x[0-9A-F]+) \*/$", s, re.M):
        name, pdu, cid = m.group(1), int(m.group(2)), int(m.group(3), 16)
        # 头文件里的值来自 DBC，带 bit31 扩展帧标志；python-can 要的是纯 29 位 ID
        cid &= 0x1FFFFFFF
        pf = (cid >> 16) & 0xFF
        mb = PF_TO_MB.get(pf)
        if mb is None:
            raise SystemExit("0x%08X 的 PF=0x%02X 不在分组表里" % (cid, pf))
        rows.append({"name": name, "pdu": pdu, "canid": cid, "pf": pf, "mb": mb})
    rows.sort(key=lambda x: x["pdu"])
    if len(rows) != 34:
        raise SystemExit("解析出 %d 条，期望 34 条" % len(rows))
    return rows


class Dut(object):
    def __init__(self, port, baud, channel, bitrate):
        self.ser = serial.Serial(port, baud, timeout=0.2)
        self.ser.reset_input_buffer()
        self.bus = can.Bus(interface="kvaser", channel=channel, bitrate=bitrate)
        self.tx = 0

    def cmd(self, text, wait=0.45):
        self.ser.reset_input_buffer()
        self.ser.write(xlate(text).encode())
        self.ser.flush()
        time.sleep(wait)
        return self.ser.read(65536).decode("utf-8", "replace")

    def counters(self):
        """返回 ({mb: n}, {pdu: n})。"""
        raw = self.cmd("!k")
        mb, pdu = {}, {}
        for line in raw.splitlines():
            line = line.strip()
            m = re.match(r"mb(\d+)\s*=\s*(\d+)", line)
            if m:
                mb[int(m.group(1))] = int(m.group(2))
                continue
            m = re.match(r"pdu\s+(\d+)\s*=\s*(\d+)", line)
            if m:
                pdu[int(m.group(1))] = int(m.group(2))
        return mb, pdu

    def reset(self):
        self.cmd("!K", 0.3)

    def send(self, canid, data=None):
        if data is None:
            data = bytes([0x5A] * 8)
        msg = can.Message(arbitration_id=canid, data=data,
                          is_extended_id=True, dlc=8)
        # Kvaser 溢出抛 CanlibError，只捕 can.CanError 时重试形同不存在
        for attempt in range(8):
            try:
                self.bus.send(msg)
                self.tx += 1
                return
            except TRANSIENT:
                if attempt == 7:
                    raise
                time.sleep(0.002 * (attempt + 1))

    def close(self):
        try:
            self.bus.shutdown()
        finally:
            self.ser.close()


def round_per_case(dut, cases, per_case):
    """逐条注入，验"邮箱计数 = PDU 计数 = 注入数"。"""
    print("  逐条注入 %d 帧/条，共 %d 条" % (per_case, len(cases)))
    dut.reset()
    base_mb, base_pdu = dut.counters()

    fails = []
    for c in cases:
        for _ in range(per_case):
            dut.send(c["canid"])
            time.sleep(0.004)
        time.sleep(0.12)

        mb, pdu = dut.counters()
        got_mb = mb.get(c["mb"], 0) - base_mb.get(c["mb"], 0)
        got_pdu = pdu.get(c["pdu"], 0) - base_pdu.get(c["pdu"], 0)
        ok = (got_mb == per_case) and (got_pdu == per_case)

        print("  %-46s PF=0x%02X mb%-2d pdu%-2d  tx=%-3d rx=%-3d/%-3d  %s"
              % (c["name"][:44], c["pf"], c["mb"], c["pdu"], per_case,
                 got_mb, got_pdu, "ok" if ok else "**FAIL**"))
        if not ok:
            fails.append("%s: 期望 %d，邮箱 %d / PDU %d"
                         % (c["name"], per_case, got_mb, got_pdu))
        base_mb, base_pdu = mb, pdu

    return fails


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="COM2")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--channel", type=int, default=1, help="Kvaser 通道（1=CAN1）")
    ap.add_argument("--bitrate", type=int, default=500000)
    ap.add_argument("--per-msg", type=int, default=5, help="每条报文注入帧数")
    ap.add_argument("--list", action="store_true", help="只列出用例，不发帧")
    a = ap.parse_args()

    cases = load_cases()
    print("CAN1 真实矩阵：%d 条，覆盖 %d 个 PF 段"
          % (len(cases), len(set(c["pf"] for c in cases))))
    if a.list:
        for c in cases:
            print("  pdu%-2d  0x%08X  PF=0x%02X  mb%-2d  %s"
                  % (c["pdu"], c["canid"], c["pf"], c["mb"], c["name"]))
        return 0

    dut = Dut(a.port, a.baud, a.channel, a.bitrate)
    try:
        print()
        fails = round_per_case(dut, cases, a.per_msg)
    finally:
        dut.close()

    print()
    print("=" * 78)
    if fails:
        print("FAIL %d / %d" % (len(fails), len(cases)))
        for f in fails:
            print("   ", f)
        return 1
    print("PASS %d / %d   （邮箱计数与 PDU 计数全部精确相等）" % (len(cases), len(cases)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
