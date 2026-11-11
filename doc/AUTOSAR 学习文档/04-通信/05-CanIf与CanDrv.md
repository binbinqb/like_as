---
title: CanIf 与 CanDrv
aliases: [CanIf, Can Driver, CAN驱动, CAN接口]
tags: [通信, 驱动]
source: [SWS_CANInterface, SWS_CANDriver]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# CanIf 与 CanDrv

> [!tip] 结论
> Can 操作控制器硬件，CanIf 管理控制器／PDU 抽象及规定缓冲与通知。必须区分“Can_Write 已复制并受理请求”与“总线发送得到确认”，尤其不能错误延长或缩短缓冲区生命周期。

## 一、资源和标识

| 对象 | 含义 |
|---|---|
| Controller | CAN 控制器实例 |
| Hardware Object / HOH | 硬件收发对象及其抽象句柄 |
| HTH / HRH | 发送／接收硬件句柄 |
| CanIf PDU ID | CanIf 配置中的逻辑对象标识，不等于 CAN ID |
| CAN ID | 总线仲裁标识，需区分标准／扩展格式 |

BasicCAN／FullCAN、一个句柄对应多个硬件对象等取决于配置与硬件能力，不能用“FullCAN 没有软件开销”概括。

## 二、Can_Write 的真实缓冲合同

`[SWS_Can_00011]` 要求驱动直接复制上层缓冲数据，**上层只需在 Can_Write 函数返回前保持该缓冲一致**。它没有要求调用者一律持有原始 SDU 到 TxConfirmation。

`[SWS_Can_00212]` 描述可用硬件对象时，将 ID、长度、SDU 复制到适当硬件寄存器／缓冲并发起传输，返回 E_OK。

因此，局部栈缓冲并不因为总线发送异步就天然非法；是否可使用，取决于当前调用边界的复制／引用合同。自定义 SDK 的 DMA 异步 API 可能另有要求，不能拿它替代 Can_Write 的规范语义。

其他层例如 CanIf、PduR、TP 的缓冲和 triggered transmission 各有合同，应逐层核对。不能把一个“静态缓冲直到确认才复用”规则套到所有 API。

## 三、发送与确认

```text
LSduR → CanIf_Transmit → Can_Write
                           ↓ 请求受理并返回
                      硬件实际发送
                           ↓
              CanIf_TxConfirmation → 上层规定通知
```

E_OK 不表示帧已在总线上成功发送，更不表示对端应用已经处理。CAN_BUSY 等结果须按 CanIf 缓冲配置或调用方策略处理，不能默认为无限排队。

CanIf 的缓冲、PDU 模式和确认行为需查规范与配置，不能将 Direct／Single／FIFO 当成所有实现统一提供的三个标准模式。

## 四、接收与过滤

驱动通过规定的 `CanIf_RxIndication` 回调交付硬件接收信息；CanIf 进行配置要求的处理，并向 LSduR 等本版本规定上层交付。

硬件 mask 的极性、范围过滤能力、FIFO／mailbox 支持和 CAN FD 长度全部查 MCU 手册。不能假设所有控制器“mask=0 就全通”或“RX mailbox 只支持标准帧”。

**当前没有已核实的 DBC、MCU CAN 控制器限制及 49 条报文统计。** 原笔记中的这些说法不作为项目选型依据。如果某硬件接收对象无法接收扩展帧，软件过滤不能让该对象接收本来被硬件丢弃的帧，需换用受支持的硬件对象／模式或方案。

## 五、优先级与错误恢复

总线仲裁优先级和节点内部发送对象调度共同影响响应。Multiplexed transmission、硬件按 ID 选择和 CanIf 缓冲策略需结合分析；不能只凭邮箱数量判断最坏延迟。

Bus-Off 事件上报与恢复策略需要驱动、CanIf、CanSM／自建状态管理配合。控制器状态、收发器状态、PDU 收发模式和 ComM 通信模式是不同状态机。

## 六、验收

验证标准／扩展 ID、过滤边界、缓冲忙、发送确认、接收突发、轮询／中断模式、Bus-Off、睡眠唤醒、并发与数据生命周期。不要在无数据时把某 MCU 限制写成项目事实。

## 七、自检

1. Can_Write 返回前与 TxConfirmation 前，需要分别保留哪些数据？
2. CAN ID 与 PDU ID 有何区别？
3. 软件过滤为什么不能弥补完全不支持某帧格式的硬件对象？

## 核对依据

- [SWS_CANDriver，PDF 第 41 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANDriver.pdf#page=41)：[SWS_Can_00011] 缓冲保持到 Can_Write 返回
- [SWS_CANDriver，PDF 第 74 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANDriver.pdf#page=74)：Can_Write 及 [SWS_Can_00212]
- [SWS_CANInterface，PDF 第 41 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANInterface.pdf#page=41)：发送路径与 LSduR 相关回调
- [SWS_CANInterface，PDF 第 52 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANInterface.pdf#page=52)：并发与缓冲一致性

---

**上一篇** → [[04-PduR路由]]
**下一篇** → [[06-CanTp传输协议]]
**相关** → [[02-MCAL微控制器抽象层]]
**返回** → [[AUTOSAR知识地图]]
