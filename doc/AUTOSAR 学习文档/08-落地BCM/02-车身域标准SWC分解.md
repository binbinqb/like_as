---
title: 车身域标准 SWC 分解
aliases: [车身域分解, Body Comfort SWC, 功能分解]
tags: [落地, BCM, 核心]
source: [EXP_AIBodyAndComfort]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# 车身域标准 SWC 分解

> [!tip] 结论
> AUTOSAR 官方给了车身域的**参考 SWC 分解**，它揭示了一个可复用的**五角色模式**：
>
> | 角色 | 职责 | 是否可复用 |
> |---|---|---|
> | **Manager** | 核心逻辑（状态机、决策） | 每个功能一个 |
> | **HMI** | 用户输入采集（开关/按键） | 按功能分组 |
> | **Sensor** | 传感器信号处理 | 按传感器类型 |
> | **Actuator** | 执行器驱动 | **高度可复用** |
> | **Adapter** | 适配/使能控制 | 按车型差异 |
>
> 五角色是本文对参考分解的归纳，不是每个功能都必须实现五个独立 SWC 或五组文件。

## 一、官方的分解原则

> This design standard is the AUTOSAR-architecture (RTE-view) for Software Compositions.
> It provides a decomposition into SW-Cs and a list of **standardized interfaces** related to each functionality.
> This decomposition is **limited in granularity to**:
> - **sensor components**
> - **adapter components**
> - **the core functionality**
> - **actuator components**

> The intent is for the decomposition to get **not to atomic SW-Cs but to "purchasable" SW-Cs** ...
> All interfaces between SW-Cs from **different vendors** should be standardized.

> The function components from Body and Comfort domain are identified according to:
> - the **controlled group of actuators** (motors, bulbs and other special devices)
> - **type of operations** (car access, lighting, comfort, acoustic signalling and other indirect operations like Terminal clamp control or battery monitoring)

**两条划分依据**：

| 依据 | 说明 | 例子 |
|---|---|---|
| **受控执行器组** | 控制什么就分什么 | 灯光组、电机组 |
| **操作类型** | 干什么类型的事 | 进入、照明、舒适、声音 |

## 二、五角色模式（核心）

把所有功能拆开看，会发现反复出现这五类组件。

### 2.1 Manager（核心逻辑）

| 特征 | 说明 |
|---|---|
| 职责 | 状态机、决策、协调 |
| 命名 | `<功能>Manager` / `<功能>Master` |
| 数量 | 每个功能域一个 |
| 是否再分解 | 官方标"not further broken down"（不再细分） |

**实例**：

| 组件 | 功能域 |
|---|---|
| `WiperWasherManager` | 雨刮洗涤 |
| `MirrorAdjustManager` | 后视镜调节 |
| `InteriorLightManager` | 内灯 |
| `CentralLockingMaster` | 中控锁 |
| `SeatAdjustManager` | 座椅调节 |

> [!important] "not further broken down" 的含义
> 原文："Comments 'not further broken down' and 'Non atomic SW-C' mean that this standardization does **not describe it in a more precise level**.
> **During the implementation, this SW-C might be further decomposed.**"
>
> 也就是说：**标准只规定"这里有一个 Manager"，不规定它内部怎么拆。**
> 你实现时想拆成 5 个子模块也行，但对外还是一个 SW-C。

### 2.2 HMI（用户输入）

| 特征 | 说明 |
|---|---|
| 职责 | 采集驾驶员操作（开关、按键、旋钮） |
| 是否标准名 | ❌ "HMI" 是**非规范性描述**（官方明确说明） |
| 数量 | 按功能分组，可能多个 |

> Please note that "HMI" is used **only for non-normative description**.

**HMI 的四个职责**（这一段极有价值）：

> The purpose of the Sensor SW-C (HMI) is to ensure (as far as needed):
> - **filtering (debouncing)** e.g. calculation of **stable output values**
> - **conditioning** e.g. calculation of **average value**
> - **plausibility check** as basis for **failure detection** (implausible)
> - **failure detection** (but **no error-handling / error-compensation**) e.g. valid / not valid

| 职责 | 做什么 | **不做什么** |
|---|---|---|
| 滤波/去抖 | 输出稳定值 | — |
| 调理 | 求平均、换算 | — |
| 合理性检查 | 判断"不可能的值" | — |
| 故障检测 | 输出 valid/invalid | **❌ 不做错误处理/补偿** |

> [!important] 这条边界极其重要
> **HMI/Sensor 只负责"检测并标记"，不负责"处理"。**
> 处理（如降级、替代值、报警）属于 **Manager** 或应用层。
>
> 违反这条边界的后果：
> - Sensor 里写了降级逻辑 → 换车型要改 Sensor
> - Sensor 里做了报警 → 无法复用

### 2.3 Sensor（传感器）

| 特征 | 说明 |
|---|---|
| 职责 | 把物理量变成语义值 |
| 命名 | `<对象>Sensor` |
| 可复用 | ✅ 同一传感器可用于多个功能 |

**实例**：

| 组件 | 说明 |
|---|---|
| `RainSensor` | 雨量传感器（提供 RainAmountStatus） |
| `WasherFluidTank` | 洗涤液位（**实例化两次**，前后） |
| `InteriorLightSensor[IntrLiActr]` | 内灯相关传感器（占位符表示多种） |
| `LightSource` / `LightSensor` | 光照 |

> [!tip] `[占位符]` 的含义
> `LightSource[IntrLiActr]` 里的 `[IntrLiActr]` 是**占位符**，代表：
> - 单个光源（如 `CbnLiFrntCen` = 前排中间顶灯）
> - 一组光源（如 `LiForReadingGroup` = 阅读灯组）
>
> **同一组件类型，多个实例。**

### 2.4 Actuator（执行器）

| 特征 | 说明 |
|---|---|
| 职责 | 驱动执行器（灯、电机、加热器） |
| 可复用 | ✅✅ **高度可复用** |
| 命名 | `<对象>` / `Front<对象>` / `Rear<对象>` |

**实例（雨刮洗涤）**：

| 组件 | 复用情况 |
|---|---|
| `Washer` | 复用于前洗涤、后洗涤、大灯洗涤 |
| `FrontWasher` / `RearWasher` / `WasherHeadLamp` | 具体实例 |
| `Wiper` / `FrontWiper` / `RearWiper` | 同上 |
| `NozzleHeater` | **实例化多次**（前/后/大灯喷嘴加热） |

**执行器的两级设计**：

> It might be decomposed into a **light actuator type independent** and a **light actuator type dependent** component, where light actuator types include conventional bulbs, LEDs or other decompositions, which allow the switching of lights on a **more "generic" level**.

```
LightSource（类型无关：开/关/调光）
    ├── BulbLightSource（类型相关：灯泡特性）
    └── LedLightSource（类型相关：LED 特性、PWM 调光）
```

> [!important] 这个"类型无关/类型相关"的两级设计
> **换执行器类型（灯泡→LED）只改下层，上层不动。**
> 这正是 [[02-MCAL微控制器抽象层]] 的分层思想在应用层的应用。

### 2.5 Adapter（适配器）

| 特征 | 说明 |
|---|---|
| 职责 | 适配车型差异、使能控制、请求计算 |
| 命名 | `<功能>Adapter` / `EnableDisable<功能>` / `<功能>Evaluator` |
| 用途 | 把"变化的策略"隔离出来 |

**实例**：

| 组件 | 作用 |
|---|---|
| `EnableDisableWiperWasher` | 按车型需求管理雨刮功能的使能 |
| `AutoWipingEvaluator` | 计算自动雨刮请求（考虑光照、温度、车速） |
| `SeatAxisActuatorAdapter` | 座椅轴执行器适配 |
| `SeatAxisMemoryAdapter` | 座椅记忆适配 |
| `AutoAdjustUserRequestManager` | 自动调节请求管理 |

> [!tip] Adapter 的价值
> 把"车型相关的策略"从"通用逻辑"里剥离。
> 低配车型不需要自动雨刮 → 只需换一个 Adapter，Manager 不动。

## 三、六个功能域的分解

### 3.1 WiperWasher（雨刮洗涤）

```
WiperWasher（组合）
├── WiperWasherManager          ← 核心
├── HMI                          ← 开关输入
├── RainSensing（子组合）
│   ├── RainSensor               ← 传感器
│   └── AutoWipingEvaluator      ← 适配器
├── WasherFluidTank（×2）        ← 前后液位
├── EnableDisableWiperWasher     ← 适配器
├── Washer / FrontWasher / RearWasher / WasherHeadLamp
├── Wiper / FrontWiper / RearWiper
└── NozzleHeater（×N）
```

**外部依赖**：
- `ExteriorLight` → 提供外部亮度
- `TerminalClampControl` → 提供车辆状态
- `BatteryMonitor`（未来）→ 电池电压

### 3.2 CentralLocking（中控锁）

```
CentralLocking（组合）
├── CentralLockingMaster         ← 核心
├── HMI                          ← 开关输入
├── RemoteKey / KeylessAccess    ← 遥控/无钥匙（含个性化信息）
├── DoorLock                     ← 门锁状态 + 命令
├── KeyPadManager                ← 键盘请求
├── GloveBox / TankFlap          ← 其他锁块
└── Intra-Domain Interfaces      ← 域内接口
```

**DoorLock 的职责**：

> Out of the doorlocks the information of the **doorlock status** is generated as well as information on **mechanical keys**.
> **Lock-commands** as well as commands for **pull aids** and setting the **child-protection-mechanism** are also sent to the doors.

| 方向 | 内容 |
|---|---|
| 输入 | 门锁状态、机械钥匙状态 |
| 输出 | 锁命令、拉动辅助、儿童锁设置 |

### 3.3 InteriorLight（内灯）

```
InteriorLight（组合）
├── InteriorLightManager         ← 核心（不再细分）
├── HMI（InteriorLightSensor[...]）← 多个传感器
├── CentralLocking               ← 门锁状态
├── ExteriorLight                ← 外部亮度
├── AntiTheftSystem              ← 防盗状态
├── TerminalClampControl         ← 钥匙状态
├── Inter-Domain Interfaces      ← 跨域
├── BatteryMonitor（未来）
└── Actuators（LightSource[...]）← 多个光源
```

**关键**：内灯依赖**大量外部信息**（门锁、光照、防盗、电源）→ 典型的"信息汇聚型"功能。

### 3.4 SeatAdjustment（座椅调节）

```
SeatAdjustment（组合）
├── SeatAdjustManager            ← 核心
├── BodySensors（HMI）           ← 开关
├── Doors / KeylessAccess / RemoteKey  ← 个性化来源
├── AutoAdjustUserRequestManager ← 自动调节请求
├── SeatAxisActuatorAdapter      ← 执行器适配
├── SeatAxisActuator             ← 执行器
├── SeatAxisMemoryAdapter        ← 记忆适配
└── Inter-DomainInterfaces
```

**特点**：**按"轴"（axis）建模** —— 每个可调轴（前后、高低、靠背）一个执行器。

### 3.5 MirrorAdjustment（后视镜）

```
MirrorAdjustment
├── MirrorAdjustManager          ← 核心
├── HMI
│   ├── MirrorManualAdjustment   ← 手动调节
│   └── MirrorAutoAdjustment     ← 自动调节 + 记忆按钮
└── ProfileManager               ← 个性化（钥匙信息）
```

### 3.6 其他

| 功能 | 关键组件 |
|---|---|
| **AntiTheftSystem** | 防盗报警 |
| **TerminalClampControl** | KL15/KL30 状态 |
| **ProfileManager** | 个性化配置协调（**不在本文档范围**） |
| **BatteryMonitor** | 电池电压（**未来功能**） |
| **ExteriorLight** | 外灯 |

## 四、对 BCM 项目的直接应用

### 4.1 用五角色模式拆你的功能

以"近光灯控制"为例：

| 角色 | 你的组件 | 职责 |
|---|---|---|
| **HMI** | `LightSwitchAcq` | 采集开关，去抖，判断合理性和有效性 |
| **Sensor** | `AmbientLightSensor` | 光照强度采集（若是模拟量） |
| **Manager** | `LowBeamManager` | 决策：是否点亮、亮度、延时 |
| **Actuator** | `LowBeamActuator` | PWM 输出、故障检测 |
| **Adapter** | `AutoLightEnable` | 是否启用自动大灯（车型差异） |

### 4.2 分解检查清单

| # | 检查项 | 通过标准 |
|---|---|---|
| 1 | 核心策略有清晰归属吗 | 可以在本功能 .c 内实现，不强制独立 Manager 类/组件 |
| 2 | 输入采集与产品策略分开了吗 | 按复用和时序需要拆分，非强制独立 HMI 文件 |
| 3 | Sensor 里有没有做错误处理 | ❌ 不该有 |
| 4 | Actuator 是否可复用 | ✅ 同类型执行器共用一个 |
| 5 | 车型差异是否隔离在 Adapter | ✅ |
| 6 | 跨域依赖是否明确 | ✅ 列出外部输入 |

### 4.3 一个反面例子

```
需结合职责评估的合并实现：
LightControl（一个大组件）
├── 读开关
├── 判断逻辑
├── 驱动 PWM
└── 处理故障
```

**问题**：
- 开关采集不可复用（雾灯也要采集开关）
- PWM 驱动不可复用（转向灯也要 PWM）
- 无法单独测试

```
存在复用需求时可采用的分解：
├── LightSwitchAcq      （HMI，可复用于所有灯）
├── LowBeamManager      （逻辑）
├── HighBeamManager     （逻辑）
├── TurnSignalManager   （逻辑）
└── LightActuator       （Actuator，所有灯共用）
```

## 五、一个容易忽略的细节：接口的"数据品质"

> In addition, **all ports are described**, showing their **AUTOSAR data qualities**.
> **Invalidation (where needed) is defined as in-band invalidation.**
> **Init values are specified** where appropriate e.g. "off", "idle", "undefined", "unknown", ...

| 概念 | 说明 | 例子 |
|---|---|---|
| **数据品质** | 端口数据的有效性语义 | valid / invalid / init |
| **带内失效（in-band）** | 失效信息放在数据里（而非单独信号） | 用特殊值表示失效 |
| **初始值** | 启动时的值 | off / idle / undefined / unknown |

> [!important] "in-band invalidation" 的含义
> 不是用单独的一根信号表示"这个值无效"，而是**在数据本身里编码失效**。
> 好处：不需要额外信号，接口简单。
> 代价：必须保留一个"不可能的值"作为失效码。

→ 与 [[03-COM信号处理]] 的"失效值"一致。

## 六、自检

1. 五角色模式里的五类组件分别是什么？
2. HMI/Sensor 的职责边界在哪？为什么不做错误处理？
3. 为什么 Actuator 要分"类型无关"和"类型相关"两层？

---

**上一篇** → [[01-BCM在AUTOSAR中的定位]]
**下一篇** → [[03-Mini-AUTOSAR分层映射]]
**返回** → [[AUTOSAR知识地图]]


## 原文入口与审查范围

- [EXP_AIBodyAndComfort](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_AIBodyAndComfort.pdf)

> [!note] 阅读边界
> 原文入口用于继续核对；定向修正以审查记录为准，未逐条验证的解释和示例不因添加链接而自动成为官方结论。
