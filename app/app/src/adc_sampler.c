/**
 * @file    adc_sampler.c
 * @brief   AdcSampler 核心：按组轮转的采样调度
 *
 * @details @section ADCS_C_WHY 与硬件无关
 *
 *          所有硬件动作经 `AdcSampler_HwOps`；Target 与 Host 编**同一份源码**。
 *          这样"完成才发布""超时丢弃""槽位一一对应"这些规则可以在 Host 上
 *          用可控的转换延迟验证，而不是靠上板猜。
 *
 *          @section ADCS_C_SEQ 时序
 *
 *          @code
 *          第 N 拍    : Start(group)              → pending
 *          第 N+1 拍  : Completed? 是 → Read + 发布；否 → 继续等/超时
 *          @endcode
 *
 *          每拍只做一次"启动"或"查询"，不做忙等。转换在微秒级完成，
 *          所以正常情况下每个通道每 2 拍（20 ms）出一个新样本。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：组轮转 + 完成发布 + 超时 |
 */

#include "adc_sampler.h"

/** @brief 有效组数（防御：生成的计数超限时截断） */
#define ADCS_NGROUP()   ((AdcSampler_GroupCount > ADC_SAMPLER_GROUP_MAX) \
                         ? ADC_SAMPLER_GROUP_MAX : AdcSampler_GroupCount)

/** @brief 每组运行状态 */
typedef struct {
	uint8 pending;   /**< 已启动、等结果 */
	uint8 left;      /**< 剩余等待拍数 */
} AdcSampler_CtxType;

static AdcSampler_CtxType s_ctx[ADC_SAMPLER_GROUP_MAX];
static uint16 s_buf[ADC_SAMPLER_GROUP_MAX][ADC_SAMPLER_CH_MAX];
static uint16 s_seq[ADC_SAMPLER_GROUP_MAX][ADC_SAMPLER_CH_MAX];
static uint8  s_valid[ADC_SAMPLER_GROUP_MAX][ADC_SAMPLER_CH_MAX];
static uint32 s_timeouts;

void AdcSampler_Init(void)
{
	uint8 i;
	uint8 k;

	for (i = 0u; i < ADC_SAMPLER_GROUP_MAX; i++) {
		s_ctx[i].pending = 0u;
		s_ctx[i].left = 0u;
		for (k = 0u; k < ADC_SAMPLER_CH_MAX; k++) {
			s_buf[i][k] = 0u;
			s_seq[i][k] = 0u;
			s_valid[i][k] = 0u;
		}
	}
	s_timeouts = 0u;
}

void AdcSampler_MainFunction(void)
{
	uint8 i;
	uint8 n;
	uint8 k;
	const AdcSampler_GroupCfgType *cfg;
	boolean done;

	n = ADCS_NGROUP();
	for (i = 0u; i < n; i++) {
		cfg = &AdcSampler_GroupCfgs[i];
		if ((cfg->group == 0xFFu) || (cfg->numChannels == 0u)) {
			continue;
		}
		/* 槽位数超过缓冲上限：截断，避免越界写（生成器应拦住） */
		if (cfg->numChannels > ADC_SAMPLER_CH_MAX) {
			continue;
		}

		if (s_ctx[i].pending == 0u) {
			if ((AdcSampler_HwOps.Start != NULL) &&
			    (AdcSampler_HwOps.Start(cfg->group) == E_OK)) {
				s_ctx[i].pending = 1u;
				s_ctx[i].left = ADC_SAMPLER_TIMEOUT_TICKS;
			}
			continue;
		}

		done = FALSE;
		if ((AdcSampler_HwOps.Completed != NULL) &&
		    (AdcSampler_HwOps.Completed(cfg->group, &done) == E_OK) &&
		    (done != FALSE)) {
			if ((AdcSampler_HwOps.Read != NULL) &&
			    (AdcSampler_HwOps.Read(cfg->group, s_buf[i],
			                           cfg->numChannels) == E_OK)) {
				for (k = 0u; k < cfg->numChannels; k++) {
					s_seq[i][k]++;
					s_valid[i][k] = 1u;
				}
			}
			/* 读失败：不发布，seq 不变 → 上层转 STALE */
			s_ctx[i].pending = 0u;
			continue;
		}

		if (s_ctx[i].left == 0u) {
			/* 超时：放弃本轮，下一拍重新启动 */
			s_timeouts++;
			s_ctx[i].pending = 0u;
		} else {
			s_ctx[i].left--;
		}
	}
}

Std_ReturnType AdcSampler_GetRaw(uint8 group, uint8 slot, uint16 *raw,
                                 uint16 *seq)
{
	uint8 i;
	uint8 n;

	if ((raw == NULL) || (seq == NULL)) {
		return E_NOT_OK;
	}
	n = ADCS_NGROUP();
	for (i = 0u; i < n; i++) {
		if (AdcSampler_GroupCfgs[i].group != group) {
			continue;
		}
		if (slot >= AdcSampler_GroupCfgs[i].numChannels) {
			return E_NOT_OK;
		}
		if (s_valid[i][slot] == 0u) {
			return E_NOT_OK;    /* 还没采到：不给 0 充数 */
		}
		*raw = s_buf[i][slot];
		*seq = s_seq[i][slot];
		return E_OK;
	}
	return E_NOT_OK;
}

uint32 AdcSampler_GetTimeouts(void)
{
	return s_timeouts;
}
