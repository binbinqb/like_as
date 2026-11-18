/**
 * @file    iohwab.c
 * @brief   IoHwAb Core：逻辑通道、消抖、滤波、极性、安全状态
 *
 * @details @section IOHWAB_C_LAYER 本文件不知道硬件
 *
 *          所有硬件动作都经生成表里的能力 ops 指针（`IoHwAb_*Ops`）。
 *          Target 与 Host 各提供一份实现，**本文件源码两边完全一致**：
 *          Host 测试证明逻辑，不需要任何目标板。
 *
 *          @section IOHWAB_C_DEBOUNCE 消抖
 *          按 10 ms 节拍计数：连续 N 个**新样本**读到同一逻辑值才提交。
 *          上电初期状态为 `NEVER`，应用必须据此判"还没稳定"，不能当 LOW 用。
 *
 *          @section IOHWAB_C_FRESH 样本新鲜度
 *          后端返回的 `seq` 是"是否新样本"的唯一判据：
 *          - `seq` 变化 → 推进消抖/滤波；
 *          - `seq` 不变 → 不重复处理旧值，累计 `sameSeqTicks`，
 *            超过表项 `staleTicks` 判 `STALE`。
 *          这样 MUX / I2C 扩展器不用被逼着每 10 ms 出数据。
 *
 *          @section IOHWAB_C_FILTER 滤波与超时
 *          一阶滤波：`filt += (raw - filt) >> shift`，
 *          右移改用 `iohwab_Shr()` 显式朝零舍入 —— 有符号右移在负值上
 *          是实现定义行为，不能依赖编译器。
 *          读取失败按拍累计：达到 `staleTicks` 判 `STALE`，两倍判 `ERROR`。
 *
 * @author  binbina
 * @version V1.0.1
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：DIN 消抖 / AIN 滤波与定点换算 / DOUT 安全状态 / PWM 限幅 |
 * | V1.0.1 | 2026-11-18 | binbina | 极性归属 Core；按 seq 推进消抖/滤波；Init 运行期守卫 + ReInit；物理量饱和；SetAllSafe 返回结果 |
 */

#include "iohwab.h"
#include "IoHwAb_Cfg.h"   /* 通道枚举与计数宏（Board.json 生成） */

/** @brief 数组尺寸：通道数为 0 时退化成 1，避免零长数组 */
#define IOHWAB_DIM(n)   (((n) == 0u) ? 1u : (n))

/* ============================ [ 运行期上下文 ] ============================ */

/** @brief DIN 上下文 */
typedef struct {
	uint8 stable;              /**< 已提交的逻辑值 */
	uint8 candidate;           /**< 当前候选逻辑值 */
	uint8 hasSample;           /**< 是否已收到过样本 */
	uint8 hasCommitted;        /**< 是否已提交过有效值（决定能否进 STALE） */
	uint16 count;              /**< 连续相同的新样本数 */
	uint16 lastSeq;            /**< 上一次处理的样本序号 */
	uint16 sameSeqTicks;       /**< 连续多少拍 seq 未变 */
	IoHwAb_StatusType status;  /**< 当前状态 */
} IoHwAb_DinCtxType;

/** @brief AIN 上下文 */
typedef struct {
	sint32 filt;               /**< 滤波后的原始值 */
	uint16 failCount;          /**< 连续读取失败拍数 */
	uint16 lastSeq;            /**< 上一次处理的样本序号 */
	uint16 sameSeqTicks;       /**< 连续多少拍 seq 未变 */
	uint8 hasSample;           /**< 是否已收到过样本 */
	IoHwAb_StatusType status;  /**< 当前状态 */
} IoHwAb_AinCtxType;

/** @brief DOUT 上下文 */
typedef struct {
	uint8 logical;             /**< 最近一次成功写入的逻辑值 */
	uint8 faulted;             /**< 最近一次写入是否失败（含从未成功） */
} IoHwAb_DoutCtxType;

static IoHwAb_DinCtxType  s_din[IOHWAB_DIM(IOHWAB_DIN_COUNT)];
static IoHwAb_AinCtxType  s_ain[IOHWAB_DIM(IOHWAB_AIN_COUNT)];
static IoHwAb_DoutCtxType s_dout[IOHWAB_DIM(IOHWAB_DOUT_COUNT)];

/** @brief 是否已首次初始化（运行期重复 Init 的守卫） */
static boolean s_initialized = FALSE;

/* ============================ [ 内部工具 ] ============================ */

/**
 * @brief 逻辑值 → 电气电平（**极性唯一转换点**）
 * @param[in] activeLevel 1 = 高有效，0 = 低有效
 * @param[in] on          逻辑值
 * @return 电气电平（1 = 高）
 * @note  能力 Adapter 收到的已经是电气电平，**不允许再按极性取反**。
 */
static uint8 iohwab_ApplyPolarity(uint8 activeLevel, uint8 on)
{
	return (on != 0u) ? activeLevel : (uint8)(activeLevel ^ 1u);
}

/**
 * @brief 电气电平 → 逻辑值（**极性唯一转换点**）
 * @param[in] activeLevel 1 = 高有效，0 = 低有效
 * @param[in] level       电气电平
 * @return 逻辑值
 */
static uint8 iohwab_RemovePolarity(uint8 activeLevel, uint8 level)
{
	return (level == activeLevel) ? 1u : 0u;
}

/**
 * @brief 有符号右移，朝零舍入
 * @param[in] v     被移位数（本文件里的差值范围远小于 INT32_MIN，取负安全）
 * @param[in] shift 移位数（1..8，生成器已校验）
 * @return v / 2^shift，向零取整
 * @note  C 语言对负值的有符号右移是**实现定义**行为，这里显式拆成正负两支，
 *        保证 Host（MSVC/MinGW）与 Target（arm-none-eabi-gcc）结果一致。
 */
static sint32 iohwab_Shr(sint32 v, uint8 shift)
{
	if (v >= 0) {
		return (sint32)(v >> shift);
	}
	return (sint32)(-((-v) >> shift));
}

/**
 * @brief int64 → sint32 饱和转换
 * @param[in] v 64 位中间量
 * @return 饱和到 INT32_MIN..INT32_MAX 的 sint32
 */
static sint32 iohwab_SatS32(int64_t v)
{
	if (v > (int64_t)INT32_MAX) {
		return INT32_MAX;
	}
	if (v < (int64_t)INT32_MIN) {
		return INT32_MIN;
	}
	return (sint32)v;
}

/**
 * @brief 清空所有运行期上下文（不碰硬件）
 */
static void iohwab_ClearState(void)
{
	uint16 i;

	for (i = 0u; i < IOHWAB_DIM(IOHWAB_DIN_COUNT); i++) {
		s_din[i].stable = 0u;
		s_din[i].candidate = 0u;
		s_din[i].hasSample = 0u;
		s_din[i].hasCommitted = 0u;
		s_din[i].count = 0u;
		s_din[i].lastSeq = 0u;
		s_din[i].sameSeqTicks = 0u;
		s_din[i].status = IOHWAB_STATUS_NEVER;
	}

	for (i = 0u; i < IOHWAB_DIM(IOHWAB_AIN_COUNT); i++) {
		s_ain[i].filt = 0;
		s_ain[i].failCount = 0u;
		s_ain[i].lastSeq = 0u;
		s_ain[i].sameSeqTicks = 0u;
		s_ain[i].hasSample = 0u;
		s_ain[i].status = IOHWAB_STATUS_NEVER;
	}

	for (i = 0u; i < IOHWAB_DIM(IOHWAB_DOUT_COUNT); i++) {
		s_dout[i].logical = 0u;
		s_dout[i].faulted = 0u;
	}
}

/**
 * @brief 写一个 DOUT（含越界与空指针保护，并记录故障标志）
 * @param[in] id      逻辑通道
 * @param[in] logical 逻辑值
 * @return E_OK / E_NOT_OK
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
		/* 本构建不适用（Host 上的 GPIO 桩 / Target 上的 Host 桩）：
		 * 明确失败，但**不置故障位** —— 不适用不是"坏了"。 */
		return E_NOT_OK;
	}
	if (cfg->ops->Write(cfg->channel,
	                    iohwab_ApplyPolarity(cfg->activeLevel, logical)) != E_OK) {
		s_dout[id].faulted = 1u;
		return E_NOT_OK;
	}
	s_dout[id].logical = logical;
	s_dout[id].faulted = 0u;
	return E_OK;
#else
	(void)id;
	(void)logical;
	return E_NOT_OK;
#endif
}

/* ============================ [ API：生命周期 ] ============================ */

boolean IoHwAb_IsInitialized(void)
{
	return s_initialized;
}

Std_ReturnType IoHwAb_Init(void)
{
	Std_ReturnType ret;

	if (s_initialized != FALSE) {
		/* 运行期重复调用：幂等，不清状态、不动输出。
		 * V1.0.0 在这里会把负载拉回安全值 —— 车辆运行中重复调用等于关灯。 */
		return E_OK;
	}

	iohwab_ClearState();
	ret = IoHwAb_SetAllSafe();
	s_initialized = TRUE;
	return ret;
}

Std_ReturnType IoHwAb_ReInit(void)
{
	Std_ReturnType ret;

	iohwab_ClearState();
	ret = IoHwAb_SetAllSafe();
	s_initialized = TRUE;
	return ret;
}

void IoHwAb_MainFunction(void)
{
#if IOHWAB_DIN_COUNT > 0
	uint16 i;
	const IoHwAb_DinCfgType *cfg;
	boolean level;
	uint16 seq;
	uint8 logical;

	for (i = 0u; i < IOHWAB_DIN_COUNT; i++) {
		cfg = &IoHwAb_DinCfgs[i];
		if ((cfg->ops == NULL) || (cfg->ops->Read == NULL)) {
			s_din[i].status = IOHWAB_STATUS_ERROR;
			continue;
		}
		if (cfg->ops->Read(cfg->channel, &level, &seq) != E_OK) {
			/* 后端失败优先于任何超时判断 */
			s_din[i].status = IOHWAB_STATUS_ERROR;
			continue;
		}

		if ((s_din[i].hasSample == 0u) || (seq != s_din[i].lastSeq)) {
			/* 新样本：推进消抖 */
			s_din[i].hasSample = 1u;
			s_din[i].lastSeq = seq;
			s_din[i].sameSeqTicks = 0u;

			logical = iohwab_RemovePolarity(cfg->activeLevel, (uint8)level);
			if (logical != s_din[i].candidate) {
				s_din[i].candidate = logical;
				s_din[i].count = 1u;
			} else if (s_din[i].count < cfg->debounceTicks) {
				s_din[i].count++;
			} else {
				/* 计数已达阈值 */
			}

			if (s_din[i].count >= cfg->debounceTicks) {
				s_din[i].stable = s_din[i].candidate;
				s_din[i].hasCommitted = 1u;
				s_din[i].status = IOHWAB_STATUS_VALID;
			} else if (s_din[i].hasCommitted == 0u) {
				s_din[i].status = IOHWAB_STATUS_NEVER;
			} else {
				/* 曾经有有效值：在候选值稳定前继续沿用旧值 */
			}
		} else {
			/* 没有新样本：不重复消抖同一个旧值，只累计超时 */
			if (s_din[i].sameSeqTicks < 0xFFFFu) {
				s_din[i].sameSeqTicks++;
			}
			if ((s_din[i].hasCommitted != 0u) &&
			    (s_din[i].sameSeqTicks >= cfg->staleTicks) &&
			    (s_din[i].status != IOHWAB_STATUS_ERROR)) {
				s_din[i].status = IOHWAB_STATUS_STALE;
			}
		}
	}
#endif

#if IOHWAB_AIN_COUNT > 0
	{
		const IoHwAb_AinCfgType *acfg;
		uint16 raw;
		uint16 seq;
		uint16 j;

		for (j = 0u; j < IOHWAB_AIN_COUNT; j++) {
			acfg = &IoHwAb_AinCfgs[j];
			if ((acfg->ops == NULL) || (acfg->ops->ReadRaw == NULL)) {
				s_ain[j].status = IOHWAB_STATUS_ERROR;
				continue;
			}
			if (acfg->ops->ReadRaw(acfg->channel, &raw, &seq) != E_OK) {
				s_ain[j].failCount++;
				if (s_ain[j].failCount >= (uint16)(2u * acfg->staleTicks)) {
					s_ain[j].status = IOHWAB_STATUS_ERROR;
				} else if (s_ain[j].failCount >= acfg->staleTicks) {
					s_ain[j].status = IOHWAB_STATUS_STALE;
				}
				continue;
			}
			s_ain[j].failCount = 0u;

			if ((s_ain[j].hasSample == 0u) || (seq != s_ain[j].lastSeq)) {
				/* 新样本：推进滤波 */
				s_ain[j].hasSample = 1u;
				s_ain[j].lastSeq = seq;
				s_ain[j].sameSeqTicks = 0u;

				if (acfg->filterShift > 0u) {
					s_ain[j].filt += iohwab_Shr((sint32)raw - s_ain[j].filt,
					                            acfg->filterShift);
				} else {
					s_ain[j].filt = (sint32)raw;
				}
				s_ain[j].status = IOHWAB_STATUS_VALID;
			} else {
				/* 没有新样本：不重复滤波同一个旧值，只累计超时 */
				if (s_ain[j].sameSeqTicks < 0xFFFFu) {
					s_ain[j].sameSeqTicks++;
				}
				if ((s_ain[j].sameSeqTicks >= acfg->staleTicks) &&
				    (s_ain[j].status == IOHWAB_STATUS_VALID)) {
					s_ain[j].status = IOHWAB_STATUS_STALE;
				}
			}
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
	int64_t phys;

	if (value == NULL) {
		return E_NOT_OK;
	}
	ret = IoHwAb_AinReadRaw(id, &raw, status);
	if (ret != E_OK) {
		return ret;
	}
#if IOHWAB_AIN_COUNT > 0
	/* 定点：raw × factor / 1000 + offset。
	 * 用 int64 中间量：raw 最大 65535、factor 可达 sint32 量级，
	 * 直接用 sint32 相乘会溢出（UB 级错误，不是精度问题）。 */
	phys = ((int64_t)raw * (int64_t)IoHwAb_AinCfgs[id].factor) / 1000
	       + (int64_t)IoHwAb_AinCfgs[id].offset;
	*value = iohwab_SatS32(phys);
#else
	(void)raw;
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

Std_ReturnType IoHwAb_DoutGetFault(IoHwAb_DoutId id, boolean *faulted)
{
#if IOHWAB_DOUT_COUNT > 0
	if (((uint16)id >= IOHWAB_DOUT_COUNT) || (faulted == NULL)) {
		return E_NOT_OK;
	}
	*faulted = (s_dout[id].faulted != 0u) ? TRUE : FALSE;
	return E_OK;
#else
	(void)id;
	(void)faulted;
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

Std_ReturnType IoHwAb_SetAllSafe(void)
{
	Std_ReturnType ret = E_OK;

#if IOHWAB_DOUT_COUNT > 0
	uint16 i;
	const IoHwAb_DoutCfgType *cfg;

	for (i = 0u; i < IOHWAB_DOUT_COUNT; i++) {
		cfg = &IoHwAb_DoutCfgs[i];
		if ((cfg->ops == NULL) || (cfg->ops->Write == NULL)) {
			/* 本构建不适用：跳过，不计入失败 */
			continue;
		}
		if (iohwab_DoutApply((IoHwAb_DoutId)i,
		                     (uint8)cfg->safeLevel) != E_OK) {
			/* 不提前返回：一路失败不能阻止其余负载进安全状态 */
			ret = E_NOT_OK;
		}
	}
#endif
#if IOHWAB_PWM_COUNT > 0
	{
		uint16 i;
		const IoHwAb_PwmCfgType *pcfg;

		for (i = 0u; i < IOHWAB_PWM_COUNT; i++) {
			pcfg = &IoHwAb_PwmCfgs[i];
			if ((pcfg->ops == NULL) || (pcfg->ops->SetDuty == NULL)) {
				continue;   /* 本构建不适用 */
			}
			if (IoHwAb_PwmSetDuty((IoHwAb_PwmId)i,
			                      pcfg->safeDuty) != E_OK) {
				ret = E_NOT_OK;
			}
		}
	}
#endif
	return ret;
}
