/**
 * @file    Dio_Cfg.c
 * @brief   Dio 通道映射表（通道号 → 端口号/引脚号）
 *
 * @details 端口号用 `Port_Cfg.h` 的 `PORT_PORT_x`（0=A..4=E），
 *          实际生效的 MUX/方向由 `Port_Cfg.c` 配，这里只描述"哪个引脚"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：STB + 三色灯 |
 */

#include "Dio.h"
#include "Dio_Cfg.h"
#include "Dio_Priv.h"

#include "Port_Cfg.h"
#include "Board_Cfg.h"   /* BOARD_DIO_CHANNELS（Board.json 生成） */

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 通道表，下标即通道号（与 Dio_Cfg.h 的宏一一对应）
 * @warning 顺序不能随意调整：调整等于改变通道号语义，业务代码会控制到别的引脚。
 */
static const Dio_ChannelConfigType Dio_ChannelConfigs[DIO_CFG_NUM_CHANNELS] = {
	/* 表体来自 config/Board/Board.json 的 dioChannels（按名字引用 pins）。
	 * 顺序即通道号，改顺序等于改语义 —— 与 Dio_Cfg.h 的宏一起改。 */
	BOARD_DIO_CHANNELS
};
const Dio_ConfigType Dio_Config = {
	Dio_ChannelConfigs,
	(uint16_t)ARRAY_SIZE(Dio_ChannelConfigs),
};
