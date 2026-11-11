/**
 * @file    PduR_Cfg.c
 * @brief   PduR 路由表：CanIf ↔ CanTp ↔ Dcm 的 4 条路径
 *
 * @details @section PDURCFG_C_DATA 数据怎么走
 *          @code
 *          RX：0x7E0 → CanIf_RxIndication
 *                     → PduR_RxIndication(2)          [Dest=CanTp] CanTp_RxIndication
 *                     → CanTp 重组（SF/FF+CF，必要时回 FC）
 *                     → PduR_TpRxIndication(0)        [Dest=Dcm]  Dcm_TpRxIndication
 *                     → Dcm 解析 SID → 组响应到 txBuffer
 *                     → Dcm_MainFunction_Response()
 *                     → PduR_TpTransmit(1)            [Dest=CanTp] CanTp_Transmit
 *                     → CanTp 分段 → CanIf_Transmit(CANIF_TX_DIAG_RESP) → 0x7E8
 *                     → 每帧发完：CanIf → PduR_TxConfirmation(3) [Src=CanTp] CanTp_TxConfirmation
 *                     → 整包发完：CanTp → PduR_TxConfirmation(1) [Src=Dcm] Dcm_TpTxConfirmation
 *          @endcode
 *
 *          @section PDURCFG_C_STATIC 为什么全静态初始化
 *          路径编译期定死，`&Array[i]` 是常量表达式，直接静态初始化省掉一个
 *          初始化顺序隐患（谁先跑填表、谁先跑 Init）。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2 条路径（错误的单跳拓扑，收不到任何诊断帧） |
 * | V1.1.0 | 2026-11-10 | binbina | 改为 4 条路径：N-PDU 上行/确认 + SDU 上行/下行 |
 */

#include "PduR.h"
#include "PduR_Priv.h"
#include "PduR_Cfg.h"

#include "CanIf.h"
#include "CanIf_Cfg.h"   /* CANIF_TX_COM_TEST：路由表 Dest 侧要用 CanIf 的 PDU 号 */
#include "CanTp.h"
#include "CanNm.h"
#include "Com.h"
#include "Dcm.h"

/* ============================ [ API 表 ] ============================ */
/*
 * `PduR_ApiType` 字段顺序（7 个）：
 *   StartOfReception / CopyRxData / TpRxIndication / RxIndication /
 *   Transmit / CopyTxData / TxConfirmation
 *
 * 同一个表可能在不同路径里扮演 Src 或 Dest，所以**两个方向的入口都要填**：
 * - 作为 Dest（下行）：StartOfReception / CopyRxData / TpRxIndication / RxIndication / Transmit
 * - 作为 Src（上行）：CopyTxData / TxConfirmation
 */

/**
 * @brief CanTp 的入口
 * @note  `RxIndication` 收 N-PDU（CanIf 上来的一帧）；
 *        `Transmit` 接收 SDU 下行请求；
 *        `TxConfirmation` 接收 N-PDU 发送完成的确认。
 *        `StartOfReception` / `CopyRxData` / `TpRxIndication` 留空 ——
 *        CanTp 是 TP 层的**下**半部，不接收来自上层的 RX 流。
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
 * @brief Com 的入口（M10）
 *
 * @note  `Transmit` 留空是对的：Com 不接收"被上层要求发送"的回调，
 *        它自己按周期调 `PduR_ComTransmit()`（函数在 `PduR_Com.c`）。
 *        这里只需要 RX 解包与 TX 确认两个回调。
 */
static const PduR_ApiType PduR_ComApi = {
	NULL,                     /* StartOfReception */
	NULL,                     /* CopyRxData */
	NULL,                     /* TpRxIndication */
	Com_RxIndication,         /* RxIndication：0x200 上行 */
	NULL,                     /* Transmit：Com 主动调 PduR_ComTransmit */
	NULL,                     /* CopyTxData */
	Com_TxConfirmation,       /* TxConfirmation：0x200 发送完成 */
};

/**
 * @brief CanNm 的入口（M9）
 *
 * @note  只有两个回调非空，因为 NM 不需要 TP：
 *        - `RxIndication`：收到 0x500 → `CanNm_RxIndication()`
 *        - `TxConfirmation`：0x500 发完 → `CanNm_TxConfirmation()`
 *
 *        `Transmit` **刻意留空**：`CanNm` 不通过 PduR 发报文，
 *        `nmSendMessage()` 直接调 `CanIf_Transmit()`（`CanNm.c:166`）。
 *        这是 AS 的设计（NM 报文固定 8 字节，走 PduR 只是多一层跳转）。
 *        留空也意味着"如果有人误配成走 PduR 发送，它会静默失败" ——
 *        实际上会打 ASLOG，但那些日志本工程没开。
 */
static const PduR_ApiType PduR_CanNmApi = {
	NULL,                     /* StartOfReception */
	NULL,                     /* CopyRxData */
	NULL,                     /* TpRxIndication */
	CanNm_RxIndication,       /* RxIndication：0x500 上行 */
	NULL,                     /* Transmit：CanNm 自己调 CanIf_Transmit，不走 PduR */
	NULL,                     /* CopyTxData */
	CanNm_TxConfirmation,     /* TxConfirmation：0x500 发送完成 */
};

/**
 * @brief CanIf 的入口
 * @note  全空是对的：CanIf 在两条路径里分别只当 Src（RX 上行，PduR 只读 Dest）
 *        和 Dest（TX 确认，PduR 只读 Src），它的回调一个都用不上。
 *        保留这个符号是为了让表看起来对称，也方便将来接 Mirror/SecOC。
 */
static const PduR_ApiType PduR_CanIfApi = {
	NULL,                     /* StartOfReception */
	NULL,                     /* CopyRxData */
	NULL,                     /* TpRxIndication */
	NULL,                     /* RxIndication */
	/**
	 * @note **M10 起这一项必须非空。** 之前 CanIf 只当 Src（RX）和
	 *       确认路径的 Dest（确认只读 Src），Transmit 一直用不到。
	 *       现在 Com 的周期发送要经过 `PduR_Transmit()` →
	 *       `DestPduRef->api->Transmit`，留空就是**静默不发**：
	 *       `PduR_Transmit` 只打 ASLOG（本工程没开），函数返回 E_OK，
	 *       Com 以为发出去了、定时器照常重装，总线上却一帧都没有。
	 */
	CanIf_Transmit,           /* Transmit：信号下行到 CAN */
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
	/* 4：NM 上行，Src = CanIf（只用 Dest，Src.api 不参与） */
	{ PDUR_MODULE_CANIF, 0u, &PduR_CanIfApi },
	/* 5：NM 发送确认，Src = CanNm 通道 0。
	 *    PduHandleId 必须是 0 —— CanNm 拿它当通道下标用，见 PduR_Cfg.h 的 @warning */
	{ PDUR_MODULE_CANNM, 0u, &PduR_CanNmApi },
	/* 6：信号下行，Src = Com PDU 0（只用 Dest，Src 不参与发送） */
	{ PDUR_MODULE_COM, 0u, &PduR_ComApi },
	/* 7：信号上行，Src = CanIf（只用 Dest） */
	{ PDUR_MODULE_CANIF, 0u, &PduR_CanIfApi },
	/* 8：信号发送确认，Src = Com PDU 0（Com 拿它当 IPdu 下标） */
	{ PDUR_MODULE_COM, 0u, &PduR_ComApi },
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
	/* 4：NM 上行 → CanNm 通道 0。
	 *    PduHandleId 必须是 0（CanNm 拿它当通道下标用），见 PduR_Cfg.h 的 @warning */
	{ { PDUR_MODULE_CANNM, 0u, &PduR_CanNmApi } },
	/* 5：确认 → CanIf（只用 Src，Dest.api 不参与） */
	{ { PDUR_MODULE_CANIF, 0u, &PduR_CanIfApi } },
	/* 6：信号下行 → CanIf。PduHandleId = CanIf 的 PDU 号，见 PduR_Cfg.h */
	{ { PDUR_MODULE_CANIF, (PduIdType)CANIF_TX_COM_TEST, &PduR_CanIfApi } },
	/* 7：信号上行 → Com PDU 1。PduHandleId = Com 的 IPdu 下标 */
	{ { PDUR_MODULE_COM, 1u, &PduR_ComApi } },
	/* 8：确认 → CanIf（只用 Src） */
	{ { PDUR_MODULE_CANIF, (PduIdType)CANIF_TX_COM_TEST, &PduR_CanIfApi } },
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
	{
		&PduR_SrcPdu[PDUR_CANIF_TO_CANNM_RX],
		PduR_DstPdu[PDUR_CANIF_TO_CANNM_RX],
		NULL,                             /* 不用内部缓冲：NM 报文固定 8 字节 */
		NULL,
		0u,
		1u,
	},
	{
		&PduR_SrcPdu[PDUR_CANNM_TX_CONFIRM],
		PduR_DstPdu[PDUR_CANNM_TX_CONFIRM],
		NULL,
		NULL,
		0u,
		1u,
	},
	{
		&PduR_SrcPdu[PDUR_COM_TO_CANIF_TX],
		PduR_DstPdu[PDUR_COM_TO_CANIF_TX],
		NULL,                             /* 不用内部缓冲：Com 自带报文镜像 */
		NULL,
		0u,
		1u,
	},
	{
		&PduR_SrcPdu[PDUR_CANIF_TO_COM_RX],
		PduR_DstPdu[PDUR_CANIF_TO_COM_RX],
		NULL,
		NULL,
		0u,
		1u,
	},
	{
		&PduR_SrcPdu[PDUR_COM_TX_CONFIRM],
		PduR_DstPdu[PDUR_COM_TX_CONFIRM],
		NULL,
		NULL,
		0u,
		1u,
	},
};

/* ============================ [ 总表 ] ============================ */

const PduR_ConfigType PduR_Config = {
#if defined(PDUR_USE_MEMPOOL)
	NULL,                                 /* mc：未启用内存池 */
#endif
	PduR_RoutingPaths,
	(uint16_t)ARRAY_SIZE(PduR_RoutingPaths),
};
