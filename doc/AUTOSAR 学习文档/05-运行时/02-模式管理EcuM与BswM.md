---
title: 模式管理 EcuM 与 BswM
aliases: [Mode Management, EcuM, BswM, 模式管理, 睡眠唤醒]
tags: [机制, 核心]
source: [EXP_ModeManagementGuide, SWS_ECUStateManager, SWS_BSWModeManager]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# 模式管理：EcuM 与 BswM

> [!tip] 结论
> EcuM 协调 ECU 生命周期与唤醒，BswM 进行配置的模式仲裁与动作编排，RTE/SchM 提供相应模式机制。BswM 不是系统中唯一允许决策的模块，应用、ComM、CanSM 等也各有自己的策略和状态。

## 一、模式不是任意共享全局变量

ModeDeclaration、ModeDeclarationGroup 和模式实例描述有效状态与切换机制。Manager 与 User 的角色、切换通知、入口／出口事件、失能条件和确认应由模型与服务规定。

指南使用全局状态变量帮助解释，不表示实现必须放一个谁都能写的全局变量。状态查询、切换请求与实际切换完成需要区分。

## 二、BswM 的规则

输入状态／请求 → 逻辑表达式 → 仲裁规则 → 动作列表。可以即时处理或延后到主函数，取决于配置；动作包括规定的 BSW 服务、路由／通信组控制、模式切换及用户 callout。

模式指南中的 `rule ... actions ... custom` 是讲解伪语法，不是标准 C 或可直接输入某生成器的统一 DSL。规则生成出来仍然是代码，不能说“完全没有逻辑代码”。

## 三、RUN／POST_RUN 请求

`EcuM_RequestRUN(User)` / Release 等按配置用户和 API 合同管理请求。不要把它实现成任意重复递增／递减的无界引用计数；要处理重复请求、释放未请求用户等情况。

允许关机还取决于保存、网络、唤醒、硬件目标等条件。“所有 RUN 请求释放”只是协调输入，不能单独证明可立即断电。

NvM 保存完成可以通过 BswM 状态通知和集成动作协调；自建框架也可使用明确的电源保持请求。不能说 NvM 必须在内部自动 RequestRUN 才是标准方法。

## 四、通信开关的层次

| 控制 | 范围 |
|---|---|
| ComM 通信需求 | 用户／通道的通信仲裁 |
| CanSM 等 | 总线相关模式与恢复 |
| CanNm／其他 NM | 网络睡眠／唤醒协调 |
| Com I-PDU Group | Com 自身配置的业务 I-PDU |
| PduR routing group | 对应配置路径的启停 |
| Dcm 通信控制 | 按诊断服务与模式规则协调 |

**诊断 TP 和 NM PDU 不自动属于 Com 的 DIAG/NM 组。** 不能通过一组 `Com_IpduGroupStart/Stop` 代表全部诊断与 NM 通信控制。

## 五、BCM 关闭与唤醒

建立状态机并定义：请求收敛、停止新的业务作业、保留必需通信、保存与超时、唤醒源设置、外设休眠、竞态检查、进入低功耗、检查／验证唤醒、恢复数据与模式。

应覆盖“准备睡眠期间新请求到达”“保存失败”“唤醒源持续有效”“诊断仍有控制权”等场景，避免一次性顺序函数遗漏竞态。

## 六、任务与多核

模式机制依赖执行上下文和共享状态保护；FreeRTOS 实现可用有界请求队列与单写者状态机。多核时按 EcuM 主／从核和各分区的 BswM 配置组织，不能简单复制全部模块。

## 七、自检

1. 模式请求和模式切换完成有何区别？
2. 为什么 RUN 请求不能简单当成任意引用计数？
3. Com I-PDU Group 为何不能替代诊断和 NM 的状态控制？

## 核对依据

- [SWS_ECUStateManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_ECUStateManager.pdf)：RUN 用户请求、关机目标、唤醒与多核流程
- [SWS_BSWModeManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_BSWModeManager.pdf)：仲裁、动作列表、请求处理与状态通知
- [EXP_ModeManagementGuide](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_ModeManagementGuide.pdf)：模式角色与示例伪语法
- [SWS_COM](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_COM.pdf)：Com I-PDU Group 的作用域

---

**上一篇** → [[01-ECU启动流程]]
**下一篇** → [[03-RTE生成与Runnable映射]]
**相关** → [[06-NVM数据管理]] | [[07-网络管理NM与ComM]]
**返回** → [[AUTOSAR知识地图]]
