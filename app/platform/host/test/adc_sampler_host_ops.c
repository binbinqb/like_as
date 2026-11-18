/**
 * @file    adc_sampler_host_ops.c
 * @brief   Host 上的 AdcSampler 硬件替身：可控的转换延迟、故障与取值
 *
 * @details @section HOSTADC_WHY 能验证什么
 *
 *          `adc_sampler.c` 在 Target 与 Host 上编同一份。这里只模拟 Adc HAL：
 *          - 转换需要若干次查询才完成（`HostAdc_SetReadyAfter`）；
 *          - 读失败（`HostAdc_SetReadFail`）与启动失败（`SetStartFail`）；
 *          - 每组每槽位的返回值可以单独摆。
 *
 *          这样"完成才发布、失败不发布、超时丢弃"就能在 Host 上确定性地测，
 *          不用靠示波器猜。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：两组（2 通道 / 1 通道）+ 延迟/故障注入 |
 */

#include "adc_sampler.h"

/* 组索引 = 0..1；组号与索引相同，便于断言 */
#define HOST_ADC_GROUPS  (2u)

static uint16  s_val[HOST_ADC_GROUPS][ADC_SAMPLER_CH_MAX];
static uint8   s_readyAfter[HOST_ADC_GROUPS];
static uint8   s_left[HOST_ADC_GROUPS];
static uint8   s_pending[HOST_ADC_GROUPS];
static uint8   s_startFail[HOST_ADC_GROUPS];
static uint8   s_readFail[HOST_ADC_GROUPS];
static uint16  s_starts;

/* ============================ [ 测试控制 ] ============================ */

void HostAdc_Reset(void)
{
	uint8 g;

	s_starts = 0u;
	for (g = 0u; g < HOST_ADC_GROUPS; g++) {
		s_left[g] = 0u;
		s_pending[g] = 0u;
	}
}

void HostAdc_SetValue(uint8 group, uint8 slot, uint16 raw)
{
	if ((group < HOST_ADC_GROUPS) && (slot < ADC_SAMPLER_CH_MAX)) {
		s_val[group][slot] = raw;
	}
}

/** @brief 转换需要多少次查询才完成（0 = 下一次查询就绪） */
void HostAdc_SetReadyAfter(uint8 group, uint8 polls)
{
	if (group < HOST_ADC_GROUPS) {
		s_readyAfter[group] = polls;
	}
}

void HostAdc_SetStartFail(uint8 group, boolean fail)
{
	if (group < HOST_ADC_GROUPS) {
		s_startFail[group] = (fail != FALSE) ? 1u : 0u;
	}
}

void HostAdc_SetReadFail(uint8 group, boolean fail)
{
	if (group < HOST_ADC_GROUPS) {
		s_readFail[group] = (fail != FALSE) ? 1u : 0u;
	}
}

uint16 HostAdc_GetStarts(void)
{
	return s_starts;
}

/* ============================ [ HwOps ] ============================ */

static Std_ReturnType hostadc_Start(uint8 group)
{
	if (group >= HOST_ADC_GROUPS) {
		return E_NOT_OK;
	}
	if (s_startFail[group] != 0u) {
		return E_NOT_OK;
	}
	s_starts++;
	s_pending[group] = 1u;
	s_left[group] = s_readyAfter[group];
	return E_OK;
}

static Std_ReturnType hostadc_Completed(uint8 group, boolean *done)
{
	if ((group >= HOST_ADC_GROUPS) || (done == NULL)) {
		return E_NOT_OK;
	}
	if (s_pending[group] == 0u) {
		*done = FALSE;
		return E_OK;
	}
	if (s_left[group] > 0u) {
		s_left[group]--;
		*done = FALSE;
	} else {
		*done = TRUE;
	}
	return E_OK;
}

static Std_ReturnType hostadc_Read(uint8 group, uint16 *buf, uint8 n)
{
	uint8 i;

	if ((group >= HOST_ADC_GROUPS) || (buf == NULL) ||
	    (n > ADC_SAMPLER_CH_MAX)) {
		return E_NOT_OK;
	}
	if (s_pending[group] == 0u) {
		return E_NOT_OK;
	}
	if (s_readFail[group] != 0u) {
		s_pending[group] = 0u;      /* 失败也结束本轮，避免死等 */
		return E_NOT_OK;
	}
	for (i = 0u; i < n; i++) {
		buf[i] = s_val[group][i];
	}
	s_pending[group] = 0u;
	return E_OK;
}

/* ============================ [ 组表 ] ============================ */

const AdcSampler_GroupCfgType AdcSampler_GroupCfgs[HOST_ADC_GROUPS] = {
	{ 0u, 2u },
	{ 1u, 1u }
};

const uint8 AdcSampler_GroupCount = HOST_ADC_GROUPS;

const AdcSampler_HwOpsType AdcSampler_HwOps = {
	hostadc_Start,
	hostadc_Completed,
	hostadc_Read
};
