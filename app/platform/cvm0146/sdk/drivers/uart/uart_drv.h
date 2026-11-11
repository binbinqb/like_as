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

#ifndef _UARTDRV_DRV_H_
#define _UARTDRV_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of UART module
 */

/******************************************************************************
 * the includes
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "uart_reg.h"

/*! \addtogroup uart_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * the defines
 *****************************************************************************/

#define UARTDRV_BRR_LOW_4BITS_MASK (0x0000000Fu)
#define UARTDRV_READ_DATA_INVALID  (0xFFFFul)
#define UARTDRV_BRAUD_RATE_INVALID (0xFFFFFFFF)

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/*! \brief Word length */
typedef enum
{
    UARTDRV_DATA_BITS_NUM_8 = 0x00u, /*!< 1 Start bit, 8 data bits, n stop bits */
    UARTDRV_DATA_BITS_NUM_9          /*!< 1 Start bit, 9 data bits, n stop bits */
} UartDrv_DataBitsNumType;

/*! \brief stop bits setting */
typedef enum
{
    UARTDRV_STOP_BITS_NUM_1 = 0x00u, /*!< 1 stop bit */
    UARTDRV_STOP_BITS_NUM_2          /*!< 2 stop bits */
} UartDrv_StopBitsNumType;

/*! \brief transfer data bit sequeue */
typedef enum
{
    UARTDRV_DATA_SHIFT_DIRECTION_LSB = 0x00u, /*!< data is transmitted/received with data bit 0 first, following the start bit. */
    UARTDRV_DATA_SHIFT_DIRECTION_MSB          /*!< data is transmitted/received with the MSB (bit 7/8/9) first, following the start bit.  */
} UartDrv_DataShiftDirectionType;

/*! \brief parity selection */
typedef enum
{
    UARTDRV_PARITY_SELECT_EVEN = 0x00u, /*!< Even parity */
    UARTDRV_PARITY_SELECT_ODD,          /*!< Odd parity */
    UARTDRV_PARITY_SELECT_UNUSED        /*!< Parity check feature is not used */
} UartDrv_ParitySelectionType;

/*! \brief Transfer mode usage */
typedef enum
{
    UARTDRV_DATA_TRANSFER_TX_RX_DIS = 0x00u, /*!< Transfer is not in tx&rx */
    UARTDRV_DATA_TRANSFER_TX_ONLY,           /*!< Transfer is in tx */
    UARTDRV_DATA_TRANSFER_RX_ONLY,           /*!< Transfer is in rx*/
    UARTDRV_DATA_TRANSFER_TX_RX_EN           /*!< Transfer is in rx&tx */
} UartDrv_DataTransferDirectType;

/*! \brief Idle character nums */
typedef enum
{
    UARTDRV_IDLE_CHAR_NUM_1 = 0x00u, /*!< 1 idle character */
    UARTDRV_IDLE_CHAR_NUM_2,         /*!< 2 idle character */
    UARTDRV_IDLE_CHAR_NUM_4,         /*!< 4 idle character */
    UARTDRV_IDLE_CHAR_NUM_8,         /*!< 8 idle character */
    UARTDRV_IDLE_CHAR_NUM_16,        /*!< 16 idle character */
    UARTDRV_IDLE_CHAR_NUM_32,        /*!< 32 idle character */
    UARTDRV_IDLE_CHAR_NUM_64,        /*!< 64 idle character */
    UARTDRV_IDLE_CHAR_NUM_128        /*!< 128 idle character */
} UartDrv_IdleCharNumsType;

/*! \brief wakeup source selection */
typedef enum
{
    UARTDRV_WAKE_SOURCE_IDLE_LINE = 0x00u, /*!< Idle line */
    UARTDRV_WAKE_SOURCE_ADDRESS_MARK       /*!< Address mark */
} UartDrv_WakeSourceType;

/*! \brief Oversampling mode */
typedef enum
{
    UARTDRV_ONE_SAMPLE_BIT_METHOD_IN_3BITS = 0u, /*!< Three sample bit method  */
    UARTDRV_ONE_SAMPLE_BIT_METHOD_IN_1BITS       /*!< One sample bit method */
} UartDrv_OneSampleBitMethod;

/*! \brief oversampling mode */
typedef enum
{
    UARTDRV_OVERSAMPLING_MODE_BY_16 = 0x00u, /*!< Oversampling by 16 */
    UARTDRV_OVERSAMPLING_MODE_BY_8           /*!< Oversampling by 8 */
} UartDrv_OverSamplingModeType;

/*! \brief Dma selection */
typedef enum
{
    UARTDRV_DMA_SELECTION_TX_RX_DIS = 0x00u, /*!< DMA mode is disabled for tx&rx */
    UARTDRV_DMA_SELECTION_TX_EN_RX_DIS,      /*!< DMA mode is enabled for tx */
    UARTDRV_DMA_SELECTION_TX_DIS_RX_EN,      /*!< DMA mode is enabled for rx */
    UARTDRV_DMA_SELECTION_TX_EN_RX_EN        /*!< DMA mode is enabled for tx&rx */
} UartDrv_DmaSelectionType;

/*! \brief Auto baudrate detect mode */
typedef enum
{
    UARTDRV_AUTO_BAUDRATE_MODE_0 = 0x00u, /*!< Measurement of the start bit is used to detect the baud rate */
    UARTDRV_AUTO_BAUDRATE_MODE_1,         /*!< Falling edge to falling edge measurement */
    UARTDRV_AUTO_BAUDRATE_MODE_2,         /*!< 0x7F frame detection */
    UARTDRV_AUTO_BAUDRATE_MODE_3,         /*!< 0x55 frame detection */
} UartDrv_AutoBaudRateModeType;

/*! \brief 7-bit Address Detection/4-bit Address Detection */
typedef enum
{
    UARTDRV_ADDR_DETECTION_MODE_LOW_4BITS = 0x00u, /*!< 4-bit address detection */
    UARTDRV_ADDR_DETECTION_MODE_ALL_BITS           /*!< 7-bit address detection (in 8-bit data mode) */
} UartDrv_AddrDetectionModeType;

/*! \brief Send the bits of the sync break signal(Low level) */
typedef enum
{
    UARTDRV_BREAK_FIELD_SYNC_BREAK_TX_BITS_NUM_13 = 0x00u, /*!< - 13 bits */
    UARTDRV_BREAK_FIELD_SYNC_BREAK_TX_BITS_NUM_14,         /*!< - 14 bits */
    UARTDRV_BREAK_FIELD_SYNC_BREAK_TX_BITS_NUM_15          /*!< - 15 bits */
} UartDrv_BreakFieldSyncBreakTxBitsNumType;

/*! \brief Send the bits of the delimiter (High level) */
typedef enum
{
    UARTDRV_BREAK_FIELD_DELIMITER_TX_BITS_NUM_1 = 0x00u, /*!<- 1 bits */
    UARTDRV_BREAK_FIELD_DELIMITER_TX_BITS_NUM_2          /*!< - 2 bits */
} UartDrv_BreakFieldDelimiterTxBitsNumType;

/*! \brief LIN synch break detect length: */
typedef enum
{
    UARTDRV_LIN_SYNC_BREAK_RX_BITS_NUM_11 = 0x00u, /*!< - 11 bits */
    UARTDRV_LIN_SYNC_BREAK_RX_BITS_NUM_12,         /*!< - 12 bits */
    UARTDRV_LIN_SYNC_BREAK_RX_BITS_NUM_13          /*!< - 13 bits */
} UartDrv_LinSyncBreakRxBitsNumType;

typedef enum
{
    UARTDRV_COSPLAY_UART = 0x00u,
    UARTDRV_COSPLAY_LIN,
    UARTDRV_COSPLAY_RS232,
    UARTDRV_COSPLAY_RS485
} UartDrv_Cosplay;

/*! \brief Interrupt source */
typedef enum
{
    UARTDRV_ISR_SRC_TX_OVERFLOW   = 0x01ul,
    UARTDRV_ISR_SRC_TX_EMPTY      = 0x02ul,
    UARTDRV_ISR_SRC_TX_COMPLETE   = 0x04ul,
    UARTDRV_ISR_SRC_TX_SYNC_BREAK = 0x08ul,

    UARTDRV_ISR_SRC_RX_UNDERFLOW  = 0x10ul,
    UARTDRV_ISR_SRC_RX_FULL       = 0x20ul,
    UARTDRV_ISR_SRC_RX_TIMEOUT    = 0x40ul,
    UARTDRV_ISR_SRC_RX_SYNC_BREAK = 0x80ul,
    UARTDRV_ISR_SRC_RX_IDLE       = 0x100ul,
    UARTDRV_ISR_SRC_RX_CTS        = 0x200ul,

    UARTDRV_ISR_SRC_ERR_PARITY         = 0x400ul,
    UARTDRV_ISR_SRC_ERR_FRAME          = 0x800ul,
    UARTDRV_ISR_SRC_ERR_NOISE          = 0x1000ul,
    UARTDRV_ISR_SRC_ERR_OVER_RUN       = 0x2000ul,
    UARTDRV_ISR_SRC_ERR_ABRE_LBDT_FAIL = 0x4000ul,
    UARTDRV_ISR_SRC_ERR_ALL            = 0x8000ul,

    UARTDRV_ISR_SRC_ALL = 0xFFFFFFFF
} UartDrv_IsrSrcType;

/*! \brief Status flag */
typedef enum
{
    UARTDRV_STATUS_PE        = 0x01ul,
    UARTDRV_STATUS_FE        = 0x02ul,
    UARTDRV_STATUS_NF        = 0x04ul,
    UARTDRV_STATUS_ORE       = 0x08ul,
    UARTDRV_STATUS_IDLE      = 0x10ul,
    UARTDRV_STATUS_RDRF      = 0x20ul,
    UARTDRV_STATUS_TC        = 0x40ul,
    UARTDRV_STATUS_TDRE      = 0x80ul,
    UARTDRV_STATUS_LBDT_DONE = 0x100ul,
    UARTDRV_STATUS_CTSIF     = 0x200ul,
    UARTDRV_STATUS_CTS       = 0x400ul,
    UARTDRV_STATUS_RTOF      = 0x800ul,
    UARTDRV_STATUS_RXUF      = 0x1000ul,
    UARTDRV_STATUS_TXOF      = 0x2000ul,
    UARTDRV_STATUS_ABRE      = 0x4000ul,
    UARTDRV_STATUS_ABRF      = 0x8000ul,
    UARTDRV_STATUS_BUSY      = 0x10000ul,
    UARTDRV_STATUS_LBDT_FAIL = 0x20000ul,
    UARTDRV_STATUS_SBRKD     = 0x40000ul,
    UARTDRV_STATUS_ISR_ALL   = 0xFFFFCFFF,
    UARTDRV_STATUS_RWU       = 0x80000ul,
    UARTDRV_STATUS_TX_EMPTY  = 0x100000ul,
    UARTDRV_STATUS_RX_EMPTY  = 0x200000ul
} UartDrv_StatusType;

/*! \brief Basic parameters for the basic features */
typedef struct _UartDrv_BasicParametersType_
{
    uint32_t                       busClockFreq;
    uint32_t                       baudRate;
    UartDrv_DataBitsNumType        dataBitsNum;
    UartDrv_StopBitsNumType        stopBitsNum;
    UartDrv_DataShiftDirectionType dataShiftDirection;
    UartDrv_ParitySelectionType    paritySelection;
    UartDrv_OneSampleBitMethod     oneSampleBitMethod;
    UartDrv_OverSamplingModeType   overSamplingMode;
    UartDrv_DataTransferDirectType dataTransferDirect;
} UartDrv_BasicParametersType;

/*! \brief advanced parameters for the advance features if used */
typedef struct _UartDrv_ExtendParametersType_
{
    UartDrv_AutoBaudRateModeType             autoBaudRateMode;
    UartDrv_DmaSelectionType                 dmaSelection;
    UartDrv_AddrDetectionModeType            addrDetectMode;
    UartDrv_WakeSourceType                   wakeSrc;
    UartDrv_BreakFieldSyncBreakTxBitsNumType breakFieldSyncBreakTxBitsNum;
    UartDrv_BreakFieldDelimiterTxBitsNumType breakFieldDelimiterTxBitsNum;
    UartDrv_LinSyncBreakRxBitsNumType        syncBreakRxBitsNum;
    UartDrv_IdleCharNumsType                 idleCharNums;
    uint32_t                                 rxTimeoutBitsCnt;
    uint8_t                                  addrMarkDetectValue;
    uint8_t                                  driverEnDeassertionTime;
    uint8_t                                  driverEnAssertionTime;
    bool                                     driverEnablePolarityActiveInLow;
    uint8_t                                  linBaudrateRxTimeoutBitsNum;
} UartDrv_ExtendParametersType;

/*! \brief advance features if wanted to be used */
typedef struct _UartDrv_ExtendFeaturesType_
{
    bool            dmaEn;
    bool            autoBaudRateDetectionEn;
    bool            rxInvertEn;
    bool            txInvertEn;
    bool            dataInvertEn;
    bool            loopEn;
    bool            wakeUpEn;
    bool            linBaudrateAutoDetectEn;
    bool            linBreakDetectEn;
    UartDrv_Cosplay cosplayer;
} UartDrv_ExtendFeaturesType;

/*! \brief the initial configuration if used to be set */
typedef struct _UartDrv_InitCfgType_
{
    UartDrv_BasicParametersType  basicParameters;
    UartDrv_ExtendParametersType extendParameters;
    UartDrv_ExtendFeaturesType   extendFeatures;
} UartDrv_InitCfgType;

/*! \brief uart instance pointer */
typedef struct _UartDrvType_
{
    UartRegType *reg;
} UartDrvType;

/******************************************************************************
 * the globals
 ******************************************************************************/

/******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Get default configures the UART module for configuration structure
 *
 * This function gets default configures the UART module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 * \return:  void
 */
extern void UartDrv_GetDefaultConfig(UartDrv_InitCfgType *pInitCfg);

/*! \brief Set the config for the uart module
 *
 * this function initializes the run-time state structure to provide for module configuration
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] pInitCfg :the pointer to the user configuration
 * \return:  void
 */
extern void UartDrv_SetConfig(UartDrvType *obj, const UartDrv_InitCfgType *pInitCfg);

/*! \brief Enable or disable the uart module
 *
 * This function enables or disables the uart module
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isEnable:
 *            0: UART disabled
 *            1: UART enabled
 * \return: void
 */
extern void UartDrv_EnableModule(UartDrvType *obj, bool isEnable);

/*! \brief Get received data number in Rx FIFO
 *
 * This function gets received data number in Rx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 * \return : data counter in Rx FIFO
 */
extern uint8_t UartDrv_GetRxCounter(const UartDrvType *obj);

/*! \brief Get wait to transmit data number in Tx FIFO
 *
 * This function gets wait to transmit data number in Tx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 * \return : data counter in Tx FIFO
 */
extern uint8_t UartDrv_GetTxCounter(const UartDrvType *obj);

/*! \brief clear all data of Tx FIFO
 *
 * This function clears all data of Tx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 */
extern void UartDrv_ClearTxFifo(const UartDrvType *obj);

/*! \brief clear all data of Rx FIFO
 *
 * This function clears all data of Rx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 */
extern void UartDrv_ClearRxFifo(const UartDrvType *obj);

/*! \brief Set the threshold value of Rx FIFO
 *
 * This function sets the threshold value of Rx FIFO
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txWater : threshold value (range 0 to 3)
 * \return : void
 */
extern void UartDrv_SetRxWater(const UartDrvType *obj, uint8_t rxWater);

/*! \brief Set the threshold value of Tx FIFO
 *
 * This function sets the threshold value of Tx FIFO
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txWater : threshold value (range 0 to 3)
 * \return : void
 */
extern void UartDrv_SetTxWater(const UartDrvType *obj, uint8_t txWater);

/*! \brief Send lin sync break field
 *
 * This function sends lin sync break field
 *
 * \param[in] obj : pointer to UART driver instance
 * \return : void
 */
extern void UartDrv_SendLinBreakField(const UartDrvType *obj);

/*! \brief Enable or disable the Line break detect
 *
 * This function enables or disables the Line break detect
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isEnable:
 *            0: Line break detect disable
 *            1: Line break detect enable
 * \return: void
 */
extern void UartDrv_EnableLineBreakDetect(const UartDrvType *obj, bool isEnable);

/*! \brief Set Auto baud rate enable or disable
 *
 *  this function enable auto baudrate features
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Auto baud rate detection is disabled.
 *            1: Auto baud rate detection is enabled.
 * \return: void
 */
extern void UartDrv_EnableAutoBaudrateFeature(const UartDrvType *obj, bool enable);

/*! \brief Initializes the UART driver module
 *
 * This function initializes UART driver by setting the register instance to it.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] reg : pointer to UART register instance
 * \return:  void
 */
extern void UartDrv_Init(UartDrvType *obj, UartRegType *pReg);

/*! \brief DeInit the uart module to default
 *
 * Call back in the usage of low power or sleep requirements
 *
 * \param[in] obj :pointer to UART driver instance
 * \return:  void
 */
extern void UartDrv_DeInit(UartDrvType *obj);

/*! \brief Read out from the rx buffer to the specific address and indicated how
 *
 * this function read out received datas from rx fifo
 *
 * \param[in] obj : pointer to UART driver instance
 * \return:  uint16_t :
 *           read-out value , if PE or FE or NF, return UARTDRV_READ_DATA_INVALID
 */
extern uint16_t UartDrv_RxData(const UartDrvType *obj);

/*! \brief Transmit one data
 *
 * This function write one data to tx fifo
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] txDatabuf : the copy of data to be sent
 * \return: void
 */
extern void UartDrv_TxData(UartDrvType *obj, uint16_t txDatabuf);

/*! \brief Read out the current status flag
 *
 * This function get the expected status
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] status : which status want to get
 * \return None
 *     - FALSE:
 *     - TRUE: some event happend
 */
extern bool UartDrv_GetStatus(const UartDrvType *obj, UartDrv_StatusType status);

/*! \brief Clear the expected status
 *
 * This function clear the special status , can be conbination with more than one status
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] status : can used the combination of the UartDrv_IsrStatusIdxType
 *              to clear more than one bit interrupt flag;
 *              for example: if want to clear PE&FE: (UARTDRV_STATUS_RXUF | UARTDRV_STATUS_STATUS_PE)
 * \return: void
 */
extern void UartDrv_ClearStatus(UartDrvType *obj, uint32_t status);

/*! \brief Enable or Disable one or more than one interrupt source
 *
 * This function set the interrupt request action if condition matched
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isrSrc : can used the more than one interrupt source once
 * \param[in] isrEn : True(Enable) or false(Disable)
 * \return: void
 */
extern void UartDrv_SetInterruptReq(UartDrvType *obj, uint32_t isrSrc, bool isrEn);

/*! \brief Get one interrupt source is enable or disable
 *
 * This function gets one interrupt source is enable or disable
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isrType :one interrupt source type
 * \return: True(Enable) or false(Disable)
 */
extern bool UartDrv_IsInterruptEnabled(UartDrvType *obj, UartDrv_IsrSrcType isrType);


#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif
