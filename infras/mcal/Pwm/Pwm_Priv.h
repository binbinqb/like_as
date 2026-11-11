/**
 * @file    Pwm_Priv.h
 * @brief   PWM 驱动的配置结构与平台层边界
 * @details 这一层是**分层分界线**：本文件之上的 `Pwm.c` 只做参数校验与查表转发，
 *          不出现任何寄存器名；本文件声明的 `PwmAc_*()` 由平台层
 *          （`app/platform/<平台>/src/PwmAc.c`）实现，那里才允许碰 SDK。
 *
 *          判断分层有没有破的硬标准：**`Pwm.c` 里不出现 `PWMLITE`
 *          / `pwmLiteDrv` / `PINSDRV` 任何一个词**。
 *
 * @author  binbina
 * @version V1.0.0
 * @date    2026-11-11
 */

#ifndef _PWM_PRIV_H_
#define _PWM_PRIV_H_

#include "Std_Types.h"
#include "Pwm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 宏 ] ============================ */

/** @brief 平台不支持的实例号 / 引脚号 / 通道号（配置表里填它表示"不用"） */
#define PWM_HW_NONE                     (0xFFu)

/* ============================ [ 类型 ] ============================ */

/**
 * @brief 单个 PWM 通道的配置
 *
 * @details 六个字段的取值都直接来自硬件的层次结构，不做抽象：
 *
 *          ```
 *          PwmLite 实例 (hwModule: 0~4)
 *            └─ 实例内通道 (hwChannel: 0~7)
 *                 └─ mux 到物理引脚 (pad: 0~7)
 *          ```
 *
 *          @warning **PwmLite 的周期是模块级的，不是通道级**
 *          （`PwmLiteDrv_ModuleConfig()` 的 `period`）。所以**同一个
 *          `hwModule` 内的所有通道必须同频率**。`Pwm_Init()` 会检查这一点并
 *          在冲突时拒绝初始化 —— 否则表现是"设了 100 Hz 出来是别的频率"，
 *          而且不会有任何报错。
 */
typedef struct {
	/** @brief PwmLite 实例号（0~4，对应 `pwmLiteDrv0`~`pwmLiteDrv4`） */
	uint8_t hwModule;

	/** @brief 实例内通道号（0~7，即 `PWMLITEDRV_PWM_CH0`~`CH7`） */
	uint8_t hwChannel;

	/**
	 * @brief 输出到的物理引脚编号（0~7，即 `PWMLITEDRV_MUX_PAD_PWM0`~`PWM7`）
	 * @note  `muxChannel` 不需要单独填：本工程约定 `muxChannel = hwModule*8 + hwChannel`，
	 *        与 SDK 的 `PWMLITEDRV_MUX_PWM<m>_CH<n>` 编码一致
	 *        （`MUX_PWM1_CH0` = 0x08 = 1*8+0）。
	 */
	uint8_t pad;

	/**
	 * @brief PWM 频率（Hz）
	 *
	 * @warning **这里是频率，不是 `Pwm_PeriodType` 的计数单位。**
	 *
	 *          为什么不按标准的"计数单位"填：`period = APB时钟 / 频率`，
	 *          而 APB 频率要运行期用 `ClockDrv_GetFreq(CLOCKDRV_APB)` 才拿到。
	 *          配置表是 `const`，编译期无法算；写死一个假定值又会在改时钟后
	 *          静默错频（症状是"设 100 Hz 出来不是 100 Hz"，且没有任何报错）。
	 *
	 *          所以约定：**配置表写 Hz，平台层在 `PwmAc_Init()` 里换算**。
	 *          好处是与功能规范直接对齐（"PWM 频率 100 Hz"就写 100）。
	 *
	 *          `Pwm_SetPeriodAndDuty()` 的 `Period` 参数仍按 AUTOSAR 语义
	 *          （计数单位），换算用 `Pwm_CalcPeriod()`。
	 */
	uint32_t frequencyHz;

	/**
	 * @brief 极性
	 * @retval 0 正极性：占空比 = 高电平时间占比
	 * @retval 1 反极性：占空比 = 低电平时间占比
	 * @note  按 `[SWS_Pwm_00014]`，0 % 时输出"极性的反"，100 % 时输出"极性本身"。
	 *        所以反极性通道的 0 % 是高电平 —— 配置时要想清负载的安全态。
	 */
	uint8_t polarity;

	/** @brief 空闲电平（`Pwm_SetOutputToIdle` / `Pwm_DeInit` 用）：0=低，1=高 */
	uint8_t idleState;

	/** @brief 通道类别（`Pwm_ClassType`），决定能否运行期改周期 */
	uint8_t channelClass;

	/** @brief 初始占空比（0x0000~0x8000） */
	Pwm_DutyCycleType defaultDuty;
} Pwm_ChannelConfigType;

/** @brief PWM 的完整配置 */
struct Pwm_Config_s {
	/** @brief 通道配置数组（下标即 `Pwm_ChannelType`） */
	const Pwm_ChannelConfigType *channels;

	/** @brief 通道数 */
	uint16_t numOfChannels;
};

/* ============================ [ 平台层要实现 ] ============================ */

/**
 * @brief 平台初始化：开时钟、配引脚复用、配模块与通道、使能输出
 * @param[in] cfg 配置表
 * @note  必须在 `Pwm_Init()` 里、参数校验之后调用。
 * @note  **时钟门控是必须显式打开的**（与 ADC 同样的坑）：`Mcu_Init()` 只做
 *        `PwmLiteDrv_Init()`（存指针），不开 `CLOCKDRV_PWMLITE<n>` 的 gating。
 *        漏掉的表现是"配置全部成功、引脚没有任何波形"，且零报错。
 */
void PwmAc_Init(const Pwm_ConfigType *cfg);

/**
 * @brief 平台反初始化：所有通道输出空闲电平，关闭模块
 */
void PwmAc_DeInit(void);

/**
 * @brief 设置单个通道的占空比
 * @param[in] ch   通道号（已由上层校验过范围）
 * @param[in] c    该通道的配置项
 * @param[in] duty 占空比（0x0000~0x8000，已由上层钳位）
 */
void PwmAc_SetDutyCycle(uint16_t ch, const Pwm_ChannelConfigType *c,
                        Pwm_DutyCycleType duty);

/**
 * @brief 同时设置周期与占空比
 * @param[in] ch     通道号
 * @param[in] c      该通道的配置项
 * @param[in] period 新周期（计数单位）
 * @param[in] duty   占空比（0x0000~0x8000）
 */
void PwmAc_SetPeriodAndDuty(uint16_t ch, const Pwm_ChannelConfigType *c,
                           Pwm_PeriodType period, Pwm_DutyCycleType duty);

/**
 * @brief 把通道输出设为空闲电平
 * @param[in] ch 通道号
 * @param[in] c  该通道的配置项
 */
void PwmAc_SetOutputToIdle(uint16_t ch, const Pwm_ChannelConfigType *c);

/**
 * @brief 读取通道当前输出电平
 * @param[in] ch 通道号
 * @param[in] c  该通道的配置项
 * @return PWM_HIGH / PWM_LOW
 */
Pwm_OutputStateType PwmAc_GetOutputState(uint16_t ch,
                                         const Pwm_ChannelConfigType *c);

/**
 * @brief 读取 PWM 定时器的输入时钟频率（Hz）
 * @return 定时器时钟频率；读不到时返回 0
 * @note  供 `Pwm_CalcPeriod()` 做 Hz → 周期计数的换算。框架层不能直接调
 *        `ClockDrv_GetFreq()`（那就把平台知识泄漏上去了），所以由这里转一手。
 */
uint32_t PwmAc_GetTimerFreq(void);

#ifdef __cplusplus
}
#endif

#endif /* _PWM_PRIV_H_ */
