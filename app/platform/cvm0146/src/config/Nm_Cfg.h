/**
 * @file    Nm_Cfg.h
 * @brief   Nm（通用网络管理）的通道编号与外部可见常量
 *
 * @details @section NMCFG_WHAT Nm 到底管什么
 *
 *          `Nm` 本身**不做状态机**，它是"总线类型分发层"：
 *
 *          @code
 *          CanNm / FrNm / UdpNm / OsekNm     各总线的 NM 状态机
 *                    ↑ 向上报告            ↓ 向下请求
 *                            Nm
 *                    ↑                    ↓
 *                            ComM
 *          @endcode
 *
 *          应用不应该直接调 `CanNm_NetworkRequest()` —— 那是"绕过 ComM/Nm
 *          直接操作某一根总线"，在只有一根 CAN 时看不出问题，
 *          多总线时会出现"ComM 以为网络没起来，CanNm 已经在发报文"。
 *          正确的调用链是 `Nm_NetworkRequest(通道)` → 分发到 `CanNm_*`。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道（CAN0） |
 */

#ifndef NM_CFG_H
#define NM_CFG_H

/* ============================ [ 通道编号 ] ============================ */
/*
 * 这是 `Nm_` 系列接口的 `NetworkHandle`，**不是 CAN 通道号**。
 * 两者当前都是 0，容易混 —— 所以给个名字，调用处一眼能看出用的是哪一个。
 */

/** @brief Nm 通道 0：CAN0 上的 CanNm */
#define NM_CFG_CHANNEL_CAN0         (0u)

/** @brief Nm 通道总数（= `Nm_Config.numOfChannels`） */
#define NM_CFG_NUM_CHANNELS         (1u)

/**
 * @brief ComM 的通道句柄，与 Nm 通道一一对应
 * @note  当前 1:1 映射。将来一个 ComM 通道管多根总线时这里才会分叉。
 */
#define NM_CFG_COMM_HANDLE_CAN0     (0u)

#endif /* NM_CFG_H */
