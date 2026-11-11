---
title: CP 与 AP 与 FO 三大标准
aliases: [Classic Platform, Adaptive Platform, Foundation, CP AP FO]
tags: [思想, 全景]
source: [TR_ReleaseOverview]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# CP、AP 与 FO 三大标准

> [!tip] 结论
> CP 面向深度嵌入式、可预测实时软件，AP 面向高性能计算等场景，FO 提供跨平台共享的协议与通用部分。这是标准范围与执行模型的区别，不是仅按芯片、语言、启动秒数或通信协议就能判定。

## 一、各自的定位

| 标准 | 学习重点 |
|---|---|
| Classic Platform | SWC、RTE、BSW、静态配置及实时集成 |
| Adaptive Platform | 相应应用、执行／通信及平台服务模型；精确接口需读 AP 官方资料 |
| Foundation | 平台互通所需的通用协议、要求和规范部分 |

本地资料主要是 CP，不用它冒充完整 AP API、语言版本或动态能力的权威来源。

## 二、原有二分法的修正

- CP 有 SOME/IP、以太网、DDS 等能力，不能称为只支持信号通信。
- CP 也有升级与后构建配置相关机制，不等于“一次烧录永远不更新”。
- 静态配置不意味着运行时没有调度决策、模式切换或条件路径。
- AP 不意味着不需要实时、保护和安全分析；这些属性也不能靠平台名字自动获得。
- MCU／SoC、C／C++、毫秒／秒启动都是常见工程背景，不是平台充分必要判据。

## 三、版本关系

本版 CP 明确依赖 Foundation R25-11。ReleaseOverview 表 1.2 给出：

| 发布版本 | 内部版本 | Schema |
|---|---|---|
| R24-11 | R4.10.0 | AUTOSAR_00053 |
| R25-11 | R4.11.0 | AUTOSAR_00054 |

学习和实现时固定所用版本；具体条目生命周期、旧接口移除和工具兼容性另行核对。不要因某版本已经发布两年就自动称其进入 Maintenance。

## 四、BCM 的学习范围

以 MCU SDK＋FreeRTOS 的车身控制框架为目标，优先 CP 的分层、IO、通信、诊断、存储、模式与调度思想。当前不把 CVM0146、特定内核、OTA 范围当作已确认硬件事实。

采用 FreeRTOS 的自建平台不会因“静态执行＋CAN”就自动成为 AUTOSAR CP 实现。它可以借鉴架构并逐项兼容所需接口／协议。

## 五、自检

1. 为什么用 SOME/IP 不能直接判断是 AP？
2. 为什么 FreeRTOS 加分层不能自动声明 CP 合规？
3. CP 对 FO 的依赖从哪里核对？

## 核对依据

- [TR_ReleaseOverview，PDF 第 8 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf#page=8)：§1.3.3 标准范围
- [TR_ReleaseOverview，PDF 第 9 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf#page=9)：FO 与跨标准依赖
- [TR_ReleaseOverview，PDF 第 12 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf#page=12)：内部版本／Schema 对照
- [TR_ReleaseOverview，PDF 第 14 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf#page=14)：DDS 扩展及已有 SOME/IP 能力背景

---

**上一篇** → [[06-标准化边界-什么进标准什么不进]]
**下一篇** → [[01-分层架构总览]]
**相关** → [[04-规范项生命周期与版本]]
**返回** → [[AUTOSAR知识地图]]
