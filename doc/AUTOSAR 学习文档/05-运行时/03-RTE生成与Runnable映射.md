---
title: RTE 生成与 Runnable 映射
aliases: [Runnable, Runnable映射, RTE生成, 任务映射]
tags: [机制, 核心]
source: [TR_VFB, EXP_LayeredSoftwareArchitecture, SWS_RTE]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# RTE 生成与 Runnable 映射

> [!tip] 结论
> Runnable 是由 RTE 启动的执行单元；RTEEvent 描述触发或等待的事件。生成器将事件、执行单元、Task、分区和核整合起来，不能把整个映射机制简化成“一 Runnable 永远只能对应一个 Task”。

## 一、Category 1 与 Category 2

| 类别 | 含义 | 设计影响 |
|---|---|---|
| Category 1 | 不含 WaitPoint | 通常短时执行并返回，可用于周期或事件处理 |
| Category 2 | 含 WaitPoint | 需要等待事件的执行环境及合适的 Extended Task 映射 |

SWS_RTE §4.2.2.6.1.4 说明 Category 2 的任务映射；通常各自映射到自己的 Extended Task，但多个放同一 Task 并非一概禁止，可能受生成器限制且引入额外等待。

这不表示可随意在 Runnable 中调用 RTOS 延时或创建线程。等待点、阻塞的服务调用和事件须通过模型描述并满足规则。对自建 BCM 框架，优先采用有界周期函数与状态机，是工程选择，不是“标准禁止所有阻塞”。

## 二、事件与映射

常见 RTEEvent 包括 TimingEvent、DataReceivedEvent、DataReceiveErrorEvent、OperationInvokedEvent、SwcModeSwitchEvent、BackgroundEvent 等，不是穷尽枚举。

映射时分别检查：

1. 哪个事件启动哪个 Runnable，哪个事件解除哪个 WaitPoint。
2. `RteEventToTaskMapping`、事件位置、调用顺序和调度条件。
3. 组件实例、`canBeInvokedConcurrently`、多实例支持与实例内存。
4. Task 所属 OS-Application、EcucPartition 和核的约束。
5. 跨分区／核通信以及同步调用的具体实现。

一个 Task 可以执行多个 Runnable，顺序应通过配置明确；“同周期所以顺序不确定”不是规则。一个可重入函数也不等于其所有组件实例都共享状态。

## 三、常见 API 的真实语义

| API 族 | 语义 |
|---|---|
| `Rte_Read` / `Rte_Write` | 显式非队列数据访问 |
| `Rte_Receive` / `Rte_Send` | 队列数据访问，需处理空队列／溢出 |
| `Rte_IRead` / `Rte_IWrite` | Runnable 隐式通信，提供配置范围内的一致数据视图 |
| `Rte_IsUpdated` | 按配置查询更新标记 |
| `Rte_Call` | 客户端发起服务操作 |
| `Rte_Result` | 客户端取得异步服务调用的结果，**不是服务端实现入口** |
| `Rte_Pim` | 访问组件实例内存 |
| `Rte_Prm` | 参数访问 |
| `Rte_Switch` / `Rte_Mode` | 模式切换／查询，按角色和配置使用 |
| `Rte_Enter` / `Rte_Exit` | ExclusiveArea 访问 |

服务端实现是由 OperationInvokedEvent 等关联的 Runnable。具体函数签名和可返回错误取决于生成合同，不能把所有 `Rte_Read` 都写成固定返回同一组错误码。

## 四、模式切换模型

SwcModeSwitchEvent 的 activation 使用 `ON-ENTRY`、`ON-EXIT` 等模型枚举；不能用自造的布尔 `<ON-TRANSITION>` 将 false/true 解释成进入／退出。需要可编译 ARXML 时，应按配套 Schema 和元模型生成，而不是照抄概念片段。

## 五、数据一致性

ExclusiveArea 是逻辑临界区，具体可能映射为 OS Resource、中断控制、锁或生成器采用的其他允许机制；不是固定等于“关闭任务调度”。

单个机器字访问可能原子，也不代表多字段快照一致，或读改写安全。`volatile` 不提供互斥或跨核内存顺序。应按数据所有权和访问场景选用隐式通信、快照、队列、ExclusiveArea、IOC 等机制。

生成文件布局取决于工具及优化，不能保证每个 SWC 都有一份 `Rte_<Swc>.c`。审查的是生成合同与行为，而非固定目录外观。

## 六、自建框架的最小实现

保留语义接口、初值与有效性、数据快照、Runnable 调度表和必要的事件队列即可起步。不要把所有层的转换逻辑都集中到一个巨大的 `rte_signals.c`；硬件采集、通信映射和业务仲裁各自负责。

应用仍以一个功能一组 `.c/.h` 编写；出现多实例需求时再引入独立上下文。没有多实例需求时，文件内 `static` 状态本身不构成错误。

## 七、自检

1. Category 2 Runnable 为什么需要特殊任务映射？
2. Rte_Result 是给客户端还是服务器使用？
3. 为什么“单次读写原子”不等于“业务快照一致”？

## 核对依据

- [SWS_RTE，PDF 第 150 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_RTE.pdf#page=150)：§4.2.2.6.1.4，Category 2 Runnable 与 Extended Task
- [SWS_RTE，PDF 第 144 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_RTE.pdf#page=144)：RTEEvent、WaitPoint 与异步结果相关事件
- [SWS_RTE，PDF 第 737 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_RTE.pdf#page=737)：§5.6.14 Rte_Result
- [SWS_RTE，PDF 第 779 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_RTE.pdf#page=779)：§5.6.37 Rte_IsUpdated
- [TPS_SoftwareComponentTemplate](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_SoftwareComponentTemplate.pdf)：SwcModeSwitchEvent、RunnableEntity、WaitPoint 元模型

---

**上一篇** → [[02-模式管理EcuM与BswM]]
**下一篇** → [[04-OS与调度]]
**相关** → [[05-RTE运行时环境]]
**返回** → [[AUTOSAR知识地图]]
