/**
 * @file    Adc_Cfg.c
 * @brief   ADC 配置表（纯数据，零逻辑）
 * @details 用开发板自带的三个模拟源验证两条关键路径：
 *          | 组 | 单元 | 通道 | 用途 | 验证什么 |
 *          |----|------|------|------|----------|
 *          | 0 | ADC0 | ch12(POT1) + ch13(VBAT) | 电位计 1 / 电池电压 | **多通道一次触发** |
 *          | 1 | ADC1 | ch2(POT2) | 电位计 2 | **第二个 ADC 单元** |
 *
 * @warning **通道取值出处**：《曦华科技 CVM0146 开发板快速入门》表 2「模拟输入」
 *          （文件号 CVA-CVM014x-EVK-003，版本 2.0，第 7 页）：
 *
 *          | MCU 端口 | 网络名 | ADC 通道 | 说明 |
 *          |----------|--------|----------|------|
 *          | PTC14 | AN_POT_1 | ADC0_SE12 | 电位计 1 |
 *          | PTD2  | AN_POT_2 | ADC1_SE2  | 电位计 2 |
 *          | PTC15 | I_AN_VBAT | ADC0_SE13 | 电池电压，分压比 0.23（Vadc = VIN×0.23） |
 *
 *          填错的症状不是报错，而是"读到别的引脚的电压"，
 *          很容易被当成"采样不准"去查采样时间，方向就错了。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道探针 |
 * | V1.1.0 | 2026-11-11 | binbina | ADC0 双通道 + ADC1 单通道，覆盖多通道与双单元 |
 */
#include "Adc.h"
#include "Adc_Priv.h"
#include "Adc_Cfg.h"

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 通道默认参数说明
 *
 * @note `samplingTime` 填 20（ADC 时钟周期）。这个值不是随便给的：
 *       MUX（RS2260）的 Ron ≈ 105 Ω 会串进采样网络，源阻抗越高需要的
 *       采样时间越长。20 对开发板的电位器（10 kΩ 级、低阻）够用，
 *       但接 RS2260 之后**必须重新扫描找收敛点**。
 *
 * @note `refVoltageMv` 填 3300：CVM014x 用 VDDA 做参考时就是 3.3 V。
 *       若板上用的是外部 VREF，这里和 `AdcAc.c` 的 `refVolSel` 必须一起改。
 *
 * @warning **同一 ADC 单元内所有通道的 `samplingTime` 必须相同** ——
 *          CVM014x 的采样时间是单元级（SC3 寄存器），不是通道级。
 *          `AdcAc_Init()` 会检查这一点，不一致直接返回失败。
 */

/** @brief ADC0 组：POT1(AN_POT_1) + VBAT。两路都在 ADC0，验多通道扫描 */
static const Adc_ChannelConfigType Adc_Ch_Adc0[] = {
	{
		/* hwChannel    */ 12u,      /* ADC0_SE12 ← PTC14 / AN_POT_1（电位计 1） */
		/* resolution   */ 12u,
		/* samplingTime */ 20u,
		/* refVoltageMv */ 3300u,
		/* diffMode     */ 0u,
	},
	{
		/* hwChannel    */ 13u,      /* ADC0_SE13 ← PTC15 / I_AN_VBAT（分压 0.23） */
		/* resolution   */ 12u,
		/* samplingTime */ 20u,      /* 必须与上一通道相同（单元级配置） */
		/* refVoltageMv */ 3300u,
		/* diffMode     */ 0u,
	},
};

/** @brief ADC1 组：POT2(AN_POT_2)。验第二个 ADC 单元能否独立工作 */
static const Adc_ChannelConfigType Adc_Ch_Adc1[] = {
	{
		/* hwChannel    */ 2u,       /* ADC1_SE2 ← PTD2 / AN_POT_2（电位计 2） */
		/* resolution   */ 12u,
		/* samplingTime */ 20u,
		/* refVoltageMv */ 3300u,
		/* diffMode     */ 0u,
	},
};

/** @brief 组表：下标即组号（`ADC_CFG_GROUP_ADC0` / `_ADC1`） */
static const Adc_GroupConfigType Adc_Groups[ADC_CFG_NUM_GROUPS] = {
	{
		/* channels      */ Adc_Ch_Adc0,
		/* numOfChannels */ (uint8_t)ARRAY_SIZE(Adc_Ch_Adc0),
		/* hwUnit        */ 0u,                      /* ADC0 */
		/* convMode      */ ADC_CONV_MODE_ONESHOT,
		/* trigSrc       */ ADC_TRIGG_SRC_SW,        /* 内部经 PDB/TRGMUX 转发 */
		/* notification  */ NULL,
	},
	{
		/* channels      */ Adc_Ch_Adc1,
		/* numOfChannels */ (uint8_t)ARRAY_SIZE(Adc_Ch_Adc1),
		/* hwUnit        */ 1u,                      /* ADC1 */
		/* convMode      */ ADC_CONV_MODE_ONESHOT,
		/* trigSrc       */ ADC_TRIGG_SRC_SW,
		/* notification  */ NULL,
	},
};

/** @brief 驱动初始化用的唯一配置实例 */
const Adc_ConfigType Adc_Config = {
	Adc_Groups,
	(uint16_t)ARRAY_SIZE(Adc_Groups),
};

/**
 * @brief 每组通道数
 * @warning 必须与 `Adc_Groups[]` 的 `numOfChannels` 一致。
 *          重复一份是为了让上层不必 include `Adc_Priv.h`（模块私有头）。
 *          改组配置时两处一起改，否则上层读到的长度与实际转换的通道数不符。
 */
const uint8_t Adc_Cfg_GroupChannels[ADC_CFG_NUM_GROUPS] = {
	(uint8_t)ARRAY_SIZE(Adc_Ch_Adc0),
	(uint8_t)ARRAY_SIZE(Adc_Ch_Adc1),
};
