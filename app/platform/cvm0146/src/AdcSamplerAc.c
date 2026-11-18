/**
 * @file    AdcSamplerAc.c
 * @brief   AdcSampler 的目标板 HwOps（Adc HAL）与组表
 *
 * @details @section ADCSAC_WHY 为什么用 Adc_ReadGroup 而不是 AdcAc_*
 *
 *          平台层直接调 `AdcAc_*` 会绕过 MCAL 的状态机（BUSY/COMPLETED），
 *          而 `Adc_ReadGroup()` 恰好要求"已完成"才给结果 —— 这个状态检查
 *          本身就是一道防错：没启动就读会返回 `E_NOT_OK`，而不是把上一轮
 *          的寄存器值当成新样本返回。
 *
 *          @note `Adc_ReadGroup()` **不会重新触发转换**（曾有一版注释这么写，
 *                是错的）：它只做 `Adc_AdvanceState()` → 判 `ADC_COMPLETED`
 *                → `AdcAc_ReadGroupRaw()`。重新触发只发生在
 *                `Adc_StartGroupConversion()`。
 *
 *          @section ADCSAC_OWNER 组所有权
 *
 *          本表里的组由 AdcSampler 独占。MUX 的 ADC COM 必须用**另一组**
 *          （生成器 R15 校验），否则两边会互相踩：一边刚启动，另一边读到的
 *          可能是上一次的结果。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：Start/Completed/Read 绑定 Adc HAL |
 */

#include "adc_sampler.h"

#include "Adc.h"
#include "Adc_Cfg.h"

/* ============================ [ HwOps ] ============================ */

/**
 * @brief 启动一次组转换
 * @param[in] group 组号
 * @return E_OK（HAL 的启动接口无返回值，失败只能在 Completed 超时上体现）
 */
static Std_ReturnType adcsac_Start(uint8 group)
{
	Adc_StartGroupConversion((Adc_GroupType)group);
	return E_OK;
}

/**
 * @brief 查询本轮是否完成
 * @param[in]  group 组号
 * @param[out] done  TRUE = 结果可用
 * @return E_OK / E_NOT_OK（参数）
 */
static Std_ReturnType adcsac_Completed(uint8 group, boolean *done)
{
	if (done == NULL) {
		return E_NOT_OK;
	}
	*done = (Adc_GetGroupStatus((Adc_GroupType)group) == ADC_COMPLETED)
	        ? TRUE : FALSE;
	return E_OK;
}

/**
 * @brief 读整组结果（不重新触发转换）
 * @param[in]  group 组号
 * @param[out] buf   输出缓冲
 * @param[in]  n     期望槽位数（必须 ≤ ADC_CFG_MAX_CH_PER_GROUP）
 * @return E_OK / E_NOT_OK
 */
static Std_ReturnType adcsac_Read(uint8 group, uint16 *buf, uint8 n)
{
	if ((buf == NULL) || (n > ADC_CFG_MAX_CH_PER_GROUP)) {
		return E_NOT_OK;
	}
	return Adc_ReadGroup((Adc_GroupType)group, (Adc_ValueGroupType *)buf);
}

/* ============================ [ 组表 ] ============================ */

/*
 * 与 Adc_Cfg.c 的 Adc_Groups[] 一一对应（组号、通道数）。
 * 通道数用 Adc_Cfg.h 的宏，改配置时只改那一处。
 */
const AdcSampler_GroupCfgType AdcSampler_GroupCfgs[ADC_CFG_NUM_GROUPS] = {
	{ (uint8)ADC_CFG_GROUP_ADC0, (uint8)ADC_CFG_GROUP0_CHANNELS },
	{ (uint8)ADC_CFG_GROUP_ADC1, (uint8)ADC_CFG_GROUP1_CHANNELS }
};

const uint8 AdcSampler_GroupCount = (uint8)ADC_CFG_NUM_GROUPS;

const AdcSampler_HwOpsType AdcSampler_HwOps = {
	adcsac_Start,
	adcsac_Completed,
	adcsac_Read
};
