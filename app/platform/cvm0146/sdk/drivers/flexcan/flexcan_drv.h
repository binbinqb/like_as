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

#ifndef _FLEXCAN_DRV_H_
#define _FLEXCAN_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the FlexCAN (Flex Controller Area Network) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "flexcan_reg.h"
#include "pcc_reg.h"
#include "scg_reg.h"
#include "sim_reg.h"

/*! \addtogroup flexcan_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Macro for select message buffer data size for CAN message buffer region
 *
 * The size of each message buffer data will affect the total message buffer number
 */
#define FLEXCANDRV_MB_SIZE_BYTE_8           (0)
#define FLEXCANDRV_MB_SIZE_BYTE_16          (1)
#define FLEXCANDRV_MB_SIZE_BYTE_32          (2)
#define FLEXCANDRV_MB_SIZE_BYTE_64          (3)

/*! \brief Macro for message buffer code
 *
 * The code field was located in message buffer and can be accessed by CPU and by FlexCAN
 * module as part of the message buffer matching and arbitration process.
 */
#define FLEXCANDRV_MSG_BUF_CODE_INACTIVE    (0x0U)
#define FLEXCANDRV_MSG_BUF_CODE_RX_ACTIVE   (0x4U)
#define FLEXCANDRV_MSG_BUF_CODE_TX_REQUEST  (0xCU)
#define FLEXCANDRV_MSG_BUF_CODE_TX_INACTIVE (0x8U)
#define FLEXCANDRV_MSG_BUF_CODE_ABORT       (0x9U)
#define FLEXCANDRV_MSG_BUF_CODE_MASK        (0xFU)
#define FLEXCANDRV_MSG_BUF_CODE_SHIFT       (24U)
#define FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM	(128U)

/*! \brief Macro for FlexCan access mode
 *
 * The access mode will affect the some of the FlexCan registers access permission
 */
#define FLEXCANDRV_CAN_ACCESS_MODE_USER     (0)
#define FLEXCANDRV_CAN_ACCESS_MODE_SUP      (1)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
/*! \brief type for data length code (DLC)
 */
typedef enum
{
    DLC_BYTE_0  = 0x00, /*!< 0 byte(s) data length code */
    DLC_BYTE_1  = 0x01, /*!< 1 byte(s) data length code */
    DLC_BYTE_2  = 0x02, /*!< 2 byte(s) data length code */
    DLC_BYTE_3  = 0x03, /*!< 3 byte(s) data length code */
    DLC_BYTE_4  = 0x04, /*!< 4 byte(s) data length code */
    DLC_BYTE_5  = 0x05, /*!< 5 byte(s) data length code */
    DLC_BYTE_6  = 0x06, /*!< 6 byte(s) data length code */
    DLC_BYTE_7  = 0x07, /*!< 7 byte(s) data length code */
    DLC_BYTE_8  = 0x08, /*!< 8 byte(s) data length code */
    DLC_BYTE_12 = 0x09, /*!< 12 byte(s) data length code */
    DLC_BYTE_16 = 0x0A, /*!< 16 byte(s) data length code */
    DLC_BYTE_20 = 0x0B, /*!< 20 byte(s) data length code */
    DLC_BYTE_24 = 0x0C, /*!< 24 byte(s) data length code */
    DLC_BYTE_32 = 0x0D, /*!< 32 byte(s) data length code */
    DLC_BYTE_48 = 0x0E, /*!< 48 byte(s) data length code */
    DLC_BYTE_64 = 0x0F  /*!< 64 byte(s) data length code */
} FlexCanDrv_DLCType;

/*! \brief type for FlexCan clock source
 */
typedef enum
{
    FLEXCANDRV_CLKSRC_OSC    = 0x00, /*!< oscillator clock source */
    FLEXCANDRV_CLKSRC_CHICLK = 0x01  /*!< peripherial clock source */
} FlexCanDrv_ClkSrcType;

/*! \brief type for FlexCan message type
 */
typedef enum
{
    FLEXCANDRV_MSGTYPE_TX, /*!< Tx message type */
    FLEXCANDRV_MSGTYPE_RX  /*!< Rx message type */
} FlexCanDrv_MsgType_t;

/*! \brief type for FlexCan node state type
 */
typedef enum
{
    FLEXCANDRV_NODESTAT_IDLE,         /*!< idle bus state */
    FLEXCANDRV_NODESTAT_RECEIVING,    /*!< receving bus state */
    FLEXCANDRV_NODESTAT_TRANSMITTING, /*!< transmitting bus state*/
} FlexCanDrv_NodeStatType;

/*! \brief type for FlexCan fault confinment state type
 */
typedef enum
{
    FLEXCANDRV_FLTCONFSTS_ERRACTIVE  = 0, /*!< error active state */
    FLEXCANDRV_FLTCONFSTS_ERRPASSIVE = 1, /*!< error passive state */
    FLEXCANDRV_FLTCONFSTS_BUSOFF     = 2, /*!< bus off state */
} FlexCanDrv_FltConfStsType;

/*! \brief the enhance rx fifo interrupt source mask bit
 *
 * This enum indicate the meaning of each bit for interrupt source
 */
typedef enum
{
    FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE  = 1ul << 28, /*!< data available interrupt */
    FLEXCANDRV_ENHANCERXFF_ISR_SRC_WMMIE = 1ul << 29, /*!< watermark indication interrupt */
    FLEXCANDRV_ENHANCERXFF_ISR_SRC_OVFIE = 1ul << 30, /*!< overflow interrupt */
    FLEXCANDRV_ENHANCERXFF_ISR_SRC_UFWIE = 1ul << 31, /*!< underflow interrupt */

} FlexCanDrv_EnhanceRxFFIsrSrcType;

/*! \brief high-resolution timer capture point select
 *
 * This enum indicate high-resolution timer capture point select
 */
typedef enum
{
    FLEXCANDRV_HR_TIMER_CAPTURE_DISABLE = 0u,
    FLEXCANDRV_HR_TIMER_CAPTURE_EOF,
    FLEXCANDRV_HR_TIMER_CAPTURE_SOF,
    FLEXCANDRV_HR_TIMER_CAPTURE_CLASSIC_SOF_FD_RES_BIT
} FlexCanDrv_HRTmrCapturePointSelectType;

/*! \brief Message buffer time stamp base
 *
 * This enum indicate Message buffer time stamp base
 */
typedef enum
{
    FLEXCANDRV_MB_TIMER_BASE_CAN_TMR = 0u,
    FLEXCANDRV_MB_TIMER_BASE_LOW16BIT_HRTMR,
    FLEXCANDRV_MB_TIMER_BASE_UPPER16BIT_HRTMR
} FlexCanDrv_MBTmrBaseSelectType;

/*! \brief Wake up by timeout or match message select
 *
 * This enum indicate Wake up by timeout or match message select
 */
typedef enum
{
    FLEXCANDRV_PN_WKP_EVENT_TIMOUT = 0u,
    FLEXCANDRV_PN_WKP_EVENT_MATCH,
    FLEXCANDRV_PN_WKP_EVENT_ALL
} FlexCanDrv_PnWkpEventType;

/*! \brief Payload Filtering Selection
 *
 *  Selects the level of payload filtering to be applied when FlexCAN is under Pretended Networking mode
 */
typedef enum
{
    FLEXCANDRV_PN_FILTER_SELECT_PLFS00 = 0U, /*!< Match upon a payload contents against an exact target value */
    FLEXCANDRV_PN_FILTER_SELECT_PLFS01,      /*!< Match upon a payload value greater than or equal to a specified target value */
    FLEXCANDRV_PN_FILTER_SELECT_PLFS10,      /*!< Match upon a payload value smaller than or equal to a specified target value */
    FLEXCANDRV_PN_FILTER_SELECT_PLFS11       /*!< Match upon a payload value inside a range, greater than or equal to a specified lower limit, and smaller than or equal to a specified upper limit */
} FlexCanDrv_PnPayloadFilterSelectType;

/*! \brief ID Filtering Selection
 *
 *   Selects the level of ID filtering to be applied when FlexCAN is under Pretended Networking mode
 */
typedef enum
{
    FLEXCANDRV_PN_FILTER_SELECT_IDFS00 = 0U, /*!< Match upon ID contents against an exact target value */
    FLEXCANDRV_PN_FILTER_SELECT_IDFS01,      /*!< Match upon ID value greater than or equal to a specified target value */
    FLEXCANDRV_PN_FILTER_SELECT_IDFS10,      /*!< Match upon ID value smaller than or equal to a specified target value */
    FLEXCANDRV_PN_FILTER_SELECT_IDFS11       /*!< Match upon ID value inside a range, greater than or equal to a specified lower limit, and smaller than or equal to a specified upper limit */
} FlexCanDrv_PnIdFilterSelectType;

typedef enum
{
    FLEXCANDRV_FILTER_ID_ONLY = 0u,  /*!< Message id filter only */
    FLEXCANDRV_FILTER_ID_PAYLOAD,    /*!< Message id filter and payload filter */
    FLEXCANDRV_FILTER_ID_WITH_CNT,   /*!< Message id filter occurring a specified number of times */
    FLEXCANDRV_FILTER_ID_PAYLOAD_CNT /*!< Message id filter and payload filter a specified number of times */
} FlexCanDrv_PnFilterCombinationSelectType;

typedef enum
{
    FLEXCANDRV_ESR_STATUS_BIT1ERR_FAST_MASK = (1UL << 31),
    FLEXCANDRV_ESR_STATUS_BIT0ERR_FAST_MASK = (1UL << 30),
    FLEXCANDRV_ESR_STATUS_CRCERR_FAST_MASK  = (1UL << 28),
    FLEXCANDRV_ESR_STATUS_FRMERR_FAST_MASK  = (1UL << 27),
    FLEXCANDRV_ESR_STATUS_STFERR_FAST_MASK  = (1UL << 26),
    FLEXCANDRV_ESR_STATUS_ERROVR_MASK       = (1UL << 21),
    FLEXCANDRV_ESR_STATUS_ERRINT_FAST_MASK  = (1UL << 20),
    FLEXCANDRV_ESR_STATUS_BOFFDONEINT_MASK  = (1UL << 19),
    FLEXCANDRV_ESR_STATUS_SYNCH_MASK        = (1UL << 18),
    FLEXCANDRV_ESR_STATUS_TWRNINT_MASK      = (1UL << 17),
    FLEXCANDRV_ESR_STATUS_RWRNINT_MASK      = (1UL << 16),
    FLEXCANDRV_ESR_STATUS_BIT1ERR_MASK      = (1UL << 15),
    FLEXCANDRV_ESR_STATUS_BIT0ERR_MASK      = (1UL << 14),
    FLEXCANDRV_ESR_STATUS_ACKERR_MASK       = (1UL << 13),
    FLEXCANDRV_ESR_STATUS_CRCERR_MASK       = (1UL << 12),
    FLEXCANDRV_ESR_STATUS_FRMERR_MASK       = (1UL << 11),
    FLEXCANDRV_ESR_STATUS_STFERR_MASK       = (1UL << 10),
    FLEXCANDRV_ESR_STATUS_TXWRN_MASK        = (1UL << 9),
    FLEXCANDRV_ESR_STATUS_RXWRN_MASK        = (1UL << 8),
    FLEXCANDRV_ESR_STATUS_IDLE_MASK         = (1UL << 7),
    FLEXCANDRV_ESR_STATUS_TX_MASK           = (1UL << 6),
    FLEXCANDRV_ESR_STATUS_FLTCONF_MASK      = (3UL << 5),
    FLEXCANDRV_ESR_STATUS_RX_MASK           = (1UL << 3),
    FLEXCANDRV_ESR_STATUS_BOFFINT_MASK      = (1UL << 2),
    FLEXCANDRV_ESR_STATUS_ERRINT_MASK       = (1UL << 1),
    FLEXCANDRV_ESR_STATUS_WAKINT_MASK       = (1UL << 0),

    FLEXCANDRV_ERR_STATUS_MASK_ALL = 0xFFFFFFFF
} FlexCanDrv_ErrStatusMaskType;

/*! \brief FlexCan message configuration data structure
 *
 * This structure configures the static attributes for a generic CAN message
 */
typedef struct _FlexCanDrv_MsgCfgType_
{
    uint16_t msgBufId;            /*!< Message buffer index to handle this message object */
    uint16_t msgBufLen;           /*!< Defines number of message buffer to handle this specific
                                       message object configuration, if msgBufLen = 1, then only
                                       single message buffer allocated to this message object,
                                       which is also a common use case, if msgBuf > 1, then multiple
                                       message buffer will allocated to this message object, which
                                       will operating as a software message buffer with depth n */
    uint32_t msgId;               /*!< Message ID can be either 11-bit or 29-bit depends on the
                                       configuration of isExtMsgId */
    bool isExtMsgId;              /*!< Select extended message ID (29-bit) or standard message
                                       ID (11-bit) */
    FlexCanDrv_MsgType_t msgType; /*!< Select message type as Tx message or Rx message */
    FlexCanDrv_DLCType   dlc;     /*!< Message data length code */
    bool                 isFd;    /*!< Select message as classic CAN message or flexible data rate
                                       message */
    bool     intEnable;           /*!< Message Tx / Rx complete interrupt enable */
    uint32_t individualMask;      /*!< Rx individual mask for mailbox n */
} FlexCanDrv_MsgCfgType;

/*! \brief FlexCan message object data structure
 *
 * This structure configures the dynamic attributes for a CAN message which can
 * be varied at runtime
 */
typedef struct _FlexCanDrv_MsgObjType_
{
    uint8_t  msgBufId; /*!< Unique ID for message where it located in message buffer */
    uint32_t msgId;    /*!< 11-bit or 29-bit message ID */
    uint8_t  data[64]; /*!< Message data field. Maximum 64 bytes, the valid length was
                            determined by message DLC */
    uint8_t  dlc;      /*!< Message DLC get from the latest received message */
    uint16_t timeStamp;
    uint32_t hrTimeStamp;
} FlexCanDrv_MsgObjType;

/*! \brief FlexCan bit timing configure data structure (CAN / CANFD)
 *
 * This structure configures the CAN / CANFD bit timing parameters
 */
typedef struct _FlexCanDrv_BitTimingType_
{
    uint32_t prescalerDiv;    /*!< Pre-scaler division factor, defines the ratio between CAN module
                                   clock frequency and the serial clock frequency in the data bit
                                   rate portion */
    uint32_t resyncJumpWidth; /*!< Re-sync jump width, the maximum number of time quanta that a bit
                                   time can be changed by one re-synchronization */
    uint32_t propSeg;         /*!< Propagation segment, defines the length of propagation segment in
                                   the bit time  */
    uint32_t phaseSeg1;       /*!< Phase segment 1, defines the length of phase segment 1 in bit time */
    uint32_t phaseSeg2;       /*!< Phase segment 2, defines the length of phase segment 2 in bit time */
} FlexCanDrv_BitTimingType;

/*! \brief The enhance rx fifo filter selection
 *
 * This enum indicate how many type of filter selection for enhance rx fifo
 */
typedef enum
{
    FLEXCANDRV_ENHRXFF_FILTER_SELECT_MASK_FITLER = 0u,
    FLEXCANDRV_ENHRXFF_FILTER_SELECT_RANGE,
    FLEXCANDRV_ENHRXFF_FILTER_SELECT_TWO_FILTER_WITHOUT_MASK,

} FlexCanDrv_EnhanceRxFFFilterSelection;

typedef struct _FlexCanDrv_InitHwParType_
{
    uint8_t canInstanceIdx;
    uint8_t canRamNum; /*!< CAN message buffer RAM number (each RAM block has 512 bytes) */
} FlexCanDrv_InitHwParType;

/*! \brief FlexCan controller (node) configuration data structure
 *
 * This structure configures static attributes for a FlexCAN controller
 */
typedef struct _FlexCanDrv_ControllerCfgType_
{
    FlexCanDrv_ClkSrcType                  clkSrc;               /*!< Select the clock source for CAN module */
    bool                                   fdEnable;             /*!< Flexible data rate enable */
    bool                                   fdISOEnable;          /*!< ISO CAN FD enable */
    bool                                   fifoEnable;           /*!< Legacy Rx FIFO enable */
    bool                                   enhancefifoEnable;    /*!< Enhance Rx FIFO enable */
    bool                                   dmaEnable;            /*!< Rx FIFO DMA enable */
    FlexCanDrv_BitTimingType               bitTiming;            /*!< nominal CAN bit timing struct */
    FlexCanDrv_BitTimingType               fdBitTiming;          /*!< FD CAN bit timing struct */
    uint8_t                                msgBufDataLenSel;     /*!< Message buffer data size selection */
    uint32_t                               rxMBGlobalMask;       /*!< Rx mailbox global mask */
    uint32_t                               rxMB14Mask;           /*!< Rx mailbox 14 mask (only effect in global mask mode) */
    uint32_t                               rxMB15Mask;           /*!< Rx mailbox 15 mask (only effect in global mask mode) */
    uint32_t                               rxFifoGlobalMask;     /*!< Rx fifo global mask */
    bool                                   individualMaskEnable; /*!< Rx individual mask enable */
    bool                                   loopbackEnable;       /*!< Loopback mode enable */
    bool                                   listenMode;
    bool                                   tdcEnable;        /*!< Transceiver delay compensation enable */
    uint8_t                                tdcOffset;        /*!< Transceiver delay compensation offset */
    uint8_t                                msgNum;           /*!< number of messages */
    const FlexCanDrv_MsgCfgType           *msgCfg;           /*!< message configuration array */
    bool                                   edgeWkupEnable;   /*!< CAN edge wakeup enable */
    bool                                   txAbortEnable;    /*!< Tx pending message abort mechanism enable */
    bool                                   busoffIntEnable;  /*!< Busoff interrupt enable */
    bool                                   errorIntEnable;   /*!< Error interrupt enable */
    bool                                   warningIntEnable; /*!< tx&rx warning interrupt enable */
    FlexCanDrv_EnhanceRxFFFilterSelection  enhRxFFFilterSelection;
    bool                                   freeRunningTmrClockedByExtTmrEn; /*!< Free running timer clocked by external time tick or not */
    FlexCanDrv_HRTmrCapturePointSelectType hrTmrCapturePointSelect;
    FlexCanDrv_MBTmrBaseSelectType         mbTmrBaseSelect;
    bool                                   selected3bitSampling;

    bool                                     pnModeEn;
    FlexCanDrv_PnWkpEventType                pnWkpEvent;
    uint8_t                                  pnMatchNum;
    FlexCanDrv_PnPayloadFilterSelectType     pnPolayFilterSelect;
    FlexCanDrv_PnIdFilterSelectType          pnIdFilterSelect;
    FlexCanDrv_PnFilterCombinationSelectType pnFilterCombinationSelect;
    uint16_t                                 pnNoMsgTimeoutCnt;
    uint32_t                                 pnFilterId1;
    uint32_t                                 pnMaskId1;
    uint8_t                                  pnDlcFilter;
    uint8_t                                  pnPayloadFilterData[8];
    uint8_t                                  pnPayloadMaskData[8];
} FlexCanDrv_ControllerCfgType;

/*! \brief FlexCan error states data structure
 *
 * This structure indicating the error states for a FlexCAN controller
 */
typedef struct _FlexCanDrv_ErrStatusType_
{
    FlexCanDrv_FltConfStsType fltConfSts;   /*!< fault confinement state */
    uint8_t                   bit1FastErr;  /*!< bit 1 error in FD message data phase */
    uint8_t                   bit0FastErr;  /*!< bit 0 error in FD message data phase */
    uint8_t                   crcFastErr;   /*!< crc error in FD message data phase */
    uint8_t                   formFastErr;  /*!< form error in FD message data phase */
    uint8_t                   stuffFastErr; /*!< stuff error in FD message data phase */
    uint8_t                   bit1Err;      /*!< bit 1 error */
    uint8_t                   bit0Err;      /*!< bit 0 error */
    uint8_t                   ackErr;       /*!< acknowledgement error */
    uint8_t                   crcErr;       /*!< crc error */
    uint8_t                   formErr;      /*!< form error */
    uint8_t                   stuffErr;     /*!< stuff error */
    uint8_t                   errOvr;
    uint8_t                   busOffDoneInt;
    uint8_t                   errFastInt;
    uint8_t                   synch;
    uint8_t                   txWarnintInt;
    uint8_t                   rxWarningInt;
    uint8_t                   txWarning;
    uint8_t                   rxWarning;
    uint8_t                   busOffInt;
    uint8_t                   errInt;
    uint8_t                   wakeUpInt;
} FlexCanDrv_ErrStatusType;

struct _FlexCanRegType_;

typedef struct _FlexCanDrvType_
{
    FlexCanRegType          *flexCanReg;
    PccRegType              *pccReg;
    ScgRegType              *scgReg;
    SimRegType              *simReg;
    FlexCanDrv_InitHwParType initHwPar;
    /* BCM CAN-05: per-instance bounded configuration, see patches documentation. */
    bool (*waitExpired)(void *context);
    void *waitContext;
    bool waitFailed;
} FlexCanDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the flexCan driver module
 *
 * This function initializes flexCan driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to FlexCan driver instance
 * \param[in] reg : pointer to FlexCan register instance
 * \param[in] initHwPar: pointer to FlexCan hardware init parameter struct
 */
extern void FlexCanDrv_Init(FlexCanDrvType           *obj,
                            struct _FlexCanRegType_  *flexCanReg,
                            struct _PccRegType_      *pccReg,
                            struct _ScgRegType_      *scgReg,
                            struct _SimRegType_      *simReg,
                            FlexCanDrv_InitHwParType *initHwPar);
/*! \brief Soft reset FlexCAN module
 *
 * This function issues a softreset to FlexCAN module
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 */
extern void FlexCanDrv_SoftReset(FlexCanDrvType *obj);

/*! \brief Start FlexCAN module
 *
 * This function starts the specified FlexCAN device
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 */
extern void FlexCanDrv_Start(FlexCanDrvType *obj);

/*! \brief Configure and initialize FlexCAN controller from user configuration
 *
 * This function configure and initialize the FlexCAN controller from user
 * configuration, it also init FlexCAN RAM area, disable FlexCAN RAM ECC feature
 * and enable the entire FlexCAN module
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] controllerCfg : pointer to FlexCAN controller configuration structure
 */
extern void FlexCanDrv_Configure(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg);

/**
 * @brief 项目扩展：按调用方提供的总截止时间配置控制器。
 * @param[in,out] obj 已由 FlexCanDrv_Init 绑定的对象；同一对象不可并发调用。
 * @param[in] controllerCfg 有效配置，不得为空。
 * @param[in] expired 非阻塞截止判断，不得为空；true 表示预算耗尽。
 * @param[in] context 回调上下文，至少存活到本函数返回；可为空。
 * @return true 表示全部配置完成；false 表示参数错误或握手超时。
 * @post 返回前解除回调绑定；失败后不继续配置，硬件状态须由上层恢复。
 * @note 原 SDK 的 void 接口保持签名；HAL 必须使用本扩展。
 */
extern bool FlexCanDrv_ConfigureBounded(FlexCanDrvType *obj,
                                       const FlexCanDrv_ControllerCfgType *controllerCfg,
                                       bool (*expired)(void *context), void *context);


/*! \brief Configure message object and register the specified CAN message buffer
 *
 * This function configure and initialize the CAN message object for its' message ID
 * direction, DLC, FD properties and message buffer interrupt enable. All the above
 * configuration will be stored in the specified message buffer located in CAN RAM
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgCfg : pointer to message object configuration
 * \param[in] msgBufId : message buffer index to store the message object
 */
extern void FlexCanDrv_CfgMsgObj(FlexCanDrvType *obj, const FlexCanDrv_MsgCfgType *msgCfg, uint8_t msgBufId);

/*! \brief Transmit the message unconditionally once
 *
 * This function transmit message unconditionally once by the set the CODE in CS field,
 * this operation shall be performed after message object initialized in message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : message buffer object pointer
 */
extern void FlexCanDrv_TransmitMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

/*! \brief Set the transmit message object into message buffer
 *
 * This function load the transmit message object into message buffer data field, the data byte order
 * will be re-odered to adapt the message buffer data field format. The data length to load
 * will retrieved from the DLC stored in the specified message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : message buffer object pointer
 */
extern void FlexCanDrv_SetTxMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

/*! \brief Get the message object from message buffer
 *
 * This function load the message buffer received data and DLC into message object data buffer.
 * The data length to load will retrieved from the DLC stored in the specified message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : message buffer object pointer
 */
extern void FlexCanDrv_GetRxMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

/*! \brief Get the message object from Rx FIFO
 *
 * This function load the Rx FIFO received data and DLC into message object data buffer.
 * The data length to load will retrieved from the DLC stored in the specified message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : message buffer object pointer
 */
extern void FlexCanDrv_GetRxFifoMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

/*! \brief Get message object flag, indicating a successful Rx / Tx operation completed
 *
 * This function returns the flag to indicating a successful Rx / Tx operation completed.
 * A clear operation need to be done once the flag is asserted.
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgBufferIdx : message buffer index
 * \return message buffer Tx / Rx operation complete flag
 *             - 0: the corresponding buffer has no occurrence of successfully
 *                  completed transmission or reception
 *             - 1: the corresponding buffer has successfully completed transmission
 *                  or reception
 */
extern uint8_t FlexCanDrv_GetMsgObjFlag(FlexCanDrvType *obj, uint8_t msgBufferIdx);

/*! \brief Get the message object from Rx FIFO
 *
 * This function load the Rx FIFO received data and DLC into message object data buffer.
 * The data length to load will retrieved from the DLC stored in the specified message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : message buffer object pointer
 */
extern void FlexCanDrv_GetRxFifoMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

/*! \brief Clear message object flag
 *
 * This function clear the correspongding message object flag
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : message buffer index
 */
extern void FlexCanDrv_ClearMsgObjFlag(FlexCanDrvType *obj, uint8_t msgBufferIdx);

/*! \brief Clear all message object flags
 *
 * This function clear all message object flags
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 */
extern void FlexCanDrv_ClearAllMsgObjFlags(FlexCanDrvType *obj);

/*! \brief Enable interrupt for the corresponding message buffer
 *
 * This function enable interrupt for the corresponding message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgBufferIdx : message buffer index
 */
extern void FlexCanDrv_EnableMsgObjInterrupt(FlexCanDrvType *obj, uint8_t msgBufferIdx);

/*! \brief Disable interrupt for the corresponding message buffer
 *
 * This function disable interrupt for the corresponding message buffer
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgBufferIdx : message buffer index
 */
extern void FlexCanDrv_DisableMsgObjInterrupt(FlexCanDrvType *obj, uint8_t msgBufferIdx);

/*! \brief Get the default FlexCan controller configuration parameters
 *
 * This function get the default FlexCan controller configuration parameters
 *
 * \param[in] controllerCfg : controller configure pointer
 */
extern void FlexCanDrv_GetDefaultCfg(FlexCanDrv_ControllerCfgType *controllerCfg);

/*! \brief Calculate the CAN bit timing parameters
 *
 * This function calculate the CAN bit timing parameters for both classic and FD CAN
 *
 * \param[out] bitTimingPara : pointer to bit timing parameter group
 * \param[in]  clkFreq       : FlexCan module frequency
 * \param[in]  samplePoint   : Can bit sample point (0 - 10000 -> 0 - 100%)
 * \param[in]  sjw           : Synchronize jump width (0 - 10000 -> 0 - 100%)
 * \param[in]  isFd          : Is the bit timing parameter group for CAN-FD
 */
extern void FlexCanDrv_BitTimingCalc(FlexCanDrv_BitTimingType *bitTimingPara,
                                     uint32_t                  clkFreq,
                                     uint32_t                  baudrate,
                                     uint16_t                  samplePoint,
                                     uint16_t                  sjw,
                                     uint8_t                   isFd);

/*! \brief Get FlexCan error states
 *
 * This function get the FlexCan error states
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \return : node status
 *
 */
extern FlexCanDrv_NodeStatType FlexCanDrv_GetNodeStatus(FlexCanDrvType *obj);

/*! \brief Get FlexCan error states
 *
 * This function get the FlexCan error states
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[out] errSts: pointer to FlexCan error states
 *
 */
extern void FlexCanDrv_GetErrorStatusFlag(FlexCanDrvType *obj, FlexCanDrv_ErrStatusType *errSts);

/*! \brief Clear bus off flag
 *
 * This function Clear bus off flag
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] errMask : err state bit mask combination  (FlexCanDrv_ErrStatusMaskType)
 *
 */
extern void FlexCanDrv_ClearErrStatusFlag(FlexCanDrvType *obj, uint32_t errMask);

/*! \brief Abort pending Tx message
 *
 * This function abort the pending Tx message, before transmitting it , reconfigure the tx mail-box again!!!
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj: message buffer object pointer
 * \return Pending Tx message abort result
 *         - 0: no Tx message transfer pending
 *         - 1: pending Tx message abort success
 *
 */
extern uint8_t FlexCanDrv_AbortPendingTxMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

/*! \brief Set enhance rx fifo water mark
 *
 * This function Set enhance rx fifo water mark
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] waterMark: the value of water mark
 * \return void
 *
 */
extern void FlexCanDrv_SetEnhanceRxFFWaterMark(FlexCanDrvType *obj, uint8_t waterMark);

/*! \brief Set enhance rx interrupt request
 *
 * This function Set enhance rx interrupt request
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] isrSrcMask: the combine of interrupt source
 * \param[in] enabled: disable or enable these interrupt req
 * \return void
 *
 */
extern void FlexCanDrv_SetEnhanceRxFFIsr(FlexCanDrvType *obj, uint32_t isrSrcMask, bool enabled);

/*! \brief Clear enhance rx interrupt flag
 *
 * This function Clear enhance rx interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] isrSrcMask: the combine of interrupt source
 * \return void
 *
 */
extern void FlexCanDrv_ClearEnhanceRxFFIsrFlag(FlexCanDrvType *obj, uint32_t isrSrcMask);

/*! \brief Clear enhance rx interrupt flag
 *
 * This function Clear enhance rx interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] isrSrc: the interrupt source
 * \return void
 *
 */
extern bool FlexCanDrv_GetEnhanceRxFFIsrFlag(FlexCanDrvType *obj, FlexCanDrv_EnhanceRxFFIsrSrcType isrSrc);

/*! \brief Get the enhance rx fifo is empyt or not
 *
 * This function  Get the enhance rx fifo is empyt or not
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \return rx ff is empty or not
 *               true: rx ff is empty
 *               false: rx ff is not empyt
 *
 */
extern bool FlexCanDrv_GetEnhanceRxFFIsEmpty(FlexCanDrvType *obj);

/*! \brief Get the enhance rx fifo is full or not
 *
 * This function  Get the enhance rx fifo is full or not
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \return rx ff is empty or not
 *               true: rx ff is full
 *               false: rx ff is not full
 *
 */
extern bool FlexCanDrv_GetEnhanceRxFFIsFull(FlexCanDrvType *obj);

/*! \brief Get the number of message stored in the enhance rx fifo
 *
 * This function Get the number of message stored in the enhance rx fifo
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \return the number of message stored in the enhance rx fifo
 *
 */
extern uint8_t FlexCanDrv_GetEnhanceRxFFMsgNums(FlexCanDrvType *obj);

/*! \brief Get the received message from enhance rx fifo
 *
 * This function Get the received message from enhance rx fifo
 *
 * \param[in] obj : pointer to FlexCAN driver instance
 * \param[in] msgObj : pointer to stored the received message buffer
 * \return void
 *
 */
extern void FlexCanDrv_GetEnhanceRxFifoMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* #ifndef _FLEXCAN_DRV_H_ */
