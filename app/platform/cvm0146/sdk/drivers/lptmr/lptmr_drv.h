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

#ifndef _LPTMR_DRV_H_
#define _LPTMR_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of LPTMR (Low Power Timer) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup lptmr_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Pulse Counter Input selection
 */
typedef enum
{
    LPTMRDRV_PINSELECT_INPUT0 = 0x00u, /*!< Pulse counter input 0 is selected */
    LPTMRDRV_PINSELECT_INPUT1 = 0x01u, /*!< Pulse counter input 1 is selected */
    LPTMRDRV_PINSELECT_INPUT2 = 0x02u, /*!< Pulse counter input 2 is selected */
    LPTMRDRV_PINSELECT_INPUT3 = 0x03u, /*!< Pulse counter input 3 is selected */
} LptmrDrv_PinSelectType;

/*! \brief Pulse Counter input polarity
 */
typedef enum
{
    LPTMRDRV_PINPOLARITY_RISING  = 0x00u, /*!< Count pulse on rising edge */
    LPTMRDRV_PINPOLARITY_FALLING = 0x01u, /*!< Count pulse on falling edge */
} LptmrDrv_PinPolarityType;

/*! \brief Work Mode
 */
typedef enum
{
    LPTMRDRV_WORKMODE_TIMER        = 0u, /*!< Timer */
    LPTMRDRV_WORKMODE_PULSECOUNTER = 1u, /*!< Pulse counter */
} LptmrDrv_WorkModeType;

/*! \brief Prescaler Selection
 */
typedef enum
{
    LPTMRDRV_PRESCALE_2                        = 0x00u, /*!< Timer mode: prescaler 2, Glitch filter mode: invalid */
    LPTMRDRV_PRESCALE_4_GLITCHFILTER_2         = 0x01u, /*!< Timer mode: prescaler 4, Glitch filter mode: 2 clocks */
    LPTMRDRV_PRESCALE_8_GLITCHFILTER_4         = 0x02u, /*!< Timer mode: prescaler 8, Glitch filter mode: 4 clocks */
    LPTMRDRV_PRESCALE_16_GLITCHFILTER_8        = 0x03u, /*!< Timer mode: prescaler 16, Glitch filter mode: 8 clocks */
    LPTMRDRV_PRESCALE_32_GLITCHFILTER_16       = 0x04u, /*!< Timer mode: prescaler 32, Glitch filter mode: 16 clocks */
    LPTMRDRV_PRESCALE_64_GLITCHFILTER_32       = 0x05u, /*!< Timer mode: prescaler 64, Glitch filter mode: 32 clocks */
    LPTMRDRV_PRESCALE_128_GLITCHFILTER_64      = 0x06u, /*!< Timer mode: prescaler 128, Glitch filter mode: 64 clocks */
    LPTMRDRV_PRESCALE_256_GLITCHFILTER_128     = 0x07u, /*!< Timer mode: prescaler 256, Glitch filter mode: 128 clocks */
    LPTMRDRV_PRESCALE_512_GLITCHFILTER_256     = 0x08u, /*!< Timer mode: prescaler 512, Glitch filter mode: 256 clocks */
    LPTMRDRV_PRESCALE_1024_GLITCHFILTER_512    = 0x09u, /*!< Timer mode: prescaler 1024, Glitch filter mode: 512 clocks */
    LPTMRDRV_PRESCALE_2048_GLITCHFILTER_1024   = 0x0Au, /*!< Timer mode: prescaler 2048, Glitch filter mode: 1024 clocks */
    LPTMRDRV_PRESCALE_4096_GLITCHFILTER_2048   = 0x0Bu, /*!< Timer mode: prescaler 4096, Glitch filter mode: 2048 clocks */
    LPTMRDRV_PRESCALE_8192_GLITCHFILTER_4096   = 0x0Cu, /*!< Timer mode: prescaler 8192, Glitch filter mode: 4096 clocks */
    LPTMRDRV_PRESCALE_16384_GLITCHFILTER_8192  = 0x0Du, /*!< Timer mode: prescaler 16384, Glitch filter mode: 8192 clocks */
    LPTMRDRV_PRESCALE_32768_GLITCHFILTER_16384 = 0x0Eu, /*!< Timer mode: prescaler 32768, Glitch filter mode: 16384 clocks */
    LPTMRDRV_PRESCALE_65536_GLITCHFILTER_32768 = 0x0Fu, /*!< Timer mode: prescaler 65536, Glitch filter mode: 32768 clocks */
} LptmrDrv_PrescaleType;

/*! \brief Definition of configuration of LPTMR driver
 */
typedef struct _LptmrDrv_ConfigType_
{
    /* General parameters */
    bool                  dmaRequest;      /*!< Enable/Disable DMA requests */
    bool                  interruptEnable; /*!< Enable/Disable Interrupt */
    bool                  freeRun;         /*!< Enable/Disable Free Running Mode */
    LptmrDrv_WorkModeType workMode;        /*!< Time/Pulse Counter Mode */

    /* Counter parameters */
    LptmrDrv_PrescaleType prescaler;       /*!< Prescaler Selection */
    bool                  bypassPrescaler; /*!< Enable/Disable prescaler bypass */
    uint16_t              compareValue;    /*!< Compare value */

    /* Pulse Counter specific parameters */
    LptmrDrv_PinSelectType   pinSelect;   /*!< Pin selection for Pulse-Counter */
    LptmrDrv_PinPolarityType pinPolarity; /*!< Pin Polarity for Pulse-Counter */
} LptmrDrv_ConfigType;

/* Forward declaration of LPTMR register */
struct _LptmrRegType_;

/*! \brief The definition of LPTMR driver class
 */
typedef struct _LptmrDrvType_
{
    struct _LptmrRegType_ *reg;
} LptmrDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the LPTMR driver module
 *
 * This function initializes LPTMR driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to LPTMR driver instance
 * \param[in] reg : pointer to LPTMR register instance
 */
extern void LptmrDrv_Init(LptmrDrvType *obj, struct _LptmrRegType_ *reg);

/*! \brief Get currunt configures of the LPTMR module for configuration structure
 *
 * This function gets currunt configures of the LPTMR module for user configuration structure
 *
 * \param[in] obj : pointer to LPTMR driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void LptmrDrv_GetConfigure(LptmrDrvType *obj, LptmrDrv_ConfigType *userConfig);

/*! \brief Get default configures the LPTMR module for configuration structure
 *
 * This function gets default configures the LPTMR module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void LptmrDrv_GetDefaultConfig(LptmrDrv_ConfigType *userConfig);

/*! \brief Configures the LPTMR module from a user configuration structure
 *
 * This function Configures the LPTMR module from a user configuration structure
 *
 * \param[in] obj : pointer to LPTMR driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void LptmrDrv_Configure(LptmrDrvType *obj, const LptmrDrv_ConfigType *userConfig);

/*! \brief Get the state of LPTMR enable
 *
 * This function gets the state of LPTMR enable
 *
 * \param[in] obj : pointer to LPTMR driver instance
 * \return state of LPTMR enable
 */
extern bool LptmrDrv_IsEnable(LptmrDrvType *obj);

/*! \brief Set the state of LPTMR enable
 *
 * This function sets the state of LPTMR enable
 *
 * \param[in] obj : pointer to lptmr LPTMR instance
 * \param[in] state of LPTMR enable
 */
extern void LptmrDrv_Enable(LptmrDrvType *obj, bool enable);

/*! \brief Get the flag of LPTMR compare flag
 *
 * This function gets the flag of LPTMR compare flag
 *
 * \param[in] obj : pointer to LPTMR driver instance
 * \return the flag of LPTMR compare flag
 */
extern bool LptmrDrv_IsCompareEventAcvt(LptmrDrvType *obj);

/*! \brief Clear the flag of LPTMR compare flag
 *
 * This function clears the flag of LPTMR compare flag
 *
 * \param[in] obj : pointer to LPTMR driver instance
 */
extern void LptmrDrv_ClearCompareFlag(LptmrDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _LPTMR_DRV_H_ */
