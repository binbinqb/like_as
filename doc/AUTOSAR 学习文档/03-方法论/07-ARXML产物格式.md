---
title: ARXML 产物格式
aliases: [ARXML, AUTOSAR XML, 元模型]
tags: [方法论, 工具]
source: [TPS_SoftwareComponentTemplate, TPS_SystemTemplate, EXP_ModelingShowCases]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# ARXML 产物格式

> [!note] 项目上下文
> 未经本轮实际工程输入验证的“现状”、器件、数量和工具信息，均按示例或待确认假设阅读；不代表已审查 SDK、原理图、DBC 或现有业务代码。


> [!tip] 结论
> ARXML 是 AUTOSAR 元模型的 XML 序列化。看懂它只需要掌握三件事：
> **① 包结构（AR-PACKAGE 嵌套）② 短名与路径引用 ③ 变体包装（VARIANTS/CONDITIONAL）**。
> 其余都是这三者的排列组合。

## 一、整体骨架

```xml
<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"
         xsi:schemaLocation="http://autosar.org/schema/r4.0 AUTOSAR_00054.xsd">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>McInt</SHORT-NAME>          <!-- 顶层包 -->
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>SwComponents</SHORT-NAME> <!-- 子包 -->
          <ELEMENTS>
            <APPLICATION-SW-COMPONENT-TYPE>
              <SHORT-NAME>Controller</SHORT-NAME>
              ...
            </APPLICATION-SW-COMPONENT-TYPE>
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
```

> 上面这段来自官方示例 `ModelingShowCases/30_MeasurementCalibration/10_Introductory/model/SwcController.arxml`。

| 层级 | 作用 |
|---|---|
| `<AUTOSAR>` | 根元素，声明命名空间与 schema 版本 |
| `<AR-PACKAGES>` | 包容器 |
| `<AR-PACKAGE>` | 包（可无限嵌套），靠 `<SHORT-NAME>` 命名 |
| `<ELEMENTS>` | 包里放元素的地方 |
| 元素（如 `APPLICATION-SW-COMPONENT-TYPE`） | 具体的元模型对象 |

## 二、三个必须掌握的概念

### 2.1 SHORT-NAME 与 AR-PATH

可标识的 Identifiable 元素具有 SHORT-NAME，短名通常在所属命名空间内唯一；不是每个 XML 元素都有 SHORT-NAME，跨包引用需检查完整模型路径。

组合成路径（AR-PATH）：

```
/McInt/SwComponents/Controller
 └─包─┘ └──子包──┘ └─元素─┘
```

引用时用 `-TREF`（target reference）后缀：

```xml
<REQUIRED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">
    /McInt/PortInterfaces/TemperatureSRIF
</REQUIRED-INTERFACE-TREF>
```

| 属性 | 作用 |
|---|---|
| `DEST` | 目标元素的类型（供工具校验） |
| 内容 | 目标元素的 AR-PATH |

> [!important] AR-PATH 是"绝对路径"
> 类似文件系统：`/包/子包/元素`。
> 也有相对路径（`SHORT-NAME-REF` 不带前导 `/`），但**强烈建议一律用绝对路径**，否则移动包时全断。

### 2.2 变体包装（Variation）

这是 AUTOSAR 元模型最独特的机制。**几乎所有可能变化的地方都被包了一层**：

```xml
<SW-DATA-DEF-PROPS>
  <SW-DATA-DEF-PROPS-VARIANTS>
    <SW-DATA-DEF-PROPS-CONDITIONAL>          <!-- 条件：默认/某变体下生效 -->
      <SW-ADDR-METHOD-REF DEST="SW-ADDR-METHOD">/McInt/SwAddrMethods/CODE</SW-ADDR-METHOD-REF>
      <SW-CALIBRATION-ACCESS>READ-ONLY</SW-CALIBRATION-ACCESS>
      <SW-IMPL-POLICY>STANDARD</SW-IMPL-POLICY>
    </SW-DATA-DEF-PROPS-CONDITIONAL>
  </SW-DATA-DEF-PROPS-VARIANTS>
</SW-DATA-DEF-PROPS>
```

| 层级 | 含义 |
|---|---|
| `XXX-VARIANTS` | 变体集合 |
| `XXX-CONDITIONAL` | 在某个条件下生效的取值（无条件时就是默认） |

**为什么这么设计**：

| 需求 | 实现 |
|---|---|
| 同一份描述支持多车型 | 不同 CONDITIONAL 对应不同变体 |
| 描述可以被"切分"给不同供应商 | `atpSplitable` 标记 |
| 一部分描述放在另一个文件 | `atpSplitable` 支持跨文件拆分 |

> [!note] `atpVariation` / `atpSplitable` 是什么
> 它们是元模型里的**构造型（stereotype）**：
> - `atpVariation`：该元素可配变体
> - `atpSplitable`：该元素可拆到不同 ARXML 文件
>
> 在官方模板文档里看到这两个词，就知道这里支持变体/拆分。

### 2.3 描述性文本（多语言）

```xml
<DESC>
  <L-2 L="EN">Port to receive the temperature of the plant</L-2>
</DESC>
```

| 标签 | 含义 |
|---|---|
| `L-2` | 二级描述（简短） |
| `L-4` | 四级描述（详细，可含结构） |
| `L="EN"` | 语言标记 |

> 这些描述会进入生成的文档，也是**模型自解释性**的来源。**不要留空。**

## 三、典型的文件切分方式

官方示例把模型拆成多个文件，这是标准做法：

| 文件 | 内容 | 对应元模型 |
|---|---|---|
| `ApplicationDataTypes.arxml` | 应用数据类型 | `ApplicationPrimitiveDataType` |
| `PlatformTypes.arxml` | 平台类型（映射到 C 类型） | `SwBaseType` |
| `CompuMethods.arxml` | 换算方法（物理值 ↔ 原始值） | `CompuMethod` |
| `UnitsAndPhysicalDimensions.arxml` | 单位与量纲 | `Unit`、`PhysicalDimension` |
| `PortInterfaces.arxml` | 端口接口定义 | `SenderReceiverInterface`、`ClientServerInterface` |
| `SwcController.arxml` | SWC 类型定义 | `ApplicationSwComponentType` |
| `SwcComposition.arxml` | 组合与连接 | `CompositionSwComponentType` |
| `DataTypeMappings.arxml` | 应用类型 → 实现类型 | `DataTypeMappingSet` |
| `SwAddrMethods.arxml` | 标定访问方式 | `SwAddrMethod` |
| `EcucConf.arxml` | ECU 配置 | `EcucModuleConfigurationValues` |
| `FlatMap.arxml` | 扁平映射 | `FlatInstanceDescriptor` |
| `System.arxml` | 系统描述 | `System` |

> [!tip] 为什么按"元模型类型"切文件
> 因为不同角色编辑不同文件：
> - 数据类型由架构师定（`ApplicationDataTypes`）
> - 接口由接口负责人定（`PortInterfaces`）
> - SWC 由组件开发者定（`SwcController`）
> - 配置由集成工程师定（`EcucConf`）
>
> **文件边界 ≈ 责任边界**，这和 [[06-两阶段开发与OEM供应商分工]] 的逻辑一致。

## 四、一个 SWC 的完整解剖

以官方 `Controller` 为例：

```xml
<APPLICATION-SW-COMPONENT-TYPE>
  <SHORT-NAME>Controller</SHORT-NAME>

  <!-- ① 端口 -->
  <PORTS>
    <R-PORT-PROTOTYPE>
      <SHORT-NAME>TemperatureRPP</SHORT-NAME>
      <REQUIRED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">
        /McInt/PortInterfaces/TemperatureSRIF
      </REQUIRED-INTERFACE-TREF>
    </R-PORT-PROTOTYPE>
    <P-PORT-PROTOTYPE>
      <SHORT-NAME>CurrentPPP</SHORT-NAME>
      <PROVIDED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">
        /McInt/PortInterfaces/CurrentSRIF
      </PROVIDED-INTERFACE-TREF>
    </P-PORT-PROTOTYPE>
    <R-PORT-PROTOTYPE>
      <SHORT-NAME>ControllerParamsRPP</SHORT-NAME>
      <REQUIRED-INTERFACE-TREF DEST="PARAMETER-INTERFACE">
        /McInt/PortInterfaces/ControllerPIF
      </REQUIRED-INTERFACE-TREF>
    </R-PORT-PROTOTYPE>
  </PORTS>

  <!-- ② 内部行为 -->
  <INTERNAL-BEHAVIORS>
    <SWC-INTERNAL-BEHAVIOR>
      <SHORT-NAME>ControllerInternalBehavior</SHORT-NAME>
      <DATA-TYPE-MAPPING-REFS>...</DATA-TYPE-MAPPING-REFS>

      <!-- 每实例内存（相当于"实例变量"） -->
      <AR-TYPED-PER-INSTANCE-MEMORYS>
        <VARIABLE-DATA-PROTOTYPE>
          <SHORT-NAME>E</SHORT-NAME>
          <SW-DATA-DEF-PROPS>...</SW-DATA-DEF-PROPS>
        </VARIABLE-DATA-PROTOTYPE>
      </AR-TYPED-PER-INSTANCE-MEMORYS>

      <!-- Runnable -->
      <RUNNABLES>
        <RUNNABLE-ENTITY>
          <SHORT-NAME>ControllerRun</SHORT-NAME>
          <MINIMUM-START-INTERVAL>0.01</MINIMUM-START-INTERVAL>
          <CAN-ENTER-EXCLUSIVE-AREA-REFS>...</CAN-ENTER-EXCLUSIVE-AREA-REFS>
          <DATA-RECEIVE-POINT-BY-ARGUMENTS>...</DATA-RECEIVE-POINT-BY-ARGUMENTS>
          <DATA-SEND-POINTS>...</DATA-SEND-POINTS>
          <SERVER-CALL-POINTS>...</SERVER-CALL-POINTS>
          <SYMBOL>ControllerRun</SYMBOL>
        </RUNNABLE-ENTITY>
      </RUNNABLES>

      <!-- 触发事件 -->
      <EVENTS>
        <TIMING-EVENT>
          <SHORT-NAME>ControllerRun_TimingEvent</SHORT-NAME>
          <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">
            /McInt/SwComponents/Controller/ControllerInternalBehavior/ControllerRun
          </START-ON-EVENT-REF>
          <PERIOD>0.01</PERIOD>
        </TIMING-EVENT>
      </EVENTS>
    </SWC-INTERNAL-BEHAVIOR>
  </INTERNAL-BEHAVIORS>
</APPLICATION-SW-COMPONENT-TYPE>
```

### 对应关系表

| ARXML 元素 | 概念 | 对应 C 代码 |
|---|---|---|
| `PORTS / R-PORT-PROTOTYPE` | 需求端口 | `Rte_Read_<port>_<data>()` |
| `PORTS / P-PORT-PROTOTYPE` | 提供端口 | `Rte_Write_<port>_<data>()` |
| `SWC-INTERNAL-BEHAVIOR` | 内部行为（唯一） | — |
| `VARIABLE-DATA-PROTOTYPE`（per-instance） | 实例变量 | 结构体成员 |
| `RUNNABLE-ENTITY` | 可执行单元 | `void Swc_Run(void)` |
| `TIMING-EVENT` + `PERIOD` | 周期触发 | Task 周期 |
| `DATA-RECEIVE-POINT-BY-ARGUMENTS` | 接收数据点 | 函数参数 |
| `DATA-SEND-POINTS` | 发送数据点 | `Rte_Write` 调用点 |
| `SERVER-CALL-POINTS` | 服务调用点 | `Rte_Call` 调用点 |
| `EXCLUSIVE-AREA` | 临界区 | `SchM_Enter/Exit` |
| `SYMBOL` | 生成符号名 | 函数名前缀 |

> [!important] 这张表是"读懂 RTE 生成代码"的钥匙
> RTE 生成器就是**按这张表机械翻译**的。
> TimingEvent 的 PERIOD 影响触发需求，不自动等于某一个 Task 的周期；访问点声明生成接口合同，不会自动替应用实现插入一条业务 Rte_Write 调用。

## 五、ARXML 的三种"视图"对应三份文件

同一个系统，三份 ARXML 描述三个视角：

| 文件 | 视图 | 内容 |
|---|---|---|
| `SwcController.arxml` | **类型视图** | SWC 类型定义（可复用） |
| `SwcComposition.arxml` | **实例视图** | 组件实例 + 连接（Connector） |
| `System.arxml` | **部署视图** | ECU + 网络 + 映射 |

> [!tip] 类型 vs 实例
> - `Controller` 是**类型**（一份定义）
> - `SHCFrontLeft`、`SHCFrontRight` 是**实例**（两个对象，共享类型）
> 这就是 [[10-软件组件SWC九种类型]] 里"多实例"的建模方式。

## 六、手写 ARXML 现实吗

| 场景 | 建议 |
|---|---|
| 学习理解 | ✅ 手写小例子，是最好的学习方式 |
| 小项目 | ⚠️ 可以手写，但要有 schema 校验（`xmllint`） |
| 正式项目 | 建议采用受控建模／生成工具；手写与脚本生成均需 Schema 和语义一致性校验 |
| 生成配置 | ⚠️ 可用脚本从 Excel/DBC 生成 |

### 最小验证方法

```bash
# 用 xmllint 校验语法与 schema
xmllint --noout --schema AUTOSAR_00054.xsd MyModel.arxml
```

> [!warning] schema 版本要匹配
> 每个 AUTOSAR release 对应一个 schema 版本号（如 `AUTOSAR_00054.xsd`）。
> 用错版本会导致"元素不存在"的诡异错误。

## 七、和你的项目的关系

| 你的产物 | ARXML 等价物 | 建议 |
|---|---|---|
| `cfg_can_matrix.h` | Communication Matrix（ARXML） | 保持 C 表，但**用脚本从矩阵生成**，避免手抄 |
| `dbc_comm` 的解析表 | System Mapping | 同上 |
| `hal_*.h` 接口 | PortInterface（部分） | 不需要 ARXML，但**保持语义稳定** |
| 配置表 `cfg_*.c` | EcucConf | 用脚本生成最实际 |

> [!important] 不必强行上 ARXML
> ARXML 的价值在"工具链互操作"。如果没有工具链，手写 ARXML 只是把 C 代码换成 XML，没有收益。
> **但"分文件、分责任、类型与实例分离、变体包装"这些思想，可以直接借用。**

→ 详见 [[03-Mini-AUTOSAR分层映射]]

## 八、自检

1. AR-PATH 里的前导 `/` 表示什么？
2. 为什么几乎所有属性都被 `VARIANTS/CONDITIONAL` 包了一层？
3. `atpSplitable` 解决了什么问题？

---

**上一篇** → [[06-两阶段开发与OEM供应商分工]]
**下一篇** → [[08-工作流实例]]
**返回** → [[AUTOSAR知识地图]]


## 原文入口与审查范围

- [TPS_SoftwareComponentTemplate](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_SoftwareComponentTemplate.pdf)
- [TPS_SystemTemplate](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TPS_SystemTemplate.pdf)

> [!note] 阅读边界
> 原文入口用于继续核对；定向修正以审查记录为准，未逐条验证的解释和示例不因添加链接而自动成为官方结论。
