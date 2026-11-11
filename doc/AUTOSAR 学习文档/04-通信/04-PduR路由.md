---
title: PduR 路由
aliases: [PduR, PDU Router, 路由, PDU路由器]
tags: [通信]
source: [SWS_PDURouter]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# PduR 路由

> [!tip] 结论
> PduR 按配置的 PDU 标识和路由路径连接上层通信模块与下层 If／TP 模块；LSduR 处理再靠近总线接口的一层。数据路径和确认／取数回调要分开画。

## 一、路由路径与引擎

Routing paths 描述源、目标、数据提供方式、缓冲和路由组；引擎执行 ID 转换与相应操作。静态配置不表示 routing path group 不可在运行时启停，也不意味着只有一种缓冲策略。

PduR 不通过任意业务数据实时计算路由，不负责信号级缩放与策略。整 PDU 网关和 Com 信号网关职责不同。

## 二、API 名称中的方向

| 代表接口 | 调用来源 | 意义 |
|---|---|---|
| `PduR_ComTransmit` / `PduR_DcmTransmit` | 上层 Com / Dcm | 请求下发 |
| `PduR_<Lo>RxIndication` | 下层 If 路径 | 向上通知接收 |
| `PduR_<Lo>TxConfirmation` | 下层 If 路径 | 向上确认发送 |
| `PduR_CanTpStartOfReception` | CanTp | 请求上层接收资源 |
| `PduR_CanTpCopyRxData` | CanTp | 向上层交付接收数据 |
| `PduR_CanTpCopyTxData` | CanTp | 从上层取得发送数据 |

`<Lo>` 是下层模块占位符；R25-11 的具体 LSduR 连接和生成名称查规范／生成合同。不要把 `PduR_<UpTp>CopyRxData` 当成下层 TP 通知的通用正确命名。

## 三、典型链路

```text
信号发送：Com → PduR → LSduR → CanIf
诊断发送：Dcm → PduR → CanTp → LSduR → CanIf
TP 网关： CanTp(源连接) → PduR → CanTp(目标连接)
```

TP 网关在 PduR 边界处理的是重组／待分段的 SDU 数据流，不是将总线 N-PDU 原样交给另一个 CanTp。On-the-fly 转发需要适当阈值、缓冲和错误处理，并非所有部署自动启用。

IpduM 可同时扮演上下层角色：面对 Com 是下层，面对更低的通信路径是上层。它常经 PduR 分别连接两侧，不要用画反的注释理解该关系。

## 四、多播与诊断边界

PduR 支持规定的 1:1、1:N、N:1 等路由，但受模块类型、方向和缓冲配置约束。不要用“一帧同时扔给 Com、Dcm、CanNm”作为通用例子：Dcm 需要 TP 上层合同，CanNm 处理自己的网络管理 PDU。

## 五、零成本并不违反标准

对于适用的简单路由，规范有 zero cost operation 机制，可由宏等方式映射调用。PduR 的逻辑合同存在，不意味着必须有一份独立运行时对象和额外拷贝。

同理，LSduR 与 PduR 可以按规范整合实现。自建框架是否拆成文件，按真实复杂度决定。

## 六、自检

1. 为什么 CanTpCopyTxData 的调用来源是 CanTp？
2. TP 网关在 PduR 层看到的是 SDU 还是单个总线分段帧？
3. 为什么宏映射仍可以保留标准路由合同？

## 核对依据

- [SWS_PDURouter](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_PDURouter.pdf)：上下层 API、zero cost operation、routing path group、TP 网关
- [SWS_LSduRouter，PDF 第 7 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_LSduRouter.pdf#page=7)：LSduR/PduR 的边界与可整合实现

---

**上一篇** → [[03-COM信号处理]]
**下一篇** → [[05-CanIf与CanDrv]]
**返回** → [[AUTOSAR知识地图]]
