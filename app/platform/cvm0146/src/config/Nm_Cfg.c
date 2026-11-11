/**
 * @file    Nm_Cfg.c
 * @brief   Nm 的通道表（单通道，CAN0 → CanNm）
 *
 * @details @section NMCFG_C_ONE 为什么表里只有一项却还要这张表
 *
 *          `Nm.c` 的每个接口第一步都是
 *          `DET_VALIDATE(NetworkHandle < NM_CONFIG->numOfChannels, ...)`，
 *          然后按 `busType` 分发。也就是说 **Nm 的所有能力都由这张表驱动**。
 *
 *          只配一项时它看起来像多余的间接层 —— 但它的价值在"将来"：
 *          加一根 CAN（CAN1 的 NM）只要在这张表加一行 + 在 `CanNm_Cfg.c`
 *          加一个通道，`ComM`/`EcuM`/应用的调用**一行都不用改**。
 *          这正是分层的目的，不能在只有一项时就把它当冗余删掉。
 *
 *          @section NMCFG_C_HANDLE 三个 handle 的区别
 *
 *          | 字段 | 含义 | 本工程取值 |
 *          |------|------|------------|
 *          | `busType` | 这根总线用哪种 NM 状态机 | `NM_BUSNM_CANNM` |
 *          | `handle` | 传给 `CanNm_*()` 的通道号 | 0 |
 *          | `ComMHandle` | 传给 `ComM_Nm_*()` 的通道号 | 0 |
 *
 *          `handle` 必须是 `CanNm_Config` 里 `ChannelConfigs[]` 的下标 ——
 *          `CanNm_TxConfirmation()` 和 `CanNm_RxIndication()` 都直接拿它当数组下标用
 *          （`CanNm.c:810` / `:851`），填错就是越界读，且不会有任何提示。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道 CAN0 |
 */

#include "Nm.h"
#include "Nm_Cfg.h"
#include "Nm_Priv.h"

/* ============================ [ 通道表 ] ============================ */

static const Nm_ChannelConfigType Nm_ChannelConfigs[] = {
	{
		/** @brief 总线类型：CAN 网络管理（对应 `CanNm_*`） */
		.busType     = NM_BUSNM_CANNM,
		/** @brief CanNm 通道号：`CanNm_ChannelConfigs[]` 的下标 */
		.handle      = (NetworkHandleType)NM_CFG_CHANNEL_CAN0,
		/** @brief ComM 通道号 */
		.ComMHandle  = (NetworkHandleType)NM_CFG_COMM_HANDLE_CAN0,
	},
};

/* ============================ [ 总表 ] ============================ */

const Nm_ConfigType Nm_Config = {
	Nm_ChannelConfigs,
	(uint8_t)ARRAY_SIZE(Nm_ChannelConfigs),
};
