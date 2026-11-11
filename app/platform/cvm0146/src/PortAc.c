/**
 * @file    PortAc.c
 * @brief   Port 驱动的平台访问层（AUTOSAR PortAc → 厂商 PinsDrv）
 *
 * @details 只做一件事：把 AS 的 `Port_PortPinConfigType`（端口号 0~4 + 引脚号 + MUX 值）
 *          翻译成厂商 `PinsDrv_SetMuxModeSel()` 的调用参数。
 *
 *          | AS 配置字段 | 厂商调用 |
 *          |-------------|----------|
 *          | `port` (0~4) | 选 `g_mcu.pta..pte` |
 *          | `pin`        | `PinsDrv_SetPinDirection/WritePin` 的 pin |
 *          | `mode`       | `PinsDrv_SetMuxModeSel` 的 MUX（1=GPIO, 2~7=ALTn） |
 *          | `pinDirection` | IN/OUT；`PORT_PIN_UNUSED` 表示只配 MUX 不碰方向 |
 *
 *          @section PORTAC_WHY 为什么不直接用 Dio 配引脚
 *          AUTOSAR 的分工是：**Port 负责 MUX/方向/初始电平，Dio 只负责读写电平**。
 *          把 MUX 配置混进 Dio 会导致"第一次写引脚时才发现方向没配"，
 *          而且 Dio 的通道表里会出现一堆与逻辑无关的端口细节。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：MUX + 方向 + 初始电平 |
 */

#include "Port.h"
#include "Port_Priv.h"

#include "platform_priv.h"

/* ============================ [ 对外接口 ] ============================ */

void PortAc_PinInit(Port_PinType pinId, const Port_PortPinConfigType *config)
{
	PinsDrvType *pPort;

	if (config == NULL) {
		return;
	}

	pPort = Platform_GetPort(config->port);
	if (pPort == NULL) {
		/* 端口号写错：跳过这一根脚。不停机——配置表的一处笔误不该让整块板子挂住 */
		return;
	}

	(void)pinId;   /* AS 只把它当序号传下来，真正的端口/引脚在 config 里 */

	/* 1) MUX：必须先配 MUX，否则后面的方向/电平写的是"别的功能"的寄存器 */
	PinsDrv_SetMuxModeSel(pPort, (uint32_t)config->pin, (PinsDrv_MuxType)config->mode);

	/* 2) 方向：UNUSED 表示该脚只做复用输出（如 CAN TX），不需要 GPIO 方向 */
	if (config->pinDirection != PORT_PIN_UNUSED) {
		PinsDrv_SetPinDirection(pPort, (uint32_t)config->pin,
		                        (config->pinDirection == PORT_PIN_OUT) ? 1u : 0u);

		/* 3) 初始电平：只对输出脚有意义，且必须在方向设为输出之后写 */
		if (config->pinDirection == PORT_PIN_OUT) {
			PinsDrv_WritePin(pPort, (uint32_t)config->pin,
			                 (config->pinLevel == PORT_PIN_LEVEL_HIGH) ? 1u : 0u);
		}
	}
}
