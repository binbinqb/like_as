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

#ifndef _TRGMUX_DRV_H_
#define _TRGMUX_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of TRGMUX (Trigger MUX)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup trgmux_drv
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

/*! \brief The definition of TRGMUX trigger source
 */
typedef enum
{
    TRGMUXDRV_TRIGSOURCE_SIG0           = 0U,
    TRGMUXDRV_TRIGSOURCE_SIG1           = 1U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN0     = 2U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN1     = 3U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN2     = 4U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN3     = 5U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN4     = 6U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN5     = 7U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN6     = 8U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN7     = 9U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN8     = 10U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN9     = 11U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN10    = 12U,
    TRGMUXDRV_TRIGSOURCE_TRGMUX_IN11    = 13U,
    TRGMUXDRV_TRIGSOURCE_CMP0_OUT       = 14U,
    TRGMUXDRV_TRIGSOURCE_SIG15          = 15U,
    TRGMUXDRV_TRIGSOURCE_LPIT_CH0       = 16U,
    TRGMUXDRV_TRIGSOURCE_LPIT_CH1       = 17U,
    TRGMUXDRV_TRIGSOURCE_LPIT_CH2       = 18U,
    TRGMUXDRV_TRIGSOURCE_LPIT_CH3       = 19U,
    TRGMUXDRV_TRIGSOURCE_SIG20          = 20U,
    TRGMUXDRV_TRIGSOURCE_LPTMR0         = 21U,
    TRGMUXDRV_TRIGSOURCE_MFT0_INIT_TRIG = 22U,
    TRGMUXDRV_TRIGSOURCE_MFT0_EXT_TRIG  = 23U,
    TRGMUXDRV_TRIGSOURCE_MFT1_INIT_TRIG = 24U,
    TRGMUXDRV_TRIGSOURCE_MFT1_EXT_TRIG  = 25U,
    TRGMUXDRV_TRIGSOURCE_MFT2_INIT_TRIG = 26U,
    TRGMUXDRV_TRIGSOURCE_MFT2_EXT_TRIG  = 27U,
    TRGMUXDRV_TRIGSOURCE_MFT3_INIT_TRIG = 28U,
    TRGMUXDRV_TRIGSOURCE_MFT3_EXT_TRIG  = 29U,
    TRGMUXDRV_TRIGSOURCE_MFT4_INIT_TRIG = 30U,
    TRGMUXDRV_TRIGSOURCE_MFT4_EXT_TRIG  = 31U,
    TRGMUXDRV_TRIGSOURCE_MFT5_INIT_TRIG = 32U,
    TRGMUXDRV_TRIGSOURCE_MFT5_EXT_TRIG  = 33U,
    TRGMUXDRV_TRIGSOURCE_ADC0_SC1A_COCO = 34U,
    TRGMUXDRV_TRIGSOURCE_ADC0_SC1B_COCO = 35U,
    TRGMUXDRV_TRIGSOURCE_ADC1_SC1A_COCO = 36U,
    TRGMUXDRV_TRIGSOURCE_ADC1_SC1B_COCO = 37U,
    TRGMUXDRV_TRIGSOURCE_PDB0_CH0_TRIG  = 38U,
    TRGMUXDRV_TRIGSOURCE_PDB0_PULSE_OUT = 39U,
    TRGMUXDRV_TRIGSOURCE_PDB1_CH0_TRIG  = 40U,
    TRGMUXDRV_TRIGSOURCE_PDB1_PULSE_OUT = 41U,
    TRGMUXDRV_TRIGSOURCE_RTC_ALARM      = 42U,
    TRGMUXDRV_TRIGSOURCE_RTC_SECOND     = 43U,
    TRGMUXDRV_TRIGSOURCE_SPI0_FRAME     = 44U,
    TRGMUXDRV_TRIGSOURCE_SPI0_WORD      = 45U,
    TRGMUXDRV_TRIGSOURCE_SPI1_FRAME     = 46U,
    TRGMUXDRV_TRIGSOURCE_SPI1_WORD      = 47U,
    TRGMUXDRV_TRIGSOURCE_SPI2_FRAME     = 48U,
    TRGMUXDRV_TRIGSOURCE_SPI2_WORD      = 49U,
    TRGMUXDRV_TRIGSOURCE_SPI3_FRAME     = 50U,
    TRGMUXDRV_TRIGSOURCE_SPI3_WORD      = 51U,
    TRGMUXDRV_TRIGSOURCE_SIM_SW_TRIG    = 52U,
    TRGMUXDRV_TRIGSOURCE_SIG53          = 53U,
    TRGMUXDRV_TRIGSOURCE_SIG54          = 54U,
    TRGMUXDRV_TRIGSOURCE_SIG55          = 55U,
    TRGMUXDRV_TRIGSOURCE_SIG56          = 56U,
    TRGMUXDRV_TRIGSOURCE_SIG57          = 57U,
    TRGMUXDRV_TRIGSOURCE_SIG58          = 58U,
    TRGMUXDRV_TRIGSOURCE_SIG59          = 59U,
    TRGMUXDRV_TRIGSOURCE_SIG60          = 60U,
    TRGMUXDRV_TRIGSOURCE_SIG61          = 61U,
    TRGMUXDRV_TRIGSOURCE_SIG62          = 62U,
    TRGMUXDRV_TRIGSOURCE_SIG63          = 63U,

} TrgMuxDrv_TrigSourceType;

/*! \brief The definition of TRGMUX trigger module
 */
typedef enum
{
    TRGMUXDRV_TARGETMODULE_DMA_CH0         = 0U,
    TRGMUXDRV_TARGETMODULE_DMA_CH1         = 1U,
    TRGMUXDRV_TARGETMODULE_DMA_CH2         = 2U,
    TRGMUXDRV_TARGETMODULE_DMA_CH3         = 3U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT0     = 4U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT1     = 5U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT2     = 6U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT3     = 7U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT4     = 8U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT5     = 9U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT6     = 10U,
    TRGMUXDRV_TARGETMODULE_TRGMUX_OUT7     = 11U,
    TRGMUXDRV_TARGETMODULE_ADC0_ADHWT_TLA0 = 12U,
    TRGMUXDRV_TARGETMODULE_ADC0_ADHWT_TLA1 = 13U,
    TRGMUXDRV_TARGETMODULE_ADC0_ADHWT_TLA2 = 14U,
    TRGMUXDRV_TARGETMODULE_ADC0_ADHWT_TLA3 = 15U,
    TRGMUXDRV_TARGETMODULE_ADC1_ADHWT_TLA0 = 16U,
    TRGMUXDRV_TARGETMODULE_ADC1_ADHWT_TLA1 = 17U,
    TRGMUXDRV_TARGETMODULE_ADC1_ADHWT_TLA2 = 18U,
    TRGMUXDRV_TARGETMODULE_ADC1_ADHWT_TLA3 = 19U,
    TRGMUXDRV_TARGETMODULE_CMP0_SAMPLE     = 20U,
    TRGMUXDRV_TARGETMODULE_MFT0_HWTRIG0    = 24U,
    TRGMUXDRV_TARGETMODULE_MFT0_FAULT0     = 25U,
    TRGMUXDRV_TARGETMODULE_MFT0_FAULT1     = 26U,
    TRGMUXDRV_TARGETMODULE_MFT0_FAULT2     = 27U,
    TRGMUXDRV_TARGETMODULE_MFT1_HWTRIG0    = 28U,
    TRGMUXDRV_TARGETMODULE_MFT1_FAULT0     = 29U,
    TRGMUXDRV_TARGETMODULE_MFT1_FAULT1     = 30U,
    TRGMUXDRV_TARGETMODULE_MFT1_FAULT2     = 31U,
    TRGMUXDRV_TARGETMODULE_MFT2_HWTRIG0    = 32U,
    TRGMUXDRV_TARGETMODULE_MFT2_FAULT0     = 33U,
    TRGMUXDRV_TARGETMODULE_MFT2_FAULT1     = 34U,
    TRGMUXDRV_TARGETMODULE_MFT2_FAULT2     = 35U,
    TRGMUXDRV_TARGETMODULE_MFT3_HWTRIG0    = 36U,
    TRGMUXDRV_TARGETMODULE_MFT3_FAULT0     = 37U,
    TRGMUXDRV_TARGETMODULE_MFT3_FAULT1     = 38U,
    TRGMUXDRV_TARGETMODULE_MFT3_FAULT2     = 39U,
    TRGMUXDRV_TARGETMODULE_MFT4_HWTRIG0    = 40U,
    TRGMUXDRV_TARGETMODULE_MFT4_FAULT0     = 41U,
    TRGMUXDRV_TARGETMODULE_MFT4_FAULT1     = 42U,
    TRGMUXDRV_TARGETMODULE_MFT4_FAULT2     = 43U,
    TRGMUXDRV_TARGETMODULE_MFT5_HWTRIG0    = 44U,
    TRGMUXDRV_TARGETMODULE_MFT5_FAULT0     = 45U,
    TRGMUXDRV_TARGETMODULE_MFT5_FAULT1     = 46U,
    TRGMUXDRV_TARGETMODULE_MFT5_FAULT2     = 47U,
    TRGMUXDRV_TARGETMODULE_PDB0_TRG_IN     = 48U,
    TRGMUXDRV_TARGETMODULE_PDB1_TRG_IN     = 52U,
    TRGMUXDRV_TARGETMODULE_LPIT_TRG_CH0    = 56U,
    TRGMUXDRV_TARGETMODULE_LPIT_TRG_CH1    = 57U,
    TRGMUXDRV_TARGETMODULE_LPIT_TRG_CH2    = 58U,
    TRGMUXDRV_TARGETMODULE_LPIT_TRG_CH3    = 59U,
    TRGMUXDRV_TARGETMODULE_LPTMR_ALT0      = 60U,
} TrgMuxDrv_TargetModuleType;

/*! \brief Definition of In Out Mapping of TRGMUX driver
 */
typedef struct _TrgMuxDrv_InOutMappingType_
{
    TrgMuxDrv_TrigSourceType   triggerSource;       /*!< selects one of the TRGMUX trigger sources */
    TrgMuxDrv_TargetModuleType targetModule;        /*!< selects one of the TRGMUX target modules  */
    bool                       lockTargetModuleReg; /*!< if true, the LOCK bit of the target module register will be
                                                     set by TrgMuxDrv_Configure(), after the current mapping is configured */

} TrgMuxDrv_InOutMappingType;

/*! \brief Definition of configuration of TRGMUX driver
 */
typedef struct _TrgMuxDrv_ConfigType_
{
    uint16_t                          numOfInOutMappings; /*!< number of in-out mappings defined in TRGMUX configuration */
    const TrgMuxDrv_InOutMappingType *inOutMapping;       /*!< pointer to array of in-out mapping structures */
} TrgMuxDrv_ConfigType;

/* Forward declaration of TRGMUX register */
struct _TrgMuxRegType_;
/* Forward declaration of TRGMUX register */
struct _SimRegType_;

/*! \brief The definition of TRGMUX driver class
 */
typedef struct _TrgMuxDrvType_
{
    struct _TrgMuxRegType_ *trgMuxReg;
    struct _SimRegType_    *simReg;
} TrgMuxDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

/*! \brief Initializes the TRGMUX driver module
 *
 * This function initializes TRGMUX driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] reg : pointer to TRGMUX register instance
 */
extern void TrgMuxDrv_Init(TrgMuxDrvType *obj, struct _TrgMuxRegType_ *trgMuxReg, struct _SimRegType_ *simReg);

/*! \brief Configures the TRGMUX module from the user configuration structure
 *
 * This function configures the TRGMUX module from the user configuration structure
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void TrgMuxDrv_Configure(TrgMuxDrvType *obj, const TrgMuxDrv_ConfigType *userConfig);

/*! \brief Configure a source trigger for a selected target module.
 *
 * This function configures a TRGMUX link between a source trigger and a target module,
 * if the requested target module is not locked.
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] triggerSource : One of the values in the TrgMuxDrv_TrigSourceType enumeration
 * \param[in] targetModule : One of the values in the TrgMuxDrv_TargetModuleType enumeration
 * \return the result of setting source for target module
 *         - true : succeed
 *         - false : failed because targetModule is locked
 */
extern bool TrgMuxDrv_SetTrigSourceForTargetModule(TrgMuxDrvType *obj, TrgMuxDrv_TrigSourceType triggerSource, TrgMuxDrv_TargetModuleType targetModule);

/*! \brief Get the source trigger configured for a target module.
 *
 * This function returns the TRGMUX source trigger linked to a selected target module.
 *
 * \note If the target module is invalid (not in the enum), this function will return source 0
 *       which has no meaning.
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] triggerSource : One of the values in the TrgMuxDrv_TrigSourceType enumeration
 * \param[in] targetModule : One of the values in the TrgMuxDrv_TargetModuleType enumeration
 */
extern TrgMuxDrv_TrigSourceType TrgMuxDrv_GetTrigSourceForTargetModule(const TrgMuxDrvType *obj, TrgMuxDrv_TargetModuleType targetModule);

/*! \brief Locks the TRGMUX register of a target module.
 *
 * This function sets the LK bit of the TRGMUX register corresponding to
 * the selected target module. Please note that some TRGMUX registers can contain up to 4
 * SEL bitfields, meaning that these registers can be used to configure up to 4 target
 * modules independently. Because the LK bit is only one per register, the configuration
 * of all target modules referred from that register will be locked.
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] targetModule : One of the values in the TrgMuxDrv_TargetModuleType enumeration
 */
extern void TrgMuxDrv_SetLockForTargetModule(TrgMuxDrvType *obj, TrgMuxDrv_TargetModuleType targetModule);

/*! \brief Get the Lock bit status of the TRGMUX register of a target module.
 *
 * This function gets the value of the LK bit from the TRGMUX register corresponding to
 * the selected target module.
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] targetModule : One of the values in the TrgMuxDrv_TargetModuleType enumeration
 * \return the result of lock
 *         - true : if the selected targetModule register is locked
 *         - false : if the selected targetModule register is not locked
 */
extern bool TrgMuxDrv_GetLockForTargetModule(const TrgMuxDrvType *obj, TrgMuxDrv_TargetModuleType targetModule);

/*! \brief Generate software triggers
 *
 * This function uses a SIM register in order to generate a software triggers to the target
 * peripherals selected in TRGMUX
 *
 * \param[in] obj : pointer to TRGMUX driver instance
 * \param[in] delay : set delay time for trigger pulse width
 */
extern void TrgMuxDrv_GenSWTrigger(TrgMuxDrvType *obj, uint32_t delay);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _TRGMUX_DRV_H_ */
