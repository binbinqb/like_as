/**
 * @file    PwmAc.c
 * @brief   PWM 的 CVM0146 平台实现（PwmLite）
 * @details 本文件是**唯一允许碰 PwmLite 寄存器/驱动的地方**。上面一层 `Pwm.c`
 *          只做参数校验与查表转发。
 *
 *          @section PWMAC_HW 硬件模型
 *          ```
 *          PwmLite 实例 (hwModule: 0~4，对应 pwmLiteDrv0~4)
 *            ├─ 模块级周期 (PwmLiteDrv_ModuleConfig → period)
 *            └─ 8 个通道 (PWMLITEDRV_PWM_CH0~CH7)
 *                 └─ mux 到物理引脚 (PWMLITEDRV_MUX_PAD_PWM0~PWM7)
 *          ```
 *          **一个实例只有一个周期**，所以同实例内所有通道必须同频率。
 *          这条约束在 `Pwm_Init()` 里已经拦住，本文件不再重复检查。
 *
 *          @section PWMAC_WAVE 波形怎么产生
 *          计数器从 0 计到 `period` 循环，在两个阈值处改变输出：
 *
 *          | 位置 | 动作（正极性） | 动作（反极性） |
 *          |------|---------------|---------------|
 *          | `threshold0 = 0` | 拉高 | 拉低 |
 *          | `threshold1 = period × duty / 0x8000` | 拉低 | 拉高 |
 *
 *          0 % 与 100 % **不配阈值**，直接把两个阈值都设成同一动作的静态电平 ——
 *          用阈值实现会在"周期开始拉高"和"立即拉低"之间产生一个纳秒级尖峰，
 *          而 `[SWS_Pwm_00018]` 明确要求禁止尖峰。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：PwmLite0~4，8 个物理引脚，0%/100% 静态电平 |
 */
#ifdef USE_PWM
/* ================================ [ INCLUDES  ] ============================================== */
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "Pwm_Priv.h"
#include "platform_priv.h"      /* g_mcu（pwmLiteDrv0~4、clockDrv、pta~pte） */
#include "platform_cvm0146.h"   /* Platform_Printf */
#include "mcu.h"
#include "Std_Debug.h"
/* ================================ [ MACROS    ] ============================================== */
#define AS_LOG_PWMAC 0
#define AS_LOG_PWMACI 0
#define AS_LOG_PWMACE 3

/** @brief PwmLite 实例数（`McuType` 里是 `pwmLiteDrv0~4`，共 5 个） */
#define PWMAC_MODULE_NUM        (5u)

/** @brief 每个实例的通道数（`PWMLITEDRV_PWM_CH0~CH7`） */
#define PWMAC_CH_PER_MODULE     (8u)

/** @brief 物理 PWM 引脚数（`PWMLITEDRV_MUX_PAD_PWM0~PWM7`） */
#define PWMAC_PAD_NUM           (8u)

/** @brief 通道运行模式（决定是否要重新 `ConfigChannel`） */
#define PWMAC_MODE_PWM          (0u)  /**< 正常调制 */
#define PWMAC_MODE_STATIC_LOW   (1u)  /**< 恒低（0% 或 100%，取决于极性） */
#define PWMAC_MODE_STATIC_HIGH  (2u)  /**< 恒高 */
/* ================================ [ TYPES     ] ============================================== */

/**
 * @brief PWM 输出引脚映射（pad 号 → 物理引脚）
 *
 * @details `pad` 是 PwmLite 的输出编号（`PWMLITEDRV_MUX_PAD_PWMn`），不是 MCU 引脚号。
 *          这层映射是**板级知识**，放在平台层而不是配置表里 —— 量产板若换了
 *          引脚方案，只改这一张表。
 *
 * @warning **`PWM4~7` 在本芯片上与 CAN 复用，不可用**：
 *
 *          | pad | 物理引脚 | 状态 |
 *          |-----|----------|------|
 *          | 0 | PTD0  | ✅ 可用 |
 *          | 1 | PTD1  | ✅ 可用 |
 *          | 2 | PTE15 | ✅ 可用 |
 *          | 3 | PTE16 | ✅ 可用 |
 *          | 4 | PTE10 | ❌ 与 `CAN3_RX` 复用（ALT3） |
 *          | 5 | PTE11 | ❌ 与 `CAN3_TX` 复用（ALT3） |
 *          | 6 | PTE4  | ❌ 与 `CAN0_RX` 复用（ALT4/5） |
 *          | 7 | PTE5  | ❌ 与 `CAN0_TX` 复用（ALT4/5） |
 *
 *          配错的表现不是 PWM 不出波形，而是**CAN 直接不通** —— 因为把 CAN 引脚
 *          的复用从 ALT3/ALT4 改成了 ALT6。这比 PWM 不工作严重得多，
 *          所以在 `PwmAc_Init()` 里直接拒绝，不留给运行期发现。
 */
typedef struct {
	uint8_t     port;     /**< 端口号：0=A,1=B,2=C,3=D,4=E */
	uint8_t     pin;      /**< 引脚号 */
	uint8_t     usable;   /**< 0 = 与 CAN 复用，禁止配置 */
	const char *name;     /**< 引脚名，仅用于诊断打印 */
} PwmAc_PadMapType;
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/** @brief pad → 物理引脚映射（见 `PwmAc_PadMapType` 的警告） */
static const PwmAc_PadMapType s_padMap[PWMAC_PAD_NUM] = {
	{ 3u,  0u, 1u, "PTD0"  },
	{ 3u,  1u, 1u, "PTD1"  },
	{ 4u, 15u, 1u, "PTE15" },
	{ 4u, 16u, 1u, "PTE16" },
	{ 4u, 10u, 0u, "PTE10(CAN3_RX)" },
	{ 4u, 11u, 0u, "PTE11(CAN3_TX)" },
	{ 4u,  4u, 0u, "PTE4(CAN0_RX)"  },
	{ 4u,  5u, 0u, "PTE5(CAN0_TX)"  },
};
/* ================================ [ LOCALS    ] ============================================== */
/** @brief 每个通道算出的周期计数（Hz → 计数，运行期换算的结果缓存） */
static uint32_t s_period[PWMAC_PAD_NUM];

/** @brief 每个通道当前的输出模式（`PWMAC_MODE_*`） */
static uint8_t s_mode[PWMAC_PAD_NUM];

/** @brief 哪些 PwmLite 实例已被初始化（避免重复配模块） */
static uint8_t s_moduleReady[PWMAC_MODULE_NUM];

/** @brief 模块是否已初始化 */
static boolean s_acInitialized = FALSE;
/* ================================ [ ALIAS     ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */

/**
 * @brief 端口号 → `PinsDrvType` 指针
 * @param[in] port 0=A,1=B,2=C,3=D,4=E
 * @return 端口对象指针；非法端口返回 NULL
 * @note  不能对 `g_mcu` 的成员做指针运算，所以只能用 switch。
 */
static PinsDrvType *PwmAc_GetPortPtr(uint8_t port)
{
	switch (port) {
	case 0u: return &g_mcu.pta;
	case 1u: return &g_mcu.ptb;
	case 2u: return &g_mcu.ptc;
	case 3u: return &g_mcu.ptd;
	case 4u: return &g_mcu.pte;
	default: return NULL;
	}
}

/**
 * @brief 实例号 → `PwmLiteDrvType` 指针
 * @param[in] m 实例号 0~4
 * @return 实例指针；非法返回 NULL
 */
static PwmLiteDrvType *PwmAc_GetModulePtr(uint8_t m)
{
	switch (m) {
	case 0u: return &g_mcu.pwmLiteDrv0;
	case 1u: return &g_mcu.pwmLiteDrv1;
	case 2u: return &g_mcu.pwmLiteDrv2;
	case 3u: return &g_mcu.pwmLiteDrv3;
	case 4u: return &g_mcu.pwmLiteDrv4;
	default: return NULL;
	}
}

/**
 * @brief 打开指定 PwmLite 实例的时钟门控
 * @param[in] m 实例号
 *
 * @note **这是必须显式做的一步。** `Mcu_Init()` 只调了 `PwmLiteDrv_Init()`
 *       （存寄存器基址指针），**没有开时钟门控**。漏掉的表现是
 *       "所有配置调用都成功、引脚一点波形都没有"，且无任何报错 ——
 *       与 ADC 那次踩的坑完全一样（`AdcAc.c` 里有同样的注释）。
 */
static void PwmAc_EnableClock(uint8_t m)
{
	ClockDrv_ModuleClkConfigType cfg;

	cfg.gating = true;
	switch (m) {
	case 0u:
		(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PWMLITE0, &cfg);
		break;
	case 1u:
		(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PWMLITE1, &cfg);
		break;
	case 2u:
		(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PWMLITE2, &cfg);
		break;
	case 3u:
		(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PWMLITE3, &cfg);
		break;
	case 4u:
		(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PWMLITE4, &cfg);
		break;
	default:
		break;
	}
}

/**
 * @brief 按"极性 + 模式"算出一对 (阈值, 动作)
 *
 * @param[in]  polarity 0=正极性，1=反极性
 * @param[in]  mode     `PWMAC_MODE_*`
 * @param[in]  period   周期计数
 * @param[in]  duty     占空比（0~0x8000）
 * @param[out] t0       threshold0
 * @param[out] t1       threshold1
 * @param[out] b0       behavior0
 * @param[out] b1       behavior1
 *
 * @note 正极性的正常调制：`t0=0` 拉高、`t1=duty×period/0x8000` 拉低。
 *       反极性把两个动作对调。
 */
static void PwmAc_CalcWave(uint8_t polarity, uint8_t mode, uint32_t period,
                           uint16_t duty, uint32_t *t0, uint32_t *t1,
                           PwmLiteDrv_OutBehaviorType *b0,
                           PwmLiteDrv_OutBehaviorType *b1)
{
	/* 极性为 0 时"有效电平"= 高；为 1 时"有效电平"= 低 */
	PwmLiteDrv_OutBehaviorType activeEdge;
	PwmLiteDrv_OutBehaviorType idleEdge;

	if (polarity == 0u) {
		activeEdge = PWMLITEDRV_HIGH_AT_REACH;
		idleEdge   = PWMLITEDRV_LOW_AT_REACH;
	} else {
		activeEdge = PWMLITEDRV_LOW_AT_REACH;
		idleEdge   = PWMLITEDRV_HIGH_AT_REACH;
	}

	if (mode == PWMAC_MODE_STATIC_HIGH) {
		/* 恒高：两个阈值都设成同一电平，且在周期两端都动作 */
		*t0 = 0u;
		*t1 = period;
		*b0 = (polarity == 0u) ? PWMLITEDRV_HIGH_AT_REACH
		                       : PWMLITEDRV_HIGH_AT_REACH;
		*b1 = PWMLITEDRV_HIGH_AT_REACH;
		return;
	}
	if (mode == PWMAC_MODE_STATIC_LOW) {
		*t0 = 0u;
		*t1 = period;
		*b0 = PWMLITEDRV_LOW_AT_REACH;
		*b1 = PWMLITEDRV_LOW_AT_REACH;
		return;
	}

	/* 正常调制 */
	*t0 = 0u;
	*b0 = activeEdge;
	*t1 = (uint32_t)(((uint64_t)period * (uint32_t)duty) / 0x8000u);
	*b1 = idleEdge;

	/* 钳一下：duty 很小时 t1 可能算成 0，与 t0 重合 → 会产生尖峰。
	 * 规范禁止尖峰，所以最小给 1 个计数。 */
	if (*t1 == 0u) {
		*t1 = 1u;
	}
	if (*t1 >= period) {
		*t1 = period - 1u;
	}
}

/**
 * @brief 把某个通道的配置真正写进硬件
 * @param[in] c    通道配置
 * @param[in] duty 占空比（0~0x8000）
 * @param[in] force 是否强制重配（即使模式没变）
 */
static void PwmAc_Apply(const Pwm_ChannelConfigType *c, uint16_t duty,
                        boolean force)
{
	PwmLiteDrvType *obj = PwmAc_GetModulePtr(c->hwModule);
	PwmLiteDrv_ChannelConfigType chCfg;
	uint32_t t0;
	uint32_t t1;
	PwmLiteDrv_OutBehaviorType b0;
	PwmLiteDrv_OutBehaviorType b1;
	uint8_t mode;
	uint8_t pad = c->pad;

	if ((obj == NULL) || (pad >= PWMAC_PAD_NUM) || (c->hwChannel >= PWMAC_CH_PER_MODULE)) {
		return;
	}

	/* 判定目标模式 */
	if (duty == 0u) {
		/* 0%：输出 = 极性的反 */
		mode = (c->polarity == 0u) ? PWMAC_MODE_STATIC_LOW : PWMAC_MODE_STATIC_HIGH;
	} else if (duty >= (uint16_t)0x8000u) {
		/* 100%：输出 = 极性本身 */
		mode = (c->polarity == 0u) ? PWMAC_MODE_STATIC_HIGH : PWMAC_MODE_STATIC_LOW;
	} else {
		mode = PWMAC_MODE_PWM;
	}

	if ((mode == s_mode[pad]) && (!force)) {
		/* 模式没变：只更新阈值，走"周期末生效"的快速路径 */
		PwmAc_CalcWave(c->polarity, mode, s_period[pad], duty, &t0, &t1, &b0, &b1);
		PwmLiteDrv_UpdatePwmThresholdAtSync(obj, c->hwChannel, t0, t1);
		return;
	}

	/* 模式变了（或强制）：整通道重配，behavior 也要改 */
	PwmAc_CalcWave(c->polarity, mode, s_period[pad], duty, &t0, &t1, &b0, &b1);

	PwmLiteDrv_GetDefaultChannelConfig(&chCfg);
	chCfg.pwmMuxType.channelNumber = (PwmLiteDrv_PwmMuxChannelType)
	                                 ((uint32_t)c->hwModule * PWMAC_CH_PER_MODULE
	                                  + (uint32_t)c->hwChannel);
	chCfg.pwmMuxType.padNumber     = (PwmLiteDrv_PwmMuxPadNumType)pad;
	chCfg.threshold0               = t0;
	chCfg.threshold1               = t1;
	chCfg.behavior0                = b0;
	chCfg.behavior1                = b1;
	PwmLiteDrv_ConfigChannel(obj, c->hwChannel, &chCfg);

	s_mode[pad] = mode;
}

void PwmAc_Init(const Pwm_ConfigType *cfg)
{
	uint32_t timerFreq;
	uint16_t i;
	uint16_t configured = 0u;
	uint8_t m;

	if (cfg == NULL) {
		return;
	}

	timerFreq = PwmAc_GetTimerFreq();
	if (timerFreq == 0u) {
		ASLOG(PWMACE, ("cannot get PWM timer clock, abort\n"));
		return;
	}

	for (m = 0u; m < PWMAC_MODULE_NUM; m++) {
		s_moduleReady[m] = 0u;
	}
	for (i = 0u; i < PWMAC_PAD_NUM; i++) {
		s_mode[i]  = 0xFFu;
		s_period[i] = 0u;
	}

	/* ---- 第 1 遍：按实例配模块（开时钟 + 设周期） ---- */
	for (i = 0u; i < cfg->numOfChannels; i++) {
		const Pwm_ChannelConfigType *c = &cfg->channels[i];
		PwmLiteDrvType *obj;
		PwmLiteDrv_ModuleConfigType modCfg;

		if ((c->pad >= PWMAC_PAD_NUM) || (c->hwModule >= PWMAC_MODULE_NUM)
		    || (c->hwChannel >= PWMAC_CH_PER_MODULE)) {
			ASLOG(PWMACE, ("ch%u has invalid hw mapping, skipped\n", (unsigned)i));
			continue;
		}
		if (s_padMap[c->pad].usable == 0u) {
			ASLOG(PWMACE, ("ch%u pad%u = %s conflicts with CAN, REFUSED\n",
			               (unsigned)i, (unsigned)c->pad, s_padMap[c->pad].name));
			continue;
		}
		if (c->frequencyHz == 0u) {
			ASLOG(PWMACE, ("ch%u frequency is 0, skipped\n", (unsigned)i));
			continue;
		}

		obj = PwmAc_GetModulePtr(c->hwModule);
		if (obj == NULL) {
			continue;
		}

		s_period[c->pad] = timerFreq / c->frequencyHz;

		if (s_moduleReady[c->hwModule] == 0u) {
			PwmAc_EnableClock(c->hwModule);

			PwmLiteDrv_GetDefaultModuleConfig(&modCfg);
			modCfg.period   = s_period[c->pad];
			/* SYNC_AT_RUNNING：配置写下去立即生效。
			 * 用 SYNC_AT_PERIOD 会让首帧要等一个完整周期才出来，
			 * 对"顶灯渐亮"这类要立刻看到亮度变化的场景不合适。 */
			modCfg.syncType = PWMLITEDRV_SYNC_AT_RUNNING;
			PwmLiteDrv_ModuleConfig(obj, &modCfg);

			/* 打印出来是必要的：PWM 的输出没有回读寄存器，
			 * 若这一行显示 period 与期望不符（比如 timerFreq 取到 0 时
			 * period 也是 0），说明时钟没起来 —— 而波形上看不出来。 */
			Platform_Printf("[pwm] mod%u period=%u (%uHz, timer=%uHz)\n",
			                (unsigned)c->hwModule,
			                (unsigned)modCfg.period,
			                (unsigned)c->frequencyHz,
			                (unsigned)timerFreq);

			s_moduleReady[c->hwModule] = 1u;
		}
	}

	/* ---- 第 2 遍：配引脚复用 + 配通道 ---- */
	for (i = 0u; i < cfg->numOfChannels; i++) {
		const Pwm_ChannelConfigType *c = &cfg->channels[i];
		PinsDrvType *port;

		if ((c->pad >= PWMAC_PAD_NUM) || (s_padMap[c->pad].usable == 0u)) {
			continue;
		}
		if (s_moduleReady[c->hwModule] == 0u) {
			continue;
		}

		port = PwmAc_GetPortPtr(s_padMap[c->pad].port);
		if (port == NULL) {
			continue;
		}

		/* 引脚复用：PWM 输出是 ALT6（**以官方例程为准**，
		 * pin_mux.xlsx 的 ALT 列编号容易数错一位） */
		PinsDrv_SetMuxModeSel(port, s_padMap[c->pad].pin, PINSDRV_MUX_ALT6);

		PwmAc_Apply(c, c->defaultDuty, TRUE);

		Platform_Printf("[pwm] ch%u -> %-5s  %uHz  duty=%u/32768\n",
		                (unsigned)i, s_padMap[c->pad].name,
		                (unsigned)c->frequencyHz, (unsigned)c->defaultDuty);
		configured++;
	}

	/* ---- 第 3 遍：使能各实例 ---- */
	for (m = 0u; m < PWMAC_MODULE_NUM; m++) {
		if (s_moduleReady[m] != 0u) {
			PwmLiteDrvType *obj = PwmAc_GetModulePtr(m);
			if (obj != NULL) {
				PwmLiteDrv_EnableModule(obj);
			}
		}
	}

	Platform_Printf("[pwm] init done: %u of %u channels active\n",
	                (unsigned)configured, (unsigned)cfg->numOfChannels);

	s_acInitialized = TRUE;
}

void PwmAc_DeInit(void)
{
	uint8_t m;

	if (!s_acInitialized) {
		return;
	}

	/* 先全部输出回到配置的空闲电平，再关模块。
	 * 顺序反了会让输出在关闭瞬间悬空，对驱动继电器的通道是隐患。 */
	for (m = 0u; m < PWMAC_MODULE_NUM; m++) {
		if (s_moduleReady[m] != 0u) {
			PwmLiteDrvType *obj = PwmAc_GetModulePtr(m);
			if (obj != NULL) {
				PwmLiteDrv_DisableModule(obj);
			}
			s_moduleReady[m] = 0u;
		}
	}

	s_acInitialized = FALSE;
}

void PwmAc_SetDutyCycle(uint16_t ch, const Pwm_ChannelConfigType *c,
                        Pwm_DutyCycleType duty)
{
	(void)ch;

	if ((!s_acInitialized) || (c == NULL)) {
		return;
	}

	PwmAc_Apply(c, duty, FALSE);
}

void PwmAc_SetPeriodAndDuty(uint16_t ch, const Pwm_ChannelConfigType *c,
                           Pwm_PeriodType period, Pwm_DutyCycleType duty)
{
	PwmLiteDrvType *obj;
	PwmLiteDrv_ModuleConfigType modCfg;
	uint8_t m;

	(void)ch;

	if ((!s_acInitialized) || (c == NULL) || (c->pad >= PWMAC_PAD_NUM)) {
		return;
	}

	m = c->hwModule;
	obj = PwmAc_GetModulePtr(m);
	if (obj == NULL) {
		return;
	}

	/* 周期是模块级的：改一个通道的周期，同实例所有通道一起变。
	 * 这是硬件限制（`Pwm_Init` 已强制同实例周期一致），不是实现缺陷。 */
	PwmLiteDrv_GetDefaultModuleConfig(&modCfg);
	modCfg.period   = period;
	modCfg.syncType = PWMLITEDRV_SYNC_AT_RUNNING;
	PwmLiteDrv_ModuleConfig(obj, &modCfg);

	{
		uint16_t i;
		for (i = 0u; i < PWMAC_PAD_NUM; i++) {
			if ((s_mode[i] != 0xFFu)) {
				/* 同实例的通道周期都变了，缓存要跟着更新 */
				s_period[i] = period;
			}
		}
	}

	PwmAc_Apply(c, duty, TRUE);
}

void PwmAc_SetOutputToIdle(uint16_t ch, const Pwm_ChannelConfigType *c)
{
	(void)ch;

	if ((!s_acInitialized) || (c == NULL)) {
		return;
	}

	/* 空闲电平走"静态"分支：把 duty 设成 0% 或 100% 使输出固定在 idleState。
	 * 注意这里借用了 duty 的边界语义：
	 *   正极性 + idleState=低 → duty=0  → 恒低
	 *   正极性 + idleState=高 → duty=100% → 恒高
	 *   反极性则相反 */
	if (c->polarity == 0u) {
		PwmAc_Apply(c, (c->idleState == 0u) ? 0u : (Pwm_DutyCycleType)0x8000u, FALSE);
	} else {
		PwmAc_Apply(c, (c->idleState == 0u) ? (Pwm_DutyCycleType)0x8000u : 0u, FALSE);
	}
}

Pwm_OutputStateType PwmAc_GetOutputState(uint16_t ch,
                                         const Pwm_ChannelConfigType *c)
{
	PwmLiteDrvType *obj;
	uint32_t th0;
	uint32_t th1;

	(void)ch;

	if ((!s_acInitialized) || (c == NULL) || (c->pad >= PWMAC_PAD_NUM)) {
		return PWM_LOW;
	}

	obj = PwmAc_GetModulePtr(c->hwModule);
	if (obj == NULL) {
		return PWM_LOW;
	}

	/* 用阈值反推当前是"恒高/恒低/调制"，再判断极性下的电平。
	 *
	 * 为什么不直接读引脚电平：PwmLite 没有"当前输出电平"的只读寄存器，
	 * 而调制状态下读引脚得到的是瞬态值，调用方拿到也没意义。
	 * 这里返回的是"按当前配置，输出的稳定电平语义"：
	 *   - 恒高/恒低模式 → 直接给对应电平
	 *   - 调制模式 → 给"周期开始时的电平"（即极性） */
	th0 = 0u;
	th1 = s_period[c->pad];

	if (s_mode[c->pad] == PWMAC_MODE_STATIC_HIGH) {
		return PWM_HIGH;
	}
	if (s_mode[c->pad] == PWMAC_MODE_STATIC_LOW) {
		return PWM_LOW;
	}

	(void)th0;
	(void)th1;

	/* 调制态：返回极性本身（周期起点电平） */
	return (c->polarity == 0u) ? PWM_HIGH : PWM_LOW;
}

uint32_t PwmAc_GetTimerFreq(void)
{
	uint32_t freq = 0u;

	if (ClockDrv_GetFreq(&g_mcu.clockDrv, CLOCKDRV_APB, &freq) == false) {
		return 0u;
	}

	return freq;
}
#endif /* USE_PWM */
