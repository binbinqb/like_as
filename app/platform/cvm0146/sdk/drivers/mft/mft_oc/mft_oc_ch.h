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

#ifndef _MFT_OC_CH_H_
#define _MFT_OC_CH_H_

/*! \brief Contains public interface to various functions related
 *         to the Output Compare channel of MFT
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup mft_oc_ch
 *  \ingroup mft_oc_drv
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

/*! \brief Selects mode operation int the output compare mode
 */
typedef enum
{
    MFTOCCH_DISABLE_OUTPUT  = 0x00U, /*!< No action on output pin */
    MFTOCCH_TOGGLE_ON_MATCH = 0x01U, /*!< Toggle on match */
    MFTOCCH_CLEAR_ON_MATCH  = 0x02U, /*!< Clear on match */
    MFTOCCH_SET_ON_MATCH    = 0x03U  /*!< Set on match */
} MftOcCh_OutputCompareModeType;

/*! \brief MFT output compare type of the next output compare value
 */
typedef enum
{
    MFTOCCH_RELATIVE_VALUE = 0x00U,     /*!< Next compared value is relative to current value */
    MFTOCCH_ABSOLUTE_VALUE = 0x01U      /*!< Next compared value is absolute */
} MftOcCh_OutputCompareUpdateType;

/*! \brief MFT driver output compare callback function prototype
 */
typedef void (*MftOcCh_CallbackType)(uint8_t event, void *params);

/*! \brief MFT driver output compare parameters for each channel
 */
typedef struct _MftOcpCh_ConfigType_
{
    uint8_t                       hwChannelId;           /*!< Physical hardware channel ID*/
    MftOcCh_OutputCompareModeType outputMode;            /*!< Channel output mode */
    uint16_t                      comparedValue;         /*!< The compared value */
    bool                          enableExternalTrigger; /*!< true: enable the generation of a trigger is used for on-chip modules
                                                          *   false: disable the generation of a trigger */
    void                *callbacksParams;                /*!< The parameters of callback functions for channels events */
    MftOcCh_CallbackType callbackFunc;                   /*!< The callback function for channels events */
} MftOcCh_ConfigType;

/* Forward declaration of MFT Output Compare driver */
struct _MftOcDrvType_;

/*! \brief The definition of MFT output compare channel prototype
 */
typedef struct _MftOcChType_
{
    struct _MftOcDrvType_ *ocDrv;
    MftOcCh_ConfigType     config;
} MftOcChType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT OC channel
 *
 * This function initializes MFT OC channel
 *
 * \param[in] obj : pointer to MFT OC channel instance
 * \param[in] base : pointer to MFT driver instance
 */
extern void MftOcCh_Init(MftOcChType *obj, struct _MftOcDrvType_ *capDrv);

/*! \brief Get default configuration of the MFT output compare channel
 *
 * This function gets default configures the MFT output compare module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftOcCh_GetDefaultConfig(MftOcCh_ConfigType *userConfig);

/*! \brief Configure the MFT output compare channel
 *
 * This function configures the channel in the output compare mode for generate timed pulses.
 * When the MFT counter matches the value of CnV, the channel output is changed based on what 
 * is specified in the output mode argument. 
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void MftOcCh_Config(MftOcChType *obj, const MftOcCh_ConfigType *userConfig);

/*! \brief Disarm the MFT Output Compare channel
 *
 * This function disables output compare mode and clears MFT timer configuration
 *
 * \param[in] obj : pointer to MFT OC channel instance
 */
extern void MftOcCh_Disarm(MftOcChType *obj);

/*! \brief Sets the next compare match value based on the current counter value
 * 
 * \param[in] obj : pointer to MFT OC channel instance
 * \param[in] nextCompareMatchValue : Timer value in ticks until the next compare match event should appear
 * \param[in] update : 
 *            - MFTOCCH_RELATIVE_VALUE : nextComparemantchValue will be added to current counter value
 *            - MFTOCCH_ABSOLUTE_VALUE : nextComparemantchValue will be written in counter register as it is
 * \param[in] softwareTrigger : This parameter will be true if software trigger sync is enabled and  the user
 * want to generate a software trigger (the value from buffer will be moved to register immediate or at next 
 * loading point depending on the sync configuration). Otherwise this parameter must be false and the next 
 * compared value will be stored in buffer untill a trigger signal will be received.
 */
extern bool MftOcCh_UpdateOutputCompare(MftOcChType *obj,
                                        uint16_t nextCompareMatchValue,
                                        MftOcCh_OutputCompareUpdateType update,
                                        bool softwareTrigger);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_OC_CH_H_ */
