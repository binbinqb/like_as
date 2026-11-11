/**
 * @file    CanTp_Cfg.h
 * @brief   CAN Transport Layer 的通道编号与时序参数
 *
 * @details @section CANTPCFG_UNIT 所有时间常量的单位是"主函数周期数"，不是毫秒
 *          `CanTp` 内部的 `timer` 是个递减计数器，由 `CanTp_MainFunction()` 每
 *          `CANTP_MAIN_FUNCTION_PERIOD` 毫秒减一次（见 `CanTp_Priv.h` 的
 *          `CanTpSetAlarm` / `CanTpSignalAlarm`）。所以 `N_Bs = 1000 ms` 必须写成
 *          `CANTP_CONVERT_MS_TO_MAIN_CYCLES(1000)` = 100，直接写 1000 会变成 10 秒。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：1 个物理寻址通道（0x7E0/0x7E8） |
 */

#ifndef CANTP_CFG_H
#define CANTP_CFG_H

/* ============================ [ 通道 ] ============================ */

/** @brief 物理寻址诊断通道（0x7E0 收 / 0x7E8 发） */
#define CANTP_CHL_P2P               (0u)

/** @brief 通道总数 */
#define CANTP_CFG_NUM_CHANNELS      (1u)

/* ============================ [ 周期 ] ============================ */

/** @brief `CanTp_MainFunction()` 的调用周期（ms），必须与主循环一致 */
#define CANTP_MAIN_FUNCTION_PERIOD  (10u)

/** @brief 毫秒 → 主函数周期数（向上取整，宁可多等不早超时） */
#define CANTP_CONVERT_MS_TO_MAIN_CYCLES(x)                                                         \
	(((x) + CANTP_MAIN_FUNCTION_PERIOD - 1u) / CANTP_MAIN_FUNCTION_PERIOD)

/* ============================ [ 时序（ISO 15765-2） ] ============================ */

/** @brief N_As：发送方等"CAN 帧发出去"的超时 */
#define CANTP_CFG_N_AS              CANTP_CONVERT_MS_TO_MAIN_CYCLES(1000u)

/** @brief N_Bs：发送方等"收到流控帧"的超时 */
#define CANTP_CFG_N_BS              CANTP_CONVERT_MS_TO_MAIN_CYCLES(1000u)

/** @brief N_Cr：接收方等"收到下一个连续帧"的超时 */
#define CANTP_CFG_N_CR              CANTP_CONVERT_MS_TO_MAIN_CYCLES(1000u)

/** @brief STmin：两个连续帧之间的最小间隔（ms）。0 = 尽快发 */
#define CANTP_CFG_STMIN             (0u)

/** @brief BS：块大小，一帧流控允许对方连发几个 CF。0 = 不再发流控 */
#define CANTP_CFG_BS                (8u)

/** @brief 接收方最多发几个"wait"流控（不能是 0xFF） */
#define CANTP_CFG_RX_WFT_MAX        (8u)

/** @brief 链路层数据长度：经典 CAN 是 8 */
#define CANTP_CFG_LL_DL             (8u)

/**
 * @brief 帧内填充值
 * @note  N-PDU 不足 8 字节时用这个值补齐。用 0xCC 而不是 0x00，
 *        是为了在 Kvaser 上能一眼区分"这是填充字节"和"这是数据里的 0"。
 */
#define CANTP_CFG_PADDING           (0xCCu)

/** @brief 单通道 N-PDU 缓冲长度（>= LL_DL，留够一帧即可） */
#define CANTP_CFG_DATA_SIZE         (64u)

/* ============================ [ 行为开关 ] ============================ */

/**
 * @brief 用"发送确认"驱动分段状态机
 *
 * @details @section TXCONF_WHY 为什么必须开
 *          `CanTp_SendCF()` 发完一帧后把状态置为 `CANTP_WAIT_CF_TX_COMPLETED`，
 *          之后**只有两条路**能推进到下一帧：
 *
 *          | 编译选项 | 推进者 | 代价 |
 *          |----------|--------|------|
 *          | 定义本宏 | `CanTp_TxConfirmation()`（由 CanIf 的发送完成回调触发） | 需要让 CanIf 的 txConfirm 接到 CanTp（PduR path 3） |
 *          | 不定义   | `CanTp_MainFunction_Fast()` 里无条件调用 `CanTp_HandleCFTxCompleted()` | 需要 1 ms 周期的 Fast 任务，且**完全绕过 STmin** |
 *
 *          不开又没接 Fast 任务的症状极具迷惑性：**FF 发得出去、第一帧 CF 也发得出去，
 *          然后就没下文了**（状态停在 WAIT_CF_TX_COMPLETED），上层等 N_As 超时才报错。
 *
 *          本工程已把 CanIf 的 TX 确认经 `PDUR_CANTP_TX_CONFIRM` 接回 CanTp，
 *          所以选第一条：**由真实发送完成驱动**，STmin 语义也正确。
 */
#define CANTP_USE_TX_CONFIRMATION

#endif /* CANTP_CFG_H */
