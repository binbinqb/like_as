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
#include "Board_Cfg.h"   /* BOARD_PINS_TABLE（Board.json 生成） */

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
	/* 表体来自 config/Board/Board.json 的 pins（Board_Cfg.h 生成宏）。
	 * 改引脚只改 JSON；数量由 PORT_CFG_NUM_PINS 在编译期对上。 */
	BOARD_PINS_TABLE
};
const Port_ConfigType Port_Config = {
	Port_PortPinConfigs,
	(uint16_t)ARRAY_SIZE(Port_PortPinConfigs),
};
