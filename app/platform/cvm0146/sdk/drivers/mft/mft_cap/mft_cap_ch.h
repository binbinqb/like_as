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

#ifndef _MFT_CAP_CH_H_
#define _MFT_CAP_CH_H_

/*! \brief Contains public interface to various functions related
 *         to the Capture channel of MFT
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup mft_cap_ch
 *  \ingroup mft_cap_drv
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

/*! \brief Selects mode operation in the input capture
 */
typedef enum
{
    MFTCAPCH_EDGE_DETECT        = 0U, /*!< MFT edge detect */
    MFTCAPCH_SIGNAL_MEASUREMENT = 1U, /*!< MFT signal measurement */
    MFTCAPCH_NO_OPERATION       = 2U  /*!< MFT no operation */
} MftCapCh_InputOpModeType;

/*! \brief MFT input capture measurement type for dual edge input capture
 */
typedef enum
{
    MFTCAPCH_NO_MEASUREMENT                  = 0x00U, /*!< No measurement */
    MFTCAPCH_RISING_EDGE_PERIOD_MEASUREMENT  = 0x01U, /*!< Period measurement between two consecutive rising edges */
    MFTCAPCH_FALLING_EDGE_PERIOD_MEASUREMENT = 0x02U, /*!< Period measurement between two consecutive falling edges */
    MFTCAPCH_PERIOD_ON_MEASUREMENT           = 0x03U, /*!< The time measurement taken for the pulse to remain ON or HIGH state */
    MFTCAPCH_PERIOD_OFF_MEASUREMENT          = 0x04U  /*!< The time measurement taken for the pulse to remain OFF or LOW state */
} MftCapCh_SignalMeasurementModeType;

/*! \brief MFT input capture edge mode as rising edge or falling edge
 */
typedef enum
{
    MFTCAPCH_NO_PIN_CONTROL = 0x00U, /*!< No trigger */
    MFTCAPCH_RISING_EDGE    = 0x01U, /*!< Rising edge trigger */
    MFTCAPCH_FALLING_EDGE   = 0x02U, /*!< Falling edge trigger */
    MFTCAPCH_BOTH_EDGES     = 0x03U  /*!< Rising and falling edge trigger */
} MftCapCh_EdgeAlignmentModeType;

/*! \brief The measurement type for input capture mode
 */
typedef enum
{
    MFTCAPCH_DISABLE_OPERATION           = 0x00U, /*!< Have no operation */
    MFTCAPCH_TIMESTAMP_RISING_EDGE       = 0x01U, /*!< Rising edge trigger */
    MFTCAPCH_TIMESTAMP_FALLING_EDGE      = 0x02U, /*!< Falling edge trigger */
    MFTCAPCH_TIMESTAMP_BOTH_EDGES        = 0x03U, /*!< Rising and falling edge trigger */
    MFTCAPCH_MEASURE_RISING_EDGE_PERIOD  = 0x04U, /*!< Period measurement between two consecutive rising edges */
    MFTCAPCH_MEASURE_FALLING_EDGE_PERIOD = 0x05U, /*!< Period measurement between two consecutive falling edges */
    MFTCAPCH_MEASURE_PULSE_HIGH          = 0x06U, /*!< The time measurement taken for the pulse to remain ON or HIGH state */
    MFTCAPCH_MEASURE_PULSE_LOW           = 0x07U  /*!< The time measurement taken for the pulse to remain OFF or LOW state */
} MftCapCh_OpModeType;

/*! \brief MFT driver Input capture callback function prototype
 */
typedef void (*MftCapCh_CallbackType)(uint8_t event, void *params);

/*! \brief MFT driver Input capture parameters for each channel
 */
typedef struct _MftCapCh_ConfigType_
{
    uint8_t                            hwChannelId;      /*!< Physical hardware channel ID*/
    MftCapCh_InputOpModeType           inputMode;        /*!< FlexTimer module mode of operation  */
    MftCapCh_EdgeAlignmentModeType     edgeAlignement;   /*!< Edge alignment Mode for signal measurement*/
    MftCapCh_SignalMeasurementModeType measurementType;  /*!< Measurement Mode for signal measurement*/
    uint16_t                           filterValue;      /*!< Filter Value */
    bool                               filterEn;         /*!< Input capture filter state */
    bool                               continuousModeEn; /*!< Continuous measurement state */
    void                              *callbacksParams;  /*!< The parameters of callback functions for channels events */
    MftCapCh_CallbackType              callbackFunc;     /*!< The callback function for channels events */
} MftCapCh_ConfigType;

/* Forward declaration of MFT Capture driver */
struct _MftCapDrvType_;

/*! \brief The definition of MFT capture channel prototype
 */
typedef struct _MftCapChType_
{
    struct _MftCapDrvType_ *capDrv;
    MftCapCh_ConfigType     config;
} MftCapChType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT CAP channel
 *
 * This function initializes MFT CAP channel
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \param[in] base : pointer to MFT driver instance
 */
extern void MftCapCh_Init(MftCapChType *obj, struct _MftCapDrvType_ *capDrv);

/*! \brief Get default configuration of the MFT capture channel
 *
 * This function gets default configures the MFT capture module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftCapCh_GetDefaultConfig(MftCapCh_ConfigType *userConfig);

/*! \brief Configure the MFT capture channel
 *
 * This function configures the channel in the Input Capture mode for either getting
 * time-stamps on edge detection or on signal measurement. When the edge specified in the capture Mode
 * argument occurs on the channel and then the MFT counter is captured into the CnV register.
 * The user have to read the CnV register separately to get this value. The filter
 * function is disabled if the filterVal argument passed as 0. The filter feature
 * is available only on channels 0,1,2,3.
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void MftCapCh_Config(MftCapChType *obj, const MftCapCh_ConfigType *userConfig);

/*! \brief Disarm the MFT capture channel
 *
 * This function disables input capture mode and clears MFT timer configuration
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 */
extern void MftCapCh_Disarm(MftCapChType *obj);

/*! \brief Starts a new single-shot signal measurement of the given channel.
 *
 * This function starts the new single-shot signal measurement of the given channel.
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \return The result of the operation
 *         - true : succeed
 *         - false : failed
 */
extern bool MftCapCh_StartNewSignalMeasurement(MftCapChType *obj);

/*! \brief Set mode operation for channel in the input capture mode
 *
 * This function will change the channel mode at run time or
 * when stopping channel. The channel mode is selected in the MftCapCh_OpModeType
 * enumeration type.
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \param[in] inputMode : The channel operation mode.
 * \param[in] enableContinuousCapture : Enable/disable the continuous capture mode.
 */
extern void MftCapCh_SetChannelMode(MftCapChType *obj, MftCapCh_OpModeType inputMode, bool enableContinuousCapture);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_CAP_CH_H_ */
