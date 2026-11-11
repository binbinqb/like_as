/**
 * @file    CanTp_Cfg.c
 * @brief   CanTp 通道表：1 条物理寻址诊断链路
 *
 * @details @section CANTPCFG_MAP 一条通道如何同时管收发
 *          `CanTp_ChannelConfigType` 里同时有收和发两组引用：
 *          @code
 *          RX: CanIf(0x7E0) → CanTp_RxIndication(CANTP_CHL_P2P)
 *                          → 重组完成 → PduR_CanTpRxIndication(PduR_RxPduId)
 *          TX: PduR_TpTransmit(PduR_TxPduId) → CanTp_Transmit(CANTP_CHL_P2P)
 *                          → 分段 → CanIf_Transmit(CanIfTxPduId) → 0x7E8
 *          @endcode
 *
 *          | 字段 | 值 | 含义 |
 *          |------|-----|------|
 *          | `CanIfTxPduId` | `CANIF_TX_DIAG_RESP` | 本通道发的 N-PDU 走哪个 CanIf TX PDU（0x7E8） |
 *          | `PduR_RxPduId` | `PDUR_CANTP_TO_DCM_RX` | 收全一包后交给哪条 PduR 路径（→ Dcm） |
 *          | `PduR_TxPduId` | `PDUR_DCM_TO_CANTP_TX` | 发送完成/取数据时回哪条 PduR 路径（→ Dcm） |
 *
 *          @warning `PduR_RxPduId` 必须是 **0**，不能随便改。Dcm 的
 *          `Dcm_StartOfReception(id,...)` 里 `DET_VALIDATE(id < numOfChls)`，
 *          它把 `id` 当通道索引用。
 *
 *          @section CANTPCFG_ADDR 为什么用 CANTP_STANDARD
 *          STANDARD = 经典诊断寻址：PCI 直接放在第 1 字节，不带地址字节。
 *          `CANTP_EXTENDED` 会在 PCI 前多插一个 N_TA 字节 —— 那是
 *          "同一个 CAN ID 上挂多个 ECU"的场景，本板一对一用不上。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：物理寻址 0x7E0/0x7E8，STmin=0，BS=8 |
 */

#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "CanTp_Priv.h"

#include "CanIf_Cfg.h"
#include "PduR_Cfg.h"

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 通道的 N-PDU 收发缓冲
 * @note  这是"一个 CAN 帧"的落点，不是整包缓冲。整包的组装/拆分由
 *        `CanTp_ChannelContextType.PduInfo` 指到上层（Dcm）的缓冲区完成。
 *        长度必须 >= `LL_DL`。
 */
static uint8_t CanTp_P2PData[CANTP_CFG_DATA_SIZE];

/** @brief 通道配置表（下标即通道号） */
static const CanTp_ChannelConfigType CanTp_ChannelConfigs[CANTP_CFG_NUM_CHANNELS] = {
	{
		CanTp_P2PData,                  /* data */
		CANTP_STANDARD,                 /* AddressingFormat */
		(uint8_t)CANIF_TX_DIAG_RESP,    /* CanIfTxPduId：发 0x7E8 */
		(uint8_t)PDUR_CANTP_TO_DCM_RX,  /* PduR_RxPduId：收全后 → Dcm（path 0） */
		(uint8_t)PDUR_DCM_TO_CANTP_TX,  /* PduR_TxPduId：整包发完 → Dcm（path 1） */
		(uint16_t)CANTP_CFG_N_AS,       /* N_As */
		(uint16_t)CANTP_CFG_N_BS,       /* N_Bs */
		(uint16_t)CANTP_CFG_N_CR,       /* N_Cr */
		(uint8_t)CANTP_CFG_STMIN,       /* STmin */
		(uint8_t)CANTP_CFG_BS,          /* BS */
		0u,                             /* N_TA：STANDARD 寻址不用 */
		(uint8_t)CANTP_CFG_RX_WFT_MAX,  /* CanTpRxWftMax */
		(uint8_t)CANTP_CFG_LL_DL,       /* LL_DL */
		(uint8_t)CANTP_CFG_PADDING,     /* padding */
		CANTP_PHYSICAL,                 /* comType */
	},
};

/** @brief 通道运行上下文（状态机、定时器、SN 等），运行期改写 */
static CanTp_ChannelContextType CanTp_ChannelContexts[CANTP_CFG_NUM_CHANNELS];

/* ============================ [ 总表 ] ============================ */

const CanTp_ConfigType CanTp_Config = {
	CanTp_ChannelConfigs,
	CanTp_ChannelContexts,
	(uint8_t)ARRAY_SIZE(CanTp_ChannelConfigs),
};
