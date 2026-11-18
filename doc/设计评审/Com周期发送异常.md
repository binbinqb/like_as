# Com 周期报文不上总线（M10 五项失败）排查记录

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：**根因已定位并修复，M10 22/22**
>
> **结论前置**：`Can.json` 里 mb11（0x500 NM_TX）与 mb13（0x200 COM_TX）的
> `intEnable` 被设成 `false`。TX 完成中断是 `CanAc.c` 里 `s_txPending[]` 的**唯一**
> 释放点，关掉之后每个邮箱只能发出**第一帧**，之后 `Can_Write()` 永远返回
> `CAN_BUSY`，上层表现为"周期报文不发、`bTxRetry` 恒为 1"。改成 `true` 后
> 0x200 = 100.0 ms、0x500 = 200.0 ms，M10 由 17/22 升到 **22/22**。

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

## 6 根因（2026-11-18 定位）

### 6.1 决定性实验

| 实验 | 结果 | 推论 |
|---|---|---|
| `can burst 5`（走 HTH0 / mb0） | 0x123 五帧全部发出 | `Can_Write` 本身正常 |
| 紧接 burst 后监听 | 0x200 **只出 1 帧**，之后 12 s 无帧 | Com 的邮箱卡死后不再释放 |
| `com` 的 tx cnt（10 s） | +109 → 主循环 **9.2 ms/拍** | 主循环与 Com 定时器正常 |
| `10 02`（走 mb4 / HTH3） | 8 ms 正常应答，可反复多帧 | 诊断邮箱能反复复用 |

### 6.2 代码链

1. `CanAc.c` 的 `Can_Write()`：受理后置 `s_txPending[ctl][i] = true`；
   若该位已为 true，直接 `return CAN_BUSY`（防覆盖上一帧数据与句柄）。
2. 清除点**只有两处**：TX 完成中断（`CanAc.c:481` → 清位 + `CanIf_TxConfirmation()`）
   与 bus-off 兜底。
3. 中断是否打开由 `CanHw_MsgCfgType.intEnable` 决定（`CanAc_Init` 只对 true 的邮箱开）。
4. `Can_Cfg.c` 的 mb11 / mb13 该字段是 **false** → 第一帧发出后标志永不清 →
   之后每次 `Can_Write` 都 BUSY → `PduR_ComTransmit` 失败 → Com 的
   `timer` 重装 + `bTxRetry=TRUE`，表现为周期报文"消失"、`retry=1`。

### 6.3 为什么以前没被发现

mb0（0x123）与 mb4（0x7E8）是 `true`，所以 **CAN 驱动自测与诊断这两条最常跑的路
一直是好的**；出问题的恰好是"按周期发"的 NM 与 Com —— 而它们只有做 M9/M10 的
周期断言时才会暴露，只测"能发一帧"是看不出来的。

## 7 修复与验证

| 项 | 内容 |
|---|---|
| 配置源 | `config/Can/Can.json`：NM_TX、COM_TX 的 `int` 改 `true`，note 写明"必须为 true"的理由 |
| 生成物 | `tools/sync_can.py` 重生成 `Can_Cfg.c`（两行由 false → true），`text` 尺寸不变 |
| 注释 | `Can_HwCfg.h` 的 `intEnable` 说明改写：删掉"NM/Com 两条例外"（那句话把缺陷写成了设计），补上症状与教训 |
| 实测 | 0x200 **100.0 / 100.1 ms**（62 帧/6 s）；0x500 **199.9~200.2 ms**（32 帧/6 s） |
| 验收 | **M10 22/22**（周期 100.1 ms、抖动 min 100/max 101、计数 deltas 全 1）；**M3 18/18** |
| 未变 | CAN1 六条真实报文 `retry=1` 属台架无对端（无 ACK），与本缺陷无关 |

