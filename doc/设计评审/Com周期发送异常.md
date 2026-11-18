# Com 周期报文不上总线（M10 五项失败）排查记录

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：已定位到 Com 发送入口，根因待验证
>
> **结论前置**：`Com_MainFunctionTx()` 每拍都在跑、周期定时器在递减，但 `PduR_ComTransmit()`
> 对 0x200 持续返回失败（`bTxRetry=1`），总线上几乎无帧。**该现象在本次 PduR 改动之前的
> HEAD 构建上同样复现**，属既有缺陷，与 PduR 路径删除无关。

## 1 现象（2026-11-18 实测，AppB 槽）

| 观察 | 数值 |
|---|---|
| 总线 0x200 | 5 s 采样 **0 帧**（刚复位后也一样） |
| 总线 0x500（NM） | 3 s 采样 1 帧（预期 200 ms 周期） |
| `com` 的 tx cnt | 10 s 内 +108（≈100 ms/次，**ComApp_Tick 正常**） |
| `com can1` | 6 条全 `retry=1` |
| `nm` | `cannm=NORMAL_OPERATION(4) mode=NETWORK(3)`，组是开的 |
| `can counters` | CAN0/CAN1 RX `total=0`（诊断帧到达时才增） |
| 诊断 | `10 02` → `50 02`，**8 ms**，收发均正常 |

## 2 A/B 对照（关键证据）

| 步骤 | 结果 |
|---|---|
| 用 HEAD（未含本次 PduR 改动）编 App，UDS 刷 A 槽，复位后立刻采样 | 8 s 内 0x200 **1 帧** —— 与改动版一致 |
| 恢复改动编 AppB，刷 B 槽，复位后采样 | 5 s 内 0x200 **0 帧** |

两个版本行为一致 → **排除"删死路径导致路由断裂"**。另：M3 诊断 18/18
（含多帧 TX/RX），说明 PduR 的诊断 4 条路径完好。

## 3 已排除项

| 假设 | 排除依据 |
|---|---|
| 时基/主循环变慢 | `com` 的 tx cnt 10 s +108 → 主循环 9.3 ms/拍；`mem` 报 `tick late 0.8 µs` |
| NM 未进网络模式、Com 组未启动 | `nm` 报 `mode=NETWORK`；`com` 报 `grp=1`；ComM 表里 CAN1(0) 与 CANTEST(1) 两组都在启动列表 |
| 配置编号错位 | `CANIF_TX_COM_TEST=5` ↔ HTH5 = `{CAN0, mb13, 0x200}` ↔ `Com_Cfg.c` 的 `PDUR_CANTEST_TX_TEST` 一致；`check-pdu` PASS |
| 本次 PduR 改动 | 见 §2 A/B 对照 |
| CAN0 硬件/收发器 | 诊断请求 8 ms 内正常应答（同一控制器、同一 Kvaser） |

## 4 未验证假设（下一步按序做）

1. **`Can_Write(HTH5)` 恒返回 `CAN_BUSY`**：0x200 的邮箱从没被释放。
   查法：`can matrix`（走各自 HTH 发 6 帧）与 `can burst`（走 HTH0）分别验证
   非 Com 路径能否发出；再读 CAN0 的 `TSR/TEC/REC`（`can regs`）看 mb13 的
   `TXRQ` 是否挂住。
2. **TX 确认回调未回收 CAN0 的 Com 邮箱**：诊断 0x7E8 用的是 HTH3，能正常复用，
   说明确认链路整体可用；但 Com 的 6 个 CAN0/CAN1 邮箱是否收到确认需单独确认
   （可在 `CanIf_TxConfirmation` 加一次性计数或用 `can counters` 扩展）。
3. **CAN1 无对端的连带影响**：6 条 CAN1 报文 `retry=1` 在台架上是**预期行为**
   （无节点 ACK，硬件无限重发 → 邮箱长期占用）。它不解释 0x200 在 CAN0 上不出，
   但会让 `Com_MainFunction_Fast` 每拍空转 6 次，排障时要先把它区分开。

## 5 影响与范围

- M10 的 22 项里 5 项失败（周期、抖动、计数步进、恢复帧率、NM 帧率），
  其余 17 项（打包/解包/超时/分组/回归）**PASS** —— 即 Com 的位布局与信号层是对的，
  纯发送调度链路有问题。
- 与 PduR 02.6 收口无关；该缺陷归 Com 模块任务"验证周期、错相、事件、重试"。
- 台架条件：Kvaser ch0 接 CAN0（诊断正常证明物理链路与 ACK 均有效），
  CAN1 无第二节点。
