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

#include <stddef.h>
#include "clock_drv.h"
#include "acg_reg.h"
#include "apc_reg.h"
#include "pcc_reg.h"
#include "scg_reg.h"
#include "../../CVM014x_features.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* Definitions for LPO frequencies */
#define LPO_128K_FREQUENCY            (128000UL)
#define LPO_32K_FREQUENCY             (32000UL)
#define LPO_1K_FREQUENCY              (1000UL)

/* Definitions for all the get and set clock interface */
#define GET_FREQ_FUNC_DEF(module)     static inline bool ClockDrv_Get##module##Freq(const ClockDrvType *obj, uint32_t *frequency)
#define GET_FREQ_FUNC(module)         ClockDrv_Get##module##Freq
#define CONFIG_CLOCK_FUNC_DEF(module) static inline bool ClockDrv_Set##module##Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
#define CONFIG_CLOCK_FUNC(module)     ClockDrv_Set##module##Clock

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Module clock function table element definition
 */
typedef struct _ClockDrv_ModuleClkFuncType_
{
    bool (*getFreqFunc)(const ClockDrvType *, uint32_t *);
    bool (*setClockFunc)(ClockDrvType *, const ClockDrv_ModuleClkConfigType *);
} ClockDrv_ModuleClkFuncType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the constants
 ******************************************************************************/

/* Forward decleratios for all get and set clock interface */
GET_FREQ_FUNC_DEF(Sosc);
CONFIG_CLOCK_FUNC_DEF(Sosc);
GET_FREQ_FUNC_DEF(Sirc);
CONFIG_CLOCK_FUNC_DEF(Sirc);
GET_FREQ_FUNC_DEF(Firc);
CONFIG_CLOCK_FUNC_DEF(Firc);
GET_FREQ_FUNC_DEF(Pll);
CONFIG_CLOCK_FUNC_DEF(Pll);
GET_FREQ_FUNC_DEF(SoscDiv1);
CONFIG_CLOCK_FUNC_DEF(SoscDiv1);
GET_FREQ_FUNC_DEF(SoscDiv2);
CONFIG_CLOCK_FUNC_DEF(SoscDiv2);
GET_FREQ_FUNC_DEF(SircDiv1);
CONFIG_CLOCK_FUNC_DEF(SircDiv1);
GET_FREQ_FUNC_DEF(SircDiv2);
CONFIG_CLOCK_FUNC_DEF(SircDiv2);
GET_FREQ_FUNC_DEF(FircDiv1);
CONFIG_CLOCK_FUNC_DEF(FircDiv1);
GET_FREQ_FUNC_DEF(FircDiv2);
CONFIG_CLOCK_FUNC_DEF(FircDiv2);
GET_FREQ_FUNC_DEF(PllDiv1);
CONFIG_CLOCK_FUNC_DEF(PllDiv1);
GET_FREQ_FUNC_DEF(PllDiv2);
CONFIG_CLOCK_FUNC_DEF(PllDiv2);
GET_FREQ_FUNC_DEF(Sys);
CONFIG_CLOCK_FUNC_DEF(Sys);
GET_FREQ_FUNC_DEF(Core);
CONFIG_CLOCK_FUNC_DEF(Core);
GET_FREQ_FUNC_DEF(Apb);
CONFIG_CLOCK_FUNC_DEF(Apb);
GET_FREQ_FUNC_DEF(Fls);
CONFIG_CLOCK_FUNC_DEF(Fls);
GET_FREQ_FUNC_DEF(Trace);
CONFIG_CLOCK_FUNC_DEF(Trace);
GET_FREQ_FUNC_DEF(ClkOut);
CONFIG_CLOCK_FUNC_DEF(ClkOut);
GET_FREQ_FUNC_DEF(RtcPadIn);
GET_FREQ_FUNC_DEF(Lpo1k);
CONFIG_CLOCK_FUNC_DEF(Lpo1k);
GET_FREQ_FUNC_DEF(Lpo32k);
CONFIG_CLOCK_FUNC_DEF(Lpo32k);
GET_FREQ_FUNC_DEF(Lpo128k);
CONFIG_CLOCK_FUNC_DEF(Lpo32k);
GET_FREQ_FUNC_DEF(Rtc);
CONFIG_CLOCK_FUNC_DEF(Rtc);
GET_FREQ_FUNC_DEF(ExtFlt);
CONFIG_CLOCK_FUNC_DEF(ExtFlt);
GET_FREQ_FUNC_DEF(Lpit);
CONFIG_CLOCK_FUNC_DEF(Lpit);
GET_FREQ_FUNC_DEF(Lptmr);
CONFIG_CLOCK_FUNC_DEF(Lptmr);
GET_FREQ_FUNC_DEF(RtcCnt);
CONFIG_CLOCK_FUNC_DEF(RtcCnt);
GET_FREQ_FUNC_DEF(PortAFlt);
CONFIG_CLOCK_FUNC_DEF(PortAFlt);
GET_FREQ_FUNC_DEF(PortBFlt);
CONFIG_CLOCK_FUNC_DEF(PortBFlt);
GET_FREQ_FUNC_DEF(PortCFlt);
CONFIG_CLOCK_FUNC_DEF(PortCFlt);
GET_FREQ_FUNC_DEF(PortDFlt);
CONFIG_CLOCK_FUNC_DEF(PortDFlt);
GET_FREQ_FUNC_DEF(PortEFlt);
CONFIG_CLOCK_FUNC_DEF(PortEFlt);
GET_FREQ_FUNC_DEF(PortA);
CONFIG_CLOCK_FUNC_DEF(PortA);
GET_FREQ_FUNC_DEF(PortB);
CONFIG_CLOCK_FUNC_DEF(PortB);
GET_FREQ_FUNC_DEF(PortC);
CONFIG_CLOCK_FUNC_DEF(PortC);
GET_FREQ_FUNC_DEF(PortD);
CONFIG_CLOCK_FUNC_DEF(PortD);
GET_FREQ_FUNC_DEF(PortE);
CONFIG_CLOCK_FUNC_DEF(PortE);
GET_FREQ_FUNC_DEF(Cmp0);
CONFIG_CLOCK_FUNC_DEF(Cmp0);
GET_FREQ_FUNC_DEF(Dma);
CONFIG_CLOCK_FUNC_DEF(Dma);
GET_FREQ_FUNC_DEF(Eim);
CONFIG_CLOCK_FUNC_DEF(Eim);
GET_FREQ_FUNC_DEF(Erm);
CONFIG_CLOCK_FUNC_DEF(Erm);
GET_FREQ_FUNC_DEF(Mpu);
CONFIG_CLOCK_FUNC_DEF(Mpu);
GET_FREQ_FUNC_DEF(Crc);
CONFIG_CLOCK_FUNC_DEF(Crc);
GET_FREQ_FUNC_DEF(Cse);
CONFIG_CLOCK_FUNC_DEF(Cse);
GET_FREQ_FUNC_DEF(Mft0);
CONFIG_CLOCK_FUNC_DEF(Mft0);
GET_FREQ_FUNC_DEF(Mft1);
CONFIG_CLOCK_FUNC_DEF(Mft1);
GET_FREQ_FUNC_DEF(Mft2);
CONFIG_CLOCK_FUNC_DEF(Mft2);
GET_FREQ_FUNC_DEF(Mft3);
CONFIG_CLOCK_FUNC_DEF(Mft3);
GET_FREQ_FUNC_DEF(Mft4);
CONFIG_CLOCK_FUNC_DEF(Mft4);
GET_FREQ_FUNC_DEF(Mft5);
CONFIG_CLOCK_FUNC_DEF(Mft5);
GET_FREQ_FUNC_DEF(Mscm);
CONFIG_CLOCK_FUNC_DEF(Mscm);
GET_FREQ_FUNC_DEF(DmaMux);
CONFIG_CLOCK_FUNC_DEF(DmaMux);
GET_FREQ_FUNC_DEF(Pdb0);
CONFIG_CLOCK_FUNC_DEF(Pdb0);
GET_FREQ_FUNC_DEF(Pdb1);
CONFIG_CLOCK_FUNC_DEF(Pdb1);
GET_FREQ_FUNC_DEF(PwmLite0);
CONFIG_CLOCK_FUNC_DEF(PwmLite0);
GET_FREQ_FUNC_DEF(PwmLite1);
CONFIG_CLOCK_FUNC_DEF(PwmLite1);
GET_FREQ_FUNC_DEF(PwmLite2);
CONFIG_CLOCK_FUNC_DEF(PwmLite2);
GET_FREQ_FUNC_DEF(PwmLite3);
CONFIG_CLOCK_FUNC_DEF(PwmLite3);
GET_FREQ_FUNC_DEF(PwmLite4);
CONFIG_CLOCK_FUNC_DEF(PwmLite4);
GET_FREQ_FUNC_DEF(Prng);
CONFIG_CLOCK_FUNC_DEF(Prng);
GET_FREQ_FUNC_DEF(Cmus);
CONFIG_CLOCK_FUNC_DEF(Cmus);
GET_FREQ_FUNC_DEF(Cmuf);
CONFIG_CLOCK_FUNC_DEF(Cmuf);
GET_FREQ_FUNC_DEF(Fccu);
CONFIG_CLOCK_FUNC_DEF(Fccu);
GET_FREQ_FUNC_DEF(Cmup);
CONFIG_CLOCK_FUNC_DEF(Cmup);
GET_FREQ_FUNC_DEF(I2C);
CONFIG_CLOCK_FUNC_DEF(I2C);
GET_FREQ_FUNC_DEF(Spi0);
CONFIG_CLOCK_FUNC_DEF(Spi0);
GET_FREQ_FUNC_DEF(Spi1);
CONFIG_CLOCK_FUNC_DEF(Spi1);
GET_FREQ_FUNC_DEF(Spi2);
CONFIG_CLOCK_FUNC_DEF(Spi2);
GET_FREQ_FUNC_DEF(Spi3);
CONFIG_CLOCK_FUNC_DEF(Spi3);
GET_FREQ_FUNC_DEF(Uart0);
CONFIG_CLOCK_FUNC_DEF(Uart0);
GET_FREQ_FUNC_DEF(Uart1);
CONFIG_CLOCK_FUNC_DEF(Uart1);
GET_FREQ_FUNC_DEF(Uart2);
CONFIG_CLOCK_FUNC_DEF(Uart2);
GET_FREQ_FUNC_DEF(Uart3);
CONFIG_CLOCK_FUNC_DEF(Uart3);
GET_FREQ_FUNC_DEF(I2SM);
CONFIG_CLOCK_FUNC_DEF(I2SM);
GET_FREQ_FUNC_DEF(I2SS);
CONFIG_CLOCK_FUNC_DEF(I2SS);
GET_FREQ_FUNC_DEF(Adc0);
CONFIG_CLOCK_FUNC_DEF(Adc0);
GET_FREQ_FUNC_DEF(Adc1);
CONFIG_CLOCK_FUNC_DEF(Adc1);
GET_FREQ_FUNC_DEF(Tclk0);
GET_FREQ_FUNC_DEF(Tclk1);
GET_FREQ_FUNC_DEF(Tclk2);
GET_FREQ_FUNC_DEF(ExtMft0);
CONFIG_CLOCK_FUNC_DEF(ExtMft0);
GET_FREQ_FUNC_DEF(ExtMft1);
CONFIG_CLOCK_FUNC_DEF(ExtMft1);
GET_FREQ_FUNC_DEF(ExtMft2);
CONFIG_CLOCK_FUNC_DEF(ExtMft2);
GET_FREQ_FUNC_DEF(ExtMft3);
CONFIG_CLOCK_FUNC_DEF(ExtMft3);
GET_FREQ_FUNC_DEF(ExtMft4);
CONFIG_CLOCK_FUNC_DEF(ExtMft4);
GET_FREQ_FUNC_DEF(ExtMft5);
CONFIG_CLOCK_FUNC_DEF(ExtMft5);
GET_FREQ_FUNC_DEF(Ewm);
CONFIG_CLOCK_FUNC_DEF(Ewm);

/* Function table for all get and set clock interface */
const ClockDrv_ModuleClkFuncType c_clockFuncTable[CLOCKDRV_CLOCK_NUM] = {
    {GET_FREQ_FUNC(Sosc),     CONFIG_CLOCK_FUNC(Sosc)    }, /* CLOCKDRV_SOSC */
    {GET_FREQ_FUNC(Sirc),     CONFIG_CLOCK_FUNC(Sirc)    }, /* CLOCKDRV_SIRC */
    {GET_FREQ_FUNC(Firc),     CONFIG_CLOCK_FUNC(Firc)    }, /* CLOCKDRV_FIRC */
    {GET_FREQ_FUNC(Pll),      CONFIG_CLOCK_FUNC(Pll)     }, /* CLOCKDRV_PLL */
    {GET_FREQ_FUNC(SoscDiv1), CONFIG_CLOCK_FUNC(SoscDiv1)}, /* CLOCKDRV_SOSC_DIV1 */
    {GET_FREQ_FUNC(SoscDiv2), CONFIG_CLOCK_FUNC(SoscDiv2)}, /* CLOCKDRV_SOSC_DIV2 */
    {GET_FREQ_FUNC(SircDiv1), CONFIG_CLOCK_FUNC(SircDiv1)}, /* CLOCKDRV_SIRC_DIV1 */
    {GET_FREQ_FUNC(SircDiv2), CONFIG_CLOCK_FUNC(SircDiv2)}, /* CLOCKDRV_SIRC_DIV2 */
    {GET_FREQ_FUNC(FircDiv1), CONFIG_CLOCK_FUNC(FircDiv1)}, /* CLOCKDRV_FIRC_DIV1 */
    {GET_FREQ_FUNC(FircDiv2), CONFIG_CLOCK_FUNC(FircDiv2)}, /* CLOCKDRV_FIRC_DIV2 */
    {GET_FREQ_FUNC(PllDiv1),  CONFIG_CLOCK_FUNC(PllDiv1) }, /* CLOCKDRV_PLL_DIV1 */
    {GET_FREQ_FUNC(PllDiv2),  CONFIG_CLOCK_FUNC(PllDiv2) }, /* CLOCKDRV_PLL_DIV2 */
    {GET_FREQ_FUNC(Sys),      CONFIG_CLOCK_FUNC(Sys)     }, /* CLOCKDRV_SYS */
    {GET_FREQ_FUNC(Core),     CONFIG_CLOCK_FUNC(Core)    }, /* CLOCKDRV_CORE */
    {GET_FREQ_FUNC(Apb),      CONFIG_CLOCK_FUNC(Apb)     }, /* CLOCKDRV_APB */
    {GET_FREQ_FUNC(Fls),      CONFIG_CLOCK_FUNC(Fls)     }, /* CLOCKDRV_FLS */
    {GET_FREQ_FUNC(Trace),    CONFIG_CLOCK_FUNC(Trace)   }, /* CLOCKDRV_TRACE */
    {GET_FREQ_FUNC(ClkOut),   CONFIG_CLOCK_FUNC(ClkOut)  }, /* CLOCKDRV_CLKOUT */
    {GET_FREQ_FUNC(RtcPadIn), NULL                       }, /* CLOCKDRV_RTC_PADIN */
    {GET_FREQ_FUNC(Lpo1k),    CONFIG_CLOCK_FUNC(Lpo1k)   }, /* CLOCKDRV_LPO_1K */
    {GET_FREQ_FUNC(Lpo32k),   CONFIG_CLOCK_FUNC(Lpo32k)  }, /* CLOCKDRV_LPO_32K */
    {GET_FREQ_FUNC(Lpo128k),  NULL                       }, /* CLOCKDRV_LPO_128K */
    {GET_FREQ_FUNC(Rtc),      CONFIG_CLOCK_FUNC(Rtc)     }, /* CLOCKDRV_RTC */
    {GET_FREQ_FUNC(ExtFlt),   CONFIG_CLOCK_FUNC(ExtFlt)  }, /* CLOCKDRV_EXT_FLT */
    {GET_FREQ_FUNC(Lpit),     CONFIG_CLOCK_FUNC(Lpit)    }, /* CLOCKDRV_LPIT */
    {GET_FREQ_FUNC(Lptmr),    CONFIG_CLOCK_FUNC(Lptmr)   }, /* CLOCKDRV_LPTMR */
    {GET_FREQ_FUNC(RtcCnt),   CONFIG_CLOCK_FUNC(RtcCnt)  }, /* CLOCKDRV_RTC_CNT */
    {GET_FREQ_FUNC(PortAFlt), CONFIG_CLOCK_FUNC(PortAFlt)}, /* CLOCKDRV_PORTA_FLT */
    {GET_FREQ_FUNC(PortBFlt), CONFIG_CLOCK_FUNC(PortBFlt)}, /* CLOCKDRV_PORTB_FLT */
    {GET_FREQ_FUNC(PortCFlt), CONFIG_CLOCK_FUNC(PortCFlt)}, /* CLOCKDRV_PORTC_FLT */
    {GET_FREQ_FUNC(PortDFlt), CONFIG_CLOCK_FUNC(PortDFlt)}, /* CLOCKDRV_PORTD_FLT */
    {GET_FREQ_FUNC(PortEFlt), CONFIG_CLOCK_FUNC(PortEFlt)}, /* CLOCKDRV_PORTE_FLT */
    {GET_FREQ_FUNC(PortA),    CONFIG_CLOCK_FUNC(PortA)   }, /* CLOCKDRV_PORTA */
    {GET_FREQ_FUNC(PortB),    CONFIG_CLOCK_FUNC(PortB)   }, /* CLOCKDRV_PORTB */
    {GET_FREQ_FUNC(PortC),    CONFIG_CLOCK_FUNC(PortC)   }, /* CLOCKDRV_PORTC */
    {GET_FREQ_FUNC(PortD),    CONFIG_CLOCK_FUNC(PortD)   }, /* CLOCKDRV_PORTD */
    {GET_FREQ_FUNC(PortE),    CONFIG_CLOCK_FUNC(PortE)   }, /* CLOCKDRV_PORTE */
    {GET_FREQ_FUNC(Cmp0),     CONFIG_CLOCK_FUNC(Cmp0)    }, /* CLOCKDRV_CMP0 */
    {GET_FREQ_FUNC(Dma),      CONFIG_CLOCK_FUNC(Dma)     }, /* CLOCKDRV_DMA */
    {GET_FREQ_FUNC(Eim),      CONFIG_CLOCK_FUNC(Eim)     }, /* CLOCKDRV_EIM */
    {GET_FREQ_FUNC(Erm),      CONFIG_CLOCK_FUNC(Erm)     }, /* CLOCKDRV_ERM */
    {GET_FREQ_FUNC(Mpu),      CONFIG_CLOCK_FUNC(Mpu)     }, /* CLOCKDRV_MPU */
    {GET_FREQ_FUNC(Crc),      CONFIG_CLOCK_FUNC(Crc)     }, /* CLOCKDRV_CRC */
    {GET_FREQ_FUNC(Cse),      CONFIG_CLOCK_FUNC(Cse)     }, /* CLOCKDRV_CSE */
    {GET_FREQ_FUNC(Mft0),     CONFIG_CLOCK_FUNC(Mft0)    }, /* CLOCKDRV_MFT0 */
    {GET_FREQ_FUNC(Mft1),     CONFIG_CLOCK_FUNC(Mft1)    }, /* CLOCKDRV_MFT1 */
    {GET_FREQ_FUNC(Mft2),     CONFIG_CLOCK_FUNC(Mft2)    }, /* CLOCKDRV_MFT2 */
    {GET_FREQ_FUNC(Mft3),     CONFIG_CLOCK_FUNC(Mft3)    }, /* CLOCKDRV_MFT3 */
    {GET_FREQ_FUNC(Mft4),     CONFIG_CLOCK_FUNC(Mft4)    }, /* CLOCKDRV_MFT4 */
    {GET_FREQ_FUNC(Mft5),     CONFIG_CLOCK_FUNC(Mft5)    }, /* CLOCKDRV_MFT5 */
    {GET_FREQ_FUNC(Mscm),     CONFIG_CLOCK_FUNC(Mscm)    }, /* CLOCKDRV_MSCM */
    {GET_FREQ_FUNC(DmaMux),   CONFIG_CLOCK_FUNC(DmaMux)  }, /* CLOCKDRV_DMA_MUX */
    {GET_FREQ_FUNC(Pdb0),     CONFIG_CLOCK_FUNC(Pdb0)    }, /* CLOCKDRV_PDB0 */
    {GET_FREQ_FUNC(Pdb1),     CONFIG_CLOCK_FUNC(Pdb1)    }, /* CLOCKDRV_PDB1 */
    {GET_FREQ_FUNC(PwmLite0), CONFIG_CLOCK_FUNC(PwmLite0)}, /* CLOCKDRV_PWMLITE0 */
    {GET_FREQ_FUNC(PwmLite1), CONFIG_CLOCK_FUNC(PwmLite1)}, /* CLOCKDRV_PWMLITE1 */
    {GET_FREQ_FUNC(PwmLite2), CONFIG_CLOCK_FUNC(PwmLite2)}, /* CLOCKDRV_PWMLITE2 */
    {GET_FREQ_FUNC(PwmLite3), CONFIG_CLOCK_FUNC(PwmLite3)}, /* CLOCKDRV_PWMLITE3 */
    {GET_FREQ_FUNC(PwmLite4), CONFIG_CLOCK_FUNC(PwmLite4)}, /* CLOCKDRV_PWMLITE4 */
    {GET_FREQ_FUNC(Prng),     CONFIG_CLOCK_FUNC(Prng)    }, /* CLOCKDRV_PRNG */
    {GET_FREQ_FUNC(Cmus),     CONFIG_CLOCK_FUNC(Cmus)    }, /* CLOCKDRV_CMUS */
    {GET_FREQ_FUNC(Cmuf),     CONFIG_CLOCK_FUNC(Cmuf)    }, /* CLOCKDRV_CMUF */
    {GET_FREQ_FUNC(Fccu),     CONFIG_CLOCK_FUNC(Fccu)    }, /* CLOCKDRV_FCCU */
    {GET_FREQ_FUNC(Cmup),     CONFIG_CLOCK_FUNC(Cmup)    }, /* CLOCKDRV_CMUP */
    {GET_FREQ_FUNC(I2C),      CONFIG_CLOCK_FUNC(I2C)     }, /* CLOCKDRV_I2C */
    {GET_FREQ_FUNC(Spi0),     CONFIG_CLOCK_FUNC(Spi0)    }, /* CLOCKDRV_SPI0 */
    {GET_FREQ_FUNC(Spi1),     CONFIG_CLOCK_FUNC(Spi1)    }, /* CLOCKDRV_SPI1 */
    {GET_FREQ_FUNC(Spi2),     CONFIG_CLOCK_FUNC(Spi2)    }, /* CLOCKDRV_SPI2 */
    {GET_FREQ_FUNC(Spi3),     CONFIG_CLOCK_FUNC(Spi3)    }, /* CLOCKDRV_SPI3 */
    {GET_FREQ_FUNC(Uart0),    CONFIG_CLOCK_FUNC(Uart0)   }, /* CLOCKDRV_UART0 */
    {GET_FREQ_FUNC(Uart1),    CONFIG_CLOCK_FUNC(Uart1)   }, /* CLOCKDRV_UART1 */
    {GET_FREQ_FUNC(Uart2),    CONFIG_CLOCK_FUNC(Uart2)   }, /* CLOCKDRV_UART2 */
    {GET_FREQ_FUNC(Uart3),    CONFIG_CLOCK_FUNC(Uart3)   }, /* CLOCKDRV_UART3 */
    {GET_FREQ_FUNC(I2SM),     CONFIG_CLOCK_FUNC(I2SM)    }, /* CLOCKDRV_I2SM */
    {GET_FREQ_FUNC(I2SS),     CONFIG_CLOCK_FUNC(I2SS)    }, /* CLOCKDRV_I2SS */
    {GET_FREQ_FUNC(Adc0),     CONFIG_CLOCK_FUNC(Adc0)    }, /* CLOCKDRV_ADC0 */
    {GET_FREQ_FUNC(Adc1),     CONFIG_CLOCK_FUNC(Adc1)    }, /* CLOCKDRV_ADC1 */
    {GET_FREQ_FUNC(Tclk0),    NULL                       }, /* CLOCKDRV_TCLK0 */
    {GET_FREQ_FUNC(Tclk1),    NULL                       }, /* CLOCKDRV_TCLK1 */
    {GET_FREQ_FUNC(Tclk2),    NULL                       }, /* CLOCKDRV_TCLK2 */
    {GET_FREQ_FUNC(ExtMft0),  CONFIG_CLOCK_FUNC(ExtMft0) }, /* CLOCKDRV_EXT_MFT0 */
    {GET_FREQ_FUNC(ExtMft1),  CONFIG_CLOCK_FUNC(ExtMft1) }, /* CLOCKDRV_EXT_MFT1 */
    {GET_FREQ_FUNC(ExtMft2),  CONFIG_CLOCK_FUNC(ExtMft2) }, /* CLOCKDRV_EXT_MFT2 */
    {GET_FREQ_FUNC(ExtMft3),  CONFIG_CLOCK_FUNC(ExtMft3) }, /* CLOCKDRV_EXT_MFT3 */
    {GET_FREQ_FUNC(ExtMft4),  CONFIG_CLOCK_FUNC(ExtMft4) }, /* CLOCKDRV_EXT_MFT4 */
    {GET_FREQ_FUNC(ExtMft5),  CONFIG_CLOCK_FUNC(ExtMft5) }, /* CLOCKDRV_EXT_MFT5 */
    {GET_FREQ_FUNC(Ewm),      CONFIG_CLOCK_FUNC(Ewm)     }, /* CLOCKDRV_EWM */
};

/*******************************************************************************
 * the functions
 ******************************************************************************/

static inline bool ClockDrv_GetFircFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(AcgReg_GetEnFirc(obj->acgReg) && AcgReg_GetStFircRdy(obj->acgReg))
    {
        *frequency = obj->fircFreq;
        return true;
    }
    return false;
}

static inline bool ClockDrv_SetFircClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* Disable FIRC first, before configure */
    AcgReg_SetEnFirc(obj->acgReg, 0);

    /* Enable FIRC if required */
    if(moduleClkConfig->gating)
    {
        AcgReg_SetEnFirc(obj->acgReg, 1);
        while(AcgReg_GetStFircRdy(obj->acgReg) == 0)
        {
            ; /* Wait until FIRC is locked */
        }
    }

    return true;
}

static inline bool ClockDrv_GetSoscFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(AcgReg_GetEnSosc(obj->acgReg) && AcgReg_GetStSoscRdy(obj->acgReg))
    {
        *frequency = obj->xtalClkFreq;
        return true;
    }
    return false;
}

static inline bool ClockDrv_SetSoscClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* Disable SOSC first, before configure */
    AcgReg_SetEnSosc(obj->acgReg, 0);

    /* Enable SOSC if required */
    if(moduleClkConfig->gating)
    {
        uint8_t soscRange = obj->xtalClkFreq < 4000000 ? 0 : (obj->xtalClkFreq < 8000000 ? 1 : (obj->xtalClkFreq < 24000000 ? 2 : (obj->xtalClkFreq <= 40000000 ? 3 : 4)));
        if(4 == soscRange)
        {
            return false;
        }
        AcgReg_SetOscRange(obj->acgReg, soscRange); /* set SOSC frequency range*/
        AcgReg_SetEnSosc(obj->acgReg, 1);
        while(AcgReg_GetStSoscRdy(obj->acgReg) == 0)
        {
            ; /* Wait until SOSC is locked */
        }
    }

    return true;
}

static inline bool ClockDrv_GetSircFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(AcgReg_GetEnSirc(obj->acgReg) && AcgReg_GetStSircRdy(obj->acgReg))
    {
        *frequency = obj->sircFreq;
        return true;
    }
    return false;
}

static inline bool ClockDrv_SetSircClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* Disable SIRC first, before configure */
    AcgReg_SetEnSirc(obj->acgReg, 0);

    /* Enable SIRC if required */
    if(moduleClkConfig->gating)
    {
        AcgReg_SetEnSirc(obj->acgReg, 1);
        while(AcgReg_GetStSircRdy(obj->acgReg) == 0)
        {
            ; /* Wait until SIRC is locked */
        }
    }

    return true;
}

static inline bool ClockDrv_GetPllFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(AcgReg_GetEnPll(obj->acgReg) && AcgReg_GetStPllLock(obj->acgReg))
    {
        uint32_t freq;
        /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
        switch(AcgReg_GetPllClkIn(obj->acgReg))
        {
        case 0: /* FIRC clock as source */
            retval = ClockDrv_GetFircFreq(obj, &freq);
            break;
        case 1: /* SIRC clock as source */
            retval = ClockDrv_GetSircFreq(obj, &freq);
            break;
        case 2: /* SOSC clock as source */
            retval = ClockDrv_GetSoscFreq(obj, &freq);
            break;
        default:
            break;
        }
        /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

        /* If the source clock is valid */
        if(false == retval)
        {
            return false;
        }

        /* Get the PLL pre-divider */
        uint32_t preDiv = 1;
        /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
        switch(AcgReg_GetPllPreDiv(obj->acgReg))
        {
        case 0:
            preDiv = 1;
            break;
        case 1:
            preDiv = 2;
            break;
        case 2:
            preDiv = 4;
            break;
        case 3:
            preDiv = 8;
            break;
        default:
            /* should not get here */
            break;
        }
        /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

        /* Get the PLL feedback divider setting */
        uint32_t mult = AcgReg_GetPllM(obj->acgReg);
        mult          = (mult == 0 ? 128 : mult);
        /* Get the PLL feedback divider setting */
        uint32_t postDiv = AcgReg_GetPllPosDiv(obj->acgReg);
        postDiv          = (postDiv == 0 ? 8 : postDiv);
        /* Get the PLL Feedback clock divider pre-scaler */
        uint32_t fblSel = AcgReg_GetPllFbkSel(obj->acgReg);
        fblSel          = fblSel + 1;

        /* Calculate the final PLL frequency */
        *frequency = (freq * mult * fblSel) / (2 * preDiv * postDiv);

        retval = true;
    }

    return retval;
}

bool ClockDrv_SetPllClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* Disable PLL first, before configure */
    AcgReg_SetEnPll(obj->acgReg, 0);

    bool retval = true;
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_SOSC: /* SOSC clock as source */
        AcgReg_SetPllClkIn(obj->acgReg, 2);
        break;
    case CLOCKDRV_SIRC: /* SIRC clock as source */
        AcgReg_SetPllClkIn(obj->acgReg, 1);
        break;
    case CLOCKDRV_FIRC: /* FIRC clock as source */
        AcgReg_SetPllClkIn(obj->acgReg, 0);
        break;
    default:
        retval = false;
        break;
    }
    /* If the source clock is valid */
    if(false == retval)
    {
        return false;
    }

    /* Set the PLL pre-divider */
    uint8_t preDiv = moduleClkConfig->pllConfig.preDiv == 1 ? 0 : (moduleClkConfig->pllConfig.preDiv == 2 ? 1 : (moduleClkConfig->pllConfig.preDiv == 4 ? 2 : (moduleClkConfig->pllConfig.preDiv == 8 ? 3 : 0xff)));
    /* If PLL pre-divider is valid */
    if(0xff == preDiv)
    {
        return false;
    }
    AcgReg_SetPllPreDiv(obj->acgReg, preDiv);

    /* Set the PLL feedback divider */
    if(moduleClkConfig->mult >= 1 && moduleClkConfig->mult <= 128)
    {
        AcgReg_SetPllM(obj->acgReg, moduleClkConfig->mult == 128 ? 0 : moduleClkConfig->mult);
    }
    else
    {
        return false;
    }

    /* Set the post-divider */
    if(moduleClkConfig->pllConfig.postDiv >= 1 && moduleClkConfig->pllConfig.postDiv <= 8)
    {
        AcgReg_SetPllPosDiv(obj->acgReg, moduleClkConfig->pllConfig.postDiv == 8 ? 0 : moduleClkConfig->pllConfig.postDiv);
    }
    else
    {
        return false;
    }

    /* Set the feedback clock divider pre-scaler */
    if(moduleClkConfig->pllConfig.fblSel == 1 || moduleClkConfig->pllConfig.fblSel == 2)
    {
        AcgReg_SetPllFbkSel(obj->acgReg, moduleClkConfig->pllConfig.fblSel - 1);
    }
    else
    {
        return false;
    }

    /* Enable PLL if required */
    if(moduleClkConfig->gating)
    {
        AcgReg_SetEnPll(obj->acgReg, 1);
        while(AcgReg_GetStPllLock(obj->acgReg) == 0)
        {
            ; /* Wait until PLL is locked */
        }
    }

    return retval;
}

static inline bool ClockDrv_GetSoscDiv1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnSoscDiv1(obj->scgReg))
    {
        retval = ClockDrv_GetSoscFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetSoscCfgDiv1(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetSoscDiv1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnSoscDiv1(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetSoscCfgDiv1(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnSoscDiv1(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSoscDiv2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnSoscDiv2(obj->scgReg))
    {
        retval = ClockDrv_GetSoscFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetSoscCfgDiv2(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetSoscDiv2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnSoscDiv2(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetSoscCfgDiv2(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnSoscDiv2(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSircDiv1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnSircDiv1(obj->scgReg))
    {
        retval = ClockDrv_GetSircFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetSircCfgDiv1(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetSircDiv1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnSircDiv1(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetSircCfgDiv1(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnSircDiv1(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSircDiv2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnSircDiv2(obj->scgReg))
    {
        retval = ClockDrv_GetSircFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetSircCfgDiv2(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetSircDiv2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnSircDiv2(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetSircCfgDiv2(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnSircDiv2(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetFircDiv1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnFircDiv1(obj->scgReg))
    {
        retval = ClockDrv_GetFircFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetFircCfgDiv1(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetFircDiv1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnFircDiv1(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetFircCfgDiv1(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnFircDiv1(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetFircDiv2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnFircDiv2(obj->scgReg))
    {
        retval = ClockDrv_GetFircFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetFircCfgDiv2(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetFircDiv2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnFircDiv2(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetFircCfgDiv2(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnFircDiv2(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetPllDiv1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnPllDiv1(obj->scgReg))
    {
        retval = ClockDrv_GetPllFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetPllCfgDiv1(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetPllDiv1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnPllDiv1(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetPllCfgDiv1(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnPllDiv1(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetPllDiv2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetCkEnPllDiv2(obj->scgReg))
    {
        retval = ClockDrv_GetPllFreq(obj, &freq);
        if(retval)
        {
            uint32_t div = ((uint32_t)1UL) << ScgReg_GetPllCfgDiv2(obj->scgReg);
            if(div <= 64)
            {
                *frequency = freq / div;
            }
            else
            {
                retval = false;
            }
        }
    }

    return retval;
}

static inline bool ClockDrv_SetPllDiv2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnPllDiv2(obj->scgReg, 0);

    uint8_t div = moduleClkConfig->div == 1 ? 0 : (moduleClkConfig->div == 2 ? 1 : (moduleClkConfig->div == 4 ? 2 : (moduleClkConfig->div == 8 ? 3 : (moduleClkConfig->div == 16 ? 4 : (moduleClkConfig->div == 32 ? 5 : (moduleClkConfig->div == 64 ? 6 : 7))))));
    if(div != 7)
    {
        ScgReg_SetPllCfgDiv2(obj->scgReg, div);
        retval = true;
    }
    /* Enable if required */
    ScgReg_SetCkEnPllDiv2(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSysFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;

    /* Get system clock freq */
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(AcgReg_GetStSysSt(obj->acgReg))
    {
    case 0: /* clk_firc */
        retval = ClockDrv_GetFircFreq(obj, frequency);
        break;
    case 1: /* clk_sosc */
        retval = ClockDrv_GetSoscFreq(obj, frequency);
        break;
    case 2: /* clk_pll */
        retval = ClockDrv_GetPllFreq(obj, frequency);
        break;
    case 3: /* clk_sirc */
        retval = ClockDrv_GetSircFreq(obj, frequency);
        break;
    default:
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetSysClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC ? 3 : 0xff)));
    if(select == 0xff)
    {
        return false;
    }

    AcgReg_SetSysSrcSys(obj->acgReg, select);
    while(AcgReg_GetStSysSt(obj->acgReg) != select);

    return true;
}

static inline bool ClockDrv_GetCoreFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    /* Get system clock freq */
    uint32_t sysFreq;
    retval = ClockDrv_GetSysFreq(obj, &sysFreq);
    if(false == retval)
    {
        return false;
    }
    /* Get core clock freq */
    *frequency = sysFreq / (AcgReg_GetSysDivCore(obj->acgReg) + 1U);

    return retval;
}

static inline bool ClockDrv_SetCoreClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* The clock source is clk_sys */
    if(moduleClkConfig->div >= 1 && moduleClkConfig->div <= 16)
    {
        AcgReg_SetSysDivCore(obj->acgReg, moduleClkConfig->div - 1);
        return true;
    }
    return false;
}

static inline bool ClockDrv_GetApbFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    /* Get core clock freq */
    uint32_t coreFreq;
    retval = ClockDrv_GetCoreFreq(obj, &coreFreq);
    if(false == retval)
    {
        return false;
    }
    /* Get APB clock freq */
    *frequency = coreFreq / (ScgReg_GetCsrDivApb(obj->scgReg) + 1U);

    return retval;
}

static inline bool ClockDrv_SetApbClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* The clock source is core clock */
    if(moduleClkConfig->div >= 1 && moduleClkConfig->div <= 16)
    {
        ScgReg_SetCsrDivApb(obj->scgReg, moduleClkConfig->div - 1);
        return true;
    }
    return false;
}

static inline bool ClockDrv_GetFlsFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    /* Get core clock freq */
    uint32_t coreFreq;
    retval = ClockDrv_GetCoreFreq(obj, &coreFreq);
    if(false == retval)
    {
        return false;
    }
    /* Get flash clock freq */
    if(PccReg_GetCkEn0Fls(obj->pccReg))
    {
        *frequency = coreFreq / (ScgReg_GetCsrDivCntFls(obj->scgReg) + 1U);
    }
    else
    {
        retval = false;
    }

    return retval;
}

static inline bool ClockDrv_SetFlsClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    /* The clock source is core clock */
    if(moduleClkConfig->div >= 1 && moduleClkConfig->div <= 8)
    {
        ScgReg_SetCsrDivCntFls(obj->scgReg, moduleClkConfig->div - 1);
        PccReg_SetCkEn0Fls(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
        return true;
    }
    return false;
}

static inline bool ClockDrv_GetTraceFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    /* Get core clock freq */
    uint32_t coreFreq;
    retval = ClockDrv_GetCoreFreq(obj, &coreFreq);
    if(false == retval)
    {
        return false;
    }
    /* Get flash clock freq */
    if(ScgReg_GetCkEnTrace(obj->scgReg))
    {
        *frequency = coreFreq / (ScgReg_GetCsrDivTrace(obj->scgReg) + 1U);
    }
    else
    {
        retval = false;
    }

    return retval;
}

static inline bool ClockDrv_SetTraceClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    ScgReg_SetCkEnTrace(obj->scgReg, 0);

    /* The clock source is core clock */
    if(moduleClkConfig->div >= 1 && moduleClkConfig->div <= 8)
    {
        ScgReg_SetCsrDivTrace(obj->scgReg, moduleClkConfig->div - 1);
        retval = true;
    }

    /* Enable if required */
    ScgReg_SetCkEnTrace(obj->scgReg, moduleClkConfig->gating ? 1 : 0);
    return retval;
}

static inline bool ClockDrv_GetClkOutFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(ScgReg_GetCkEnOut(obj->scgReg) == 0)
    {
        return false;
    }

    bool     retval = false;
    uint32_t freq   = 0;
    if(ScgReg_GetClkOutSrc(obj->scgReg) == 0)
    {
        /* SCG out selected */
        /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
        switch(ScgReg_GetClkOutScg(obj->scgReg))
        {
        case 0:
            /* clk_fls */
            retval = ClockDrv_GetFlsFreq(obj, &freq);
            break;
        case 1:
            /* clk_sosc */
            retval = ClockDrv_GetSoscFreq(obj, &freq);
            break;
        case 2:
            /* clk_sirc */
            retval = ClockDrv_GetSircFreq(obj, &freq);
            break;
        case 3:
            /* clk_firc */
            retval = ClockDrv_GetFircFreq(obj, &freq);
            break;
        case 4:
            /* clk_pll */
            retval = ClockDrv_GetPllFreq(obj, &freq);
            break;
        case 5:
            /* clk_core */
            retval = ClockDrv_GetCoreFreq(obj, &freq);
            break;
        case 6:
            /* clk_apb */
            retval = ClockDrv_GetApbFreq(obj, &freq);
            break;
        case 7:
            /* clk_firc_div2 */
            retval = ClockDrv_GetFircDiv2Freq(obj, &freq);
            break;
        default:
            break;
        }
        /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    }
    else
    {
        switch(ScgReg_GetClkOutSrc(obj->scgReg))
        {
        case 1:
            /* clk_sosc_div2 */
            retval = ClockDrv_GetSoscDiv2Freq(obj, &freq);
            break;
        case 2:
            /* clk_pll_div2 */
            retval = ClockDrv_GetPllDiv2Freq(obj, &freq);
            break;
        case 3:
            /* clk_sirc_div2 */
            retval = ClockDrv_GetSircDiv2Freq(obj, &freq);
            break;
        case 4:
            /* clk_lpo128, this is alway available */
            retval = ClockDrv_GetLpo128kFreq(obj, &freq);
            break;
        case 5:
            /* clk_lpo32 */
            retval = ClockDrv_GetLpo32kFreq(obj, &freq);
            break;
        case 6:
            /* clk_lpo1 */
            retval = ClockDrv_GetLpo1kFreq(obj, &freq);
            break;
        case 7:
            /* clk_rtc */
            retval = ClockDrv_GetRtcFreq(obj, &freq);
            break;
        default:
            break;
        }
    }

    if(true == retval)
    {
        *frequency = freq / (ScgReg_GetClkOutDiv(obj->scgReg) + 1);
    }

    return retval;
}

static inline bool ClockDrv_SetClkOutClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;

    /* Disable first before configure */
    ScgReg_SetCkEnOut(obj->scgReg, 0);

    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_FLS:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 0);
        break;
    case CLOCKDRV_SOSC:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 1);
        break;
    case CLOCKDRV_SIRC:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 2);
        break;
    case CLOCKDRV_FIRC:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 3);
        break;
    case CLOCKDRV_PLL:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 4);
        break;
    case CLOCKDRV_CORE:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 5);
        break;
    case CLOCKDRV_APB:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 6);
        break;
    case CLOCKDRV_FIRC_DIV2:
        ScgReg_SetClkOutSrc(obj->scgReg, 0); /* scg_out must be selected to enable scg clock out */
        ScgReg_SetClkOutScg(obj->scgReg, 7);
        break;
    case CLOCKDRV_SOSC_DIV2:
        ScgReg_SetClkOutSrc(obj->scgReg, 1);
        break;
    case CLOCKDRV_PLL_DIV2:
        ScgReg_SetClkOutSrc(obj->scgReg, 2);
        break;
    case CLOCKDRV_SIRC_DIV2:
        ScgReg_SetClkOutSrc(obj->scgReg, 3);
        break;
    case CLOCKDRV_LPO_128K:
        ScgReg_SetClkOutSrc(obj->scgReg, 4);
        break;
    case CLOCKDRV_LPO_32K:
        ScgReg_SetClkOutSrc(obj->scgReg, 5);
        break;
    case CLOCKDRV_LPO_1K:
        ScgReg_SetClkOutSrc(obj->scgReg, 6);
        break;
    case CLOCKDRV_RTC:
        ScgReg_SetClkOutSrc(obj->scgReg, 7);
        break;
    default:
        retval = false;
        break;
    }

    if(retval)
    {
        if(moduleClkConfig->div >= 1 && moduleClkConfig->div <= 8)
        {
            ScgReg_SetClkOutDiv(obj->scgReg, moduleClkConfig->div - 1);
        }
        else
        {
            retval = false;
        }
    }

    /* Enable if required */
    ScgReg_SetCkEnOut(obj->scgReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetRtcPadInFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    (void)obj; /* Unused, avoid warning */
    *frequency = obj->rtcClkInFreq;
    return true;
}

static inline bool ClockDrv_GetLpo1kFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(ApcReg_GetClkEnLpo1(obj->apcReg))
    {
        *frequency = LPO_1K_FREQUENCY;
        return true;
    }
    return false;
}

static inline bool ClockDrv_SetLpo1kClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnLpo1(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetLpo32kFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(ApcReg_GetClkEnLpo32(obj->apcReg))
    {
        *frequency = LPO_32K_FREQUENCY;
        return true;
    }
    return false;
}

static inline bool ClockDrv_SetLpo32kClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnLpo32(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetLpo128kFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    (void)obj; /* Unused, avoid warning */
    *frequency = LPO_128K_FREQUENCY;
    return true;
}

static inline bool ClockDrv_GetRtcFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;

    if(ApcReg_GetClkEnRtcSrc(obj->apcReg) == 0)
    {
        return false;
    }

    if(ApcReg_GetClkCfgSrcRtcSrc(obj->apcReg) == 0)
    {
        /* clk_lpo32 */
        retval = ClockDrv_GetLpo32kFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcRtcSrc(obj->apcReg) == 1)
    {
        /* RTC_CLKIN from PAD_PTA7 */
        retval = ClockDrv_GetRtcPadInFreq(obj, frequency);
    }

    return retval;
}

static inline bool ClockDrv_SetRtcClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;

    /* Disable first before configure */
    ApcReg_SetClkEnRtcSrc(obj->apcReg, 0);

    if(moduleClkConfig->source == CLOCKDRV_LPO_32K)
    {
        ApcReg_SetClkCfgSrcRtcSrc(obj->apcReg, 0);
        retval = true;
    }
    else if(moduleClkConfig->source == CLOCKDRV_RTC_PADIN)
    {
        ApcReg_SetClkCfgSrcRtcSrc(obj->apcReg, 1);
        retval = true;
    }

    ApcReg_SetClkEnRtcSrc(obj->apcReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetExtFltFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;

    if(ApcReg_GetClkCfgSrcExtFlt(obj->apcReg) == 0)
    {
        /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcExtFlt(obj->apcReg) == 1)
    {
        /* clk_lpo128 */
        *frequency = LPO_128K_FREQUENCY;
        retval     = true;
    }

    return retval;
}

static inline bool ClockDrv_SetExtFltClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;

    if(moduleClkConfig->source == CLOCKDRV_APB)
    {
        ApcReg_SetClkCfgSrcExtFlt(obj->apcReg, 0);
        retval = true;
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_128K)
    {
        ApcReg_SetClkCfgSrcExtFlt(obj->apcReg, 1);
        retval = true;
    }

    return retval;
}

static inline bool ClockDrv_GetLpitFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;

    /* Check if the lpit clock is enable */
    if(ApcReg_GetClkEnLpit(obj->apcReg) == 0)
    {
        return false;
    }

    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(ApcReg_GetClkCfgSrcLpit(obj->apcReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    case 4: /* clk_lpo128 */
        *frequency = LPO_128K_FREQUENCY;
        retval     = true;
        break;
    default:
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetLpitClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;

    /* Disable first before configure */
    ApcReg_SetClkEnLpit(obj->apcReg, 0);

    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_FIRC_DIV2:
        ApcReg_SetClkCfgSrcLpit(obj->apcReg, 0);
        break;
    case CLOCKDRV_SOSC_DIV2:
        ApcReg_SetClkCfgSrcLpit(obj->apcReg, 1);
        break;
    case CLOCKDRV_PLL_DIV2:
        ApcReg_SetClkCfgSrcLpit(obj->apcReg, 2);
        break;
    case CLOCKDRV_SIRC_DIV2:
        ApcReg_SetClkCfgSrcLpit(obj->apcReg, 3);
        break;
    case CLOCKDRV_LPO_128K:
        ApcReg_SetClkCfgSrcLpit(obj->apcReg, 4);
        break;
    default:
        retval = false;
        break;
    }

    ApcReg_SetClkEnLpit(obj->apcReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetLptmrFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool     retval = false;
    uint32_t freq   = 0;
    /* Check if the lptmr clock is enable */
    if(ApcReg_GetClkEnLptmr(obj->apcReg) == 0)
    {
        return false;
    }
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(ApcReg_GetClkCfgSrcLptmr(obj->apcReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, &freq);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, &freq);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, &freq);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, &freq);
        break;
    case 4: /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, &freq);
        break;
    case 5: /* clk_lpo1 */
        retval = ClockDrv_GetLpo1kFreq(obj, &freq);
        break;
    case 6: /* clk_lpo32 */
        retval = ClockDrv_GetLpo32kFreq(obj, &freq);
        break;
    case 7: /* RTC_CLKIN from PAD_PTA7 */
        retval = ClockDrv_GetRtcPadInFreq(obj, &freq);
        break;
    default:
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    if(retval)
    {
        uint32_t div = ApcReg_GetClkCfgDivLptmr(obj->apcReg) + 1;
        *frequency   = freq / div;
    }

    return retval;
}

static inline bool ClockDrv_SetLptmrClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;

    /* Disable first before configure */
    ApcReg_SetClkEnLptmr(obj->apcReg, 0);

    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_FIRC_DIV2:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 0);
        break;
    case CLOCKDRV_SOSC_DIV2:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 1);
        break;
    case CLOCKDRV_PLL_DIV2:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 2);
        break;
    case CLOCKDRV_SIRC_DIV2:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 3);
        break;
    case CLOCKDRV_LPO_128K:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 4);
        break;
    case CLOCKDRV_LPO_1K:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 5);
        break;
    case CLOCKDRV_LPO_32K:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 6);
        break;
    case CLOCKDRV_RTC_PADIN:
        ApcReg_SetClkCfgSrcLptmr(obj->apcReg, 7);
        break;
    default:
        retval = false;
        break;
    }

    if(moduleClkConfig->div >= 1 && moduleClkConfig->div <= 8)
    {
        ApcReg_SetClkCfgDivLptmr(obj->apcReg, moduleClkConfig->div - 1);
    }
    else
    {
        retval = false;
    }

    ApcReg_SetClkEnLptmr(obj->apcReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetRtcCntFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;

    /* Check if the rtc function clock is enable */
    if(ApcReg_GetClkEnRtcCnt(obj->apcReg) == 0)
    {
        return false;
    }

    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    if(ApcReg_GetClkCfgSrcRtcCnt(obj->apcReg) == 0)
    {
        /* clk_rtc */
        retval = ClockDrv_GetRtcFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcRtcCnt(obj->apcReg) == 1)
    {
        /* clk_lpo1 */
        retval = ClockDrv_GetLpo1kFreq(obj, frequency);
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetRtcCntClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;

    /* Disable first before configure */
    ApcReg_SetClkEnRtcCnt(obj->apcReg, 0);

    if(moduleClkConfig->source == CLOCKDRV_RTC)
    {
        ApcReg_SetClkCfgSrcRtcCnt(obj->apcReg, 0);
        retval = true;
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_1K)
    {
        ApcReg_SetClkCfgSrcRtcCnt(obj->apcReg, 1);
        retval = true;
    }

    ApcReg_SetClkEnRtcCnt(obj->apcReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetPortAFltFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkCfgSrcPortAFlt(obj->apcReg) == 0)
    { /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcPortAFlt(obj->apcReg) == 1)
    { /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortAFltClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    if(moduleClkConfig->source == CLOCKDRV_APB)
    { /* clk_apb */
        ApcReg_SetClkCfgSrcPortAFlt(obj->apcReg, 0);
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_128K)
    { /* clk_lpo128 */
        ApcReg_SetClkCfgSrcPortAFlt(obj->apcReg, 1);
    }
    return retval;
}

static inline bool ClockDrv_GetPortBFltFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkCfgSrcPortBFlt(obj->apcReg) == 0)
    { /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcPortBFlt(obj->apcReg) == 1)
    { /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortBFltClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    if(moduleClkConfig->source == CLOCKDRV_APB)
    { /* clk_apb */
        ApcReg_SetClkCfgSrcPortBFlt(obj->apcReg, 0);
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_128K)
    { /* clk_lpo128 */
        ApcReg_SetClkCfgSrcPortBFlt(obj->apcReg, 1);
    }
    return retval;
}

static inline bool ClockDrv_GetPortCFltFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkCfgSrcPortCFlt(obj->apcReg) == 0)
    { /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcPortCFlt(obj->apcReg) == 1)
    { /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortCFltClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    if(moduleClkConfig->source == CLOCKDRV_APB)
    { /* clk_apb */
        ApcReg_SetClkCfgSrcPortCFlt(obj->apcReg, 0);
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_128K)
    { /* clk_lpo128 */
        ApcReg_SetClkCfgSrcPortCFlt(obj->apcReg, 1);
    }
    return retval;
}

static inline bool ClockDrv_GetPortDFltFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkCfgSrcPortDFlt(obj->apcReg) == 0)
    { /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcPortDFlt(obj->apcReg) == 1)
    { /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortDFltClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    if(moduleClkConfig->source == CLOCKDRV_APB)
    { /* clk_apb */
        ApcReg_SetClkCfgSrcPortDFlt(obj->apcReg, 0);
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_128K)
    { /* clk_lpo128 */
        ApcReg_SetClkCfgSrcPortDFlt(obj->apcReg, 1);
    }
    return retval;
}

static inline bool ClockDrv_GetPortEFltFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkCfgSrcPortEFlt(obj->apcReg) == 0)
    { /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcPortEFlt(obj->apcReg) == 1)
    { /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortEFltClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    if(moduleClkConfig->source == CLOCKDRV_APB)
    { /* clk_apb */
        ApcReg_SetClkCfgSrcPortEFlt(obj->apcReg, 0);
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPO_128K)
    { /* clk_lpo128 */
        ApcReg_SetClkCfgSrcPortEFlt(obj->apcReg, 1);
    }
    return retval;
}

static inline bool ClockDrv_GetPortAFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkEnPortA(obj->apcReg))
    {
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortAClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnPortA(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPortBFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkEnPortB(obj->apcReg))
    {
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortBClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnPortB(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPortCFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkEnPortC(obj->apcReg))
    {
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortCClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnPortC(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPortDFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkEnPortD(obj->apcReg))
    {
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortDClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnPortD(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPortEFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;
    if(ApcReg_GetClkEnPortE(obj->apcReg))
    {
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    return retval;
}

static inline bool ClockDrv_SetPortEClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    ApcReg_SetClkEnPortE(obj->apcReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetCmp0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    bool retval = false;

    /* Check if the cmp0 clock is enable */
    if(ApcReg_GetClkEnCmp0(obj->apcReg) == 0)
    {
        return false;
    }

    if(ApcReg_GetClkCfgSrcCmp0(obj->apcReg) == 0)
    { /* clk_apb */
        retval = ClockDrv_GetApbFreq(obj, frequency);
    }
    else if(ApcReg_GetClkCfgSrcCmp0(obj->apcReg) == 1)
    { /* clk_lptmr */
        retval = ClockDrv_GetLptmrFreq(obj, frequency);
    }

    return retval;
}

static inline bool ClockDrv_SetCmp0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;

    /* Disable first before configure */
    ApcReg_SetClkEnCmp0(obj->apcReg, 0);

    if(moduleClkConfig->source == CLOCKDRV_APB)
    {
        ApcReg_SetClkCfgSrcCmp0(obj->apcReg, 0);
        retval = true;
    }
    else if(moduleClkConfig->source == CLOCKDRV_LPTMR)
    {
        ApcReg_SetClkCfgSrcCmp0(obj->apcReg, 1);
        retval = true;
    }

    ApcReg_SetClkEnCmp0(obj->apcReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetDmaFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Dma(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetDmaClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Dma(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetEimFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Eim(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetEimClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Eim(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetErmFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Erm(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetErmClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Erm(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetMpuFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Mpu(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetMpuClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Mpu(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetCrcFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Crc(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetCrcClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Crc(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetCseFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Cse(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetCseClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Cse(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetMft0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft0(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetMft0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Mft0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetMft1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft1(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetMft1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Mft1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetMft2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft2(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetMft2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Mft2(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetMft3Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft3(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
}

static inline bool ClockDrv_SetMft3Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Mft3(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetMft4Freq(const ClockDrvType *obj, uint32_t *frequency)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    if(PccReg_GetCkEn1Mft4(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_SetMft4Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    PccReg_SetCkEn1Mft4(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_GetMft5Freq(const ClockDrvType *obj, uint32_t *frequency)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    if(PccReg_GetCkEn1Mft5(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetCoreFreq(obj, frequency);
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_SetMft5Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    PccReg_SetCkEn1Mft5(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_GetMscmFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Mscm(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetMscmClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Mscm(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetDmaMuxFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0DmaMux(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetDmaMuxClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0DmaMux(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPdb0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Pdb0(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPdb0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Pdb0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPdb1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Pdb1(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPdb1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Pdb1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPwmLite0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Pwm0(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPwmLite0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Pwm0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPwmLite1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Pwm1(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPwmLite1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Pwm1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPwmLite2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Pwm2(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPwmLite2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Pwm2(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPwmLite3Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Pwm3(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPwmLite3Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Pwm3(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPwmLite4Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Pwm4(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPwmLite4Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Pwm4(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetPrngFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Prng(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetApbFreq(obj, frequency);
}

static inline bool ClockDrv_SetPrngClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0Prng(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetCmusFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Cmus(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetSoscFreq(obj, frequency);
}

static inline bool ClockDrv_SetCmusClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Cmus(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetCmufFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Cmuf(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetFircFreq(obj, frequency);
}

static inline bool ClockDrv_SetCmufClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Cmuf(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetFccuFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Fccu(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetFircFreq(obj, frequency);
}

static inline bool ClockDrv_SetFccuClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Fccu(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetCmupFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Cmup(obj->pccReg) == 0)
    {
        return false;
    }
    return ClockDrv_GetPllFreq(obj, frequency);
}

static inline bool ClockDrv_SetCmupClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn1Cmup(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetI2CFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0I2C(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcI2C(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetI2CClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0I2C(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcI2C(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0I2C(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSpi0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Spi0(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcSpi0(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetSpi0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Spi0(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcSpi0(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Spi0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSpi1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Spi1(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcSpi1(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetSpi1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Spi1(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcSpi1(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Spi1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSpi2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Spi2(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcSpi2(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetSpi2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Spi2(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcSpi2(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Spi2(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetSpi3Freq(const ClockDrvType *obj, uint32_t *frequency)
{
#if FEATURE_SPI_INSTANCE_NUM == 4
    if(PccReg_GetCkEn0Spi3(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcSpi3(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_SetSpi3Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
#if FEATURE_SPI_INSTANCE_NUM == 4
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Spi3(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcSpi3(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Spi3(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_GetUart0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Uart0(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcUart0(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetUart0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Uart0(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcUart0(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Uart0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetUart1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Uart1(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcUart1(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetUart1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Uart1(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcUart1(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Uart1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetUart2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Uart2(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcUart2(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetUart2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Uart2(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcUart2(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Uart2(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetUart3Freq(const ClockDrvType *obj, uint32_t *frequency)
{
#if FEATURE_UART_INSTANCE_NUM == 4
    if(PccReg_GetCkEn0Uart3(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcUart3(obj->pccReg))
    {
    case 0: /* clk_firc_div2 */
        retval = ClockDrv_GetFircDiv2Freq(obj, frequency);
        break;
    case 1: /* clk_sosc_div2 */
        retval = ClockDrv_GetSoscDiv2Freq(obj, frequency);
        break;
    case 2: /* clk_pll_div2 */
        retval = ClockDrv_GetPllDiv2Freq(obj, frequency);
        break;
    case 3: /* clk_sirc_div2 */
        retval = ClockDrv_GetSircDiv2Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_SetUart3Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
#if FEATURE_UART_INSTANCE_NUM == 4
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Uart3(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC_DIV2 ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC_DIV2 ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL_DIV2 ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC_DIV2 ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcUart3(obj->pccReg, select);
        retval = true;
    }

    PccReg_SetCkEn0Uart3(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_GetI2SMFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0I2SM(obj->pccReg) == 0)
    {
        return false;
    }

    bool     retval = true;
    uint32_t freq   = 0;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl0SrcI2SM(obj->pccReg))
    {
    case 0: /* clk_firc */
        retval = ClockDrv_GetFircFreq(obj, &freq);
        break;
    case 1: /* clk_sosc */
        retval = ClockDrv_GetSoscFreq(obj, &freq);
        break;
    case 2: /* clk_pll */
        retval = ClockDrv_GetPllFreq(obj, &freq);
        break;
    case 3: /* clk_sirc */
        retval = ClockDrv_GetSircFreq(obj, &freq);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    /* Divider */
    uint32_t div = PccReg_GetCkCtl1DivI2SM(obj->pccReg) + 1;
    if(div < 2)
    {
        div = 2;
    }
    *frequency = freq / div;

    return retval;
}

static inline bool ClockDrv_SetI2SMClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0I2SM(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl0SrcI2SM(obj->pccReg, select);
        retval = true;
    }

    /* Divider */
    if(true == retval)
    {
        if(moduleClkConfig->div >= 2 && moduleClkConfig->div <= 64)
        {
            PccReg_SetCkCtl1DivI2SM(obj->pccReg, moduleClkConfig->div - 1);
        }
        else
        {
            retval = false;
        }
    }

    /* Enable if required */
    PccReg_SetCkEn0I2SM(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetI2SSFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    /* Can not get the frequency of I2S slave */
    return false;
}

static inline bool ClockDrv_SetI2SSClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    PccReg_SetCkEn0I2SS(obj->pccReg, moduleClkConfig->gating ? 1 : 0);
    return true;
}

static inline bool ClockDrv_GetAdc0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Adc0(obj->pccReg) == 0)
    {
        return false;
    }

    bool     retval = true;
    uint32_t freq   = 0;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl2SrcAdc0(obj->pccReg))
    {
    case 0: /* clk_firc */
        retval = ClockDrv_GetFircFreq(obj, &freq);
        break;
    case 1: /* clk_sosc */
        retval = ClockDrv_GetSoscFreq(obj, &freq);
        break;
    case 2: /* clk_pll */
        retval = ClockDrv_GetPllFreq(obj, &freq);
        break;
    case 3: /* clk_sirc */
        retval = ClockDrv_GetSircFreq(obj, &freq);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    /* Divider */
    uint32_t div = PccReg_GetCkCtl2DivAdc0(obj->pccReg);
    div          = div == 0 ? 1 : div * 2;
    *frequency   = freq / div;

    return retval;
}

static inline bool ClockDrv_SetAdc0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Adc0(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl2SrcAdc0(obj->pccReg, select);
        retval = true;
    }

    /* Divider */
    if(true == retval)
    {
        uint8_t div = moduleClkConfig->div / 2u;
        if(div < 8)
        {
            PccReg_SetCkCtl2DivAdc0(obj->pccReg, div);
        }
        else
        {
            retval = false;
        }
    }

    /* Enable if required */
    PccReg_SetCkEn0Adc0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetAdc1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Adc1(obj->pccReg) == 0)
    {
        return false;
    }

    bool     retval = true;
    uint32_t freq   = 0;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl2SrcAdc1(obj->pccReg))
    {
    case 0: /* clk_firc */
        retval = ClockDrv_GetFircFreq(obj, &freq);
        break;
    case 1: /* clk_sosc */
        retval = ClockDrv_GetSoscFreq(obj, &freq);
        break;
    case 2: /* clk_pll */
        retval = ClockDrv_GetPllFreq(obj, &freq);
        break;
    case 3: /* clk_sirc */
        retval = ClockDrv_GetSircFreq(obj, &freq);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    /* Divider */
    uint32_t div = PccReg_GetCkCtl2DivAdc1(obj->pccReg);
    div          = div == 0 ? 1 : div * 2;
    *frequency   = freq / div;

    return retval;
}

static inline bool ClockDrv_SetAdc1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = false;
    /* Disable first before configure */
    PccReg_SetCkEn0Adc1(obj->pccReg, 0);
    /* Select source */
    uint8_t select = moduleClkConfig->source == CLOCKDRV_FIRC ? 0 : (moduleClkConfig->source == CLOCKDRV_SOSC ? 1 : (moduleClkConfig->source == CLOCKDRV_PLL ? 2 : (moduleClkConfig->source == CLOCKDRV_SIRC ? 3 : 0xff)));
    if(select != 0xff)
    {
        PccReg_SetCkCtl2SrcAdc1(obj->pccReg, select);
        retval = true;
    }

    /* Divider */
    if(true == retval)
    {
        uint8_t div = moduleClkConfig->div / 2u;
        if(div < 8)
        {
            PccReg_SetCkCtl2DivAdc1(obj->pccReg, div);
        }
        else
        {
            retval = false;
        }
    }

    /* Enable if required */
    PccReg_SetCkEn0Adc1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetTclk0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    (void)obj; /* Unused, avoid warning */
    *frequency = obj->tclkFreq[0];
    return true;
}

static inline bool ClockDrv_GetTclk1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    (void)obj; /* Unused, avoid warning */
    *frequency = obj->tclkFreq[1];
    return true;
}

static inline bool ClockDrv_GetTclk2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    (void)obj; /* Unused, avoid warning */
    *frequency = obj->tclkFreq[2];
    return true;
}

static inline bool ClockDrv_GetExtMft0Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft0(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl3SrcExtMft0(obj->pccReg))
    {
    case 0: /* TCLK0 */
        retval = ClockDrv_GetTclk0Freq(obj, frequency);
        break;
    case 1: /* TCLK1 */
        retval = ClockDrv_GetTclk1Freq(obj, frequency);
        break;
    case 2: /* TCLK2 */
        retval = ClockDrv_GetTclk2Freq(obj, frequency);
        break;
    case 3: /* clk_firc_div1 */
        retval = ClockDrv_GetFircDiv1Freq(obj, frequency);
        break;
    case 4: /* clk_sosc_div1 */
        retval = ClockDrv_GetSoscDiv1Freq(obj, frequency);
        break;
    case 5: /* clk_pll_div1 */
        retval = ClockDrv_GetPllDiv1Freq(obj, frequency);
        break;
    case 6: /* clk_sirc_div1 */
    case 7: /* clk_sirc_div1 */
        retval = ClockDrv_GetSircDiv1Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetExtMft0Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn1Mft0(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_TCLK0: /* TCLK0 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 0);
        break;
    case CLOCKDRV_TCLK1: /* TCLK1 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 1);
        break;
    case CLOCKDRV_TCLK2: /* TCLK2 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 2);
        break;
    case CLOCKDRV_FIRC_DIV1: /* clk_firc_div1 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 3);
        break;
    case CLOCKDRV_SOSC_DIV1: /* clk_sosc_div1 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 4);
        break;
    case CLOCKDRV_PLL_DIV1: /* clk_pll_div1 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 5);
        break;
    case CLOCKDRV_SIRC_DIV1: /* clk_sirc_div1 */
        PccReg_SetCkCtl3SrcExtMft0(obj->pccReg, 6);
        /* Actually it can also be 7 */
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn1Mft0(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetExtMft1Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft1(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl3SrcExtMft1(obj->pccReg))
    {
    case 0: /* TCLK0 */
        retval = ClockDrv_GetTclk0Freq(obj, frequency);
        break;
    case 1: /* TCLK1 */
        retval = ClockDrv_GetTclk1Freq(obj, frequency);
        break;
    case 2: /* TCLK2 */
        retval = ClockDrv_GetTclk2Freq(obj, frequency);
        break;
    case 3: /* clk_firc_div1 */
        retval = ClockDrv_GetFircDiv1Freq(obj, frequency);
        break;
    case 4: /* clk_sosc_div1 */
        retval = ClockDrv_GetSoscDiv1Freq(obj, frequency);
        break;
    case 5: /* clk_pll_div1 */
        retval = ClockDrv_GetPllDiv1Freq(obj, frequency);
        break;
    case 6: /* clk_sirc_div1 */
    case 7: /* clk_sirc_div1 */
        retval = ClockDrv_GetSircDiv1Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetExtMft1Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn1Mft1(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_TCLK0: /* TCLK0 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 0);
        break;
    case CLOCKDRV_TCLK1: /* TCLK1 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 1);
        break;
    case CLOCKDRV_TCLK2: /* TCLK2 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 2);
        break;
    case CLOCKDRV_FIRC_DIV1: /* clk_firc_div1 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 3);
        break;
    case CLOCKDRV_SOSC_DIV1: /* clk_sosc_div1 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 4);
        break;
    case CLOCKDRV_PLL_DIV1: /* clk_pll_div1 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 5);
        break;
    case CLOCKDRV_SIRC_DIV1: /* clk_sirc_div1 */
        PccReg_SetCkCtl3SrcExtMft1(obj->pccReg, 6);
        /* Actually it can also be 7 */
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn1Mft1(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetExtMft2Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft2(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl3SrcExtMft2(obj->pccReg))
    {
    case 0: /* TCLK0 */
        retval = ClockDrv_GetTclk0Freq(obj, frequency);
        break;
    case 1: /* TCLK1 */
        retval = ClockDrv_GetTclk1Freq(obj, frequency);
        break;
    case 2: /* TCLK2 */
        retval = ClockDrv_GetTclk2Freq(obj, frequency);
        break;
    case 3: /* clk_firc_div1 */
        retval = ClockDrv_GetFircDiv1Freq(obj, frequency);
        break;
    case 4: /* clk_sosc_div1 */
        retval = ClockDrv_GetSoscDiv1Freq(obj, frequency);
        break;
    case 5: /* clk_pll_div1 */
        retval = ClockDrv_GetPllDiv1Freq(obj, frequency);
        break;
    case 6: /* clk_sirc_div1 */
    case 7: /* clk_sirc_div1 */
        retval = ClockDrv_GetSircDiv1Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetExtMft2Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn1Mft2(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_TCLK0: /* TCLK0 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 0);
        break;
    case CLOCKDRV_TCLK1: /* TCLK1 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 1);
        break;
    case CLOCKDRV_TCLK2: /* TCLK2 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 2);
        break;
    case CLOCKDRV_FIRC_DIV1: /* clk_firc_div1 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 3);
        break;
    case CLOCKDRV_SOSC_DIV1: /* clk_sosc_div1 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 4);
        break;
    case CLOCKDRV_PLL_DIV1: /* clk_pll_div1 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 5);
        break;
    case CLOCKDRV_SIRC_DIV1: /* clk_sirc_div1 */
        PccReg_SetCkCtl3SrcExtMft2(obj->pccReg, 6);
        /* Actually it can also be 7 */
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn1Mft2(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetExtMft3Freq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn1Mft3(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl3SrcExtMft3(obj->pccReg))
    {
    case 0: /* TCLK0 */
        retval = ClockDrv_GetTclk0Freq(obj, frequency);
        break;
    case 1: /* TCLK1 */
        retval = ClockDrv_GetTclk1Freq(obj, frequency);
        break;
    case 2: /* TCLK2 */
        retval = ClockDrv_GetTclk2Freq(obj, frequency);
        break;
    case 3: /* clk_firc_div1 */
        retval = ClockDrv_GetFircDiv1Freq(obj, frequency);
        break;
    case 4: /* clk_sosc_div1 */
        retval = ClockDrv_GetSoscDiv1Freq(obj, frequency);
        break;
    case 5: /* clk_pll_div1 */
        retval = ClockDrv_GetPllDiv1Freq(obj, frequency);
        break;
    case 6: /* clk_sirc_div1 */
    case 7: /* clk_sirc_div1 */
        retval = ClockDrv_GetSircDiv1Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
}

static inline bool ClockDrv_SetExtMft3Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn1Mft3(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_TCLK0: /* TCLK0 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 0);
        break;
    case CLOCKDRV_TCLK1: /* TCLK1 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 1);
        break;
    case CLOCKDRV_TCLK2: /* TCLK2 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 2);
        break;
    case CLOCKDRV_FIRC_DIV1: /* clk_firc_div1 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 3);
        break;
    case CLOCKDRV_SOSC_DIV1: /* clk_sosc_div1 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 4);
        break;
    case CLOCKDRV_PLL_DIV1: /* clk_pll_div1 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 5);
        break;
    case CLOCKDRV_SIRC_DIV1: /* clk_sirc_div1 */
        PccReg_SetCkCtl3SrcExtMft3(obj->pccReg, 6);
        /* Actually it can also be 7 */
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn1Mft3(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

static inline bool ClockDrv_GetExtMft4Freq(const ClockDrvType *obj, uint32_t *frequency)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    if(PccReg_GetCkEn1Mft4(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl3SrcExtMft4(obj->pccReg))
    {
    case 0: /* TCLK0 */
        retval = ClockDrv_GetTclk0Freq(obj, frequency);
        break;
    case 1: /* TCLK1 */
        retval = ClockDrv_GetTclk1Freq(obj, frequency);
        break;
    case 2: /* TCLK2 */
        retval = ClockDrv_GetTclk2Freq(obj, frequency);
        break;
    case 3: /* clk_firc_div1 */
        retval = ClockDrv_GetFircDiv1Freq(obj, frequency);
        break;
    case 4: /* clk_sosc_div1 */
        retval = ClockDrv_GetSoscDiv1Freq(obj, frequency);
        break;
    case 5: /* clk_pll_div1 */
        retval = ClockDrv_GetPllDiv1Freq(obj, frequency);
        break;
    case 6: /* clk_sirc_div1 */
    case 7: /* clk_sirc_div1 */
        retval = ClockDrv_GetSircDiv1Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_SetExtMft4Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn1Mft4(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_TCLK0: /* TCLK0 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 0);
        break;
    case CLOCKDRV_TCLK1: /* TCLK1 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 1);
        break;
    case CLOCKDRV_TCLK2: /* TCLK2 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 2);
        break;
    case CLOCKDRV_FIRC_DIV1: /* clk_firc_div1 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 3);
        break;
    case CLOCKDRV_SOSC_DIV1: /* clk_sosc_div1 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 4);
        break;
    case CLOCKDRV_PLL_DIV1: /* clk_pll_div1 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 5);
        break;
    case CLOCKDRV_SIRC_DIV1: /* clk_sirc_div1 */
        PccReg_SetCkCtl3SrcExtMft4(obj->pccReg, 6);
        /* Actually it can also be 7 */
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn1Mft4(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_GetExtMft5Freq(const ClockDrvType *obj, uint32_t *frequency)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    if(PccReg_GetCkEn1Mft5(obj->pccReg) == 0)
    {
        return false;
    }

    bool retval = true;
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    switch(PccReg_GetCkCtl3SrcExtMft5(obj->pccReg))
    {
    case 0: /* TCLK0 */
        retval = ClockDrv_GetTclk0Freq(obj, frequency);
        break;
    case 1: /* TCLK1 */
        retval = ClockDrv_GetTclk1Freq(obj, frequency);
        break;
    case 2: /* TCLK2 */
        retval = ClockDrv_GetTclk2Freq(obj, frequency);
        break;
    case 3: /* clk_firc_div1 */
        retval = ClockDrv_GetFircDiv1Freq(obj, frequency);
        break;
    case 4: /* clk_sosc_div1 */
        retval = ClockDrv_GetSoscDiv1Freq(obj, frequency);
        break;
    case 5: /* clk_pll_div1 */
        retval = ClockDrv_GetPllDiv1Freq(obj, frequency);
        break;
    case 6: /* clk_sirc_div1 */
    case 7: /* clk_sirc_div1 */
        retval = ClockDrv_GetSircDiv1Freq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_SetExtMft5Clock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
#if FEATURE_MFT_INSTANCE_NUM == 6
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn1Mft5(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_TCLK0: /* TCLK0 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 0);
        break;
    case CLOCKDRV_TCLK1: /* TCLK1 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 1);
        break;
    case CLOCKDRV_TCLK2: /* TCLK2 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 2);
        break;
    case CLOCKDRV_FIRC_DIV1: /* clk_firc_div1 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 3);
        break;
    case CLOCKDRV_SOSC_DIV1: /* clk_sosc_div1 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 4);
        break;
    case CLOCKDRV_PLL_DIV1: /* clk_pll_div1 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 5);
        break;
    case CLOCKDRV_SIRC_DIV1: /* clk_sirc_div1 */
        PccReg_SetCkCtl3SrcExtMft5(obj->pccReg, 6);
        /* Actually it can also be 7 */
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn1Mft5(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
#else
    /* Not available */
    return false;
#endif
}

static inline bool ClockDrv_GetEwmFreq(const ClockDrvType *obj, uint32_t *frequency)
{
    if(PccReg_GetCkEn0Ewm(obj->pccReg) == 0)
    {
        return false;
    }
    bool retval = true;
    switch(PccReg_GetCkCtl0SrcEwm(obj->pccReg))
    {
    case 0: /* clk_lpo128 */
        retval = ClockDrv_GetLpo128kFreq(obj, frequency);
        break;
    case 1: /* clk_lpo32 */
        retval = ClockDrv_GetLpo32kFreq(obj, frequency);
        break;
    case 2: /* clk_lpo1 */
        retval = ClockDrv_GetLpo1kFreq(obj, frequency);
        break;
    default:
        retval = false;
        break;
    }
    return retval;
}

static inline bool ClockDrv_SetEwmClock(ClockDrvType *obj, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    bool retval = true;
    /* Disable first before configure */
    PccReg_SetCkEn0Ewm(obj->pccReg, 0);
    /* Select source */
    switch(moduleClkConfig->source)
    {
    case CLOCKDRV_LPO_128K: /* clk_lpo128 */
        PccReg_SetCkCtl0SrcEwm(obj->pccReg, 0);
        break;
    case CLOCKDRV_LPO_32K: /* clk_lpo32 */
        PccReg_SetCkCtl0SrcEwm(obj->pccReg, 1);
        break;
    case CLOCKDRV_LPO_1K: /* clk_lpo1 */
        PccReg_SetCkCtl0SrcEwm(obj->pccReg, 2);
        break;
    default:
        retval = false;
        break;
    }

    PccReg_SetCkEn0Ewm(obj->pccReg, moduleClkConfig->gating ? 1 : 0);

    return retval;
}

void ClockDrv_Init(ClockDrvType                  *obj,
                   struct _AcgRegType_           *acgReg,
                   struct _ApcRegType_           *apcReg,
                   struct _ScgRegType_           *scgReg,
                   struct _PccRegType_           *pccReg,
                   const ClockDrv_InitParamsType *initParams)
{
    obj->acgReg       = acgReg;
    obj->apcReg       = apcReg;
    obj->scgReg       = scgReg;
    obj->pccReg       = pccReg;
    obj->fircFreq     = initParams->fircFreq;
    obj->sircFreq     = initParams->sircFreq;
    obj->xtalClkFreq  = initParams->xtalClkFreq;
    obj->rtcClkInFreq = initParams->rtcClkInFreq;
    uint8_t i         = 0;
    for(i = 0; i < TCLK_INPUTS_NUM; ++i)
    {
        obj->tclkFreq[i] = initParams->tclkFreq[i];
    }
}

bool ClockDrv_GetFreq(const ClockDrvType *obj, ClockDrv_NamesType clockName, uint32_t *frequency)
{
    if(clockName >= CLOCKDRV_CLOCK_NUM)
    {
        return false;
    }

    bool retval = false;
    if(c_clockFuncTable[clockName].getFreqFunc != NULL)
    {
        retval = c_clockFuncTable[clockName].getFreqFunc(obj, frequency);
    }
    return retval;
}

bool ClockDrv_ConfigureClock(ClockDrvType *obj, ClockDrv_NamesType clockName, const ClockDrv_ModuleClkConfigType *moduleClkConfig)
{
    if(clockName >= CLOCKDRV_CLOCK_NUM)
    {
        return false;
    }

    bool retval = false;
    if(c_clockFuncTable[clockName].setClockFunc != NULL)
    {
        AcgReg_SetLockKey(obj->acgReg, 0xFA8623E4); /* Unlock ACG */
        ApcReg_SetLockKey(obj->apcReg, 0xC1C51F9C); /* Unlock APC */
        PccReg_SetLockKey(obj->pccReg, 0x70637577); /* Unlock PCC */
        ScgReg_SetLockKey(obj->scgReg, 0x53436D65); /* Unlock SCG */
        retval = c_clockFuncTable[clockName].setClockFunc(obj, moduleClkConfig);
        AcgReg_SetLockKey(obj->acgReg, 0); /* Lock ACG again */
        ApcReg_SetLockKey(obj->apcReg, 0); /* Lock APC again */
        PccReg_SetLockKey(obj->pccReg, 0); /* Lock PCC again */
        ScgReg_SetLockKey(obj->scgReg, 0); /* Lock SCG again */
    }

    return retval;
}
