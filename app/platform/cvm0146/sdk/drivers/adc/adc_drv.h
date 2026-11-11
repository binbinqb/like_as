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

#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of ADC (Analog-to-digital conversion)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup adc_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
#define ADCDRV_CHANNEL_NUM (24)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief ADC type of hardware average times selection
 */
typedef enum
{
    ADCDRV_AVERAGE_4  = 0x0U, /*!< Hardware average of 4 samples.*/
    ADCDRV_AVERAGE_8  = 0x1U, /*!< Hardware average of 8 samples.*/
    ADCDRV_AVERAGE_16 = 0x2U, /*!< Hardware average of 16 samples.*/
    ADCDRV_AVERAGE_32 = 0x3U, /*!< Hardware average of 32 samples.*/
} AdcDrv_AverageMode;

/*! \brief ADC type of self-test channel selection
 */
typedef enum
{
    ADCDRV_SELF_TEST_VALUE_AVSS              = 0x0U, /*!< ADC self-test channel select AVSS.*/
    ADCDRV_SELF_TEST_VALUE_ONE_EIGHTH_AVSS   = 0x1U, /*!< ADC self-test channel select 1/8*VREF.*/
    ADCDRV_SELF_TEST_VALUE_HALF_AVSS         = 0x2U, /*!< ADC self-test channel select 1/2*VREF.*/
    ADCDRV_SELF_TEST_VALUE_SEVEN_EIGHTH_AVSS = 0x3U, /*!< ADC self-test channel select 7/8*VREF.*/

} AdcDrv_SelfTestValue;

/*! \brief ADC type of resolution selection
 */
typedef enum
{
    ADCDRV_CONVERSION_8BIT    = 0x0U, /*!< Selects the ADC resolution to 8-bit conversion.*/
    ADCDRV_CONVERSION_12BIT   = 0x1U, /*!< Selects the ADC resolution to 12-bit conversion.*/
    ADCDRV_CONVERSION_10BIT   = 0x2U, /*!< Selects the ADC resolution to 10-bit conversion.*/
    ADCDRV_CONVERSION_12BIT_2 = 0x3U, /*!< Selects the ADC resolution to 12-bit conversion.*/
} AdcDrv_ConversionMode;

/*! \brief ADC type of VREF selection
 */
typedef enum
{
    /*! \note If VDDA is selected, VDDA needs to be shorted with VREFH by hardware.*/
    ADCDRV_REFVOLT_VDDA = 0x0U, /*!< ADC VREF select VDDA.*/
    ADCDRV_REFVOLT_VREF = 0x1U, /*!< ADC VREF select external VREF.*/
} AdcDrv_RefVolt;

/*! \brief ADC type of compare mode
 */
typedef enum
{
    ADCDRV_CMPMODE_NO_COMPARE                 = 0x0U, /*!< ADC disable compare function.*/
    ADCDRV_CMPMODE_LESSTHAN                   = 0x1U, /*!< Automatic compare with interrupt for less-than.*/
    ADCDRV_CMPMODE_GREATER_OR_EQUTHAN         = 0x2U, /*!< Automatic compare with interrupt for greater-than or equal-to.*/
    ADCDRV_CMPMODE_OUTSIDE_EXCLUDE_BOUNDARIES = 0x3U, /*!< Automatic compare with interrupt for out-of-range(Does not contain boundaries).*/
    ADCDRV_CMPMODE_INSIDE_EXCLUDE_BOUNDARIES  = 0x4U, /*!< Automatic compare with interrupt for within range(Does not contain boundaries).*/
    ADCDRV_CMPMODE_INSIDE_INCLUDE_BOUNDARIES  = 0x5U, /*!< Automatic compare with interrupt for within range(Contain boundaries).*/
    ADCDRV_CMPMODE_OUTSIDE_INCLUDE_BOUNDARIES = 0x6U, /*!< Automatic compare with interrupt for out-of-range range(Contain boundaries).*/
} AdcDrv_CmpMode;

/*! \brief ADC type of input channel selection.
 */
typedef enum
{
    ADCDRV_INCHN_EXT0              = 0x0U,  /*!< External channel 0.*/
    ADCDRV_INCHN_EXT1              = 0x1U,  /*!< External channel 1.*/
    ADCDRV_INCHN_EXT2              = 0x2U,  /*!< External channel 2.*/
    ADCDRV_INCHN_EXT3              = 0x3U,  /*!< External channel 3.*/
    ADCDRV_INCHN_EXT4              = 0x4U,  /*!< External channel 4.*/
    ADCDRV_INCHN_EXT5              = 0x5U,  /*!< External channel 5.*/
    ADCDRV_INCHN_EXT6              = 0x6U,  /*!< External channel 6.*/
    ADCDRV_INCHN_EXT7              = 0x7U,  /*!< External channel 7.*/
    ADCDRV_INCHN_EXT8              = 0x8U,  /*!< External channel 8.*/
    ADCDRV_INCHN_EXT9              = 0x9U,  /*!< External channel 9.*/
    ADCDRV_INCHN_EXT10             = 0xAU,  /*!< External channel 10.*/
    ADCDRV_INCHN_EXT11             = 0xBU,  /*!< External channel 11.*/
    ADCDRV_INCHN_EXT12             = 0xCU,  /*!< External channel 12.*/
    ADCDRV_INCHN_EXT13             = 0xDU,  /*!< External channel 13.*/
    ADCDRV_INCHN_EXT14             = 0xEU,  /*!< External channel 14.*/
    ADCDRV_INCHN_EXT15             = 0xFU,  /*!< External channel 15.*/
    ADCDRV_INCHN_EXT16             = 0x10U, /*!< External channel 16.*/
    ADCDRV_INCHN_EXT17             = 0x11U, /*!< External channel 17.*/
    ADCDRV_INCHN_EXT18             = 0x12U, /*!< External channel 18.*/
    ADCDRV_INCHN_EXT19             = 0x13U, /*!< External channel 19.*/
    ADCDRV_INCHN_EXT20             = 0x14U, /*!< External channel 20.*/
    ADCDRV_INCHN_EXT21             = 0x15U, /*!< External channel 21.*/
    ADCDRV_INCHN_EXT22             = 0x16U, /*!< External channel 22.*/
    ADCDRV_INCHN_EXT23             = 0x17U, /*!< External channel 23.*/
    ADCDRV_INCHN_LPVBG             = 0x19U, /*!< LPVBG.*/
    ADCDRV_INCHN_VBG               = 0x1AU, /*!< VBG.*/
    ADCDRV_INCHN_LDO_VOLT          = 0x1BU, /*!< monitor_ldo_volt.*/
    ADCDRV_INCHN_SELF_TEST_VOLTAGE = 0x1DU, /*!< selftest_volt.*/
    ADCDRV_INCHN_DISABLE           = 0x1FU, /*!< Module is disabled.*/
} AdcDrv_InChnType;

/*! \brief ADC type of continuous conversion mode selection.
 */
typedef enum
{
    ADCDRV_ONESHOT    = 0x0U, /*!< One conversion will be performed (or one set of conversions, if AVGE is set) after a conversion is initiated.*/
    ADCDRV_CONTINUOUS = 0x1U, /*!< Continuous conversions will be performed (or continuous sets of conversions, if AVGE is set) after a conversion is initiated.*/
} AdcDrv_ContinuousMode;

/*! \brief ADC type of instance selection.
 */
typedef enum
{
    ADCDRV_INSTANCE_0 = 0x0U, /*!< ADC instance 0.*/
    ADCDRV_INSTANCE_1 = 0x1U, /*!< ADC instance 1.*/
} AdcDrv_InstanceNumber;

/*! \brief ADC type of interleave channel selection.
 */
typedef enum
{
    ADCDRV_INTERLEAVE_ADC0SE4_ADC1SE14 = 0x0U, /*!< ADC0_SE4 and ADC1_SE14 channels are interleaved on PTB0 pin.*/
    ADCDRV_INTERLEAVE_ADC0SE5_ADC1SE15 = 0x1U, /*!< ADC0_SE5 and ADC1_SE15 channels are interleaved on PTB1 pin.*/
    ADCDRV_INTERLEAVE_ADC0SE8_ADC1SE8  = 0x2U, /*!< ADC1_SE8 and ADC0_SE8 channels are interleaved on PTB13 pin.*/
    ADCDRV_INTERLEAVE_ADC0SE9_ADC1SE9  = 0x3U, /*!< ADC1_SE9 and ADC0_SE9 channels are interleaved on PTB14 pin.*/
    ADCDRV_INTERLEAVE_CHANNEL_NUMBER   = 0x4U, /*!< The number of ADC channels that can be interleaved.*/
} AdcDrv_InterleaveChannel;

/*! \brief ADC type of hardware trigger source selection.
 */
typedef enum
{
    ADCDRV_HW_TRGSRC_PDB    = 0x0U, /*!< Select PDB output for trigger source.*/
    ADCDRV_HW_TRGSRC_TRGMUX = 0x1U, /*!< Select TRGMUX output output for trigger source.*/
} AdcDrv_HwTrgSrc;

/*! \brief ADC type of software pretrigger source selection.
 */
typedef enum
{
    ADCDRV_SWPRETRG_PRETRIGGER_0 = 0x4U, /*!< Select PRETRIGGER_0 for software pretrigger sources.*/
    ADCDRV_SWPRETRG_PRETRIGGER_1 = 0x5U, /*!< Select PRETRIGGER_1 for software pretrigger sources.*/
    ADCDRV_SWPRETRG_PRETRIGGER_2 = 0x6U, /*!< Select PRETRIGGER_2 for software pretrigger sources.*/
    ADCDRV_SWPRETRG_PRETRIGGER_3 = 0x7U, /*!< Select PRETRIGGER_3 for software pretrigger sources.*/
} ADCDRV_SwPretrgSrc;

/*! \brief ADC type of hardware pretrigger source selection.
 */
typedef enum
{
    ADCDRV_PRETRG_PDB_PRETRIGGER      = 0x0U, /*!< Select PDB pretrigger for ADC pretrigger sources.*/
    ADCDRV_PRETRG_TRGMUX_PRETRIGGER   = 0x1U, /*!< Select TRGMUX pretrigger for ADC pretrigger sources.*/
    ADCDRV_PRETRG_SOFTWARE_PRETRIGGER = 0x2U, /*!< Select SOFTWARE pretrigger for ADC pretrigger sources.*/
} ADCDRV_PretrgSrc;

/*! \brief Initial parameters
 */
typedef struct _AdcDrv_InitParamsType_
{
    AdcDrv_InstanceNumber adcNumber; /*!< ADC instance number*/
} AdcDrv_InitParamsType;

/*! \brief Definition of configuration of ADC trigger/pretrigger.
 */
typedef struct _AdcDrv_TrgSrcCfgType_
{
    AdcDrv_HwTrgSrc    hwTrgSrc;    /*!< Selects hardware trigger source for ADC.*/
    ADCDRV_SwPretrgSrc swPretrgSrc; /*!< Selects software pretrigger sources for ADC*/
    ADCDRV_PretrgSrc   pretrgSrc;   /*!< Selects pretrigger sources for ADC*/
} AdcDrv_TrgSrcCfgType;

/*! \brief Definition of configuration of ADC channel
 */
typedef struct _AdcDrv_ChnCfgType_
{
    AdcDrv_InChnType chnSel;    /*!< Input channel select.*/
    bool             intEnable; /*!< Interrupt enable.*/
} AdcDrv_ChnCfgType;

/*! \brief Definition of configuration of ADC compare function
 */
typedef struct _AdcDrv_CmpCfgType_
{
    uint16_t       lowerLim; /*!< Lower limiting value in ADC compare function.*/
    uint16_t       upperLim; /*!< Upper limiting value in ADC compare function.*/
    AdcDrv_CmpMode cmpMode;  /*!< Select compare mode.*/
} AdcDrv_CmpCfgType;

/*! \brief Definition of configuration of ADC interleave channel
 */
typedef struct _AdcDrv_InterleaveType_
{
    bool state[ADCDRV_INTERLEAVE_CHANNEL_NUMBER]; /*!< Selects each ADC channel interleave state.*/
} AdcDrv_InterleaveType;

/*! \brief Definition of configuration of ADC driver
 */
typedef struct _AdcDrv_ConfigType_
{
    AdcDrv_ConversionMode conversionMode;             /*!< Conversion mode select.*/
    uint8_t               sampleLen;                  /*!< ADC sampling time.*/
    uint8_t               firstSampleLen;             /*!< First sample delay time.*/
    uint8_t               pwrOnLen;                   /*!< Power on sample delay time.*/
    AdcDrv_RefVolt        refVolSel;                  /*!< ADC VREF Select.*/
    bool                  dmaEnable;                  /*!< Switch DMA enable.*/
    AdcDrv_CmpCfgType     cmpCfg;                     /*!< Compare function configuration*/
    AdcDrv_ContinuousMode continuousMode;             /*!< Switch continuous conversion enable*/
    AdcDrv_AverageMode    avgSamplesSel;              /*!< Hardware average select*/
    bool                  avgEnable;                  /*!< Switch hardware average enable*/
    AdcDrv_ChnCfgType     chnCfg[ADCDRV_CHANNEL_NUM]; /*!< ADC channel configuration*/
    AdcDrv_InterleaveType interleaveMode;             /*!< ADC interleave channel configuration*/
    AdcDrv_TrgSrcCfgType  trgSrcCfg;                  /*!< ADC trigger source configuration*/
} AdcDrv_ConfigType;

/* Forward declaration of ADC register */
struct _AdcRegType_;

/* Forward declaration of SIm register */
struct _SimRegType_;

/*! \brief The definition of ADC driver class
 */
typedef struct _AdcDrvType_
{
    struct _AdcRegType_  *adcReg;
    struct _SimRegType_  *simReg;
    AdcDrv_InstanceNumber adcNumber;
} AdcDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the ADC driver module
 *
 * This function initializes ADC driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to ADC driver instance
 * \param[in] pdbReg : pointer to ADC register instance
 * \param[in] simReg : pointer to SIM register instance
 * \param[in] initParams : pointer to ADC initialization parameters
 */
extern void AdcDrv_Init(AdcDrvType *obj, struct _AdcRegType_ *adcReg, struct _SimRegType_ *simReg, const AdcDrv_InitParamsType *initParams);

/*! \brief Get default configures the ADC module for configuration structure
 *
 * This function gets default configures the ADC module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void AdcDrv_GetDefaultConfig(AdcDrv_ConfigType *userConfig);

/*! \brief Configures the ADC module from a user configuration structure
 *
 * This function configures the ADC module from a user configuration structure
 *
 * \param[in] obj : pointer to ADC driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void AdcDrv_Configure(AdcDrvType *obj, const AdcDrv_ConfigType *userConfig);

/*! \brief Get configures of the ADC module
 *
 * This function get configures of the ADC module
 *
 * \param[in] obj : pointer to ADC driver instance
 * \param[out] currentConfig : pointer to configuration structure
 */
extern void AdcDrv_GetConfig(AdcDrvType *obj, AdcDrv_ConfigType *currentConfig);

/*! \brief ADC clear lock trigger
 *
 * This function for ADC clear lock trigger
 *
 * \param[in] obj : pointer to ADC driver instance
 */
extern void AdcDrv_ClrLockTrg(AdcDrvType *obj);

/*! \brief Get ADC data result
 *
 * This function for get ADC data result
 *
 * \param[in] obj : pointer to ADC driver instance
 * \param[in] chn  : channel number
 * \return ADC data result.
 */
extern uint16_t AdcDrv_GetRn(AdcDrvType *obj, uint8_t chn);

/*! \brief Get ADC conversion complete flag
 *
 * This function for get ADC conversion complete flag.
 *
 * \param[in] obj : pointer to ADC driver instance
 * \param[in] chn  : channel number
 * \return ADC data result.
 */
extern bool AdcDrv_GetCocon(AdcDrvType *obj, uint8_t chn);

/*! \brief Disable ADC
 *
 * This function for disable ADC
 *
 * \param[in] obj : pointer to ADC driver instance
 */
extern void AdcDrv_DisableAdc(AdcDrvType *obj);

/*! \brief Enable ADC
 *
 * This function for enable ADC
 *
 * \param[in] obj : pointer to ADC driver instance
 */
extern void AdcDrv_EnableAdc(AdcDrvType *obj);

/*! \brief Abort ADC channel n
 *
 * This function for abort ADC channel n
 *
 * \param[in] obj : pointer to ADC driver instance
 * \param[in] chn  : channel number
 */
extern void AdcDrv_AbortChn(AdcDrvType *obj, uint8_t chn);

/*! \brief Selects one of the input channels.
 *
 * This function for selects one of the input channels.
 *
 * \param[in] obj   : pointer to ADC driver instance
 * \param[in] chn   : channel number
 * \param[in] state : input channel selection.
 */
extern void AdcDrv_ConfigureChn(AdcDrvType *obj, uint8_t chn, AdcDrv_InChnType state);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _ADC_DRV_H_ */
