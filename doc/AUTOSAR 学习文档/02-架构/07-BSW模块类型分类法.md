---
title: BSW 模块类型分类法
aliases: [Driver, Interface, Handler, Manager, 模块类型]
tags: [架构, 核心]
source: [EXP_LayeredSoftwareArchitecture]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# BSW 模块类型分类法

> [!tip] 结论
> Driver、Interface、Handler、Manager 是架构中的职责特征，不是可凭两条判断完全推导出的互斥类型。一个模块可兼有多个角色，具体职责以对应 SWS 为准。

## 一、四种职责特征

| 角色 | 核心理解 |
|---|---|
| Driver | 控制和访问内部或外部器件 |
| Interface | 隐藏下层器件数量、位置或硬件实现差异 |
| Handler | 协调多个客户端对驱动的并发／异步访问，例如缓冲、排队、仲裁、复用 |
| Manager | 提供超出搬运／仲裁的服务，可以评估、改变或适配数据 |

原笔记“五类”将 internal driver 与 external driver 分开计数，这可用于学习，但不是五个互斥元模型类别。

## 二、内部与外部驱动

内部器件驱动通常属于 MCAL；外部器件驱动通常通过 MCAL 的 Spi、I2c、Dio 等访问，属于相应板级抽象。内存映射的外部器件若直接依赖 MCU 访问机制，是架构文档特别讨论的例外。

不能单凭“器件在芯片外”或文件名含 Driver 决定位置。应结合标准的功能域与具体 SWS，尤其是收发器和 Memory Driver。

## 三、不要把“改数据”变成唯一判据

架构文档说 Manager **can** evaluate/change/adapt data，不是所有 Manager 都必须修改载荷。Driver 也必须判断忙闲、参数、硬件状态和故障，并常有状态机。

“驱动不能判断、不能有状态机”“有 CRC 就是 Manager”“只有 Manager 能做格式变化”都不是可靠的推论。

| 模块 | 理解重点 |
|---|---|
| Spi Handler/Driver | 同时体现硬件驱动与异步访问组织 |
| Adc | 组、触发、缓冲与转换状态，不能说只有寄存器读写 |
| CanIf | 控制器／PDU 抽象，同时可能含发送缓冲 |
| CanTp | 特定传输协议职责，不必强行命名为半个 Manager |
| NvM | 块与作业管理、校验、恢复、默认值 |
| IoHwAb | ECU 信号抽象与所需调理／诊断，API 不是固定的通用 GPIO 表 |

## 四、设计时怎样使用

先问模块对外承诺什么，再明确内部所需角色。对 PCA9555，设备协议与影子寄存器属于设备驱动；共享 I²C 访问由相应总线服务协调；MUX 扫描由采集机制负责；有效极性和物理量解释属于信号配置／调理。

这些职责可以分成几个文件，也可以在小规模实现中组合，但应有清楚的数据所有权、完成通知、超时和错误边界。不要为了凑角色数量增加空封装。

## 五、自检

1. 为什么 Spi 可以同时是 Handler 与 Driver？
2. 为什么一个驱动有状态机并不构成越界？
3. 怎样区分芯片驱动与输入采集路线管理？

## 核对依据

- [EXP_LayeredSoftwareArchitecture](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf)：Driver、Interface、Handler、Manager 定义
- [SWS_IOHardwareAbstraction，PDF 第 34 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_IOHardwareAbstraction.pdf#page=34)：多路输入与功率芯片示例

---

**上一篇** → [[06-复杂驱动CDD]]
**下一篇** → [[08-三种接口类型]]
**相关** → [[04-分层哲学的由来]]
**返回** → [[AUTOSAR知识地图]]
