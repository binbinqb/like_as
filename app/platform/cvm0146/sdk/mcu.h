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

#ifndef _MCU_H_
#define _MCU_H_

/*! \brief Contains public interface to various functions related
 *         to the MCAL (MCU Abstract Layer) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "CVM014x_features.h"
#include "drivers/adc/adc_drv.h"
#include "drivers/clock/clock_drv.h"
#include "drivers/cmp/cmp_drv.h"
#include "drivers/cmu/cmu_drv.h"
#include "drivers/cpu/cpu_drv.h"
#include "drivers/crc/crc_drv.h"
#include "drivers/cse/cse_drv.h"
#include "drivers/edma/edma_drv.h"
#include "drivers/eim/eim_drv.h"
#include "drivers/erm/erm_drv.h"
#include "drivers/ewm/ewm_drv.h"
#include "drivers/fccu/fccu_drv.h"
#include "drivers/flash/flash_drv.h"
#include "drivers/flexcan/flexcan_drv.h"
#include "drivers/i2c/i2c_drv.h"
#include "drivers/i2sm/i2sm_drv.h"
#include "drivers/i2ss/i2ss_drv.h"
#include "drivers/lpit/lpit_drv.h"
#include "drivers/lptmr/lptmr_drv.h"
#include "drivers/mft/mft_drv.h"
#include "drivers/mpu/mpu_drv.h"
#include "drivers/pdb/pdb_drv.h"
#include "drivers/pins/pins_drv.h"
#include "drivers/power/power_drv.h"
#include "drivers/prng/prng_drv.h"
#include "drivers/pwmlite/pwmlite_drv.h"
#include "drivers/reset/reset_drv.h"
#include "drivers/rtc/rtc_drv.h"
#include "drivers/spi/spi_drv.h"
#include "drivers/trgmux/trgmux_drv.h"
#include "drivers/uart/uart_drv.h"
#include "drivers/wdg/wdg_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Definition of MCU prototype
 */
typedef struct _McuType_
{
    AdcDrvType     adc0Drv;
    AdcDrvType     adc1Drv;
    ClockDrvType   clockDrv;
    CmpDrvType     cmpDrv;
    CmuDrvType     cmuFirc;
    CmuDrvType     cmuPll;
    CmuDrvType     cmuSosc;
    CrcDrvType     crcDrv;
    CseDrvType     cseDrv;
    EDmaDrvType    edmaDrv;
    EimDrvType     eimDrv;
    ErmDrvType     ermDrv;
    EwmDrvType     ewmDrv;
    FccuDrvType    fccuDrv;
    FlashDrvType   flashDrv;
    FlexCanDrvType flexCanDrv0;
    FlexCanDrvType flexCanDrv1;
    FlexCanDrvType flexCanDrv2;
    FlexCanDrvType flexCanDrv3;
    I2cDrvType     i2cDrv0;
    I2smDrvType    i2smDrv;
    I2ssDrvType    i2ssDrv;
    LpitDrvType    lpitDrv;
    LptmrDrvType   lptmrDrv;
    MftDrvType     mftDrv0;
    MftDrvType     mftDrv1;
    MftDrvType     mftDrv2;
    MftDrvType     mftDrv3;
#if FEATURE_MFT_INSTANCE_NUM == 6
    MftDrvType     mftDrv4;
    MftDrvType     mftDrv5;
#endif
    MpuDrvType     mpuDrv;
    PdbDrvType     pdb0Drv;
    PdbDrvType     pdb1Drv;
    PinsDrvType    pta;
    PinsDrvType    ptb;
    PinsDrvType    ptc;
    PinsDrvType    ptd;
    PinsDrvType    pte;
    PowerDrvType   powerDrv;
    PrngDrvType    prngDrv;
    PwmLiteDrvType pwmLiteDrv0;
    PwmLiteDrvType pwmLiteDrv1;
    PwmLiteDrvType pwmLiteDrv2;
    PwmLiteDrvType pwmLiteDrv3;
    PwmLiteDrvType pwmLiteDrv4;
    ResetDrvType   resetDrv;
    RtcDrvType     rtcDrv;
    SpiDrvType     spiDrv0;
    SpiDrvType     spiDrv1;
    SpiDrvType     spiDrv2;
#if FEATURE_SPI_INSTANCE_NUM == 4
    SpiDrvType     spiDrv3;
#endif
    TrgMuxDrvType  trgMuxDrv;
    UartDrvType    uartDrv0;
    UartDrvType    uartDrv1;
    UartDrvType    uartDrv2;
#if FEATURE_UART_INSTANCE_NUM == 4
    UartDrvType    uartDrv3;
#endif
    WdgDrvType     wdgDrv;
    
} McuType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MCU
 *
 * This function initializes MCU by setting up all the peripheral drivers
 *
 * \param[in] obj : pointer to MCU instance
 */
extern void Mcu_Init(McuType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _MCU_H_ */
