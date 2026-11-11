---
title: 规范文档体系 SWS-RS-EXP-TPS-TR
aliases: [文档体系, 文档类型, SWS, RS, EXP, TPS, TR]
tags: [规范导读, 元知识]
source: [TR_ReleaseOverview]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# 规范文档体系：SWS / RS / EXP / TPS / TR

> [!tip] 结论
> 212 份文档分六类，**先搞清楚类型，再决定要不要读**：
>
> | 类型 | 数量 | 性质 | 什么时候读 |
> |---|---|---|---|
> | **SWS** | 127 | 规范性 | 实现/配置某个模块时 |
> | **RS** | 45 | 规范性 | 理解"为什么有这个模块"时 |
> | **EXP** | 21 | **说明性** | **学习概念时（最高优先）** |
> | **TPS** | 7 | 规范性 | 建模/写工具时 |
> | **TR** | 11 | 说明性 | 方法论/版本 |
> | **ASWS** | 1 | 规范性 | 特殊（Transformer） |

## 一、六类文档的本质区别

### 1.1 SWS（Software Specification，软件规范）

| 项 | 内容 |
|---|---|
| 全称 | Specification of XXX |
| 数量 | **127**（本地 SWS 文件数，含 RTE、类型、库与通用规范，不能等同 BSW 模块数） |
| 性质 | **规范性**（含 SHALL 要求） |
| 内容 | API 定义、状态机、配置参数、错误码、时序 |
| 读者 | BSW 开发者、集成工程师 |
| 典型篇幅 | 100~800 页 |

**结构高度统一**（因为有模板）：

```
1 Introduction and functional overview
2 Acronyms
3 Related documentation
4 Constraints and assumptions
5 Dependencies to other modules
6 Requirements Tracing          ← 需求追溯表
7 Functional specification      ← 核心：功能与 API
8 API specification             ← 核心：函数原型
9 Sequence diagrams
10 Configuration specification  ← 核心：配置参数
A Change history
```

> [!tip] 功能、API、配置是重点，但不能省略依赖和约束
> **第 7 章（功能）、第 8 章（API）、第 10 章（配置）**。
> 同时检查适用范围、依赖、初始化、时序、错误、并发和已知问题，章节号以本文件目录为准。

### 1.2 RS（Requirements Specification，需求规范）

| 项 | 内容 |
|---|---|
| 全称 | Requirements Specification of / General Requirements on |
| 数量 | **45** |
| 性质 | **规范性**（需求条目） |
| 内容 | `SRS_xxx_xxxxx` 形式的需求 |
| 读者 | 架构师、需求工程师、SWS 编写者 |
| 典型篇幅 | 20~200 页 |

**RS 与 SWS 的关系**：

```
RS（要什么）              SWS（怎么做）
┌──────────────┐        ┌──────────────┐
│ SRS_Can_01059│──追溯──▶│ SWS_Can_00011│
│ "驱动应直接   │        │ "Can 模块应   │
│  拷贝数据"    │        │  直接拷贝..." │
└──────────────┘        └──────────────┘
```

**两类 RS**：

| 类型 | 例子 | 特点 |
|---|---|---|
| **通用需求** | `RS_BSWGeneral` | 所有模块都要遵守（BSW 的"宪法"） |
| **模块需求** | `RS_CAN`、`RS_COM` | 单个模块的需求 |

### 1.3 EXP（Explanation，说明性文档）

| 项 | 内容 |
|---|---|
| 全称 | Explanation of / Guide to / Guideline for |
| 数量 | **21**（含 7 个 `AI*` 应用接口说明） |
| 性质 | 通常为解释性／指南内容；应逐份检查范围与规范性声明，不能只由 EXP 前缀断言完全没有约束或条目标识 |
| 内容 | 概念解释、架构说明、最佳实践、示例 |
| 读者 | **所有学习者** |

> [!important] 这是本库的主要信息来源
> 原文明确："This document **does not contain requirements** and is **informative only**."
> 但**恰恰是这些文档讲清了"为什么"**。
>
> | 文档 | 讲什么 |
> |---|---|
> | `EXP_LayeredSoftwareArchitecture` | 分层架构（182 页幻灯片，全是精华） |
> | `EXP_ModeManagementGuide` | 模式管理（含 BswM 规则示例） |
> | `EXP_NVDataHandling` | NVM 机制（含配置变更处理） |
> | `EXP_CDDDesignAndIntegrationGuideline` | CDD 设计（含文件结构） |
> | `EXP_AIBodyAndComfort` | **车身域标准 SWC 分解** |
> | `EXP_ErrorDescription` | 错误码体系 |
> | `EXP_FunctionalSafetyMeasures` | 功能安全措施 |

### 1.4 TPS（Template Specification，模板规范）

| 项 | 内容 |
|---|---|
| 全称 | Template Specification of XXX |
| 数量 | **7** |
| 性质 | **规范性**（元模型定义） |
| 内容 | ARXML 的结构（类、属性、约束） |
| 读者 | 工具开发者、建模者 |

| 文档 | 定义什么 |
|---|---|
| `TPS_SystemTemplate` | 系统描述的结构（ECU、网络、映射） |
| `TPS_SoftwareComponentTemplate` | SWC 描述的结构（端口、Runnable、内部行为） |
| `TPS_ECUConfiguration` | ECU 配置参数的结构 |
| `TPS_BSWModuleDescriptionTemplate` | BSW 模块描述 |
| `TPS_ECUResourceTemplate` | 硬件资源描述 |
| `TPS_DiagnosticExtractTemplate` | 诊断描述 |
| `TPS_TimingExtensions` | 时序约束描述 |

> [!note] TPS 是"描述的语言"
> 如果把 AUTOSAR 比作一门语言：
> - **TPS = 语法**（怎么写才合法）
> - **SWS = 词汇表**（每个模块的语义）
> - **EXP = 语言使用指南**（怎么用好）

### 1.5 TR（Technical Report，技术报告）

| 项 | 内容 |
|---|---|
| 全称 | Technical Report on / for |
| 数量 | **11** |
| 性质 | **说明性** |
| 内容 | 方法论、版本概览、示例、建模指南 |

| 文档 | 讲什么 |
|---|---|
| `TR_Methodology` | **方法论（457 页，产物链完整定义）** |
| `TR_VFB` | **虚拟功能总线（思想源头）** |
| `TR_ReleaseOverview` | 版本变化、CP/AP/FO 格局 |
| `TR_WorkflowExample` | **完整案例（轮速→车速）** |
| `TR_ModelingShowCases` | 建模示例说明 |
| `TR_SWCModelingGuide` | SWC 建模指南 |
| `TR_AIDesignPatternsCatalogue` | AI 设计模式 |

### 1.6 ASWS（Transformer 专用）

只有 1 份：`ASWS_TransformerGeneral`。

| 项 | 内容 |
|---|---|
| 用途 | 定义数据转换器（Transformer）的通用规范 |
| 何时看 | 需要跨 ECU 数据转换（序列化、端序、缩放）时 |

## 二、按目的查文档（决策表）

| 你想干什么 | 查哪类 | 具体文档 |
|---|---|---|
| **理解 AUTOSAR 是什么** | EXP / TR | LayeredSoftwareArchitecture、TR_VFB |
| **理解分层为什么这样分** | EXP | LayeredSoftwareArchitecture |
| **知道从功能到代码怎么走** | TR | TR_Methodology |
| **实现一个 BSW 模块** | SWS + RS | 对应模块的 SWS + RS_BSWGeneral |
| **配置某个模块** | SWS 第 10 章 | 对应模块 SWS |
| **建模（写 ARXML）** | TPS | 对应 Template |
| **理解通信栈** | SWS + EXP | SWS_COM/PduR/CanIf/CanTp |
| **理解模式管理** | EXP | ModeManagementGuide |
| **理解 NVM** | EXP | NVDataHandling |
| **做 BCM 功能分解** | EXP | AIBodyAndComfort |
| **写 CDD** | EXP | CDDDesignAndIntegrationGuideline |
| **知道版本改了什么** | TR | ReleaseOverview |
| **看一个完整例子** | TR + 示例文件 | WorkflowExample + ModelingShowCases |

## 三、文档之间的追溯关系

```
项目目标 / 通用需求（Foundation）
        │
        ▼
RS（模块需求，SRS_xxx）
        │ 追溯
        ▼
SWS（模块规范，SWS_xxx）
        │ 配置规范
        ▼
TPS_ECUConfiguration（配置参数结构）
        │
        ▼
生成的代码
```

| 关系 | 含义 |
|---|---|
| **RS → SWS** | SWS 必须覆盖 RS 的所有需求（"Requirements Tracing" 章节） |
| **SWS → TPS** | SWS 的配置参数必须符合 TPS 定义的元模型 |
| **EXP → 无** | 说明性文档不参与追溯 |

> [!tip] "Requirements Tracing" 章节是宝库
> 每个 SWS 都有这一章，列出：
> - 它实现了哪些上游需求
> - 每个需求对应哪些 SWS 条目
>
> **想知道"这个 API 为什么必须这样"，从这里往上追。**

## 四、文档编号体系

每份文档有一个 **Document ID**（全局唯一）：

| 文档 | Document ID |
|---|---|
| `TR_ReleaseOverview` | 0 |
| `SWS_Can` | 11 |
| `SWS_CanTp` | 14 |
| `SWS_COM` | 15 |
| `SWS_Dcm` | 18 |
| `SWS_OS` | 34 |
| `SWS_PduR` | 35 |
| `RS_BSWGeneral` | 43 |
| `EXP_LayeredSoftwareArchitecture` | 53 |
| `TR_VFB` | 56 |
| `TPS_SoftwareComponentTemplate` | 62 |
| `TR_Methodology` | 68 |
| `SWS_EcuM` | 78 |
| `SWS_WdgM` | 80 |
| `EXP_AIBodyAndComfort` | 268 |
| `EXP_ModeManagementGuide` | 440 |
| `EXP_CDDDesignAndIntegrationGuideline` | 622 |
| `TR_ModelingShowCases` | 789 |
| `EXP_NVDataHandling` | 810 |
| `TR_WorkflowExample` | 1145 |

**用途**：引用文档时可以写 "见 DocID 68"（比文件名短，且不随版本改名）。

## 五、命名规律

```
AUTOSAR_CP_<类型>_<主题>.pdf
          │      │
          │      └── 模块名/主题名（驼峰，无下划线）
          └── SWS / RS / EXP / TR / TPS / ASWS / MOD

例：
AUTOSAR_CP_SWS_CANTransportLayer.pdf   → SWS，主题 CANTransportLayer
AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf
AUTOSAR_CP_RS_BSWGeneral.pdf
```

> [!note] 主题名与模块名的差异
> 文件名用**完整英文名**（`CANTransportLayer`），模块缩写是 `CanTp`。
> 查找时用完整名，代码里用缩写。

## 六、哪些文档可以跳过

| 文档类型 | 可以跳过吗 |
|---|---|
| EXP / TR | ❌ **不能跳**（最有价值） |
| RS_BSWGeneral | ❌ 不能跳（BSW 宪法） |
| 你用的模块的 SWS | ❌ 不能跳 |
| 你不用的模块的 SWS | ✅ 跳过（如 V2X、DDS、ChrgM） |
| TPS（除非写工具） | ⚠️ 可跳（但 `TPS_SoftwareComponentTemplate` 值得看） |
| 各种 RS（模块级） | ⚠️ 实现时查，不必通读 |

### 对 BCM 项目，优先读这 10 份

| # | 文档 | 理由 |
|---|---|---|
| 1 | `EXP_LayeredSoftwareArchitecture` | 架构总纲 |
| 2 | `TR_VFB` | 思想源头 |
| 3 | `TR_Methodology` | 产物链 |
| 4 | `RS_BSWGeneral` | BSW 宪法 |
| 5 | `EXP_AIBodyAndComfort` | 车身域分解 |
| 6 | `EXP_ModeManagementGuide` | 睡眠唤醒 |
| 7 | `EXP_NVDataHandling` | 存储 |
| 8 | `SWS_COM` | 信号处理 |
| 9 | `SWS_CanTp` | 诊断传输 |
| 10 | `SWS_Dcm` | 诊断服务 |

## 七、自检

1. 想理解"为什么分四层"，该查哪类文档？
2. SWS 和 RS 的关系是什么？
3. 为什么 EXP 类文档"不含需求"却最值得读？

---

**上一篇** → [[03-产品线工程]]
**下一篇** → [[02-如何读一份SWS]]
**返回** → [[AUTOSAR知识地图]]


## 原文入口与审查范围

- [TR_ReleaseOverview](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf)

> [!note] 阅读边界
> 原文入口用于继续核对；定向修正以审查记录为准，未逐条验证的解释和示例不因添加链接而自动成为官方结论。
