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

#ifndef _CVM014X_H_
#define _CVM014X_H_

/*! \brief Contains public interface to various functions related
 *         to all the registers of CVM014x series chips
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the Interrupt Number Definition
 ******************************************************************************/

typedef enum
{
    /* Auxiliary constants */
    NotAvail_IRQn = -128, /*!< Not available device specific interrupt */

    /* Core interrupts */
    NonMaskableInt_IRQn   = -14, /*!< Non Maskable Interrupt */
    HardFault_IRQn        = -13, /*!< SV Hard Fault Interrupt */
    MemoryManagement_IRQn = -12, /*!< Memory Management Interrupt */
    BusFault_IRQn         = -11, /*!< Bus Fault Interrupt */
    UsageFault_IRQn       = -10, /*!< Usage Fault Interrupt */
    SVCall_IRQn           = -5,  /*!< SV Call Interrupt */
    DebugMonitor_IRQn     = -4,  /*!< Debug Monitor Interrupt */
    PendSV_IRQn           = -2,  /*!< Pend SV Interrupt */
    SysTick_IRQn          = -1,  /*!< System Tick Interrupt */

    /* Device specific interrupts */
    DMA0_IRQn               = 0u,   /*!< DMA channel 0 transfer complete */
    DMA1_IRQn               = 1u,   /*!< DMA channel 1 transfer complete */
    DMA2_IRQn               = 2u,   /*!< DMA channel 2 transfer complete */
    DMA3_IRQn               = 3u,   /*!< DMA channel 3 transfer complete */
    DMA4_IRQn               = 4u,   /*!< DMA channel 4 transfer complete */
    DMA5_IRQn               = 5u,   /*!< DMA channel 5 transfer complete */
    DMA6_IRQn               = 6u,   /*!< DMA channel 6 transfer complete */
    DMA7_IRQn               = 7u,   /*!< DMA channel 7 transfer complete */
    DMA8_IRQn               = 8u,   /*!< DMA channel 8 transfer complete */
    DMA9_IRQn               = 9u,   /*!< DMA channel 9 transfer complete */
    DMA10_IRQn              = 10u,  /*!< DMA channel 10 transfer complete */
    DMA11_IRQn              = 11u,  /*!< DMA channel 11 transfer complete */
    DMA12_IRQn              = 12u,  /*!< DMA channel 12 transfer complete */
    DMA13_IRQn              = 13u,  /*!< DMA channel 13 transfer complete */
    DMA14_IRQn              = 14u,  /*!< DMA channel 14 transfer complete */
    DMA15_IRQn              = 15u,  /*!< DMA channel 15 transfer complete */
    DMA_Error_IRQn          = 16u,  /*!< DMA error interrupt channels 0-15 */
    MCM_IRQn                = 17u,  /*!< FPU sources */
    FTFC_IRQn               = 18u,  /*!< FTFC Command complete */
    FTFC_ReadCollision_IRQn = 19u,  /*!< FTFC Read collision */
    FTFC_Fault_IRQn         = 21u,  /*!< FTFC Double bit fault detect */
    WDOG_IRQn               = 22u,  /*!< Interrupt request out before wdg reset out */
    EWM_IRQn                = 23u,  /*!< EWM output as interrupt */
    RCM_IRQn                = 24u,  /*!< RCM Asynchronous Interrupt */
    I2C0_IRQn               = 25u,  /*!< I2C0 Interrupt */
    SPI0_IRQn               = 26u,  /*!< SPI0 Interrupt */
    SPI1_IRQn               = 27u,  /*!< SPI1 Interrupt */
    SPI2_IRQn               = 28u,  /*!< SPI2 Interrupt */
    SPI3_IRQn               = 29u,  /*!< SPI3 Interrupt */
    UART0_RxTx_IRQn         = 31u,  /*!< UART0 Transmit / Receive Interrupt */
    UART1_RxTx_IRQn         = 32u,  /*!< UART1 Transmit / Receive Interrupt */
    UART2_RxTx_IRQn         = 33u,  /*!< UART2 Transmit / Receive Interrupt */
    UART3_RxTx_IRQn         = 34u,  /*!< UART3 Transmit / Receive Interrupt */
    FCCU_IRQn               = 35u,  /*!< FCCU Interrupt */
    FCCU_CfgTO_IRQn         = 36u,  /*!< FCCU Configuration Timeout Interrupt */
    PRNG_IRQn               = 37u,  /*!< PRNG Interrupt */
    CSE_IRQn                = 38u,  /*!< CSEc Interrupt */
    ADC0_IRQn               = 39u,  /*!< ADC0 interrupt request. */
    ADC1_IRQn               = 40u,  /*!< ADC1 interrupt request. */
    PDB0_IRQn               = 41u,  /*!< PDB0 interrupt */
    PDB1_IRQn               = 42u,  /*!< PDB1 interrupt */
    CMP0_IRQn               = 43u,  /*!< CMP0 interrupt request */
    LPTMR0_IRQn             = 45u,  /*!< LPTIMER interrupt request */
    RTC_Alarm_IRQn          = 46u,  /*!< RTC alarm interrupt */
    RTC_Seconds_IRQn        = 47u,  /*!< RTC seconds interrupt */
    LPIT0_Ch0_IRQn          = 48u,  /*!< LPIT0 channel 0 overflow interrupt */
    LPIT0_Ch1_IRQn          = 49u,  /*!< LPIT0 channel 1 overflow interrupt */
    LPIT0_Ch2_IRQn          = 50u,  /*!< LPIT0 channel 2 overflow interrupt */
    LPIT0_Ch3_IRQn          = 51u,  /*!< LPIT0 channel 3 overflow interrupt */
    PORTA_IRQn              = 53u,  /*!< Port A pin detect interrupt */
    PORTB_IRQn              = 54u,  /*!< Port B pin detect interrupt */
    PORTC_IRQn              = 55u,  /*!< Port C pin detect interrupt */
    PORTD_IRQn              = 56u,  /*!< Port D pin detect interrupt */
    PORTE_IRQn              = 57u,  /*!< Port E pin detect interrupt */
    I2S_Slave_IRQn          = 58u,  /*!< I2S Slave interrupt */
    I2S_Master_IRQn         = 59u,  /*!< I2S Master interrupt */
    MFT0_Ch0_Ch1_IRQn       = 60u,  /*!< MFT0 Channel 0 and 1 interrupt */
    MFT0_Ch2_Ch3_IRQn       = 61u,  /*!< MFT0 Channel 2 and 3 interrupt */
    MFT0_Ch4_Ch5_IRQn       = 62u,  /*!< MFT0 Channel 4 and 5 interrupt */
    MFT0_Ch6_Ch7_IRQn       = 63u,  /*!< MFT0 Channel 6 and 7 interrupt */
    MFT0_Fault_IRQn         = 64u,  /*!< MFT0 Fault interrupt */
    MFT0_Ovf_Reload_IRQn    = 65u,  /*!< MFT0 Counter overflow and Reload interrupt */
    MFT1_Ch0_Ch1_IRQn       = 66u,  /*!< MFT1 Channel 0 and 1 interrupt */
    MFT1_Ch2_Ch3_IRQn       = 67u,  /*!< MFT1 Channel 2 and 3 interrupt */
    MFT1_Ch4_Ch5_IRQn       = 68u,  /*!< MFT1 Channel 4 and 5 interrupt */
    MFT1_Ch6_Ch7_IRQn       = 69u,  /*!< MFT1 Channel 6 and 7 interrupt */
    MFT1_Fault_IRQn         = 70u,  /*!< MFT1 Fault interrupt */
    MFT1_Ovf_Reload_IRQn    = 71u,  /*!< MFT1 Counter overflow and Reload interrupt */
    MFT2_Ch0_Ch1_IRQn       = 72u,  /*!< MFT2 Channel 0 and 1 interrupt */
    MFT2_Ch2_Ch3_IRQn       = 73u,  /*!< MFT2 Channel 2 and 3 interrupt */
    MFT2_Ch4_Ch5_IRQn       = 74u,  /*!< MFT2 Channel 4 and 5 interrupt */
    MFT2_Ch6_Ch7_IRQn       = 75u,  /*!< MFT2 Channel 6 and 7 interrupt */
    MFT2_Fault_IRQn         = 76u,  /*!< MFT2 Fault interrupt */
    MFT2_Ovf_Reload_IRQn    = 77u,  /*!< MFT2 Counter overflow and Reload interrupt */
    MFT3_Ch0_Ch1_IRQn       = 78u,  /*!< MFT3 Channel 0 and 1 interrupt */
    MFT3_Ch2_Ch3_IRQn       = 79u,  /*!< MFT3 Channel 2 and 3 interrupt */
    MFT3_Ch4_Ch5_IRQn       = 80u,  /*!< MFT3 Channel 4 and 5 interrupt */
    MFT3_Ch6_Ch7_IRQn       = 81u,  /*!< MFT3 Channel 6 and 7 interrupt */
    MFT3_Fault_IRQn         = 82u,  /*!< MFT3 Fault interrupt */
    MFT3_Ovf_Reload_IRQn    = 83u,  /*!< MFT3 Counter overflow and Reload interrupt */
    MFT4_Ch0_Ch1_IRQn       = 84u,  /*!< MFT3 Channel 0 and 1 interrupt */
    MFT4_Ch2_Ch3_IRQn       = 85u,  /*!< MFT3 Channel 2 and 3 interrupt */
    MFT4_Ch4_Ch5_IRQn       = 86u,  /*!< MFT3 Channel 4 and 5 interrupt */
    MFT4_Ch6_Ch7_IRQn       = 87u,  /*!< MFT3 Channel 6 and 7 interrupt */
    MFT4_Fault_IRQn         = 88u,  /*!< MFT3 Fault interrupt */
    MFT4_Ovf_Reload_IRQn    = 89u,  /*!< MFT3 Counter overflow and Reload interrupt */
    MFT5_Ch0_Ch1_IRQn       = 90u,  /*!< MFT3 Channel 0 and 1 interrupt */
    MFT5_Ch2_Ch3_IRQn       = 91u,  /*!< MFT3 Channel 2 and 3 interrupt */
    MFT5_Ch4_Ch5_IRQn       = 92u,  /*!< MFT3 Channel 4 and 5 interrupt */
    MFT5_Ch6_Ch7_IRQn       = 93u,  /*!< MFT3 Channel 6 and 7 interrupt */
    MFT5_Fault_IRQn         = 94u,  /*!< MFT3 Fault interrupt */
    MFT5_Ovf_Reload_IRQn    = 95u,  /*!< MFT3 Counter overflow and Reload interrupt */
    CMU_Firc_IRQn           = 96u,  /*!< CMU FIRC interrupt */
    CMU_Pll_IRQn            = 97u,  /*!< CMU PLL interrupt */
    CMU_Sosc_IRQn           = 98u,  /*!< CMU SOSC interrupt */
    CAN0_ORed_IRQn          = 100u, /*!< CAN0 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    CAN0_Error_IRQn         = 101u, /*!< CAN0 Interrupt indicating that errors were detected on the CAN bus */
    CAN0_FrameWakeup_IRQn   = 102u, /*!< CAN0 Pretended Networking operation is enabled, and a valid message match or timeout during Low Power mode */
    CAN0_ORed_0_15_MB_IRQn  = 103u, /*!< CAN0 OR'ed Message buffer (0-15) */
    CAN0_ORed_16_31_MB_IRQn = 104u, /*!< CAN0 OR'ed Message buffer (16-31) */
    CAN0_ORed_32_47_MB_IRQn = 105u, /*!< CAN0 OR'ed Message buffer (32-47) */
    CAN0_ORed_48_63_MB_IRQn = 106u, /*!< CAN0 OR'ed Message buffer (48-63) */
    CAN0_ORed_64_79_MB_IRQn = 107u, /*!< CAN0 OR'ed Message buffer (64-79) */
    CAN0_ORed_80_95_MB_IRQn = 108u, /*!< CAN0 OR'ed Message buffer (80-95) */
    CAN0_EdgeWakeup_IRQn    = 109u, /*!< CAN0 self wakeup by edge */
    CAN0_EccErr_IRQn        = 110u, /*!< CAN0 ECC error */
    CAN0_ERxFIFO_IRQn       = 111u, /*!< CAN0 Enhanced Rx FIFO related interrupts */
    CAN1_ORed_IRQn          = 112u, /*!< CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    CAN1_Error_IRQn         = 113u, /*!< CAN1 Interrupt indicating that errors were detected on the CAN bus */
    CAN1_EccErr_IRQn        = 114u, /*!< CAN1 ECC error */
    CAN1_ORed_0_15_MB_IRQn  = 115u, /*!< CAN1 OR'ed Interrupt for Message buffer (0-15) */
    CAN1_ORed_16_31_MB_IRQn = 116u, /*!< CAN1 OR'ed Interrupt for Message buffer (16-31) */
    CAN1_ORed_32_47_MB_IRQn = 117u, /*!< CAN1 OR'ed Message buffer (32-47) */
    CAN1_ORed_48_63_MB_IRQn = 118u, /*!< CAN1 OR'ed Message buffer (48-63) */
    CAN1_EdgeWakeup_IRQn    = 119u, /*!< CAN1 self wakeup by edge */
    CAN2_ORed_IRQn          = 120u, /*!< CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    CAN2_Error_IRQn         = 121u, /*!< CAN2 Interrupt indicating that errors were detected on the CAN bus */
    CAN2_EccErr_IRQn        = 122u, /*!< CAN2 ECC error */
    CAN2_ORed_0_15_MB_IRQn  = 123u, /*!< CAN2 OR'ed Message buffer (0-15) */
    CAN2_ORed_16_31_MB_IRQn = 124u, /*!< CAN2 OR'ed Message buffer (16-31) */
    CAN2_EdgeWakeup_IRQn    = 127u, /*!< CAN2 self wakeup by edge */
    CAN3_ORed_IRQn          = 128u, /*!< CAN3 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
    CAN3_Error_IRQn         = 129u, /*!< CAN3 Interrupt indicating that errors were detected on the CAN bus */
    CAN3_EccErr_IRQn        = 130u, /*!< CAN3 ECC error */
    CAN3_ORed_0_15_MB_IRQn  = 131u, /*!< CAN3 OR'ed Message buffer (0-15) */
    CAN3_ORed_16_31_MB_IRQn = 132u, /*!< CAN3 OR'ed Message buffer (16-31) */
    CAN3_EdgeWakeup_IRQn    = 135u, /*!< CAN3 self wakeup by edge */

} IRQn_Type;

/*******************************************************************************
 * the Processor and Core Peripheral Section
 ******************************************************************************/

/* Configuration of the Cortex-M# Processor and Core Peripherals */
#define __CM4_REV              0x0201

#define __NVIC_PRIO_BITS       4 /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used     */
#define __MPU_PRESENT          0 /*!< MPU present or not                               */
#define __FPU_PRESENT          1 /*!< FPU present or not                               */
#define __VFP_FP__             1 /*!< VFP                                              */

#include "../cmsis/core_cm4.h"

/*******************************************************************************
 * the Device Specific Peripheral registers structures
 ******************************************************************************/

#include "aips_reg.h"
#include "mscm_reg.h"
#include "cmu_reg.h"
#include "fccu_reg.h"
#include "edma_reg.h"
#include "crc_reg.h"
#include "mpu_reg.h"
#include "erm_reg.h"
#include "eim_reg.h"
#include "cse_reg.h"
#include "ftfc_reg.h"
#include "dmamux_reg.h"
#include "axbs_reg.h"
#include "prng_reg.h"
#include "adc_reg.h"
#include "pdb_reg.h"
#include "ewm_reg.h"
#include "spi_reg.h"
#include "mft_reg.h"
#include "flexcan_reg.h"
#include "pwmlite_reg.h"
#include "trgmux_reg.h"
#include "sim_reg.h"
#include "port_reg.h"
#include "i2c_reg.h"
#include "uart_reg.h"
#include "scg_reg.h"
#include "pcc_reg.h"
#include "i2sm_reg.h"
#include "i2ss_reg.h"
#include "cmp_reg.h"
#include "lptmr_reg.h"
#include "lpit_reg.h"
#include "rtc_reg.h"
#include "wdg_reg.h"
#include "pmc_reg.h"
#include "rcm_reg.h"
#include "acg_reg.h"
#include "apc_reg.h"
#include "gpio_reg.h"
#include "mcm_reg.h"
#include "cache_reg.h"

/*******************************************************************************
 * the Peripheral memory map
 ******************************************************************************/

/* AIPS module */
#define AIPS_BASE     (0x40000000u)
#define AIPS          ((AipsRegType *)AIPS_BASE)

/* MSCM module */
#define MSCM_BASE     (0x40001000u)
#define MSCM          ((MscmRegType *)MSCM_BASE)

/* CMU module */
#define CMU_FIRC_BASE (0x40002000u)
#define CMU_FIRC      ((CmuRegType *)CMU_FIRC_BASE)
#define CMU_PLL_BASE  (0x40003000u)
#define CMU_PLL       ((CmuRegType *)CMU_PLL_BASE)
#define CMU_SOSC_BASE (0x40004000u)
#define CMU_SOSC      ((CmuRegType *)CMU_SOSC_BASE)

/* FCCU  module */
#define FCCU_BASE     (0x40005000u)
#define FCCU          ((FccuRegType *)FCCU_BASE)

/* DMA module */
#define DMA_BASE      (0x40008000u)
#define DMA           ((EDmaRegType *)DMA_BASE)

/* CRC module */
#define CRC_BASE      (0x4000C000u)
#define CRC           ((CrcRegType *)CRC_BASE)

/* MPU module */
#define MPU_BASE      (0x4000D000u)
#define MPU           ((MpuRegType *)MPU_BASE)

/* ERM module */
#define ERM_BASE      (0x40018000u)
#define ERM           ((ErmRegType *)ERM_BASE)

/* EIM module */
#define EIM_BASE      (0x40019000u)
#define EIM           ((EimRegType *)EIM_BASE)

/* CSE module */
#define CSE_BASE      (0x4001C000u)
#define CSE           ((CseRegType *)CSE_BASE)

/* FTFC module */
#define FTFC_BASE     (0x40020000u)
#define FTFC          ((FtfcRegType *)FTFC_BASE)

/* DMAMUX module */
#define DMAMUX_BASE   (0x40021000u)
#define DMAMUX        ((DmamuxRegType *)DMAMUX_BASE)

/* AXBS module */
#define AXBS_BASE     (0x40022000u)
#define AXBS          ((AxbsRegType *)AXBS_BASE)

/* PRNG module */
#define PRNG_BASE     (0x40023000u)
#define PRNG          ((PrngRegType *)PRNG_BASE)

/* ADC modules */
#define ADC0_BASE     (0x40024000u)
#define ADC0          ((AdcRegType *)ADC0_BASE)
#define ADC1_BASE     (0x40025000u)
#define ADC1          ((AdcRegType *)ADC1_BASE)

/* PDB modules */
#define PDB0_BASE     (0x40026000u)
#define PDB0          ((PdbRegType *)PDB0_BASE)
#define PDB1_BASE     (0x40027000u)
#define PDB1          ((PdbRegType *)PDB1_BASE)

/* EWM module */
#define EWM_BASE      (0x4002B000u)
#define EWM           ((EwmRegType *)EWM_BASE)

/* SPI modules */
#define SPI0_BASE     (0x4002C000u)
#define SPI0          ((SpiRegType *)SPI0_BASE)
#define SPI1_BASE     (0x4002D000u)
#define SPI1          ((SpiRegType *)SPI1_BASE)
#define SPI2_BASE     (0x4002E000u)
#define SPI2          ((SpiRegType *)SPI2_BASE)
#define SPI3_BASE     (0x4002F000u)
#define SPI3          ((SpiRegType *)SPI3_BASE)

/* MFT modules */
#define MFT0_BASE     (0x40030000u)
#define MFT0          ((MftRegType *)MFT0_BASE)
#define MFT1_BASE     (0x40031000u)
#define MFT1          ((MftRegType *)MFT1_BASE)
#define MFT2_BASE     (0x40032000u)
#define MFT2          ((MftRegType *)MFT2_BASE)
#define MFT3_BASE     (0x40033000u)
#define MFT3          ((MftRegType *)MFT3_BASE)
#define MFT4_BASE     (0x40034000u)
#define MFT4          ((MftRegType *)MFT4_BASE)
#define MFT5_BASE     (0x40035000u)
#define MFT5          ((MftRegType *)MFT5_BASE)

/* CAN modules */
#define CAN0_BASE     (0x40038000u)
#define CAN0          ((FlexCanRegType *)CAN0_BASE)
#define CAN1_BASE     (0x4003C000u)
#define CAN1          ((FlexCanRegType *)CAN1_BASE)
#define CAN2_BASE     (0x40040000u)
#define CAN2          ((FlexCanRegType *)CAN2_BASE)
#define CAN3_BASE     (0x40044000u)
#define CAN3          ((FlexCanRegType *)CAN3_BASE)

/* PWMLITE modules */
#define PWMLITE0_BASE (0x40058000u)
#define PWMLITE0      ((PwmLiteRegType *)PWMLITE0_BASE)
#define PWMLITE1_BASE (0x40059000u)
#define PWMLITE1      ((PwmLiteRegType *)PWMLITE1_BASE)
#define PWMLITE2_BASE (0x4005A000u)
#define PWMLITE2      ((PwmLiteRegType *)PWMLITE2_BASE)
#define PWMLITE3_BASE (0x4005B000u)
#define PWMLITE3      ((PwmLiteRegType *)PWMLITE3_BASE)
#define PWMLITE4_BASE (0x4005C000u)
#define PWMLITE4      ((PwmLiteRegType *)PWMLITE4_BASE)

/* TRGMUX module */
#define TRGMUX_BASE   (0x4005E000u)
#define TRGMUX        ((TrgMuxRegType *)TRGMUX_BASE)

/* SIM module */
#define SIM_BASE      (0x4005F000u)
#define SIM           ((SimRegType *)SIM_BASE)

/* PORT modules */
#define PORTA_BASE    (0x40060000u)
#define PORTA         ((PortRegType *)PORTA_BASE)
#define PORTB_BASE    (0x40061000u)
#define PORTB         ((PortRegType *)PORTB_BASE)
#define PORTC_BASE    (0x40062000u)
#define PORTC         ((PortRegType *)PORTC_BASE)
#define PORTD_BASE    (0x40063000u)
#define PORTD         ((PortRegType *)PORTD_BASE)
#define PORTE_BASE    (0x40064000u)
#define PORTE         ((PortRegType *)PORTE_BASE)

/* I2C modules */
#define I2C_BASE      (0x40066000u)
#define I2C           ((I2cRegType *)I2C_BASE)

/* UART module */
#define UART0_BASE    (0x4006A000u)
#define UART0         ((UartRegType *)UART0_BASE)
#define UART1_BASE    (0x4006B000u)
#define UART1         ((UartRegType *)UART1_BASE)
#define UART2_BASE    (0x4006C000u)
#define UART2         ((UartRegType *)UART2_BASE)
#define UART3_BASE    (0x4006D000u)
#define UART3         ((UartRegType *)UART3_BASE)

/* SCG module */
#define SCG_BASE      (0x4006E000u)
#define SCG           ((ScgRegType *)SCG_BASE)

/* PCC module */
#define PCC_BASE      (0x4006F000u)
#define PCC           ((PccRegType *)PCC_BASE)

/* I2SM module */
#define I2SM_BASE     (0x40072000u)
#define I2SM          ((I2smRegType *)I2SM_BASE)

/* I2SS module */
#define I2SS_BASE     (0x40073000u)
#define I2SS          ((I2ssRegType *)I2SS_BASE)

/* CMP module */
#define CMP_BASE      (0x40074000u)
#define CMP           ((CmpRegType *)CMP_BASE)

/* LPTMR module */
#define LPTMR_BASE    (0x40075000u)
#define LPTMR         ((LptmrRegType *)LPTMR_BASE)

/* LPIT module */
#define LPIT_BASE     (0x40077000u)
#define LPIT          ((LpitRegType *)LPIT_BASE)

/* RTC module */
#define RTC_BASE      (0x40078000u)
#define RTC           ((RtcRegType *)RTC_BASE)

/* WDG module */
#define WDG_BASE      (0x4007A000u)
#define WDG           ((WdgRegType *)WDG_BASE)

/* PMC module */
#define PMC_BASE      (0x4007D000u)
#define PMC           ((PmcRegType *)PMC_BASE)

/* RCM module */
#define RCM_BASE      (0x4007F000u)
#define RCM           ((RcmRegType *)RCM_BASE)

/* ACG module */
#define ACG_BASE      (0x4007F800u)
#define ACG           ((AcgRegType *)ACG_BASE)

/* APC module */
#define APC_BASE      (0x4007FC00u)
#define APC           ((ApcRegType *)APC_BASE)

/* GPIO modules */
#define GPIOA_BASE    (0x400FF000u)
#define GPIOA         ((GpioRegType *)GPIOA_BASE)
#define GPIOB_BASE    (0x400FF040u)
#define GPIOB         ((GpioRegType *)GPIOB_BASE)
#define GPIOC_BASE    (0x400FF080u)
#define GPIOC         ((GpioRegType *)GPIOC_BASE)
#define GPIOD_BASE    (0x400FF0C0u)
#define GPIOD         ((GpioRegType *)GPIOD_BASE)
#define GPIOE_BASE    (0x400FF100u)
#define GPIOE         ((GpioRegType *)GPIOE_BASE)

/* MCM module */
#define MCM_BASE      (0xE0080000u)
#define MCM           ((McmRegType *)MCM_BASE)

/* CACHE module */
#define CACHE_BASE    (0xE0082000u)
#define CACHE         ((CacheRegType *)CACHE_BASE)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CVM014X_H_ */
