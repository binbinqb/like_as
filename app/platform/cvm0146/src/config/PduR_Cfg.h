/**
 * @file    PduR_Cfg.h
 * @brief   PDU Router 的路由路径编号
 *
 * @details @section PDURCFG_TOPO 一条 ISO-TP 诊断链路要过 4 条路径
 *          这是最容易搞错的地方：**TP 型报文要过两次 PduR**。
 *          @code
 *          N-PDU（单帧 CAN 报文）          SDU（重组后的整条诊断请求）
 *          0x7E0 → CanIf → PduR → CanTp  →  PduR → Dcm
 *                    path2                path0
 *          @endcode
 *
 *          | pathId | 方向 | Src | Dest | 用到的回调 |
 *          |--------|------|-----|------|------------|
 *          | 0 | SDU 上行 | CanTp | Dcm   | `TpRxIndication` / `StartOfReception` / `CopyRxData` |
 *          | 1 | SDU 下行 | Dcm   | CanTp | `Transmit` / `CopyTxData` / `TxConfirmation` |
 *          | 2 | N-PDU 上行 | CanIf | CanTp | `RxIndication` |
 *          | 3 | N-PDU 发送确认 | CanTp | CanIf | `TxConfirmation` |
 *
 *          @section PDURCFG_WHY 为什么 path0 必须是 0
 *          **PduR 的 RX pathId 在 Dcm 那侧被当成"通道号"用**：
 *          `Dcm_StartOfReception(id,...)` 里有 `DET_VALIDATE(id < config->numOfChls)`。
 *          当前只有 1 个诊断通道，所以 SDU 上行路径必须是 0。
 *          其余三条编号只在本文件内自洽，不影响别处。
 *
 *          @section PDURCFG_CONFIRM 为什么 path3 的 Src 是 CanTp
 *          `PduR_TxConfirmation(pathId)` 把结果交给 **`SrcPduRef->api->TxConfirmation`**
 *          —— 确认永远是"往上游走"。CanIf 的 N-PDU 发送确认要回到 CanTp，
 *          所以这条路径的 Src 必须是 CanTp、Dest 才是 CanIf。
 *          写成"Src=CanIf, Dest=CanTp"会得到一个空指针调用（静默失败）。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2 条路径（错误的单跳拓扑） |
 * | V1.1.0 | 2026-11-10 | binbina | 改为 4 条路径：N-PDU 与 SDU 各一对 |
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
 * @brief N-PDU 上行：CanIf（收到一帧 0x500）→ CanNm（M9）
 *
 * @note  这是唯一一条"目的地是 BSW 协议模块而不是 Dcm"的路径。
 *        它没有对应的 TP 分层 —— NM 报文固定 8 字节，不需要重组，
 *        所以 **一帧直接到 CanNm**，中间只过 PduR 这一层。
 *
 * @warning 这条路径的 `DestPduRef->PduHandleId` 必须是 **0**，
 *          不是 CanIf 的 PDU 号。因为 `CanNm_RxIndication(RxPduId, ...)`
 *          把第一个参数当**通道下标**用（`CanNm.c:851`：
 *          `context = &CANNM_CONFIG->ChannelContexts[RxPduId]`），
 *          传 10 就是越界读。这是 PduR 与 CanNm 的一个语义错配，
 *          AS 靠"配置里填 0"化解，我们照做。
 */
#define PDUR_CANIF_TO_CANNM_RX  (4u)

/**
 * @brief N-PDU 发送确认：CanNm ← CanIf（0x500 那帧发出去了，M9）
 *
 * @note  同样是反向的"确认往上游走"：Src = CanNm，Dest = CanIf。
 *        与 `PDUR_CANTP_TX_CONFIRM` 的拓扑完全一致。
 *
 * @warning 同样要求 `SrcPduRef->PduHandleId = 0`：
 *          `PduR_TxConfirmation()` 会把 `SrcPduRef->PduHandleId` 传下去，
 *          而 `CanNm_TxConfirmation(TxPduId, ...)` 也拿它当通道下标。
 */
#define PDUR_CANNM_TX_CONFIRM   (5u)

/**
 * @brief 信号下行：Com → CanIf（M10）
 *
 * @note  `Com_MainFunctionTx()` 到周期就调 `PduR_ComTransmit(TxPduId)`，
 *        `TxPduId` 就是这个路径号。PduR 再用
 *        **本路径 Dest 的 `PduHandleId`** 去调 `CanIf_Transmit()` ——
 *        所以 Dest 侧填的是 **CanIf 的 PDU 号**（`CANIF_TX_COM_TEST`），
 *        不是 Com 的 PDU 号。这是本表里第一次出现
 *        "Src 和 Dest 的 PduHandleId 属于不同编号体系"。
 */
#define PDUR_COM_TO_CANIF_TX    (6u)

/**
 * @brief 信号上行：CanIf → Com（M10）
 *
 * @note  Dest 侧填 **Com 的 PDU 号**（`COM_PDU_RX_TEST` = 1），
 *        因为 `Com_RxIndication(RxPduId)` 拿它当 `IPduConfigs[]` 下标
 *        （`Com.c:605`：`&COM_CONFIG->IPduConfigs[RxPduId]`）。
 */
#define PDUR_CANIF_TO_COM_RX    (7u)

/**
 * @brief 信号发送确认：Com ← CanIf（M10）
 *
 * @note  确认往上游走，Src 必须是 Com，`SrcPduRef->PduHandleId`
 *        要填 **Com 的 PDU 号**（0），因为 `Com_TxConfirmation(TxPduId)`
 *        也拿它当 `IPduConfigs[]` 下标。
 */
#define PDUR_COM_TX_CONFIRM     (8u)

/** @brief 路径总数（= `RoutingPaths[]` 长度） */
#define PDUR_NUM_ROUTING_PATHS  (9u)

#endif /* PDUR_CFG_H */
