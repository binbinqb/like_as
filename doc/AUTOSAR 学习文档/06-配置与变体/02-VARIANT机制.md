---
title: VARIANT 机制
aliases: [Variant, 变体, Variation Point, Predefined Variant]
tags: [配置, 变体]
source: [TR_VFB, EXP_LayeredSoftwareArchitecture, TPS_SoftwareComponentTemplate]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# VARIANT 机制

> [!tip] 结论
> 结构变体描述元素在配置中是否存在及如何连接，运行模式描述软件在执行时如何工作。VFB 对运行期结构变异的限制，不等于禁止 CP 运行时切换功能、模式、通信组或诊断控制。

## 一、绑定阶段

VFB 讨论 System Design、Code Generation、Pre Compile、Link Time、Post Build 等绑定时间。应按具体元素的 latest binding time 检查，不能写成“所有变体必须在构建前绑定”，因为 Post Build 本来就是更晚的阶段。

## 二、基本元素

| 元素 | 作用 |
|---|---|
| VariationPoint | 描述受条件影响的元素 |
| Software System Constant | 支持相应早期绑定条件 |
| Software System Dependent Formula | 基于系统常量表达条件 |
| Post Build Variant Criterion / Condition | 支持规定的后构建选择 |
| PredefinedVariant | 一组经组织的赋值与准则绑定 |

PredefinedVariant 管理组合，不会自动解决所有组合测试。合法组合仍需定义资源约束、禁止组合和验证覆盖。

## 三、组件、端口、连接器的区别

VFB 对 SWC、Port 和 Connector 的 variability 分别规定约束，部分组件存在性可以晚至 Post Build，端口存在性有更早的绑定限制。不要把 BSW 的 `VARIANT-*` 支持声明与所有 SWC 元素变异机械画成一一对应关系。

删除组件／端口后，关联未连接端口的行为必须核对，不能默认工具会创造一个可工作的替代功能。概念 XML 不能直接用作符合 Schema 的输入。

## 四、运行时允许发生什么

```text
启动选择“高配配置”        → 受支持的 post-build selection
自动大灯功能在 RUN 下使能 → 运行策略／模式
关闭一组 Com I-PDU        → 通信运行状态
诊断临时获得 HSD 控制权   → 控制权状态
运行中任意创建／删除 SWC、改变端口结构 → 不能由上述机制直接推出支持
```

分支和运行状态会改变执行路径，但不意味着无法分析 WCET；原笔记“运行期路径变化所以不能证明时序”的推论不成立。

## 五、BCM 变体管理建议

先定义维度、合法组合和默认行为，再选绑定阶段。几十种组合可以通过构建矩阵、生成配置、后构建选择或其组合实现，不存在“组合多就必须全部 post-build”。

若 NvM 编码决定启动配置，应避免初始化循环依赖：选择配置所需的最小读取机制与后续 NvM／完整 BSW 配置要有明确启动顺序。

## 六、自检

1. “运行时关闭自动大灯”为什么不是运行期重新绑定 SWC 结构？
2. latest binding time 约束的是哪一个元素？
3. 配置选择依赖 NvM 数据时如何避免初始化循环？

## 核对依据

- [TR_VFB](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_VFB.pdf)：§Variability：binding times、组件／端口／连接器变体
- [TPS_SoftwareComponentTemplate](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_SoftwareComponentTemplate.pdf)：VariationPoint 与组件模型
- [TPS_ECUConfiguration，PDF 第 174 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_ECUConfiguration.pdf#page=174)：EcucPostBuildVariants 配置选择模型

---

**上一篇** → [[01-配置三态]]
**下一篇** → [[03-产品线工程]]
**返回** → [[AUTOSAR知识地图]]
