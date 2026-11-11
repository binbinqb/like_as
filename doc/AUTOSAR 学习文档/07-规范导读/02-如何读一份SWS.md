---
title: 如何读一份 SWS
aliases: [读SWS, SWS导读, 规范阅读方法]
tags: [规范导读, 元知识, 核心]
source: [SWS_BSWGeneral, RS_BSWGeneral]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# 如何读一份 SWS

> [!tip] 结论
> 按“版本与范围 → 依赖 → 功能行为 → API 合同 → 配置 → 追溯与已知问题”阅读。章节号只是导航，不同 SWS 可能不同；EXP 的示意图和笔记中的代码都不能替代模块规范正文。

## 一、先确认范围

记录文档标题、Document ID、版本、状态、变更历史和依赖文档。引用要带版本、条目 ID 及必要上下文；仅条目 ID 存在不证明自己的解释正确。

SHALL 表示要求，SHOULD 表示推荐，MAY 表示允许，具体按文档的术语约定理解。不要把 MUST 机械解释成比 SHALL 更高的第二档强制等级。

## 二、API 表至少检查这些字段

| 字段 | 要问的问题 |
|---|---|
| Syntax / 类型 | 参数、位宽、const、指针和句柄到底是什么？ |
| Sync/Async | 返回意味着完成，还是仅受理请求？ |
| Reentrancy | 同一通道／实例／对象能否并发？ |
| 调用上下文 | Task、ISR、Hook 或初始化阶段是否允许？ |
| 返回值／输出参数 | 查询成功与被查询作业结果是否不同？ |
| 缓冲生命周期 | 谁拥有数据，何时可修改／释放？ |
| 错误行为 | 拒绝、报告、状态改变、通知分别是什么？ |

`Reentrant` 不意味着任意上下文均可调用；`Non Reentrant` 也不意味着只要在 ISR 调用就必然出错。调用上下文限制和并发限制是两个维度。`Reentrant for different channels` 应理解为不同通道间允许的重入，不能改写成“不同线程可以，同一线程不行”。

## 三、配置字段

读取类型、单位、范围、Multiplicity、默认值、依赖、引用目标、配置类和 post-build 支持属性。`0..1` 是可选且最多一个，不能当成必填；字段存在也不代表所有变体和目标都支持。

配置名必须来自本版本正文或配套模型。看起来合理的名称不等于真实参数。

## 四、COM 接收超时的正确练习

1. 在 SWS_COM 查 reception deadline monitoring 及启停条件。
2. 检查 `ComTimeout`、`ComFirstTimeout`、`ComRxDataTimeoutAction`、通知与 update bit 的关系。
3. 查看 `Com_ReceiveSignal` 的实际返回定义，不要自造 `COM_E_MAX_AGE_EXCEEDED`。
4. 核对 RTE 配置如何将数据、状态与超时通知呈现给 SWC。
5. 测试首次未接收、正常接收、超时、恢复、失效编码和通信组停止。

“超时必须小于 3 倍周期”“事件不能用 Alive 过滤”不是这里可以直接引用的标准结论。实际 deadline 来自系统需求与通信抖动预算；过滤使用本版本真实枚举。

## 五、图、正文与示例交叉阅读

状态机图适合建立理解，条目正文给出约束，两者都可能有边界和勘误。不能说图一定比文字准确。发现冲突时记录具体版本、页码与条目，并查看已知技术缺陷，而不是自行选一个当绝对依据。

## 六、产出一张导读卡

记录职责、不负责什么、关键 API、配置、状态、错误、初始化依赖、异步完成、并发、证据链接、待确认项及最小测试。模板见 [[规范导读卡模板]]。

代码片段明确标注“概念示例／自建接口”或“标准 API”，可编译 ARXML 与伪 XML 分开。不能用占位 ID 冒充真实条目。

## 七、自检

1. API 同步属性与可重入属性分别说明什么？
2. 发现一个参数名是否足以证明整个超时链路正确？
3. 为什么“引用 ID 存在”和“引用语义正确”需要分别审查？

## 核对依据

- [SWS_COM，PDF 第 100 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=100)：实际返回状态定义
- [SWS_COM，PDF 第 194 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=194)：接收超时配置对象
- [SWS_BSWGeneral](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_BSWGeneral.pdf)：BSW 通用接口、命名与行为要求
- [TR_ReleaseOverview，PDF 第 31 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf#page=31)：已知技术缺陷章节起始

---

**上一篇** → [[01-规范文档体系-SWS-RS-EXP-TPS-TR]]
**下一篇** → [[03-需求编号与追溯]]
**返回** → [[AUTOSAR知识地图]]
