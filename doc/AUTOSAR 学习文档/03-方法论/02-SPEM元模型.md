---
title: SPEM 元模型
aliases: [SPEM, Methodology Library, 方法论元模型]
tags: [方法论, 理论]
source: [TR_Methodology]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 结构与引用检查；正文解释不视为逐条合规认证
review_basis: AUTOSAR CP R25-11 本地资料
---

# SPEM 元模型

> [!note] 项目上下文
> 未经本轮实际工程输入验证的“现状”、器件、数量和工具信息，均按示例或待确认假设阅读；不代表已审查 SDK、原理图、DBC 或现有业务代码。


> [!tip] 结论
> AUTOSAR 方法论不是"流程建议"，而是用 **SPEM 2.0**（Software & Systems Process Engineering Metamodel）形式化定义的**可执行流程模型**。
> 每个任务、每个产物、每个角色都被建模成有属性的对象，所以才能被工具链驱动。

## 一、为什么方法论需要元模型

**问题**：如果方法论写成自然语言文档，会怎样？

| 后果 | 说明 |
|---|---|
| 无法验证完整性 | 不知道某个 Task 的输入是否都有产出者 |
| 无法工具化 | 工具不知道"下一步该做什么" |
| 无法裁剪 | 不同项目要走不同路径，文字无法表达分支 |
| 无法度量 | 不知道进度、不知道谁在做什么 |

**解法**：用元模型把流程"数据化"。

## 二、两层结构

```
Methodology（方法论）
├── Methodology Library（方法库）        ← 可复用的"素材"
│   └── Methodology Library Element
│       ├── Task Definition             任务定义
│       ├── Work Product Definition     产物定义
│       ├── Role Definition             角色定义
│       ├── Tool Definition             工具定义
│       └── Guidance                    指导（当前未使用）
│
└── Use Case Specifications（用例规范）   ← 把素材"编排"成流程
    ├── Activity                        活动（组织 Task）
    └── Capability Pattern              能力模式（可复用的流程片段）
```

> [TR_METH_01007] The Methodology Library defines the Methodology Library Elements of every method pattern such as Roles, Tasks, and Work Product Definitions.
> [TR_METH_01009] The Methodology Library and the Methodology Library Elements correspond to the **Method Content** and **Method Content Elements** in the **SPEM meta model**.

## 三、五类库元素

### 3.1 Task Definition（任务定义）

> `[TR_METH_01011]` a Task Definition is an **assignable unit of work** that is being performed by specific Roles.
> The duration of a task is generally **a few hours to a few days**. Tasks usually generate one or more work products.
> Each Task is associated to **input and output Work Products**. Inputs are differentiated in **mandatory and optional** inputs.

| 属性 | 说明 | 例子（"配置 BSW 与 RTE"） |
|---|---|---|
| 名称 | 任务标识 | Configure BSW and RTE |
| 目的 | 达成什么目标 | 产出可编译的 BSW/RTE 配置 |
| 执行角色 | 谁做 | ECU Integrator |
| 输入（必需） | 一定要有的 | ECU Extract |
| 输入（可选） | 有则更好 | 时序约束 |
| 输出 | 产出什么 | ECU Configuration |
| 使用工具 | 用什么 | 配置工具 |
| 步骤 | 怎么做 | 分步骤说明 |

> `[TR_METH_01012]` A Task has a clear purpose ... It provides complete **step-by-step explanations** of doing all the work.
> This description is **completely independent of when in a process lifecycle** the work would actually be done.
> **It does not describe when what work is being done, but describes all the work that gets done.**

> [!important] Task 是"能力"不是"日程"
> Task 定义的是"这件事怎么做"，不是"这件事什么时候做"。
> 同一个 Task 可以在项目里被调用多次，每次侧重不同步骤。
> `[TR_METH_01013]` ... it provides the information which pieces of the Task will actually be performed at any particular point in time.

### 3.2 Work Product Definition（产物定义）

产物是 Task 的输入/输出，有**生命周期状态**。

| 属性 | 说明 |
|---|---|
| 名称 | 产物标识 |
| 描述 | 是什么 |
| 生命周期状态 | Draft / Submitted / Approved / ... |
| 负责角色 | 谁维护 |
| 前置产物 | 依赖哪些上游产物 |

**AUTOSAR 里的典型 Work Product**：

| 产物 | 格式 | 生产者 | 消费者 |
|---|---|---|---|
| Abstract System Description | ARXML | 系统架构师 | VFB 设计 |
| VFB System Description | ARXML | 软件架构师 | 系统设计 |
| System Description | ARXML | 系统工程师 | Extract 生成 |
| System Extract | ARXML | OEM | 供应商 |
| ECU Extract | ARXML | 集成工程师 | ECU 配置 |
| ECU Configuration | ARXML | 集成工程师 | 生成器 |
| RTE 代码 | C | RTE 生成器 | 编译器 |
| BSW 配置代码 | C | 配置生成器 | 编译器 |
| 可执行文件 | ELF/HEX | 编译器 | 测试 |

### 3.3 Role Definition（角色定义）

标准里定义的角色（部分）：

| 角色 | 职责 |
|---|---|
| System Architect | 系统架构、拓扑、映射 |
| Software Architect | SWC 分解、接口设计 |
| SWC Developer | 实现 SWC、Runnable |
| BSW Integrator | 配置 BSW |
| ECU Integrator | 集成、生成、构建 |
| Tester | 测试 |

> [!note] 角色 vs 岗位
> 一个岗位可能承担多个角色（小公司里"架构师 + 集成"常是同一人）。
> 但**角色必须被显式分配**，否则 Task 没有执行者。

### 3.4 Tool Definition（工具定义）

| 工具类 | 用途 |
|---|---|
| 建模工具 | 编辑 ARXML（System Descr / SWC Descr） |
| 配置工具 | ECU Configuration |
| 生成器 | RTE / BSW 代码生成 |
| 编译器/链接器 | 构建 |
| 测试工具 | HIL / 单元测试 |

> [!warning] 工具链是 AUTOSAR 落地的真正门槛
> 标准只定义"产物格式"，不定义"工具怎么用"。
> 实际项目里，**工具链的选型、license、版本兼容**往往比技术本身更耗时间。
> 开源工具／实现是否适用，需检查实际版本、能力、许可和维护情况；本文不将某软件库等同于完整方法论工具链。

### 3.5 Guidance（指导）

> `[TR_METH_01010]` ... Guidance（当前未使用）
> 脚注：The Guidance is currently **not used** in the AUTOSAR Methodology. It may be used in future AUTOSAR releases.

标准预留了"最佳实践/指导"这个元素，但还没用。所以**最佳实践不在标准里**，在本库里。

## 四、Use Case 层：把 Task 编排成流程

### 4.1 Activity（活动）

> `[TR_METH_01011 脚注]` The RS_Methodology document uses the term "Activity" when addressing process elements in general.
> In this document the atomic process elements are called "Tasks", whereas an "Activity" is used to **organize tasks and to define processes**.

| 层级 | 含义 |
|---|---|
| Activity | 一组 Task 的组织单元（如"开发系统"） |
| Task | 原子工作单元（如"生成 ECU Extract"） |

### 4.2 Capability Pattern（能力模式）

**可复用的流程片段**。

| 例子 | 说明 |
|---|---|
| "两阶段开发模式" | OEM 定义系统 + 供应商定义子系统 |
| "配置类处理模式" | Pre-compile / Link-time / Post-build 的处理流程 |
| "E2E 保护配置模式" | 端到端保护的配置流程 |

好处：同一模式可在不同项目、不同用例里复用。

## 五、Task 的图形化表示

标准用 SPEM 图表达 Task：

```
        ┌──────────────┐
WorkProduct1 ──input──▶│              │
WorkProduct2 ──input──▶│    Task      │──output──▶ WorkProduct3
                        │              │
     Role ──performs──▶ │              │──used tool──▶ Tool1
                        └──────────────┘
```

| 关系 | 含义 |
|---|---|
| `«input»` | Task 消费的产物（0..*） |
| `«output»` | Task 产出的产物（0..*） |
| `«inoutput»` | 既消费又产出的产物（0..*） |
| `«performs»` | 执行该 Task 的角色 |
| `«used tool»` | 使用的工具 |

> [!tip] `«inoutput»` 是个有用概念
> 表示"这个产物被读取、修改、写回"。
> 典型例子：**ECU Configuration**（配置工具读取、修改、保存）。

## 六、这对你意味着什么

### 6.1 如果你的项目要"像 AUTOSAR 一样跑"

| 要求 | 落地做法 |
|---|---|
| Task 明确 | 每个开发步骤写成"输入→处理→输出" |
| 产物明确 | 每份文档/配置有格式、有 owner、有生命周期 |
| 角色明确 | 谁产出、谁评审、谁批准 |
| 工具明确 | 每类产物用什么工具编辑 |
| 可追溯 | 每个产物能追到上游 |

### 6.2 一个最小可行的"方法库"

即使不引入 ARXML 工具，也可以借用这个框架：

| 你的 Task | 输入 | 输出 | 角色 |
|---|---|---|---|
| 定义通信矩阵 | DBC / 需求 | `cfg_can_matrix.h` | 系统工程师 |
| 定义 HAL 接口 | 硬件手册 | `hal_*.h` | 架构师 |
| 实现 HAL 平台 | `hal_*.h` + SDK | `hal_*_cvm014x.c` | 驱动工程师 |
| 配置表生成 | Excel / 脚本 | `cfg_*.c/h` | 工具链 |
| 集成验证 | 全部产物 | 测试报告 | 测试 |

> [!important] 关键洞见
> **"产物链"比"工具"重要。**
> 你可以不用 ARXML，但必须有明确的"谁产出什么、给谁用"。
> 否则项目一大就失控 —— 这正是 [[03-Mini-AUTOSAR分层映射]] 要解决的。

## 七、自检

1. Task 和 Activity 的区别是什么？
2. 为什么 Task 要"与生命周期阶段无关"？
3. `«inoutput»` 关系在什么场景下最典型？

---

**上一篇** → [[01-方法论总览-V模型产物链]]
**下一篇** → [[03-抽象系统描述]]
**返回** → [[AUTOSAR知识地图]]


## 原文入口与审查范围

- [TR_Methodology](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_Methodology.pdf)

> [!note] 阅读边界
> 原文入口用于继续核对；定向修正以审查记录为准，未逐条验证的解释和示例不因添加链接而自动成为官方结论。
