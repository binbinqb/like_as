---
title: 两阶段开发与 OEM 供应商分工
aliases: [两阶段开发, Two phase development, OEM供应商分工]
tags: [方法论, 协作]
source: [TR_Methodology]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# 两阶段开发与 OEM 供应商分工

> [!note] 项目上下文
> 未经本轮实际工程输入验证的“现状”、器件、数量和工具信息，均按示例或待确认假设阅读；不代表已审查 SDK、原理图、DBC 或现有业务代码。


> [!tip] 结论
> AUTOSAR 的方法论不是纯技术设计，它**把汽车行业的组织关系写进了标准**：
> OEM 定义整车系统并切出子系统，供应商并行开发各自的 ECU。
> 产物（Extract）是技术交付与接口约束；法律效力取决于实际合同，不能由技术标准直接推导。

## 一、官方对分工的描述

> `[TR_METH_01047]` **Two phase development approach**
> The two phase approach is used when there is an **organizational separation of responsibility**, where the **primary organization (usually OEM)** defines the overall system in the first phase, and several other organizations (usually suppliers) define the **subsystems in parallel** during the second phase.
> In this case, the primary organization hands over **System Extracts**, which represent the subsystems of the whole system.

关键短语：**organizational separation of responsibility**（责任的组织性分离）。

这不是"为了并行而并行"，而是**责任边界决定产物边界**。

## 二、责任矩阵

| 活动 | OEM | Tier-1 | Tier-2 |
|---|---|---|---|
| 整车功能定义 | ✅ 主责 | 参与 | — |
| 系统架构（拓扑、网络） | ✅ 主责 | 参与 | — |
| **System Extract 切分** | ✅ 主责 | — | — |
| ECU System Description | 审核 | ✅ 主责 | — |
| SWC 设计与实现 | — | ✅ 主责 | 参与 |
| BSW 配置 | — | ✅ 主责 | — |
| 底层驱动/芯片 | — | 集成 | ✅ 主责 |
| 集成测试 | ✅ 验收 | ✅ 执行 | — |
| 标定 | 定义目标 | ✅ 执行 | — |

> [!note] Tier-1 的真实位置
> 你（BCM 供应商）在中间：
> - 上接 OEM 的 System Extract（要求）
> - 下接芯片/BSW 供应商（Tier-2）
> - **两头都是"契约关系"，两头都不能随便改**

## 三、信息可见性：三层防火墙

> `[TR_METH_01048]` The overall system defines the major **public ECUs** and topologies, and the subsystem design contributes by adding **private ECUs** and networks.
> **portions defined within a subsystem are not directly visible to any other subsystem or to the overall system.**

```
┌─────────────────────────────────────────────────┐
│                 Overall System (OEM)             │
│  可见：所有 Public ECU、公共网络、公共接口          │
├──────────────────┬──────────────────────────────┤
│  Subsystem A     │  Subsystem B                  │
│  ┌────────────┐  │  ┌────────────┐               │
│  │ Public ECU │◀─┼─▶│ Public ECU │  可见         │
│  ├────────────┤  │  ├────────────┤               │
│  │Private ECU │  │  │Private ECU │  互相不可见    │
│  │ 私有网络    │  │  │ 私有网络    │               │
│  └────────────┘  │  └────────────┘               │
└──────────────────┴──────────────────────────────┘
```

| 层级 | 可见性 | 设计自由度 |
|---|---|---|
| Public ECU | 全体可见 | **低**（接口被冻结） |
| Public 网络 | 全体可见 | 低 |
| Private ECU | 仅本子系统 | **高** |
| 私有网络 | 仅本子系统 | 高 |
| 子系统内部 SWC 结构 | 仅本子系统 | 高 |

> [!important] 这条规则的双重作用
> 1. **商业保护**：供应商的内部实现是商业机密
> 2. **复杂度控制**：没人需要理解整个系统的所有细节
>
> 这也是为什么 System Extract 是"切片"而不是"全量"。

## 四、交付契约的四个要素

System Extract 作为契约，必须明确四件事：

| 要素 | 内容 | 缺失后果 |
|---|---|---|
| **接口** | 所有跨边界的 Port、数据类型、单位 | 供应商猜接口，集成失败 |
| **行为** | 时序要求、超时、失效处理 | 双方理解不一致 |
| **资源** | 该 ECU 可用的总线带宽、诊断地址 | 资源冲突 |
| **验收标准** | 怎么算"满足要求" | 扯皮 |

### 接口描述的粒度

| 层级 | 内容 | 谁需要 |
|---|---|---|
| 信号级 | 信号名、位宽、分辨率、范围、单位 | 集成工程师 |
| 语义级 | 物理量含义、有效范围、失效值 | SWC 开发者 |
| 时序级 | 周期、超时、抖动要求 | 系统工程师 |

> [!warning] 最常见的契约缺陷
> **只给了 DBC，没给语义。**
> DBC 里有 `Sig_LightBrightness: 8 bit, factor 0.5, range 0-127.5`，
> 但没有说"127.5 表示什么？是百分比还是 lux？失效值是多少？"
> 结果：供应商按"百分比"实现，OEM 期望"lux"，集成时数据全错。

## 五、两阶段开发的三种变体

### 变体 1：标准两阶段

```
Phase 1 (OEM):     系统定义 → System Extract
Phase 2 (供应商):   ECU System Description → 实现 → 交付
```

### 变体 2：多级供应链

```
OEM → System Extract → Tier-1
Tier-1 → 再切分 → System Extract' → Tier-2
```

> 注意：多级组织可采用相似的切分与映射，但具体交付物按实际分工约定，不要求每次采购都产生同类 Extract。

### 变体 3：平台化（OEM 与供应商长期合作）

```
OEM 定义平台级接口（跨车型稳定）
供应商建平台化 ECU System Description（自己的架构）
每个车型只改配置（post-build）
```

这种模式下，**System View Mapping 是核心资产**（因为它连接了 OEM 接口和供应商平台）。

## 六、这个分工模式带来的工程现实

### 现实 1：你的架构自由度被切成两半

| 自由度 | 说明 |
|---|---|
| **高** | 内部 SWC 怎么分、用什么算法、怎么调度 |
| **低** | 对外接口、通信矩阵、诊断服务、时序要求 |
| 由适用要求约束 | 已确认的 OEM／协议／法规要求；不预设全部 UDS 服务均受法规强制 |

> [!tip] 判断方法
> 问："这个改动，OEM 会不会知道？"
> - 会 → 低自由度，要走变更流程
> - 不会 → 高自由度，自己决定

### 现实 2：变更成本沿链条放大

```
OEM 改 1 个信号
  → Extract 更新（1 天）
  → 供应商重新映射（3 天）
  → 重新配置生成（1 天）
  → 回归测试（1 周）
  → 台架验证（1 周）
```

**放大倍数约 20~50 倍。**

这就是为什么 OEM 的通信矩阵一旦冻结就极难改 —— 不是不愿意，是成本太高。

### 现实 3：接口文档的质量决定项目成败

| 接口文档质量 | 项目表现 |
|---|---|
| 完整、精确、有示例 | 集成一次通过 |
| 有遗漏但可澄清 | 集成反复，但能收敛 |
| 模糊、有歧义 | **集成阶段返工，进度崩盘** |

> [!important] 一条经验
> **在接口定义上多花 1 天，能在集成阶段省 1 周。**
> 接口评审是所有评审里 ROI 最高的。

## 七、对 BCM 项目的直接建议

| 场景 | 建议 |
|---|---|
| 收到 OEM 的 DBC/诊断规范 | 逐条核对语义（单位、失效值、超时），有疑问**在开发前**提出 |
| 内部 SWC 分解 | 保留自己的架构自由，不要照抄 OEM 的功能清单 |
| 接口变更 | 建立变更记录（谁、何时、为什么），并评估影响链 |
| 与 OEM 的接口争议 | 用"要求 vs 方案"框架沟通：OEM 提要求，你提方案 |

### 一个实用的"契约检查表"

每次收到 OEM 输入，检查：

| # | 检查项 | 通过标准 |
|---|---|---|
| 1 | 所有信号有单位 | ✅ |
| 2 | 所有信号有范围 | ✅ |
| 3 | 所有信号有失效值 | ✅ |
| 4 | 所有周期报文有周期和超时 | ✅ |
| 5 | 所有诊断服务有会话/安全要求 | ✅ |
| 6 | 所有 DTC 有触发/恢复条件 | ✅ |
| 7 | 电源模式定义清楚 | ✅ |
| 8 | 唤醒/睡眠时序明确 | ✅ |

**这 8 条里任何一条缺失，都会在集成阶段变成 bug。**

## 八、自检

1. 为什么 System Extract 要"切"而不是"给全量"？
2. "要求 vs 方案"的框架，怎么用在和 OEM 的接口争议上？
3. 你的项目里，哪些设计决策属于"高自由度"，哪些属于"零自由度"？

---

**上一篇** → [[05-SystemExtract与ECUExtract]]
**下一篇** → [[07-ARXML产物格式]]
**返回** → [[AUTOSAR知识地图]]


## 原文入口与审查范围

- [TR_Methodology](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_Methodology.pdf)

> [!note] 阅读边界
> 原文入口用于继续核对；定向修正以审查记录为准，未逐条验证的解释和示例不因添加链接而自动成为官方结论。
