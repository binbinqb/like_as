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

#ifndef _RESET_DRV_H_
#define _RESET_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of Reset
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup reset_drv
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

/*! \brief Definition of modules that can be software reset
 */
typedef enum
{
    RESETDRV_SWRESET_WDG = 0,
    RESETDRV_SWRESET_LPTMR,
    RESETDRV_SWRESET_CMP,
    RESETDRV_SWRESET_LPIT,
    RESETDRV_SWRESET_PORTA,
    RESETDRV_SWRESET_PORTB,
    RESETDRV_SWRESET_PORTC,
    RESETDRV_SWRESET_PORTD,
    RESETDRV_SWRESET_PORTE,
    RESETDRV_SWRESET_FLS,
    RESETDRV_SWRESET_DMA,
    RESETDRV_SWRESET_EIM,
    RESETDRV_SWRESET_ERM,
    RESETDRV_SWRESET_MSCM,
    RESETDRV_SWRESET_MPU,
    RESETDRV_SWRESET_EWM,
    RESETDRV_SWRESET_DMAMUX,
    RESETDRV_SWRESET_CAN0,
    RESETDRV_SWRESET_CAN1,
    RESETDRV_SWRESET_CAN2,
    RESETDRV_SWRESET_CAN3,
    RESETDRV_SWRESET_ADC0,
    RESETDRV_SWRESET_ADC1,
    RESETDRV_SWRESET_PDB0,
    RESETDRV_SWRESET_PDB1,
    RESETDRV_SWRESET_SPI0,
    RESETDRV_SWRESET_SPI1,
    RESETDRV_SWRESET_SPI2,
    RESETDRV_SWRESET_SPI3,
    RESETDRV_SWRESET_UART0,
    RESETDRV_SWRESET_UART1,
    RESETDRV_SWRESET_UART2,
    RESETDRV_SWRESET_UART3,
    RESETDRV_SWRESET_I2C,
    RESETDRV_SWRESET_I2SM,
    RESETDRV_SWRESET_I2SS,
    RESETDRV_SWRESET_CRC,
    RESETDRV_SWRESET_CSE,
    RESETDRV_SWRESET_PRNG,
    RESETDRV_SWRESET_MFT0,
    RESETDRV_SWRESET_MFT1,
    RESETDRV_SWRESET_MFT2,
    RESETDRV_SWRESET_MFT3,
    RESETDRV_SWRESET_MFT4,
    RESETDRV_SWRESET_MFT5,
    RESETDRV_SWRESET_PWMLITE0,
    RESETDRV_SWRESET_PWMLITE1,
    RESETDRV_SWRESET_PWMLITE2,
    RESETDRV_SWRESET_PWMLITE3,
    RESETDRV_SWRESET_PWMLITE4,
    RESETDRV_SWRESET_GPIO,
    RESETDRV_SWRESET_CMUF,
    RESETDRV_SWRESET_CMUP,
    RESETDRV_SWRESET_CMUS,
    RESETDRV_SWRESET_FCCU,
    RESETDRV_SWRESET_SYS
} ResetDrv_SwResetModuleType;

/*! \brief Definition of delay between interrupt and reset
 * \details The unit is LPO128k clock cycle
 */
typedef enum
{
    RESETDRV_RESETDELAY_10LPOCYCLES  = 0,
    RESETDRV_RESETDELAY_34LPOCYCLES  = 1,
    RESETDRV_RESETDELAY_130LPOCYCLES = 2,
    RESETDRV_RESETDELAY_514LPOCYCLES = 3
} ResetDrv_ResetDelayType;

/*! \brief Definition of reset enable modules
 */
typedef enum
{
    RESETDRV_RESETEN_PLL_LOSS,
    RESETDRV_RESETEN_LOCKUP,
} ResetDrv_ResetEnModuleType;

/*! \brief Definition of reset interrupt modules
 */
typedef enum
{
    RESETDRV_RESETINT_WDG,
    RESETDRV_RESETINT_SYS,
    RESETDRV_RESETINT_PIN,
    RESETDRV_RESETINT_MDMAP,
    RESETDRV_RESETINT_PLL_LOSS,
    RESETDRV_RESETINT_CMUF,
    RESETDRV_RESETINT_CMUP,
    RESETDRV_RESETINT_CMUS,
} ResetDrv_ResetIntModuleType;

/*! \brief Definition of reset source
 */
typedef enum
{
    RESETDRV_SOURCE_WDG = 0,
    RESETDRV_SOURCE_SYS,
    RESETDRV_SOURCE_LOCKUP,
    RESETDRV_SOURCE_PIN,
    RESETDRV_SOURCE_MDMAP,
    RESETDRV_SOURCE_PLL_LOSS,
    RESETDRV_SOURCE_CMUF,
    RESETDRV_SOURCE_CMUP,
    RESETDRV_SOURCE_CMUS,
    RESETDRV_SOURCE_FCCU,
    RESETDRV_SOURCE_STDBY_EXIT,
    RESETDRV_SOURCE_FLS_INITIAL,
    RESETDRV_SOURCE_LVR,
    RESETDRV_SOURCE_POR,

    RESETDRV_SOURCE_NUM
} ResetDrv_SourceType;

/*! \brief Definition of configuration of Reset driver
 */
typedef struct _ResetDrv_ConfigType_
{
    bool                    enableExtFlt;         /*!< whether to enable the external reset input digital filter */
    uint16_t                extFltLen;            /*!< external reset input digital filter length */
    bool                    enableResetInterrupt; /*!< whether to enable the global reset interrupt */
    ResetDrv_ResetDelayType delay;                /*!< The delay between the interrupt and the reset */
} ResetDrv_ConfigType;

/* Forward declaration of related register */
struct _RcmRegType_;
struct _PccRegType_;
struct _ApcRegType_;

/*! \brief The definition of RESET driver class
 */
typedef struct _ResetDrvType_
{
    struct _RcmRegType_ *rcmReg; /*!< pointer to RCM register */
    struct _PccRegType_ *pccReg; /*!< pointer to PCC register */
    struct _ApcRegType_ *apcReg; /*!< pointer to APC register */
} ResetDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the Reset driver module
 *
 * This function initializes Reset driver by setting the register
 * instances to it.
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] rcmReg : pointer to RCM register instance
 * \param[in] apcReg : pointer to APC register instance
 */
extern void ResetDrv_Init(ResetDrvType *obj, struct _RcmRegType_ *rcmReg, struct _PccRegType_ *pccReg, struct _ApcRegType_ *apcReg);

/*! \brief Get default configures the Reset module for configuration structure
 *
 * This function gets default configures the Reset module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void ResetDrv_GetDefaultConfig(ResetDrv_ConfigType *userConfig);

/*! \brief Configures the Reset module from a user configuration structure
 *
 * This function configures the Reset module from a used configuration.
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void ResetDrv_Configure(ResetDrvType *obj, const ResetDrv_ConfigType *userConfig);

/*! \brief Get whether a specified source caused MCU's most recent reset
 *
 * This function gets whether a specified source caused MCU's most recent reset.
 * Multiple source can be true if multiple reset events occur at the same time.
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] source : the reset source
 * \return whether the specified source caused MCU's most recent reset
 *         - true : the reset source occurred
 *         - false : the reset source not occurred
 */
extern bool ResetDrv_IsResetCaused(const ResetDrvType *obj, ResetDrv_SourceType source);

/*! \brief Get whether a specified reset occurred since the last POR or LVD that have not been cleared by software
 *
 * This function gets whether a specified reset occurred since the last POR or LVD that have not been cleared by software
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] source : the reset source
 * \return whether the specified reset occurred since the last POR or LVD that have not been cleared by software
 *         - true : the reset source occurred
 *         - false : the reset source not occurred
 */
extern bool ResetDrv_IsResetSticky(const ResetDrvType *obj, ResetDrv_SourceType source);

/*! \brief Clear Sticky reset flag since a reset has been caused
 *
 * This function clear Sticky reset flag since a reset has been caused
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] source : the reset source
 */
extern void ResetDrv_ClrResetStickyFlag(ResetDrvType *obj, ResetDrv_SourceType source);

/*! \brief Enable or disable the reset interrupt for a given module
 *
 * This function enable or disable the reset interrupt for a given module
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] module : the module to configure
 * \param[in] enable : whether to enable or disable the reset interrupt
 *                     - true : enable the reset interrupt
 *                     - falsa : disable the reset interrupt
 */
extern void ResetDrv_EnableResetInterrupt(ResetDrvType *obj, ResetDrv_ResetIntModuleType module, bool enable);

/*! \brief Get whether a specified reset interrupt occurred
 *
 * This function gets whether a specified reset interrupt occurred since the last POR or LVD that have not been cleared by software
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] module : the module to configure
 * \return whether the specified reset interrupt occurred since the last POR or LVD that have not been cleared by software
 *         - true : the reset interrupt occurred
 *         - false : the reset interrupt not occurred
 */
extern bool ResetDrv_IsResetInterrupt(const ResetDrvType *obj, ResetDrv_ResetIntModuleType module);

/*! \brief Enable or disable the reset for a given module
 *
 * This function enable or disable the reset for a given module
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] module : the module to configure
 * \param[in] enable : whether to enable or disable the reset
 *                     - true : enable the reset
 *                     - falsa : disable the reset
 */
extern void ResetDrv_EnableReset(ResetDrvType *obj, ResetDrv_ResetEnModuleType module, bool enable);

/*! \brief Trigger the software reset for a given module
 *
 * This function triggers the software reset for a given module
 *
 * \param[in] obj : pointer to Reset driver instance
 * \param[in] module : the module to configure
 */
extern void ResetDrv_SoftwareResetModule(ResetDrvType *obj, ResetDrv_SwResetModuleType module);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _RESET_DRV_H_ */
