---
title: 库函数与 ICC 一致性类
aliases: [Libraries, ICC, Implementation Conformance Class, 一致性类]
tags: [架构, 裁剪]
source: [EXP_LayeredSoftwareArchitecture]
created: 2026-10-23
reviewed: 2026-10-23
review_basis: AUTOSAR CP R25-11 本地官方资料
review_scope: 重点技术内容核对与修订
---

# 库函数与 ICC 一致性类

> [!tip] 结论
> 库与模块的区分帮助组织公共能力；ICC 描述实现组织与兼容范围。二者都不能通过名字推断安全性、合规性或可任意删减的范围。

## 一、库的架构特征与具体 SWS

架构文档描述库通常在调用者上下文与保护环境运行，强调可重入、无独立运行生命周期、同步等特征。具体库仍可能有调用者持有的状态、配置、初始化函数及特定依赖。

例如 E2E 有 Protect/Check state 和初始化相关服务；“库没有内部私有状态”不能理解为 E2E 算法不需要任何状态。并发使用同一状态对象也不会因函数叫库函数就自动安全。

## 二、常见库

| 库 | 用途 |
|---|---|
| Bfx | 位操作 |
| Crc | 规定参数与语义的 CRC 计算 |
| Ifx / Ifl | 定点／浮点插值 |
| Mfx / Mfl | 定点／浮点数学 |
| Efx | 扩展数学功能，具体以 SWS 为准 |
| E2E | 按 Profile 进行保护／检查及状态管理 |
| Bmc | 多核安全操作相关公共功能 |
| Msf | **Memory Standard Function Library**，标准化内存复制、移动、填充等函数；本地 R25-11 API 标有 DRAFT |

## 三、MSF 与 libc 的重要纠正

SWS_MSFLibrary §1 称其为 Memory Standard Function Library；§8.3 明确定义 `Msf_MemCopy`、`Msf_MemCopyAligned_u32`、`Msf_MemMove`、`Msf_MemSet_<TypeMn>` 等。该版相关条目为 DRAFT。不能仅按首页变更历史的不同措辞推导功能，也不能凭这份规范虚构 MemCompare API 或宣称必须全面替代 libc。

是否使用编译器提供的 memcpy/memset，取决于项目规则、供应商库特性、工具链、验证与调用约束。规范存在不等于任意实现已经获得 MISRA 或安全保证；也不能说链接 memcpy 必然引入 printf 全家桶。

## 四、ICC 的边界

| 类 | 主要理解 |
|---|---|
| ICC1 | 内部私有结构不按标准模块／簇限制 |
| ICC2 | 以声明的簇边界组织 |
| ICC3 | 标准模块接口与行为组织 |

架构文档要求 ICC1–3 的外部行为遵循 ICC3 规范，并要求 ICC1/2 配置相对系统描述的兼容性。内部结构自由不是对外协议、配置、错误和时序自由。

ICC2 的簇划分也不是本笔记所列若干模块天然构成一个被认可的簇；需要声明边界及证据。ICC3 不是要求每个 ECU 无条件装入全部 127 份 SWS 对应内容。

## 五、自建框架的合适定位

SDK＋FreeRTOS＋自定义配置框架可以借鉴接口、分层和配置思想。若希望兼容某些 API、协议或数据模型，列明版本、支持范围、例外和测试；不要由“总线报文互通”推导完整 ICC 合规。

## 六、自检

1. E2E 有状态对象为什么仍被称为 Library？
2. MSF 的 API 在本版本是什么状态？复制与移动的重叠约束有何区别？
3. ICC1 的内部自由附带哪些外部约束？

## 核对依据

- [SWS_MSFLibrary，PDF 第 1 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MSFLibrary.pdf#page=1)：Memory Specific Function library 名称与版本历史
- [SWS_MSFLibrary](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MSFLibrary.pdf)：MSF 的实际 API 与功能
- [SWS_E2ELibrary，PDF 第 31 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_E2ELibrary.pdf#page=31)：ProtectState 等状态类型
- [EXP_LayeredSoftwareArchitecture，PDF 第 74 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf#page=74)：ICC1
- [EXP_LayeredSoftwareArchitecture，PDF 第 75 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf#page=75)：ICC 外部行为与系统描述约束


## 本轮核对依据

- [SWS_MSFLibrary，PDF 第 5 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MSFLibrary.pdf#page=5)：§1 的全称与范围
- [SWS_MSFLibrary，PDF 第 14 页](file:///H:/Bcm_Frame/doc/AUTOSAR-CP_R25-11%E5%AE%98%E6%96%B9%E8%B5%84%E6%96%99/AUTOSAR_CP_SWS_MSFLibrary.pdf#page=14)：[CP_SWS_Msf_00003] Msf_MemCopy，DRAFT 及不重叠约束

---

**上一篇** → [[11-分区与多核]]
**下一篇** → [[01-方法论总览-V模型产物链]]
**相关** → [[01-分层架构总览]]
**返回** → [[AUTOSAR知识地图]]
