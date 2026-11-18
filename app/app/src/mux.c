/**
 * @file    mux.c
 * @brief   MuxManager Core：共享 A/B/C 的非阻塞扫描状态机
 *
 * @details @section MUX_C_WHY 本文件不知道引脚
 *
 *          所有硬件动作经 `Mux_HwOps`（Target 用 Dio/Adc，Host 用模拟）。
 *          本文件在 Target 与 Host 上编的是**同一份源码**，所以 Host 用例
 *          证明的是真实状态机，不是替身。
 *
 *          @section MUX_C_SEQ 扫描顺序
 *
 *          ABC 从 0 到 7 逐个推进，一个 ABC 值下所有设备的 Y 通道同时取样：
 *
 *          @code
 *          ABC=000 → dev0.GPIO 读 Y0  ┐
 *                    dev1.ADC  启 Y0  ├─ 同一选择周期
 *                    dev2.GPIO 读 Y0  ┘
 *          等 dev1 ADC 完成（或超时）后才允许 ABC=001
 *          @endcode
 *
 *          这条约束是硬性的：ADC 转换期间切 ABC，采到的就是别的通道的电压。
 *
 *          @section MUX_C_BOUND 有界执行
 *
 *          `Mux_MainFunction()` 最多推进 `MUX_STEPS_PER_TICK` 步，遇到
 *          "要等"（建立时间/ADC 未完成）立刻返回。所以它不会在 10 ms
 *          节拍里死等，也不会因为一拍里扫完全部 ABC 而超时。
 *
 *          @section MUX_C_FAIL 失败语义
 *
 *          - GPIO 读失败：本通道不发布，`seq` 不变 → 上层自然转 STALE；
 *          - ADC 启动失败：该设备本 ABC 跳过（不发布）；
 *          - ADC 超时：累计 `Mux_GetAdcTimeouts()`，丢弃本拍样本后继续扫描
 *            —— **不能让一片坏器件卡死整条扫描链**。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：状态机 + 共享 ABC 调度 + 样本发布/超时 |
 */

#include "mux.h"

/** @brief 数组尺寸兜底：计数为 0 时退化成 1，避免零长数组 */
#define MUX_DIM(n)      (((n) == 0u) ? 1u : (n))
/** @brief 有效设备数（防御：生成的计数超过上限时截断，避免越界） */
#define MUX_NDEV()      ((Mux_DeviceCount > MUX_DEV_MAX) ? MUX_DEV_MAX : Mux_DeviceCount)
#define MUX_NBUS()      ((Mux_BusCount > MUX_BUS_MAX) ? MUX_BUS_MAX : Mux_BusCount)

/* ============================ [ 样本与状态 ] ============================ */

/** @brief 一个已发布样本 */
typedef struct {
	uint16 value;   /**< 电气电平（DIN）或原始 ADC 值（AIN） */
	uint16 seq;     /**< 发布序号，每发布一次 +1（允许回绕） */
	uint8  valid;   /**< 是否至少发布过一次 */
} Mux_SampleType;

static Mux_SampleType s_din[MUX_DEV_MAX][MUX_Y_MAX];
static Mux_SampleType s_ain[MUX_DEV_MAX][MUX_Y_MAX];

static Mux_StateType s_state = MUX_STATE_IDLE;
static uint8  s_abc;              /**< 当前 ABC 值（0..7） */
static uint8  s_busMask;          /**< 所有总线 scanMask 的并集 */
static uint8  s_settleLeft;       /**< 剩余建立等待拍数 */
static uint8  s_adcLeft;          /**< ADC 剩余等待拍数 */
static uint8  s_adcTimeout;       /**< ADC 超时拍数（取各总线最大值） */
static uint8  s_pending;          /**< 等待 ADC 的设备位图 */
static uint8  s_inited;
static uint32 s_rounds;           /**< 完成的扫描轮数 */
static uint32 s_adcTimeouts;      /**< ADC 超时累计 */

/* ============================ [ 内部工具 ] ============================ */

/**
 * @brief 把 ABC 写到**所有**需要该值的总线
 * @param[in] abc 选择值（bit0/1/2 = A/B/C）
 * @note  同一 ABC 值可同时作用于多条总线：它们各自有独立的 A/B/C 引脚，
 *        互不干扰，这样两条总线的扫描是并行而不是串行的。
 */
static void mux_SelectAll(uint8 abc)
{
	uint8 i;

	if (Mux_HwOps.SelectWrite == NULL) {
		return;
	}
	for (i = 0u; i < MUX_NBUS(); i++) {
		if ((Mux_BusCfgs[i].scanMask & (uint8)(1u << abc)) != 0u) {
			Mux_HwOps.SelectWrite(i, abc);
		}
	}
}

/** @brief 该设备在当前 ABC 上是否有通道 */
static uint8 mux_DevActive(uint8 dev, uint8 abc)
{
	const Mux_DeviceCfgType *cfg;

	cfg = &Mux_DeviceCfgs[dev];
	if (cfg->activeMask == 0u) {
		return 0u;
	}
	if ((cfg->activeMask & (uint8)(1u << abc)) == 0u) {
		return 0u;
	}
	return 1u;
}

/** @brief 发布一个 DIN 样本 */
static void mux_PublishDin(uint8 dev, uint8 y, boolean level)
{
	s_din[dev][y].value = (level != FALSE) ? 1u : 0u;
	s_din[dev][y].seq++;
	s_din[dev][y].valid = 1u;
}

/** @brief 发布一个 AIN 样本 */
static void mux_PublishAin(uint8 dev, uint8 y, uint16 raw)
{
	s_ain[dev][y].value = raw;
	s_ain[dev][y].seq++;
	s_ain[dev][y].valid = 1u;
}

/**
 * @brief START 阶段：GPIO 立即读，ADC 启动转换
 * @param[in] abc 当前选择值
 */
static void mux_StartPhase(uint8 abc)
{
	uint8 dev;
	const Mux_DeviceCfgType *cfg;
	boolean level;

	s_pending = 0u;
	for (dev = 0u; dev < MUX_NDEV(); dev++) {
		if (mux_DevActive(dev, abc) == 0u) {
			continue;
		}
		cfg = &Mux_DeviceCfgs[dev];
		if (cfg->comType == (uint8)MUX_COM_GPIO) {
			if ((Mux_HwOps.GpioRead != NULL) &&
			    (Mux_HwOps.GpioRead(cfg->comChannel, &level) == E_OK)) {
				mux_PublishDin(dev, abc, level);
			}
			/* 读失败：不发布，seq 不变 → 上层转 STALE */
		} else if (cfg->comType == (uint8)MUX_COM_ADC) {
			if ((Mux_HwOps.AdcStart != NULL) &&
			    (Mux_HwOps.AdcStart(cfg->comChannel) == E_OK)) {
				s_pending |= (uint8)(1u << dev);
			}
			/* 启动失败：本 ABC 该设备不采样 */
		} else {
			/* 非法 comType：配置错误，跳过（生成器应拦住） */
		}
	}
}

/**
 * @brief WAIT_SAMPLE 阶段：查询已完成的转换并发布
 * @return 1 = 已全部完成（可推进）；0 = 仍在等
 */
static uint8 mux_PollPhase(uint8 abc)
{
	uint8 dev;
	boolean ready;
	uint16 raw;
	const Mux_DeviceCfgType *cfg;

	for (dev = 0u; dev < MUX_NDEV(); dev++) {
		if ((s_pending & (uint8)(1u << dev)) == 0u) {
			continue;
		}
		cfg = &Mux_DeviceCfgs[dev];
		ready = FALSE;
		if ((Mux_HwOps.AdcReady != NULL) &&
		    (Mux_HwOps.AdcReady(cfg->comChannel, &ready) != E_OK)) {
			ready = FALSE;
		}
		if (ready != FALSE) {
			if ((Mux_HwOps.AdcRead != NULL) &&
			    (Mux_HwOps.AdcRead(cfg->comChannel, &raw) == E_OK)) {
				mux_PublishAin(dev, abc, raw);
			}
			s_pending &= (uint8)~(uint8)(1u << dev);
		}
	}

	if (s_pending == 0u) {
		return 1u;
	}

	/* 还有设备没转换完 */
	if (s_adcLeft == 0u) {
		/* 超时：丢弃这些设备的本拍样本，继续扫描（不卡死整条链） */
		s_adcTimeouts++;
		s_pending = 0u;
		return 1u;
	}
	s_adcLeft--;
	return 0u;
}

/**
 * @brief 找第一个需要扫描的 ABC
 * @return 0..7；没有可扫描通道返回 0xFF
 * @note  与 mux_NextAbc() 的区别：本函数**包含 0**。初始化必须用它 ——
 *        用"取下一个"会把 ABC0 整轮跳过（V1.1.0 首版就是这个错）。
 */
static uint8 mux_FirstAbc(void)
{
	uint8 abc;

	for (abc = 0u; abc < MUX_Y_MAX; abc++) {
		if ((s_busMask & (uint8)(1u << abc)) != 0u) {
			return abc;
		}
	}
	return 0xFFu;
}

/**
 * @brief 找下一个需要扫描的 ABC
 * @param[in] from 当前值
 * @return 下一个值；找不到返回 0xFF
 */
static uint8 mux_NextAbc(uint8 from)
{
	uint8 n;

	for (n = 1u; n <= 8u; n++) {
		uint8 candidate = (uint8)((from + n) & 0x07u);

		if ((s_busMask & (uint8)(1u << candidate)) != 0u) {
			return candidate;
		}
	}
	return 0xFFu;
}

/**
 * @brief 推进一步
 * @return 1 = 有进展（可在本拍内继续）；0 = 在等（本拍结束）
 */
static uint8 mux_Step(void)
{
	switch (s_state) {
	case MUX_STATE_SET_SELECT:
		mux_SelectAll(s_abc);
		{
			uint8 i;
			uint8 s = 0u;

			/* 取所有总线里最大的建立时间，保证每条总线都稳 */
			for (i = 0u; i < MUX_NBUS(); i++) {
				if (Mux_BusCfgs[i].settleTicks > s) {
					s = Mux_BusCfgs[i].settleTicks;
				}
			}
			if (s > 0u) {
				s_settleLeft = s;
				s_state = MUX_STATE_WAIT_SETTLE;
				return 0u;
			}
		}
		s_state = MUX_STATE_START;
		return 1u;

	case MUX_STATE_WAIT_SETTLE:
		if (s_settleLeft > 1u) {
			s_settleLeft--;
			return 0u;
		}
		s_state = MUX_STATE_START;
		return 1u;

	case MUX_STATE_START:
		mux_StartPhase(s_abc);
		if (s_pending == 0u) {
			s_state = MUX_STATE_ADVANCE;
			return 1u;
		}
		s_adcLeft = s_adcTimeout;
		s_state = MUX_STATE_WAIT_SAMPLE;
		return 1u;

	case MUX_STATE_WAIT_SAMPLE:
		if (mux_PollPhase(s_abc) != 0u) {
			s_state = MUX_STATE_ADVANCE;
			return 1u;
		}
		return 0u;

	case MUX_STATE_ADVANCE:
		{
			uint8 next = mux_NextAbc(s_abc);

			if (next == 0xFFu) {
				s_state = MUX_STATE_IDLE;
				return 0u;
			}
			if (next <= s_abc) {
				s_rounds++;   /* ABC 回绕 = 扫完一轮 */
			}
			s_abc = next;
			s_state = MUX_STATE_SET_SELECT;
			return 1u;
		}

	case MUX_STATE_IDLE:
	default:
		return 0u;
	}
}

/* ============================ [ API ] ============================ */

void Mux_Init(void)
{
	uint8 dev;
	uint8 i;
	uint8 y;

	for (dev = 0u; dev < MUX_DEV_MAX; dev++) {
		for (y = 0u; y < MUX_Y_MAX; y++) {
			s_din[dev][y].value = 0u;
			s_din[dev][y].seq = 0u;
			s_din[dev][y].valid = 0u;
			s_ain[dev][y].value = 0u;
			s_ain[dev][y].seq = 0u;
			s_ain[dev][y].valid = 0u;
		}
	}

	s_busMask = 0u;
	s_adcTimeout = 1u;
	for (i = 0u; i < MUX_NBUS(); i++) {
		s_busMask |= Mux_BusCfgs[i].scanMask;
		if (Mux_BusCfgs[i].adcTimeoutTicks > s_adcTimeout) {
			s_adcTimeout = Mux_BusCfgs[i].adcTimeoutTicks;
		}
	}

	s_abc = 0u;
	s_settleLeft = 0u;
	s_adcLeft = 0u;
	s_pending = 0u;
	s_rounds = 0u;
	s_adcTimeouts = 0u;
	s_inited = 1u;

	/* INH 静态使能：只在 Init 写一次，扫描过程中不再动 */
	if (Mux_HwOps.InhWrite != NULL) {
		for (dev = 0u; dev < MUX_NDEV(); dev++) {
			if (Mux_DeviceCfgs[dev].inhChannel != MUX_NO_CHANNEL) {
				Mux_HwOps.InhWrite(Mux_DeviceCfgs[dev].inhChannel,
				                   Mux_DeviceCfgs[dev].inhActiveLevel);
			}
		}
	}

	if (s_busMask == 0u) {
		s_state = MUX_STATE_IDLE;
		return;
	}
	s_abc = mux_FirstAbc();
	if (s_abc == 0xFFu) {
		s_state = MUX_STATE_IDLE;
		return;
	}
	s_state = MUX_STATE_SET_SELECT;
}

void Mux_MainFunction(void)
{
	uint8 steps = 0u;
	uint32 rounds0;

	if ((s_inited == 0u) || (s_state == MUX_STATE_IDLE)) {
		return;
	}
	rounds0 = s_rounds;
	while (steps < MUX_STEPS_PER_TICK) {
		if (mux_Step() == 0u) {
			break;      /* 在等：本拍结束，不空转 */
		}
		steps++;
		if (s_rounds != rounds0) {
			break;      /* 一拍最多扫完一轮，避免纯 GPIO 场景空转 */
		}
	}
}

Std_ReturnType Mux_GetDin(uint8 dev, uint8 y, boolean *level, uint16 *seq)
{
	if ((level == NULL) || (seq == NULL) ||
	    (dev >= MUX_NDEV()) || (y >= MUX_Y_MAX)) {
		return E_NOT_OK;
	}
	if ((Mux_DeviceCfgs[dev].activeMask & (uint8)(1u << y)) == 0u) {
		return E_NOT_OK;
	}
	if (Mux_DeviceCfgs[dev].comType != (uint8)MUX_COM_GPIO) {
		return E_NOT_OK;
	}
	if (s_din[dev][y].valid == 0u) {
		return E_NOT_OK;    /* 还没采到：不要给 0 充数 */
	}
	*level = (s_din[dev][y].value != 0u) ? TRUE : FALSE;
	*seq = s_din[dev][y].seq;
	return E_OK;
}

Std_ReturnType Mux_GetAin(uint8 dev, uint8 y, uint16 *raw, uint16 *seq)
{
	if ((raw == NULL) || (seq == NULL) ||
	    (dev >= MUX_NDEV()) || (y >= MUX_Y_MAX)) {
		return E_NOT_OK;
	}
	if ((Mux_DeviceCfgs[dev].activeMask & (uint8)(1u << y)) == 0u) {
		return E_NOT_OK;
	}
	if (Mux_DeviceCfgs[dev].comType != (uint8)MUX_COM_ADC) {
		return E_NOT_OK;
	}
	if (s_ain[dev][y].valid == 0u) {
		return E_NOT_OK;
	}
	*raw = s_ain[dev][y].value;
	*seq = s_ain[dev][y].seq;
	return E_OK;
}

Mux_StateType Mux_GetState(void)
{
	return s_state;
}

uint8 Mux_GetAbc(void)
{
	return s_abc;
}

uint32 Mux_GetScanRounds(void)
{
	return s_rounds;
}

uint32 Mux_GetAdcTimeouts(void)
{
	return s_adcTimeouts;
}
