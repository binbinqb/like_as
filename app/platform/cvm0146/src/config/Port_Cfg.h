/**
 * @file    Port_Cfg.h
 * @brief   端口号定义（0=A .. 4=E）与引脚表规模
 *
 * @details 端口号是给 `Platform_GetPort()` 用的内部编号，与 CVM014x 的 PORTA..PORTE 一一对应。
 *          AS 的 simulator 平台用同样的编号，配置表可以在平台之间直接照搬。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：PORTA..PORTE 编号 |
 * | V1.1.0 | 2026-11-10 | binbina | 引脚表 6 → 9：加 CAN1 的 PTC6/PTC7/PTE13 |
 */

#ifndef PORT_CFG_H
#define PORT_CFG_H

/* ============================ [ 端口号 ] ============================ */

#define PORT_PORT_A     (0u)
#define PORT_PORT_B     (1u)
#define PORT_PORT_C     (2u)
#define PORT_PORT_D     (3u)
#define PORT_PORT_E     (4u)

/* ============================ [ 规模 ] ============================ */

/** @brief 引脚表长度（必须与 Port_Cfg.c 的数组长度一致） */
#define PORT_CFG_NUM_PINS   (9u)

#endif /* PORT_CFG_H */
