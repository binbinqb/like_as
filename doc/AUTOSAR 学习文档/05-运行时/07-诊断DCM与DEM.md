---
title: 诊断 DCM 与 DEM
aliases: [Dcm, Dem, UDS, 诊断, 故障管理]
tags: [机制, 核心]
source: [SWS_DiagnosticCommunicationManager, SWS_DiagnosticEventManager]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# 诊断 DCM 与 DEM

> [!tip] 结论
> Dcm 管诊断协议与服务处理，Dem 管事件／DTC 状态和记录，NvM 提供持久化。UDS 定义服务语义，具体 DID、DTC、例程、权限和时序仍由产品诊断规范约束。

## 一、职责边界

| 模块 | 负责 | 不替代 |
|---|---|---|
| Dcm | 协议处理、会话／访问检查、服务分发、时序、异步上下文 | 业务检测、硬件扫描、存储底层 |
| Dem | Event 状态、去抖、操作周期、DTC、冻结帧、扩展数据、存储协调 | UDS 传输和任意业务控制 |
| NvM | 逻辑块作业与持久化 | DTC 状态语义 |
| CanTp | CAN 上的诊断消息传输 | UDS 服务与 P2/P2* |

DSL／DSD／DSP 可以帮助理解 Dcm 的职责组织；不要由此强制规定实现一定拆成三个源文件。

## 二、事件与 DTC

监控报告 EventId 与检测结果，经内部或 Dem 配置去抖产生 FAILED/PASSED。事件与 DTC 的关联按配置，可涉及多个事件组合到 DTC，不能固定成一对一。

| 状态位 | 含义 |
|---|---|
| bit0 testFailed | 当前相关测试失败状态 |
| bit1 testFailedThisOperationCycle | 本操作周期出现过失败 |
| bit2 pendingDTC | 按规定设置／清除的 pending 状态，不能简单等同“去抖未成熟” |
| bit3 confirmedDTC | 按确认条件达到 confirmed |
| bit4 testNotCompletedSinceLastClear | 清除后尚未完成测试 |
| bit5 testFailedSinceLastClear | 清除后曾失败 |
| bit6 testNotCompletedThisOperationCycle | 本周期尚未完成测试 |
| bit7 warningIndicatorRequested | 警告指示请求 |

去抖、确认、恢复、老化和清码是不同过程。0x19 按其子功能、状态掩码、记录编号等选择数据，不是只有 confirmedDTC 才能读。

## 三、DTC 与 NVM

```text
检测 → Event → Dem 状态与记录 → RAM 工作数据
                                ↓ 持久化触发与策略
                              NvM → 存储后端
UDS 0x19 → Dcm → Dem 查询状态／记录
UDS 0x14 → Dcm → Dem 清除并协调 NV 一致性
```

冻结帧在配置触发时捕获，不是诊断读取时重新取当前值。清除的正响应时点必须结合 `DemClearDTCBehavior` 和持久化结果定义，避免清除后立即掉电导致记录复现。

快照是否必需、保存哪些数据和次数由诊断需求决定；不能说“没有快照就没有诊断”。

## 四、实时 DID 与下线测试

数字量、ADC、HSD 电流／温度／故障位通常读 RAM 采样缓存，检查值、有效性、采样时间和序号。读 DID 不需要先写 NVM。

诊断传输可能分多次取数，响应快照必须在本次事务中保持一致，不能让后台刷新导致一份响应前后来自不同采样。缓冲的容量、并发请求和超时均需有界。

需要新采样时向采集服务请求刷新，异步等待完成；不能在 Dcm 中自行切换 MUX 破坏正常扫描。

| 操作 | 常用服务 | 需要定义 |
|---|---|---|
| 读实时／标识数据 | 0x22 | DID、格式、单位、有效性、权限 |
| 写编码／参数 | 0x2E | 校验、提交、持久化时点、失败响应 |
| 控制输出 | 0x2F（若产品定义） | 控制权、参数、保护、超时、归还控制 |
| 执行下线流程 | 0x31 | RID、开始／停止／查结果、异步状态 |

不是所有测试都必须使用同一个服务，必须匹配 OEM 诊断合同。

## 五、输出仲裁

业务请求、诊断请求和系统状态共同进入输出仲裁，硬件保护限制最终动作。诊断控制权在归还、会话切换、S3 超时、复位或规定故障时释放，具体规则需定义并测试。

明确区分请求命令、已执行命令和实际反馈。UDS 不能仅回显写入的命令就声称负载动作成功。

## 六、哪些服务必须实现

从 OEM 诊断规范和所选协议／合规范围建立服务支持矩阵，逐个列出会话、访问级别、子功能、寻址方式、NRC、时序和恢复规则。不存在“所有 BCM 无条件必须支持 0x10/11/14/19/22/27/2E/31/3E”的通用结论。

0x28 的通信控制需要 Dcm、BswM 及通信相关模块协调；不是 Dcm 直接开关所有 Com 报文。0x34/36/37 是否放 Bootloader 及应用如何交接也要由启动与升级架构决定。

## 七、自检

1. pending、confirmed、去抖和老化分别是什么？
2. 多帧读 DID 时如何保证数据快照一致？
3. 下线强制控制为什么必须有归还控制和保护规则？

## 核对依据

- [SWS_DiagnosticCommunicationManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_DiagnosticCommunicationManager.pdf)：服务、异步调用、时序、DID、0x2F 与 0x31
- [SWS_DiagnosticEventManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_DiagnosticEventManager.pdf)：状态位、事件组合、冻结帧、清码与 NvM
- [SWS_IOHardwareAbstraction，PDF 第 48 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_IOHardwareAbstraction.pdf#page=48)：§8.6 功能诊断控制与读取接口
- [TPS_DiagnosticExtractTemplate](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_DiagnosticExtractTemplate.pdf)：诊断数据和配置模型

---

**上一篇** → [[06-NVM数据管理]]
**下一篇** → [[08-看门狗与监控]]
**相关** → [[05-错误处理三级分类]]
**返回** → [[AUTOSAR知识地图]]
