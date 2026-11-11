/**
 * @file    ComM_Cfg.h
 * @brief   ComM 的时基与编译期开关
 *
 * @details @section COMMCFG_PERIOD ComM 没有周期性定时器，但保留周期宏
 *
 *          AS 的 ComM 状态机（`ComM_MainFunction_*`）是**事件驱动**的：
 *          只有 `ComM_RequestComMode` / `ComM_Nm_*` 改了标志，主函数才动作，
 *          不存在"等 N 毫秒"的超时。所以 `COMM_MAIN_FUNCTION_PERIOD`
 *          只被 `COMM_CONVERT_MS_TO_MAIN_CYCLES` 用（当前唯一用途是
 *          `NmLightTimeout`，而本工程不开 LIGHT 变体）。
 *
 *          仍然定义它，是为了与生成器（`tools/generator/ComM.py:19`）保持一致，
 *          将来打开 LIGHT 变体时不用再改。
 *
 * @warning **不定义 `COMM_USE_PB_CONFIG`**：它会让 `ComM.c` 用
 *          `comConfig`（一个 `ComM_Init` 传入的指针）替代 `&ComM_Config`。
 *          本工程是编译前固定配置，不定义才是对的。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道 / 单用户，NM 全功能变体 |
 */

#ifndef COMM_CFG_H
#define COMM_CFG_H

/* ============================ [ 时基 ] ============================ */

#ifndef COMM_MAIN_FUNCTION_PERIOD
#define COMM_MAIN_FUNCTION_PERIOD   (10u)
#endif

#define COMM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                          \
	(((x) + COMM_MAIN_FUNCTION_PERIOD - 1u) / COMM_MAIN_FUNCTION_PERIOD)

/* ============================ [ 通道 / 用户编号 ] ============================ */

/**
 * @name ComM 用户句柄
 * @note  用户是"谁在要求通信"（应用、诊断、OTA…）。当前只有一个：应用。
 *        `ComM_RequestComMode(User, Mode)` 的第一个参数就是它。
 *
 *        多用户的意义在于**仲裁**：只要还有一个用户要求 FULL_COM，
 *        通道就不会降级。BCM 上典型的第二个用户是诊断（编程会话时要保持通信）。
 */
/** @{ */
#define COMM_USER_APP               (0u)    /**< 应用（主循环） */
#define COMM_NUM_USERS              (1u)
/** @} */

/**
 * @name ComM 通道句柄
 * @note  与 `Nm_Cfg.h` 的 `NM_CFG_CHANNEL_CAN0` 是**两套编号**，
 *        当前都是 0，靠 `ComM_ChannelConfigType.nmHandle` 显式关联。
 */
/** @{ */
#define COMM_CHANNEL_CAN0           (0u)
#define COMM_NUM_CHANNELS           (1u)
/** @} */

#endif /* COMM_CFG_H */
