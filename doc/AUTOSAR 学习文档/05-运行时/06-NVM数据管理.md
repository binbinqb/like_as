---
title: NVM 数据管理
aliases: [NvM, NVRAM, NVM, 非易失存储]
tags: [机制, 核心]
source: [EXP_NVDataHandling, SWS_NVRAMManager]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# NVM 数据管理

> [!tip] 结论
> NvM 管逻辑块与存储作业，不是所有实时变量的保存容器。采样和诊断实时值通常驻留 RAM；需要掉电保留的数据才按明确策略持久化。

## 一、四种基本存储对象

RAM Block、ROM Block、NV Block、Administrative Block 共同描述一个逻辑 NVRAM Block。Admin 是管理状态，不是用户数据的第四份副本；ROM 是默认数据来源，RAM 可为永久块或通过请求提供的临时缓冲。

| 管理类型 | NV 数据组织 | 适用考虑 |
|---|---|---|
| Native | 一个 NV Block | 普通块；不代表数据一定不重要 |
| Redundant | 两个 NV Block | 提升对数据损坏的恢复能力，不是绝对原子事务 |
| Dataset | 多个等长 NV／ROM 数据实例 | 使用 DataIndex 选择，需配置数量与合法范围 |

冗余写入增加成本，但总耗时不保证恰好两倍。恢复、CRC、写验证与事务行为应结合后端验证。

## 二、同步与缓冲所有权

隐式同步共享应用数据区，必须保证作业期间缓冲满足规范的一致性与生命周期要求。显式同步通过回调复制到／从 NvM RAM mirror，**不会自动消除应用内部的并发问题**：拷贝时仍要快照、短临界区或版本机制。

显式／隐式同步不等于同步／异步服务。`NvM_WriteBlock` 是异步作业；返回成功只是受理，必须处理完成和失败。

`NULL_PTR` 不总是非法：某些 API 在配置了永久 RAM 块时使用空指针选择它。不能套用统一“非空检查”的示例替代 API 规范。

## 三、CRC 比较与默认恢复

`NvMCalcRamBlockCrc` 与 `NvMBlockUseCRCCompMechanism` 不是同一配置。启用 RAM CRC 计算不代表所有写作业都会自动跳过相同数据；具体比较机制及冗余退化时的行为查 SWS。

默认值来自配置的 ROM 数据或初始化回调等路径，不能固定描述为“ROM 失败后一定再调用另一个回调”。写验证用于检查本次写入结果，不能保证未保存的数据在突然掉电后存在。

## 四、软件升级与配置版本

`NvMDynamicConfiguration`、`NvmCompiledConfigID` 与每块的 `NvMResistantToChangedSw` 共同影响配置变更后的初始化行为。不是打开 DynamicConfiguration 后就永远不用 NV 数据。

保持稳定块映射，并为用户数据定义布局版本、兼容性和迁移策略。ConfigID 是配置兼容机制，不会自动把旧结构转换为新结构。

## 五、启动与关闭

初始化各存储层 → `NvM_Init` → 按配置发起 `NvM_ReadAll` → 跟踪选中块的结果 → 发布数据可用状态。

关闭时由集成的模式管理规则发起所需保存，等待完成或进入明确的超时／故障策略。**不能一边忙等，一边停止运行推进作业所需的任务和 MainFunction。**

完成状态查询的 API 形态是：

```c
Std_ReturnType NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType *RequestResultPtr);
```

`Std_ReturnType` 表示状态查询本身是否成功，作业结果写入输出参数。多块作业状态按规范约定查询或接收通知；不能写成 `while (NvM_GetErrorStatus(&blk) == NVM_REQ_PENDING)`。

RUN 请求可以作为集成策略，但不是 NvM 必须自行 RequestRUN/ReleaseRUN 的唯一标准方案。见 [[02-模式管理EcuM与BswM]]。

## 六、BCM 数据放置

| 数据 | 建议位置 | 持久化策略 |
|---|---|---|
| 数字／模拟采样、HSD 当前诊断 | 静态 RAM 样本表 | 默认不写 |
| UDS 接收响应、测试上下文 | 有界静态缓冲／内存池 | 默认不写 |
| 诊断强制输出权 | RAM | 会话／超时后释放 |
| 车型编码、标定、用户设置 | RAM 工作副本＋NV | 按变更和产品要求保存 |
| DTC 与冻结帧 | Dem 工作数据＋配置的 NV | 由 Dem 协调，不重复维护第二套 DTC |
| 下线测试结果 | 依追溯需求决定 | 必要时保存结果、版本及校验 |

静态／动态是 RAM 分配方式；是否写 NVM 是持久性决策，二者不是互斥选项。

## 七、必须验证的异常

作业受理失败、队列满、同块并发、缓冲被修改、写入中复位、GC 中断电、CRC 失败、默认值不适用、版本迁移、存储耗尽。后端链路见 [[09-存储栈MemIf-Fee-Fls]]。

## 八、自检

1. 显式同步为何仍需应用保证快照一致？
2. NvM_GetErrorStatus 的返回值和输出参数各是什么？
3. ConfigID 为何不能代替用户结构的迁移设计？

## 核对依据

- [SWS_NVRAMManager，PDF 第 29 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_NVRAMManager.pdf#page=29)：块管理类型
- [SWS_NVRAMManager，PDF 第 32 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_NVRAMManager.pdf#page=32)：冗余恢复的范围
- [SWS_NVRAMManager，PDF 第 103 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_NVRAMManager.pdf#page=103)：CRC comparison 的条件与冗余例外
- [SWS_NVRAMManager，PDF 第 114 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_NVRAMManager.pdf#page=114)：NvM_WriteAll 的异步语义
- [SWS_NVRAMManager](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_NVRAMManager.pdf)：NvM_GetErrorStatus、同步机制及配置变更处理
- [EXP_NVDataHandling](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_NVDataHandling.pdf)：运行数据、持久化与同步的背景

---

**上一篇** → [[05-错误处理三级分类]]
**下一篇** → [[07-诊断DCM与DEM]]
**相关** → [[09-存储栈MemIf-Fee-Fls]]
**返回** → [[AUTOSAR知识地图]]
