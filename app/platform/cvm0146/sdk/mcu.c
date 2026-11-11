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

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include "mcu.h"
#include "drivers/cpu/startup/system_M014x.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void Mcu_Init(McuType *obj)
{
    /* Initialize ADC driver */
    AdcDrv_InitParamsType adcInitParams;
    adcInitParams.adcNumber = ADCDRV_INSTANCE_0;
    AdcDrv_Init(&obj->adc0Drv, ADC0, SIM, &adcInitParams);
    adcInitParams.adcNumber = ADCDRV_INSTANCE_1;
    AdcDrv_Init(&obj->adc1Drv, ADC1, SIM, &adcInitParams);

    /* Initialize clock driver */
    ClockDrv_InitParamsType clockInitParams;
    clockInitParams.fircFreq     = CPU_INT_FAST_CLK_HZ;
    clockInitParams.sircFreq     = CPU_INT_SLOW_CLK_HZ;
    clockInitParams.xtalClkFreq  = CPU_XTAL_CLK_HZ;
    clockInitParams.rtcClkInFreq = 0;
    clockInitParams.tclkFreq[0]  = 0;
    clockInitParams.tclkFreq[1]  = 0;
    clockInitParams.tclkFreq[2]  = 0;
    ClockDrv_Init(&obj->clockDrv, ACG, APC, SCG, PCC, &clockInitParams);

    /* Initialize CMP driver */
    CmpDrv_Init(&obj->cmpDrv, CMP);

    /* Initialize CMU driver */
    CmuDrv_Init(&obj->cmuFirc, CMU_FIRC);
    CmuDrv_Init(&obj->cmuPll, CMU_PLL);
    CmuDrv_Init(&obj->cmuSosc, CMU_SOSC);

    /* Initialize CRC driver */
    CrcDrv_Init(&obj->crcDrv, CRC);

    /* Initialize CSE driver */
    CseDrv_Init(&obj->cseDrv, CSE);

    /* Initialize EDMA driver */
    EDmaDrv_Init(&obj->edmaDrv, DMA, DMAMUX);

    /* Initialize EIM driver */
    EimDrv_Init(&obj->eimDrv, EIM);

    /* Initialize ERM driver */
    ErmDrv_Init(&obj->ermDrv, ERM);

    /* Initialize EWM driver */
    EwmDrv_Init(&obj->ewmDrv, EWM);

    /* Initialize FCCU driver */
    FccuDrv_Init(&obj->fccuDrv, FCCU, SIM);

    /* Initialize Flash driver */
    FlashDrv_Init(&obj->flashDrv, FTFC);

    /* Initialize flexCAN driver */
    FlexCanDrv_InitHwParType canInitHwPar;
    canInitHwPar.canInstanceIdx = 0;
    canInitHwPar.canRamNum      = 3;
    FlexCanDrv_Init(&obj->flexCanDrv0, CAN0, PCC, SCG, SIM, &canInitHwPar);
    canInitHwPar.canInstanceIdx = 1;
    canInitHwPar.canRamNum      = 2;
    FlexCanDrv_Init(&obj->flexCanDrv1, CAN1, PCC, SCG, SIM, &canInitHwPar);
    canInitHwPar.canInstanceIdx = 2;
    canInitHwPar.canRamNum      = 1;
    FlexCanDrv_Init(&obj->flexCanDrv2, CAN2, PCC, SCG, SIM, &canInitHwPar);
#if FEATURE_CAN_FD_INSTANCE_NUM == 4
    canInitHwPar.canInstanceIdx = 3;
    canInitHwPar.canRamNum      = 1;
    FlexCanDrv_Init(&obj->flexCanDrv3, CAN3, PCC, SCG, SIM, &canInitHwPar);
#endif

    /* Initialize I2C driver */
    I2cDrv_Init(&obj->i2cDrv0, I2C);

    /* Initialize I2SM driver */
    I2smDrv_Init(&obj->i2smDrv, I2SM, SIM);

    /* Initialize I2SS driver */
    I2ssDrv_Init(&obj->i2ssDrv, I2SS, SIM);

    /* Initialize LPIT driver */
    LpitDrv_Init(&obj->lpitDrv, LPIT);

    /* Initialize LPTMR driver */
    LptmrDrv_Init(&obj->lptmrDrv, LPTMR);

    /* Initialize MFT drivers */
    MftDrv_Init(&obj->mftDrv0, MFT0);
    MftDrv_Init(&obj->mftDrv1, MFT1);
    MftDrv_Init(&obj->mftDrv2, MFT2);
    MftDrv_Init(&obj->mftDrv3, MFT3);
#if FEATURE_MFT_INSTANCE_NUM == 6
    MftDrv_Init(&obj->mftDrv4, MFT4);
    MftDrv_Init(&obj->mftDrv5, MFT5);
#endif

    /* Initialize MPU driver */
    MpuDrv_Init(&obj->mpuDrv, MPU);

    /* Initialize PDB driver */
    PdbDrv_Init(&obj->pdb0Drv, PDB0, SIM);
    PdbDrv_Init(&obj->pdb1Drv, PDB1, SIM);

    /* Initialize PINS driver */
    PinsDrv_Init(&obj->pta, PORTA, GPIOA);
    PinsDrv_Init(&obj->ptb, PORTB, GPIOB);
    PinsDrv_Init(&obj->ptc, PORTC, GPIOC);
    PinsDrv_Init(&obj->ptd, PORTD, GPIOD);
    PinsDrv_Init(&obj->pte, PORTE, GPIOE);

    /* Initialize POWER driver */
    PowerDrv_Init(&obj->powerDrv, PMC, ACG);

    /* Initialize PRNG driver */
    PrngDrv_Init(&obj->prngDrv, PRNG);

    /* Initialize PWMLITE driver */
    PwmLiteDrv_Init(&obj->pwmLiteDrv0, PWMLITE0, SIM);
    PwmLiteDrv_Init(&obj->pwmLiteDrv1, PWMLITE1, SIM);
    PwmLiteDrv_Init(&obj->pwmLiteDrv2, PWMLITE2, SIM);
    PwmLiteDrv_Init(&obj->pwmLiteDrv3, PWMLITE3, SIM);
    PwmLiteDrv_Init(&obj->pwmLiteDrv4, PWMLITE4, SIM);

    /* Initialize reset driver */
    ResetDrv_Init(&obj->resetDrv, RCM, PCC, APC);

    /* Initialize RTC driver */
    RtcDrv_Init(&obj->rtcDrv, RTC);

    /* Initialize SPI driver */
    SpiDrv_Init(&obj->spiDrv0, SPI0);
    SpiDrv_Init(&obj->spiDrv1, SPI1);
    SpiDrv_Init(&obj->spiDrv2, SPI2);
#if FEATURE_SPI_INSTANCE_NUM == 4
    SpiDrv_Init(&obj->spiDrv3, SPI3);
#endif

    /* Initialize TRGMUX driver */
    TrgMuxDrv_Init(&obj->trgMuxDrv, TRGMUX, SIM);

    /* Initialize UART driver */
    UartDrv_Init(&obj->uartDrv0, UART0);
    UartDrv_Init(&obj->uartDrv1, UART1);
    UartDrv_Init(&obj->uartDrv2, UART2);
#if FEATURE_UART_INSTANCE_NUM == 4
    UartDrv_Init(&obj->uartDrv3, UART3);
#endif

    /* Initialize watchdog driver */
    WdgDrv_Init(&obj->wdgDrv, WDG);
}
