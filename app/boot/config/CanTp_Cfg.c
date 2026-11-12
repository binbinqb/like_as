/**
 * @file    CanTp_Cfg.c
 * @brief   boot 版 CanTp 通道表：1 条物理寻址诊断链路
 *
 * @details 与 app 版**内容等价**（参数全部相同），区别只在 include：
 *          app 那份 include 的是 app 的 `CanIf_Cfg.h` / `PduR_Cfg.h`
 *          （`CANIF_TX_DIAG_RESP = 3`），boot 这份拿到的是 boot 版
 *          （`CANIF_TX_DIAG_RESP = 0`）。
 *
 *          **为什么不直接复用 app 的 `CanTp_Cfg.c`**：它在 CanTp 库里编译，
 *          用的是 `$CanTp_Cfg` 指向的 app 配置目录 —— 找不到 boot 版的
 *          `CanIf_Cfg.h`，会拿到 app 的 PDU 号 3，而 boot 的 CanIf 只有 1 条
 *          TX PDU（编号 0）→ `CanIf_Transmit(3)` 越界。
 *          这个错误不会在编译期暴露，只会在刷写时一声不响。
 *
 * @note    `CanTp_Cfg.h`（时序参数）**刻意复用 app 那份**：STmin/BS/N_As
 *          这些值必须两边一致，否则"app 里能刷、boot 里超时"。
 *          将来 M24 按福田规范改 BS=0 / STmin=10ms 时，改一处两边都生效。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-12 | binbina | 首版：boot 专用通道表 |
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
