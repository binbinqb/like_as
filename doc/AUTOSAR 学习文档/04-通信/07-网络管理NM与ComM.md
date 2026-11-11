---
title: 网络管理 NM 与 ComM
aliases: [NM, Network Management, ComM, 网络管理, 睡眠协调]
tags: [通信, 机制]
source: [SWS_COMManager, SWS_CANNetworkManagement, SWS_NetworkManagementInterface]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# 网络管理 NM 与 ComM

> [!tip] 结论
> ComM 仲裁本 ECU 的通信需求，Nm 提供网络管理接口，CanNm 等实现总线相关网络管理，CanSM 等管理总线状态。它们与 EcuM/BswM 协调，但不是一个无条件“取最高请求就立即进入 FULL”的计数器。

## 一、ComM 的对象与模式

配置的 User、Channel 和 PNC 表达需求关联。NO_COMMUNICATION、SILENT_COMMUNICATION、FULL_COMMUNICATION 是不同通信模式；用户请求允许的模式不等于通道内部全部状态集合。

No Communication 不意味着硬件完全失去所有唤醒检测；Silent 的支持及行为也依总线类型与配置决定。通信允许、抑制、诊断活跃、唤醒、Nm variant 等会影响状态迁移。

Dcm 有诊断活跃相关接口，NM 有状态／请求回调，不能画成它们都作为普通 User 直接调用同一个 RequestComMode(FULL)。

## 二、典型职责链

```text
用户通信需求、诊断活跃、网络与唤醒状态
                  ↓
                ComM
          ↙                 ↘
      Nm / CanNm           CanSM
      网络管理协议         总线模式／Bus-Off 等
          ↘                 ↙
        BswM / EcuM 协调 ECU 模式与低功耗
```

R25-11 的通信数据路径包含 LSduR，不能继续将所有 NM PDU 固定画成 CanNm→CanIf 直接调用，也不能使用 Com I-PDU Group 代替 NM 控制。

## 三、CanNm 状态与接收行为

Bus-Sleep、Prepare Bus-Sleep、Network Mode 及其 Repeat Message、Normal Operation、Ready Sleep 等状态按 SWS 状态机执行。

Ready Sleep 收到 NM 报文可能重置相应超时；**不是任意收到 NM 就无条件跳回 Normal Operation**。本地网络请求、重复报文请求等触发要分开看。

NM 使用协议和定时器实现协调，不是所有节点逐一“投票同意”，也不保证全网同时睡眠；部分网络、被动节点和协调网络还需检查相应规则。

## 四、定时器不要混淆

| 参数 | 核心作用 |
|---|---|
| CanNmMsgCycleTime | NM 周期发送相关时间 |
| CanNmTimeoutTime | NM 网络超时相关机制 |
| CanNmMsgTimeoutTime | NM 发送确认超时相关机制，不是多久未收到对方 |
| CanNmRepeatMessageTime | Repeat Message 阶段相关时间 |
| CanNmWaitBusSleepTime | Prepare Bus-Sleep 等待时间 |

不能统一规定 `WaitBusSleepTime > MsgTimeoutTime > MsgCycleTime`；参数间约束应按相应状态机、网络规范和配置条件核对。

## 五、网络睡眠不等于 ECU 可以立即休眠

还要检查本地输出、存储作业、诊断控制权、保持请求、唤醒源、供电和外设状态。设置唤醒源与最后一次请求检查之间的竞态必须覆盖。

PNC 是功能通信关联概念，选择性唤醒依赖收发器、网络和配置支持，不能仅靠软件划 PNC 就保证只唤醒特定 ECU。

## 六、BCM 自建方案

是否使用 AUTOSAR CanNm、J1939 地址管理或 OEM 自定义休眠协议，以通信规范为准。即使不采用完整 ComM 模块，也要保留通信需求、抑制、诊断和睡眠的明确协调机制。

## 七、自检

1. User 请求与 Channel 实际模式为何可能不同？
2. CanNmMsgTimeoutTime 和 CanNmTimeoutTime 有何区别？
3. Ready Sleep 收到 NM 为什么不必无条件回 Normal？

## 核对依据

- [SWS_COMManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COMManager.pdf)：User、Channel、请求、抑制、诊断与模式
- [SWS_CANNetworkManagement](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANNetworkManagement.pdf)：状态迁移与 NM 定时器
- [SWS_CANStateManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANStateManager.pdf)：总线状态与 Bus-Off 恢复
- [SWS_LSduRouter，PDF 第 7 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_LSduRouter.pdf#page=7)：NM 等模块与下层接口的连接

---

**上一篇** → [[06-CanTp传输协议]]
**下一篇** → [[08-通信矩阵与DBC]]
**相关** → [[02-模式管理EcuM与BswM]]
**返回** → [[AUTOSAR知识地图]]
