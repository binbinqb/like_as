---
title: RTE 运行时环境
aliases: [RTE, Runtime Environment, 运行时环境]
tags: [架构, 核心]
source: [EXP_LayeredSoftwareArchitecture, TR_VFB, SWS_RTE]
created: 2026-10-23
reviewed: 2026-10-23
review_scope: 定向修正；其余内容未逐条验证
review_basis: AUTOSAR CP R25-11 本地资料
---

# RTE 运行时环境

> [!tip] 结论
> RTE 是**生成出来的胶水代码**，为每颗 ECU 单独生成。
> 它把"组件想要什么"翻译成"BSW 怎么做"，并在本地场景下退化成几乎零开销的直接访问。
> **RTE 之上是组件风格，之下是分层风格 —— 它是两种范式之间唯一的翻译层。**

## 一、官方定义

> The RTE is a layer providing communication services to the application software (AUTOSAR Software Components and/or AUTOSAR Sensor/Actuator components).
> **Above the RTE the software architecture style changes from "layered" to "component style".**
> The AUTOSAR Software Components communicate with other components (inter and/or intra ECU) and/or services via the RTE.
>
> **Task**: Make AUTOSAR Software Components **independent from the mapping to a specific ECU**.
> **Properties**:
> - Implementation: **ECU and application specific (generated individually for each ECU)**
> - Upper Interface: **completely ECU independent**
> —— EXP_LayeredSoftwareArchitecture

| 关键词 | 含义 |
|---|---|
| **Generated** | 不是手写库，由 RTE 生成器根据配置产出 |
| **Per-ECU** | 同一套 SWC 在不同 ECU 上生成不同 RTE |
| **Upper: ECU independent** | 组件代码一份，跨 ECU 通用 |
| **Lower: 接 BSW** | 通过 Standardized Interface 调 BSW |

## 二、RTE 必须提供的五类能力

`TR_VFB` 3.8 明确了 RTE 的职责边界：

> The RTE must provide a **complete environment** for the component, including:
> - mechanisms through which the implementation can: provide values for PPorts, read RPorts, access calibration parameters, provide implementations for operations, invoke operations of other components
> - mechanisms through which the implementation is **invoked** in response to: **fixed-time schedules**, **communication events**, **physical events**
> - mechanisms to access other common resources, such as **instance-specific memory**
> - all common **synchronization mechanisms** (multi-threaded environment)

| # | 能力 | RTE API 形态 |
|---|---|---|
| 1 | 数据通信 | `Rte_Write_<p>_<d>()` / `Rte_Read_<p>_<d>()` |
| 2 | 服务调用 | `Rte_Call_<p>_<o>()` |
| 3 | 标定参数访问 | `Rte_Prm_<p>_<d>()` / Calibration Port |
| 4 | 触发与调度 | Runnable 由 RTE 调用（`TaskBody`） |
| 5 | 实例内存与同步 | `Rte_Enter_<mode>()`、Exclusive Area、IOC |

> [!important] 第 4 条是关键
> **组件不 main()、不 while(1)、不创建任务。** 组件只有 Runnable 函数，由 RTE 在合适的时机调用。
> 这叫**控制反转（IoC）**：组件交出执行权，换取部署自由。

## 三、RTE 生成物里到底有什么

看懂 RTE 生成代码，就真正理解了 AUTOSAR。

### 3.1 文件构成

| 文件 | 内容 |
|---|---|
| `Rte_<Swc>.h` | 该组件可用的 API 声明（组件只 include 这个） |
| `Rte_<Swc>.c` | 该组件相关的实现（读值、写值、调用） |
| `Rte.c` / `Rte.h` | RTE 核心（Start/Stop、模式机、IOC） |
| `Rte_Type.h` | 数据类型映射（ApplicationType → ImplementationType） |
| `Rte_Cbk.h` | 供 BSW 反向调用的回调声明（如 `Rte_COMCbk`） |
| `Rte_Main.h` | 生命周期函数（`Rte_Start`、`Rte_Stop`） |

### 3.2 三种连接的生成结果

| 连接场景 | `Rte_Write_X()` 生成的代码 | 开销 |
|---|---|---|
| **同 ECU、同 Task** | 直接写一个全局变量（或宏） | ≈ 0 |
| **同 ECU、不同 Task（同核）** | 写变量 + 临界区保护 | 少量 |
| **同 ECU、不同核** | IOC 发送（核间通信） | 较高 |
| **跨 ECU** | `Com_SendSignal()` → PduR → CanIf → Can | 最高 |
| **客户端-服务端（同 ECU）** | 直接函数调用 | ≈ 函数调用 |

示例（同 ECU 同 Task）：

```c
/* 生成结果近似于 */
#define Rte_Write_Pp_LightCmd(v)  (Rte_Inst_MySwc->LightCmd = (v))
#define Rte_Read_Rp_VehicleSpeed(v) (*(v) = Rte_Inst_MySwc->VehicleSpeed)
```

示例（跨 ECU）：

```c
Std_ReturnType Rte_Write_Pp_LightCmd(uint8 value) {
    return Com_SendSignal(COM_SIG_LIGHT_CMD, &value);
    /* 内部还会处理：发送模式、超时、更新位 */
}
```

> [!tip] 一个实用推论
> 同 ECU、同 Task 时可生成直接访问等优化，但实际成本由数据、触发和保护配置决定，应检查生成物。
> 同任务也可能存在复制、状态处理和触发成本，不能用部署位置单独断言零开销。
> 这决定了小项目要不要引入完整 RTE。

## 四、RTE 与 Task 的关系（最容易搞错）

映射链：

```
SwcInternalBehavior
    └── RunnableEntity（一个函数）
            ↓ 映射（由集成者配置）
        Task（OS 对象）
            ↓ 分配
        Partition（错误隔离域）
            ↓ 绑定
        Core（物理核）
```

| 规则 | 说明 |
|---|---|
| 一个 Runnable **只能**映射到一个 Task | 否则会有重入问题 |
| 一个 Task **可以**含多个 Runnable | 顺序执行 |
| 一个 Task 绑定一个 Partition | 分区是错误隔离单位 |
| 一个 Partition 绑定一个 Core | 核不共享 |
| Runnable 等待行为 | Category 1 不含等待点；Category 2 可含 WaitPoint，需要相应映射 |

> [!warning] 常见错误：把 Runnable 当线程用
> 不应随意在 Runnable 中使用无限循环或 RTOS 延时；标准 Category 2 等待点应按模型与生成合同处理。
> 长任务应拆分，或用状态机 + 多次调用（每次做一点）。

## 五、RTE 的三种工作模式

| 模式 | 说明 | 典型 API |
|---|---|---|
| **初始化** | `Rte_Start()` 前，只允许 `Rte_Init` 类调用 | `Rte_Start()` |
| **运行** | 正常调度，Runnable 被触发 | `Rte_Stop()` 退出 |
| **关闭** | 停止调度，允许清理 | — |

EcuM 的调用时序（摘自 `EXP_ModeManagementGuide` 的 BswM 规则）：

```c
actions SwitchToStartup on condition {
    custom "EcuM_DriverInitListTwo()"
    custom "Rte_Start()"                      /* ← RTE 在这里启动 */
    custom "EcuM_DriverInitListThree()"
    custom "ComM_CommunicationAllowed(TRUE)"
    custom "EcuM_SetState(ECUM_STATE_APP_RUN)"
}
```

## 六、RTE 的错误处理

| 错误类型 | 机制 |
|---|---|
| 开发错误（参数非法） | `Det_ReportError(RTE_MODULE_ID, ...)` |
| 运行错误（队列溢出） | `Det_ReportRuntimeError()` |
| 服务调用失败 | 返回 `Std_ReturnType`（`E_OK` / `E_NOT_OK`） |
| 数据失效 | Invalid Value（配置的失效值） |

→ 详见 [[05-错误处理三级分类]]

## 七、手写 RTE 可能吗

**可能，而且对小项目是合理的。** 判断标准：

| 项目特征 | 手写 RTE 等价物 | 用生成器 |
|---|---|---|
| 单 ECU、单核、少量 Task | ✅ 合理（宏 + 全局变量） | 工具链成本高 |
| 跨 ECU 通信多 | ⚠️ 手工维护易错 | ✅ 强烈推荐 |
| 多车型变体 | ⚠️ 需自建配置机制 | ✅ 推荐 |
| 需要与 OEM 交换 ARXML | ❌ 不可能 | ✅ 必须 |

> [!note] "手写 RTE"的正确姿势
> 不是"不抽象"，而是**用最薄的一层把"部署细节"隔离掉**：
> ```c
> /* rte_signals.h —— 只做信号语义映射，不含任何通信细节 */
> static inline void Rte_Write_LightCmd(uint8_t v) { sig_bind_light_cmd(v); }
> ```
> 关键：**业务层只调 `Rte_*`，不碰 `msg.data[]`**。
> 详见 [[03-Mini-AUTOSAR分层映射]]

## 八、RTE 的性能现实

| 场景 | 典型开销 | 优化方向 |
|---|---|---|
| 同 Task 读写 | 1~2 条指令 | 无需优化 |
| 跨 Task（同核） | 临界区进出（几 µs） | 减少跨 Task 交互，用数据副本 |
| 跨核 IOC | 10~50 µs | 批量传输、减少频次 |
| 跨 ECU CAN | 1~10 ms（取决于周期） | 合并信号、提高波特率、CAN FD |
| 服务调用（同 ECU） | ≈ 函数调用 | 无 |

> [!warning] 真实项目的性能陷阱
> "每个信号一个 `Rte_Write`" 在周期任务里可能导致：
> - 每次写都触发一次 Com 的发送请求检查
> - 一帧 CAN 内 8 个信号 → 8 次调用 → 实际只发 1 帧
> 是否使用 Signal Group、PENDING transfer property 或显式触发，应按一致性和发送需求设计；不能无条件额外触发而改变原有报文时序。

## 九、自检

1. 为什么 RTE 必须"每 ECU 生成一份"，而不能做成通用库？
2. 同 ECU 同 Task 的连接，RTE 生成的代码和直接赋值有区别吗？
3. 如果两个 SWC 在不同核，`Rte_Write` 会做什么？


## 本轮核对依据

- [SWS_RTE，PDF 第 150 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_RTE.pdf#page=150)：Category 2 Runnable 映射
- [SWS_COM，PDF 第 106 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf#page=106)：发送触发受 TransferProperty 与模式约束

---

**上一篇** → [[04-服务层]]
**下一篇** → [[06-复杂驱动CDD]]
**相关** → [[03-虚拟功能总线VFB]] | [[03-RTE生成与Runnable映射]]
**返回** → [[AUTOSAR知识地图]]
