/**
 * @file    Dcm_Cfg.h
 * @brief   Dcm 的服务裁剪、会话掩码与周期
 *
 * @details @section DCMCFG_SVC 只编需要的三个服务
 *          `Dcm_Dsp.c` 2300 行里绝大部分被 `DCM_USE_SERVICE_*` 包着，
 *          不定义就不编进来。M3 最小集只要：
 *          | 服务 | SID | 用途 |
 *          |------|-----|------|
 *          | SessionControl | 0x10 | `10 03` 进扩展会话 |
 *          | ReadDataByIdentifier | 0x22 | `22 F1 90` 读 VIN（17 字节 → 强制多帧） |
 *          | TesterPresent | 0x3E | `3E 00` 保活，防 S3 超时 |
 *
 *          **不定义** `DCM_USE_SERVICE_SECURITY_ACCESS`：一旦定义，
 *          `Dcm_SesSecAccessType` 会从 2 个字段变成 3 个，所有初始化器都要跟着改。
 *          这也是最容易踩的坑 —— 结构体成员随宏变化，编译期不报错、运行时错位。
 *
 *          @section DCMCFG_MASK 会话掩码是位图，不是会话号
 *          规则是 `1 << (sessionId - 1)`：
 *          | 会话 | ID | 掩码 |
 *          |------|----|------|
 *          | Default | 0x01 | 0x01 |
 *          | Programming | 0x02 | 0x02 |
 *          | Extended | 0x03 | 0x04 |
 *          `DCM_ANY_SESSION_MASK`(0xFF) 表示"任何会话都允许"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：0x10 / 0x22 / 0x3E，无安全访问 |
 */

#ifndef DCM_CFG_H
#define DCM_CFG_H

/* ============================ [ 周期 ] ============================ */

/** @brief `Dcm_MainFunction()` 的调用周期（ms） */
#define DCM_MAIN_FUNCTION_PERIOD    (10u)

#define DCM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                           \
	(((x) + DCM_MAIN_FUNCTION_PERIOD - 1u) / DCM_MAIN_FUNCTION_PERIOD)

/* ============================ [ 服务裁剪 ] ============================ */

/** @brief 0x22 ReadDataByIdentifier */
#define DCM_USE_SERVICE_READ_DATA_BY_IDENTIFIER

/** @brief 0x3E TesterPresent */
#define DCM_USE_SERVICE_TESTER_PRESENT

/**
 * @brief 0x14 ClearDiagnosticInformation
 * @note  打开这个开关会编译 `Dcm_Dsp.c:1139` 那段，它**硬编码调用 Dem**
 *        （`Dem_SelectDTC` / `Dem_ClearDTC`），所以必须同时链接 Dem 库。
 *        本工程的 Dem 是 `infras/diagnostic/Dem/` 里的简化实现，
 *        接口与 AUTOSAR 一致，只是没有去抖和老化。
 */
#define DCM_USE_SERVICE_CLEAR_DIAGNOSTIC_INFORMATION

/**
 * @brief 0x19 ReadDTCInformation
 * @note  同样硬编码调 Dem。本工程只注册三个子功能
 *        （0x01 报告数量 / 0x02 按状态掩码报告 / 0x0A 报告支持的 DTC），
 *        其余子功能（快照、扩展数据、镜像内存）依赖的 Dem 接口没实现，
 *        注册进来会链接失败 —— 这也是"只注册用得上的"另一个理由。
 */
#define DCM_USE_SERVICE_READ_DTC_INFORMATION

/**
 * @brief 0x27 SecurityAccess
 *
 * @warning **打开它会让 `Dcm_SesSecAccessType` 从 2 个字段变成 3 个**
 *          （多一个 `securityMask`，插在 `sessionMask` 和 `miscMask` 之间）。
 *          所有服务表、DID 表、0x19 子功能表里的初始化器**都要补一位**，
 *          漏改不会编译报错 —— 因为 `DCM_MISC_PHYSICAL` 之类的宏是整数，
 *          会被静默赋给 `securityMask`，`miscMask` 变成 0，
 *          现象是"所有服务都回 NRC 0x10/0x11"，非常难查。
 *          本文件的每个初始化器都改成了**逐字段命名注释**，就是为了防这个。
 *
 * @note  本工程 `securityMask` 一律填 `0x01`（bit0 = `DCM_SEC_LEV_LOCKED`），
 *        意思是"未解锁状态下也允许"。换句话说：**0x27 开了，但不挡任何服务**，
 *        符合"暂时都通过"的要求。将来要真正限制某个服务，
 *        把它那一项的 `securityMask` 从 `0x01` 改成 `0x02`（bit1 = level 1）即可。
 */
#define DCM_USE_SERVICE_SECURITY_ACCESS

/**
 * @brief 0x2E WriteDataByIdentifier
 * @note  本工程只允许写 `0xF190`（VIN）。写的数据落到 NvM 的 VIN 块，
 *        与 0x22 读的是**同一份数据** —— 否则会出现"写完读不到"，
 *        而且排查时两边各看一次都显示"正常"。
 */
#define DCM_USE_SERVICE_WRITE_DATA_BY_IDENTIFIER

/* ============================ [ 刷写服务（A/B） ] ============================ */
/*
 * 0x31 / 0x34 / 0x36 / 0x37 / 0x11 是 A/B 升级的最小集合：
 *   31 01 FFxx  擦除非活动槽 / 校验镜像
 *   34/36/37    下载到非活动槽，37 时写 meta
 *   11 01       复位，让 boot 跳新槽
 *
 * 业务实现全在 `app/app/src/flash_loader.c`，这里只是打开编译开关。
 *
 * @note 这四个开关会改变 `Dcm_ConfigType` 的**字段数量**（rtCtrlConfig 等），
 *       所以 `Dcm_Cfg.c` 里的 `Dcm_Config` 初始化必须同步补字段。
 *       漏补的后果不是编译错，而是后面的字段整体错位 —— 症状是
 *       "开一个服务，另一个无关服务突然坏了"。本工程的初始化器一律
 *       带字段名注释，就是为了让这种错位在 code review 时能看出来。
 */

/** @brief 0x31 RoutineControl */
#define DCM_USE_SERVICE_ROUTINE_CONTROL

/** @brief 0x34 RequestDownload */
#define DCM_USE_SERVICE_REQUEST_DOWNLOAD

/** @brief 0x36 TransferData */
#define DCM_USE_SERVICE_TRANSFER_DATA

/** @brief 0x37 RequestTransferExit */
#define DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT

/** @brief 0x11 ECUReset */
#define DCM_USE_SERVICE_ECU_RESET

/* 0x10 SessionControl 无需开关，Dcm_Dsp.c 里始终编译 */

/* ============================ [ 会话 ] ============================ */

/** @brief 扩展诊断会话 ID（AUTOSAR 只预定义了 Default/Programming） */
#define DCM_EXTENDED_SESSION        (0x03u)

/** @brief 会话掩码 = 1 << (会话ID - 1) */
#define DCM_DEFAULT_MASK            (0x01u)
#define DCM_EXTENDED_MASK           (0x04u)

/* ============================ [ 缓冲 ] ============================ */

/**
 * @brief 诊断收发缓冲大小
 * @note  必须 >= 最长的一条诊断请求/响应。VIN 响应 20 字节，
 *        留 128 字节给将来的 `2E` 写 DID / `31` 例程控制。
 */
#define DCM_RX_BUF_SIZE             (128u)
#define DCM_TX_BUF_SIZE             (128u)

#endif /* DCM_CFG_H */
