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

#ifndef _POWER_DRV_H_
#define _POWER_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of power related modules such as reset
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup power_drv
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
typedef enum
{
    POWERDRV_LVW1   = 0x0U, /*!< LVW LEVEL1 */
    POWERDRV_LVW2   = 0x1U, /*!< LVW LEVEL2 */
    POWERDRV_LVW3   = 0x2U  /*!< LVW LEVEL3 */
} PowerDrvLvwLevelType;

typedef enum
{
    POWERDRV_POWER_MODE_RUN                        = 0x0U, /*!< RUN MODE */
    POWERDRV_POWER_MODE_STOP                       = 0x1U, /*!< STOP MODE */
    POWERDRV_POWER_MODE_STANDBY_WITH_CPU_RETENTION = 0x2U  /*!< STANDBY MODE WITH CPU RETENTION */
} PowerDrvPowerModeType;

typedef enum
{
    POWERDRV_NO_WU     = -1,    /*!< No WAKEUP FLAG */
    POWERDRV_PORTA_WU  = 0x00U, /*!< WAKEUP BY PORTA */
    POWERDRV_PORTB_WU  = 0x01U, /*!< WAKEUP BY PORTB */
    POWERDRV_PORTC_WU  = 0x02U, /*!< WAKEUP BY PORTC */
    POWERDRV_PORTD_WU  = 0x03U, /*!< WAKEUP BY PORTD */
    POWERDRV_PORTE_WU  = 0x04U, /*!< WAKEUP BY PORTE */
    POWERDRV_RSTPIN_WU = 0x05U, /*!< WAKEUP BY RESET PIN */
    POWERDRV_RTC_WU    = 0x06U, /*!< WAKEUP BY RTC */
    POWERDRV_LPIT_WU   = 0x07U, /*!< WAKEUP BY LPIT */
    POWERDRV_LPTMR_WU  = 0x08U, /*!< WAKEUP BY LPTMR */
    POWERDRV_CMP_WU    = 0x09U  /*!< WAKEUP BY CMP */
} PowerDrvWakeupFlagType;

typedef struct _PowerDrvType_
{
    struct _PmcRegType_ *pmcReg;
    struct _AcgRegType_ *acgReg;
} PowerDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
/*! \brief Initializes the Power reg
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 * \param[in] pmcReg : pointer to POWER register instance
 * \param[in] acgReg : pointer to ACG register instance
 */
extern void PowerDrv_Init(PowerDrvType *obj, struct _PmcRegType_ *pmcReg, struct _AcgRegType_ *acgReg);

/*! \brief Unlock the PMC register write access
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_UnlockRegWriteAccess(PowerDrvType *obj);

/*! \brief Lock the PMC register write access
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_LockRegWriteAccess(PowerDrvType *obj);

/*! \brief Enable the LVW warning
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableLvwWarning(PowerDrvType *obj);

/*! \brief Disable the LVW warning
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableLvwWarning(PowerDrvType *obj);

/*! \brief set the lvw warning level
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 * \param[in] level : the target lvw warning level
 */
extern void PowerDrv_SetLvwLevel(PowerDrvType *obj, PowerDrvLvwLevelType level);

/*! \brief Enable the LVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableLvdDetect(PowerDrvType *obj);

/*! \brief Disable the LVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableLvdDetect(PowerDrvType *obj);

/*! \brief Enable the OTP warning
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableOtpWarning(PowerDrvType *obj);

/*! \brief Disable the OTP warning
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableOtpWarning(PowerDrvType *obj);

/*! \brief Enable the FLDO detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableFldoDetect(PowerDrvType *obj);

/*! \brief Disable the FLDO detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableFldoDetect(PowerDrvType *obj);

/*! \brief Enable the OVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableOvdDetect(PowerDrvType *obj);

/*! \brief Disable the OVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableOvdDetect(PowerDrvType *obj);

/*! \brief Enable the OVD11 detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableOvd11Detect(PowerDrvType *obj);

/*! \brief Disable the OVD11 detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableOvd11Detect(PowerDrvType *obj);

/*! \brief Enable the LPBG OVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableLpbgOvdDetect(PowerDrvType *obj);

/*! \brief Disable the LPBG OVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableLpbgOvdDetect(PowerDrvType *obj);

/*! \brief Enable the LPBG LVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_EnableLpbgLvdDetect(PowerDrvType *obj);

/*! \brief Disable the LPBG LVD detect
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_DisableLpbgLvdDetect(PowerDrvType *obj);

/*! \brief release the pad keep feature
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_ReleasePadKeep(PowerDrvType *obj);

/*! \brief get the previous pmc mode info
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 * \param[out] PowerDrvPowerModeType : mode
 *             - 0 : run
 *             - 1 : stop
 *             - 2 : standby
 */
extern PowerDrvPowerModeType PowerDrv_GetPreviousPmcMode(PowerDrvType *obj);

/*! \brief clear the previous pmc mode info
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_ClrPreviousPmcMode(PowerDrvType *obj);

/*! \brief clear all wakeup flags
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 */
extern void PowerDrv_ClrAllWakupFlags(PowerDrvType *obj);

/*! \brief clear dedicated wakeup flag
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 * \param[in] flag : the wakeup flag
 */
extern void PowerDrv_ClrWakeupFlag(PowerDrvType *obj, PowerDrvWakeupFlagType flag);

/*! \brief get the wakeup flag
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 * \param[out] PowerDrvWakeupFlagType : flag
 */
extern PowerDrvWakeupFlagType PowerDrv_GetWakeupSource(PowerDrvType *obj);

/*! \brief set the power mode
 *
 *
 * \param[in] obj : pointer to POWER driver instance
 * \param[in] mode : the target mode
 */
extern void PowerDrv_SetPowerMode(PowerDrvType *obj, PowerDrvPowerModeType mode);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _POWER_DRV_H_ */
