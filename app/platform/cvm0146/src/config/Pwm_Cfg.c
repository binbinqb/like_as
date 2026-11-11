/**
 * @file    Pwm_Cfg.c
 * @brief   PWM 通道配置表（CVM0146 开发板）
 * @details 本表的取值依据两条：
 *          1. 《福田 L1 平台 24V IDM 功能规范》—— 顶灯的 PWM 频率与占空比曲线
 *          2. `refs/.../examples/CVM0146/driver_examples/pwm_lite_output`
 *             —— 引脚与 mux 的对应关系（**以例程为准，不以 pin_mux.xlsx 的
 *             ALT 列编号为准**，那张表的列偏移容易数错一位）
 *
 *          @section PWMC_CFG_WHY 为什么 4 个通道都是 100 Hz
 *          PwmLite 的**周期是模块级**的（`PwmLiteDrv_ModuleConfig` 只有一个
 *          `period`），不是通道级。本表 4 个通道都落在实例 0，所以必须同频率。
 *
 *          真实项目里不同频率要分到不同实例：
 *          | 负载 | 频率 | 依据 |
 *          |------|------|------|
 *          | 顶灯渐亮 | **100 Hz** | IL001 明文 |
 *          | 鼓风机调速（PWM+RC 模拟 0~12V） | 20 kHz 量级 | 纹波要小，频率越高越好 |
 *          | 水泵 PWM | 2 Hz ~ 2 kHz（推荐 200 Hz） | 框图注 |
 *          | 三通比例阀 | 由阀厂给定 | 框图注 |
 *
 *          所以将来这几个负载要**各自占一个 PwmLite 实例**。
 *
 *          @warning **`PWM4~7` 在本芯片上与 CAN 复用，不可用**。详见
 *          `PwmAc.c` 的 `s_padMap` 表 —— 配错不是"PWM 不出波形"，
 *          而是"CAN 直接不通"。
 *
 * @author  binbina
 * @version V1.0.0
 * @date    2026-11-11
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：顶灯 100Hz + 3 路不同占空比验证通道 |
 */

#include "Pwm.h"
#include "Pwm_Priv.h"
#include "Pwm_Cfg.h"

/* ============================ [ 配置表 ] ============================ */

/**
 * @brief PWM 通道配置表
 *
 * @note 用 designated initializer 而不是位置初始化：字段多，位置初始化
 *       在将来插入新字段时会**静默错位**（编译通过、行为不对）。
 *
 * @note `defaultDuty` 是上电初值。顶灯给 0（灭），验证通道给固定占空比
 *       便于用示波器/逻辑分析仪直接看到波形，不用先发命令。
 */
static const Pwm_ChannelConfigType Pwm_Channels[PWM_CFG_NUM_CHANNELS] = {
	/* ---- ch0：顶灯（IL001 渐亮） ---- */
	{
		.hwModule     = 0u,             /* PwmLite0 */
		.hwChannel    = 0u,             /* PWMLITEDRV_PWM_CH0 */
		.pad          = 0u,             /* PAD0 → PTD0 */
		.frequencyHz  = 100u,           /* 规范要求 100 Hz */
		.polarity     = 0u,             /* 正极性：占空比 = 高电平占比 */
		.idleState    = 0u,             /* 空闲 = 低（灯灭） */
		.channelClass = (uint8_t)PWM_FIXED_PERIOD,
		.defaultDuty  = 0u,             /* 上电灭 */
	},

	/* ---- ch1：验证用，50% ---- */
	{
		.hwModule     = 0u,
		.hwChannel    = 1u,             /* PWMLITEDRV_PWM_CH1 */
		.pad          = 1u,             /* PAD1 → PTD1 */
		.frequencyHz  = 100u,           /* 必须与同实例一致 */
		.polarity     = 0u,
		.idleState    = 0u,
		.channelClass = (uint8_t)PWM_FIXED_PERIOD,
		.defaultDuty  = 0x4000u,        /* 50% */
	},

	/* ---- ch2：验证用，25% ---- */
	{
		.hwModule     = 0u,
		.hwChannel    = 2u,             /* PWMLITEDRV_PWM_CH2 */
		.pad          = 2u,             /* PAD2 → PTE15 */
		.frequencyHz  = 100u,
		.polarity     = 0u,
		.idleState    = 0u,
		.channelClass = (uint8_t)PWM_FIXED_PERIOD,
		.defaultDuty  = 0x2000u,        /* 25% */
	},

	/* ---- ch3：验证用，75% ---- */
	{
		.hwModule     = 0u,
		.hwChannel    = 3u,             /* PWMLITEDRV_PWM_CH3 */
		.pad          = 3u,             /* PAD3 → PTE16 */
		.frequencyHz  = 100u,
		.polarity     = 0u,
		.idleState    = 0u,
		.channelClass = (uint8_t)PWM_FIXED_PERIOD,
		.defaultDuty  = 0x6000u,        /* 75% */
	},
};

/**
 * @brief 驱动初始化用的唯一配置实例
 * @note  表长用 `PWM_CFG_NUM_CHANNELS` 与 `ARRAY_SIZE` 双重约束：
 *        少写一条会编译不过（数组初始化不足），多写一条会编译不过（超出）。
 */
const Pwm_ConfigType Pwm_Config = {
	.channels       = Pwm_Channels,
	.numOfChannels  = (uint16_t)PWM_CFG_NUM_CHANNELS,
};

/* 编译期自检：表长必须与宏一致，避免"改了宏忘改表" */
typedef char Pwm_Cfg_ChannelCountCheck[
	(ARRAY_SIZE(Pwm_Channels) == PWM_CFG_NUM_CHANNELS) ? 1 : -1];
