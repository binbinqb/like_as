---
title: PDU 与 SDU 分层命名
aliases: [PDU, SDU, PCI, 命名约定]
tags: [通信, 基础]
source: [EXP_LayeredSoftwareArchitecture]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# PDU 与 SDU 分层命名

> [!tip] 结论
> SDU 是本层向相邻层提供服务时处理的载荷；PDU 是本协议层交换的单元，含本层所需的 PCI。名称是相对于层次的视角，不代表所有层都把“头＋数据”放进同一块连续数组。

## 一、三种术语

| 名称 | 含义 |
|---|---|
| SDU | Service Data Unit，相邻层服务边界上的数据 |
| PCI | Protocol Control Information，本协议控制信息，不一定只有前置头 |
| PDU | Protocol Data Unit，本协议交换单元 |

上层 PDU 可以成为下层 SDU。传输协议分段／重组时不是简单的一一加头关系，还可能涉及流控、序号和多个底层 PDU。

## 二、AUTOSAR 常见前缀

| 前缀 | 学习视角 | 例子 |
|---|---|---|
| I | Interaction | Com 等处理的 I-PDU |
| N | Network | CanTp 的 N-SDU 与 N-PDU |
| L | Link | CAN L-SDU／L-PDU |

这些前缀沿协议分层解释，不能把 AUTOSAR 每个模块与 OSI 层机械一一等同。

## 三、CanTp 的两个边界

`CanTp_Transmit(TxPduId, PduInfoPtr)` 上侧的 ID 标识待传输 N-SDU；CanTp 下侧提供包含 PCI 的 N-PDU。原笔记将上侧 TxPduId 标为 N-PDU，应纠正。

```text
Dcm → PduR → CanTp：完整诊断消息／N-SDU
                   ↓ 分段、添加 PCI
              N-PDU → LSduR → CanIf → Can
```

短消息也是 SF，不能省略 TP；普通 Com 信号路径则可不经过 CanTp。具体选择按配置，不能一律按“大于 8 字节”判断。

## 四、长度不能混用

经典 CAN、normal addressing、8 字节载荷时：SF 的 N-PDU 数据区可为 8 字节，其中 PCI 占 1，应用载荷最多 7；普通 FF 首段载荷为 6，CF 载荷为 7。

不能把“SF 载荷 7 字节”写成“N-PDU 总长不超过 7 字节且包含 PCI”。CAN FD、附加地址和长长度字段另有开销。Com 信号也不一律限制在 1..64 bit，存在数组、动态长度等类型。

## 五、ID 与数据分离

CAN ID、长度和 SDU 指针在 API 中往往是独立字段。线上仲裁字段、CRC、ACK 等由控制器生成，不是 CanIf 将它们全部 prepend 到同一 data 数组。

DBC 的 Message 描述 CAN 帧相关对象；AUTOSAR 的 Frame、PDU 和映射是不同对象。常见一帧一 I-PDU 不代表模型上恒等，网关、复用与 TP 会产生不同映射。

## 六、自检

1. 为什么同一份数据的 PDU/SDU 名称会随观察层改变？
2. CanTp_Transmit 上侧处理 N-SDU 还是 N-PDU？
3. 为什么 SF 的载荷长度不能当作 N-PDU 总长度？

## 核对依据

- [EXP_LayeredSoftwareArchitecture](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf)：PDU/SDU/PCI 及分层命名
- [SWS_CANTransportLayer](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANTransportLayer.pdf)：CanTp_Transmit 的 N-SDU 与下层 N-PDU
- [SWS_CommunicationStackTypes](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CommunicationStackTypes.pdf)：PduInfoType、长度、MetaData 与 API 数据表示

---

**上一篇** → [[01-通信栈全景]]
**下一篇** → [[03-COM信号处理]]
**返回** → [[AUTOSAR知识地图]]
