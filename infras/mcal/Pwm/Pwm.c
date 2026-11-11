/**
 * @file    Pwm.c
 * @brief   PWM 驱动的芯片无关实现（AUTOSAR MCAL）
 * @details 本文件**只做四件事**，与 `Adc.c` / `Dio.c` 同一套路：
 *          1. DET 参数校验；
 *          2. 维护模块的初始化状态；
 *          3. 查配置表 + 做参数归一化（占空比钳位）；
 *          4. 转发给平台 `PwmAc_*()`。
 *
 *          @warning **这里不允许出现任何寄存器名或芯片型号**。
 *                   一旦在 `Pwm.c` 里看到 `PWMLITE` / `pwmLiteDrv` / `PINSDRV`，
 *                   分层就破了 —— 换芯片时要改的就是这一层，那就失去了分层的意义。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：Init/DeInit/SetDutyCycle/SetPeriodAndDuty/SetOutputToIdle/GetOutputState |
 */
#ifdef USE_PWM
/* ================================ [ INCLUDES  ] ============================================== */
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "Pwm_Priv.h"
#include "Det.h"
#include "Std_Debug.h"
#include <string.h>
/* ================================ [ MACROS    ] ============================================== */
#define AS_LOG_PWM 0
#define AS_LOG_PWMI 0
#define AS_LOG_PWME 3

/** @brief 全局唯一的配置实例（由 `Pwm_Cfg.c` 定义） */
#define PWM_CONFIG (&Pwm_Config)

/**
 * @brief 占空比的满量程（对应 100%）
 * @note  标准规定是 0x8000 而不是 0xFFFF —— 用 0xFFFF 会让 50% 变成 49.998%，
 *        在 16 位分辨率下看不出来，但和"按 0x8000 算"的模块对接时会差 1 个 LSB。
 */
#define PWM_DUTY_FULL       (0x8000u)
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
extern const Pwm_ConfigType Pwm_Config;
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/** @brief 模块是否已初始化（未初始化时所有服务都应被 DET 拦下） */
static boolean s_initialized = FALSE;
/* ================================ [ ALIAS     ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */

/**
 * @brief 检查同一硬件实例内的频率是否一致
 *
 * @details PwmLite 的周期是**模块级**（`PwmLiteDrv_ModuleConfig()` 的
 *          `period`），不是通道级。同一个实例里配两个不同频率，硬件上做不到 ——
 *          后配的会覆盖先配的，两个通道都变成后一个频率。
 *
 *          这个检查放在 `Init` 而不是等到波形不对再查，因为**它的症状是
 *          "频率不对"而不是"不工作"**：示波器不用看不出，用逻辑分析仪测了
 *          也容易怀疑成"分频算错了"。
 *
 * @param[in] cfg 配置表
 * @return TRUE 一致 / FALSE 有冲突
 */
static boolean Pwm_CheckPeriodConsistency(const Pwm_ConfigType *cfg)
{
	uint16_t i;
	uint16_t j;

	for (i = 0u; i < cfg->numOfChannels; i++) {
		for (j = 0u; j < i; j++) {
			if (cfg->channels[i].hwModule == cfg->channels[j].hwModule) {
				if (cfg->channels[i].frequencyHz != cfg->channels[j].frequencyHz) {
					ASLOG(PWME, ("ch%u(module%u,%uHz) conflicts with ch%u(%uHz)\n",
					             (unsigned)i, (unsigned)cfg->channels[i].hwModule,
					             (unsigned)cfg->channels[i].frequencyHz,
					             (unsigned)j, (unsigned)cfg->channels[j].frequencyHz));
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

void Pwm_Init(const Pwm_ConfigType *ConfigPtr)
{
	DET_VALIDATE(!s_initialized, PWM_SID_INIT, PWM_E_ALREADY_INITIALIZED, return);

	/* ---- 以下两项**不能**用 DET_VALIDATE ---- */
	/*
	 * `DET_VALIDATE` 在 `DET_CFG_ENABLE == 0` 时是空宏（见 `Det.h`），
	 * 也就是说生产构建里整条检查会消失。下面两项的后果不是"参数不好看"，
	 * 而是**崩溃或静默错误**，所以必须独立于 DET 开关：
	 *
	 *   1. ConfigPtr 为 NULL → 解引用直接 HardFault
	 *   2. 同实例频率冲突 → 硬件做不到，后配的覆盖先配的，
	 *      两个通道都变成后一个频率，**没有任何报错**
	 */
	if ((ConfigPtr == NULL) || (ConfigPtr->channels == NULL)) {
		ASLOG(PWME, ("Pwm_Init: NULL config, aborted\n"));
		return;
	}
	if (!Pwm_CheckPeriodConsistency(ConfigPtr)) {
		ASLOG(PWME, ("Pwm_Init: period conflict in same PwmLite module, aborted\n"));
		return;
	}

	PwmAc_Init(ConfigPtr);

	s_initialized = TRUE;
}

void Pwm_DeInit(void)
{
	DET_VALIDATE(s_initialized, PWM_SID_DEINIT, PWM_E_UNINIT, return);

	PwmAc_DeInit();

	s_initialized = FALSE;
}

void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, Pwm_DutyCycleType DutyCycle)
{
	Pwm_DutyCycleType duty = DutyCycle;

	DET_VALIDATE(s_initialized, PWM_SID_SET_DUTY_CYCLE, PWM_E_UNINIT, return);
	DET_VALIDATE(ChannelNumber < PWM_CONFIG->numOfChannels,
	             PWM_SID_SET_DUTY_CYCLE, PWM_E_PARAM_CHANNEL, return);

	/* 超范围钳位而不报错：与 Adc 的处理风格一致。
	 * 业务层算出来的占空比偶尔会因为四舍五入越界（比如算出 0x8001），
	 * 为这个报错会让调用方到处写判断，不划算。 */
	if (duty > (Pwm_DutyCycleType)PWM_DUTY_FULL) {
		duty = (Pwm_DutyCycleType)PWM_DUTY_FULL;
	}

	PwmAc_SetDutyCycle(ChannelNumber, &PWM_CONFIG->channels[ChannelNumber], duty);
}

void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber,
                          Pwm_PeriodType Period,
                          Pwm_DutyCycleType DutyCycle)
{
	Pwm_DutyCycleType duty = DutyCycle;

	DET_VALIDATE(s_initialized, PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_UNINIT, return);
	DET_VALIDATE(ChannelNumber < PWM_CONFIG->numOfChannels,
	             PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_PARAM_CHANNEL, return);

	/* 固定周期的通道不许改周期（[SWS_Pwm_00047]） */
	DET_VALIDATE(PWM_CONFIG->channels[ChannelNumber].channelClass
	                 != (uint8_t)PWM_FIXED_PERIOD,
	             PWM_SID_SET_PERIOD_AND_DUTY,
	             PWM_E_PERIOD_UNCHANGEABLE, return);

	DET_VALIDATE(Period > 0u, PWM_SID_SET_PERIOD_AND_DUTY,
	             PWM_E_PARAM_CHANNEL, return);

	if (duty > (Pwm_DutyCycleType)PWM_DUTY_FULL) {
		duty = (Pwm_DutyCycleType)PWM_DUTY_FULL;
	}

	PwmAc_SetPeriodAndDuty(ChannelNumber, &PWM_CONFIG->channels[ChannelNumber],
	                       Period, duty);
}

void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber)
{
	DET_VALIDATE(s_initialized, PWM_SID_SET_OUTPUT_TO_IDLE, PWM_E_UNINIT, return);
	DET_VALIDATE(ChannelNumber < PWM_CONFIG->numOfChannels,
	             PWM_SID_SET_OUTPUT_TO_IDLE, PWM_E_PARAM_CHANNEL, return);

	PwmAc_SetOutputToIdle(ChannelNumber, &PWM_CONFIG->channels[ChannelNumber]);
}

Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber)
{
	DET_VALIDATE(s_initialized, PWM_SID_GET_OUTPUT_STATE,
	             PWM_E_UNINIT, return PWM_LOW);
	DET_VALIDATE(ChannelNumber < PWM_CONFIG->numOfChannels,
	             PWM_SID_GET_OUTPUT_STATE, PWM_E_PARAM_CHANNEL, return PWM_LOW);

	return PwmAc_GetOutputState(ChannelNumber, &PWM_CONFIG->channels[ChannelNumber]);
}

void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber,
                            Pwm_EdgeNotificationType Edge)
{
	(void)Edge;

	DET_VALIDATE(s_initialized, PWM_SID_ENABLE_NOTIFICATION,
	             PWM_E_UNINIT, return);
	DET_VALIDATE(ChannelNumber < PWM_CONFIG->numOfChannels,
	             PWM_SID_ENABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL, return);

	/* 本工程未实现硬件边沿中断：BCM 没有"必须在 PWM 边沿做动作"的场景。
	 * 保留空实现是为了接口完整，将来要用时不必改头文件。 */
}

void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber)
{
	DET_VALIDATE(s_initialized, PWM_SID_DISABLE_NOTIFICATION,
	             PWM_E_UNINIT, return);
	DET_VALIDATE(ChannelNumber < PWM_CONFIG->numOfChannels,
	             PWM_SID_DISABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL, return);
}

Pwm_PeriodType Pwm_CalcPeriod(uint32_t frequencyHz)
{
	uint32_t clk;

	if (frequencyHz == 0u) {
		return 0u;
	}

	clk = PwmAc_GetTimerFreq();
	if (clk == 0u) {
		return 0u;
	}

	return (Pwm_PeriodType)(clk / frequencyHz);
}

boolean Pwm_IsInitialized(void)
{
	return s_initialized;
}

void Pwm_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	DET_VALIDATE(versioninfo != NULL, PWM_SID_GET_VERSION_INFO,
	             PWM_E_PARAM_POINTER, return);

	if (versioninfo != NULL) {
		versioninfo->vendorID         = 0u;
		versioninfo->moduleID         = (uint16_t)MODULE_ID_PWM;
		versioninfo->sw_major_version = 1u;
		versioninfo->sw_minor_version = 0u;
		versioninfo->sw_patch_version = 0u;
	}
}
#endif /* USE_PWM */
