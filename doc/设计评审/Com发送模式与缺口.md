# Com 发送语义：周期 / 错相 / 事件 / 重试 四项结论

> **编写**：binbina ｜ **日期**：2026-11-18 ｜ **状态**：两项实测通过、两项判定"本版不支持，记录差异"
>
> **结论前置**：这一版 Com **只支持周期发送**。`Com_IPduTxConfigType` 里只有
> `FirstTime` / `CycleTime` / `TxPduId`，既没有 AUTOSAR 的 `TimeOffset`
> （每周期相位），也没有事件型发送模式。四项验收因此分成两类：
> **周期 ✅ 22/22、重试 ✅ 5/5**；**错相 → 仅"启动相位"（FirstTime）、事件型 → 不适用**，
> 按 roadmap 的惯例记差异，不扩上游（与 LSduR 的处理方式一致）。

## 1 代码事实（`infras/communication/Com/Com_Priv.h` / `Com.c`）

`Com_IPduTxConfigType` 的**全部**字段：

| 字段 | 作用 | 代码位置 |
|---|---|---|
| `context` | 运行期 timer / bTxRetry | `Com_Priv.h:160` |
| `ErrorNotification` / `TxNotification` / `TxIpduCallout` | 三个可选回调（本工程未开） | `Com_Priv.h:162-169` |
| `FirstTime` | **启动分组时**的首次装填值 | `Com.c:419-423` |
| `CycleTime` | 周期（以 10 ms 主函数拍计） | `Com.c:865` |
| `TxPduId` | PduR 路径号 | `Com.c:863` |

由此可得三条硬结论：

1. **没有 `TimeOffset`**：每次发送成功后统一 `timer = CycleTime`（`Com.c:865`），
   不存在"每周期固定相位偏移"的字段；`FirstTime` 只在 `Com_IpduGroupStart(id, TRUE)`
   时生效一次（`Com.c:419`），语义是"首帧延后"，不是"相位"。
2. **没有事件型发送**：`Com_SendSignal()` 只写 PDU 缓冲并置 update bit
   （`Com.c:174-198`），**从不触发发送**；发送唯一入口是 `Com_MainFunctionTx()`
   的 timer 到期分支。`COM_USE_SIGNAL_UPDATE_BIT` 的作用是 RX 侧"是否有新值"
   与发送后清位（`Com.c:210-219`），与事件发送无关。
3. **重试是内建的**：`PduR_ComTransmit` 失败 → `timer=CycleTime; bTxRetry=TRUE`
   （`Com.c:869-872`），由 `Com_MainFunction_Fast()` 每拍推进（`Com.c:889-920`）。

## 2 四项验收结果

| 项 | 状态 | 判据 / 证据 |
|---|---|---|
| **周期** | ✅ PASS | `m10_check.py` 22/22：0x200 间隔 100.0/100.1 ms（62 帧/6 s，抖动 ≤1 ms），0x500 199.9~200.2 ms，计数每帧 +1 |
| **重试** | ✅ PASS | `tools/com_retry_check.py` 5/5：`can ctrl stop` 期间 0 帧；`start` 后首帧 ≤0.5 s；恢复后 10.5 帧/s；计数器 min=1 / max=21（停用期间时间照走） |
| **错相** | ⚠ 不适用 | 本版只有 `FirstTime` 启动相位；当前矩阵里**没有同周期报文对**（CAN1 为 5/10/20/100 拍，CAN0 只有 0x200/0x500 两个不同周期），构造不出错相场景。若将来出现两条同周期报文且要求均分总线，需要扩 `TimeOffset` |
| **事件型** | ⚠ 不适用 | 本版无事件发送模式；Foton L1 矩阵全部为周期报文，本期无需求 |

## 3 判定（与 R25-11 / LSduR 同一处理方式）

- **不扩上游**：加 `TimeOffset` 与 `TxMode` 要同时改 `Com_Priv.h` 结构、
  `Com.c` 的主函数分支、`tools/generator/Com.py` 的字段输出，并重跑
  67 项对账与上板回归 —— 收益为零（当前没有需求场景），成本明显。
- **记录差异**：本工程相对 AUTOSAR COM 的发送能力缺 `TimeOffset` 与事件模式。
  一旦出现"同周期多报文"或"变化即发"的需求，按独立任务做，不要临时打补丁。
- **验收入口固定**：周期 = `m10_check.py`；重试 = `com_retry_check.py`；
  两者都已入 tools，可进回归集。

## 4 重试用例的两个台架陷阱（实测踩到）

1. **`can ctrl start` 后 CanIf 队列会先吐旧帧**：停用期间 `CanIf_Transmit`
   仍可能受理并排队，恢复瞬间先发出**停用前的旧值**（实测首帧 cnt=132，
   第二帧才是当前值 153）。所以"恢复是否正确"不能看首帧计数器，
   要看**增量分布**：正常稳态 min=1，停用跳变 max≥5。
2. **速率必须按帧时间戳算**：用墙钟窗口会把积压帧算进去，速率被算高
   （首版脚本因此误报 R4 FAIL，26 帧/2 s 实为 10.5 帧/s）。
