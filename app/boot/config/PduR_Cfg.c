/**
 * @file    PduR_Cfg.c
 * @brief   boot 版 PDU Router 配置：4 条诊断路径
 *
 * @details 拓扑与 app 版完全一致（只是少了 NM / Com 的 5 条）：
 *          @code
 *          N-PDU（单帧 CAN 报文）          SDU（重组后的整条诊断请求）
 *          0x7E0 → CanIf → PduR → CanTp  →  PduR → Dcm
 *                    path2                path0
 *          @endcode
 *
 *          | pathId | 方向 | Src | Dest |
 *          |--------|------|-----|------|
 *          | 0 | SDU 上行 | CanTp | Dcm |
 *          | 1 | SDU 下行 | Dcm | CanTp |
 *          | 2 | N-PDU 上行 | CanIf | CanTp |
 *          | 3 | N-PDU 确认 | CanTp | CanIf |
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用 4 条诊断路径 |
 */

#include "PduR.h"
#include "PduR_Cfg.h"
#include "PduR_Priv.h"

#include "CanTp.h"
#include "Dcm.h"
#include "CanIf.h"

/* ============================ [ 模块入口 ] ============================ */

/**
 * @brief CanTp 的入口
 * @note  `RxIndication` 收 N-PDU（CanIf 上来的一帧）；
 *        `Transmit` 接收 SDU 下行请求；
 *        `TxConfirmation` 接收 N-PDU 发送完成的确认。
 */
static const PduR_ApiType PduR_CanTpApi = {
	NULL,                     /* StartOfReception */
	NULL,                     /* CopyRxData */
	NULL,                     /* TpRxIndication */
	CanTp_RxIndication,       /* RxIndication：N-PDU 上行 */
	CanTp_Transmit,           /* Transmit：SDU 下行 */
	NULL,                     /* CopyTxData */
	CanTp_TxConfirmation,     /* TxConfirmation：N-PDU 发送确认回到 CanTp */
};

/**
 * @brief Dcm 的入口
 * @note  `TpRxIndication` 收完整 SDU；`CopyTxData` / `TxConfirmation`
 *        供 CanTp 反向取数据和回报发送完成。
 */
static const PduR_ApiType PduR_DcmApi = {
	Dcm_StartOfReception,     /* StartOfReception */
	Dcm_CopyRxData,           /* CopyRxData */
	Dcm_TpRxIndication,       /* TpRxIndication：SDU 上行完成 */
	NULL,                     /* RxIndication：Dcm 不用 IF 型接口 */
	NULL,                     /* Transmit：Dcm 自己调 PduR，不需要被回调 */
	Dcm_CopyTxData,           /* CopyTxData */
	Dcm_TpTxConfirmation,     /* TxConfirmation：整包发送完成 */
};

/**
 * @brief CanIf 的入口
 * @note  **本表里 `Transmit` 必须非空**：path1（Dcm → CanTp）的 Transmit
 *        走的是 `PduR_CanTpApi.Transmit`，而 path3 的确认只需要 Src。
 *        但 `PduR_Transmit()` 在找不到 Dest 的 Transmit 时会**静默返回 E_OK**，
 *        所以这里保留 `CanIf_Transmit` 是为了将来 boot 若要走"直接发 PDU"
 *        的路径时不用改表 —— 当前用不到，但留着不会增加体积。
 */
static const PduR_ApiType PduR_CanIfApi = {
	NULL,                     /* StartOfReception */
	NULL,                     /* CopyRxData */
	NULL,                     /* TpRxIndication */
	NULL,                     /* RxIndication */
	CanIf_Transmit,           /* Transmit */
	NULL,                     /* CopyTxData */
	NULL,                     /* TxConfirmation */
};

/* ============================ [ 端点 ] ============================ */

/** @brief 每个路径的"发起方"端点 */
static const PduR_PduType PduR_SrcPdu[PDUR_NUM_ROUTING_PATHS] = {
	/* 0：SDU 上行，Src = CanTp 通道 0 */
	{ PDUR_MODULE_CANTP, 0u, &PduR_CanTpApi },
	/* 1：SDU 下行，Src = Dcm 通道 0 */
	{ PDUR_MODULE_DCM,   0u, &PduR_DcmApi },
	/* 2：N-PDU 上行，Src = CanIf（只用 Dest，Src.api 不参与） */
	{ PDUR_MODULE_CANIF, 0u, &PduR_CanIfApi },
	/* 3：N-PDU 确认，Src = CanTp 通道 0（确认往上游走） */
	{ PDUR_MODULE_CANTP, 0u, &PduR_CanTpApi },
};

/** @brief 每个路径的"目的方"端点（1 对 1） */
static const PduR_PduType PduR_DstPdu[PDUR_NUM_ROUTING_PATHS][1] = {
	/* 0：SDU 上行 → Dcm 通道 0 */
	{ { PDUR_MODULE_DCM,   0u, &PduR_DcmApi } },
	/* 1：SDU 下行 → CanTp 通道 0 */
	{ { PDUR_MODULE_CANTP, 0u, &PduR_CanTpApi } },
	/* 2：N-PDU 上行 → CanTp 通道 0 */
	{ { PDUR_MODULE_CANTP, 0u, &PduR_CanTpApi } },
	/* 3：确认 → CanIf（只用 Src，Dest.api 不参与） */
	{ { PDUR_MODULE_CANIF, 0u, &PduR_CanIfApi } },
};

/** @brief 路由路径表（下标即 pathId） */
static const PduR_RoutingPathType PduR_RoutingPaths[PDUR_NUM_ROUTING_PATHS] = {
	{
		&PduR_SrcPdu[PDUR_CANTP_TO_DCM_RX],
		PduR_DstPdu[PDUR_CANTP_TO_DCM_RX],
		NULL,                             /* DestTxBufferRef：不用 PduR 内部发送缓冲 */
		NULL,                             /* GwBuffer */
		0u,                               /* GwBufferSize */
		1u,                               /* numOfDestPdus */
	},
	{
		&PduR_SrcPdu[PDUR_DCM_TO_CANTP_TX],
		PduR_DstPdu[PDUR_DCM_TO_CANTP_TX],
		NULL,
		NULL,
		0u,
		1u,
	},
	{
		&PduR_SrcPdu[PDUR_CANIF_TO_CANTP_RX],
		PduR_DstPdu[PDUR_CANIF_TO_CANTP_RX],
		NULL,
		NULL,
		0u,
		1u,
	},
	{
		&PduR_SrcPdu[PDUR_CANTP_TX_CONFIRM],
		PduR_DstPdu[PDUR_CANTP_TX_CONFIRM],
		NULL,
		NULL,
		0u,
		1u,
	},
};

/* ============================ [ 总表 ] ============================ */

const PduR_ConfigType PduR_Config = {
	PduR_RoutingPaths,
	(uint16_t)ARRAY_SIZE(PduR_RoutingPaths),
};
