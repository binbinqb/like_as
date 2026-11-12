/**
 * @file    CanIf_Cfg.c
 * @brief   boot 版 CAN Interface 表：1 条收（0x7E0）+ 1 条发（0x7E8）
 *
 * @details 与 app 版的关系：
 *
 *          | 项 | app | boot |
 *          |---|---|---|
 *          | RX 过滤表 | 57 条（私有 + 矩阵 + J1939 段） | **1 条**（0x7E0） |
 *          | TX 表 | 12 条（心跳/扩展/诊断/NM/Com/矩阵） | **1 条**（0x7E8） |
 *          | 控制器 | CAN0 + CAN1 | **CAN0** |
 *          | 报文池 | 0（同步） | 0（同步） |
 *
 *          硬件层（`Can_Cfg.c` 的邮箱表）**复用 app 那份**，所以这里的
 *          `hoh` 必须与那份配置严格对应，不能自己重排。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用 1RX + 1TX |
 */

#include "platform_cvm0146.h"   /* Platform_Printf（临时诊断） */
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanIf_Priv.h"

#include "Can_HwCfg.h"
#include "PduR_CanIf.h"     /* PduR_CanIfRxIndication / PduR_CanIfTxConfirmation */
#include "PduR_Cfg.h"       /* PDUR_CANIF_TO_CANTP_RX / PDUR_CANTP_TX_CONFIRM */

/* ============================ [ 回调 ] ============================ */

/**
 * @brief 收到诊断请求 0x7E0 → 交给 PduR 的 N-PDU 上行路径
 * @param[in] RxPduId    CanIf 侧的 PDU 号（本表只有一个，忽略）
 * @param[in] PduInfoPtr 帧内容
 * @note  这里做一次编号换算：CanIf 用 `CANIF_RX_DIAG_REQ`(0)，
 *        PduR 用 `PDUR_CANIF_TO_CANTP_RX`(2)。两套编号体系不能混。
 */
static void CanIfCfg_DiagRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	(void)RxPduId;
	PduR_CanIfRxIndication((PduIdType)PDUR_CANIF_TO_CANTP_RX, PduInfoPtr);
}

/**
 * @brief 诊断响应 0x7E8 发送完成 → 交给 PduR 的确认路径
 * @note  **这一条不能少**：`CanTp` 发完一帧 CF 后停在
 *        `CANTP_WAIT_CF_TX_COMPLETED`，只有这个确认能把它推到下一帧。
 *        没有它，多帧响应只会发出第一帧，然后等 N_As 超时。
 */
static void CanIfCfg_DiagTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	(void)TxPduId;
	PduR_CanIfTxConfirmation((PduIdType)PDUR_CANTP_TX_CONFIRM, result);
}

/* ============================ [ 表 ] ============================ */

/**
 * @brief CAN0 接收过滤表（boot 只有一条）
 *
 * @warning `canid & mask == canid` 必须成立，否则这条**永远匹配不上**：
 *          `CanIf_RxDispatch()` 比较的是"来帧 ID 按掩码与过"与"原样存储的 canid"。
 *          0x7E0 配 `0x1FFFFFFF`（全 1，精确匹配）天然满足。
 *
 * @warning `hoh` 必须是 `Can_Cfg.c` 里 0x7E0 用的那个邮箱（5）。
 *          写错不会报错 —— 只会"这条报文永远收不到"。
 */
static const CanIf_RxPduType CanIf_RxPdus_CAN0[] = {
	{
		CanIfCfg_DiagRxIndication,      /* rxInd：收到后交给 PduR → CanTp */
		CANIF_RX_DIAG_REQ,              /* rxPduId：0 */
		0x7E0u,                         /* canid：诊断物理请求 */
		0x1FFFFFFFu,                    /* mask：精确匹配 */
		5u,                             /* hoh：CAN0 邮箱 5（与 Can_Cfg.c 一致） */
	},
};

/**
 * @brief 发送 PDU 表（boot 只有一条）
 * @warning `hoh` 用 `CAN_HW_HTH_DIAG_RESP`（=3）而不是裸数字：
 *          这个宏与 `Can_Cfg.c` 的 `CanHw_Hohs[]` 同源，改硬件配置时不会漏。
 */
static const CanIf_TxPduType CanIf_TxPdus[] = {
	{
		CanIfCfg_DiagTxConfirmation,    /* txConfirm：推进 CanTp 的 CF 分段 */
		CANIF_TX_DIAG_RESP,             /* txPduId：0 */
		CAN_HW_ID_DIAG_RESP,            /* canid：0x7E8 */
		NULL,                           /* p_canid：固定 ID，不用动态 */
		CAN_HW_HTH_DIAG_RESP,           /* hoh：CAN0 HTH 3 → 邮箱 4 */
		CANIF_CHL_CAN0,                 /* ControllerId */
	},
};

/**
 * @brief 控制器上下文
 * @note  必须是**非 const**：`CanIf_SetControllerMode()` 会改写 PduMode 等字段。
 */
static CanIf_CtrlContextType CanIf_CtrlContexts[CANIF_CTRL_NUM];

/** @brief 每个控制器的 RX 过滤表（下标与 CtrlContexts 一致） */
static const CanIf_CtrlConfigType CanIf_CtrlConfigs[CANIF_CTRL_NUM] = {
	{
		CanIf_RxPdus_CAN0,                          /* rxPdus */
		(uint16_t)ARRAY_SIZE(CanIf_RxPdus_CAN0),    /* numOfRxPdus */
	},
};

/* ============================ [ 总表 ] ============================ */

const CanIf_ConfigType CanIf_Config = {
	CanIf_TxPdus,                               /* txPdus */
	CanIf_CtrlContexts,                         /* CtrlContexts */
	CanIf_CtrlConfigs,                          /* CtrlConfigs */
	(uint16_t)ARRAY_SIZE(CanIf_TxPdus),         /* numOfTxPdus */
	(uint8_t)ARRAY_SIZE(CanIf_CtrlContexts),    /* numOfCtrls */
};

/* ============================ [ 配置自检 ] ============================ */

/**
 * @brief 检查接收过滤表是否满足二分查找的前置条件
 * @retval true  表合法（boot 只有一项，只要自身合法就一定是升序）
 *
 * @details 与 app 版同名同签名，方便将来把调用点统一。
 *          判据保持两条：`canid & mask == canid`、严格升序。
 */
bool CanIfCfg_CheckRxOrder(void)
{
	const CanIf_CtrlConfigType *ctrl;
	const CanIf_RxPduType *p;
	uint16_t i;
	uint8_t c;

	for (c = 0u; c < CanIf_Config.numOfCtrls; c++) {
		ctrl = &CanIf_Config.CtrlConfigs[c];

		for (i = 0u; i < ctrl->numOfRxPdus; i++) {
			p = &ctrl->rxPdus[i];

			if ((p->canid & p->mask) != p->canid) {
				return false;
			}

			if ((i > 0u) && (p->canid <= ctrl->rxPdus[i - 1u].canid)) {
				return false;
			}
		}
	}

	return true;
}
