---
title: Mini-AUTOSAR 分层映射
aliases: [Mini AUTOSAR, 分层映射, 自研架构]
tags: [落地, BCM, 核心]
source: [EXP_LayeredSoftwareArchitecture, RS_BSWGeneral]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# Mini-AUTOSAR 分层映射

> [!tip] 定位
> 本项目目前确认的是 Git 仓库、官方与学习资料，以及你计划提供 MCU SDK／FreeRTOS。原笔记提及的既有六层代码、CVM014x 平台和通信工具不视为已审查事实。以下是拟议设计，不是现有代码审计结论，也不构成 AUTOSAR ICC 合规声明。

## 一、最小职责划分

```text
app/          lighting.c/.h、button.c/.h、door_lock.c/.h…
signals/      业务语义、通信映射、数据有效性和必要的薄连接
services/     生命周期、诊断、故障、存储、监控、控制权仲裁
io/           采集路线、扫描、信号调理、输出提交
devices/      RS2260、PCA9555/TCA9539、HSD 等具体器件
platform/     MCU SDK 与 FreeRTOS 适配
config/       原始配置、Schema、生成表；横切数据，不是调用中间层
```

这是职责建议，目录可合并，OS 适配也属于横向能力。MCU HAL 不等于完整 ECU 抽象；厂商 SDK 是软件，不是硬件本身。

## 二、解耦靠合同

| 边界 | 必须定义 |
|---|---|
| IO 端点 | 类型、设备通道、访问能力、同步／异步、错误 |
| 采集路线 | MUX、采样端、资源、建立时间、采样完成 |
| 逻辑信号 | 原始值／工程值、极性、滤波、有效性、时间戳 |
| 通信映射 | DBC 字段、枚举、单位、超时、命令／状态语义 |
| 输出 | 请求、控制者、已执行值、反馈、保护与归还控制 |
| 存储 | 数据布局、作业生命周期、提交和掉电恢复 |

硬件路线设计详见 [[06-IO端点与采集路线设计]]，通信和诊断联动见 [[07-业务绑定诊断与任务落地]]。

## 三、不要为了封装而封装

一个功能先一组 `.c/.h`，内部辅助函数和状态用 `static`。出现真实的多实例或跨功能复用后，再提取公共上下文和算法。

不强制所有代码经过一个巨大的 `rte_signals.c`。通信映射负责 DBC 语义转换，采集服务负责硬件路径，应用负责策略；薄接口只连接这些已经定义的职责。

函数名不必模仿 `Rte_*`。使用这个前缀也不会自动获得 RTE 的调度、一致性、模式和生成合同。

## 四、任务设计独立于文件设计

Task 按截止期、阻塞、资源归属和预算划分，多功能周期函数可共享一个 Task。IO 扫描状态机和存储作业不能阻塞应用任务，诊断通过请求接口访问硬件与输出仲裁。

对于 FreeRTOS，静态对象、状态快照、有界命令队列和明确溢出策略比机械照搬 AUTOSAR 模块数量更重要。

## 五、ICC 与自研定位

ICC1 的内部结构自由仍附带规定的外部行为及系统描述兼容要求。SDK＋FreeRTOS＋自定义配置可以是借鉴 AUTOSAR 的平台，不应自动称为“合法 AUTOSAR 子集”或“已满足 ICC1”。

若日后需要兼容某接口或协议，逐项记录版本、API、配置、时序、错误行为和测试证据。总线互通、接口兼容和完整平台合规是不同范围。

## 六、实施顺序与验收

1. 建立接口／资源模型、可重复构建和 PC 模拟端。
2. 跑通一条真实链路：按钮／CAN 请求 → 功能 → 输出 → 反馈。
3. 加入采集失败、超时、诊断控制、DTC 和存储异常恢复。
4. 用第二种路线、第二板卡或 MCU 验证复用边界。

不要预设几周必然完成。进度取决于 SDK、板卡、电路、协议矩阵、工具与验证资源。

## 七、自检

1. 哪些是当前确认的项目输入，哪些只是拟议设计？
2. 为什么功能文件和 Task 不必一一对应？
3. 薄语义接口与完整 RTE 有哪些能力差异？

## 核对依据

- [EXP_LayeredSoftwareArchitecture，PDF 第 75 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf#page=75)：ICC 外部行为及系统描述兼容约束
- [SWS_IOHardwareAbstraction，PDF 第 34 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_IOHardwareAbstraction.pdf#page=34)：输入多路复用与功率保护的实际边界
- [SWS_RTE](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_RTE.pdf)：标准 RTE 能力与自建薄接口的区别

---

**上一篇** → [[02-车身域标准SWC分解]]
**下一篇** → [[04-裁剪决策记录]]
**返回** → [[AUTOSAR知识地图]]
