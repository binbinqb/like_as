---
title: 复杂驱动 CDD
aliases: [CDD, Complex Driver, Complex Drivers, 复杂驱动]
tags: [架构, 驱动]
source: [EXP_LayeredSoftwareArchitecture, EXP_CDDDesignAndIntegrationGuideline]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# 复杂驱动 CDD

> [!note] 项目上下文
> 未经本轮实际工程输入验证的“现状”、器件、数量和工具信息，均按示例或待确认假设阅读；不代表已审查 SDK、原理图、DBC 或现有业务代码。


> [!tip] 结论
> CDD 是 AUTOSAR 支持特殊设备、时序和迁移需求的扩展机制：一个"不被标准化、但可以和标准模块互相调用"的软件实体。
> 它的本质特征不是"位置特殊"，而是**上层接口可以带硬件依赖**——这是其他所有层都不允许的。

## 一、官方定义

> A Complex Driver is a software entity **not standardized by AUTOSAR** that can access or be accessed via AUTOSAR Interfaces and/or Basic Software Modules APIs.
> —— EXP_CDDDesignAndIntegrationGuideline, 5

> The Complex Drivers Layer **spans from the hardware to the RTE**.
> **Task**: Provide the possibility to integrate special purpose functionality, e.g. drivers for devices:
> - which are **not specified within AUTOSAR**,
> - with **very high timing constrains** or
> - for **migration purposes**
> **Properties**:
> - Implementation: might be **application, µC and ECU hardware dependent**
> - Upper Interface: might be **application, µC and ECU hardware dependent**
> —— EXP_LayeredSoftwareArchitecture

> [!important] 关键差异
> 对比其他层的 "Upper Interface: ... independent"，CDD 是**唯一**允许"上层接口也依赖硬件"的层。
> 这就是它的存在意义：**用可移植性换取能力**。

## 二、CDD 的四种合法用途

| 用途 | 说明 | 例子 |
|---|---|---|
| **1. 标准未覆盖的器件** | AUTOSAR 没有对应 SWS | 特殊传感器、专用 ASIC、非标外设 |
| **2. 极高时序要求** | 标准栈的分层开销无法接受 | 电机 FOC 控制、点火正时、高速 PWM 闭环 |
| **3. 复杂传感器评估** | 需要专用算法 + 直接中断 | 爆震检测、氧传感器泵电流控制 |
| **4. 迁移/遗留封装** | 把非 AUTOSAR 代码包进来 | 老平台代码平滑迁移 |

原文对"主目标"的表述：

> The main goal of the CDD is to implement **complex sensor evaluation and actuator control with direct access to the microcontroller using specific interrupts and/or complex microcontroller peripherals, external devices** (communication transceivers, ASIC...) to fulfill the special functional and timing requirements.
> In addition it might be used to implement enhanced services / protocols or **encapsulates legacy functionality** of a non-AUTOSAR system.
> Finally, the CDD can serve as **mechanism of migration**.

## 三、CDD 能连什么（官方给了完整清单）

CDD 的特殊之处：它**既能被标准模块调用，也能调用标准模块**。

```
              ┌─────────────┐
   SWC ──RTE──│             │──MCAL 模块（Adc/Spi/Can...）
              │     CDD     │──Memory Stack（NvM/MemIf）
   BswM ──────│             │──Watchdog Stack（Wdg/WdgM）
   EcuM ──────│             │──Communication Stack（PduR/CanIf/Com/ComM/Nm/TcpIp）
              │             │──XCP / DLT / Det / Dem / OS / StbM
              └─────────────┘
```

| 接口方向 | 对接对象 | 典型用途 |
|---|---|---|
| CDD → RTE/SWC | 应用组件 | 通过 Port 提供复杂功能 |
| SWC → CDD | 应用调用 | 应用请求 CDD 服务 |
| CDD → MCAL | Adc、Spi、Can、Icu | 复用底层驱动，不重复写寄存器 |
| CDD → Memory Stack | NvM / MemIf | 保存标定/状态数据 |
| CDD → Wdg Stack | Wdg / WdgM | 参与看门狗监督 |
| CDD → Comm Stack | PduR / CanIf / Com | 收发自定义报文 |
| CDD → Dem/Det | 错误上报 | 报故障/开发错误 |
| CDD → OS | 任务、事件、告警 | 调度 |
| BswM/EcuM → CDD | 模式控制 | CDD 参与模式管理 |

> [!warning] 最容易犯的错：CDD 里重复实现 MCAL
> 可用标准驱动满足需求时应优先复用；特殊时序可能需要 CDD 直接访问硬件，但必须明确资源归属、与标准驱动的冲突和初始化／并发规则。
> CDD 可以包括硬件访问，不是仅容纳算法；不能将普通驱动与 CDD 同时作为同一寄存器的无协调控制者。

## 四、CDD 的实现约束（不是完全自由）

> There are few constraints coming from AUTOSAR regarding CDD implementation. **At least**:
> - CDD shall respect the input specifications（通用需求、分层架构、BSW 通用规范等）
> - CDD shall **protect its critical resources** defining critical sections which can be handled by **SchM or OS** mechanisms
> - CDD mode may be manageable by **EcuM and BswM**
> - CDD may handle its memory sections using the **memory mapping mechanisms**
> - CDD may report its errors using **Det or Dem**

| 约束 | 具体要求 | 后果 |
|---|---|---|
| 遵守通用需求 | MISRA C、命名规范、错误处理 | 否则无法通过集成审查 |
| 临界区保护 | 用 SchM/OS 的 Exclusive Area，不自己关中断 | 自己关中断会破坏 OS 时序 |
| 模式管理 | 接受 EcuM/BswM 的模式控制 | 否则无法参与睡眠/唤醒 |
| 内存映射 | 用 MemMap.h 分段 | 否则无法控制 RAM/Flash 布局 |
| 错误上报 | 用 Det/Dem，不自己定义错误码体系 | 否则诊断无法统一 |

## 五、文件结构（官方推荐）

```
CDD_<MODULENAME>.c              # 主体（必需）
CDD_<MODULENAME>.h              # 唯一对外头文件（用户只 include 这个）
CDD_<MODULENAME>_Irq.c          # 中断函数
CDD_<MODULENAME>_Callout.c      # 回调函数
CDD_<MODULENAME>_Cfg.h/.c       # Pre-compile 配置
CDD_<MODULENAME>_Lcfg.c         # Link-time 配置对象
CDD_<MODULENAME>_PBcfg.c        # Post-build 配置对象
CDD_<MODULENAME>_Types.h        # 类型定义（可选）
```

> 命名规则遵循 `[SRS_BSW_00300]`（模块名 2~8 字母）与 `[SRS_BSW_00310]`（API 命名 `<Module>_<Service>()`）。
> 注意：CDD 的模块名前缀习惯用 `Cdd_`，如 `Cdd_Motor.c`。

## 六、User's Manual 必须写什么

`EXP_CDDDesignAndIntegrationGuideline` 6.1.1 列了完整清单，这份清单本身就是**CDD 交付物的验收标准**：

| # | 章节 | 内容 |
|---|---|---|
| 1 | 概述 | CDD 介绍与总览 |
| 2 | 功能操作 | 初始化、正常、关机、故障操作 |
| 3 | 与其他模块的关系 | 对 BSW/SchM/RTE 的依赖（如需要哪些 NvM 块、哪些临界区） |
| 4 | 文件结构与依赖 | 文件清单、包含关系 |
| 5 | 接口描述 | 名称、描述、**可重入性**、参数（名/类型/范围/取值）、返回值、配置类 |
| 6 | 非功能需求 | 时序与行为要求、资源占用、与其他模块的交互行为 |
| 7 | 错误 | Dem 错误、可选 Det 错误、调试变量 |
| 8 | 配置参数 | 名称、类型、范围、取值 |
| 9 | 内存映射需求 | Flash/RAM 分段要求 |
| 10 | 限制与未决问题 | 使用限制、open issues |
| 11 | 集成约束 | 对其他模块的要求 |
| 12 | 示例 | 用法示例 |

> [!tip] 这份清单可以直接当模板用
> 你写自己的 HAL/CDD 模块时，按这 12 项写文档，可形成有用的交付检查表，但不自动证明 AUTOSAR 合规。

## 七、CDD 的代价（必须量化）

| 代价 | 说明 |
|---|---|
| **可移植性取决于实现** | 隔离硬件访问并复用标准接口可限制迁移范围 |
| **无法被工具链验证** | 配置工具不认识它，时序/资源分析要手工做 |
| **集成风险集中** | 出问题往往在 CDD（因为它不受标准约束） |
| **测试成本高** | 需要专门的白盒测试 + 硬件在环 |
| **架构腐化入口** | 一旦开了口子，容易变成"什么都往 CDD 塞" |

> [!warning] CDD 准入检查表
> 引入 CDD 前，逐条回答：
> 1. 标准模块组合真的做不到吗？（列出尝试过的方案）
> 2. 时序要求具体是多少？（量化，如 < 50 µs）
> 3. 这部分代码能否被隔离到最小范围？（不要蔓延到业务层）
> 4. 换 MCU 时的重写成本是多少？（评估）
> 5. 谁负责维护？（明确 owner）
>
> 五条里有任何一条答不上来，就不要用 CDD。

## 八、BCM 项目里的 CDD 候选

| 功能 | 是否该用 CDD | 理由 |
|---|---|---|
| 普通车灯开关控制 | ❌ | 标准 Dio/Pwm + IoHwAb 足够 |
| 车灯 PWM 调光（渐变） | ⚠️ 看要求 | 若只需 100 Hz 软 PWM，标准 Pwm 可做；若要高频精确调光，考虑 CDD |
| LIN 从机特殊协议 | ⚠️ | 标准 LinIf 可做常规；私有协议扩展考虑 CDD |
| 无刷电机控制（如电子水泵） | ✅ | 高时序 + 专用算法 |
| 雨量传感器信号处理 | ⚠️ | 若为标准 LIN/模拟量，IoHwAb 即可；若为专用编码，CDD |
| 智能功率开关诊断（SPI） | ⚠️ | 标准 Spi + 自定义上层可做；若需快速故障响应，CDD |
| 老平台遗留代码封装 | ✅ | 迁移用途，正当 |

## 九、自检

1. CDD 和其他层最本质的区别是什么？（提示：看 Upper Interface 那行）
2. CDD 能不能自己关中断来实现临界区？为什么？
3. 你的项目里，有没有"事实上的 CDD"（即已经绕过了分层的东西）？


## 本轮核对依据

- [EXP_CDDDesignAndIntegrationGuideline](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_CDDDesignAndIntegrationGuideline.pdf)：CDD 接口、资源与集成限制

---

**上一篇** → [[05-RTE运行时环境]]
**下一篇** → [[07-BSW模块类型分类法]]
**相关** → [[02-MCAL微控制器抽象层]]
**返回** → [[AUTOSAR知识地图]]
