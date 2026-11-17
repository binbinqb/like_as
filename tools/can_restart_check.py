#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CAN-01 / CAN-02 上板验收：反复启停 + 同邮箱重发 + 忙检查的正向证明。

## 验的是什么

| 用例 | 对应问题 | 判据 |
|------|---------|------|
| S1   | CAN-01 | 100 次 `can ctrl stop 0` / `start 0`，每次返回 OK |
| S2   | CAN-01 | 重启后 RX 存活：注入 0x201 ×20 → `can counters` 的 CAN0 total 增量 = 20 |
| S3   | CAN-01 | 重启后 TX 存活：`can auto on` → 总线看到 0x123（邮箱中断使能循环没坏）|
| S4   | CAN-01 | 通道 1 同样 100 次启停 + 注入 0x18FE4021 ×20 → CAN1 total 增量 = 20 |
| S5   | CAN-02 | 正向证明 CAN_BUSY：**无 ACK 源**（Kvaser 关闭）时 auto-tx 第一帧受理、
               后续全部被拒 → 串口出现 "CanIf_Transmit(heartbeat) failed"。
               修复前这里是静默覆盖邮箱，什么都不会打印 |
| S6   | CAN-02 | bus-off 释放占用：S5 会自然演进到 bus-off（TEC ≥256），
               恢复后 TX 仍能发出（占用标志没有死锁） |

## 为什么 S5 能证明 CAN_BUSY

无 ACK 时 FlexCAN 永远重发、TX 完成中断永不来 → 邮箱持续"占用"。
- 修复后：`Can_Write` 返回 CAN_BUSY → `CanIf_Transmit` 失败 → `CanTest_SendOne`
  打印 failed（每个 auto 周期一条）。
- 修复前：无条件覆盖邮箱与 s_txHandle，**一行日志都不会有**，同时 bus-off 前
  也没有任何可见差异。
所以"出现 failed 打印"就是 CAN_BUSY 路径被真实踩到的证据。

## 环境与已知坑

- 串口 COM2 115200；Kvaser ch0 = CAN0 @500k（0x201 探针、0x123 自测帧）、
  ch1 = CAN1 @500k（0x18FE4021 探针、`can matrix` 发送）。
- Kvaser 驱动跨进程缓存帧：每次统计 TX 前必须先 drain（连续静默 0.5 s），
  复用 a3_isolation_check 的教训。
- S5 会让 CAN0 进 bus-off 并向 Dem 记事件（落 NvM），属于预期副作用；
  S6 验证恢复后收发正常，之后建议复位一次再跑其他回归。

@author binbina
"""
import argparse
import re
import sys
import time

import can
import serial

ID_RX_PROBE0 = 0x201         # CAN0 接收邮箱（Com）
ID_RX_PROBE1 = 0x18FE4021    # CAN1 真实矩阵 RX（扩展帧）
ID_SELFTEST = 0x123          # CAN0 自测 TX（auto-tx）

results = []


def note(name, ok, detail=""):
    results.append((name, ok, detail))
    print("  [%s] %-40s %s" % ("PASS" if ok else "FAIL", name,
                               ("(%s)" % detail) if detail else ""))


class Rig:
    def __init__(self, a):
        self.ser = serial.Serial(a.port, a.baud, timeout=0.2)
        self.a = a
        self.bus0 = None
        self.bus1 = None

    def cmd(self, t, wait=0.35):
        self.ser.reset_input_buffer()
        self.ser.write((t + "\n").encode())
        self.ser.flush()
        time.sleep(wait)
        return self.ser.read(65536).decode("utf-8", "replace")

    def open_bus(self, which):
        if which == 0 and self.bus0 is None:
            self.bus0 = can.Bus(interface="kvaser", channel=self.a.ch0,
                                bitrate=self.a.bitrate)
        if which == 1 and self.bus1 is None:
            self.bus1 = can.Bus(interface="kvaser", channel=self.a.ch1,
                                bitrate=self.a.bitrate)

    def close_bus(self):
        for attr in ("bus0", "bus1"):
            b = getattr(self, attr)
            if b is not None:
                b.shutdown()
                setattr(self, attr, None)

    def drain(self, bus, quiet=0.5, cap=3.0):
        """连续 quiet 秒读不到帧才算排空（Kvaser 跨进程缓存，固定时长不可靠）。

        cap 是总时长上限：CAN1 上有周期业务帧（M23 灯状态），
        "连续静默"可能永远等不到 —— 那不是缓存没排空，是总线本来就忙。
        超过 cap 就当排空结束，靠后续的计数窗口兜底。
        """
        start = time.time()
        bus.flush_tx_buffer()
        last_rx = time.time()
        while (time.time() - start < cap) and (time.time() - last_rx < quiet):
            if bus.recv(timeout=0.05) is not None:
                last_rx = time.time()

    def inject(self, bus, arbId, n, ext):
        msg = can.Message(arbitration_id=arbId, data=bytes(range(8)),
                          is_extended_id=ext, dlc=8)
        for _ in range(n):
            try:
                bus.send(msg)
            except can.CanError:
                pass
            time.sleep(0.02)

    def rx_total(self, ch):
        out = self.cmd("can counters")
        m = re.search(r"CAN%u\s+total=(\d+)" % ch, out) or \
            re.search(r"CAN%d\s+total=(\d+)" % ch, out)
        return int(m.group(1)) if m else None

    def count_tx(self, bus, arbId, seconds):
        n = 0
        end = time.time() + seconds
        while time.time() < end:
            f = bus.recv(timeout=0.1)
            if f is not None and f.arbitration_id == arbId:
                n += 1
        return n


def stop_start(rig, ch, cycles):
    bad = 0
    for i in range(cycles):
        for v in ("stop", "start"):
            out = rig.cmd("can ctrl %s %u" % (v, ch), 0.18)
            if "<+0" not in out:
                bad += 1
                if bad <= 3:
                    print("    第 %u 次轮 %s 返回异常：%r" % (i + 1, v, out[-80:]))
    return bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="COM2")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--ch0", type=int, default=0)
    ap.add_argument("--ch1", type=int, default=1)
    ap.add_argument("--bitrate", type=int, default=500000)
    ap.add_argument("--cycles", type=int, default=100)
    a = ap.parse_args()

    rig = Rig(a)

    print("== S1/S2/S3：CAN0 通道 %u 次启停 + 收发存活 ==" % a.cycles)
    bad = stop_start(rig, 0, a.cycles)
    note("S1a CAN0 %u 次 stop/start 全部返回 OK" % a.cycles, bad == 0,
         "%u 次异常" % bad)

    rig.open_bus(0)
    rig.drain(rig.bus0)
    b0 = rig.rx_total(0)
    rig.inject(rig.bus0, ID_RX_PROBE0, 20, ext=False)
    time.sleep(0.4)
    d0 = rig.rx_total(0)
    ok = (b0 is not None and d0 is not None and d0 - b0 == 20)
    note("S2 重启后 CAN0 RX 存活（+20）", ok,
         "total %s → %s" % (b0, d0))

    rig.drain(rig.bus0)
    rig.cmd("can auto on", 0.3)
    n123 = rig.count_tx(rig.bus0, ID_SELFTEST, 2.0)
    rig.cmd("can auto off", 0.3)
    # auto-tx 周期约 300 ms（实测 2 s ≈ 6 帧），判"活着"用 ≥4，不要按 10 ms 算
    note("S3 重启后 CAN0 TX 存活（2 s 内 0x123 = %u）" % n123, n123 >= 4)

    print("== S4：CAN1 通道 %u 次启停 + 收发存活 ==" % a.cycles)
    bad = stop_start(rig, 1, a.cycles)
    note("S4a CAN1 %u 次 stop/start 全部返回 OK" % a.cycles, bad == 0,
         "%u 次异常" % bad)

    rig.open_bus(1)
    rig.drain(rig.bus1)
    b1 = rig.rx_total(1)
    rig.inject(rig.bus1, ID_RX_PROBE1, 20, ext=True)
    time.sleep(0.4)
    d1 = rig.rx_total(1)
    ok = (b1 is not None and d1 is not None and d1 - b1 == 20)
    note("S4b 重启后 CAN1 RX 存活（+20）", ok, "total %s → %s" % (b1, d1))

    rig.drain(rig.bus1)
    rig.cmd("can matrix", 0.8)
    nmat = 0
    end = time.time() + 1.0
    while time.time() < end:
        f = rig.bus1.recv(timeout=0.1)
        if f is not None:
            nmat += 1
    note("S4c 重启后 CAN1 TX 存活（matrix 后 1 s 收到 %u 帧）" % nmat, nmat >= 5)

    print("== S5/S6：CAN-02 无 ACK 正向证明（此段关闭 Kvaser）==")
    rig.close_bus()
    time.sleep(0.3)
    out = rig.cmd("can auto on", 2.5)
    nfail = out.count("CanIf_Transmit(heartbeat) failed")
    note("S5 无 ACK 时第二帧起被 CAN_BUSY 拒绝（failed 打印 x%u）" % nfail,
         nfail >= 2, "修复前这里一行都不会打印")
    out = rig.cmd("can auto off", 0.3)
    note("S5b auto 已关", "auto-tx: OFF" in out, out[-120:])

    # S6：bus-off 之后占用标志必须被释放 —— 重新挂上 ACK 源，TX 应能恢复
    rig.open_bus(0)
    rig.drain(rig.bus0)
    time.sleep(0.5)   # 等 bus-off 自动恢复（128×11 隐性位）
    rig.cmd("can auto on", 0.5)
    n123b = rig.count_tx(rig.bus0, ID_SELFTEST, 1.5)
    rig.cmd("can auto off", 0.3)
    note("S6 bus-off 恢复后 TX 存活（1.5 s 内 0x123 = %u）" % n123b, n123b >= 3,
         "占用标志若没被 bus-off 清掉，这里会是 0")

    rig.close_bus()
    fails = sum(1 for _, ok, _ in results if not ok)
    print("-" * 70)
    print("%d/%d PASS" % (len(results) - fails, len(results)))
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
