---
title: frame 框架与 AUTOSAR CP R25-11 对照评审
aliases: [frame AUTOSAR 对照, frame 架构复盘]
tags: [落地, BCM, 架构评审, frame]
created: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料与 H:/frame 工程真源
review_scope: 组织、分层、配置、生命周期、通信、诊断、存储与工程裁剪
status: 待架构裁决
---

# frame 框架与 AUTOSAR CP R25-11 对照评审

> [!abstract] 结论
> 当前 frame 已经具备一套有约束力的自研车载框架骨架，最有价值的部分是 `arch_module` 身份、依赖闭集、自动门禁、CAN 唯一出口、HAL 契约面以及 L6 语义接口。它不是 AUTOSAR Classic Platform 的实现，也不适合继续用“八层逐层对应 AUTOSAR”的方式解释。
>
> 当前主要问题不是缺少更多层，而是**组织模型、模块职责和工程组合模型没有完全统一**：65 个注册模块中只有 9 个进入 `module.yaml + Kconfig`；`cfg` 被编号成最底层，容易与运行时层混淆；`PATH`、`DRV`、`STACK` 各自包含多种 AUTOSAR 角色；应用装配仍集中在 `task/main.c`；诊断、存储的异步合同尚未稳定。
>
> 建议保留现有物理目录，先重建“职责视图 + 模块元数据 + 生成式工程装配”，再按模块逐步清理代码。不要先做大规模目录搬迁。

## 1. 评审边界与证据

本次读取并交叉核对：

- `spec/AUTOSAR 学习文档/` 的 72 篇学习与审查材料；
- `spec/AUTOSAR-CP_R25-11官方资料/` 中与本框架直接相关的分层、BSW 通用要求、CanIf、Dcm、NvM、IoHwAb、ECU 配置等官方 PDF；
- `project/frame_IAR/project.yaml`、`architecture/class_matrix.yaml`、`Kconfig`、`kconfig_files/`、`modules/*/module.yaml`；
- `src/hal`、`src/drv`、`src/path`、`src/stack`、`src/rte`、`src/feature`、`src/task` 的代表性实现；
- 现有架构门禁与工程状态。

官方资料只用于判断职责和接口合同。学习文档中的项目建议、示例参数和候选目录不视为项目指令，也不视为已经批准的产品需求。

## 2. 项目定位必须先说清楚

### 2.1 建议的正式定位

建议将 frame 定义为：

> **借鉴 AUTOSAR CP 职责边界、模块生命周期和配置方法的静态车载嵌入式框架。**

这一定义允许项目：

- 使用 FreeRTOS 或裸机；
- 使用 DBC 而不是 ARXML；
- 实现轻量 RTE、Dcm、Dem、NvM 子集；
- 按产品需要裁剪；
- 保留 CVM014x SDK 适配；
- 不声明 AUTOSAR CP 合规、ICC 合规或模块可替换性。

“Class-AUTOSAR”可以继续作为项目名，但文档必须持续说明它是自研框架名称，不能把目录相似性写成标准合规性。

### 2.2 为什么不能把八层直接映射成 AUTOSAR 四层

AUTOSAR CP 的 BSW 在官方分层资料中由 Services、ECU Abstraction、MCAL 和 Complex Drivers 组成；官方资料还明确说明不能继续增加 AUTOSAR 软件层。frame 的 L0~L7 是项目治理视图，不是 AUTOSAR 软件层。

因此后续文档应使用两张图：

1. **项目依赖视图**：保留 `app → feature → runtime → stack/path → drv → hal` 的工程约束；
2. **AUTOSAR 职责视图**：把每个模块映射到 MCAL、ECU Abstraction、Services、RTE、Application 或项目扩展。

不要再用“L3 PATH 相当于 AUTOSAR 的某一层”这种一对一表达。

## 3. 现有组织与 AUTOSAR 职责的准确映射

| frame 组织 | 当前实际职责 | 较接近的 AUTOSAR 角色 | 评审结论 |
|---|---|---|---|
| `src/cfg` | 板级、产品、通信和业务静态表；少量注册胶水 | ECUC 生成结果、模块配置数据 | **横切配置，不是运行时底层。**“L0”只可作为项目编号，不能表达调用层级 |
| `src/hal` | MCU 片内外设契约、SDK 隔离、实例适配 | MCAL 的项目适配面 | 方向正确，但“HAL = 完整 MCAL”不成立；标准化 API、错误、模式和配置合同仍是自研的 |
| `src/drv` | CAN 收发器、HSD、IO 扩展、MUX、EEPROM | CAN Trcv、Onboard Device Abstraction、Memory HW Abstraction、IoHwAb 支撑 | 不是单一 AUTOSAR 层；应按模块角色管理，不能以“片外芯片”统一决定全部接口形态 |
| `src/path` | 输入物理路线、MUX 级联、板级端点 | ECU Abstraction / IoHwAb 的一部分 | 设计有价值；应定义为 ECU 信号路由与采集服务，不应宣称为 AUTOSAR 独立层 |
| `src/stack/canif` | CAN 帧统一出口、收发分发 | CanIf | 边界基本正确；上层不应直接访问 CAN Driver |
| `src/stack/cansm` | CAN 控制器状态管理 | CanSM | 方向正确，仍需把收发器和控制器的模式请求、确认与恢复合同做完整 |
| `src/stack/dbc` | DBC 编解码、信号池桥接、周期发送 | COM 的部分能力 + 项目通信适配 | 可保留轻量实现，但不能称为完整 COM；缺少统一 PDU/路由/组控制等合同 |
| `src/stack/isotp` | UDS over CAN 传输 | CanTp 类角色 | 名称可以自研，外部行为应按声明支持范围验证 |
| `src/stack/uds` | UDS 协议与服务表 | Dcm 的子集 | 应按 Dcm 的会话、安全、寻址、P2/P2*、OpStatus 合同重整；当前不是 Dem/NvM 的所有者 |
| `src/stack/dtc` + `src/srv/fault` | DTC 词汇、事件判定、状态与持久化连接 | Dem 子集 | 目前职责拆散，需建立唯一事件所有者和明确的状态/去抖/确认/老化边界 |
| `src/stack/nvm` | 块管理、队列、Fee 与 DFlash 后端 | NvM + Fee + 存储驱动适配 | 异步方向正确；模块边界、块配置、通知和统计语义仍需收紧 |
| `src/stack/wdgm` | Alive supervision 子集 | WdgM 子集 | 可以保留，但监督策略属于产品决策，框架只提供机制 |
| `src/rte/signal` | 信号池、有效性、具名读写接口 | 轻量 RTE 数据访问 | 对业务隔离有效，但不等同完整 RTE；缺 Runnable、事件、模式、一致性组、客户/服务调用等完整合同 |
| `src/rte/output` | 输出门控和硬件提交 | IoHwAb/应用输出仲裁的项目组合 | 需区分功能请求、仲裁结果、硬件命令、反馈和保护状态 |
| `src/feature` | 灯光功能逻辑 | Application SWC 内部逻辑 | 边界正确，继续禁止硬件、报文和诊断内部依赖 |
| `src/task` | ECU 装配、初始化、周期调用和部分产品服务 | EcuM/BswM/SchM/RTE 调度 + Composition Root | 这是当前最重的混合区；应由生成式生命周期清单替代手工装配知识 |

## 4. 当前已经做对的部分

### 4.1 模块身份不按目录猜

`project.yaml` 的 `arch_module` 是模块身份真源，`class_matrix.yaml` 给出依赖闭集。这比单靠目录层级可靠，能够表达 `debug.cmd`、`boot.interface`、`runtime.path` 等横向或特殊模块。

### 4.2 边界有机器门禁

现有门禁已经覆盖：

- HAL 公共头零 SDK；
- 只有 HAL 芯片实现面接触 SDK；
- cfg 零函数、注册面禁调用；
- Feature 只依赖语义运行时接口；
- CAN 唯一发送出口；
- ISR 上下文限制；
- 模块依赖闭集、同类精确放行和无环；
- 源文件必须登记到工程；
- 人读矩阵与 YAML 真源同步。

这些规则是框架最成熟的资产，应作为重构期间的保护网保留。

### 4.3 HAL 契约面和实现面分离

`src/hal/include/*.h` 与 `*_cvm014x.c` 的分离符合“上层与 MCU 实现解耦”的目标。它不自动等于 AUTOSAR MCAL，但已经建立了可迁移所需的第一道边界。

### 4.4 CAN 经 CanIf 统一出口

官方 CanIf 规范明确要求上层通信模块只经 CanIf 发起传输，不直接访问 CanDrv。项目规定 `hal_can_send_ch` 只允许在 `canif.c`，这一边界与官方职责一致，应继续保持。

### 4.5 L6 已使用具名语义接口

灯光功能通过 `Rte_Read_*` / `Rte_Write_*` 访问语义信号，不直接解析 DBC，不直接访问硬件。即使这是轻量 RTE，它也已经实现了最关键的业务隔离价值。

## 5. 当前组织上的主要问题

### 5.1 `cfg` 的“L0 最底层”表述会持续制造误解

配置数据可以被多个模块读取，也可能在 pre-compile、link-time 或 post-build 阶段绑定。它不是一条 `APP → ... → CFG` 运行时调用链的末端。

建议：

- 保留 `src/cfg` 目录；
- 文档中将其改称“配置域”或“配置切面”；
- 架构图用侧边注入箭头表达，不放在垂直调用栈最底部；
- `cfg.*` class 继续只允许数据、对象引用和注册胶水；
- 将“L0”明确标注为项目编号，不表示 AUTOSAR 层级。

### 5.2 `DRV` 按“片外芯片”分层过粗

CAN 收发器、外部 EEPROM、IO 扩展器、MUX、HSD 的职责并不相同。它们在 AUTOSAR 中可能属于通信硬件抽象、存储硬件抽象、Onboard Device Abstraction 或 IoHwAb 支撑。

建议不急于搬目录，先在 `arch_module` 和 `module.yaml` 中给出标准角色标签，例如：

```yaml
role: ecu_abstraction.io_device
role: ecu_abstraction.comm_transceiver
role: ecu_abstraction.memory_device
```

依赖规则按角色验证，目录只承担物理组织。

### 5.3 `PATH` 的概念正确，但层级解释不准确

R25-11 IoHwAb 规范明确把 IoHwAb 放在 ECU Abstraction，并允许由多个模块实现。它把 IoHwAb 端口映射为 ECU 信号，官方示例也包含 MUX 数字输入、周期采集、去抖和快速保护。

因此 PATH 可以保留为本项目独特且有价值的“路线引擎”，但应满足：

- PATH 管物理路线、资源占用、选通与建立时间；
- Driver 管器件合同；
- 信号调理和品质合同有唯一所有者；
- 快速保护不经过慢速业务路径；
- PATH 不解释产品业务意义。

### 5.4 `STACK` 是目录桶，不是架构层

`stack` 同时放通信接口、状态管理、传输协议、诊断、存储和监督。它们在 AUTOSAR 中跨 Communication Services、Memory Services、System Services 和 Diagnostic Services。

建议：

- 文档停止把 `STACK` 当成一个单一职责层；
- 架构、裁剪、生命周期一律按 `arch_module`/模块角色处理；
- 目录可在后续模块迁移完成后再分成 `comm/diag/storage/supervision`；
- 在迁移前不要为了“看起来像 AUTOSAR”进行大规模移动。

### 5.5 `task/main.c` 仍是手工装配中心

当前 `main.c` 约 390 行，直接知道 Fee、NvM、Sig、Fault、UDS、CanSm、WdgM 等模块的配置和初始化顺序。`App_Run()` 也手工固定多个 MainFunction 顺序。

这会造成：

- 新工程创建必须复制并修改装配代码；
- Kconfig 关闭模块后仍可能残留初始化或 include；
- 生命周期依赖与源文件依赖分离；
- 裁剪组合难以证明闭合；
- 同一模块的 `init/main_function/phase` 信息在多处重复。

应由模块清单生成生命周期表或编排代码，`main.c` 只保留平台入口和启动阶段推进。

## 6. 工程创建与裁剪的真实缺口

当前统计：

| 项目 | 数量 |
|---|---:|
| `project.yaml` 注册模块 | 65 |
| `modules/*/module.yaml` | 9 |
| `Kconfig` 的 `MODULE_*` 开关 | 9 |
| `src` 下 C 文件 | 196 |

说明 M7/Kconfig 已证明最小闭环，但尚未成为全框架的工程模型。现在仍存在三套信息：

1. `project.yaml`：完整源集与架构身份真源；
2. `module.yaml`：少数模块的依赖、能力和生命周期；
3. `Kconfig`：少数模块的可选性。

目标应收敛为：

```text
Kconfig 选择
  ↓
module.yaml 模块闭包（requires/provides/conflicts/target/runtime/config）
  ↓
生成 selected_modules + project.yaml 源集片段 + lifecycle 表 + include 路径
  ↓
生成 IAR 工程和验收清单
```

在完成迁移前，`project.yaml` 仍是唯一真源；不能提前让 `module.yaml` 与它形成两个可编辑真源。

### 6.1 `module.yaml` 需要补齐的字段

每个模块至少需要：

| 字段 | 用途 |
|---|---|
| `id` / `arch_module` / `class` | 身份和依赖门禁 |
| `targets` / `when` | 工程与 Kconfig 选择 |
| `sources` / `public_includes` / `private_includes` | 构建输入 |
| `requires` / `provides` / `conflicts` | 模块闭包和替代能力 |
| `runtime.init` / `runtime.main_function` / `runtime.phase` | 生命周期生成 |
| `config_inputs` / `generated_outputs` | 配置与生成链追溯 |
| `tests` / `acceptance` | 被选择后必须执行的验证 |
| `owner` / `status` | 维护边界与迁移状态 |

### 6.2 Kconfig 只负责选择，不承载全部架构知识

Kconfig 适合表达 bool/choice、依赖和默认值。以下内容不应散落在 Kconfig 中：

- C 源文件全清单；
- 初始化调用顺序；
- DBC、DID、DTC、NvM 块等产品数据；
- 架构 class 允许边；
- 工具生成产物的手工复制规则。

## 7. 运行时与接口细节

### 7.1 轻量 RTE 的边界

当前 RTE 主要解决“业务不碰槽位和报文”。下一步应优先补合同，不急于增加更多包装函数：

- 值、有效性、时间戳、序号的一致快照；
- 明确无数据、过期、替代值和错误的状态；
- 时间戳不能用 0 表示无数据；
- 事件类命令与状态类信号分开；
- 读接口使用物理语义和单位，不泄漏 DBC 位宽；
- 输出区分请求值、仲裁值、已提交值和实际反馈；
- MainFunction 与 Task 映射有机器可读来源。

DBC 生成桥直接写入 RTE 内部信号池可以作为同一 ECU 的高效适配，但这个接口应标记为 RTE 内部 provider API；Feature 继续只看具名端口。

### 7.2 生命周期

各模块不必机械实现全部 AUTOSAR API，但框架应统一描述：

- 初始化前可调用哪些查询；
- `Init` 是否可重复；
- `MainFunction` 周期和调用上下文；
- 异步请求的受理、运行、完成和取消；
- 回调在哪个上下文执行；
- 模式切换的请求与确认；
- 错误报告与返回值的关系；
- 关闭、复位和掉电时的未完成作业处置。

当前 `Hal_Init`/`Drv_Init` 已收敛部分顺序，但存在返回值被忽略、直接永久循环停车等既有行为。看门狗、复位、停车策略属于人工裁决范围，本评审只记录，不建议在架构重构中顺手改变。

## 8. 通信栈评审

### 8.1 保留 CanIf 唯一出口

`CanIf_Transmit` 的官方职责是上层发送 L-PDU 的统一入口，并向下调用 CAN Driver。当前框架用 `canif` 统一发送是正确的。

### 8.2 不一定要照搬 PduR/COM 模块名，但职责不能缺失

轻量框架可以把静态路由、DBC 编解码和信号状态合并实现，但至少要显式描述：

- 帧/PDU 的所有者；
- RX 分发与 TX 确认；
- 发送队列和忙返回；
- 周期、触发、重复和超时；
- 通信启停与模式；
- ISO-TP 与普通报文是否共享资源；
- DBC 生成物与业务语义的转换边界。

当前 `comm.signal.dbc` 直接依赖 `runtime.signal` 是可接受的项目选择；它代表“COM + RTE 适配合并”，不能据此宣称具有完整 COM/PduR 能力。

### 8.3 CanSM/收发器启动

`Drv_Init()` 当前直接把所有收发器拉到 NORMAL 再启动控制器，文件中已经标注为 bring-up 临时行为。后续应由产品网络与电源策略决定模式管理；该策略不能在通用框架重构中自行决定。

## 9. 诊断、DTC 与存储评审

### 9.1 M2 继续前必须修正异步诊断合同

R25-11 Dcm 在 `[SWS_Dcm_00527]`~`[SWS_Dcm_00530]` 中定义了异步操作合同：

1. 首次调用使用 `DCM_INITIAL`；
2. 后台未完成返回 pending；
3. Dcm 在 `Dcm_MainFunction` 中以 `DCM_PENDING` 重调；
4. 需要立即发送 0x78 时使用 FORCE_RCRRP 流程；
5. 0x78 确认后以 `DCM_FORCE_RCRRP_OK` 重调；
6. 取消时传入 `DCM_CANCEL`。

frame 不必照抄全部类型名，但应保留同样的状态语义。推荐的轻量接口：

```c
typedef enum {
    UDS_OP_INITIAL,
    UDS_OP_PENDING,
    UDS_OP_CANCEL,
    UDS_OP_FORCE_RCRRP_OK
} Uds_OpStatusType;

typedef enum {
    UDS_JOB_OK,
    UDS_JOB_PENDING,
    UDS_JOB_FORCE_RCRRP,
    UDS_JOB_FAILED
} Uds_JobResultType;
```

服务回调拥有自己的作业上下文；UDS 核心只管理请求占用、P2/P2*、0x78、取消和最终响应。存储完成状态由 NvM 查询或作业句柄提供，避免 `app_persist → Uds_Complete...` 的反向通知把应用层绑定进诊断核心。

因此，当前尚未验证的通用 `Uds_StartPendingResponse`、`Uds_PendingPollType`、DID 专用完成通知方案不应直接定型。先按上述合同重画状态机，再继续 M2-02/M2-03。

### 9.2 0x2E 持久化的所有权

建议链路：

```text
UDS 0x2E 服务
  → 校验会话/权限/长度/可写性
  → DID owner 更新 RAM 工作副本
  → 请求 NvM 写块
  → 返回 PENDING
  → 后续 OpStatus 调用查询 NvM 作业
  → 成功才发 0x6E；失败发 0x72；取消时释放事务
```

DID 定义、默认值和序列化布局应是配置数据；UDS 服务不应自己长期拥有产品全部 DID 缓冲。

### 9.3 NvM 统计语义

数据修复表示从冗余副本或默认值恢复；写请求被拒绝表示请求/资源/故障注入失败。两者不是同一类事件。

因此不建议把 `write-rejected` 计入 `repair_count`。应分别维护：

- `repair_count` / `last_repair_reason`；
- `write_reject_count` / `last_write_error`；
- 可选的底层 Fee/Flash 错误统计。

故障注入属于 debug/test adapter。生产 `Nvm_Write` 不应包含全局测试开关；可由测试后端、弱钩子或编译期测试模块在受控构建中注入。

### 9.4 Dem 风格边界

故障管理至少要区分：

- 监控器报告的 Event；
- 去抖状态；
- DTC 状态位；
- confirmed 判定；
- 恢复与老化；
- 冻结帧/扩展数据；
- 清码；
- NvM 持久化。

这些策略不能从 UDS 服务实现反推。DTC 老化策略属于人工产品决策，框架只提供可配置机制。

## 10. 建议的目标组织

不要求立即搬目录，先在模块元数据中形成以下逻辑域：

```text
platform
  mcal_adapter      CVM014x 片内外设适配
  os_adapter        bare / FreeRTOS

ecu_abstraction
  io_device         HSD / IO expander / MUX
  io_route          PATH / endpoint / sample route
  comm_hw           CAN transceiver
  memory_hw         external EEPROM / flash adapter

services
  comm              CanIf / CanSM / ISO-TP / DBC signal adapter
  diag              UDS core / service callbacks
  event             fault / DTC state
  memory            NvM / Fee
  supervision       WdgM
  mode              lifecycle / mode requests

runtime
  ports             named Rte_Read/Rte_Write
  signal_store      value / quality / timestamp / sequence
  scheduler         generated lifecycle table

application
  feature           light / turn / future body functions
  composition       product wiring and policy

configuration       cross-cutting input and generated tables
debug_test          removable shell, probes and injection adapters
```

这是一张职责图，不要求添加同名目录或新增 AUTOSAR 层。

## 11. 推荐实施顺序

### 阶段 A：冻结身份和职责

1. 为每个现有 `arch_module` 增加 `role`、owner、公共 API、配置输入和生命周期说明。
2. 写 ADR，确认“frame 是 AUTOSAR-inspired，不声明 CP 合规”。
3. 修正文档图：cfg 画成横切域，PATH 画入 ECU Abstraction 视图，STACK 按服务域展开。
4. 保持目录和 API 不动，只改模型与文档。

### 阶段 B：完成模块模型迁移

1. 按 `project.yaml` 65 个模块补齐 `module.yaml`；一批只迁 5~10 个。
2. 每批比较解析结果与原 `project.yaml`，必须源集逐文件一致。
3. 扩展 Kconfig，使模块选择、依赖和 target 闭合。
4. 在迁移完成前继续以 `project.yaml` 为唯一真源。

### 阶段 C：生成工程与生命周期

1. 由选择后的模块闭包生成 IAR groups、include 路径和源集。
2. 由 `runtime.phase/init/main_function` 生成生命周期表。
3. `main.c` 收敛为平台入口、阶段推进和失败汇总。
4. App_A、App_B、EVK_APP、EVK_BOOT 共用同一解析器，通过 target/variant 选择差异。

### 阶段 D：补齐运行时合同

1. 信号快照统一 value/quality/timestamp/sequence。
2. 区分状态信号与事件命令。
3. 明确输出请求、仲裁、提交与反馈。
4. 将 provider API 与 Feature API 分开。

### 阶段 E：按职责收紧服务

1. 通信：形成 CanIf/CanSM/ISO-TP/DBC 的明确 PDU 与模式合同。
2. 诊断：引入 OpStatus 异步合同，重做 M2 pending 路径。
3. 存储：分开 NvM、Fee、后端和配置；分开修复与写拒绝统计。
4. 故障：建立 Event→DTC→记录→持久化的唯一所有权。

### 阶段 F：清理废弃内容

每批迁移完成后，由工具生成：

- 未被任何工程选择的源文件；
- 零消费者公共接口；
- 旧生成物和重复配置；
- 已被新模块替代的目录；
- 仅剩历史说明的文档链接。

逐路径确认并删除，随后更新 `project.yaml`、模块清单、文档和验收记录。禁止用整目录删除代替消费者分析，也禁止在脏工作区使用 `git add -A`。

## 12. M1/M2 当前处置建议

| 项目 | 建议 |
|---|---|
| M1 已闭环部分 | 保持，不因本次架构学习返工 |
| M2-04 / M2-05 已闭环部分 | 保持既有验收结论，后续只做接口兼容检查 |
| M2-01 0x27 | 继续预留；算法、密钥和策略由人工决定 |
| M2-02 DID 持久化 | 暂停定型；先确定 DID owner、NvM block 合同和 OpStatus 服务接口 |
| M2-03 0x78/P2/P2* | 暂停当前通用 pending 方案；按 Dcm OpStatus 状态机重设计 |
| 写失败注入 | 移到 debug/test adapter，不能污染生产 NvM 统计语义 |

本表是架构评审建议，不直接改写验收总表状态。

## 13. 架构裁决点

以下项目需要人确认后才能实施：

1. 是否接受“项目八层视图 + AUTOSAR 职责视图”双视图，不再做一对一层映射；
2. 是否把 cfg 从垂直层图中移到横切配置域，但保留 `L0` 历史编号；
3. 是否把 `STACK` 降为物理目录概念，架构按 comm/diag/storage/supervision 角色解释；
4. 是否将 65 个注册模块全部迁入 `module.yaml + Kconfig`，最终由模块清单生成工程；
5. 是否采用 Dcm 风格 OpStatus 合同重做 M2-02/M2-03 未完成实现；
6. 是否在模块模型成熟后再进行目录搬迁和废弃文件删除。

这些裁决涉及架构分层、依赖模型或产品策略，本评审不擅自修改。

## 14. 官方核对依据

- `AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf`：PDF 第 11 页说明非标准模块可作为 Complex Driver 集成且不能增加 AUTOSAR 层；第 13 页给出 BSW 四类；第 15 页说明 MCAL 是 BSW 最低层、上接口标准化且与 MCU 无关；第 30~31 页展示 I/O Hardware Abstraction、Onboard Device Abstraction 与外部器件驱动关系。
- `AUTOSAR_CP_SWS_IOHardwareAbstraction.pdf`：PDF 第 8 页说明 IoHwAb 属于 ECU Abstraction、可由多个模块实现且用于把端口映射为 ECU 信号；第 34~35 页给出 MUX 输入、周期读取、去抖和快速过流保护示例。
- `AUTOSAR_CP_SWS_CANInterface.pdf`：PDF 第 40 页说明上层通信模块只通过 `CanIf_Transmit` 发起传输，CanIf 再调用 CAN Driver。
- `AUTOSAR_CP_SWS_DiagnosticCommunicationManager.pdf`：PDF 第 52 页 `[SWS_Dcm_00527]`~`[SWS_Dcm_00530]` 定义 INITIAL、PENDING、FORCE_RCRRP 和 MainFunction 重调行为；PDF 第 281 页展示异步接口的 `DCM_INITIAL/DCM_PENDING/DCM_CANCEL/DCM_FORCE_RCRRP_OK` 操作状态。
- `AUTOSAR_CP_SWS_NVRAMManager.pdf`：第 7.2.2.12 节定义异步请求/作业处理，第 8.3.2 节定义异步单块请求，第 8.5.3 节定义可配置作业结束通知。
- `AUTOSAR_CP_TPS_ECUConfiguration.pdf`：定义 ECU 配置描述、模块配置以及 pre-compile/link-time/post-build 配置时间和变体支持。
- `AUTOSAR_CP_SWS_BSWGeneral.pdf`：定义模块文件结构、初始化、版本信息、Scheduled Functions、SchM 接口和共享代码可重入要求。

## 15. 本次机器检查结果

在 2026-10-23 当前工作区执行：

```text
python tools/arch_check.py                    → 退出码 0（需 PYTHONIOENCODING=utf-8）
python tools/arch_matrix.py --check           → 退出码 0
python tools/module_layout_check.py           → 退出码 0，actual 123，baseline 138
python tools/doc_matrix_sync.py --check       → 退出码 0
python tools/acceptance_status.py --check     → 退出码 0
```

`arch_check.py` 在默认 GBK 控制台会因输出 `↔` 触发 `UnicodeEncodeError`，这是工具输出兼容性问题，不是架构违规；设置 `PYTHONIOENCODING=utf-8` 后完整执行并退出 0。

本次未构建、未运行宿主测试、未上板。原因是本轮只新增评审文档，没有修改运行代码；且当前工作区已有大量未提交改动，未验证的 M2 代码不能据此宣称通过。

---

**相关** → [[03-Mini-AUTOSAR分层映射]] | [[06-IO端点与采集路线设计]] | [[07-业务绑定诊断与任务落地]]

