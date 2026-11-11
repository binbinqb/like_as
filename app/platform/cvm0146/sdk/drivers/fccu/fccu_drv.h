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

#ifndef _FCCU_DRV_H_
#define _FCCU_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of FCCU
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup fccu_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* FCCU Transient unlock key, 0xA4 unlock, others value lock */
#define FCCUDRV_TRANS_UNLOCK_KEY      (0xA4)

/* FCCU Permanent unlock key, 0x68 lock, others value unlock */
#define FCCUDRV_PERMNT_LOCK_KEY       (0x68)

/* FCCU FCCU_FST unlock key, 0x66EAABF3 unlock, others value lock */
#define FCCUDRV_FST_UNLOCK_KEY        (0x66EAABF3)

/* FCCU CONFIG Timeout Irq clear mask */
#define FCCUDRV_CONFIG_IRQ_CLEAR_MASK (0x1)

/* FCCU ALARM Status Interrupt clear */
#define FCCUDRV_ALARM_STS_CLEAR       (0x1)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Fccu error injection channel num
 */
typedef enum
{
    FCCUDRV_ERR_CH0_PMC_LVW                 = 0x00U, /*!< fccu error injection channel 0 HPBG low voltage warning                           */
    FCCUDRV_ERR_CH1_PMC_LVD                 = 0x01U, /*!< fccu error injection channel 1 HPBG low voltage detect                            */
    FCCUDRV_ERR_CH2_PMC_OVD                 = 0x02U, /*!< fccu error injection channel 2 HPBG over voltage detect                           */
    FCCUDRV_ERR_CH3_PMC_OVD_VDD11           = 0x03U, /*!< fccu error injection channel 3 HPBG VDD11 over voltage detect                     */
    FCCUDRV_ERR_CH4_PMC_FLDO_LVD            = 0x04U, /*!< fccu error injection channel 4 FLASH low voltage detect                           */
    FCCUDRV_ERR_CH5_PMC_LPBG_LVD            = 0x05U, /*!< fccu error injection channel 5 LPBG low voltage detect                            */
    FCCUDRV_ERR_CH6_PMC_LPBG_OVD            = 0x06U, /*!< fccu error injection channel 5 LPBG over voltage detect                           */
    FCCUDRV_ERR_CH7_FLT_SRAML_SBC           = 0x07U, /*!< fccu error injection channel 7 SRAML access single bit correction error           */
    FCCUDRV_ERR_CH8_FLT_SRAML_NCE           = 0x08U, /*!< fccu error injection channel 8 SRAML access multi bits non-correction error       */
    FCCUDRV_ERR_CH9_FLT_SRAMU_SBC           = 0x09U, /*!< fccu error injection channel 9 SRAMU access single bit correction error           */
    FCCUDRV_ERR_CH10_FLT_SRAMU_NCE          = 0x0AU, /*!< fccu error injection channel 10 SRAMU access multi bits non-correction error      */
    FCCUDRV_ERR_CH11_FLT_FLASH_SBC          = 0x0BU, /*!< fccu error injection channel 11 FLASH access single bit correction error          */
    FCCUDRV_ERR_CH12_FLT_FLASH_NCE          = 0x0CU, /*!< fccu error injection channel 12 FLASH access multi bits non-correction error      */
    FCCUDRV_ERR_CH13_FLT_CACHE_SBC          = 0x0DU, /*!< fccu error injection channel 13 CACHE access single bit correction error          */
    FCCUDRV_ERR_CH14_FLT_CACHE_NCE          = 0x0EU, /*!< fccu error injection channel 14 CACHE access multi bits non-correction error      */
    FCCUDRV_ERR_CH15_FLT_ERR_IN             = 0x0FU, /*!< fccu error injection channel 15 extern error injection                            */
    FCCUDRV_ERR_CH16_E2E_MSTR0_CACHE        = 0x10U, /*!< fccu error injection channel 16 E2E matser0 cache                                 */
    FCCUDRV_ERR_CH17_E2E_MSTR1_CPU_SYS      = 0x11U, /*!< fccu error injection channel 17 E2E matser1 CPU system                            */
    FCCUDRV_ERR_CH18_E2E_MSTR2_DMA          = 0x12U, /*!< fccu error injection channel 18 E2E matser2 DMA                                   */
    FCCUDRV_ERR_CH19_E2E_MSTR3_CSE          = 0x13U, /*!< fccu error injection channel 19 E2E matser3 CSE                                   */
    FCCUDRV_ERR_CH20_E2E_AIPS1_FLS_ADDR     = 0x14U, /*!< fccu error injection channel 20 E2E slave0 FLASH                                  */
    FCCUDRV_ERR_CH21_E2E_AIPS1_FLS_WDATA    = 0x15U, /*!< fccu error injection channel 21 E2E slave1 SRAM                                   */
    FCCUDRV_ERR_CH22_E2E_AIPS2_SRAM_ADDR    = 0x16U, /*!< fccu error injection channel 22 E2E slave2 AIPS0                                  */
    FCCUDRV_ERR_CH23_E2E_AIPS2_SRAM_WDATA   = 0x17U, /*!< fccu error injection channel 23 E2E slave3 AIPS1                                  */
    FCCUDRV_ERR_CH24_E2E_AIPS0_GPIO_ADDR    = 0x18U, /*!< fccu error injection channel 24 E2E slave4 AIPS2                                  */
    FCCUDRV_ERR_CH25_E2E_AIPS0_GPIO_WDATA   = 0x19U, /*!< fccu error injection channel 25 E2E slave5 GPIO                                   */
    FCCUDRV_ERR_CH26_HPBG_OTP               = 0x1AU, /*!< fccu error injection channel 26 temperature exception                             */
    FCCUDRV_ERR_CHx_TOTAL_NUM               = 0x1BU  /*!< fccu error injection channel total num                                            */
} FccuDrv_ChnNumType;

/*! \brief OP unlock key
 */
typedef enum
{
    FCCUDRV_UNLOCK_KEY_OP1 = 0x2505D287, /*!< option control unlock OP1 */
    FCCUDRV_UNLOCK_KEY_OP2 = 0x0E1147D7  /*!< option control unlock OP2 */
} FccuDrv_OpUnlockType;

/*! \brief OP select
 */
typedef enum
{
    FCCUDRV_SEL_CTRL_OP0  = 0x00U, /*!< option control flow, none to do                                                 */
    FCCUDRV_SEL_CTRL_OP1  = 0x01U, /*!< option control flow, FSM status change from NORMAL to CONFIG                    */
    FCCUDRV_SEL_CTRL_OP2  = 0x02U, /*!< option control flow, FSM status change from CONFIG to NORMAL                    */
    FCCUDRV_SEL_CTRL_OP12 = 0x0CU, /*!< option control flow, softtware recover FCCU_FST, trigger by hardware            */
    FCCUDRV_SEL_CTRL_OP13 = 0x0DU, /*!< option control flow, clear all status change register                           */
    FCCUDRV_SEL_CTRL_OP14 = 0x0EU, /*!< option control flow, FSM status change from CONFIG to ALARM, trigger by timeout */
    FCCUDRV_SEL_CTRL_OP15 = 0x0FU  /*!< option control flow, trigger FCCU_OP_STAT back to idle                          */
} FccuDrv_OpSelType;

/*! \brief OP status
 */
typedef enum
{
    FCCUDRV_OP_IDLE     = 0, /*!< fccu OP status idle     */
    FCCUDRV_OP_EXCUTING = 1, /*!< fccu OP status excuting */
    FCCUDRV_OP_ABORT    = 2, /*!< fccu OP status abort    */
    FCCUDRV_OP_SUCCESS  = 3, /*!< fccu OP status success  */
} FccuDrv_OpStatusType;

/*! \brief Config register status
 */
typedef enum
{
    FCCUDRV_CONFIG_STATUS_LOCK   = 0, /*!< fccu CONFIG register status on unlock */
    FCCUDRV_CONFIG_STATUS_UNLOCK = 1, /*!< fccu CONFIG register status on lock   */
} FccuDrv_ConfigRegStatusType;

/*! \brief Config fake in status
 */
typedef enum
{
    FCCUDRV_FAKE_NONE = 0, /*!< fccu Error fake none */
    FCCUDRV_FAKE_IN   = 1, /*!< fccu Error fake in  */
} FccuDrv_FakeStatusType;

/*! \brief Config error inject fault type
 */
typedef enum
{
    FCCUDRV_ERR_INJECT_CRITICAL      = 0, /*!< fccu Error Injection fault type critical */
    FCCUDRV_ERR_INJECT_NON_CRITICAL  = 1, /*!< fccu Error Injection fault type non-critical  */
} FccuDrv_ErrInFaultType;

/*! \brief FSM(finite status machine) status
 */
typedef enum
{
    FCCUDRV_FSM_NORMAL = 0, /*!< fccu FSM on normal status */
    FCCUDRV_FSM_CONFIG = 1, /*!< fccu FSM on config status */
    FCCUDRV_FSM_ALARM  = 2, /*!< fccu FSM on alarm status  */
    FCCUDRV_FSM_FAULT  = 3, /*!< fccu FSM on fault status  */
} FccuDrv_FsmStatusType;

/*! \brief EOut Permanent status level polarity
 */
typedef enum
{
    FCCUDRV_EOUT_PS_POL_LOW  = 0, /*!< EOut level status is low  */
    FCCUDRV_EOUT_PS_POL_HIGH = 1  /*!< EOut level status is high */
} FccuDrv_EOutPsStatusType;

/*! \brief EOut level polarity
 */
typedef enum
{
    FCCUDRV_EOUT_PAD_DISABLE = 0, /*!< EOut out to pad disable */
    FCCUDRV_EOUT_PAD_ENABLE  = 1  /*!< EOut out to pad enable  */
} FccuDrv_EOutPadStatusType;

/*! \brief EOut self-loop pad Test
 */
typedef enum
{
    FCCUDRV_EOUT_TST_DISABLE = 0, /*!< EOut out to self-loop pad disable */
    FCCUDRV_EOUT_TST_ENABLE  = 1  /*!< EOut out to self-loop pad enable  */
} FccuDrv_EOutTstStatusType;

/* Forward declaration of related register */
struct _FccuRegType_;

/*! \brief The definition of Fccu driver class
 */
typedef struct _FccuDrvType_
{
    struct _FccuRegType_ *regFccu; /*!< pointer to FCCU register */
    struct _SimRegType_  *regSim;  /*!< pointer to SIM register */
} FccuDrvType;

/*! \brief Option control element
 */
typedef struct _FccuDrv_OptCtrlType_
{
    FccuDrv_OpUnlockType opUnlock;  /*!< option control unlock  */
    FccuDrv_OpSelType    opCtrlSel; /*!< option control select  */
    FccuDrv_OpStatusType opStatus;  /*!< OP current status get */
} FccuDrv_OptCtrlType;

/*! \brief EOut control element
 */
typedef struct _FccuDrv_EOutCtrlType_
{
    uint16_t                  eoutPwmFreq;     /*!< EOut PWM frequency set                  */
    FccuDrv_EOutPsStatusType  eoutPsStatus;    /*!< EOut Permanent level status             */
    FccuDrv_EOutPadStatusType eoutPadEnable;   /*!< EOut pad out status                     */
    uint8_t                   eoutTstEnable;   /*!< EOut self-loop test enable>             */
    uint32_t                  eoutMinHoldTime; /*!< FSM on fault status, Eout min hold time */
} FccuDrv_EOutCtrlType;

/*! \brief error injection for all channel control
 */
typedef struct _FccuDrv_ChnCtrlType_
{
    uint32_t chnRstEn;       /*!< Exception for reset on all channel               */
    uint32_t chnAlarmIrqEn;  /*!< Exception for interrupt request on all channel   */
    uint32_t chnNmiEn;       /*!< Exception for none mask interrupt on all channel */
    uint32_t chnEOutEn;      /*!< Exception for eout on all channel                */
    uint32_t chnErrInEn;     /*!< All channel error injection enable               */
    uint32_t chnErrTypeSet;  /*!< All channel error type config,
                                  critical(FAULT) of non-critical(ALARM)           */
} FccuDrv_ChnCtrlType;

/*! \brief FSM status change record
 */
typedef struct _FccuDrv_FsmStausChgRecdType_
{
    uint32_t fsmNormalToAlarmSrc; /*!< FSM change from Normal to Alarm cause record            */
    uint32_t fsmAlarmToFaultSrc0; /*!< FSM change from Alarm to Fault cause by timeout record  */
    uint32_t fsmAlarmToFaultSrc1; /*!< FSM change from Alarm to Fault cause by critical record */
    uint32_t fsmNormalToFaultSrc; /*!< FSM change from Normal to Fault cause record            */
    uint32_t fsmFaultToAlarmSrc;  /*!< FSM change from Fault to Alarm cause record             */
} FccuDrv_FsmStausChgRecordType;

/*! \brief interrupt status get
 */
typedef struct _FccuDrv_irqStatusdType_
{
    bool irqNmiStatus;    /*!< FSM on fault status, NMI Irq status      */
    bool irqAlarmStatus;  /*!< FSM on alarm status, alram Irq status    */
    bool irqConfigStatus; /*!< FSM on config status, config Irq status  */
} FccuDrv_irqStatusdType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the FCCU driver module
 *
 * This function initializes FCCU driver by setting the register
 * instances to it.
 *
 * \param[in] this : pointer to FCCU driver instance
 * \param[in] fccuReg : pointer to FCCU register instance
 * \param[in] simReg : pointer to SIM register instance
 */
extern void FccuDrv_Init(FccuDrvType *obj, struct _FccuRegType_ *fccuReg, struct _SimRegType_ *simReg);

/*! \brief Set Option Flow1.
 *
 * This function set option flow for fsm transform
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return none
 * \note: unlock and set option flow is atom operation
 */
extern void FccuDrv_SetOptFlowNormal2Config(FccuDrvType *obj);

/*! \brief Set Option Flow2.
 *
 * This function set option flow for fsm transform
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return none
 * \note: unlock and set option flow is atom operation
 */
extern void FccuDrv_SetOptFlowConfig2Normal(FccuDrvType *obj);

/*! \brief Set Option Flow13.
 *
 * This function set option flow for debug register clear
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return none
 * \note: unlock and set option flow is atom operation
 */
extern void FccuDrv_ClrDbgStatusRcd(FccuDrvType *obj);

/*! \brief Set Option Flow15.
 *
 * This function set operation status return to idle. 
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return none
 * \note: unlock and set option flow is atom operation
 */
extern void FccuDrv_OpBackToIdle(FccuDrvType *obj);

/*! \brief Set CONFIG mode timeout enable
 *
 * This function set CONFIG mode timeout enable or not
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] enable :
 *             - true  : enable
 *             - false : disable
 */
extern void FccuDrv_SetConfigTimeoutIrqMode(FccuDrvType *obj, bool enable);

/*! \brief Get CONFIG mode timeout enable
 *
 * This function get CONFIG mode timeout enable or not
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *             - true  : enable
 *             - false : disable
 */
extern bool FccuDrv_GetConfigTimeoutIrqMode(FccuDrvType *obj);

/*! \brief Set Debug mode enable
 *
 * This function set debug mode enable or not,
 * if debug mode enable, on debug mode timer will work on
 * else timer stop work
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] enable :
 *             - true  : enable
 *             - false : disable
 */
extern void FccuDrv_SetDebugMode(FccuDrvType *obj, bool enable);

/*! \brief Get Debug mode enable
 *
 * This function get debug mode enable or not,
 * if debug mode enable, on debug mode timer will work on
 * else timer stop work
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *             - true  : enable
 *             - false : disable
 */
extern bool FccuDrv_GetDebugMode(FccuDrvType *obj);

/*! \brief Set Option Control Flow
 *
 * This function set FCCU work flow, selcet different
 * option will excute corresponding flow.
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] opType :
 *             - FCCUDRV_SEL_CTRL_OP0  : none to do
 *             - FCCUDRV_SEL_CTRL_OP1  : FSM status change from NORMAL to CONFIG
 *             - FCCUDRV_SEL_CTRL_OP2  : FSM status change from CONFIG to NORMAL
 *             - FCCUDRV_SEL_CTRL_OP12 : softtware recover FCCU_FST, trigger by hardware
 *             - FCCUDRV_SEL_CTRL_OP13 : clear all status change register
 *             - FCCUDRV_SEL_CTRL_OP14 : FSM status change from CONFIG to ALARM, trigger by timeout
 *             - FCCUDRV_SEL_CTRL_OP15 : Option status back to idle
 */
extern bool FccuDrv_SetOpCtrl(FccuDrvType *obj, FccuDrv_OpSelType opType);

/*! \brief Get Option Control Flow
 *
 * This function get FCCU work flow, selcet different
 * option will excute corresponding flow.
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return :
 *             - FCCUDRV_SEL_CTRL_OP0  : none to do
 *             - FCCUDRV_SEL_CTRL_OP1  : FSM status change from NORMAL to CONFIG
 *             - FCCUDRV_SEL_CTRL_OP2  : FSM status change from CONFIG to NORMAL
 *             - FCCUDRV_SEL_CTRL_OP12 : softtware recover FCCU_FST, trigger by hardware
 *             - FCCUDRV_SEL_CTRL_OP13 : clear all status change register
 *             - FCCUDRV_SEL_CTRL_OP14 : FSM status change from CONFIG to ALARM, trigger by timeout
 *             - FCCUDRV_SEL_CTRL_OP15 : Option status back to idle
 */
extern FccuDrv_OpSelType FcccDrv_GetOpCtrl(FccuDrvType *obj);

/*! \brief Get Option Status
 *
 * This function get FCCU Option status
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return :
 *             - FCCUDRV_OP_IDLE     : OP status idle
 *             - FCCUDRV_OP_EXCUTING : OP status excuting
 *             - FCCUDRV_OP_ABORT    : OP status abort
 *             - FCCUDRV_OP_SUCCESS  : OP status success
 */
extern FccuDrv_OpStatusType FccuDrv_GetOpStatus(FccuDrvType *obj);

/*! \brief Set Transinet lock
 *
 * This function set CONFIG register lock mode
 * for transient lock status
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern void FccuDrv_SetTransLock(FccuDrvType *obj);

/*! \brief Set Transinet unlock
 *
 * This function set CONFIG register unlock mode
 * for transient unlock status
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern void FccuDrv_SetTransUnlock(FccuDrvType *obj);

/*! \brief Set Permanent lock
 *
 * This function set CONFIG register lock mode
 * for permanent lock status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \note: unlock only by MCU reset
 */
extern void FccuDrv_SetPermntLock(FccuDrvType *obj);

/*! \brief Set FSM Enter CONFIG mode
 *
 * This function set FSM on CONFIG mode,
 * channel config register only in this mode can RW
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern bool FccuDrv_EnterConfigMode(FccuDrvType *obj);

/*! \brief Set FSM Exit CONFIG mode
 *
 * This function set FSM on NORMAL mode,
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern bool FccuDrv_ExitConfigMode(FccuDrvType *obj);

/*! \brief Set EOut config
 *
 * This function set EOut config parameters
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] eoutCtrl : EOut parameters, polarity, out enable,
 *                       pwm frequency, hold time.
 */
extern void FccuDrv_SetEOutConfig(FccuDrvType *obj, FccuDrv_EOutCtrlType *eoutCtrl);

/*! \brief Get EOut config
 *
 * This function get EOut config parameters
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *          EOut parameters, polarity, out enable,
 *          pwm frequency, hold time.
 */
extern void FccuDrv_GetEOutConfig(FccuDrvType *obj, FccuDrv_EOutCtrlType *eoutCtrl);

/*! \brief Set channel config
 *
 * This function set channel config parameters
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] chnCtrl : channel control parameters, rst, alarm, nmi,
 *                      eout, error injection, error type.
 */
extern void FccuDrv_SetChnConfig(FccuDrvType *obj, FccuDrv_ChnCtrlType *chnCtrl);

/*! \brief Get channel config
 *
 * This function get channel config parameters
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *          channel control parameters, rst, alarm, nmi,
 *           eout, error injection, error type.
 */
extern void FccuDrv_GetChnConfig(FccuDrvType *obj, FccuDrv_ChnCtrlType *chnCtrl);

/*! \brief Set channel fake in config
 *
 * This function set channel config parameters
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *          channel control parameters fake in.
 */
void FccuDrv_SetChnFakeIn(FccuDrvType *obj, uint32_t fakeIn);

/*! \brief Get channel fake in config
 *
 * This function get channel config parameters
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *          channel control parameters fake in.
 */
uint32_t FccuDrv_GetChnFakeIn(FccuDrvType *obj);

/*! \brief Set Alarm timeout threshold
 *
 * This function set alarm status timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] timeCnt : timer ccount
 */
extern void FccuDrv_SetAlarmModeTimeoutThreshold(FccuDrvType *obj, uint32_t timeCnt);

/*! \brief Get Alarm timeout threshold
 *
 * This function get alarm status timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 *
 * \return
 *          timer ccount
 */
extern uint32_t FccuDrv_GetAlarmModeTimeoutThreshold(FccuDrvType *obj);

/*! \brief Set CONOFIG mode timeout threshold
 *
 * This function set CONFIG mode status timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] timeCnt : timer ccount
 */
extern void FccuDrv_SetConfigModeTimeoutThreshold(FccuDrvType *obj, uint8_t timeCnt);

/*! \brief Get CONOFIG mode timeout threshold
 *
 * This function get CONFIG mode status timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \return
 *          timer ccount
 */
extern uint8_t FccuDrv_GetConfigModeTimeoutThreshold(FccuDrvType *obj);

/*! \brief Get FSM status change record
 *
 * This function get FSM status convert record
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] fsmChgRecord :
 *              FSM convert from NORMAL to ALARM Source
 *              FSM convert from ALARM to FALUT Source0
 *              FSM convert from NORMAL to FALUT Source1
 *              FSM convert from NORMAL to FALUT Source
 *              FSM convert from FALUT to ALARM Source
 */
extern void FccuDrv_GetFsmStatusChangeRecord(FccuDrvType *obj, FccuDrv_FsmStausChgRecordType *fsmChgRecord);

/*! \brief Get Channel Error status
 *
 * This function get channel error status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \return
 *          bit[x] : 0 current channel normal
 *          bit[x] : 1 current channel fault occur
 *          x : channel 0 ~ 15
 */
extern uint32_t FccuDrv_GetChnStatus(FccuDrvType *obj);

/*! \brief Get Channel Error status
 *
 * This function get channel error status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] chnClrMask :
 *          bit[x] : 0 current channel ignore
 *          bit[x] : 1 current channel clear
 *          x : channel 0 ~ 15
 */
extern void FccuDrv_SetChnErrorStatusClear(FccuDrvType *obj, uint32_t chnClrMask);

/*! \brief Get Channel Config Register status
 *
 * This function get channel config register status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \return
 *         0 : unlock
 *         1 : lcok
 */
extern FccuDrv_ConfigRegStatusType FccuDrv_GetConfigRegLockStatus(FccuDrvType *obj);

/*! \brief Get Channel Error Injection status
 *
 * This function get channel error injection status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \return
 *         0 : fault
 *         1 : normal
 */
extern FccuDrv_FakeStatusType FccuDrv_GetErrInjectStatus(FccuDrvType *obj);

/*! \brief Get FSM status
 *
 * This function get FSM status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \return
 *         0 : FSM NORMAL
 *         1 : FSM NORMAL
 *         2 : FSM ALARM
 *         3 : FSM FAULT
 */
extern FccuDrv_FsmStatusType FccuDrv_GetFsmStatus(FccuDrvType *obj);

/*! \brief Get Irq status
 *
 * This function get Irq status
 *
 * \param[in] obj : pointer to FCCU driver instance
 * \param[in] irqStatus : Config Irq, Alarm Irq, NMI Irq
 */
extern void FccuDrv_GetIrqStatus(FccuDrvType *obj, FccuDrv_irqStatusdType *irqStatus);

/*! \brief Clear Alarm Irq status
 *
 * This function clear alarm irq status
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern void FccuDrv_AlarmIrqStatusClr(FccuDrvType *obj);

/*! \brief Clear Config Irq status
 *
 * This function clear config status
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern void FccuDrv_ClrConfigTimeoutStatus(FccuDrvType *obj);

/*! \brief Get Alarm Timer Count value
 *
 * This function get FSM on Alarm mode, timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern uint32_t FccuDrv_GetFsmAlarmTmrValue(FccuDrvType *obj);

/*! \brief Get CONFIG Timer Count value
 *
 * This function get FSM on CONFIG mode, timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern uint32_t FccuDrv_GetFsmConfigTmrValue(FccuDrvType *obj);

/*! \brief Get EOut Timer Count value
 *
 * This function get EOut mode, timer count
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern uint32_t FccuDrv_GetEOutTmrValue(FccuDrvType *obj);

/*! \brief Set FCCU to initial status
 *
 * This function set FSM to initial mode Normal Mode
 *
 * \param[in] obj : pointer to FCCU driver instance
 */
extern bool FccuDrv_InitialToNormal(FccuDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _FCCU_DRV_H_ */
