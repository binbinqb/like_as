/**
 * @file    PduR_Cfg.h
 * @brief   boot 版 PDU Router 路由表：只有诊断一条链路（4 条路径）
 *
 * @details @section BOOTPDUR_WHY 为什么 boot 要自带一份，而不是复用 app 的
 *
 *          app 的 `PduR_Cfg.h` 有 **9 条**路径（诊断 4 条 + NM 2 条 + Com 3 条），
 *          `PDUR_NUM_ROUTING_PATHS = 9`。boot 没有 NM / Com / Dem，
 *          但那张表是 `const` 数组，链接器不会按需裁剪单个表项 ——
 *          复用就等于把 5 条用不上的路径连同它们的 `PduR_ApiType` 一起搬进 boot。
 *
 *          更关键的是**语义风险**：app 那张表里 `path 6/7/8` 的
 *          `PduHandleId` 指的是 Com 的 PDU 号，如果将来有人给 boot 加服务时
 *          顺手复用了 app 的 PduR_Cfg，这些编号在 boot 里毫无意义，
 *          接错就是静默不发。
 *
 *          所以 boot 这份**只保留诊断链路**，编号与 app 的前 4 条一致
 *          （这样 `CanTp_Cfg.c` 可以原样复用 app 那份参数）。
 *
 * @note    `PDUR_CANTP_TO_DCM_RX` 必须是 0：`Dcm_StartOfReception()` 里
 *          `DET_VALIDATE(id < numOfChls)`，把 RX pathId 当**通道索引**用。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用 4 条诊断路径 |
 */

#ifndef PDUR_CFG_H
#define PDUR_CFG_H

/* ============================ [ 路由路径 ] ============================ */

/**
 * @brief SDU 上行：CanTp（重组完）→ Dcm
 * @warning 必须是 0：Dcm 拿 RX pathId 当通道索引用
 */
#define PDUR_CANTP_TO_DCM_RX    (0u)

/** @brief SDU 下行：Dcm → CanTp（开始分段发送） */
#define PDUR_DCM_TO_CANTP_TX    (1u)

/** @brief N-PDU 上行：CanIf（收到一帧 0x7E0）→ CanTp */
#define PDUR_CANIF_TO_CANTP_RX  (2u)

/** @brief N-PDU 发送确认：CanTp ← CanIf（0x7E8 那帧发出去了） */
#define PDUR_CANTP_TX_CONFIRM   (3u)

/**
 * @brief 路径总数（= `RoutingPaths[]` 长度）
 *
 * @warning 改这个值必须同时改 `PduR_Cfg.c` 里的三张表
 *          （`SrcPdu` / `DstPdu` / `RoutingPaths`），三张表长度都跟着它走。
 */
#define PDUR_NUM_ROUTING_PATHS  (4u)

#endif /* PDUR_CFG_H */
