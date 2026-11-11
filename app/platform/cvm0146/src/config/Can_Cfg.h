/**
 * @file    Can_Cfg.h
 * @brief   CAN 通道配置的对外声明
 *
 * @details **不含任何厂商头**：本文件会被 `infras/mcal/Can/Can.c` 直接包含，
 *          一旦引入厂商类型，BSW 就被绑死在这颗芯片上，分层也就破了。
 *          厂商相关的邮箱表在 `src/CanAc.c` 内部，不出现在这里。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：M1 只开 CAN0 |
 */

#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Can.h"

/* ============================ [ 通道 ] ============================ */

#define CAN_CHL_CAN0            (0u)
#define CAN_CHL_CAN1            (1u)

/** @brief 启用的控制器数量（M2：CAN0 + CAN1 双通道） */
#define CAN_CFG_NUM_CHANNELS    (2u)

/** @brief 波特率（Kvaser 两路都配 500 kbps） */
#define CAN_CFG_BAUDRATE        (500000u)

/** @brief 采样点，单位 1%（75% 是 CAN 的通用推荐值） */
#define CAN_CFG_SAMPLE_POINT    (75u)

/* ============================ [ 平台扩展：总线状态查询 ] ============================ */
/*
 * 下面这组不属于 AUTOSAR Can 标准接口 —— 标准里 bus-off 是 CanSM 的职责，
 * 应用拿不到。本工程没有 CanSM，但应用必须能知道"总线上出过什么事"，
 * 否则故障码无从记录、bus-off 之后也没有任何痕迹。
 *
 * 放在 `Can_Cfg.h` 而不是另建头文件：应用已经 include 它，
 * 少一个头文件就少一处 include 顺序问题。
 */

/**
 * @brief bus-off 现场信息
 * @note  只有 `count` 是累计值，其余三项都是**首次** bus-off 那一刻的快照
 *        （`ESR1` 在硬件自动恢复后立刻回到 error-active，事后再读全是 0）。
 */
typedef struct {
	uint16_t count;      /**< 累计 bus-off 次数（饱和 0xFFFF，不回零） */
	uint8_t  fltConf;    /**< 首次发生时的 FLTCONF：0=error active, 1=error passive, 2=bus-off */
	uint8_t  errBits;    /**< 首次发生时观察到的错误类型，取值见 `CAN_BUSOFF_ERR_*` */
} Can_BusOffInfoType;

/** @brief 错误位图：bit0 = bit1 错 */
#define CAN_BUSOFF_ERR_BIT1     (0x01u)
/** @brief 错误位图：bit1 = bit0 错 */
#define CAN_BUSOFF_ERR_BIT0     (0x02u)
/** @brief 错误位图：bit2 = ACK 错（总线上没有其它节点应答，最常见的一种） */
#define CAN_BUSOFF_ERR_ACK      (0x04u)
/** @brief 错误位图：bit3 = CRC 错 */
#define CAN_BUSOFF_ERR_CRC      (0x08u)
/** @brief 错误位图：bit4 = 格式错 */
#define CAN_BUSOFF_ERR_FORM     (0x10u)
/** @brief 错误位图：bit5 = 填充错 */
#define CAN_BUSOFF_ERR_STUFF    (0x20u)

/**
 * @brief 取某通道的 bus-off 统计与首次快照
 * @param[in]  controller 通道号（`CAN_CHL_CAN0` / `CAN_CHL_CAN1`）
 * @param[out] info       输出结构；通道号越界时不写
 * @retval true  通道号合法，`info` 已填
 * @retval false 通道号越界或 `info` 为 NULL
 */
bool CanAc_GetBusOffInfo(uint8_t controller, Can_BusOffInfoType *info);

/**
 * @brief 控制器**当前**是否处于 bus-off
 * @details 读的是 `ESR1.FLTCONF` 的实时值，不是历史计数。
 *          硬件开了自动恢复（`BOFFREC=1`），所以正常情况下几毫秒后就变回 false。
 * @retval true  此刻仍在 bus-off
 */
bool CanAc_IsBusOff(uint8_t controller);

/**
 * @brief 清零 bus-off 计数与快照（验收用）
 * @note  给 `!B` 命令清故障表时配套使用，业务代码不要调。
 */
void CanAc_ClearBusOffInfo(uint8_t controller);

/**
 * @brief 打印控制器关键寄存器（**仅供 bring-up 排查**）
 * @note  能看到 `TEC/REC`、`FLTCONF`、`BOFFINT`、`BOFFMSK`。
 *        "为什么没进 bus-off 中断"这类问题，第一步就是看 TEC 有没有涨。
 */
void CanAc_DbgDump(uint8_t controller);

#endif /* CAN_CFG_H */
