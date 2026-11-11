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

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 通道表，下标即通道号（与 Dio_Cfg.h 的宏一一对应）
 * @warning 顺序不能随意调整：调整等于改变通道号语义，业务代码会控制到别的引脚。
 */
static const Dio_ChannelConfigType Dio_ChannelConfigs[DIO_CFG_NUM_CHANNELS] = {
	{ (uint8_t)PORT_PORT_C, 1u  },   /* 0: PTC1  CAN0 STB */
	{ (uint8_t)PORT_PORT_D, 1u  },   /* 1: PTD1  LED 红 */
	{ (uint8_t)PORT_PORT_D, 3u  },   /* 2: PTD3  LED 绿 */
	{ (uint8_t)PORT_PORT_A, 17u },   /* 3: PTA17 LED 蓝 */
	{ (uint8_t)PORT_PORT_E, 13u },   /* 4: PTE13 CAN1 STB */
};

const Dio_ConfigType Dio_Config = {
	Dio_ChannelConfigs,
	(uint16_t)ARRAY_SIZE(Dio_ChannelConfigs),
};
