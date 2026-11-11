---
title: System Extract 与 ECU Extract
aliases: [System Extract, ECU Extract, ECU System Description, 系统摘取]
tags: [方法论, 协作]
source: [TR_Methodology]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# System Extract 与 ECU Extract

> [!tip] 结论
> 这两个概念是**组织边界的产物**：
> - **System Extract** = OEM 切给供应商的"子系统切片"（要求）
> - **ECU Extract** = 单颗 ECU 的"完整物料清单"（配置输入）
>
> 它们的真正价值：**让 ECU 开发可以在整车系统描述完成之前就开始。**

## 一、System Extract：切给供应商的切片

### 官方定义

> `[TR_METH_01047]` The primary organization (usually OEM) defines the overall system in the first phase, and several other organizations (usually suppliers) define the subsystems in parallel during the second phase.
> In this case, the primary organization hands over **System Extracts**, which represent the subsystems of the whole system.

> 2.5.3 Description: Generate for further development, a System Extract which represents the description of a part of the system (sub-system).
> **This allows a start of work on ECU's even if the system is not completely described.**

| 项 | 内容 |
|---|---|
| 生产者 | OEM / 一级供应商（primary organization） |
| 消费者 | 下级供应商 |
| 内容 | 子系统相关的 SWC、接口、连接（含跨边界连接） |
| 关键约束 | **只含该子系统可见的部分** |

### 一个关键限制

> `[TR_METH_01048]` The overall system defines the major **public** ECUs and topologies, and the subsystem design contributes by adding **private** ECUs and networks.
> Please note that **portions defined within a subsystem are not directly visible to any other subsystem or to the overall system.**

| 概念 | 含义 |
|---|---|
| **Public ECU** | OEM 定义的系统级 ECU，所有供应商可见 |
| **Private ECU** | 供应商在自己的子系统里加的 ECU，对外不可见 |
| **不可见性** | 子系统内部细节对其他子系统和总系统不可见 |

> [!important] 这就是"信息防火墙"
> 供应商 A 不知道供应商 B 内部怎么实现，只知道 B 对外的接口。
> **这既是商业保护，也是复杂度控制。**

### 子系统之间的连接

```
┌─────────────────┐         ┌─────────────────┐
│  子系统 A        │         │  子系统 B        │
│  ┌───────────┐  │  接口   │  ┌───────────┐  │
│  │ Public ECU│──┼─────────┼──│ Public ECU│  │
│  └───────────┘  │         │  └───────────┘  │
│  ┌───────────┐  │         │  ┌───────────┐  │
│  │Private ECU│  │  ✗ 不可见 │  │Private ECU│  │
│  └───────────┘  │         │  └───────────┘  │
└─────────────────┘         └─────────────────┘
```

## 二、ECU System Description：供应商的"方案"

### 两种做法（官方明确给了选项）

> `[TR_METH_01126]` **Using the System Extract as the structural basis**: The System Extract is taken as the structural basis for the ECU development. In this case the **System Extract becomes an ECU System Description**.

> `[TR_METH_01127]` **Creating a new structure**: A new structure is created as a basis for the ECU development. The newly created ECU System Description is **mapped to the initial System Extract**.
> For this purpose the task **Define System View Mapping** creates the initial **System View Mapping** artifact which is refined during the sub-system design.

> `[TR_METH_01078]` The different views are mapped by the **System View Mapping**.

| 做法 | 适用 | 优点 | 缺点 |
|---|---|---|---|
| **A. 直接用 Extract 结构** | 供应商内部结构与 OEM 一致 | 简单、无映射开销 | 被 OEM 结构绑死 |
| **B. 建新结构 + 映射** | 供应商有自己的架构习惯 | 保留内部架构自由 | 需要维护 System View Mapping |

> [!tip] 这是"要求 vs 方案"的具体体现
> - OEM 的 System Extract = **要求**（要这些功能、这些接口、这些时序）
> - 供应商的 ECU System Description = **方案**（我用这套结构实现）
> - **结构可以不同，只要满足要求**
>
> 这正是 [[06-两阶段开发与OEM供应商分工]] 的核心机制。

### 什么时候选 A，什么时候选 B

| 场景 | 建议 |
|---|---|
| 供应商是 OEM 的全资子公司 / 长期合作 | A（省事） |
| 供应商同时给多家 OEM 供货，有自己的平台 | **B**（保护平台复用） |
| 供应商内部有成熟的 SWC 库 | B |
| 项目周期紧、变更少 | A |
| 需要频繁同步 OEM 的结构变更 | A（B 的映射维护成本高） |

## 三、ECU Extract：单 ECU 的物料清单

### 官方定义

> 2.5.7 Purpose: This Activity provides an extract of the System description for **setting up an ECU Configuration** for specific ECU.
> Description: Generate the ECU Extract which is a basis for setting up the ECU configuration and further development on ECU level.
> **It can be generated either from a full system (System Configuration Description), a System Extract or an ECU System Description.**

| 项 | 内容 |
|---|---|
| 用途 | **ECU 配置的重要输入之一**；还需 SWC/BSW 描述、参数定义、实现约束与集成决定 |
| 来源 | 完整系统 / System Extract / ECU System Description（三选一） |
| 输出 | 单颗 ECU 的完整视图 |

### ECU Extract 包含的六个子提取

官方 Workflow 显示，ECU Extract 是由多个部分"拼"起来的：

| 子提取 | 内容 |
|---|---|
| **ECU Extract of Topology** | 该 ECU 相关的拓扑部分 |
| **ECU Extract for Communication** | 该 ECU 收发的所有 PDU/信号 |
| **ECU Extract of Data Mapping** | 数据类型映射 |
| **ECU Extract of VFB System** | 该 ECU 上的 SWC 及连接 |
| **ECU Extract of Rapid Prototyping Scenario** | 快速原型场景（可选） |
| **Flatten Software Composition** | **扁平化**后的软件组合 |

> [!important] "扁平化（Flatten）"是个关键动作
> 组合（Composition）是嵌套的，但 **ECU 配置需要扁平视图**。
> 扁平化 = 把所有嵌套的 Composition 展开成"该 ECU 上的所有原子组件 + 所有连接"。
> 这一步由工具自动完成，但理解它有助于排查"为什么配置里少了一个组件"。

### 从 Extract 到配置

```
ECU Extract
    │
    ├── SWC 实例 + 连接  ──→  RTE 配置
    ├── 通信需求（PDU）  ──→  Com / PduR / CanIf 配置
    ├── 诊断需求         ──→  Dcm / Dem 配置
    ├── NVM 需求         ──→  NvM 配置
    └── 硬件资源需求     ──→  Mcu / Port / Adc 配置
                              ↓
                        ECU Configuration
```

## 四、CpSoftwareCluster：本版本中的相关产物

除了 System Extract，还有 **CP Software Cluster Extract**：

> 2.5.6 Generate CpSoftwareCluster Extract

| 概念 | 含义 |
|---|---|
| **CpSoftwareCluster** | 一组可独立分发/部署的软件单元（含 SWC + BSW 部分） |
| 用途 | 支持"软件作为产品"的分发模式 |
| Extract | 把某个 Cluster 从系统里切出来 |

> [!note] 为什么会有这个概念
> 传统模式：整个 ECU 的软件一起交付。
> Cluster 模式：软件按"功能包"交付（如"诊断包""通信包"），支持跨 ECU 复用和独立升级。
> 这是 AUTOSAR 向"软件定义汽车"演进的痕迹。

## 五、三个 Extract 的对比

| | System Extract | ECU System Description | ECU Extract |
|---|---|---|---|
| **范围** | 子系统（可能多 ECU） | 单 ECU（供应商方案） | 单 ECU（配置输入） |
| **生产者** | OEM | 供应商 | 集成工程师/工具 |
| **是否含私有 ECU** | ❌ 不含 | ✅ 可含 | ✅ 含（扁平化后） |
| **结构** | OEM 结构 | 供应商结构（可不同） | 扁平结构 |
| **用途** | 交付/分工 | 设计依据 | **配置输入** |
| **关系** | 要求 | 方案 | 物料清单 |

## 六、BCM 项目里的对应

以下以供应商承接 OEM BCM 项目为假设例子，不作为当前组织关系与交付产物的确认：

| 阶段 | 谁 | 产出 |
|---|---|---|
| 1. OEM 定义整车系统 | Foton | System Description（含通信矩阵、诊断规范） |
| 2. OEM 切子系统 | Foton | **System Extract**（BCM 相关部分） |
| 3. 你建立自己的结构 | 你 | **ECU System Description**（你的 SWC 分解） |
| 4. 映射 | 你 | System View Mapping（你的 SWC ↔ OEM 的接口） |
| 5. 生成配置依据 | 工具/你 | **ECU Extract** |
| 6. 配置与实现 | 你 | 代码 + 配置 |

> [!important] 你实际在做的事
> 即使不用 ARXML，这个流程**逻辑上必须存在**：
> - OEM 给的 DBC/诊断规范 = 需求输入的一部分，不是完整 System Extract 的等价物
> - 你的 `cfg_can_matrix.h` / `dbc_comm` 层 = System View Mapping 的等价物
> - 你的 Mini-AUTOSAR 分层 = ECU System Description 的等价物
>
> **理解了这套逻辑，就知道"哪些是 OEM 的约束（不能改），哪些是自己的设计自由（可以改）"。**
> 详见 [[03-Mini-AUTOSAR分层映射]]

## 七、Extract 环节最容易出的问题

| 问题 | 症状 | 根因 |
|---|---|---|
| Extract 缺跨边界连接 | 供应商说"我没收到这个信号" | OEM 切割时漏了 |
| Extract 含了不该有的信息 | 供应商看到了别家子系统细节 | 切割粒度错误 |
| 版本不同步 | OEM 改了矩阵，供应商没收到 | 变更管理缺失 |
| 结构映射丢失 | 供应商的 SWC 没对上 OEM 的接口 | System View Mapping 不完整 |
| 扁平化后组件缺失 | 配置里少了某个 SWC | Composition 嵌套层次太深/配置错误 |

> [!warning] 变更管理是最大的坑
> OEM 改一条报文，影响链是：
> Extract → ECU System Description → ECU Extract → 配置 → 生成代码 → 测试
> **任何一环没同步，就会出现"代码和矩阵不一致"，且往往到台架才暴露。**

## 八、自检

1. System Extract 为什么"不含私有 ECU"？
2. 路径 A（直接用 Extract 结构）和路径 B（建新结构）各适合什么场景？
3. "扁平化"做了什么？为什么配置需要扁平视图？

---

**上一篇** → [[04-VFB系统描述与系统设计]]
**下一篇** → [[06-两阶段开发与OEM供应商分工]]
**返回** → [[AUTOSAR知识地图]]


## 原文入口与审查范围

- [TR_Methodology](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_Methodology.pdf)

> [!note] 阅读边界
> 原文入口用于继续核对；定向修正以审查记录为准，未逐条验证的解释和示例不因添加链接而自动成为官方结论。
