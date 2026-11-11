---
title: CanTp 传输协议
aliases: [CanTp, CAN Transport Layer, ISO 15765-2, TP]
tags: [通信, 核心]
source: [SWS_CANTransportLayer]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# CanTp 传输协议

> [!tip] 结论
> CanTp 处理 ISO-TP 的分段／重组、流控、序号及超时。UDS 的 P2/P2* 是应用层响应时序，不能与传输层 N_* 定时器混在一起。

## 一、R25-11 的位置

```text
发送：Dcm → PduR → CanTp → LSduR → CanIf → Can
接收：Can → CanIf → LSduR → CanTp → PduR → Dcm
```

旧架构常见 CanTp 直接连接 CanIf。R24-11 下层切换到 LSduR；R25-11 增加 TP 通道发送请求队列。队列容量与支持行为仍要查配置，不能假设任何请求都会无限排队。

## 二、四种帧

| 帧 | 含义 | 要点 |
|---|---|---|
| SF | Single Frame | 短消息也包含 PCI，仍属于 TP |
| FF | First Frame | 声明多帧消息长度并携带首段数据 |
| CF | Consecutive Frame | 后续数据与 4 位序号 |
| FC | Flow Control | CTS、WAIT、OVFLW，以及 BS、STmin |

经典 CAN、normal addressing、8 字节载荷的常见情况：SF 数据最多 7 字节，普通 FF 首段 6 字节，CF 7 字节。增加地址字节或改变数据长度后容量不同。

CAN FD 使用 64 字节载荷且不带额外地址字节时，SF 使用长度转义可携带 62 字节；普通 12 位 FF 长度格式有 62 字节首段数据，32 位长度转义 FF 有 58 字节，CF 为 63 字节。不能把所有 FF 一律写成 58 字节。

4095 是 12 位长度格式的上限，不是所有现代 ISO-TP／AUTOSAR 配置的绝对最大长度。支持范围受协议版本、API 类型、实现和缓冲配置限制。

## 三、定时器分清角色

| 定时器 | 监控的阶段 |
|---|---|
| N_As | 发送方数据帧的发送确认 |
| N_Ar | 接收方 FC 帧的发送确认；**不是等收到数据帧** |
| N_Bs | 发送方等待 FC |
| N_Br | 接收方准备／提供 FC 所涉及的处理时间 |
| N_Cs | 发送方准备后续 CF 所涉及的处理时间 |
| N_Cr | 接收方等待下一 CF |

具体启动、停止、重启点按状态机和确认事件核对，不能简单在调用发送函数后不管结果就开始等 FC。

## 四、BS、STmin 与 WAIT

BS=0 表示本次连续传输不因块大小要求周期等待新的 FC，不表示无限接收缓冲。STmin 编码包括 0x00..0x7F 的毫秒范围和 0xF1..0xF9 的 100..900 µs 范围；保留值处理按规范。

CF 序号在 FF 后从 1 开始，模 16 回绕。序号错误、超时和溢出按规定中止／通知，不应统一描述为自动重传。

WFTmax 涉及接收方最多允许发送的 WAIT 数量等规则，不能把接收端 `CanTpRxWftMax` 配置直接说成任意发送端都有的同名计数参数。

## 五、刷写与长操作

Flash 擦除通常通过诊断服务／例程异步执行，必要时由 UDS responsePending 与 P2* 协调。传输正在进行时仍必须满足 TP 流控和 N_* 时序。

不应默认将 N_Bs/N_Cr 放大到 5~10 秒解决擦除慢；这可能掩盖任务阻塞或缓冲设计问题，并违反 OEM 参数。应先确认超时发生在帧发送确认、等 FC、等 CF 还是诊断服务处理阶段。

主机工具参数按角色匹配协议合同，而不是统一乘以 ECU 超时的 1.5。Python 库、适配器、操作系统和实际工具接口需在集成时确认；本库不假定已经有某套 Kvaser 刷写工具。

## 六、验收项目

覆盖 SF/FF/CF/FC、地址格式、CAN FD 长度格式、序号回绕、BS、STmin、WAIT/OVFLW、队列满、取消、不同连接并发、各定时器边界及错误后的恢复。

## 七、自检

1. N_Ar 为什么是 FC 的发送确认时间？
2. CAN FD 普通 FF 和长长度转义 FF 的有效载荷为什么不同？
3. 擦除慢时，首先检查 TP 定时器还是诊断服务状态机？如何区分？

## 核对依据

- [SWS_CANTransportLayer](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_CANTransportLayer.pdf)：变更历史、帧格式、定时器、队列及上下层接口
- [SWS_LSduRouter，PDF 第 7 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_LSduRouter.pdf#page=7)：CanTp 与总线接口之间的层次
- [SWS_DiagnosticCommunicationManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_DiagnosticCommunicationManager.pdf)：P2/P2*、responsePending 与异步服务处理

---

**上一篇** → [[05-CanIf与CanDrv]]
**下一篇** → [[07-网络管理NM与ComM]]
**返回** → [[AUTOSAR知识地图]]
