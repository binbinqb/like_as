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

#ifndef _PDB_DRV_H_
#define _PDB_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of PDB module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup pdb_drv
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

/*! \brief PDB type of LDMOD
 */
typedef enum
{
    /*!< The internal registers are loaded with the values from their buffers, immediately after 1 is written to LDOK. */
    PDBDRV_LDMOD_LOAD_VAL_IMMEDIATELY = 0U,

    /*!< The internal registers are loaded with the values from their buffers when the PDB counter (CNT) = MOD + 1 CNT delay elapsed, after 1 is written to LDOK. */
    PDBDRV_LDMOD_LOAD_VAL_AT_MODULO_COUNTER = 1U,

    /*!< The internal registers are loaded with the values from their buffers when a trigger input event is detected, after 1 is written to LDOK.*/
    PDBDRV_LDMOD_LOAD_VAL_AT_NEXT_TRIGGER = 2U,

    /*!< The internal registers are loaded with the values from their buffers when either the PDB counter (CNT) = MOD + 1 CNT delay elapsed, or a trigger
    input event is detected, after 1 is written to LDOK.*/
    PDBDRV_LDMOD_LOAD_VAL_AT_MODULO_COUNTER_OR_NEXT_TRIGGER = 3U,
} PdbDrv_LdmodType;

/*! \brief PDB type of trigger input source select
 * Trigger-In 1 ~ Trigger-In 14 is reserved
 */
typedef enum
{
    PDBDRV_TRGSEL_TRGGER_IN_0     = 0U,  /*!< Select Trigger channel 0*/
    PDBDRV_TRGSEL_TRGGER_IN_1     = 1U,  /*!< Select Trigger channel 1*/
    PDBDRV_TRGSEL_TRGGER_IN_2     = 2U,  /*!< Select Trigger channel 2*/
    PDBDRV_TRGSEL_TRGGER_IN_3     = 3U,  /*!< Select Trigger channel 3*/
    PDBDRV_TRGSEL_TRGGER_IN_4     = 4U,  /*!< Select Trigger channel 4*/
    PDBDRV_TRGSEL_TRGGER_IN_5     = 5U,  /*!< Select Trigger channel 5*/
    PDBDRV_TRGSEL_TRGGER_IN_6     = 6U,  /*!< Select Trigger channel 6*/
    PDBDRV_TRGSEL_TRGGER_IN_7     = 7U,  /*!< Select Trigger channel 7*/
    PDBDRV_TRGSEL_TRGGER_IN_8     = 8U,  /*!< Select Trigger channel 8*/
    PDBDRV_TRGSEL_TRGGER_IN_9     = 9U,  /*!< Select Trigger channel 9*/
    PDBDRV_TRGSEL_TRGGER_IN_10    = 10U, /*!< Select Trigger channel 10*/
    PDBDRV_TRGSEL_TRGGER_IN_11    = 11U, /*!< Select Trigger channel 11*/
    PDBDRV_TRGSEL_TRGGER_IN_12    = 12U, /*!< Select Trigger channel 12*/
    PDBDRV_TRGSEL_TRGGER_IN_13    = 13U, /*!< Select Trigger channel 13*/
    PDBDRV_TRGSEL_TRGGER_IN_14    = 14U, /*!< Select Trigger channel 14*/
    PDBDRV_TRGSEL_TRGGER_SOFTWARE = 15U, /*!< Select Trigger form Software*/
} PdbDrv_TrgselType;

/*! \brief PDB type of Pre-Trigger channel selection.
 */
typedef enum
{
    PDBDRV_PRE_CHANNEL0  = 0U, /*!< Select Pre-Trigger channel 0*/
    PDBDRV_PRE_CHANNEL1  = 1U, /*!< Select Pre-Trigger channel 1*/
    PDBDRV_PRE_CHANNEL2  = 2U, /*!< Select Pre-Trigger channel 2*/
    PDBDRV_PRE_CHANNEL3  = 3U, /*!< Select Pre-Trigger channel 3*/
    PDBDRV_PRE_CHANNEL4  = 4U, /*!< Select Pre-Trigger channel 4*/
    PDBDRV_PRE_CHANNEL5  = 5U, /*!< Select Pre-Trigger channel 5*/
    PDBDRV_PRE_CHANNEL6  = 6U, /*!< Select Pre-Trigger channel 6*/
    PDBDRV_PRE_CHANNEL7  = 7U, /*!< Select Pre-Trigger channel 7*/
    PDBDRV_PRE_CH_NUMBER = 8U, /*!< Pre-Trigger channel number*/
} PdbDrv_PreChType;

/*! \brief PDB type of channel selection.
 */
typedef enum
{
    PDBDRV_CHANNEL0  = 0U, /*!< Select channel 0*/
    PDBDRV_CHANNEL1  = 1U, /*!< Select channel 1*/
    PDBDRV_CHANNEL2  = 2U, /*!< Select channel 2*/
    PDBDRV_CH_NUMBER = 3U, /*!< channel number*/
} PdbDrv_ChType;

/*! \brief PDB type of Pulse out channel selection.
 */
typedef enum
{
    PDBDRV_PO_CHANNEL0  = 0U, /*!< Select pulse out channel 0*/
    PDBDRV_PO_CH_NUMBER = 1U, /*!< Pulse out channel number*/
} PdbDrv_PoChType;

/*! \brief PDB type of CONT
 */
typedef enum
{
    PDBDRV_CONT_ONE_SHOT   = 0U, /*!< PDB operation in One-Shot mode*/
    PDBDRV_CONT_CONTINUOUS = 1U, /*!< PDB operation in Continuous mode*/
} PdbDrv_ContType;

/*! \brief PDB type of PRESCALER
 */
typedef enum
{
    PDBDRV_PRESCALER_1MULT   = 0U, /*!< Counting uses the peripheral clock divided by MULT (the multiplication factor). */
    PDBDRV_PRESCALER_2MULT   = 1U, /*!< Counting uses the peripheral clock divided by 2 x MULT (the multiplication factor). */
    PDBDRV_PRESCALER_4MULT   = 2U, /*!< Counting uses the peripheral clock divided by 4 x MULT (the multiplication factor). */
    PDBDRV_PRESCALER_8MULT   = 3U, /*!< Counting uses the peripheral clock divided by 8 x MULT (the multiplication factor). */
    PDBDRV_PRESCALER_16MULT  = 4U, /*!< Counting uses the peripheral clock divided by 16 x MULT (the multiplication factor). */
    PDBDRV_PRESCALER_32MULT  = 5U, /*!< Counting uses the peripheral clock divided by 32 x MULT (the multiplication factor). */
    PDBDRV_PRESCALER_64MULT  = 6U, /*!< Counting uses the peripheral clock divided by 64 x MULT (the multiplication factor). */
    PDBDRV_PRESCALER_128MULT = 7U, /*!< Counting uses the peripheral clock divided by 128 x MULT (the multiplication factor). */
} PdbDrv_PrescalerType;

/*! \brief PDB type of MULT
 */
typedef enum
{
    PDBDRV_MULT_FACTOR_1  = 0U, /*!< Multiplication factor is 1*/
    PDBDRV_MULT_FACTOR_10 = 1U, /*!< Multiplication factor is 10*/
    PDBDRV_MULT_FACTOR_20 = 2U, /*!< Multiplication factor is 20*/
    PDBDRV_MULT_FACTOR_40 = 3U, /*!< Multiplication factor is 40*/
} PdbDrv_MultFactorType;

/*! \brief PDB type of pre-trigger mode
 */
typedef enum
{
    PDBDRV_PRETRG_DISABLE       = 0U, /*!< PDB Channel Pre-Trigger disable*/
    PDBDRV_PRETRG_BYPASSED_MODE = 1U, /*!< PDB Channel Pre-Trigger bypassed enable*/
    PDBDRV_PRETRG_DELAY_MODE    = 2U, /*!< PDB Channel Pre-Trigger delay enable*/
    PDBDRV_PRETRG_BB_MODE       = 3U, /*!< PDB Channel Pre-Trigger Back-to-Back operation enable*/
} PdbDrv_PreTrgModeType;

/*! \brief Definition of delay count configuration of PDB driver
 */
typedef struct _PdbDrv_DlyCfgType_
{
    uint16_t modCnt;                                         /*!<PDB Modulus*/
    uint16_t idlyCnt;                                        /*!<PDB Interrupt Delay*/
    uint16_t dlyCnt[PDBDRV_CH_NUMBER][PDBDRV_PRE_CH_NUMBER]; /*!<PDB Channel Delay*/
} PdbDrv_DlyCfgType;

/*! \brief Definition of Pulse out configuration of PDB driver
 */
typedef struct _PdbDrv_PoCfgType_
{
    bool     poen[PDBDRV_PO_CH_NUMBER]; /*!<PDB Pulse-Out Enable*/
    uint16_t dly1[PDBDRV_PO_CH_NUMBER]; /*!<PDB Pulse-Out Delay 1*/
    uint16_t dly2[PDBDRV_PO_CH_NUMBER]; /*!<PDB Pulse-Out Delay 2*/
} PdbDrv_PoCfgType;

/*! \brief Definition of configuration of pre-trigger of PDB driver
 */
typedef struct _PdbDrv_PreTrgType_
{
    PdbDrv_PreTrgModeType mode[PDBDRV_CH_NUMBER][PDBDRV_PRE_CH_NUMBER]; /*!<PDB Channel Pre-Trigger mode*/
} PdbDrv_PreTrgType;

/*! \brief Definition of configuration of PDB driver
 */
typedef struct _PdbDrv_ConfigType_
{
    PdbDrv_LdmodType      ldmode;          /*!< Load Mode Select*/
    bool                  pdbeie;          /*!< PDB Sequence Error Interrupt Enable*/
    bool                  dmaen;           /*!< DMA enable*/
    PdbDrv_PrescalerType  prescalerFactor; /*!< Prescaler Divider Select*/
    PdbDrv_TrgselType     trgInSel;        /*!< Trigger Input Source Select*/
    bool                  pdbie;           /*!< PDB Interrupt Enable*/
    PdbDrv_MultFactorType mult;            /*!< Multiplication Factor Select for Pre-scaler*/
    PdbDrv_ContType       cMode;           /*!< Continuous Mode*/
    PdbDrv_DlyCfgType     dlyCfg;          /*!< delay count configuration*/
    PdbDrv_PreTrgType     preTrgCfg;       /*!< Pre-Trigger channel n configuration*/
    PdbDrv_PoCfgType      poCfg;           /*!< Pulse out n configuration*/
    uint8_t               bbSel;           /*!< Selects ADC COCO source as PDB back-to-back mode*/
                                           /* - 000b : PDB0 and PDB1 operates independently.
                                            *           PDB0 CH0 operate with ADC0 COCO[7:0], and PDB1 CH0 operate with ADC1 COCO[7:0]
                                            *  - 001b : Chaining of CH0-CH0 of PDB0 and PDB1.
                                            *           Channel0 of PDB0 and PDB1 back-to-back operation with COCO[7:0] of ADC0 and ADC1
                                            *  - 01xb : Inter channel chaining of PDB0 CH0 and CH1.
                                            *           CH0 and CH1 of PDB0 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC0.
                                            *           PDB1 CH0 back to back operation with ADC1 COCO[7:0]
                                            *  - 10xb : Inter channel chaining of PDB1 CH0 and CH1.
                                            *           CH0 and CH1 of PDB1 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC1.
                                            *           PDB0 CH0 back to back operation with ADC0 COCO[7:0]
                                            *  - 11xb : Inter channel chaining of PDB0 CH0 and CH1 and PDB1 CH0 and CH1 both.
                                            *           CH0 and CH1 of PDB0 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC0,
                                            *           and CH0 and CH1 of PDB1 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC1.
                                            */
} PdbDrv_ConfigType;

/* Forward declaration of PDB register */
struct _PdbRegType_;

/* Forward declaration of SIm register */
struct _SimRegType_;

/*! \brief The definition of PDB driver class
 */
typedef struct _PdbDrvType_
{
    struct _PdbRegType_ *pdbReg;
    struct _SimRegType_ *simReg;
} PdbDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the PDB driver module
 *
 * This function initializes PDB driver by setting the register
 * instance to it.
 *
 * \param[in] obj    : pointer to PDB driver instance
 * \param[in] pdbReg  : pointer to PDB register instance
 * \param[in] simReg  : pointer to SIM register instance
 */
extern void PdbDrv_Init(PdbDrvType *obj, struct _PdbRegType_ *pdbReg, struct _SimRegType_ *simReg);

/*! \brief enable PDB driver
 *
 * This function enable PDB driver.
 *
 * \param[in] obj : pointer to PDB driver instance
 */
extern void PdbDrv_EnablePdb(PdbDrvType *obj);

/*! \brief disbale PDB driver
 *
 * This function disable PDB driver.
 *
 * \param[in] obj : pointer to PDB driver instance
 */
extern void PdbDrv_PdbDisable(PdbDrvType *obj);

/*! \brief  Configures the PDB from a user configuration structure
 *
 * This function configures the PDB from a user configuration structure.
 *
 * \param[in] obj       : pointer to PDB driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void PdbDrv_Configure(PdbDrvType *obj, const PdbDrv_ConfigType *userConfig);

/*! \brief  Get configures of the PDB module currently
 *
 * This function get configures of the PDB module currently.
 *
 * \param[in] obj        : pointer to PDB driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void PdbDrv_GetConfig(const PdbDrvType *obj, PdbDrv_ConfigType *userConfig);

/*! \brief Software trigger for the PDB driver
 *
 * This function software trigger for the PDB driver.
 *
 * \param[in] obj : pointer to PDB driver instance
 */
extern void PdbDrv_SwtrigCmd(PdbDrvType *obj);

/*! \brief Clear PDB interrupt flag for the PDB driver
 *
 * This function clear PDB interrupt flag for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 */
extern void PdbDrv_ClrPdbif(PdbDrvType *obj);

/*! \brief Updates the MOD, IDLY, CHnDLYm, and POyDLY for the PDB driver
 *
 * This function Updates the MOD, IDLY, CHnDLYm, and POyDLY for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 */
extern void PdbDrv_LoadCmd(PdbDrvType *obj);

/*! \brief Get current cnt for the PDB driver
 *
 * This function get current cnt for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 * \return the current PDB current count.
 */
extern uint16_t PdbDrv_GetCnt(const PdbDrvType *obj);

/*! \brief Get current CHn Channel Flags for the PDB driver
 *
 * This function get current CHn Channel Flags for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] chn  : channel number
 *  One bit for each channel state
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * \return the current PDB channel n flags.
 */
extern uint8_t PdbDrv_GetChnCf(const PdbDrvType *obj, PdbDrv_ChType chn);

/*! \brief Clear CHn Channel Flags for the PDB driver
 *
 * This function clear CHn Channel Flags for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] chn  : channel number
 */
extern void PdbDrv_ClrChnCf(PdbDrvType *obj, PdbDrv_ChType chn);

/*! \brief Get PDB Channel Sequence Error Flags for the PDB driver
 *
 * This function get PDB Channel Sequence Error Flags for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] chn  : channel number
 *  One bit for each channel state
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * \return the current PDB channel n sequence error flags.
 */
extern uint8_t PdbDrv_GetChnErr(const PdbDrvType *obj, PdbDrv_ChType chn);

/*! \brief Clear PDB Channel Sequence Error Flags for the PDB driver
 *
 * This function clear PDB Channel Sequence Error Flags for the PDB driver
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] chn  : channel number
 */
extern void PdbDrv_ClrChnErr(PdbDrvType *obj, PdbDrv_ChType chn);

/*! \brief  Configures the delay count of PDB from a user configuration structure
 *
 * This function configures the delay count of PDB from a user configuration structure.
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void PdbDrv_ConfigDly(PdbDrvType *obj, const PdbDrv_DlyCfgType *userConfig);

/*! \brief  Get configures of the PDB delay count currently
 *
 * This function get configures of the PDB delay count currently.
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void PdbDrv_GetConfigDly(const PdbDrvType *obj, PdbDrv_DlyCfgType *userConfig);

/*! \brief  Configures the CHnC1 of PDB from a user configuration structure
 *
 * This function configures the CHnC1 of PDB from a user configuration structure.
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void PdbDrv_ConfigPreTrg(PdbDrvType *obj, const PdbDrv_PreTrgType *userConfig);

/*! \brief  Get configures of the PDB pre-trigger currently
 *
 * This function get configures of the PDB pre-trigger currently.
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void PdbDrv_GetPreTrgCfg(const PdbDrvType *obj, PdbDrv_PreTrgType *userConfig);

/*! \brief  Configures the Pulse out of PDB from a user configuration structure
 *
 * This function configures the Pulse out of PDB from a user configuration structure.
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void PdbDrv_ConfigPo(PdbDrvType *obj, const PdbDrv_PoCfgType *userConfig);

/*! \brief  Get configures of the PDB Pulse out currently
 *
 * This function get configures of the PDB Pulse out currently.
 *
 * \param[in] obj : pointer to PDB driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void PdbDrv_GetConfigPo(const PdbDrvType *obj, PdbDrv_PoCfgType *userConfig);

/*! \brief Get default configures the PDB module for configuration structure
 *
 * This function gets default configures the PDB module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void PdbDrv_GetDefaultConfig(PdbDrv_ConfigType *userConfig);

/*! \brief Set pre-trigger to Back-to-Back operation
 *
 * This function set PDB pre-trigger to Back-to-Back operation.
 *
 * \param[in] obj  : pointer to PDB driver instance
 * \param[in] ch    : PDB channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger back-to-back operation disabled.
 * - 1b: PDB channel's corresponding pre-trigger back-to-back operation enabled.
 * \param[in] value : bb value
 */
extern void PdbDrv_SetChnBbMode(PdbDrvType *obj, PdbDrv_ChType ch, uint8_t value);

/*! \brief  Get Back-to-Back operation configures of PDB
 *
 * This function get Back-to-Back operation configures of PDB.
 *
 * \param[in] obj  : pointer to PDB driver instance
 * \param[in] ch    : PDB channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger back-to-back operation disabled.
 * - 1b: PDB channel's corresponding pre-trigger back-to-back operation enabled.
 * \return the current PDB CHnC1[BB] register configuration.
 */
extern uint8_t PdbDrv_GetChnBbMode(PdbDrvType *obj, PdbDrv_ChType ch);

/*! \brief  Set CHnC1[tos] configuration
 *
 * This function set CHnC1[tos] configuration
 *
 * \param[in] obj  : pointer to PDB driver instance
 * \param[in] ch    : PDB channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger is in bypassed mode. The pre-trigger asserts one peripheral clock cycle after a rising edge
 *       is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * - 1b: PDB channel's corresponding pre-trigger asserts when the counter reaches the channel delay register plus one peripheral clock cycle
 *       after a rising edge is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * \return the current PDB CHnC1[TOS] register configuration.
 */
extern void PdbDrv_SetChnTosMode(PdbDrvType *obj, PdbDrv_ChType ch, uint8_t value);

/*! \brief Get CHnC1[TOS] configuration
 *
 * This function get CHnC1[TOS] configuration
 *
 * \param[in] obj  : pointer to PDB driver instance
 * \param[in] ch    : PDB channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger is in bypassed mode. The pre-trigger asserts one peripheral clock cycle after a rising edge
 *       is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * - 1b: PDB channel's corresponding pre-trigger asserts when the counter reaches the channel delay register plus one peripheral clock cycle
 *       after a rising edge is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * \return the current PDB CHnC1[TOS] register configuration.
 */
extern uint8_t PdbDrv_GetChnTosMode(PdbDrvType *obj, PdbDrv_ChType ch);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _PDB_DRV_H_ */
