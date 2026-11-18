/**
 * @file    iohwab.c
 * @brief   IoHwAb Core：逻辑通道、消抖、滤波、安全状态
 *
 * @details @section IOHWAB_C_LAYER 本文件不知道硬件
 *
 *          所有硬件动作都经生成表里的能力 ops 指针（`IoHwAb_*Ops`）。
 *          Target 与 Host 各提供一份实现，**本文件源码两边完全一致**：
 *          Host 测试证明逻辑，不需要任何目标板。
 *
 *          @section IOHWAB_C_DEBOUNCE 消抖
 *          按 10 ms 节拍计数：连续 N 拍读到同一逻辑值才提交。上电初期
 *          状态为 `NEVER`，应用必须据此判"还没稳定"，不能当 LOW 用。
 *
 *          @section IOHWAB_C_FILTER 滤波与超时
 *          一阶滤波：`filt += (raw - filt) >> shift`（sint32 中间量）。
 *          读取失败按拍累计：达到 `staleTicks` 判 `STALE`，两倍判 `ERROR`。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：DIN 消抖 / AIN 滤波与定点换算 / DOUT 安全状态 / PWM 限幅 |
 */

#include "iohwab.h"
#include "IoHwAb_Cfg.h"   /* 通道枚举与计数宏（Board.json 生成） */

/** @brief 数组尺寸：通道数为 0 时退化成 1，避免零长数组 */
#define IOHWAB_DIM(n)   (((n) == 0u) ? 1u : (n))

/* ============================ [ 运行期上下文 ] ============================ */

/** @brief DIN 上下文 */
typedef struct {
	uint8 stable;              /**< 已提交的逻辑值 */
	uint8 candidate;           /**< 本拍读到的逻辑值 */
	uint16 count;              /**< 连续相同拍数 */
	IoHwAb_StatusType status;  /**< 当前状态 */
} IoHwAb_DinCtxType;

/** @brief AIN 上下文 */
typedef struct {
	sint32 filt;               /**< 滤波后的原始值 */
	uint16 failCount;          /**< 连续读取失败拍数 */
	IoHwAb_StatusType status;  /**< 当前状态 */
} IoHwAb_AinCtxType;

/** @brief DOUT 上下文 */
typedef struct {
	uint8 logical;             /**< 最近一次成功写入的逻辑值 */
} IoHwAb_DoutCtxType;

static IoHwAb_DinCtxType  s_din[IOHWAB_DIM(IOHWAB_DIN_COUNT)];
static IoHwAb_AinCtxType  s_ain[IOHWAB_DIM(IOHWAB_AIN_COUNT)];
static IoHwAb_DoutCtxType s_dout[IOHWAB_DIM(IOHWAB_DOUT_COUNT)];

/* ============================ [ 内部工具 ] ============================ */

/**
 * @brief 逻辑值 → 电气电平（极性只在这里转换一次）
 * @param[in] cfg 表项
 * @param[in] on  逻辑值
 * @return 电气电平（1 = 高）
 */
static uint8 iohwab_ApplyPolarity(uint8 activeLevel, uint8 on)
{
	return (on != 0u) ? activeLevel : (uint8)(activeLevel ^ 1u);
}

/**
 * @brief 电气电平 → 逻辑值
 */
static uint8 iohwab_RemovePolarity(uint8 activeLevel, uint8 level)
{
	return (level == activeLevel) ? 1u : 0u;
}

/**
 * @brief 写一个 DOUT（含越界与空指针保护）
 */
static Std_ReturnType iohwab_DoutApply(IoHwAb_DoutId id, uint8 logical)
{
	const IoHwAb_DoutCfgType *cfg;

#if IOHWAB_DOUT_COUNT > 0
	if ((uint16)id >= IOHWAB_DOUT_COUNT) {
		return E_NOT_OK;
	}
	cfg = &IoHwAb_DoutCfgs[id];
	if ((cfg->ops == NULL) || (cfg->ops->Write == NULL)) {
		return E_NOT_OK;
	}
	if (cfg->ops->Write(cfg->channel,
	                    iohwab_ApplyPolarity(cfg->activeLevel, logical)) != E_OK) {
		return E_NOT_OK;
	}
	s_dout[id].logical = logical;
	return E_OK;
#else
	(void)id;
	(void)logical;
	return E_NOT_OK;
#endif
}

/* ============================ [ API：生命周期 ] ============================ */

void IoHwAb_Init(void)
{
	uint16 i;

	/* DIN：全部回到从未采样 */
	for (i = 0u; i < IOHWAB_DIM(IOHWAB_DIN_COUNT); i++) {
		s_din[i].stable = 0u;
		s_din[i].candidate = 0u;
		s_din[i].count = 0u;
		s_din[i].status = IOHWAB_STATUS_NEVER;
	}

	/* AIN：滤波初值 0，状态 NEVER */
	for (i = 0u; i < IOHWAB_DIM(IOHWAB_AIN_COUNT); i++) {
		s_ain[i].filt = 0;
		s_ain[i].failCount = 0u;
		s_ain[i].status = IOHWAB_STATUS_NEVER;
	}

	for (i = 0u; i < IOHWAB_DIM(IOHWAB_DOUT_COUNT); i++) {
		s_dout[i].logical = 0u;
	}

	/* 输出进入安全状态（Init 幂等，重复调用结果一致） */
	IoHwAb_SetAllSafe();
}

void IoHwAb_MainFunction(void)
{
#if IOHWAB_DIN_COUNT > 0
	uint16 i;
	const IoHwAb_DinCfgType *cfg;
	boolean level;
	uint8 logical;

	for (i = 0u; i < IOHWAB_DIN_COUNT; i++) {
		cfg = &IoHwAb_DinCfgs[i];
		if ((cfg->ops == NULL) || (cfg->ops->Read == NULL)) {
			s_din[i].status = IOHWAB_STATUS_ERROR;
			continue;
		}
		if (cfg->ops->Read(cfg->channel, &level) != E_OK) {
			s_din[i].status = IOHWAB_STATUS_ERROR;
			continue;
		}
		logical = iohwab_RemovePolarity(cfg->activeLevel, (uint8)level);
		if (logical != s_din[i].candidate) {
			s_din[i].candidate = logical;
			s_din[i].count = 1u;
		} else if (s_din[i].count < cfg->debounceTicks) {
			s_din[i].count++;
		} else {
			/* 计数已达阈值：提交 */
		}
		if (s_din[i].count >= cfg->debounceTicks) {
			s_din[i].stable = s_din[i].candidate;
			s_din[i].status = IOHWAB_STATUS_VALID;
		}
	}
#endif

#if IOHWAB_AIN_COUNT > 0
	{
		const IoHwAb_AinCfgType *acfg;
		uint16 raw;
		uint16 j;

		for (j = 0u; j < IOHWAB_AIN_COUNT; j++) {
			acfg = &IoHwAb_AinCfgs[j];
			if ((acfg->ops == NULL) || (acfg->ops->ReadRaw == NULL)) {
				s_ain[j].status = IOHWAB_STATUS_ERROR;
				continue;
			}
			if (acfg->ops->ReadRaw(acfg->channel, &raw) != E_OK) {
				s_ain[j].failCount++;
				if (s_ain[j].failCount >= (uint16)(2u * acfg->staleTicks)) {
					s_ain[j].status = IOHWAB_STATUS_ERROR;
				} else if (s_ain[j].failCount >= acfg->staleTicks) {
					s_ain[j].status = IOHWAB_STATUS_STALE;
				}
				continue;
			}
			s_ain[j].failCount = 0u;
			if (acfg->filterShift > 0u) {
				s_ain[j].filt += (sint32)(((sint32)raw - s_ain[j].filt)
				                          >> acfg->filterShift);
			} else {
				s_ain[j].filt = (sint32)raw;
			}
			s_ain[j].status = IOHWAB_STATUS_VALID;
		}
	}
#endif
}

/* ============================ [ API：输入 ] ============================ */

Std_ReturnType IoHwAb_DinRead(IoHwAb_DinId id, boolean *value,
                              IoHwAb_StatusType *status)
{
#if IOHWAB_DIN_COUNT > 0
	if (((uint16)id >= IOHWAB_DIN_COUNT) || (value == NULL)) {
		return E_NOT_OK;
	}
	*value = (boolean)s_din[id].stable;
	if (status != NULL) {
		*status = s_din[id].status;
	}
	return E_OK;
#else
	(void)id;
	(void)value;
	if (status != NULL) {
		*status = IOHWAB_STATUS_ERROR;
	}
	return E_NOT_OK;
#endif
}

Std_ReturnType IoHwAb_AinReadRaw(IoHwAb_AinId id, uint16 *value,
                                 IoHwAb_StatusType *status)
{
#if IOHWAB_AIN_COUNT > 0
	if (((uint16)id >= IOHWAB_AIN_COUNT) || (value == NULL)) {
		return E_NOT_OK;
	}
	if ((s_ain[id].status != IOHWAB_STATUS_VALID) &&
	    (s_ain[id].status != IOHWAB_STATUS_STALE)) {
		if (status != NULL) {
			*status = s_ain[id].status;
		}
		return E_NOT_OK;
	}
	*value = (uint16)s_ain[id].filt;
	if (status != NULL) {
		*status = s_ain[id].status;
	}
	return E_OK;
#else
	(void)id;
	(void)value;
	if (status != NULL) {
		*status = IOHWAB_STATUS_ERROR;
	}
	return E_NOT_OK;
#endif
}

Std_ReturnType IoHwAb_AinReadPhys(IoHwAb_AinId id, sint32 *value,
                                  IoHwAb_StatusType *status)
{
	uint16 raw;
	Std_ReturnType ret;

	if (value == NULL) {
		return E_NOT_OK;
	}
	ret = IoHwAb_AinReadRaw(id, &raw, status);
	if (ret != E_OK) {
		return ret;
	}
#if IOHWAB_AIN_COUNT > 0
	/* 定点：raw × factor / 1000 + offset，因子用 sint32 防溢 */
	*value = ((sint32)raw * IoHwAb_AinCfgs[id].factor) / 1000
	         + IoHwAb_AinCfgs[id].offset;
#endif
	return E_OK;
}

/* ============================ [ API：输出 ] ============================ */

Std_ReturnType IoHwAb_DoutWrite(IoHwAb_DoutId id, boolean on)
{
#if IOHWAB_DOUT_COUNT > 0
	return iohwab_DoutApply(id, (uint8)(on ? 1u : 0u));
#else
	(void)id;
	(void)on;
	return E_NOT_OK;
#endif
}

Std_ReturnType IoHwAb_DoutReadBack(IoHwAb_DoutId id, boolean *on)
{
#if IOHWAB_DOUT_COUNT > 0
	const IoHwAb_DoutCfgType *cfg;
	boolean level;

	if (((uint16)id >= IOHWAB_DOUT_COUNT) || (on == NULL)) {
		return E_NOT_OK;
	}
	cfg = &IoHwAb_DoutCfgs[id];
	if ((cfg->ops == NULL) || (cfg->ops->Read == NULL)) {
		/* 不支持回读：明确失败，不伪造 */
		return E_NOT_OK;
	}
	if (cfg->ops->Read(cfg->channel, &level) != E_OK) {
		return E_NOT_OK;
	}
	*on = (boolean)iohwab_RemovePolarity(cfg->activeLevel, (uint8)level);
	return E_OK;
#else
	(void)id;
	(void)on;
	return E_NOT_OK;
#endif
}

Std_ReturnType IoHwAb_PwmSetDuty(IoHwAb_PwmId id, uint16 duty)
{
#if IOHWAB_PWM_COUNT > 0
	const IoHwAb_PwmCfgType *cfg;

	if (((uint16)id >= IOHWAB_PWM_COUNT) || (duty > IOHWAB_PWM_FULL)) {
		return E_NOT_OK;
	}
	cfg = &IoHwAb_PwmCfgs[id];
	if ((cfg->ops == NULL) || (cfg->ops->SetDuty == NULL)) {
		return E_NOT_OK;
	}
	return cfg->ops->SetDuty(cfg->channel, duty);
#else
	(void)id;
	(void)duty;
	return E_NOT_OK;
#endif
}

void IoHwAb_SetAllSafe(void)
{
#if IOHWAB_DOUT_COUNT > 0
	uint16 i;

	for (i = 0u; i < IOHWAB_DOUT_COUNT; i++) {
		(void)iohwab_DoutApply((IoHwAb_DoutId)i, IoHwAb_DoutCfgs[i].safeLevel);
	}
#endif
#if IOHWAB_PWM_COUNT > 0
	{
		uint16 i;

		for (i = 0u; i < IOHWAB_PWM_COUNT; i++) {
			(void)IoHwAb_PwmSetDuty((IoHwAb_PwmId)i, IoHwAb_PwmCfgs[i].safeDuty);
		}
	}
#endif
}
