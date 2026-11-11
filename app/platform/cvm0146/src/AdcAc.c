/**
 * @file    AdcAc.c
 * @brief   ADC 平台实现（CVM0146）
 * @details 本文件是 ADC 模块里**唯一允许接触芯片寄存器**的地方。
 *
 * @section ADCAC_SWTRIG 为什么"软件触发"要绕道 PDB
 *
 *          `CVM014x` 的厂商 ADC 驱动 `adc_drv.h` 只有
 *          `Init / GetDefaultConfig / Configure / GetRn / GetCocon`，
 *          **没有任何"启动一次转换"的 API** —— 这不是 SDK 漏了，
 *          而是这颗 ADC 的设计：转换只能由**硬件触发源**启动
 *          （PDB 或 TRGMUX），没有"写个寄存器就转"的独立触发位。
 *
 *          所以本工程的软件触发链路是：
 *          @code
 *          PdbDrv_SwtrigCmd()  →  PDB 产生预触发  →  ADC 开始转换
 *                                              →  COCO 置位
 *          AdcDrv_GetRn()      ←  读结果并自动清 COCO
 *          @endcode
 *
 *          @warning 这就是记忆里那条"ADC 禁软触发"勘误的实际含义。
 *                   如果将来有人试图在 `AdcAc_StartGroupConversion()` 里
 *                   直接写 ADC 的 SC1 寄存器来启动转换，**不会生效也不报错** ——
 *                   表现为"启动了但 COCO 永远不置位"。
 *
 * @section ADCAC_LIMIT 当前实现的能力边界（**刻意保守**）
 *
 *          | 能力 | 状态 |
 *          |------|------|
 *          | 单通道、单组 | ✅ 已实现 |
 *          | 多通道扫描组 | ❌ 返回 `E_NOT_OK` |
 *          | ADC1 / PDB1 | ❌ 返回 `E_NOT_OK` |
 *
 *          原因：一次触发到底转几个通道、结果落在哪个 `Rn`，
 *          取决于 SC1A..SC1n 的序列语义，**必须上板实测确认**。
 *          在没验证前就写"支持多通道"，等于把猜测当结论。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：ADC0 + PDB0 单通道软触发 |
 */
#include "Adc.h"
#include "Adc_Priv.h"
#include "Adc_Cfg.h"

#include "platform_priv.h"      /* g_mcu（含 adc0Drv / pdb0Drv）+ mcu.h 聚合的驱动头 */
#include "platform_cvm0146.h"   /* Platform_Printf */

/* ============================ [ 宏 ] ============================ */

/**
 * @brief 使用的 SC1 槽位
 * @note  用槽位 0（SC1A）做"单通道转换器"：每次启动前把 SC1A 的 ADCH
 *        改成本次要采的通道，结果始终读 R[0]。
 *        **槽位号 ≠ 通道号**，这两个概念在本文件里必须分清：
 *        | 概念 | 含义 | 在哪 |
 *        |------|------|------|
 *        | 槽位 | SC1A/SC1B… 的序号，决定结果进哪个 Rn | `ADCAC_SLOT` |
 *        | 通道 | ADCH 域，决定采样哪个引脚 | 配置表 `hwChannel` |
 */
#define ADCAC_SLOT              (0u)

/** @brief 仅支持 ADC0 + PDB0；其他单元在 Init 阶段就拒绝，不静默降级 */
#define ADCAC_SUPPORTED_UNIT    (0u)

/* ============================ [ 数据 ] ============================ */

static const Adc_ConfigType *s_cfg;
static boolean               s_active[ADC_CFG_NUM_GROUPS];

/* ============================ [ 内部 ] ============================ */

/**
 * @brief 取某组唯一通道的硬件通道号
 * @param[in]  group 组号
 * @param[out] ch    硬件通道号（ADCH）
 * @return E_OK 该组正好一个通道且单元受支持；否则 E_NOT_OK
 */
static Std_ReturnType AdcAc_GetSingleChannel(Adc_GroupType group, uint8_t *ch)
{
	const Adc_GroupConfigType *g;

	if ((s_cfg == NULL) || (group >= s_cfg->numOfGroups)) {
		return E_NOT_OK;
	}

	g = &s_cfg->groups[group];
	if (g->numOfChannels != 1u) {
		return E_NOT_OK;   /* 多通道扫描语义未验证，拒绝而不是猜 */
	}
	if (g->hwUnit != ADCAC_SUPPORTED_UNIT) {
		return E_NOT_OK;
	}

	*ch = g->channels[0].hwChannel;
	return E_OK;
}

/* ============================ [ 平台接口 ] ============================ */

Std_ReturnType AdcAc_Init(const Adc_ConfigType *config)
{
	AdcDrv_ConfigType adcCfg;
	PdbDrv_ConfigType pdbCfg;
	ClockDrv_ModuleClkConfigType clockCfg;
	TrgMuxDrv_ConfigType         trgmuxCfg;
	uint32_t pdbFreq;
	uint16_t g;
	uint16_t i;
	uint8_t  sampleLen;

	if (config == NULL) {
		return E_NOT_OK;
	}

	/*
	 * 一致性检查：CVM014x 的采样时间是**单元级**（SC3 寄存器），
	 * 不是通道级。所以所有组的采样时间必须相同 —— 配成不同值的话，
	 * 后配的会覆盖先配的，现象是"某些通道读数偏低"且很难定位。
	 * 与其静默覆盖，不如直接拒绝。
	 */
	sampleLen = (uint8_t)config->groups[0].channels[0].samplingTime;
	for (g = 0u; g < config->numOfGroups; g++) {
		if (config->groups[g].hwUnit != ADCAC_SUPPORTED_UNIT) {
			Platform_Printf("[adc] only ADC0 supported (group %u asks unit %u)\n",
			                (unsigned)g, (unsigned)config->groups[g].hwUnit);
			return E_NOT_OK;
		}
		for (i = 0u; i < config->groups[g].numOfChannels; i++) {
			if ((uint8_t)config->groups[g].channels[i].samplingTime != sampleLen) {
				Platform_Printf("[adc] samplingTime differs (group %u ch %u)\n",
				                (unsigned)g, (unsigned)i);
				return E_NOT_OK;
			}
		}
	}

	/* ------------------------------------------------------------------
	 * 0) 时钟：ADC0 与 PDB0 的时钟在 `Mcu_Init()` 里**不会**被打开，
	 *    必须在这里显式开 —— 这是实测踩出来的第一个隐形坑。
	 *
	 *    时钟没开时的表现非常有欺骗性：
	 *    `AdcDrv_Configure()` 不报错、寄存器写"成功"、`GetCocon()` 永远读 0。
	 *    不是"配置错了"，是模块根本没在跑。
	 * ------------------------------------------------------------------ */
	clockCfg.gating = true;
	clockCfg.source = CLOCKDRV_PLL;
	clockCfg.div    = 4u;                    /* ADC 时钟 = PLL/4（与官方例程一致） */
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_ADC0, &clockCfg);

	clockCfg.gating = true;                  /* PDB 只需开门控，不查分频 */
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv, CLOCKDRV_PDB0, &clockCfg);

	/* ------------------------------------------------------------------
	 * 0b) TRGMUX：把 SIM 的软件触发路由到 PDB0 的 TRG_IN。
	 *
	 * @warning 这是"软件触发 ADC"的**必由之路**，别想着直接用
	 *          `PdbDrv_SwtrigCmd()` 就行 —— 实测走不通（PDB 的 SC[SWTRIG]
	 *          在 `trgInSel` 未选通时不会启动计数）。
	 *          正确链路是：
	 *          @code
	 *          TrgMuxDrv_GenSWTrigger()
	 *             → SIM_SW_TRIG 脉冲 → TRGMUX → PDB0 TRG_IN
	 *             → PDB 计数 → 预触发 → ADC 转换
	 *          @endcode
	 * ------------------------------------------------------------------ */
	{
		static const TrgMuxDrv_InOutMappingType s_trgmuxMap[] = {
			{ TRGMUXDRV_TRIGSOURCE_SIM_SW_TRIG, TRGMUXDRV_TARGETMODULE_PDB0_TRG_IN, false },
		};

		trgmuxCfg.numOfInOutMappings = (uint16_t)ARRAY_SIZE(s_trgmuxMap);
		trgmuxCfg.inOutMapping       = s_trgmuxMap;
		TrgMuxDrv_Configure(&g_mcu.trgMuxDrv, &trgmuxCfg);
	}

	AdcDrv_GetDefaultConfig(&adcCfg);
	adcCfg.conversionMode = ADCDRV_CONVERSION_12BIT;   /* 分辨率 */
	adcCfg.continuousMode = ADCDRV_ONESHOT;            /* 单次，不自循环 */
	adcCfg.sampleLen      = sampleLen;
	adcCfg.refVolSel      = ADCDRV_REFVOLT_VDDA;       /* 与 Cfg 的 refVoltageMv 对应 */
	adcCfg.trgSrcCfg.hwTrgSrc  = ADCDRV_HW_TRGSRC_PDB;        /* 触发源 = PDB */
	adcCfg.trgSrcCfg.pretrgSrc = ADCDRV_PRETRG_PDB_PRETRIGGER;

	/* 把所有组用到的通道都配成外部输入；槽位 0 先指向第一个通道 */
	for (g = 0u; g < config->numOfGroups; g++) {
		for (i = 0u; i < config->groups[g].numOfChannels; i++) {
			uint8_t ch = config->groups[g].channels[i].hwChannel;

			adcCfg.chnCfg[ch].chnSel    = (AdcDrv_InChnType)ch;  /* EXT0~EXTn */
			adcCfg.chnCfg[ch].intEnable = false;                 /* 轮询，不开中断 */
		}
	}

	AdcDrv_Configure(&g_mcu.adc0Drv, &adcCfg);
	AdcDrv_EnableAdc(&g_mcu.adc0Drv);

	/*
	 * PDB：只要一条预触发通路（CH0 / PRE0），delay 给 1 个计数。
	 * 这里的 delay 是"触发到 ADC 启动"的延迟，不是采样时间 ——
	 * 采样时间在 adcCfg.sampleLen 里。
	 */
	/* ------------------------------------------------------------------
	 * 2) PDB：这些取值**逐项照抄官方例程**
	 *    `examples/CVM0146/driver_examples/adc_pdb_trigger/src/main.c`
	 *
	 *    不照抄的代价是"每个字段都对、组合起来不工作"：
	 *    `prescalerFactor` 与 `mult` 决定计数时钟，选错只是触发变慢；
	 *    但 `trgInSel` 选错 → TRGMUX 送进来的触发根本进不了 PDB。
	 * ------------------------------------------------------------------ */
	(void)ClockDrv_GetFreq(&g_mcu.clockDrv, CLOCKDRV_PDB0, &pdbFreq);

	PdbDrv_GetDefaultConfig(&pdbCfg);
	pdbCfg.ldmode          = PDBDRV_LDMOD_LOAD_VAL_IMMEDIATELY;
	pdbCfg.trgInSel        = PDBDRV_TRGSEL_TRGGER_IN_0;   /* TRGMUX → TRG_IN0 */
	pdbCfg.cMode           = PDBDRV_CONT_CONTINUOUS;
	pdbCfg.prescalerFactor = PDBDRV_PRESCALER_128MULT;
	pdbCfg.mult            = PDBDRV_MULT_FACTOR_40;
	pdbCfg.preTrgCfg.mode[0][0] = PDBDRV_PRETRG_DELAY_MODE;
	pdbCfg.dlyCfg.dlyCnt[0][0]  = 0u;
	/* 周期 1 s：本工程靠 GenSWTrigger 手动触发，这个值只决定"下次自动触发"
	 * 何时到来。设小会与手动触发抢时序，导致读到的值属于上一个 MUX 地址。 */
	pdbCfg.dlyCfg.modCnt        = (uint16_t)(pdbFreq / 128u / 40u);
	PdbDrv_Configure(&g_mcu.pdb0Drv, &pdbCfg);

	/*
	 * @warning **必须调 LoadCmd，`PdbDrv_Configure()` 不会帮你调。**
	 *
	 *          PDB 的配置寄存器是"双缓冲"的：`PdbDrv_Configure()` 写进去的
	 *          只是缓冲区，要置 `SC[LDOK]=1` 才加载到工作寄存器参与计数。
	 *          漏这一步的表现是：所有配置读回来都对，但 **PDB 完全不动**，
	 *          ADC 永远收不到触发，COCO 永不置位。
	 */
	PdbDrv_LoadCmd(&g_mcu.pdb0Drv);

	PdbDrv_EnablePdb(&g_mcu.pdb0Drv);

	s_cfg = config;
	for (g = 0u; g < (uint16_t)ADC_CFG_NUM_GROUPS; g++) {
		s_active[g] = FALSE;
	}

	return E_OK;
}

void AdcAc_DeInit(void)
{
	PdbDrv_PdbDisable(&g_mcu.pdb0Drv);
	AdcDrv_DisableAdc(&g_mcu.adc0Drv);
	s_cfg = NULL;
}

Std_ReturnType AdcAc_StartGroupConversion(Adc_GroupType group)
{
	uint8_t ch;

	if (AdcAc_GetSingleChannel(group, &ch) != E_OK) {
		return E_NOT_OK;
	}

	/* 1) 把槽位 0 指向本次要采的通道（运行期可改，这是单通道复用的关键） */
	AdcDrv_ConfigureChn(&g_mcu.adc0Drv, ADCAC_SLOT, (AdcDrv_InChnType)ch);

	/*
	 * 2) 读一次结果寄存器丢弃。
	 *    Kinetis 系 ADC 的 COCO 在读 Rn 时清除；上一次转换若没被读走，
	 *    COCO 会一直挂着，导致这次刚触发就被判"已完成"，读到上一次的值。
	 */
	(void)AdcDrv_GetRn(&g_mcu.adc0Drv, ADCAC_SLOT);

	/* 3) 经 TRGMUX 产生一次软件触发（不是直接写 PDB 的 SWTRIG） */
	TrgMuxDrv_GenSWTrigger(&g_mcu.trgMuxDrv, 100u);

	s_active[group] = TRUE;
	return E_OK;
}

Std_ReturnType AdcAc_StopGroupConversion(Adc_GroupType group)
{
	if (group >= (Adc_GroupType)ADC_CFG_NUM_GROUPS) {
		return E_NOT_OK;
	}
	s_active[group] = FALSE;
	return E_OK;
}

boolean AdcAc_IsGroupCompleted(Adc_GroupType group)
{
	if ((group >= (Adc_GroupType)ADC_CFG_NUM_GROUPS) || (!s_active[group])) {
		return FALSE;
	}

	return AdcDrv_GetCocon(&g_mcu.adc0Drv, ADCAC_SLOT) ? TRUE : FALSE;
}

Std_ReturnType AdcAc_ReadGroupRaw(Adc_GroupType group, uint16_t *raw)
{
	uint8_t ch;

	if (raw == NULL) {
		return E_NOT_OK;
	}
	if (AdcAc_GetSingleChannel(group, &ch) != E_OK) {
		return E_NOT_OK;
	}
	(void)ch;   /* 结果在槽位 0 的 R0 里，与 ADCH 无关 */

	raw[0] = AdcDrv_GetRn(&g_mcu.adc0Drv, ADCAC_SLOT);
	s_active[group] = FALSE;
	return E_OK;
}
