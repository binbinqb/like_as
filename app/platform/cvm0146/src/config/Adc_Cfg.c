/**
 * @file    Adc_Cfg.c
 * @brief   ADC 配置表（纯数据，零逻辑）
 * @details 当前只有一个"探针组"，用来先验证 ADC + PDB 的链路是否成立，
 *          还没接入实际的 MUX/传感器通道 —— 那些要等硬件通道号确认后再填。
 *
 * @warning **本表里的 `hwChannel` 必须填 ADCH 的硬件通道号**，不是引脚号。
 *          填错的症状不是报错，而是"读到别的引脚的电压"，
 *          很容易被当成"采样不准"去查采样时间，方向就错了。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：单通道探针组（ADCH0 / 12 bit / 3.3 V） |
 */
#include "Adc.h"
#include "Adc_Priv.h"
#include "Adc_Cfg.h"

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 探针组的通道表
 *
 * @note **通道取值出处**：《曦华科技 CVM0146 开发板快速入门》表 2「模拟输入」
 *       （文件号 CVA-CVM014x-EVK-003，版本 2.0，第 7 页）：
 *
 *       | MCU 端口 | 网络名 | ADC 通道 | 说明 |
 *       |----------|--------|----------|------|
 *       | PTC14 | AN_POT_1 | **ADC0_SE12** | 电位计 1，本探针用它 |
 *       | PTD2  | AN_POT_2 | ADC1_SE2  | 电位计 2，在 ADC1 上（本模块暂不支持） |
 *       | PTC15 | I_AN_VBAT | ADC0_SE13 | 电池电压，分压比 0.23（Vadc = VIN×0.23） |
 *
 *       选 POT1 而不是 VBAT 的原因：电位计能手动拧，读数必须跟着变 ——
 *       这是"链路真的在采样"最直接的证据；VBAT 是固定分压，
 *       读到一个数也无法区分"采样正确"和"读到的是残值"。
 *
 * @note `samplingTime` 填 20（ADC 时钟周期）。这个值不是随便给的：
 *       MUX（RS2260）的 Ron ≈ 105 Ω 会串进采样网络，源阻抗越高需要的
 *       采样时间越长。20 只是起点，**必须上板扫一遍找收敛点**。
 * @note `refVoltageMv` 填 3300：CVM014x 用 VDDA 做参考时就是 3.3 V。
 *       若板上用的是外部 VREF，这里和 `AdcAc.c` 的 `refVolSel` 必须一起改。
 */
static const Adc_ChannelConfigType Adc_Channels_Probe[] = {
	{
		/* hwChannel    */ 12u,      /* ADC0_SE12 ← PTC14 / AN_POT_1（电位计 1） */
		/* resolution   */ 12u,
		/* samplingTime */ 20u,
		/* refVoltageMv */ 3300u,
		/* diffMode     */ 0u,
	},
};

/** @brief 组表：下标即组号（`ADC_CFG_GROUP_PROBE` = 0） */
static const Adc_GroupConfigType Adc_Groups[ADC_CFG_NUM_GROUPS] = {
	{
		/* channels      */ Adc_Channels_Probe,
		/* numOfChannels */ (uint8_t)ARRAY_SIZE(Adc_Channels_Probe),
		/* hwUnit        */ 0u,                      /* ADC0 */
		/* convMode      */ ADC_CONV_MODE_ONESHOT,
		/* trigSrc       */ ADC_TRIGG_SRC_SW,        /* 内部经 PDB 转发 */
		/* notification  */ NULL,
	},
};

/** @brief 驱动初始化用的唯一配置实例 */
const Adc_ConfigType Adc_Config = {
	Adc_Groups,
	(uint16_t)ARRAY_SIZE(Adc_Groups),
};
