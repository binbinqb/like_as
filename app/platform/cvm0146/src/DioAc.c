/**
 * @file    DioAc.c
 * @brief   Dio 驱动的平台访问层（AUTOSAR DioAc → 厂商 PinsDrv）
 *
 * @details 只做电平读写，**不碰 MUX 和方向**——那是 `PortAc_PinInit()` 的职责。
 *          这个分工是 AUTOSAR 的约定，好处是：MUX 表与逻辑表分离，
 *          换板子时只改 Port_Cfg，业务代码里的 Dio 通道号不用动。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：通道读写 |
 */

#include "Dio.h"
#include "Dio_Priv.h"

#include "platform_priv.h"

/* ============================ [ 对外接口 ] ============================ */

void DioAc_WriteChannel(Dio_ChannelType ChannelId, const Dio_ChannelConfigType *config,
                        Dio_LevelType Level)
{
	PinsDrvType *pPort;

	if (config == NULL) {
		return;
	}

	pPort = Platform_GetPort(config->port);
	if (pPort == NULL) {
		return;
	}

	(void)ChannelId;
	PinsDrv_WritePin(pPort, (uint32_t)config->pin, (Level == STD_HIGH) ? 1u : 0u);
}

Dio_LevelType DioAc_ReadChannel(Dio_ChannelType ChannelId, const Dio_ChannelConfigType *config)
{
	PinsDrvType *pPort;

	if (config == NULL) {
		return STD_LOW;
	}

	pPort = Platform_GetPort(config->port);
	if (pPort == NULL) {
		return STD_LOW;
	}

	(void)ChannelId;
	return (PinsDrv_ReadPin(pPort, (uint32_t)config->pin) != 0u) ? STD_HIGH : STD_LOW;
}
