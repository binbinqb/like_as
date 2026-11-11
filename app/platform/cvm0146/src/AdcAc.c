/**
 * @file    AdcAc.c
 * @brief   ADC 平台实现（CVM0146）：ADC0 + ADC1 双单元、多通道
 * @details 本文件是 ADC 模块里**唯一允许接触芯片寄存器**的地方。
 *
 * @section ADCAC_SWTRIG 为什么"软件触发"要绕道 PDB + TRGMUX
 *
 *          `CVM014x` 的厂商 ADC 驱动 `adc_drv.h` 只有
 *          `Init / GetDefaultConfig / Configure / GetRn / GetCocon`，
 *          **没有任何"启动一次转换"的 API** —— 这不是 SDK 漏了，
 *          而是这颗 ADC 的设计：转换只能由**硬件触发源**启动
 *          （PDB 或 TRGMUX），没有"写个寄存器就转"的独立触发位。
 *
 *          实测可用的链路（三个环节缺一不可）：
 *          @code
 *          TrgMuxDrv_GenSWTrigger()
 *             → SIM_SW_TRIG 脉冲 → TRGMUX → PDBn TRG_IN
 *             → PDBn 计数 → 预触发 → ADCn 转换
 *             → COCO 置位 → AdcDrv_GetRn() 读值并自动清标志
 *          @endcode
 *
 * @warning 这就是"ADC 禁软触发"那条勘误的实际含义。
 *          三条都踩过：① 时钟没开 ② 没配 TRGMUX ③ PDB 配置没 LoadCmd。
 *          三者都不报错，只表现为"COCO 永不置位"。
 *
 * @section ADCAC_SLOT 槽位 vs 通道：两个不能混的概念
 *
 *          | 概念 | 含义 | 谁决定 |
 *          |------|------|--------|
 *          | **槽位** | SC1A/SC1B… 的序号，决定**结果进哪个 Rn** | 组内通道的**顺序** |
 *          | **通道** | ADCH 域，决定**采样哪个引脚** | 配置表的 `hwChannel` |
 *
 *          `AdcDrv_ConfigureChn(obj, chn, state)` 里 `chn` 是**槽位**、
 *          `state` 才是 ADCH（它内部就是 `AdcReg_SetScAdCh(reg, chn, state)`）。
 *          搞反了会读到"另一个槽位上一次的值"，而不是报错。
 *
 * @section ADCAC_LIMIT 能力边界
 *          | 能力 | 状态 |
 *          |------|------|
 *          | ADC0 / ADC1 双单元 | ✅ |
 *          | 单组多通道（同单元内一次触发扫描） | ✅ 按槽位 0..n-1 顺序映射 |
 *          | 组内跨单元 | ❌ 配置检查阶段就拒绝（一组只能一个 `hwUnit`） |
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：ADC0 + PDB0 单通道软触发 |
 * | V1.1.0 | 2026-11-11 | binbina | 双单元 + 多通道（槽位=组内序号），槽位默认全禁用 |
 */
#include "Adc.h"
#include "Adc_Priv.h"
#include "Adc_Cfg.h"

#include "platform_priv.h"      /* g_mcu（adc0/1Drv、pdb0/1Drv、trgMuxDrv） */
#include "platform_cvm0146.h"   /* Platform_Printf */

/* ============================ [ 宏 ] ============================ */

/** @brief 支持的 ADC 单元数（ADC0 / ADC1） */
#define ADCAC_UNIT_NUM          (2u)

/** @brief 单组最大通道数，与 `ADC_CFG_MAX_CH_PER_GROUP` 一致 */
#define ADCAC_MAX_CH_PER_GROUP  (ADC_CFG_MAX_CH_PER_GROUP)

/* ============================ [ 类型 ] ============================ */

/**
 * @brief 一个 ADC 单元的运行上下文
 * @note  ADCn 只能由 PDBn 触发（PDB 的 bbSel 描述：PDB0 CH0 对 ADC0 COCO、
 *        PDB1 CH0 对 ADC1 COCO，两者独立）。所以单元与 PDB 是**成对**的，
 *        不能交叉复用。
 */
typedef struct {
	AdcDrvType *adc;   /**< ADC 驱动实例 */
	PdbDrvType *pdb;   /**< 对应的 PDB 驱动实例 */
	uint8_t     group; /**< 该单元承载的组号（**一个单元只承载一个组**） */
	boolean     used;  /**< 配置里是否用到该单元 */
} AdcAc_UnitType;

/* ============================ [ 数据 ] ============================ */

static AdcAc_UnitType       s_unit[ADCAC_UNIT_NUM];
static const Adc_ConfigType *s_cfg;
static boolean              s_active[ADC_CFG_NUM_GROUPS];

/* ============================ [ 内部 ] ============================ */

/**
 * @brief 取某组对应的单元上下文
 * @param[in]  group 组号
 * @param[out] unit  单元上下文
 * @return E_OK 组号合法且该单元已被初始化
 */
static Std_ReturnType AdcAc_GetUnit(Adc_GroupType group, AdcAc_UnitType **unit)
{
	uint8_t u;

	if ((s_cfg == NULL) || (group >= s_cfg->numOfGroups)) {
		return E_NOT_OK;
	}

	u = s_cfg->groups[group].hwUnit;
	if ((u >= ADCAC_UNIT_NUM) || (!s_unit[u].used)) {
		return E_NOT_OK;
	}

	*unit = &s_unit[u];
	return E_OK;
}

/**
 * @brief 配置一个 ADC 单元 + 配对的 PDB，并把组内通道映射到槽位
 * @param[in] unit       单元号（0/1）
 * @param[in] sampleLen  采样时间（单元级，SC3）
 * @param[in] grp        该单元承载的组（通道按顺序占槽位 0..n-1）
 * @return E_OK / E_NOT_OK
 *
 * @warning **槽位必须在 `AdcDrv_Configure()` 里一次配好，不能等到运行期再改。**
 *
 *          实测教训：先按"全部槽位 DISABLE"配置，然后在
 *          `AdcAc_StartGroupConversion()` 里用 `AdcDrv_ConfigureChn()`
 *          把槽位 0 改成目标通道 —— 结果 `COCO` **永不置位**（一直 BUSY）。
 *          把同样的槽位配置挪到 `Configure()` 的 `chnCfg[]` 里就正常了。
 *
 *          结论：ADC 使能后再改 SC1 的 ADCH，不保证被下一次触发采用。
 *          配表阶段一次定死，运行期只触发、不改通道。
 *
 * @note 其余槽位显式写 `ADCDRV_INCHN_DISABLE`（0x1F）。
 *       `AdcDrv_GetDefaultConfig()` 会把 24 个槽位全部使能
 *       （`chnCfg[i].chnSel = i`），不清掉的话一次触发会**扫全部 24 路**。
 */
static Std_ReturnType AdcAc_SetupUnit(uint8_t unit, uint8_t sampleLen,
                                      const Adc_GroupConfigType *grp)
{
	AdcDrv_ConfigType adcCfg;
	PdbDrv_ConfigType pdbCfg;
	ClockDrv_ModuleClkConfigType clockCfg;
	uint32_t pdbFreq;
	uint8_t  i;

	/* 1) 时钟：ADCn 与 PDBn 的时钟在 Mcu_Init() 里都不开，必须显式开 */
	clockCfg.gating = true;
	clockCfg.source = CLOCKDRV_PLL;
	clockCfg.div    = 4u;                    /* ADC 时钟 = PLL/4（与官方例程一致） */
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv,
	                              (unit == 0u) ? CLOCKDRV_ADC0 : CLOCKDRV_ADC1,
	                              &clockCfg);

	clockCfg.gating = true;                  /* PDB 只需开门控 */
	(void)ClockDrv_ConfigureClock(&g_mcu.clockDrv,
	                              (unit == 0u) ? CLOCKDRV_PDB0 : CLOCKDRV_PDB1,
	                              &clockCfg);

	/* 2) ADC 基本参数 */
	AdcDrv_GetDefaultConfig(&adcCfg);
	adcCfg.conversionMode = ADCDRV_CONVERSION_12BIT;
	adcCfg.continuousMode = ADCDRV_ONESHOT;
	adcCfg.sampleLen      = sampleLen;
	adcCfg.refVolSel      = ADCDRV_REFVOLT_VDDA;
	adcCfg.trgSrcCfg.hwTrgSrc  = ADCDRV_HW_TRGSRC_PDB;
	adcCfg.trgSrcCfg.pretrgSrc = ADCDRV_PRETRG_PDB_PRETRIGGER;

	for (i = 0u; i < (uint8_t)ADCDRV_CHANNEL_NUM; i++) {
		adcCfg.chnCfg[i].chnSel    = ADCDRV_INCHN_DISABLE;
		adcCfg.chnCfg[i].intEnable = false;
	}
	/* 组内第 i 个通道 → 槽位 i（结果落在 Rn 的 n=i） */
	for (i = 0u; i < grp->numOfChannels; i++) {
		adcCfg.chnCfg[i].chnSel = (AdcDrv_InChnType)grp->channels[i].hwChannel;
	}

	AdcDrv_Configure(s_unit[unit].adc, &adcCfg);
	AdcDrv_EnableAdc(s_unit[unit].adc);

	/* 3) PDB：取值逐项照抄官方例程 adc_pdb_trigger */
	(void)ClockDrv_GetFreq(&g_mcu.clockDrv,
	                       (unit == 0u) ? CLOCKDRV_PDB0 : CLOCKDRV_PDB1, &pdbFreq);

	PdbDrv_GetDefaultConfig(&pdbCfg);
	pdbCfg.ldmode          = PDBDRV_LDMOD_LOAD_VAL_IMMEDIATELY;
	pdbCfg.trgInSel        = PDBDRV_TRGSEL_TRGGER_IN_0;   /* TRGMUX → TRG_IN0 */
	pdbCfg.cMode           = PDBDRV_CONT_CONTINUOUS;
	pdbCfg.prescalerFactor = PDBDRV_PRESCALER_128MULT;
	pdbCfg.mult            = PDBDRV_MULT_FACTOR_40;
	pdbCfg.preTrgCfg.mode[0][0] = PDBDRV_PRETRG_DELAY_MODE;

	/*
	 * 多通道的关键：**第二个及以后的预触发必须配成背靠背模式**。
	 *
	 * @warning 只配 `mode[0][0]` 时，一次触发只转换**第一个**通道，
	 *          其余槽位的 COCO 永远不置位 —— 现象是
	 *          "`IsGroupCompleted()` 永远返回 FALSE，整组 timeout"，
	 *          但单通道组完全正常（ADC1 那组就是这么通过的，
	 *          一度让人以为多通道本身不可用）。
	 *
	 *          `PDBDRV_PRETRG_BB_MODE` 表示该预触发在前一个完成后
	 *          立即接续（back-to-back），PDB 会连着把整组触发完。
	 *          官方例程 `adc_pdb_trigger` 里那 15 行
	 *          `mode[0][1..7] = PRETRG_BB_MODE` 就是这个作用。
	 */
	for (i = 1u; i < grp->numOfChannels; i++) {
		pdbCfg.preTrgCfg.mode[0][i] = PDBDRV_PRETRG_BB_MODE;
	}

	pdbCfg.dlyCfg.dlyCnt[0][0]  = 0u;
	/* 周期 1 s：本工程靠 GenSWTrigger 手动触发，这个值只决定"下次自动触发"
	 * 何时到来。设小会与手动触发抢时序，导致读到的值属于上一个 MUX 地址。 */
	pdbCfg.dlyCfg.modCnt        = (uint16_t)(pdbFreq / 128u / 40u);
	PdbDrv_Configure(s_unit[unit].pdb, &pdbCfg);

	/*
	 * @warning **必须调 LoadCmd，`PdbDrv_Configure()` 不会帮你调。**
	 *          PDB 的配置寄存器是双缓冲的：Configure 只写缓冲区，
	 *          要置 `SC[LDOK]=1` 才加载到工作寄存器参与计数。
	 *          漏这一步的症状是"配置读回全对，PDB 完全不动"。
	 */
	PdbDrv_LoadCmd(s_unit[unit].pdb);
	PdbDrv_EnablePdb(s_unit[unit].pdb);

	return E_OK;
}

/* ============================ [ 平台接口 ] ============================ */

Std_ReturnType AdcAc_Init(const Adc_ConfigType *config)
{
	static const TrgMuxDrv_InOutMappingType s_trgmuxMap[] = {
		{ TRGMUXDRV_TRIGSOURCE_SIM_SW_TRIG, TRGMUXDRV_TARGETMODULE_PDB0_TRG_IN, false },
		{ TRGMUXDRV_TRIGSOURCE_SIM_SW_TRIG, TRGMUXDRV_TARGETMODULE_PDB1_TRG_IN, false },
	};
	TrgMuxDrv_ConfigType trgmuxCfg;
	uint8_t  sampleLen[ADCAC_UNIT_NUM];
	boolean  unitSeen[ADCAC_UNIT_NUM];
	uint16_t g;
	uint16_t i;
	uint8_t  u;

	if (config == NULL) {
		return E_NOT_OK;
	}

	/* 单元实例绑定：ADCn ↔ PDBn 成对，不能交叉 */
	s_unit[0].adc = &g_mcu.adc0Drv;
	s_unit[0].pdb = &g_mcu.pdb0Drv;
	s_unit[1].adc = &g_mcu.adc1Drv;
	s_unit[1].pdb = &g_mcu.pdb1Drv;
	for (u = 0u; u < ADCAC_UNIT_NUM; u++) {
		s_unit[u].used = FALSE;
		unitSeen[u] = FALSE;
		sampleLen[u] = 0u;
	}

	/* 先扫一遍配置：校验单元号、组内不跨单元、同单元采样时间一致 */
	for (g = 0u; g < config->numOfGroups; g++) {
		const Adc_GroupConfigType *grp = &config->groups[g];

		if ((grp->numOfChannels == 0u) ||
		    (grp->numOfChannels > (uint8_t)ADCAC_MAX_CH_PER_GROUP)) {
			Platform_Printf("[adc] group %u bad channel count %u\n",
			                (unsigned)g, (unsigned)grp->numOfChannels);
			return E_NOT_OK;
		}
		if (grp->hwUnit >= ADCAC_UNIT_NUM) {
			Platform_Printf("[adc] group %u asks unsupported unit %u\n",
			                (unsigned)g, (unsigned)grp->hwUnit);
			return E_NOT_OK;
		}

		u = grp->hwUnit;
		/* 一个 ADC 单元只承载一个组：槽位从 0 开始按组内顺序分配，
		 * 同一单元上放两个组会让槽位重叠（后配的覆盖先配的）。 */
		if (s_unit[u].used) {
			Platform_Printf("[adc] unit %u already carries group %u; "
			                "only one group per ADC unit is supported\n",
			                (unsigned)u, (unsigned)s_unit[u].group);
			return E_NOT_OK;
		}
		s_unit[u].used  = TRUE;
		s_unit[u].group = (uint8_t)g;

		for (i = 0u; i < grp->numOfChannels; i++) {
			uint8_t sl = (uint8_t)grp->channels[i].samplingTime;

			if (!unitSeen[u]) {
				sampleLen[u] = sl;
				unitSeen[u] = TRUE;
			} else if (sl != sampleLen[u]) {
				/* 采样时间是单元级（SC3），同单元不同值会被后配的覆盖 */
				Platform_Printf("[adc] unit %u samplingTime mismatch (%u vs %u)\n",
				                (unsigned)u, (unsigned)sl, (unsigned)sampleLen[u]);
				return E_NOT_OK;
			}
		}
	}

	/* TRGMUX：把 SIM 的软件触发同时路由到两个 PDB 的 TRG_IN */
	trgmuxCfg.numOfInOutMappings = (uint16_t)ARRAY_SIZE(s_trgmuxMap);
	trgmuxCfg.inOutMapping       = s_trgmuxMap;
	TrgMuxDrv_Configure(&g_mcu.trgMuxDrv, &trgmuxCfg);

	for (u = 0u; u < ADCAC_UNIT_NUM; u++) {
		if (s_unit[u].used) {
			if (AdcAc_SetupUnit(u, sampleLen[u],
			                    &config->groups[s_unit[u].group]) != E_OK) {
				return E_NOT_OK;
			}
		}
	}

	s_cfg = config;
	for (g = 0u; g < (uint16_t)ADC_CFG_NUM_GROUPS; g++) {
		s_active[g] = FALSE;
	}

	return E_OK;
}

void AdcAc_DeInit(void)
{
	uint8_t u;

	for (u = 0u; u < ADCAC_UNIT_NUM; u++) {
		if (s_unit[u].used) {
			PdbDrv_PdbDisable(s_unit[u].pdb);
			AdcDrv_DisableAdc(s_unit[u].adc);
			s_unit[u].used = FALSE;
		}
	}
	s_cfg = NULL;
}

Std_ReturnType AdcAc_StartGroupConversion(Adc_GroupType group)
{
	const Adc_GroupConfigType *grp;
	AdcAc_UnitType *unit;
	uint16_t i;

	if (AdcAc_GetUnit(group, &unit) != E_OK) {
		return E_NOT_OK;
	}
	grp = &s_cfg->groups[group];

	/* 1) 清掉残留 COCO。读 Rn 会清标志；上次没读走的话，
	 *    这次刚触发就会被判"已完成"，读到的是上一次的值。
	 *
	 *    @note 这里**不再改槽位的 ADCH** —— 见 `AdcAc_SetupUnit()` 的
	 *          @warning：使能后再改 SC1 不保证生效。槽位映射在 Configure
	 *          阶段就定死了。 */
	for (i = 0u; i < grp->numOfChannels; i++) {
		(void)AdcDrv_GetRn(unit->adc, (uint8_t)i);
	}

	/* 2) 经 TRGMUX 产生一次软件触发（不是直接写 PDB 的 SWTRIG） */
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
	const Adc_GroupConfigType *grp;
	AdcAc_UnitType *unit;
	uint16_t i;

	if ((group >= (Adc_GroupType)ADC_CFG_NUM_GROUPS) || (!s_active[group])) {
		return FALSE;
	}
	if (AdcAc_GetUnit(group, &unit) != E_OK) {
		return FALSE;
	}
	grp = &s_cfg->groups[group];

	/* 整组完成 = 组内所有槽位的 COCO 都置位 */
	for (i = 0u; i < grp->numOfChannels; i++) {
		if (!AdcDrv_GetCocon(unit->adc, (uint8_t)i)) {
			return FALSE;
		}
	}
	return TRUE;
}

Std_ReturnType AdcAc_ReadGroupRaw(Adc_GroupType group, uint16_t *raw)
{
	const Adc_GroupConfigType *grp;
	AdcAc_UnitType *unit;
	uint16_t i;

	if (raw == NULL) {
		return E_NOT_OK;
	}
	if (AdcAc_GetUnit(group, &unit) != E_OK) {
		return E_NOT_OK;
	}
	grp = &s_cfg->groups[group];

	for (i = 0u; i < grp->numOfChannels; i++) {
		raw[i] = AdcDrv_GetRn(unit->adc, (uint8_t)i);
	}

	s_active[group] = FALSE;
	return E_OK;
}
