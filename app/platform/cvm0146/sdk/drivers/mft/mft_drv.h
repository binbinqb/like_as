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

#ifndef _MFT_DRV_H_
#define _MFT_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of MFT (Multi Functional Timer)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "mft_reg.h"

/*! \addtogroup mft_drv
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

/*! \brief MFT counting mode
 */
typedef enum
{
    MFTDRV_UP_COUNTING,      /*!< up counting mode */
    MFTDRV_UP_DOWN_COUNTING, /*!< up-down counting mode */
} MftDrv_CountingModeType;

/*! \brief MFT clock source selection
 */
typedef enum
{
    MFTDRV_CLOCK_SOURCE_NONE        = 0x00U, /*!< None use clock for MFT  */
    MFTDRV_CLOCK_SOURCE_SYSTEMCLK   = 0x01U, /*!< System clock            */
    MFTDRV_CLOCK_SOURCE_FIXEDCLK    = 0x02U, /*!< Fixed clock             */
    MFTDRV_CLOCK_SOURCE_EXTERNALCLK = 0x03U  /*!< External clock          */
} MftDrv_ClockSrcType;

/*! \brief MFT pre-scaler factor selection for the clock source
 */
typedef enum
{
    MFTDRV_PRESCALE_DIV_BY_1   = 0x00U, /*!< Divide by 1   */
    MFTDRV_PRESCALE_DIV_BY_2   = 0x01U, /*!< Divide by 2   */
    MFTDRV_PRESCALE_DIV_BY_4   = 0x02U, /*!< Divide by 4   */
    MFTDRV_PRESCALE_DIV_BY_8   = 0x03U, /*!< Divide by 8   */
    MFTDRV_PRESCALE_DIV_BY_16  = 0x04U, /*!< Divide by 16  */
    MFTDRV_PRESCALE_DIV_BY_32  = 0x05U, /*!< Divide by 32  */
    MFTDRV_PRESCALE_DIV_BY_64  = 0x06U, /*!< Divide by 64  */
    MFTDRV_PRESCALE_DIV_BY_128 = 0x07U  /*!< Divide by 128 */
} MftDrv_PrescaleType;

/*! \brief List of MFT interrupts
 */
typedef enum
{
    MFTDRV_CHANNEL0_INT_ENABLE      = 0x00000001U, /*!< Channel 0 interrupt */
    MFTDRV_CHANNEL1_INT_ENABLE      = 0x00000002U, /*!< Channel 1 interrupt */
    MFTDRV_CHANNEL2_INT_ENABLE      = 0x00000004U, /*!< Channel 2 interrupt */
    MFTDRV_CHANNEL3_INT_ENABLE      = 0x00000008U, /*!< Channel 3 interrupt */
    MFTDRV_CHANNEL4_INT_ENABLE      = 0x00000010U, /*!< Channel 4 interrupt */
    MFTDRV_CHANNEL5_INT_ENABLE      = 0x00000020U, /*!< Channel 5 interrupt */
    MFTDRV_CHANNEL6_INT_ENABLE      = 0x00000040U, /*!< Channel 6 interrupt */
    MFTDRV_CHANNEL7_INT_ENABLE      = 0x00000080U, /*!< Channel 7 interrupt */
    MFTDRV_FAULT_INT_ENABLE         = 0x00000100U, /*!< Fault interrupt */
    MFTDRV_TIME_OVERFLOW_INT_ENABLE = 0x00000200U, /*!< Time overflow interrupt */
    MFTDRV_RELOAD_INT_ENABLE        = 0x00000400U  /*!< Reload interrupt */
} MftDrv_InterruptOptionType;

/*! \brief List of MFT flags
 */
typedef enum
{
    MFTDRV_CHANNEL0_FLAG        = 0x00000001U, /*!< Channel 0 Flag */
    MFTDRV_CHANNEL1_FLAG        = 0x00000002U, /*!< Channel 1 Flag */
    MFTDRV_CHANNEL2_FLAG        = 0x00000004U, /*!< Channel 2 Flag */
    MFTDRV_CHANNEL3_FLAG        = 0x00000008U, /*!< Channel 3 Flag */
    MFTDRV_CHANNEL4_FLAG        = 0x00000010U, /*!< Channel 4 Flag */
    MFTDRV_CHANNEL5_FLAG        = 0x00000020U, /*!< Channel 5 Flag */
    MFTDRV_CHANNEL6_FLAG        = 0x00000040U, /*!< Channel 6 Flag */
    MFTDRV_CHANNEL7_FLAG        = 0x00000080U, /*!< Channel 7 Flag */
    MFTDRV_FAULT_FLAG           = 0x00000100U, /*!< Fault Flag */
    MFTDRV_TIME_OVER_FLOW_FLAG  = 0x00000200U, /*!< Time overflow Flag */
    MFTDRV_RELOAD_FLAG          = 0x00000400U, /*!< Reload Flag */
    MFTDRV_CHANNEL_TRIGGER_FLAG = 0x00000800U  /*!< Channel trigger Flag */
} MftDrv_StatusFlagType;

/*! \brief List of MFT BDM Mode
 */
typedef enum
{
    MFTDRV_BDM_MODE_00 = 0x00U, /*!< MFT counter stopped */
    MFTDRV_BDM_MODE_01 = 0x01U, /*!< MFT counter stopped */
    MFTDRV_BDM_MODE_10 = 0x02U, /*!< MFT counter stopped */
    MFTDRV_BDM_MODE_11 = 0x03U  /*!< MFT counter in functional mode*/
} MftDrv_BdmModeType;

/*! \brief MFT configuration structure
 */
typedef struct _MftDrv_ConfigType_
{
    MftDrv_ClockSrcType     clockSource;  /*!< Clock source */
    MftDrv_CountingModeType countingMode; /*!< Counting mode */
    MftDrv_PrescaleType     prescaler;    /*!< Register pre-scaler options */
    MftDrv_BdmModeType      bdmMode;      /*!< Select MFT behavior in BDM mode */
} MftDrv_ConfigType;

/*! \brief The definition of MFT driver prototype
 */
typedef struct _MftDrvType_
{
    struct _MftRegType_ *reg; /*!< MFT register */
} MftDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT reg and state
 *
 * This function initializes MFT driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] reg : pointer to MFT register instance
 */
extern void MftDrv_Init(MftDrvType *obj, struct _MftRegType_ *reg);

/*! \brief Get default configures the MFT module for configuration structure
 *
 * This function gets default configures the MFT module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftDrv_GetDefaultConfig(MftDrv_ConfigType *userConfig);

/*! \brief Configure the MFT driver
 *
 * This function resets MFT module, enables the MFT module, configures MFT
 * module. The MFT configuration structure shall
 * be passed as arguments.
 * This function should be called before calling any other MFT driver function.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] userConfig : pointer to MFT config instance
 */
extern void MftDrv_Config(MftDrvType *obj, const MftDrv_ConfigType *userConfig);

/*! \brief Mask the output of channels
 *
 * This function will mask the output of the channels and at match events will be ignored
 * by the masked channels.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channelsMask : channels mask
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_MaskOutputChannels(MftDrvType *obj, uint32_t channelsMask, bool softWareTrigger);

/*! \brief Initializes the Mft module counter value
 *
 * This function configure the initial counter value. The counter will get this
 * value after an overflow event.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] counterValue : counter Value
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetInitialCounterValue(MftDrvType *obj, uint16_t counterValue, bool softWareTrigger);

/*! \brief Get the Mft module channel counter value
 *
 * This function get the counter value. Captured MFT counter value of the input modes or
 * the match value for the output modes
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channel : channel number
 * \return Channel counter value
 */
extern uint16_t MftDrv_GetChnCounterValue(MftDrvType *obj, uint8_t channel);

/*! \brief Configure the value of the counter which will generates an reload point
 *
 * This function configure the value of the counter which will
 * generates an reload point.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] reloadPoint : reload Point
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetHalfCycleReloadPoint(MftDrvType *obj, uint16_t reloadPoint, bool softWareTrigger);

/*! \brief Set soft out channel value
 *
 * This function will force the output value of a channel to a specific value.
 * Before using this function it's mandatory to mask the match events using
 * MftDrv_MaskOutputChannels and to enable software output control using
 * MftDrv_SetSoftwareOutputChannelControl.
 *
 * \note When the PWM signal is configured with LOW/HIGH polarity on the channel (n).
 * It should be set the safe state as LOW level state. However, We will have an issue
 * with COMP bit is zero and CH(n)OCV is HIGH and CH(n+1)OCV is LOW.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channelsValues : The values which will be software configured for channels.
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetSoftOutChnValue(MftDrvType *obj, uint8_t channelsValues, bool softWareTrigger);

/*! \brief Set software output channel Control
 *
 * This function will configure which output channel can be software controlled.
 * Software output control forces the following values on channels (n) and (n+1) when the
 * COMP bit is zero and POL bit is zero.
 * CH(n)OC|CH(n+1)OC|CH(n)OCV|CH(n+1)OCV|Channel (n) Output      | Channel (n+1) Output
 *    0   |    0    |   X    |    X     | is not modified by SWOC| is not modified by SWOC
 *    1   |    1    |   0    |    0     | is forced to zero      | is forced to zero
 *    1   |    1    |   0    |    1     | is forced to zero      | is forced to one
 *    1   |    1    |   1    |    0     | is forced to one       | is forced to zero
 *    1   |    1    |   1    |    1     | is forced to one       | is forced to one
 *
 * Software output control forces the following values on channels (n) and (n+1) when the
 * COMP bit is one and POL bit is zero.
 * CH(n)OC|CH(n+1)OC|CH(n)OCV|CH(n+1)OCV|Channel (n) Output      | Channel (n+1) Output
 *    0   |    0    |   X    |    X     | is not modified by SWOC| is not modified by SWOC
 *    1   |    1    |   0    |    0     | is forced to zero      | is forced to zero
 *    1   |    1    |   0    |    1     | is forced to zero      | is forced to one
 *    1   |    1    |   1    |    0     | is forced to one       | is forced to zero
 *    1   |    1    |   1    |    1     | is forced to one       | is forced to zero
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channelsMask : The mask which will configure the channels which can be software controlled
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetSoftwareOutputChannelControl(MftDrvType *obj, uint8_t channelsMask, bool softWareTrigger);

/*! \brief This function will control list of channels by software to force the output to specified value.
 *
 * Despite the odd channels are configured as HIGH/LOW, they will be inverted in the following
 * configuration: COMP bit = 1 and CH(n)OCV and CH(n+1)OCV are HIGH.
 * Please check software output control behavior chapter from reference manual.
 *
 * \note When the PWM signal is configured with LOW/HIGH polarity on the channel (n).
 * It should be set the safe state as LOW level state. However, We will have an issue
 * with COMP bit is zero and CH(n)OCV is HIGH and CH(n+1)OCV is LOW.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channelsMask : The mask which will configure the channels which can be software controlled.
 * \param[in] channelValueMask : The values which will be software configured for channels.
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetAllChnSoftwareOutputControl(MftDrvType *obj, uint8_t channelMask, uint8_t channelValueMask, bool softWareTrigger);

/*! \brief Set inverting control
 *
 * This function will configure if the second channel of a pair will be inverted or not.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channelsPairMask : The mask which will configure which channel pair will invert the second channel.
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetInvertingControl(MftDrvType *obj, uint8_t channelsPairMask, bool softWareTrigger);

/*! \brief Set Modulo Counter Value
 *
 * This function configure the maximum counter value.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] counterValue : Maximum counter value
 * \param[in] softWareTrigger : whether to enable softWare trigger
 *                              - false : disable software trigger
 *                              - true : enable software trigger
 */
extern void MftDrv_SetModuloCounterValue(MftDrvType *obj, uint16_t counterValue, bool softWareTrigger);

/*! \brief Set Output level
 *
 * This function will set the channel edge or level on the selection
 * of the channel mode.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channel : channel number
 * \param[in] level : the level or edge selection for channel mode.
 */
extern void MftDrv_SetOutputlevel(MftDrvType *obj, uint8_t channel, uint8_t level);

/*! \brief Enable interrupts
 *
 * This function will enable the generation a list of interrupts.
 * It includes the MFT overflow interrupts, the reload point interrupt, the fault
 * interrupt and the channel (n) interrupt.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] interruptMask : interrupt Mask. This is the logical OR of members of the MftDrv_InterruptOptionType
 */
extern void MftDrv_EnableInterrupts(MftDrvType *obj, uint32_t interruptMask);

/*! \brief Disable interrupts
 *
 * This function is used to disable some interrupts.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] interruptMask : interrupt Mask. This is the logical OR of members of the MftDrv_InterruptOptionType
 */
extern void MftDrv_DisableInterrupts(MftDrvType *obj, uint32_t interruptMask);

/*! \brief Get enabled interrupts
 *
 * This function will get the enabled MFT interrupts.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \return The enabled interrupts. This is the logical OR of members of the MftDrv_InterruptOptionType
 */
extern uint32_t MftDrv_GetEnabledInterrupts(MftDrvType *obj);

/*! \brief Get status flags
 *
 * This function will get the MFT status flags.
 *
 * \note Regarding the duty cycle is 100% at the channel output, the match interrupt
 * has no event due to the C(n)V and C(n+1)V value are not between CNTIN value and MOD value.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \return The status flags. This is the logical OR of members of the MftDrv_StatusFlagType
 */
extern uint32_t MftDrv_GetStatusFlags(MftDrvType *obj);

/*! \brief Clear status flags
 *
 * This function is used to clear the MFT status flags.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] flagMask : The status flags to clear. This is a logical OR of members of the MftDrv_StatusFlagType
 */
extern void MftDrv_ClearStatusFlags(MftDrvType *obj, uint32_t flagMask);

/*! \brief Reset the counter
 *
 * This function will allow the MFT to restart the counter to
 * its initial counting value in the register.
 *
 * \note The configuration is set in the MftDrv_SetSync() function to make
 * sure that the MFT registers are updated by software trigger or hardware trigger.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] softwareTrigger : Selects the software trigger or hardware trigger to update COUNT register.
 *                              - true: A software trigger is generate to update register
 *                              - false: A software trigger is not implemented and need to update later or
 *                                       select a hardware trigger and waiting an external trigger for updating register.
 */
extern void MftDrv_CounterReset(MftDrvType *obj, bool softWareTrigger);

/*! \brief Enables or disables the MFT dual edge capture mode.
 *
 * This function enables or disables the MFT dual edge capture mode.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of dual edge capture mode
 *                     - true : To enable dual edge capture
 *                     - false : To disable
 */
extern void MftDrv_SetDualEdgeCaptureCmd(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables the MFT channel dual edge capture.
 *
 * This function enables or disables the MFT channel dual edge capture.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of dual edge capture mode
 *                     - true : To enable dual edge capture
 *                     - false : To disable
 */
extern void MftDrv_SetDualChannelDecap(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables the MFT dual edge capture mode.
 *
 * This function enables or disables the MFT dual edge capture mode.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \return Dual edge capture mode status
 *         - true : To enable dual edge capture
 *         - false: To disable
 */
extern bool MftDrv_GetDualEdgeCaptureCmd(MftDrvType *obj, uint8_t pairNum);

/*! \brief Enables or disables the MFT complementary mode
 *
 * This function enables or disables the MFT complementary mode
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of complementary mode
 *                     - true : To enable complementary
 *                     - false : To disable
 */
extern void MftDrv_SetDualChannelComp(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables the MFT combine mode
 *
 * This function enables or disables the MFT combine mode
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of combine mode
 *                     - true : To enable combine
 *                     - false : To disable
 */
extern void MftDrv_SetDualChannelCombine(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables the MFT modified combine mode
 *
 * This function enables or disables the MFT modified combine mode
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of modified combine mode
 *                     - true : To enable modified combine
 *                     - false : To disable
 */
extern void MftDrv_SetDualChannelModifiedCombine(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables the MFT dual channel fault
 *
 * This function enables or disables the MFT dual channel fault
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of dual channel fault
 *                     - true : To enable dual channel fault
 *                     - false : To disable
 */
extern void MftDrv_SetDualChannelFault(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables the MFT dual channel PWM sync
 *
 * This function enables or disables the MFT dual channel PWM sync
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel pair number
 * \param[in] enable : State of dual channel PWM sync
 *                     - true : To enable dual channel PWM sync
 *                     - false : To disable
 */
extern void MftDrv_SetDualChannelPwmSync(MftDrvType *obj, uint8_t pairNum, bool enable);

/*! \brief Enables or disables PWM channel Outputs
 *
 * This function enables or disables PWM channel Outputs
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channel : The MFT peripheral channel number
 * \param[in] enable : whether to enable PWM channel output
 *                     - true : enable PWM channel output
 *                     - false : disable PWM channel output
 */
extern void MftDrv_EnablePwmChannelOutputs(MftDrvType *obj, uint8_t channel, bool enable);

/*! \brief Enables or disables the generation of the MFT peripheral timer channel trigger
 *
 * This function enables or disables the generation of the MFT peripheral timer channel trigger
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channel : The MFT peripheral channel number
 * \param[in] enable : State of trigger command
 *                     - true : enable external trigger
 *                     - false : disable external trigger
 */
extern void MftDrv_SetChannelTriggerCmd(MftDrvType *obj, uint8_t channel, bool enable);

/*! \brief Sets the PWM Synchronization Software Trigger
 *
 * This function sets the PWM Synchronization Software Trigger
 *
 * \param[in] obj : pointer to MFT driver instance
 */
extern void MftDrv_SoftWareTrigger(MftDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_DRV_H_ */
