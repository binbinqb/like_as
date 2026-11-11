/**
 * @file    Dio_Cfg.h
 * @brief   Dio 通道定义（通道号 → 端口/引脚）
 *
 * @details 通道号是**逻辑编号**，业务代码只认它；端口/引脚在 `Dio_Cfg.c` 里映射。
 *          换板子时只改 .c 的映射表，通道号保持稳定 —— 这是 Dio 层存在的意义。
 *
 *          本板（《CVM0146 开发板快速入门》表 8）：
 *          | 通道 | 引脚 | 用途 | 有效电平 |
 *          |------|------|------|----------|
 *          | 0 | PTC1  | CAN0 收发器 STB（TJA1044） | 低=正常，高=待机 |
 *          | 1 | PTD1  | LED 红 | 低=亮 |
 *          | 2 | PTD3  | LED 绿 | 低=亮 |
 *          | 3 | PTA17 | LED 蓝 | 低=亮 |
 *          | 4 | PTE13 | CAN1 收发器 STB（TJA1044） | 低=正常，高=待机 |
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：STB + 三色灯 |
 * | V1.1.0 | 2026-11-10 | binbina | 加 CAN1 STB（PTE13） |
 */

#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "Dio.h"

/* ============================ [ 通道号 ] ============================ */

/** @brief CAN0 收发器 STB 脚（PTC1）：LOW=Normal，HIGH=Standby */
#define DIO_CHANNEL_CAN0_STB    ((Dio_ChannelType)0u)

#define DIO_CHANNEL_LED_RED     ((Dio_ChannelType)1u)   /**< PTD1，低电平亮 */
#define DIO_CHANNEL_LED_GREEN   ((Dio_ChannelType)2u)   /**< PTD3，低电平亮 */
#define DIO_CHANNEL_LED_BLUE    ((Dio_ChannelType)3u)   /**< PTA17，低电平亮 */

/** @brief CAN1 收发器 STB 脚（PTE13）：LOW=Normal，HIGH=Standby */
#define DIO_CHANNEL_CAN1_STB    ((Dio_ChannelType)4u)

/** @brief 通道总数（必须与 Dio_Cfg.c 的映射表长度一致） */
#define DIO_CFG_NUM_CHANNELS    (5u)

#endif /* DIO_CFG_H */
