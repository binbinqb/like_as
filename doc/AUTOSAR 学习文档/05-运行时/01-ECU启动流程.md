---
title: ECU 启动流程
aliases: [启动流程, Startup, StartPreOS, StartPostOS, 上电时序]
tags: [机制, 核心]
source: [SWS_ECUStateManager, EXP_ModeManagementGuide]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# ECU 启动流程

> [!tip] 结论
> 先建立最小硬件和 C 运行环境，再由 EcuM 协调 StartPreOS、StartOS、StartPostOS，后续初始化与运行使能由依赖和模式规则决定。不能把指南示例中的四个列表当成所有模块固定归属的规范表。

## 一、启动前置

复位入口和启动代码建立栈、C 数据区等基本环境后，才可调用 EcuM_Init。某些硬件初始化必然发生在其前面；是否合法取决于需求和调用合同，不是“任何需要配置的代码都不能在前面”。

## 二、StartPreOS

按 SWS 的序列执行中断相关设置、`EcuM_AL_DriverInitZero`、后构建配置确定与一致性检查、`EcuM_AL_DriverInitOne`、复位／唤醒原因处理、关机目标选择及相应活动，再启动 OS。具体 optional 与条件查序列表及配置。

InitZero 不能使用尚未确定的 post-build 配置；InitOne 与其余阶段按启动 OS 的必需依赖组织。此阶段尽量短，一般不使用中断；如必须使用，按规范只允许 Category I。

## 三、StartPostOS

集成方安排自动启动的 OS Task，调用 `EcuM_StartupTwo`。SWS 的 Figure 7.5 顺序为：

```text
SchM_Start → BswM_Init → SchM_Init → SchM_StartTiming
```

这是本地版本给出的顺序，但不能用“BswM 先能跑所以信号量可以后初始化”擅自解释所有实现；还需检查相应 SchM/RTE 生成合同。

## 四、后续初始化是依赖图

模式指南中的 DriverInitListTwo/Three 是示例动作安排，不能直接推出“所有 NvM/Dem/Dcm 一定在 RTE_Start 后初始化”。

应列出模块前置条件：时钟／Port／总线 → 外部芯片 → 存储后端 → NvM 初始化与读取 → Dem 恢复 → 应用必要数据就绪 → 按配置启动 RTE／业务与通信。实际顺序随依赖而定，不是照抄此箭头作为唯一顺序。

存在 Dem 早期初始化和后续完整初始化等场景，必须核对真实模块初始化合同。数据尚未恢复时不应发布“有效默认配置”冒充已加载用户数据。

## 五、配置一致性

EcuM 有运行时检查 post-build 配置与代码构建信息的一致性机制。初始化零块已在更早阶段运行，不能将“首次 BSW 初始化前检查”脱离 InitZero 上下文扩展为所有活动都未发生。

本项目若支持独立配置镜像，定义版本、结构、长度、完整性、合法性与可恢复更新；哈希或 CRC 单独不能证明语义兼容。

## 六、启动、运行和休眠

STARTUP/UP/SHUTDOWN/SLEEP/OFF 是相关阶段概念，不能仅画成一条总是返回复位入口的循环。Halt/Poll、唤醒检查、验证和恢复依实际目标与硬件选择。

启动时限、暗电流、关键输出和掉电保存时间必须来自产品规范。原来的 100 ms、1 mA 等只可作为示例，不作为已确认指标。

## 七、自建 FreeRTOS 框架

保留启动依赖、分阶段就绪、配置检查、复位原因、异常路径和关闭协调；不必为了外观实现全部 EcuM API。任务创建、启用中断和启动调度器的时点要按 FreeRTOS port 与 SDK 检查。

## 八、自检

1. 为什么 NvM 初始化与 NvM_ReadAll 完成是两个阶段？
2. InitZero 与 post-build 配置检查有什么先后约束？
3. 为什么模块初始化列表要由依赖而非固定名称分配？

## 核对依据

- [SWS_ECUStateManager，PDF 第 37 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_ECUStateManager.pdf#page=37)：启动前置及 StartupTwo 入口
- [SWS_ECUStateManager，PDF 第 41 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_ECUStateManager.pdf#page=41)：InitZero/One、Category I 及 pre-OS 边界
- [SWS_ECUStateManager，PDF 第 42 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_ECUStateManager.pdf#page=42)：Figure 7.5 StartPostOS 顺序
- [SWS_NVRAMManager，PDF 第 78 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_NVRAMManager.pdf#page=78)：NvM_Init 不初始化永久 RAM 内容，ReadAll 承担恢复
- [EXP_ModeManagementGuide](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_ModeManagementGuide.pdf)：示例编排与模式管理

---

**上一篇** → [[08-工作流实例]]
**下一篇** → [[02-模式管理EcuM与BswM]]
**相关** → [[09-存储栈MemIf-Fee-Fls]]
**返回** → [[AUTOSAR知识地图]]
