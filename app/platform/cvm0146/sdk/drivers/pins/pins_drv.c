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

#include "pins_drv.h"
#include "port_reg.h"
#include "gpio_reg.h"

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

void PinsDrv_Init(PinsDrvType *obj, struct _PortRegType_ *port, struct _GpioRegType_ *gpio)
{
    obj->port = port;
    obj->gpio = gpio;
}

void PinsDrv_SetPullSel(PinsDrvType *obj, uint32_t pin, PinsDrv_InternalPullModeType pullMode)
{
    if(PORT_PCR_COUNT <= pin)
    {
        return;
    }

    /* Pull-down and pull-up cannot be enabled at the same time */
    switch(pullMode)
    {
    case PINSDRV_INTERNAL_NO_PULL:
        PortReg_SetPcrPde(obj->port, pin, 0); /* disable pull-down */
        PortReg_SetPcrPue(obj->port, pin, 0); /* disable pull-up */
        break;
    case PINSDRV_INTERNAL_PULL_DOWN:
        PortReg_SetPcrPde(obj->port, pin, 1); /* enable pull-down */
        PortReg_SetPcrPue(obj->port, pin, 0); /* disable pull-up */
        break;
    case PINSDRV_INTERNAL_PULL_UP:
        PortReg_SetPcrPde(obj->port, pin, 0); /* disable pull-down */
        PortReg_SetPcrPue(obj->port, pin, 1); /* enable pull-up */
        break;
    default:
        break;
    }
}

void PinsDrv_SetMuxModeSel(PinsDrvType *obj, uint32_t pin, PinsDrv_MuxType mux)
{
    /* analog feature */
    if(mux == PINSDRV_PIN_DISABLED)
    {
    	PortReg_SetPcrMux(obj->port, pin, mux);
        /* Analog pin, need enable analog feature */
        PortReg_SetPcrAen(obj->port, pin, 1);
    }
    else
    {
        /* Other functions, must disable analog feature */
        PortReg_SetPcrAen(obj->port, pin, 0);
        PortReg_SetPcrMux(obj->port, pin, mux);
    }
}

void PinsDrv_SetPinIntSel(PinsDrvType *obj, uint32_t pin, PinsDrv_InterruptConfigType intConfig)
{
    if(PORT_PCR_COUNT <= pin)
    {
        return;
    }

    PortReg_SetPcrIrqCfg(obj->port, pin, intConfig);
}

PinsDrv_InterruptConfigType PinsDrv_GetPinIntSel(const PinsDrvType *obj, uint32_t pin)
{
    PinsDrv_InterruptConfigType retval;
    if(PORT_PCR_COUNT <= pin)
    {
        retval = PINSDRV_DMA_INT_RESERVED;
    }
    else
    {
        retval = (PinsDrv_InterruptConfigType)PortReg_GetPcrIrqCfg(obj->port, pin);
    }
    return retval;
}

void PinsDrv_ClearPinIntFlagCmd(PinsDrvType *obj, uint32_t pin)
{
    if(PORT_PCR_COUNT <= pin)
    {
        return;
    }

    PortReg_SetPcrIsf(obj->port, pin, 1); /* Write 1 to clear */
}

void PinsDrv_EnableDigitalFilter(PinsDrvType *obj, uint32_t pin)
{
    if(PORT_PCR_COUNT <= pin)
    {
        return;
    }

    uint32_t tmp = PortReg_GetDferEn(obj->port);
    tmp |= (uint32_t)1U << pin;
    PortReg_SetDferEn(obj->port, tmp);
}

void PinsDrv_DisableDigitalFilter(PinsDrvType *obj, uint32_t pin)
{
    if(PORT_PCR_COUNT <= pin)
    {
        return;
    }

    uint32_t tmp = PortReg_GetDferEn(obj->port);
    tmp &= ~((uint32_t)1U << pin);
    PortReg_SetDferEn(obj->port, tmp);
}

void PinsDrv_ConfigDigitalFilter(PinsDrvType *obj, const PinsDrv_FilterConfigType *config)
{
    PortReg_SetDfwrLen(obj->port, config->width);
}

uint32_t PinsDrv_GetPortIntFlag(const PinsDrvType *obj)
{
    return PortReg_GetIsfrIsf(obj->port);
}

void PinsDrv_ClearPortIntFlagCmd(PinsDrvType *obj)
{
    PortReg_SetIsfrIsf(obj->port, 0xffffffff);
}

void PinsDrv_SetPinsFloating(PinsDrvType *obj, uint16_t pins)
{
    uint32_t mask = 0;
    mask += pins;
    PortReg_SetGpclr(obj->port, mask);
    PortReg_SetGpchr(obj->port, mask);
}

void PinsDrv_SetGlobalPinControl(PinsDrvType *obj, uint16_t pins, uint16_t value, PinsDrv_GlobalControlPinsType whichHalf)
{
    uint32_t mask = 0;
    /* keep only available fields */
    mask |= PORT_PCR_PUE_MASK;
    mask |= PORT_PCR_PDE_MASK;
    mask |= PORT_PCR_PAS_FLT_MASK;
    mask |= PORT_PCR_SR_MASK;
    mask |= PORT_PCR_DRV_STR_MASK;
    mask |= PORT_PCR_ODE_MASK;
    mask |= PORT_PCR_MUX_MASK;
    mask |= PORT_PCR_FAST_MASK;
    mask |= PORT_PCR_LOCK_MASK;
    mask &= value;

    /* analog feature */
    if(((mask & PORT_PCR_MUX_MASK) >> PORT_PCR_MUX_SHIFT) == PINSDRV_PIN_DISABLED)
    {
        /* Analog pin, need enable analog feature */
        mask |= PORT_PCR_AEN_MASK;
    }

    mask <<= 16;
    mask += pins;

    switch(whichHalf)
    {
    case PINDRV_GLOBAL_CONTROL_LOWER_HALF_PINS:
        PortReg_SetGpclr(obj->port, mask);
        break;
    case PINDRV_GLOBAL_CONTROL_UPPER_HALF_PINS:
        PortReg_SetGpchr(obj->port, mask);
        break;
    default:
        break;
    }
}

void PinsDrv_SetGlobalIntControl(PinsDrvType *obj, uint16_t pins, uint16_t value, PinsDrv_GlobalControlPinsType whichHalf)
{
    uint32_t mask = 0;

    mask = ((uint32_t)value << 16) + pins;

    switch(whichHalf)
    {
    case PINDRV_GLOBAL_CONTROL_LOWER_HALF_PINS:
        PortReg_SetGiclrInt(obj->port, mask);
        break;
    case PINDRV_GLOBAL_CONTROL_UPPER_HALF_PINS:
        PortReg_SetGichrInt(obj->port, mask);
        break;
    default:
        break;
    }
}

uint32_t PinsDrv_GetPinsDirection(const PinsDrvType *obj)
{
    return GpioReg_GetPddrDir(obj->gpio);
}

void PinsDrv_SetPinDirection(PinsDrvType *obj, uint32_t pin, uint8_t direction)
{
    uint32_t pinDirections = GpioReg_GetPddrDir(obj->gpio);
    pinDirections &= (uint32_t)(~((uint32_t)1U << pin));
    pinDirections |= (uint32_t)((uint32_t)direction << pin);
    GpioReg_SetPddrDir(obj->gpio, pinDirections);
}

void PinsDrv_SetPortInputDisable(PinsDrvType *obj, uint32_t mask)
{
    GpioReg_SetPidrInDisable(obj->gpio, mask);
}

uint32_t PinsDrv_GetPortInputDisable(const PinsDrvType *obj)
{
    return GpioReg_GetPidrInDisable(obj->gpio);
}

void PinsDrv_WritePin(PinsDrvType *obj, uint32_t pin, uint8_t value)
{
    uint32_t pinDirections = GpioReg_GetPdorDatOut(obj->gpio);
    pinDirections &= (uint32_t)(~((uint32_t)1U << pin));
    pinDirections |= (uint32_t)((uint32_t)value << pin);
    GpioReg_SetPdorDatOut(obj->gpio, pinDirections);
}

void PinsDrv_WritePins(PinsDrvType *obj, uint32_t mask)
{
    GpioReg_SetPdorDatOut(obj->gpio, mask);
}

uint8_t PinsDrv_GetPinOutput(const PinsDrvType *obj, uint32_t pin)
{
    return (uint8_t)((GpioReg_GetPdorDatOut(obj->gpio) >> pin) & 0x01);
}

uint32_t PinsDrv_GetPinsOutput(const PinsDrvType *obj)
{
    return GpioReg_GetPdorDatOut(obj->gpio);
}

void PinsDrv_SetPin(PinsDrvType *obj, uint32_t pin)
{
    GpioReg_SetPsorDatSet(obj->gpio, (uint32_t)1U << pin);
}

void PinsDrv_SetPins(PinsDrvType *obj, uint32_t mask)
{
    GpioReg_SetPsorDatSet(obj->gpio, mask);
}

void PinsDrv_ClearPin(PinsDrvType *obj, uint32_t pin)
{
    GpioReg_SetPcorDatClr(obj->gpio, (uint32_t)1U << pin);
}

void PinsDrv_ClearPins(PinsDrvType *obj, uint32_t mask)
{
    GpioReg_SetPcorDatClr(obj->gpio, mask);
}

void PinsDrv_TogglePin(PinsDrvType *obj, uint32_t pin)
{
    GpioReg_SetPtorDatTog(obj->gpio, (uint32_t)1U << pin);
}

void PinsDrv_TogglePins(PinsDrvType *obj, uint32_t mask)
{
    GpioReg_SetPtorDatTog(obj->gpio, mask);
}

uint8_t PinsDrv_ReadPin(PinsDrvType *obj, uint32_t pin)
{
    uint8_t  retval   = 0;
    uint32_t pinsData = GpioReg_GetPdirDatIn(obj->gpio) & ((uint32_t)1U << pin);
    if(pinsData == 0)
    {
        retval = 0;
    }
    else
    {
        retval = 1;
    }

    return retval;
}

uint32_t PinsDrv_ReadPins(const PinsDrvType *obj)
{
    return GpioReg_GetPdirDatIn(obj->gpio);
}
