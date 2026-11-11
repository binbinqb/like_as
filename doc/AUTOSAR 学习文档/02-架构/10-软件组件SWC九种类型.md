---
title: 软件组件 SWC 九种类型
aliases: [SWC, SoftwareComponent, 软件组件类型]
tags: [架构, 组件]
source: [TPS_SoftwareComponentTemplate]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# 软件组件 SWC 九种类型

> [!tip] 结论
> AUTOSAR 定义了 **9 种** SwComponentType，其中 **7 种是原子类型**（其执行实例受 ECU 映射约束，ServiceProxy 有专门的多 ECU prototype 映射规则），**1 种是组合**，**1 种是参数容器**。
> 分类依据是"**它代表什么**"：应用逻辑？硬件？服务？配置？

## 一、类型总览

```
SwComponentType
├── AtomicSwComponentType（原子，不可再分，落一颗 ECU）
│   ├── ApplicationSwComponentType            应用软件
│   ├── SensorActuatorSwComponentType         传感器/执行器
│   ├── EcuAbstractionSwComponentType         ECU 抽象
│   ├── ComplexDeviceDriverSwComponentType    复杂驱动
│   ├── ServiceSwComponentType                服务
│   ├── ServiceProxySwComponentType           服务代理
│   └── NvBlockSwComponentType                NVM 块
├── ParameterSwComponentType                  参数/标定（无行为）
└── CompositionSwComponentType                组合（可嵌套）
```

## 二、七种原子类型逐一说明

### 2.1 ApplicationSwComponentType（应用）

> The ApplicationSwComponentType is used to represent the **application software**.

| 项 | 内容 |
|---|---|
| 代表什么 | 纯业务逻辑 |
| 典型内容 | 灯光控制、雨刮逻辑、门锁逻辑 |
| 能访问硬件吗 | ❌ 只能通过 Port |
| 数量 | 项目中最多 |
| BCM 例子 | `LightControl`、`WiperControl`、`CentralLocking` |

### 2.2 SensorActuatorSwComponentType（传感器/执行器）

> each hardware sensor/actuator is coupled to a SensorActuatorSwComponentType.
> [constr_1144] SensorActuatorSwComponentType, EcuAbstractionSwComponentType, and ComplexDeviceDriverSwComponentType may only reference a **HwType**.

| 项 | 内容 |
|---|---|
| 代表什么 | **物理世界的接入点** |
| 关键能力 | 可引用 ECU Resource 描述中的 `HwType`（真实硬件元素） |
| 端口模式 | 一个 Port 从 ECU Abstraction 取硬件信号；另一个 Port 把物理值提供给 RTE |
| BCM 例子 | `SeatHeating`（座椅加热）、`RainSensor`（雨量传感器） |
| 意义 | **软件模型与硬件模型的绑定点**，让"软件里的传感器"能对应到"BOM 里的那个器件" |

> [!note] 为什么需要这个类型
> 因为 AUTOSAR 要求"**软件描述**"与"**ECU 资源描述**"能对上。
> 你说"我有一个温度传感器"，工具要知道它接在哪个引脚、什么型号 —— `HwType` 引用就是这根线。

### 2.3 EcuAbstractionSwComponentType（ECU 抽象）

| 项 | 内容 |
|---|---|
| 代表什么 | 板级抽象逻辑，作为 SWC 存在 |
| 用处 | 把 IoHwAb 的某些功能以组件形式建模 |
| 能引用硬件 | ✅ `hardwareElement` → `HwType` |
| 实际使用 | 较少（多数项目直接用 BSW 的 IoHwAb，不建模成 SWC） |

### 2.4 ComplexDeviceDriverSwComponentType（复杂驱动）

| 项 | 内容 |
|---|---|
| 代表什么 | 以组件形式存在的 CDD |
| 用处 | 让 CDD 能通过 RTE 与 SWC 交互 |
| 能引用硬件 | ✅ `hardwareElement` → `HwType` |
| 与 BSW 侧 CDD 的区别 | 这个是通过 RTE 暴露的；BSW 侧的 CDD 是模块 |

→ 参见 [[06-复杂驱动CDD]]

### 2.5 ServiceSwComponentType（服务）

| 项 | 内容 |
|---|---|
| 代表什么 | **由 BSW 提供的服务**，以组件形式呈现给应用 |
| 典型 | NvM 服务端口、Dem 服务端口、Dcm、EcuM 模式 |
| 谁实现 | BSW 模块（不是应用开发者） |
| 应用怎么用 | 通过 `Standardized AUTOSAR Interface` 连到它的 Port |

> [!important] 这解释了"应用怎么访问 NVM"
> 应用不会 `#include "NvM.h"`。它通过配置的标准 NvM service port 连接服务组件；`NvDataInterface` 则是另一种 NvBlock 数据接口机制，
> RTE 生成代码后，应用调 `Rte_Call_Pp_NvWrite(...)`，RTE 内部调 `NvM_WriteBlock()`。

### 2.6 ServiceProxySwComponentType（服务代理）

这里不是“本地代理任意远程 BSW RPC”的一般模型。TPS §11.3 以车辆模式请求为例：代理通过本地 service port 访问本 ECU 的服务，为来自其他 ECU 的请求提供连接。

`[TPS_SWCT_01416]` 规定此类 prototype 可映射到多个 ECU，在各 ECU 生成面向当地服务的实例；这是对“原子类型只能映射一个 ECU”的重要特殊场景，不能用简化口号覆盖。

`[constr_2018]` 规定其远程通信只允许 SenderReceiverInterface 的 RPort、1:n 场景；两个 ServiceProxy prototype 之间也不允许连接。它不是任意双向服务转发器。

### 2.7 NvBlockSwComponentType（NVM 块）

| 项 | 内容 |
|---|---|
| 代表什么 | 一块 NVRAM 数据的软件视图 |
| 用处 | 让应用以"数据块"方式访问 NVM，而不是调 API |
| 特点 | 通常**没有 Runnable**（除非需要代理 NvM 服务端口） |

> 原文注：`NvBlockSoftwareComponent does not require any RunnableEntity if there is no need to proxy any NvMService port or NvMAdmin port.`
> —— TR_VFB, 3.8

| 对比 | NvBlock SWC 方式 | Service 端口方式 |
|---|---|---|
| 应用看到 | 一块有结构的数据（自动同步） | 一组 API（显式读写） |
| 适用 | 周期性保存的状态数据 | 事件驱动的存储操作 |
| 配置复杂度 | 较高 | 较低 |

## 三、ParameterSwComponentType（参数容器）

> [constr_1092] The following restrictions exist for a ParameterSwComponentType:
> - it shall **never aggregate a SwcInternalBehavior**
> - the only aggregated PortPrototypes shall be **PPortPrototypes of type ParameterInterface**

| 项 | 内容 |
|---|---|
| 代表什么 | 一组标定参数 |
| 没有行为 | 无 Runnable、无 InternalBehavior |
| 只有 | ParameterInterface 的提供端口 |
| 用途 | 把标定参数打包，供 XCP/标定工具访问 |

**典型场景**：把"灯光渐变斜率""雨刮间歇档位时间""门锁延时"等参数打包成一个 `CalibParams` 组件。

## 四、CompositionSwComponentType（组合）

> The purpose of an AUTOSAR CompositionSwComponentType is to allow the **encapsulation of specific functionality by aggregating existing software-components**.
> Since a CompositionSwComponentType is also a SwComponentType, it **again may be aggregated** in further CompositionSwComponentTypes.

| 项 | 内容 |
|---|---|
| 代表什么 | 组件的容器，可递归嵌套 |
| 关键特性 | **封装**（内部组件对外不可见，只暴露 Port） |
| 用途 1 | 表达"功能子系统"（如 `CentralLocking` 组合） |
| 用途 2 | 表达"采购单元"（见 [[06-标准化边界-什么进标准什么不进]]） |
| 用途 3 | 分层设计（顶层系统 → 域 → 子系统 → 原子组件） |

### 组合的封装性（与文件组织无一一对应）

```
Composition: CentralLocking
├── 内部组件：CentralLockingMaster, DoorLock, RemoteKey, HMI
├── 内部连接：全部隐藏
└── 对外端口：只有 DoorCmd、LockStatus 等少量端口
```

组合通过对外端口表达交互；内部改动若影响时序、资源或外部语义仍需重新验证。

> [!warning] 组合 ≠ 可跨 ECU
> 一个 Composition 内部的组件**可以**分布到不同 ECU（如果组合本身没被限制）。
> 通常一个原子执行实例不拆分到不同 ECU；ServiceProxy prototype 的特殊多 ECU 映射见上文，不能混淆类型、prototype 与实例。
> “Atomic”强调内部不再聚合组件；执行与映射还需遵守具体类型及集成约束。

## 五、九种类型速查表

| 类型 | 有无行为 | 能连硬件 | 谁实现 | BCM 场景 |
|---|---|---|---|---|
| Application | ✅ | ❌ | 应用开发者 | 灯光/雨刮/门锁逻辑 |
| SensorActuator | ✅ | ✅ HwType | 驱动/集成 | 传感器接入 |
| EcuAbstraction | ✅ | ✅ HwType | 集成 | 板级抽象 |
| ComplexDeviceDriver | ✅ | ✅ HwType | 驱动开发者 | 特殊驱动 |
| Service | ✅ | ❌ | BSW 供应商 | NvM/Dem 服务端口 |
| ServiceProxy | ✅ | ❌ | 集成 | 为远程请求访问 ECU 本地服务 |
| NvBlock | ⚠️ 常无 | ❌ | 应用/集成 | 配置数据块 |
| Parameter | ❌ | ❌ | 应用/标定 | 标定参数集 |
| Composition | 无自己的 SwcInternalBehavior/Runnable，聚合子组件 | ❌ | 架构师 | 功能子系统 |

## 六、命名冲突：SymbolProps 机制

原子组件的生成符号可能出现命名冲突，类型、实例、Runnable 的生成命名需分开检查：

> [TPS_SWCT_01110] ... it is possible to provide the AtomicSwComponentType along with an accompanying **symbolic name** that can be used for resolving the name clash.
> [TPS_SWCT_01001] If and only if the attribute symbol ... exists, its value shall also be taken for **prefixing the symbols generated for the RunnableEntitys**.

| 场景 | 处理 |
|---|---|
| 两个不同包里有同名 `LightControl` | 各自配 `symbolProps.symbol`（如 `BodyLight` / `RearLight`） |
| 生成代码 | `BodyLight_LightControl_Run()` vs `RearLight_LightControl_Run()` |

> [!tip] 命名规范也是防御手段
> `[TPS_SWCT_01635]` 明确说："定义命名约定可以进一步降低冲突风险"。
> 实践建议：SWC 短名带域前缀（`Body_LightControl`、`Door_LockCtrl`）。

## 七、对 BCM 的启示

| 问题 | 答案 |
|---|---|
| 我的业务逻辑该做成哪种 SWC？ | `ApplicationSwComponentType` |
| 车灯 PWM 输出该不该建 SensorActuator？ | 如果需要在模型里绑定具体硬件，是；否则用 IoHwAb |
| 中控锁该建 Composition 吗？ | 是，它是一个功能子系统（且是采购单元） |
| 标定参数放哪？ | `ParameterSwComponentType` |
| 用不用 ServiceProxy？ | 仅按规定的代理用例、端口与映射约束选择 |

→ 完整分解参考 [[02-车身域标准SWC分解]]

## 八、自检

1. 为什么 `SensorActuatorSwComponentType` 需要引用 `HwType`？
2. `ServiceSwComponentType` 和 `ServiceProxySwComponentType` 的本质区别是什么？
3. 一个 Composition 内部的原子组件，能不能分布在不同 ECU 上？


## 本轮核对依据

- [TPS_SoftwareComponentTemplate，PDF 第 668 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_SoftwareComponentTemplate.pdf#page=668)：[TPS_SWCT_01414]—[TPS_SWCT_01416]
- [TPS_SoftwareComponentTemplate，PDF 第 669 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_SoftwareComponentTemplate.pdf#page=669)：[constr_2016]—[constr_2018]

---

**上一篇** → [[09-横向纵向接口规则]]
**下一篇** → [[11-分区与多核]]
**相关** → [[03-虚拟功能总线VFB]]
**返回** → [[AUTOSAR知识地图]]
