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

#ifndef _EWM_DRV_H_
#define _EWM_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of EWM (External Watchdog Monitor)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup ewm_drv
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

/*! \brief Definition of EWM input configuration
 */
typedef enum
{
    EWMDRV_IN_ASSERT_DISABLED      = 0x00U, /*!< Input pin disabled                    */
    EWMDRV_IN_ASSERT_ON_LOGIC_ZERO = 0x01U, /*!< Input pin asserts EWM when on logic 0 */
    EWMDRV_IN_ASSERT_ON_LOGIC_ONE  = 0x02U  /*!< Input pin asserts EWM when on logic 1 */
} EwmDrv_InAssertLogicType;

/*! \brief Definition of EWM configuration structure
 */
typedef struct _EwmDrv_ConfigType_
{
    uint8_t assertLogic;     /*!< Assert logic for EWM input pin */
    bool    interruptEnable; /*!< Enable EWM interrupt           */
    uint8_t prescaler;       /*!< EWM clock prescaler            */
    uint8_t compareLow;      /*!< Compare low value              */
    uint8_t compareHigh;     /*!< Compare high value             */
} EwmDrv_ConfigType;

/*! \brief The definition of EWM driver class
 */
typedef struct _EwmDrvType_
{
    struct _EwmRegType_ *reg;
} EwmDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the EWM driver module
 *
 * This function initializes EWM driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to EWM driver instance
 * \param[in] reg : pointer to EWM register instance
 */
extern void EwmDrv_Init(EwmDrvType *obj, struct _EwmRegType_ *reg);

/*! \brief Get default configures the EWM module for configuration structure
 *
 * This function gets default configures the EWM module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void EwmDrv_GetDefaultConfig(EwmDrv_ConfigType *userConfig);

/*! \brief Configures the EWM module from a user configuration structure
 *
 * This function resets EWM module, enables the EWM module, configures EWM
 * module. The EWM configuration structure shall
 * be passed as arguments.
 * This function should be called before calling any other EWM driver function.
 *
 * \param[in] obj : pointer to EWM driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void EwmDrv_Configure(EwmDrvType *obj, const EwmDrv_ConfigType *userConfig);

/*! \brief Clears Interrupt flag.
 *
 * This function clears the EWM interrupt flag
 *
 * \param[in] obj : pointer to EWM driver instance
 */
extern void EwmDrv_ClearInterruptFlag(EwmDrvType *obj);

/*! \brief Refresh EWM.
 *
 * This function refreshes the EWM
 * This method needs to be called within the window period
 * specified by the Compare Low and Compare High registers.
 *
 * \param[in] obj : pointer to EWM driver instance
 */
extern void EwmDrv_Refresh(EwmDrvType *obj);

/*! \brief Get the Input pin assert logic.
 *
 * This function gets the input pin assert logic
 *
 * \param[in] obj : pointer to EWM driver instance
 * \return the input pin assert logic:
 *         - EWMDRV_IN_ASSERT_DISABLED      : EWM in disabled
 *         - EWMDRV_IN_ASSERT_ON_LOGIC_ZERO : EWM is asserted when EWM_in is logic 0
 *         - EWMDRV_IN_ASSERT_ON_LOGIC_ONE  : EWM is asserted when EWM_in is logic 1
 */
extern EwmDrv_InAssertLogicType EwmDrv_GetInputPinAssertLogic(const EwmDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _EWM_REG_H_ */
