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

#ifndef _WDG_DRV_H_
#define _WDG_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of WDG module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup wdg_drv
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

/*! \brief Definition of mode options available for the clock source type
 */
typedef enum
{
    WDGDRV_CLK_SRC_BUS     = 0x00U, /*!< Bus clock */
    WDGDRV_CLK_SRC_LPO128K = 0x01U, /*!< LPO128 clock */
    WDGDRV_CLK_SRC_SOSC    = 0x02U, /*!< SOSC clock */
    WDGDRV_CLK_SRC_SIRC    = 0x03U, /*!< SIRC clock */
    WDGDRV_CLK_SRC_LPO32K  = 0x04U, /*!< LPO32 clock */
    WDGDRV_CLK_SRC_LPO1K   = 0x05U, /*!< LPO1 clock */
} WdgDrv_ClkSrcType;

/*! \brief Definition of mode options available for the TEST mode
 */
typedef enum
{
    WDGDRV_TEST_MODE_DISABLED = 0x00U, /*!< Test mode disabled */
    WDGDRV_TEST_MODE_USER     = 0x01U, /*!< User mode enabled. (Test mode disabled.) */
    WDGDRV_TEST_MODE_LOW      = 0x02U, /*!< Test mode enabled, only the low byte is used. */
    WDGDRV_TEST_MODE_HIGH     = 0x03U  /*!< Test mode enabled, only the high byte is used. */
} WdgDrv_TestModeType;

/*! \brief Definition of configuration of WDG driver
 */
typedef struct _WdgDrv_ConfigureType_
{
    WdgDrv_ClkSrcType   clkSource;       /*!< RW, The clock source of the WDOG */
    uint8_t             winEnable;       /*!< RW, If true, window mode is enabled */
    uint8_t             flag;            /*!< W1C, If true, clear wdg interrupt flag */
    uint8_t             prescalerEnable; /*!< RW, If true, a fixed 256 prescaling of the counter reference clock is enabled */
    uint8_t             enable;          /*!< RW, If true, the WDOG are enabled */
    uint8_t             intEnable;       /*!< RW, If true, an interrupt request is generated before reset */
    uint8_t             updateEnable;    /*!< RW, If true, further updates of the WDOG are enabled */
    uint8_t             debugModeEnable; /*!< RW, Debug mode */
    uint8_t             stopModeEnable;  /*!< RW, Stop mode */
    uint32_t            windowValue;     /*!< RW, The window value */
    uint32_t            timeoutValue;    /*!< RW, The timeout value */
    uint8_t             tstRstFlg;       /*!< W1C, test reset flag */
    uint8_t             tstRstEn;        /*!< RW, test reset enable */
    WdgDrv_TestModeType testMode;        /*!< RW, Test mode */

} WdgDrv_ConfigureType;

/*! \brief Forward declaration of WDG register
 */
struct _WdgRegType_;

/*! \brief The definition of WDG driver class
 */
typedef struct _WdgDrvType_
{
    struct _WdgRegType_ *reg; /*!< pointer to WDG register */
} WdgDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the WDG driver module
 *
 * This function initializes WDG driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] reg : pointer to WDG register instance
 */
extern void WdgDrv_Init(WdgDrvType *obj, struct _WdgRegType_ *reg);

/*! \brief Get default configures the WDG module for configuration structure
 *
 * This function gets default configures the WDG module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void WdgDrv_GetDefaultConfig(WdgDrv_ConfigureType *userConfig);

/*! \brief Configures the WDG module from a user configuration structure
 *
 * This function configures the WDG module from a user configuration structure
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void WdgDrv_Configure(WdgDrvType *obj, const WdgDrv_ConfigureType *userConfig);

/*! \brief Get current configures the WDG module for configuration structure
 *
 * This function gets current configures the WDG module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void WdgDrv_GetCurrentConfig(const WdgDrvType *obj, WdgDrv_ConfigureType *userConfig);

/*! \brief Enable the WDG module currently
 *
 * This function enable the WDG module currently
 *
 * \param[in] obj : pointer to WDG driver instance
 */
extern void WdgDrv_Enable(WdgDrvType *obj);

/*! \brief Disable the WDG module currently
 *
 * This function Disable the WDG module currently
 *
 * \param[in] obj : pointer to WDG driver instance
 */
extern void WdgDrv_Disable(WdgDrvType *obj);

/*!
 * \brief Enables/Disables the WDG Interrupt.
 *
 * This function enables/disables the WDG Interrupt.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] enable : enable/disable WDG Interrupt.
 */
extern void WdgDrv_SetInt(WdgDrvType *obj, bool enable);

/*!
 * \brief Clear the WDG Interrupt flag.
 *
 * This function Clear the WDG Interrupt flag.
 *
 * \param[in] obj : pointer to WDG driver instance
 */
extern void WdgDrv_ClearIntFlag(WdgDrvType *obj);

/*!
 * \brief refresh the WDG counter value.
 *
 * This function refresh the WDG counter.
 *
 * \param[in] obj : pointer to WDG driver instance
 */
extern void WdgDrv_Refresh(WdgDrvType *obj);

/*!
 * \brief Enables/Disables the WDG window mode.
 *
 * This function enables/Disables the WDG window mode.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] winVal : pointer to window value.
 * \param[in] enable : enable/disable WDG Interrupt.
 */
extern void WdgDrv_SetWindow(WdgDrvType *obj, uint32_t winVal, bool enable);

/*!
 * \brief Enables/Disables the WDG stop mode.
 *
 * This function enables/disables the WDG stop mode.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] enable : enable/disable WDG stop mode.
 */
extern void WdgDrv_SetStopMode(WdgDrvType *obj, bool enable);

/*!
 * \brief set timeout value.
 *
 * This function set timeout value.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] toval : set timeout value.
 */
extern void WdgDrv_SetTimeout(WdgDrvType *obj, uint32_t toval);

/*!
 * \brief Sets the WDG test mode.
 *
 * This function sets the WDG test mode.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[in] type set WDG test mode.
 *                    - 000b: watchdog test mode disable
 *                    - 001b: watchdog user mode enable. (watchdog test mode disabled)
 *                    - 010b: watchdog test mode enabled, only the low byte is used.
 *                    - 011b: watchdog test mode enabled, only the high byte is used.
 */
extern void WdgDrv_SetTestMode(WdgDrvType *obj, WdgDrv_TestModeType type);

/*!
 * \brief Get type of the WDG test mode.
 *
 * This function get type of the WDG test mode.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[out] func : test mode type.
 */
extern WdgDrv_TestModeType WdgDrv_GetTestMode(const WdgDrvType *obj);

/*!
 * \brief Get value of the WDG counter.
 *
 * This function get value of the WDG counter.
 *
 * \param[in] obj : pointer to WDG driver instance
 * \param[out] func : CNT value.
 */
extern uint32_t WdgDrv_GetCnt(const WdgDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif
