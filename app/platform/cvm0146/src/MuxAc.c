/**
 * @file    MuxAc.c
 * @brief   MuxManager 的目标板 HwOps（Dio 已接，ADC 待实装）
 *
 * @details @section MUXAC_WHY 为什么配置表在这里是空的
 *
 *          `Mux_BusCfgs` / `Mux_DeviceCfgs` 将来由 `Board.json` 的
 *          `selectBuses` / `devices` 生成。当前**没有 RS2260 实物**，
 *          也没有确定的引脚分配，所以先给一份"零设备"的定义：
 *          状态机在 `Mux_DeviceCount == 0` 时直接停在 IDLE，不产生任何
 *          Dio/Adc 访问。
 *
 *          这样做的好处是：链接与编译期就能发现接口不一致，而不会在
 *          加器件时才暴露；同时目标板上不会因为"空扫"去动 LED 引脚。
 *
 *          @section MUXAC_ADC ADC 路径为什么还没接
 *
 *          MUX 的 ADC COM 与直连 AIN 是**同一个前置**：需要先定 ADC 组表
 *          与"取上次转换结果"的读取方式（见 `IoHwAbAc.c` 的 `iohwabac_AinReadRaw`
 *          注释）。这两个一起做才有意义，所以这里显式返回 `E_NOT_OK`，
 *          **不假装能采**。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：Dio 选择线/INH/GPIO 读；ADC 显式未实现 |
 */

#include "mux.h"

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

/* ============================ [ ADC：显式未实现 ] ============================ */

static Std_ReturnType muxac_AdcStart(uint16 ch)
{
	(void)ch;
	return E_NOT_OK;    /* 与直连 AIN 同批实装（见文件头 §MUXAC_ADC） */
}

static Std_ReturnType muxac_AdcReady(uint16 ch, boolean *ready)
{
	(void)ch;
	(void)ready;
	return E_NOT_OK;
}

static Std_ReturnType muxac_AdcRead(uint16 ch, uint16 *raw)
{
	(void)ch;
	(void)raw;
	return E_NOT_OK;
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
