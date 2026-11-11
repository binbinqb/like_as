/**
 * @file    Port_Cfg.c
 * @brief   引脚复用/方向/初始电平表
 *
 * @details 这是**唯一**决定"某根引脚做什么用"的地方。`Dio_Cfg.c` 只描述通道，
 *          真正写 MUX 寄存器的是这里，由 `Port_Init()` 在启动时一次性完成。
 *
 *          @section PORTCFG_MUX MUX 值从哪来
 *          `PINSDRV_MUX_AS_GPIO = 1`，`ALT2..ALT7 = 2..7`，与厂商 `pins_drv.h` 一致。
 *          CAN0 的 PTE4/PTE5 是 ALT5（照厂商 `flexcan_tx_rx_mb` 例程）。
 *
 *          @section PORTCFG_STB STB 为什么初始给 HIGH
 *          TJA1044 的 STB：**低=Normal，高=Standby**。上电先停在待机，
 *          等软件显式调用 `CanIf_SetTrcvMode(NORMAL)` 才上总线 ——
 *          避免初始化未完成就往总线上发垃圾帧（真实 ECU 的必要行为，台架上更安全）。
 *
 *          @section PORTCFG_LED LED 为什么初始给 HIGH
 *          本板三色灯是**低电平点亮**，给 HIGH 即"上电全灭"，便于肉眼确认复位发生过。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：CAN0 两脚 + STB + 三色灯 |
 */

#include "Port.h"
#include "Port_Cfg.h"
#include "Port_Priv.h"

/* ============================ [ 数据 ] ============================ */

/**
 * @brief 引脚表
 * @note  `PORT_PIN_DEF(pinMode, pinDirection, pinLevel, port, pin, mux)`
 *        - `pinMode`：AUTOSAR 逻辑用途（CAN/DIO/...），仅作记录
 *        - `pinDirection`：IN / OUT / UNUSED（UNUSED = 只配 MUX，不碰 GPIO 方向）
 *        - `pinLevel`：初始电平（只对 OUT 有效）
 *        - `port`：`PORT_PORT_x`；`pin`：引脚号；`mux`：厂商 MUX 值
 */
static const Port_PortPinConfigType Port_PortPinConfigs[PORT_CFG_NUM_PINS] = {
	/* ---- CAN0（通信 1）：PTE4/PTE5，ALT5 已在 M1 上板验证 ---- */
	/* PTE4 = CAN0_RX，ALT5；方向由 CAN 外设接管，不走 GPIO */
	PORT_PIN_DEF(CAN,   UNUSED, LOW,  PORT_PORT_E, 4u,  5u),
	/* PTE5 = CAN0_TX，ALT5 */
	PORT_PIN_DEF(CAN,   UNUSED, LOW,  PORT_PORT_E, 5u,  5u),

	/* PTC1 = CAN0 STB，GPIO 输出，上电待机（HIGH） */
	PORT_PIN_DEF(DIO,   OUT,    HIGH, PORT_PORT_C, 1u,  1u),

	/* ---- CAN1（通信 2）：PTC6/PTC7，ALT3 ----
	 * 依据：《CVM0146 开发板快速入门》表 8 + 本板 PinMux 表（cvm0146）
	 *   PTC6: DEFAULT=ADC1_SE4 / ALT0=ADC1_SE4 / ALT1=PTC6 / ALT2=UART1_RX / **ALT3=CAN1_RX**
	 *   PTC7: DEFAULT=ADC1_SE5 / ALT0=ADC1_SE5 / ALT1=PTC7 / ALT2=UART1_TX / **ALT3=CAN1_TX**
	 * ⚠ 与 CAN0 的 ALT5 不同，不能照抄 */
	PORT_PIN_DEF(CAN,   UNUSED, LOW,  PORT_PORT_C, 6u,  3u),   /* PTC6 = CAN1_RX */
	PORT_PIN_DEF(CAN,   UNUSED, LOW,  PORT_PORT_C, 7u,  3u),   /* PTC7 = CAN1_TX */

	/* PTE13 = CAN1 STB，GPIO 输出，上电待机（HIGH，1=STANDBY） */
	PORT_PIN_DEF(DIO,   OUT,    HIGH, PORT_PORT_E, 13u, 1u),

	/* ---- 三色灯：低电平点亮，上电全灭 ---- */
	PORT_PIN_DEF(DIO,   OUT,    HIGH, PORT_PORT_D, 1u,  1u),   /* PTD1 红 */
	PORT_PIN_DEF(DIO,   OUT,    HIGH, PORT_PORT_D, 3u,  1u),   /* PTD3 绿 */
	PORT_PIN_DEF(DIO,   OUT,    HIGH, PORT_PORT_A, 17u, 1u),   /* PTA17 蓝 */
};

const Port_ConfigType Port_Config = {
	Port_PortPinConfigs,
	(uint16_t)ARRAY_SIZE(Port_PortPinConfigs),
};
