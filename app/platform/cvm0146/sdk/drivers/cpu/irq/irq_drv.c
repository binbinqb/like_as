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

#include "irq_drv.h"
#include "../cva/CVM014x.h"
#include "../../../CVM014x_features.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* The last IRQn defined by this chip */
#define LAST_IRQn (FEATURE_LAST_IRQn)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*! Those symbols are defined in the startup code */
#if defined(__ARMCC_VERSION)
extern uint32_t __VECTOR_RAM;
extern uint32_t __VECTOR_ROM;
extern uint32_t __DATA_ROM;
extern uint32_t __RAM_START;
#else
#if defined(__ICCARM__)
extern uint32_t __RAM_START[];
#pragma section = "__CODE_ROM"
extern uint32_t CODE_ROM_SECTION_START = (uint32_t)__section_begin("__CODE_ROM");
#endif
extern uint32_t __VECTOR_RAM[((uint32_t)(LAST_IRQn)) + 16U + 1U];
extern uint32_t __VECTOR_TABLE[((uint32_t)(LAST_IRQn)) + 16U + 1U];
extern uint32_t __DATA_ROM[];
extern uint32_t __DATA_END[];
#endif

/*! Counter to manage the nested callings of global disable/enable interrupt. */
static int32_t s_interruptDisableCount = 0;

/*******************************************************************************
 * the functions
 ******************************************************************************/

void IrqDrv_InstallHandler(uint16_t irqNumber, IrqHandlerType newHandler, IrqHandlerType *oldHandler)
{
    const uint32_t *aVectorRam = (uint32_t *)__VECTOR_RAM;
#if defined(__ARMCC_VERSION)
    const uint32_t *aVectorTable = (uint32_t *)__VECTOR_ROM;
#else
    const uint32_t *aVectorTable = (uint32_t *)__VECTOR_TABLE;
#endif

    /* Check whether there is vector table in RAM */
#if defined(__ARMCC_VERSION)
    if((aVectorRam != aVectorTable) || (__DATA_ROM > __RAM_START)) /* polyspace DEFECT:USELESS_IF [No action planned:Low] "Depend on link script" */
#elif(defined(__ICCARM__))
    if((aVectorRam != aVectorTable) || ((uint32_t)CODE_ROM_SECTION_START > (uint32_t)__RAM_START)) /* polyspace DEFECT:USELESS_IF [No action planned:Low] "Depend on link script" */
#else
    const uint32_t *aDataRom = (uint32_t *)__DATA_ROM;
    const uint32_t *aDataRam = (uint32_t *)__DATA_END;
    if((aVectorRam != aVectorTable) || (aDataRom == aDataRam)) /* polyspace DEFECT:USELESS_IF [No action planned:Low] "Depend on link script" */
#endif
    {
        uint32_t *pVectorRam = (uint32_t *)__VECTOR_RAM;
        /* Save the former handler pointer */
        if(oldHandler != (IrqHandlerType *)0)
        {
            *oldHandler = (IrqHandlerType)pVectorRam[((int32_t)irqNumber) + 16];
        }
        /* Set handler into vector table */
        pVectorRam[((int32_t)irqNumber) + 16] = (uint32_t)newHandler;
    }
}

void IrqDrv_EnableGlobalInterrupt(void)
{
    /* Check and update */
    if(s_interruptDisableCount > 0)
    {
        s_interruptDisableCount--;
        if(s_interruptDisableCount <= 0)
        {
/* Enable the global interrupt*/
#if defined(__GNUC__)
            __asm volatile("cpsie i"
                           :
                           :
                           : "memory");
#else
            __asm("cpsie i");
#endif
        }
    }
}

void IrqDrv_DisableGlobalInterrupt(void)
{
/* Disable the global interrupt */
#if defined(__GNUC__)
    __asm volatile("cpsid i"
                   :
                   :
                   : "memory");
#else
    __asm("cpsid i");
#endif
    /* Update counter*/
    s_interruptDisableCount++;
}

void IrqDrv_EnableIrq(uint16_t irqNumber)
{
    NVIC_EnableIRQ((IRQn_Type)irqNumber);
}

void IrqDrv_DisableIrq(uint16_t irqNumber)
{
    NVIC_DisableIRQ((IRQn_Type)irqNumber);
}

void IrqDrv_SetPriorityGrouping(uint32_t priorityGroup)
{
    NVIC_SetPriorityGrouping(priorityGroup);
}

void IrqDrv_SetPriority(uint16_t irqNumber, uint32_t preemptPriority, uint32_t subPriority)
{
    NVIC_SetPriority((IRQn_Type)irqNumber, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), preemptPriority, subPriority));
}

void IrqDrv_GetPriority(uint16_t irqNumber, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
    NVIC_DecodePriority(NVIC_GetPriority((IRQn_Type)irqNumber), NVIC_GetPriorityGrouping(), pPreemptPriority, pSubPriority);
}

void IrqDrv_ClearPending(uint16_t irqNumber)
{
    NVIC_ClearPendingIRQ((IRQn_Type)irqNumber);
}

void IrqDrv_SetPending(uint16_t irqNumber)
{
    NVIC_SetPendingIRQ((IRQn_Type)irqNumber);
}

bool IrqDrv_IsPending(uint16_t irqNumber)
{
    return NVIC_GetPendingIRQ((IRQn_Type)irqNumber) == 1;
}

bool IrqDrv_IsActive(uint16_t irqNumber)
{
    return NVIC_GetActive((IRQn_Type)irqNumber) == 1;
}
