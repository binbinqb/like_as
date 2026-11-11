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

#ifndef _DMAMUX_REG_H_
#define _DMAMUX_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the DMAMUX (Direct Memory Access Multiplexer) Registers
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/* DMAMUX peripheral is available in silicon. */
#define DMAMUX_AVAILABLE
/* Number of DMA channels. */
#define DMAMUX_CHANNELS           (16U)
/* Has the periodic trigger capability */
#define DMAMUX_HAS_TRIG           (1)

/* CR Bit Fields */
#define DMAMUX_CHCFG_SOURCE_MASK  (0x7Fu)
#define DMAMUX_CHCFG_SOURCE_SHIFT (0u)
#define DMAMUX_CHCFG_SOURCE_WIDTH (7u)
#define DMAMUX_CHCFG_TRIG_MASK    (0x80u)
#define DMAMUX_CHCFG_TRIG_SHIFT   (7u)
#define DMAMUX_CHCFG_TRIG_WIDTH   (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
/** DMAMUX - Size of Registers Arrays */
#define DMAMUX_CHCFG_COUNT        (16u)

/*! \brief The definition of DMAMUX registers
 */
typedef struct _DmamuxRegType_
{
    volatile uint8_t  CHCFG[DMAMUX_CHCFG_COUNT]; /*!< Channel Configuration register, array offset: 0x0, array step: 0x1 */
    volatile uint16_t CHENA;                     /*!< Channel Enable register, offset: 0x10*/
} DmamuxRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
/*! \brief Configures the DMA request for the DMAMUX channel.
 *
 * Selects which DMA source is routed to a DMA channel.
 *
 * \param[in] obj : pointer to DMAMUX register instance.
 * \param[in] channel : DMAMUX channel number.
 * \param[in] source : DMA request source.
 */
__attribute__((always_inline)) static inline void DmamuxReg_SetChannelSource(DmamuxRegType *obj, uint8_t channel, uint8_t source)
{
    uint8_t regValTemp;
    regValTemp = obj->CHCFG[channel];
    regValTemp &= (uint8_t) ~(DMAMUX_CHCFG_SOURCE_MASK);
    regValTemp |= (uint8_t)(((uint8_t)(((uint8_t)(source)) << DMAMUX_CHCFG_SOURCE_SHIFT)) & DMAMUX_CHCFG_SOURCE_MASK);
    obj->CHCFG[channel] = regValTemp;
}

/*! \brief Configure DMA Channel Trigger bit in DMAMUX.
 *
 * Enables/Disables DMA Channel Trigger bit in DMAMUX.
 *
 * \param[in] obj : pointer to DMAMUX register instance.
 * \param[in] channel : DMAMUX channel number.
 * \param[in] enable: Enables (true) or Disables (false) command.
 */
__attribute__((always_inline)) static inline void DmamuxReg_SetChannelTrigger(DmamuxRegType *obj, uint8_t channel, bool enable)
{
    if(enable)
    {
        obj->CHCFG[channel] |= DMAMUX_CHCFG_TRIG_MASK;
    }
    else
    {
        obj->CHCFG[channel] &= ~DMAMUX_CHCFG_TRIG_MASK;
    }
}

/*! \brief Enables/Disables the DMAMUX channel.
 *
 * Enables the hardware request. If enabled, the hardware request is  sent to
 * the corresponding DMA channel.
 *
 * \param[in] obj : pointer to DMAMUX register instance.
 * \param[in] channel DMAMUX channel number.
 * \param[in] enable: Enables (true) or Disables (false) DMAMUX channel.
 */
__attribute__((always_inline)) static inline void DmamuxReg_SetChannelCmd(DmamuxRegType *obj, uint8_t channel, bool enable)
{
    if(enable)
    {
        obj->CHENA |= (uint16_t)(1 << channel);
    }
    else
    {
        obj->CHENA &= ~((uint16_t)(1 << channel));
    }
}

/*! \brief Initializes the DMAMUX module to the reset state.
 *
 * Initializes the DMAMUX module to the reset state.
 *
 * \param[in] obj : pointer to DMAMUX register instance.
 */
__attribute__((always_inline)) static inline void DmamuxReg_Init(DmamuxRegType *obj)
{
    uint8_t i;

    for(i = 0; i < DMAMUX_CHANNELS; i++)
    {
        obj->CHCFG[i] = 0;
    }
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _DMAMUX_REG_H_ */
