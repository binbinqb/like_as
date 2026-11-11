/*
 * Copyright (c) 2022, Shenzhen CVA Innovation CO.,LTD
 * All rights reserved.
 *
 * Shenzhen CVA Innovation CO.,LTD (CVA chip) is supplying this file for use
 * exclusively with CVA's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * CVA SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */

#ifndef _CVM014X_FEATURES_H_
#define _CVM014X_FEATURES_H_

/*! \brief Contains public interface to various functions related
 *         to the features definition of CVM014x series chips
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

#if defined(MCU_CVM0146FMLQ) || defined(MCU_CVM0146LMLQ)

#ifdef FEATURE_PFLASH_SIZE
#undef FEATURE_PFLASH_SIZE
#endif
#define FEATURE_PFLASH_SIZE (0x100000)

#ifdef FEATURE_RAM_SIZE
#undef FEATURE_RAM_SIZE
#endif
#define FEATURE_RAM_SIZE (0x20000)

#ifdef FEATURE_DFLASH_SIZE
#undef FEATURE_DFLASH_SIZE
#endif
#define FEATURE_DFLASH_SIZE (0x20000)

#ifdef FEATURE_EEPROM_SIZE
#undef FEATURE_EEPROM_SIZE
#endif
#define FEATURE_EEPROM_SIZE (0x1000)

#ifdef FEATURE_CAN_FD_INSTANCE_NUM
#undef FEATURE_CAN_FD_INSTANCE_NUM
#endif
#define FEATURE_CAN_FD_INSTANCE_NUM (4)

#ifdef FEATURE_MFT_INSTANCE_NUM
#undef FEATURE_MFT_INSTANCE_NUM
#endif
#define FEATURE_MFT_INSTANCE_NUM (6)

#ifdef FEATURE_UART_INSTANCE_NUM
#undef FEATURE_UART_INSTANCE_NUM
#endif
#define FEATURE_UART_INSTANCE_NUM (4)

#ifdef FEATURE_SPI_INSTANCE_NUM
#undef FEATURE_SPI_INSTANCE_NUM
#endif
#define FEATURE_SPI_INSTANCE_NUM (4)

#ifdef FEATURE_LAST_IRQn
#undef FEATURE_LAST_IRQn
#endif
#define FEATURE_LAST_IRQn (CAN3_EdgeWakeup_IRQn)

#elif defined(MCU_CVM0146FMLL) || defined(MCU_CVM0146LMLL)

#ifdef FEATURE_PFLASH_SIZE
#undef FEATURE_PFLASH_SIZE
#endif
#define FEATURE_PFLASH_SIZE (0x100000)

#ifdef FEATURE_RAM_SIZE
#undef FEATURE_RAM_SIZE
#endif
#define FEATURE_RAM_SIZE (0x20000)

#ifdef FEATURE_DFLASH_SIZE
#undef FEATURE_DFLASH_SIZE
#endif
#define FEATURE_DFLASH_SIZE (0x20000)

#ifdef FEATURE_EEPROM_SIZE
#undef FEATURE_EEPROM_SIZE
#endif
#define FEATURE_EEPROM_SIZE (0x1000)

#ifdef FEATURE_CAN_FD_INSTANCE_NUM
#undef FEATURE_CAN_FD_INSTANCE_NUM
#endif
#define FEATURE_CAN_FD_INSTANCE_NUM (4)

#ifdef FEATURE_MFT_INSTANCE_NUM
#undef FEATURE_MFT_INSTANCE_NUM
#endif
#define FEATURE_MFT_INSTANCE_NUM (6)

#ifdef FEATURE_UART_INSTANCE_NUM
#undef FEATURE_UART_INSTANCE_NUM
#endif
#define FEATURE_UART_INSTANCE_NUM (4)

#ifdef FEATURE_SPI_INSTANCE_NUM
#undef FEATURE_SPI_INSTANCE_NUM
#endif
#define FEATURE_SPI_INSTANCE_NUM (4)

#ifdef FEATURE_LAST_IRQn
#undef FEATURE_LAST_IRQn
#endif
#define FEATURE_LAST_IRQn (CAN3_EdgeWakeup_IRQn)

#elif defined(MCU_CVM0146FMLH) || defined(MCU_CVM0146LMLH)

#ifdef FEATURE_PFLASH_SIZE
#undef FEATURE_PFLASH_SIZE
#endif
#define FEATURE_PFLASH_SIZE (0x100000)

#ifdef FEATURE_RAM_SIZE
#undef FEATURE_RAM_SIZE
#endif
#define FEATURE_RAM_SIZE (0x20000)

#ifdef FEATURE_DFLASH_SIZE
#undef FEATURE_DFLASH_SIZE
#endif
#define FEATURE_DFLASH_SIZE (0x20000)

#ifdef FEATURE_EEPROM_SIZE
#undef FEATURE_EEPROM_SIZE
#endif
#define FEATURE_EEPROM_SIZE (0x1000)

#ifdef FEATURE_CAN_FD_INSTANCE_NUM
#undef FEATURE_CAN_FD_INSTANCE_NUM
#endif
#define FEATURE_CAN_FD_INSTANCE_NUM (3)

#ifdef FEATURE_MFT_INSTANCE_NUM
#undef FEATURE_MFT_INSTANCE_NUM
#endif
#define FEATURE_MFT_INSTANCE_NUM (4)

#ifdef FEATURE_UART_INSTANCE_NUM
#undef FEATURE_UART_INSTANCE_NUM
#endif
#define FEATURE_UART_INSTANCE_NUM (3)

#ifdef FEATURE_SPI_INSTANCE_NUM
#undef FEATURE_SPI_INSTANCE_NUM
#endif
#define FEATURE_SPI_INSTANCE_NUM (3)

#ifdef FEATURE_LAST_IRQn
#undef FEATURE_LAST_IRQn
#endif
#define FEATURE_LAST_IRQn (CAN2_EdgeWakeup_IRQn)

#elif defined(MCU_CVM0144FMLL) || defined(MCU_CVM0144LMLL)

#ifdef FEATURE_PFLASH_SIZE
#undef FEATURE_PFLASH_SIZE
#endif
#define FEATURE_PFLASH_SIZE (0x80000)

#ifdef FEATURE_RAM_SIZE
#undef FEATURE_RAM_SIZE
#endif
#define FEATURE_RAM_SIZE (0x20000)

#ifdef FEATURE_DFLASH_SIZE
#undef FEATURE_DFLASH_SIZE
#endif
#define FEATURE_DFLASH_SIZE (0x10000)

#ifdef FEATURE_EEPROM_SIZE
#undef FEATURE_EEPROM_SIZE
#endif
#define FEATURE_EEPROM_SIZE (0x1000)

#ifdef FEATURE_CAN_FD_INSTANCE_NUM
#undef FEATURE_CAN_FD_INSTANCE_NUM
#endif
#define FEATURE_CAN_FD_INSTANCE_NUM (4)

#ifdef FEATURE_MFT_INSTANCE_NUM
#undef FEATURE_MFT_INSTANCE_NUM
#endif
#define FEATURE_MFT_INSTANCE_NUM (4)

#ifdef FEATURE_UART_INSTANCE_NUM
#undef FEATURE_UART_INSTANCE_NUM
#endif
#define FEATURE_UART_INSTANCE_NUM (4)

#ifdef FEATURE_SPI_INSTANCE_NUM
#undef FEATURE_SPI_INSTANCE_NUM
#endif
#define FEATURE_SPI_INSTANCE_NUM (4)

#ifdef FEATURE_LAST_IRQn
#undef FEATURE_LAST_IRQn
#endif
#define FEATURE_LAST_IRQn (CAN3_EdgeWakeup_IRQn)

#elif defined(MCU_CVM0144FMLH) || defined(MCU_CVM0144LMLH)

#ifdef FEATURE_PFLASH_SIZE
#undef FEATURE_PFLASH_SIZE
#endif
#define FEATURE_PFLASH_SIZE (0x80000)

#ifdef FEATURE_RAM_SIZE
#undef FEATURE_RAM_SIZE
#endif
#define FEATURE_RAM_SIZE (0x20000)

#ifdef FEATURE_DFLASH_SIZE
#undef FEATURE_DFLASH_SIZE
#endif
#define FEATURE_DFLASH_SIZE (0x10000)

#ifdef FEATURE_EEPROM_SIZE
#undef FEATURE_EEPROM_SIZE
#endif
#define FEATURE_EEPROM_SIZE (0x1000)

#ifdef FEATURE_CAN_FD_INSTANCE_NUM
#undef FEATURE_CAN_FD_INSTANCE_NUM
#endif
#define FEATURE_CAN_FD_INSTANCE_NUM (3)

#ifdef FEATURE_MFT_INSTANCE_NUM
#undef FEATURE_MFT_INSTANCE_NUM
#endif
#define FEATURE_MFT_INSTANCE_NUM (4)

#ifdef FEATURE_UART_INSTANCE_NUM
#undef FEATURE_UART_INSTANCE_NUM
#endif
#define FEATURE_UART_INSTANCE_NUM (3)

#ifdef FEATURE_SPI_INSTANCE_NUM
#undef FEATURE_SPI_INSTANCE_NUM
#endif
#define FEATURE_SPI_INSTANCE_NUM (3)

#ifdef FEATURE_LAST_IRQn
#undef FEATURE_LAST_IRQn
#endif
#define FEATURE_LAST_IRQn (CAN2_EdgeWakeup_IRQn)

#elif defined(MCU_CVM0142FMLH) || defined(MCU_CVM0142LMLH)

#ifdef FEATURE_PFLASH_SIZE
#undef FEATURE_PFLASH_SIZE
#endif
#define FEATURE_PFLASH_SIZE (0x40000)

#ifdef FEATURE_RAM_SIZE
#undef FEATURE_RAM_SIZE
#endif
#define FEATURE_RAM_SIZE (0x10000)

#ifdef FEATURE_DFLASH_SIZE
#undef FEATURE_DFLASH_SIZE
#endif
#define FEATURE_DFLASH_SIZE (0x10000)

#ifdef FEATURE_EEPROM_SIZE
#undef FEATURE_EEPROM_SIZE
#endif
#define FEATURE_EEPROM_SIZE (0x1000)

#ifdef FEATURE_CAN_FD_INSTANCE_NUM
#undef FEATURE_CAN_FD_INSTANCE_NUM
#endif
#define FEATURE_CAN_FD_INSTANCE_NUM (3)

#ifdef FEATURE_MFT_INSTANCE_NUM
#undef FEATURE_MFT_INSTANCE_NUM
#endif
#define FEATURE_MFT_INSTANCE_NUM (4)

#ifdef FEATURE_UART_INSTANCE_NUM
#undef FEATURE_UART_INSTANCE_NUM
#endif
#define FEATURE_UART_INSTANCE_NUM (3)

#ifdef FEATURE_SPI_INSTANCE_NUM
#undef FEATURE_SPI_INSTANCE_NUM
#endif
#define FEATURE_SPI_INSTANCE_NUM (3)

#ifdef FEATURE_LAST_IRQn
#undef FEATURE_LAST_IRQn
#endif
#define FEATURE_LAST_IRQn (CAN2_EdgeWakeup_IRQn)

#else
#error "No correct chip defined"
#endif

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CVM014X_FEATURES_H_ */
