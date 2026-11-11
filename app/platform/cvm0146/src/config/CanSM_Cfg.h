/**
 * @file    CanSM_Cfg.h
 * @brief   CanSM 的时基换算
 *
 * @details @section CANSMCFG_PERIOD 所有 Bor* 时间都是"主函数拍数"
 *
 *          `CanSM_ChannelContextType` 里的 `BusOffTimer` / `BusOffTxEnsuredTimer`
 *          / `TxRecoveryTimer` 都是 `uint16_t` 递减计数器，每调一次
 *          `CanSM_MainFunction()` 减一。所以配置里的 `BorTimeL1` 等
 *          必须用 `CANSM_CONVERT_MS_TO_MAIN_CYCLES()` 换算。
 *
 *          @warning 误填毫秒值（`BorTimeL1` 填 100 而不是 10）会让
 *                   bus-off 恢复等待变成 **1 秒**，慢 10 倍，且不报错 ——
 *                   现象只是"总线故障后恢复得很慢"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单网络（CAN0） |
 */

#ifndef CANSM_CFG_H
#define CANSM_CFG_H

#ifndef CANSM_MAIN_FUNCTION_PERIOD
#define CANSM_MAIN_FUNCTION_PERIOD  (10u)
#endif

#define CANSM_CONVERT_MS_TO_MAIN_CYCLES(x)                                                         \
	(((x) + CANSM_MAIN_FUNCTION_PERIOD - 1u) / CANSM_MAIN_FUNCTION_PERIOD)

/* 不定义 CANSM_USE_PB_CONFIG：本工程是编译前固定配置，
 * 定义了会让 CanSM.c 用 `canSMConfig` 指针而不是 `&CanSM_Config`。 */

#endif /* CANSM_CFG_H */
