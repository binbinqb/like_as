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

#include "system_M014x.h"
#include "../cpu_drv.h"

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

void SystemInit(void)
{
    /* Enable cache */
    CACHE->CTRL = 0x1C7;
    /* Enable PFLASH prefetch */
    SimReg_SetFlashPFlsPfbEn(SIM, 1);

    /* Setup the clock */
    AcgReg_SetLockKey(ACG, 0xFA8623E4);   /* Unlock ACG */
    ScgReg_SetLockKey(SCG, 0x53436D65);   /* Unlock SCG */

    /* Switch system clock to default clock */
    if(AcgReg_GetStSysSt(ACG) != 0)
    {
        AcgReg_SetSysSrcSys(ACG, 0);
        while(AcgReg_GetStSysSt(ACG) != 0)
        {
            ;
        }
        /* Flash AHB bus read access time configure */
        FtfcReg_SetFcnfgBusReadTm(FTFC, 0); /* 1T required */
    }

#if defined (_USE_EXT_OSC_)
    /* Use External oscillator */
    AcgReg_SetEnSosc(ACG, 0); /* disable SOSC */
    AcgReg_SetOscRange(ACG, 3); /* set SOSC frequency range(use max value when SOSC as the clock source of the PLL) */
    AcgReg_SetEnSosc(ACG, 1); /* enable SOSC */
    while(AcgReg_GetStSoscRdy(ACG) == 0); /* wait until SOSC is ready */
    
    /* Configure PLL */
    AcgReg_SetEnPll(ACG, 0); /* Disable PLL first */
    /* PLL configuration:
     * - PLL input clock source : SOSC
     * - PLL pre-divider : 1
     * - feedback divider : 45
     * - PLL Feedback clock divider pre-scaler : 1
     * - PLL post-divider setting : 3
     * Final PLL output frequency is 16M(SOSC) * 45 / 3 / 2 = 120M
     */
    AcgReg_SetPllClkIn(ACG, 2);
    AcgReg_SetPllPreDiv(ACG, 0);
    AcgReg_SetPllM(ACG, 45);
    AcgReg_SetPllFbkSel(ACG, 0);
    AcgReg_SetPllPosDiv(ACG, 3);
    /* SCG PLL configuration:
     * - PLL DIV1 clock divider : 1
     * - PLL DIV2 clock divider : 1
     */
    ScgReg_SetPllCfgDiv1(SCG, 0);
    ScgReg_SetPllCfgDiv2(SCG, 0);

    /* delay before enable PLL */
    SysTick->LOAD = 48000U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = 5U;     /* SysTick uses the processor clock and enable sysTick */
    while(SysTick->CTRL < 0x10000){
        ;/* wait for COUNTFLAG setting*/
    }
    /*recover sysTick register*/
    SysTick->CTRL = 4U;
    SysTick->LOAD = 0U;
    SysTick->VAL  = 0U;

    /* Enable PLL */
    AcgReg_SetEnPll(ACG, 1);

    while(AcgReg_GetStPllLock(ACG) == 0); /* Wait until PLL is locked */

    /* Set Core and APB clock source divider */
    AcgReg_SetSysDivCore(ACG, 0); /* Divide-by-1 */
    ScgReg_SetCsrDivApb(SCG, 1);  /* Divide-by-2 */

    /* Flash frequency MUST be 8M */
    ScgReg_SetCsrDivCntFls(SCG, 14); /* Divide-by-15 */
    /* Flash AHB bus read access time configure */
    FtfcReg_SetFcnfgBusReadTm(FTFC, 2); /* 160M->3, 120M->2, 80M->1, 48M->0 */

    /* Set Core clock source to PLL */
    AcgReg_SetSysSrcSys(ACG, 2); /* select pll as clock source */
#else
    /* Use on-chip internal clock */

    /* Configure PLL */
    AcgReg_SetEnPll(ACG, 0); /* Disable PLL first */
    /* PLL configuration:
     * - PLL input clock source : FIRC
     * - PLL pre-divider : 1
     * - feedback divider : 15
     * - PLL Feedback clock divider pre-scaler : 1
     * - PLL post-divider setting : 3
     * Final PLL output frequency is 48M(FIRC) * 15 / 3 / 2 = 120M
     */
    AcgReg_SetPllClkIn(ACG, 0);
    AcgReg_SetPllPreDiv(ACG, 0);
    AcgReg_SetPllM(ACG, 15);
    AcgReg_SetPllFbkSel(ACG, 0);
    AcgReg_SetPllPosDiv(ACG, 3);
    /* SCG PLL configuration:
     * - PLL DIV1 clock divider : 1
     * - PLL DIV2 clock divider : 1
     */
    ScgReg_SetPllCfgDiv1(SCG, 0);
    ScgReg_SetPllCfgDiv2(SCG, 0);
    /* Enable PLL */
    AcgReg_SetEnPll(ACG, 1);
    while(AcgReg_GetStPllLock(ACG) == 0); /* Wait until PLL is locked */

    /* Set Core and APB clock source divider */
    AcgReg_SetSysDivCore(ACG, 0); /* Divide-by-1 */
    ScgReg_SetCsrDivApb(SCG, 1);  /* Divide-by-2 */

    /* Flash frequency MUST be 8M */
    ScgReg_SetCsrDivCntFls(SCG, 14); /* Divide-by-15 */
    /* Flash AHB bus read access time configure */
    FtfcReg_SetFcnfgBusReadTm(FTFC, 2); /* 160M->3, 120M->2, 80M->1, 48M->0 */

    /* Set Core clock source to PLL */
    AcgReg_SetSysSrcSys(ACG, 2); /* select pll as clock source */
#endif

    /* Finish setting up the clock */
    AcgReg_SetLockKey(ACG, 0);   /* Lock ACG again */
    ScgReg_SetLockKey(SCG, 0);   /* Lock SCG again */

    /* Enable FPU */
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */

    /*Release of all peripheral interview access*/
    AIPS->PACRA = 0;
    AIPS->PACRB = 0;
    AIPS->PACRC = 0;
    AIPS->PACRD = 0;
    AIPS->PACRE = 0;
    AIPS->PACRF = 0;
    AIPS->PACRG = 0;
    AIPS->PACRH = 0;
}

