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

#ifndef _CMP_DRV_H_
#define _CMP_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of CMP module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup cmp_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 *******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief CMP type of comparator output invert selection
 */
typedef enum
{
    CMPDRV_INVT_NORMAL = 0U, /*!< Output signal isn't inverted */
    CMPDRV_INVT_INVERT = 1U, /*!< Output signal is inverted. */
} CmpDrv_InvtType;

/*! \brief CMP type of input channel low-pass filer cut-off frequency select signal
 */
typedef enum
{
    CMPDRV_LPFSEL_23MHz = 0U, /*!< 23MHz */
    CMPDRV_LPFSEL_16MHz = 1U, /*!< 16MHz */
    CMPDRV_LPFSEL_13MHz = 2U, /*!< 13MHz */
    CMPDRV_LPFSEL_10MHz = 3U, /*!< 10MHz */
} CmpDrv_LpfselType;

/*! \brief CMP type of power Mode
 */
typedef enum
{
    CMPDRV_PMODE_LS = 0U, /*!< Low Speed (LS) comparison mode is selected */
    CMPDRV_PMODE_HS = 1U, /*!< High Speed (HS) comparison mode is selected*/
} CmpDrv_PmodeType;

/*! \brief CMP type of comparator output
 */
typedef enum
{
    CMPDRV_COS_COUT  = 0U, /*!< Set CMPO to equal COUT (filtered comparator output) */
    CMPDRV_COS_COUTA = 1U, /*!< Set CMPO to equal COUTA (unfiltered comparator output)*/
} CmpDrv_CosType;

/*! \brief CMP type of comparator hard block offset control
 */
typedef enum
{
    CMPDRV_OFFSET_LEVEL_0 = 0U, /*!< The comparator hard block output has level 0 offset internally*/
    CMPDRV_OFFSET_LEVEL_1 = 1U, /*!< The comparator hard block output has level 1 offset internally*/
} CmpDrv_OffsetType;

/*! \brief CMP type of hard block hysteresis control
 */
typedef enum
{
    CMPDRV_HYSTCTR_LEVEL_0 = 0U, /*!< The hard block output has level 0 hysteresis internally*/
    CMPDRV_HYSTCTR_LEVEL_1 = 1U, /*!< The hard block output has level 1 hysteresis internally*/
    CMPDRV_HYSTCTR_LEVEL_2 = 2U, /*!< The hard block output has level 2 hysteresis internally*/
    CMPDRV_HYSTCTR_LEVEL_3 = 3U, /*!< The hard block output has level 3 hysteresis internally*/
} CmpDrv_HystctrType;

/*! \brief CMP type of selection of the input to the positive or negative port of the comparator
 */
typedef enum
{
    CMPDRV_DAC   = 0U, /*!< IN0, from the 8-bit DAC output*/
    CMPDRV_MUX   = 1U, /*!< IN1, from the analog 8-1 mux(P/N MUX)*/
} CmpDrv_InPortType;

/*! \brief CMP type of channel selection.
 */
typedef enum
{
    CMPDRV_CHANNEL_IN0 = 0U, /*!< Select IN0 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN1 = 1U, /*!< Select IN1 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN2 = 2U, /*!< Select IN2 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN3 = 3U, /*!< Select IN3 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN4 = 4U, /*!< Select IN4 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN5 = 5U, /*!< Select IN5 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN6 = 6U, /*!< Select IN6 from the analog 8-1 mux */
    CMPDRV_CHANNEL_IN7 = 7U, /*!< Select IN7 from the analog 8-1 mux */
} CmpDrv_ChSelType;

/*! \brief CMP type of supply voltage reference source
 */
typedef enum
{
    CMPDRV_VRSEL_VIN1 = 0U, /*!< Vin1 is selected as resistor ladder network supply reference Vin*/
    CMPDRV_VRSEL_VIN2 = 1U, /*!< Vin2 is selected as resistor ladder network supply reference Vin*/
} CmpDrv_VrselType;

/*! \brief CMP type of fix the analog mux port for the round-robin mode
 */
typedef enum
{
    CMPDRV_FXMP_PLUS  = 0U, /*!< The Plus port is fixed. Only the inputs to the Minus port are swept in each round*/
    CMPDRV_FXMP_MINUS = 1U, /*!< The Minus port is fixed. Only the inputs to the Plus port are swept in each round*/
} CmpDrv_FxmpType;

/*! \brief CMP type of output interrupt configuration
 */
typedef enum
{
    CMP_NO_EVENT     = 0U, /*!< Comparator output interrupts are disabled OR no event occurred. */
    CMP_FALLING_EDGE = 1U, /*!< Comparator output interrupts will be generated only on falling edge OR only falling edge event occurred. */
    CMP_RISING_EDGE  = 2U, /*!< Comparator output interrupts will be generated only on rising edge OR only rising edge event occurred. */
    CMP_BOTH_EDGES   = 3U, /*!< Comparator output interrupts will be generated on both edges OR both edges event occurred. */
} CmpDrv_TriggerType;

/*! \brief CMP type of functional modes
 */
typedef enum
{
    CMP_DISABLED                   = 0U, /*!< CMP is disabled */
    CMP_CONTINUOUS                 = 1U, /*!< Continuous mode */
    CMP_SAMPLED_NONFILTRED_INT_CLK = 2U, /*!< Sampled, Non-Filtered mode with interior clock */
    CMP_SAMPLED_NONFILTRED_EXT_CLK = 3U, /*!< Sampled, Non-Filtered mode with exterior clock */
    CMP_SAMPLED_FILTRED_INT_CLK    = 4U, /*!< Sampled, Filtered mode with interior clock */
    CMP_SAMPLED_FILTRED_EXT_CLK    = 5U, /*!< Sampled, Filtered mode with exterior clock */
    CMP_WINDOWED                   = 6U, /*!< Windowed mode */
    CMP_WINDOWED_RESAMPLED         = 7U, /*!< Windowed/Resampled mode */
    CMP_WINDOWED_FILTRED           = 8U, /*!< Windowed/Filtered mode */
} CmpDrv_ModeType;

/*! \brief Definition of configuration of CMP driver in normal modes
 */
typedef struct _CmpDrv_NormalCfgType_
{
    bool               dmaEnable;          /*!< Enables the DMA transfer triggered from the CMP module*/
    CmpDrv_TriggerType triggerMode;        /*!< Interrupt configuration*/
    CmpDrv_ModeType    mode;               /*!< The comparator functional mode*/
    uint8_t            filterSamplePeriod; /*!< Filter sample period */
    uint8_t            filterSampleCount;  /*!< Number of sample count for filtering */
    CmpDrv_PmodeType   powerMode;          /*!< Power mode select */
    CmpDrv_InvtType    inverterState;      /*!< Comparator invert */
    bool               pinState;           /*!< Comparator output pin enable */
    CmpDrv_CosType     outputSelect;       /*!< Comparator output select */
    CmpDrv_HystctrType hystLvl;            /*!< Comparator hard block hysteresis control */
    CmpDrv_OffsetType  hystOffsetState;    /*!< Comparator hard block offset control */
    CmpDrv_LpfselType  lpfsel;             /*!< CMP input channel low-pass filer cut-off frequency select signal */
} CmpDrv_NormalCfgType;

/*! \brief Definition of configuration of CMP driver of the analog mux
 */
typedef struct _CmpDrv_MuxCfgType_
{
    CmpDrv_InPortType posPortMux;  /*!< Select positive port signal*/
    CmpDrv_InPortType negPortMux;  /*!< Select negative port signal*/
    CmpDrv_ChSelType  posInputMux; /*!< Select which channel is selected for the plus mux*/
    CmpDrv_ChSelType  negInputMux; /*!< Select which channel is selected for the minus mux*/
} CmpDrv_MuxCfgType;

/*! \brief Definition of configuration of CMP driver in round robin modes
 */
typedef struct _CmpDrv_RoundRobinCfgType_
{
    bool             intrEnable;   /*!< Round - Robin interrupt enable*/
    CmpDrv_FxmpType  fixedMuxPort; /*!< Fixed the analog mux port for the round-robin mode*/
    CmpDrv_ChSelType fixedChnSel;  /*!< Select channel in the mux port is fixed in a given round-robin mode*/
    uint8_t          sampleCnt;    /*!< Select number of round-robin clock cycles for a given channel*/
    uint8_t          initDelayCnt; /*!< Comparator and DAC initialization delay modulus*/
    uint8_t          channelState; /*!< One bit for each channel state*/
                                   /*!< |---------|---------|-----|---------|---------|*/
                                   /*!< |CH7_state|CH6_state|.....|CH1_state|CH0_state|*/
                                   /*!< |---------|---------|-----|---------|---------|*/
    uint8_t channelPreState;       /*!< One bit for each channel pre-set state*/
} CmpDrv_RoundRobinCfgType;

/*! \brief Definition of configuration of DAC
 */
typedef struct _CmpDrv_DacCfgType_
{
    CmpDrv_VrselType dacVoltInSel; /*!< Supply Voltage Reference Source Select*/
    uint8_t          dacVoltScale; /*!< DAC Output Voltage Select*/
    bool             state;        /*!< DAC Enable*/
} CmpDrv_DacCfgType;

/*! \brief Definition of configuration of CMP driver
 */
typedef struct _CmpDrv_ConfigType_
{
    CmpDrv_NormalCfgType     normalCfg;
    CmpDrv_RoundRobinCfgType rrCfg;
    CmpDrv_DacCfgType        dacCfg;
    CmpDrv_MuxCfgType        muxCfg;
} CmpDrv_ConfigType;

/* Forward declaration of CMP register */
struct _CmpRegType_;

/*! \brief The definition of CMP driver class
 */
typedef struct _CmpDrvType_
{
    struct _CmpRegType_ *reg;
} CmpDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the CMP driver module
 *
 * This function initializes CMP driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to CMP driver instance
 * \param[in] reg  : pointer to CMP register instance
 */
extern void CmpDrv_Init(CmpDrvType *obj, struct _CmpRegType_ *reg);

/*! \brief Configures the CMP normal module from a user configuration structure
 *
 * This function configures the CMP normal module from a user configuration structure
 *
 * \param[in] obj       : pointer to CMP driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void CmpDrv_ConfigureNormal(CmpDrvType *obj, const CmpDrv_ConfigType *userConfig);

/*! \brief Configures the CMP round robin module from a user configuration structure
 *
 * This function configures the CMP round robin module from a user configuration structure
 *
 * \param[in] obj       : pointer to CMP driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void CmpDrv_ConfigureTriggerMode(CmpDrvType *obj, const CmpDrv_ConfigType *userConfig);

/*! \brief Get configures of the CMP module currently
 *
 * This function gets configures of the CMP module currently
 *
 * \param[in] obj        : pointer to CMP driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CmpDrv_GetConfig(const CmpDrvType *obj, CmpDrv_ConfigType *userConfig);

/*! \brief Get default configures the CMP module for configuration structure
 *
 * This function gets default configures the CMP module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CmpDrv_GetDefaultConfig(CmpDrv_ConfigType *userConfig);

/*! \brief Set state for CMP
 *
 * This function for enable or disable CMP
 *
 * \param[in] obj  : pointer to CMP driver instance
 * \param[in] state : state for CMP
 */
extern void CmpDrv_SetCmpState(CmpDrvType *obj, const bool state);

/*! \brief Get state from CMP
 *
 * This function for get state from CMP
 *
 * \param[in] obj  : pointer to CMP driver instance
 * \param[out] bool : CMP current state
 */
extern bool CmpDrv_GetCmpState(const CmpDrvType *obj);

/*! \brief Get CMP output flags
 *
 * This function for get CMP output flags
 *
 * \param[in] obj                : pointer to CMP driver instance
 * \param[out] CmpDrv_TriggerType : CMP current output flags
 */
extern CmpDrv_TriggerType CmpDrv_GetOutputFlags(const CmpDrvType *obj);

/*! \brief Clear CMP output flags
 *
 * This function for clear CMP output flags
 *
 * \param[in] obj                : pointer to CMP driver instance
 */
extern void CmpDrv_ClearOutputFlags(CmpDrvType *obj);

/*! \brief Clear CMP input flags
 *
 * This function for clear CMP input flags
 *
 * \param[in] obj                : pointer to CMP driver instance
 */
extern void CmpDrv_ClearInputFlags(CmpDrvType *obj);

/*! \brief Get CMP input flags
 *
 * This function for get CMP input flags
 *
 * \param[in] obj                : pointer to CMP driver instance
 * \param[out] uint8_t            : CMP input flags
 */
extern uint8_t CmpDrv_GetInputFlags(const CmpDrvType *obj);

/*! \brief Configures the CMP DAC from a user configuration structure
 *
 * This function configures the CMP DAC from a user configuration structure
 *
 * \param[in] obj       : pointer to CMP driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void CmpDrv_ConfigureDac(CmpDrvType *obj, const CmpDrv_DacCfgType *userConfig);

/*! \brief Get configuration the CMP DAC from a user configuration structure
 *
 * This function configures the CMP DAC from a user configuration structure
 *
 * \param[in] obj        : pointer to CMP driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CmpDrv_GetDacConfig(const CmpDrvType *obj, CmpDrv_DacCfgType *userConfig);

/*! \brief Configures the CMP analog mux from a user configuration structure
 *
 * This function configures the CMP analog mux from a user configuration structure
 *
 * \param[in] obj       : pointer to CMP driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void CmpDrv_ConfigureMux(CmpDrvType *obj, const CmpDrv_MuxCfgType *userConfig);

/*! \brief Get configuration the CMP analog mux from a user configuration structure
 *
 * This function configures the CMP analog mux from a user configuration structure
 *
 * \param[in] obj        : pointer to CMP driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CmpDrv_GetMuxConfig(const CmpDrvType *obj, CmpDrv_MuxCfgType *userConfig);

/*! \brief Configures the CMP ACO from a user configuration structure
 *
 * This function configures the CMP ACO from a user configuration structure
 *
 * \param[in] obj            : pointer to CMP driver instance
 * \param[in] channelPreState : defines the pre-set state of channel n.
 */
extern void CmpDrv_SetChannelPreState(CmpDrvType *obj, const uint8_t channelPreState);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _CMP_DRV_H_ */
