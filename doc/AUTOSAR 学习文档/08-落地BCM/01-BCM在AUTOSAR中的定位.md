---
title: BCM 在 AUTOSAR 中的定位
aliases: [BCM定位, 车身控制器, Body Control Module]
tags: [落地, BCM]
source: [EXP_AIBodyAndComfort, EXP_LayeredSoftwareArchitecture]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# BCM 在 AUTOSAR 中的定位

> [!tip] 结论
> BCM 是车身控制功能的一种 ECU 部署方案，不是 AUTOSAR 规定的固定模块清单或固定硬件配置。参考车身域分解帮助明确接口与职责，实际功能按 OEM、硬件和系统架构确定。

## 一、可能承载的职责

灯光、门锁、按钮、雨刮、电源策略、外部负载与诊断等可在 BCM 实现，也可能分散到门控、灯控或区域控制器。不能声称 BCM 控制所有舒适功能或必然只是中等实时性。

BCM 可能聚合 IO、参与 CAN/LIN 通信和睡眠管理，但是否网关、是否 LIN master、采用何种诊断与安全机制都需输入确认。

## 二、与本项目的关系

当前已确认的设计输入是：MCU SDK／FreeRTOS 可提供；存在直连和 MUX 输入路线、I²C IO 扩展的需求；计划使用 DBC 生成代码与 dbcom；关心 UDS、DTC、NVM、下线测试及功能文件／任务划分。

尚未在本轮核实 MCU、引脚、负载、总线数、DBC 内容、DTC 清单、诊断规范和时序预算。其他目录虽有 OEM 文档，本轮不据其文件名推断具体技术要求。

## 三、首版能力按链路确定

输入／CAN 请求 → 语义与有效性 → 功能策略 → 输出仲裁 → 驱动 → 反馈／故障。

围绕此链路配置调度、存储、诊断和监控。具体模块选取见 [[04-裁剪决策记录]]；硬件路线见 [[06-IO端点与采集路线设计]]。

## 四、不能提前定死的指标

启动响应、保护时延、暗电流、NVM 保存时间、CAN 负载、栈与 CPU 余量必须有需求来源和测试方法。原笔记的固定电流／毫秒数不作为当前产品指标。

是否采用以太网、加密、E2E、多核与保护机制，不能仅凭“这是传统 BCM”全部排除，应以功能、网络、安全和资源分析决定。

## 五、自检

1. 功能分解与部署成一颗 BCM 有何区别？
2. 当前哪些是用户已确认输入，哪些需要实际资料验证？
3. 最小能力集合为何应围绕具体端到端链路确定？

## 核对依据

- [EXP_AIBodyAndComfort](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_AIBodyAndComfort.pdf)：车身功能参考分解与接口范围
- [EXP_LayeredSoftwareArchitecture](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf)：功能、平台与硬件职责边界

---

**上一篇** → [[05-R25-11变更要点]]
**下一篇** → [[02-车身域标准SWC分解]]
**返回** → [[AUTOSAR知识地图]]
