---
title: 存储栈 MemIf-Fee-Fls
aliases: [MemIf, Fee, Fls, EA, 存储栈, 磨损均衡]
tags: [机制, 存储]
source: [EXP_NVDataHandling, SWS_MemoryAbstractionInterface, SWS_FlashEEPROMEmulation, SWS_MemoryDriver]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# 存储栈：MemIf、Fee、MemAcc 与 Mem

> [!tip] 版本结论
> 文件名保留以维持 Obsidian 旧链接。旧版常见链路是 `NvM → MemIf → Fee → Fls`；本库基于 R25-11，当前存储架构应核对 `NvM → MemIf → Fee/Ea → MemAcc → Mem`。Fls/Eep 规范已在该版本移除，不是只从架构图中隐藏。

## 一、新旧链路分开学习

```text
历史常见实现：NvM → MemIf → Fee/Ea → Fls/Eep → 存储硬件
R25-11 参考： NvM → MemIf → Fee/Ea → MemAcc → Mem → 存储硬件
```

具体外部存储驱动与总线驱动的连接依硬件和实现决定；上图不是所有可能拓扑的穷尽。

| 模块 | 核心职责 |
|---|---|
| NvM | 用户逻辑块、管理状态、CRC、冗余、默认值和作业管理 |
| MemIf | 抽象 Fee/Ea，按设备索引分派 API |
| Fee | 在 Flash 上实现逻辑块的 EEPROM 仿真 |
| Ea | EEPROM 的块抽象；真实 EEPROM 也有写入限制和寿命要求 |
| MemAcc | 硬件无关的地址区域访问与作业协调 |
| Mem | 硬件相关的 Memory Driver |

## 二、MemIf 不是按 NvM BlockId 范围自动路由

`MemIf_Write(DeviceIndex, BlockNumber, DataPtr)` 中，DeviceIndex 选择下层存储抽象实例，BlockNumber 标识该实例的块。NvM 的块配置决定设备与底层块映射，不能直接把 NvM 的 BlockId 当成跨层通用 ID。

只有一个下层实例时，规范允许 MemIf 用宏直接映射到对应模块，不需要增加运行时函数调用。因此“优化直连就一定不标准”是错误的。

## 三、异步作业的四件事

1. 返回 `E_OK` 通常只代表请求受理；完成状态通过规范 API／通知获取。
2. 必须持续推进所需 MainFunction 和底层完成处理。
3. 是否有队列、容量多少、忙时拒绝还是排队，逐层查规范；不能默认每个驱动都有任意深队列。
4. 缓冲区的生命周期与访问限制一直持续到规定的完成点。

MemAcc 规定每个 address area 只允许一个作业请求。NvM 队列能力不能自动推导为所有下层也支持多作业排队。

## 四、Fee 的职责与算法自由

追加记录、块映射、垃圾回收、扇区轮换是常见实现方法，不是标准唯一指定的“双扇区算法”。记录格式、提交标记、回收恢复和磨损策略应查供应商实现说明。

| 机制 | 解决的问题 | 不能直接保证 |
|---|---|---|
| CRC | 检测一定类别的数据损坏 | 写入原子性、语义正确、绝对无碰撞 |
| 冗余块 | 一份无效时有恢复来源 | 任意断电后必有最新值 |
| 写验证 | 检查写入结果 | 未来掉电时保存未提交数据 |
| 默认值 | 数据不可用时初始化 | 默认值一定满足所有工况 |
| 事务提交／恢复设计 | 区分已提交与未完成记录 | 超出硬件保证的无限故障容忍 |

正常掉电过程中应等待保存完成或执行明确的超时策略；意外断电无法靠“WriteAll 不允许被打断”消除，必须测试各个写入和回收阶段的恢复行为。

## 五、存储预算应来自实际器件

Flash 擦除粒度、写入粒度、寿命、读写并发、擦写期间 CPU 停顿、ECC 和温度影响全部查 MCU／存储器手册。不能套用“内部 Flash 都是 20~50 ms”“EEPROM 不需考虑磨损”等固定结论。

逻辑块不必一律按硬件页大小对齐；Fee/MemAcc/Mem 会施加各自的约束。过度打包小数据可能增加写放大，应结合写入频率、元数据和回收成本评估。

## 六、BCM 的实施建议

以 SDK 封装硬件存储访问，选择或实现经过掉电验证的块存储后端，再提供 NvM 风格的块管理。若选择保留旧 Fls 风格接口，明确标为项目兼容层，不声称它是 R25-11 的现行模块规范。

验收至少覆盖：空白存储、记录损坏、冗余退化、写入中复位、回收中断电、配置升级、空间不足、持续写入寿命预算。

## 七、自检

1. DeviceIndex 与 BlockNumber 各负责什么？
2. 为什么 CRC 和双备份不自动等于掉电事务安全？
3. R25-11 为什么不能只画 Fee → Fls 而不说明版本？

## 核对依据

- [TR_ReleaseOverview，PDF 第 18 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_TR_ReleaseOverview.pdf#page=18)：§2.2.4，Flash/EEPROM Driver 的 RS 与 SWS 被移除
- [SWS_MemoryAccess，PDF 第 7 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MemoryAccess.pdf#page=7)：§1、Figure 1.1 新存储架构
- [SWS_MemoryAccess，PDF 第 19 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MemoryAccess.pdf#page=19)：[SWS_MemAcc_00018]，每个地址区域一个作业
- [SWS_MemoryAbstractionInterface，PDF 第 17 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MemoryAbstractionInterface.pdf#page=17)：[SWS_MemIf_00018]、[SWS_MemIf_00019]，设备选择及单实例宏映射
- [SWS_FlashEEPROMEmulation](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_FlashEEPROMEmulation.pdf)：Fee 行为和配置，算法示例不得替代规范

---

**上一篇** → [[08-看门狗与监控]]
**下一篇** → [[01-通信栈全景]]
**相关** → [[06-NVM数据管理]]
**返回** → [[AUTOSAR知识地图]]
