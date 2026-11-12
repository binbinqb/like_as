/**
 * @file    Dcm_Cfg.h
 * @brief   boot 版 Dcm 配置：只有"会话 + 安全 + 刷写"三块
 *
 * @details @section BOOTDCM_SVC 服务集与 app 的差别
 *
 *          | 服务 | SID | boot | app | 为什么 |
 *          |------|-----|------|-----|--------|
 *          | SessionControl | 0x10 | ✅ | ✅ | 编程会话是刷写前提 |
 *          | ECUReset | 0x11 | ✅ | ✅ | 刷完复位跳新镜像 |
 *          | SecurityAccess | 0x27 | ✅ | ✅ | 擦写 Flash 必须解锁 |
 *          | RoutineControl | 0x31 | ✅ | ✅ | 擦槽 / 校验 CRC |
 *          | RequestDownload | 0x34 | ✅ | ⚠️ D1 后关 | 刷写入口 |
 *          | TransferData | 0x36 | ✅ | ⚠️ D1 后关 | 传数据 |
 *          | RequestTransferExit | 0x37 | ✅ | ⚠️ D1 后关 | 结束传输 |
 *          | TesterPresent | 0x3E | ✅ | ✅ | 防 S3 超时 |
 *          | ReadDataByIdentifier | 0x22 | ❌ | ✅ | 依赖 NvM 的 VIN 表；boot 暂不做 |
 *          | WriteDataByIdentifier | 0x2E | ❌ | ✅ | 同上 |
 *          | ClearDTC / ReadDTC | 0x14/0x19 | ❌ | ✅ | 依赖 Dem |
 *
 *          **不开 0x22 不等于 boot 用不了 NvM**：`Boot_StorageSelfTest()`
 *          已经在启动时把 VIN 读到 RAM。将来若福田规范要求编程会话下能读 VIN，
 *          只需在这里加 `DCM_USE_SERVICE_READ_DATA_BY_IDENTIFIER` +
 *          一张 `Dcm_rDIDConfigs`（约 30 行），NvM 通路现成。
 *
 * @warning **`DCM_USE_SERVICE_*` 不只是"编不编那段代码"**：它还会改变
 *          `Dcm_ConfigType` 的字段数（见 `Dcm_Priv.h:558` 的条件字段）。
 *          所以 boot 的 `Dcm_Cfg.c` 必须与这份头文件的宏**严格一致** ——
 *          两者错位不会编译报错，只会让初始化器整体偏移一格，
 *          运行期表现为"某个函数指针指向了别的字段"，极难定位。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用 7 个服务 |
 */

#ifndef DCM_CFG_H
#define DCM_CFG_H

/* ============================ [ 周期 ] ============================ */

/** @brief `Dcm_MainFunction()` 的调用周期（ms），必须与 boot 主循环一致 */
#define DCM_MAIN_FUNCTION_PERIOD    (10u)

/** @brief 毫秒 → 主函数周期数（向上取整） */
#define DCM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                           \
	(((x) + DCM_MAIN_FUNCTION_PERIOD - 1u) / DCM_MAIN_FUNCTION_PERIOD)

/* ============================ [ 服务裁剪 ] ============================ */

/** @brief 0x10 会话控制 */
#define DCM_USE_SERVICE_DIAGNOSTIC_SESSION_CONTROL

/** @brief 0x11 ECU 复位 */
#define DCM_USE_SERVICE_ECU_RESET

/** @brief 0x27 安全访问 */
#define DCM_USE_SERVICE_SECURITY_ACCESS

/** @brief 0x31 例程控制（擦槽 / 校验） */
#define DCM_USE_SERVICE_ROUTINE_CONTROL

/** @brief 0x34 请求下载 */
#define DCM_USE_SERVICE_REQUEST_DOWNLOAD

/** @brief 0x36 传输数据 */
#define DCM_USE_SERVICE_TRANSFER_DATA

/** @brief 0x37 请求退出传输 */
#define DCM_USE_SERVICE_REQUEST_TRANSFER_EXIT

/** @brief 0x3E 会话保活 */
#define DCM_USE_SERVICE_TESTER_PRESENT

/* ============================ [ 缓冲 ] ============================ */

/**
 * @brief 诊断请求 / 响应缓冲
 *
 * @details 为什么是 1024 而不是 app 的 128：
 *          福田诊断规范要求诊断缓冲 ≥ 1024 字节（评审已记录为待修项）。
 *          128 只够一个 120 字节的 0x36 数据块，一旦诊断仪改大 block 就溢出。
 *          boot 有 48 KB 余量，两块 1 KB 的代价可以忽略。
 */
#define DCM_RX_BUF_SIZE             (1024u)
#define DCM_TX_BUF_SIZE             (1024u)

/* ============================ [ 会话掩码 ] ============================ */

/**
 * @brief 会话掩码是位图，不是会话号：`1 << (sessionId - 1)`
 *
 * @note  与 `Dcm_Priv.h` 的 `DCM_DFTS_MASK` / `DCM_PRGS_MASK` / `DCM_EXTDS_MASK`
 *        数值相同，这里给一套可读的别名。
 * @note  `DCM_EXTENDED_SESSION`（0x03）AUTOSAR 没有预定义（只有
 *        Default/Programming），app 版把它放在自己的 `Dcm_Cfg.h`，boot 同样自带。
 */
#define DCM_EXTENDED_SESSION        (0x03u)

#define DCM_DEFAULT_MASK            (0x01u)
#define DCM_PROGRAMMING_MASK        (0x02u)
#define DCM_EXTENDED_MASK           (0x04u)

/**
 * @brief `securityMask` 的取值：**允许** locked 与 level 1 两种状态
 *
 * @warning **`securityMask` 是"允许的等级集合"，不是"最低要求的等级"。**
 *          填 `0x01`（只有 locked 允许）的结果是 —— **解锁之后所有服务反而全被拒**，
 *          回 NRC 0x33。因为 `Dcm_Dsl.c:135` 是这么判的：
 *          @code
 *          if (0u != (sesSecAccess->securityMask & (1u << context->currentLevel)))
 *              r = E_OK;                                    // 命中才放行
 *          else
 *              *nrc = DCM_E_SECUTITY_ACCESS_DENIED;         // 0x33
 *          @endcode
 *          解锁后 `currentLevel = 1`，所以要允许它就得把 bit1 也置上。
 */
#define DCM_SEC_MASK_LOCKED_OR_L1   (0x03u)

#endif /* DCM_CFG_H */
