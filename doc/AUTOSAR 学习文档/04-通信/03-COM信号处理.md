---
title: COM 信号处理
aliases: [Com, Communication, 信号处理, 信号打包]
tags: [通信, 核心]
source: [SWS_COM]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# COM 信号处理

> [!tip] 结论
> Com 管理信号／信号组与 I-PDU 的转换、触发、监控和失效处理。DBC 的物理值换算和业务请求仲裁不是 Com 必然自动完成的能力，必须指定在哪一层实现。

## 一、打包与数据模型

信号位布局、字节序、符号和信号组通过配置描述。I-PDU 不一定是 8 字节，也可以使用 CAN FD 或 TP。Com 的基本信号接口不等同于带单位的业务接口。

Motorola sawtooth 编号示例：8 位信号起始位为 byte0.bit7 时，占用 byte0.bit7..bit0，不会扩展到 byte1.bit0。生成工具必须正确转换 DBC 与 AUTOSAR 模型中的位位置约定。

## 二、发送模式与 TransferProperty 分开

| 对象 | 常见枚举 | 作用 |
|---|---|---|
| I-PDU 发送模式 `ComTxModeMode` | DIRECT、PERIODIC、MIXED、NONE | 定义发送机制 |
| 信号 `ComTransferProperty` | PENDING、TRIGGERED、TRIGGERED_ON_CHANGE 等 | 决定信号更新如何触发 PDU |

因此“Event = OnChange”不成立：同值写入是否触发，取决于 transfer property 等配置。还需检查 MDT、重复发送、模式选择和 Tx confirmation。

重复发送提高传递机会，不保证报文必达。`Com_SendSignal` 被接受也不等于该帧已经上总线或被对端业务消费。

## 三、过滤用真实配置名

`ComFilterAlgorithm` 包括 ALWAYS、NEVER、MASKED_NEW_DIFFERS_MASKED_OLD、MASKED_NEW_EQUALS_X、MASKED_NEW_DIFFERS_X、NEW_IS_WITHIN、NEW_IS_OUTSIDE、ONE_EVERY_N 等，适用性按信号类型与方向核对。

不能把 Alive、Masked、Range 当作标准枚举，也不能把所有过滤都解释成“只通知值变化”。`ComAliveTimeout` 与这里的 filter algorithm 不是一回事。

## 四、接收超时、失效和更新位是不同机制

| 机制 | 说明 |
|---|---|
| `ComTimeout` / `ComFirstTimeout` | 按配置进行 deadline monitoring；不能用自造的 `ComRxDataTimeout` 替代参数名 |
| 接收超时动作 | 可涉及保持、替换或替代等策略，检查 `ComRxDataTimeoutAction` 等配置 |
| Invalid value | 协议约定的数据无效编码，与超时不是同一原因 |
| Update bit | 指示配置的数据是否更新；**不能替代 valid/invalid 状态位** |
| RTE 数据状态 | 由 RTE 合同、Com 通知／状态及连接配置共同决定 |

不能断言 `Com_ReceiveSignal` 一定返回 `COM_E_MAX_AGE_EXCEEDED`，或所有超时都自动等价于 `Rte_Read` 返回某个错误。查阅各自 API 表和生成配置。

没有可用带内失效编码时，可以设计单独的有效性字段／接口状态。保持最后值也可以是明确的降级策略，但必须携带过期状态，不能让业务误认为是新采样。

## 五、Signal Group 与一致性

Signal Group 提供一组相关信号的一致访问机制，但不自动保证不同传感器在物理世界同时采样。应明确 shadow buffer、更新动作、RTE 访问方式和数据时间戳。

## 六、I-PDU Group 的边界

Com I-PDU Group 管的是 Com 所属 I-PDU，不能用它直接启停 CanNm 的 NM PDU 或 Dcm/CanTp 的诊断传输。网络模式、PduR routing group、Com 通信组与诊断控制需要协调，但不是同一开关。

## 七、与 dbcom 的落地关系

先读取 dbcom 的接口和能力，再明确哪些由中间件负责、哪些由通信映射层补齐：位布局、物理值换算、周期发送、失效、接收超时和完成通知都只保留一个权威实现。

业务绑定见 [[08-通信矩阵与DBC]]，同一状态被多个任务访问时还需一致快照和数据所有权规则。

## 八、自检

1. DIRECT 与 TRIGGERED_ON_CHANGE 为什么不是同一个维度？
2. Update bit 为什么不能用来代替有效性？
3. 为什么停 Com I-PDU Group 不等于停全部 NM／诊断通信？

## 核对依据

- [SWS_COM，PDF 第 106 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=106)：Com_SendSignal、TransferProperty 与 DIRECT/MIXED 的关系
- [SWS_COM，PDF 第 174 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=174)：ComFilterAlgorithm 枚举模型
- [SWS_COM，PDF 第 194 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=194)：ComTimeout、ComFirstTimeout、失效与替代相关配置
- [SWS_COM，PDF 第 100 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=100)：Com 的错误／返回状态定义

---

**上一篇** → [[02-PDU与SDU分层命名]]
**下一篇** → [[04-PduR路由]]
**返回** → [[AUTOSAR知识地图]]
