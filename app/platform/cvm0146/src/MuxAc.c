/**
 * @file    MuxAc.c
 * @brief   MuxManager 的目标板 HwOps（Dio + Adc）
 *
 * @details @section MUXAC_WHY 配置表不在这里
 *
 *          `Mux_BusCfgs` / `Mux_DeviceCfgs` 由 `Board.json` 的
 *          `selectBuses` / `devices` 生成到 `config/Board/GEN/Mux_Cfg.c`。
 *          当前**没有 RS2260 实物**，那两张表是空的：状态机停在 IDLE，
 *          不产生任何 Dio/Adc 访问，也不去动 LED 引脚。
 *
 *          @section MUXAC_ADC ADC 路径
 *
 *          `Adc_ReadGroup()` 只在组状态为 `ADC_COMPLETED` 时返回结果，
 *          且**不会重新触发转换**（重新触发只在 `Adc_StartGroupConversion`）。
 *          所以 MuxManager 的 START/WAIT/READ 三步可以直接映射：
 *          Start → `Adc_StartGroupConversion`；Ready → `Adc_GetGroupStatus`；
 *          Read → `Adc_ReadGroup` + 取槽位。
 *
 *          @warning **未在实物上验证**（没有 RS2260）。另外这一组 ADC
 *          不能被 `AdcSampler` 同时使用 —— 组所有权由生成器 R15 校验。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：Dio 选择线/INH/GPIO 读；ADC 显式未实现 |
 * | V1.1.1 | 2026-11-18 | binbina | ADC 接 Adc HAL（Start/Status/ReadGroup），组所有权交生成器校验 |
 */

#include "mux.h"

#include "Adc.h"
#include "Adc_Cfg.h"
#include "Dio.h"

/* ============================ [ Dio 访问 ] ============================ */

/**
 * @brief 写一条总线的 A/B/C
 * @param[in] bus 总线索引
 * @param[in] abc bit0/1/2 = A/B/C
 */
static void muxac_SelectWrite(uint8 bus, uint8 abc)
{
	if (bus >= Mux_BusCount) {
		return;
	}
	Dio_WriteChannel((Dio_ChannelType)Mux_BusCfgs[bus].pinA,
	                 ((abc & 0x01u) != 0u) ? STD_HIGH : STD_LOW);
	Dio_WriteChannel((Dio_ChannelType)Mux_BusCfgs[bus].pinB,
	                 ((abc & 0x02u) != 0u) ? STD_HIGH : STD_LOW);
	Dio_WriteChannel((Dio_ChannelType)Mux_BusCfgs[bus].pinC,
	                 ((abc & 0x04u) != 0u) ? STD_HIGH : STD_LOW);
}

/**
 * @brief 写 INH
 * @param[in] ch    Dio 通道
 * @param[in] level 有效电平（1 = 高）
 */
static void muxac_InhWrite(uint8 ch, uint8 level)
{
	Dio_WriteChannel((Dio_ChannelType)ch,
	                 (level != 0u) ? STD_HIGH : STD_LOW);
}

/**
 * @brief 读 COM 引脚电平
 * @param[in]  ch    Dio 通道
 * @param[out] level 电气电平
 * @return E_OK / E_NOT_OK
 */
static Std_ReturnType muxac_GpioRead(uint16 ch, boolean *level)
{
	if (level == NULL) {
		return E_NOT_OK;
	}
	*level = (Dio_ReadChannel((Dio_ChannelType)ch) == STD_HIGH) ? TRUE : FALSE;
	return E_OK;
}

/* ============================ [ ADC ] ============================ */

/** @brief 整组读取缓冲（MUX 一次只关心槽位 slot，但 HAL 是整组读） */
static uint16 s_adcBuf[ADC_CFG_MAX_CH_PER_GROUP];

/**
 * @brief 启动 MUX 所在组的转换
 * @param[in] ch `(group << 8) | slot`
 * @return E_OK
 * @note  HAL 的启动接口无返回值，失败只能在 `muxac_AdcReady` 一直不就绪时
 *        由状态机的超时机制暴露。
 */
static Std_ReturnType muxac_AdcStart(uint16 ch)
{
	Adc_StartGroupConversion((Adc_GroupType)(ch >> 8));
	return E_OK;
}

/**
 * @brief 查询组转换是否完成
 * @param[in]  ch    `(group << 8) | slot`
 * @param[out] ready TRUE = 可读
 * @return E_OK / E_NOT_OK
 */
static Std_ReturnType muxac_AdcReady(uint16 ch, boolean *ready)
{
	if (ready == NULL) {
		return E_NOT_OK;
	}
	*ready = (Adc_GetGroupStatus((Adc_GroupType)(ch >> 8)) == ADC_COMPLETED)
	         ? TRUE : FALSE;
	return E_OK;
}

/**
 * @brief 取本槽位的原始值
 * @param[in]  ch  `(group << 8) | slot`
 * @param[out] raw 原始值
 * @return E_OK / E_NOT_OK
 * @warning **未在实物上验证**（无 RS2260）。逻辑上只在 `muxac_AdcReady`
 *          返回 TRUE 后调用，此时 `Adc_ReadGroup` 才会返回结果；
 *          组所有权由生成器 R15 保证不会与 `AdcSampler` 抢同一组。
 */
static Std_ReturnType muxac_AdcRead(uint16 ch, uint16 *raw)
{
	uint8 slot;

	if (raw == NULL) {
		return E_NOT_OK;
	}
	if (Adc_ReadGroup((Adc_GroupType)(ch >> 8), s_adcBuf) != E_OK) {
		return E_NOT_OK;
	}
	slot = (uint8)(ch & 0xFFu);
	if (slot >= ADC_CFG_MAX_CH_PER_GROUP) {
		return E_NOT_OK;
	}
	*raw = s_adcBuf[slot];
	return E_OK;
}

/* ============================ [ 实例 ] ============================ */

/*
 * `Mux_BusCfgs` / `Mux_DeviceCfgs` / 两个计数由生成器写到
 * `config/Board/GEN/Mux_Cfg.c`（源：Board.json 的 selectBuses / devices）。
 * 本文件只提供硬件访问表，**不要**在这里再定义配置表 —— 那会和生成物冲突。
 */

const Mux_HwOpsType Mux_HwOps = {
	muxac_SelectWrite,
	muxac_InhWrite,
	muxac_GpioRead,
	muxac_AdcStart,
	muxac_AdcReady,
	muxac_AdcRead
};
