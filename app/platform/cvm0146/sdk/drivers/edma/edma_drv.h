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

#ifndef _DMA_DRV_H_
#define _DMA_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the DMA (Direct Memory Access) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "edma_reg.h"

/*! \addtogroup edma_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Macro for the memory size needed for the software TCD.
 *
 * Software TCD is aligned to 32 bytes. We don't need a software TCD structure for the first
 * descriptor, since the configuration is pushed directly to registers.
 * To make sure the software TCD can meet the eDMA module requirement regarding alignment,
 * allocate memory for the remaining descriptors with extra 31 bytes.
 */
#define STCD_SIZE(number)  (((number)*32U) - 1U)
#define STCD_ADDR(address) (((uint32_t)address + 31UL) & ~0x1FUL)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
/*! \brief Status return codes.
 * Common error codes will be a unified enumeration (C enum) that will contain all error codes
 * (common and specific). There will be separate "error values spaces" (or slots), each of 256
 * positions, allocated per functionality.
 */
typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS     = 0x000U, /*!< Generic operation success status */
    STATUS_ERROR       = 0x001U, /*!< Generic operation failure status */
    STATUS_BUSY        = 0x002U, /*!< Generic operation busy status */
    STATUS_TIMEOUT     = 0x003U, /*!< Generic operation timeout status */
    STATUS_UNSUPPORTED = 0x004U, /*!< Generic operation unsupported status */
} EDmaDrv_Status;

/*! \brief eDMA channel priority setting
 */
typedef enum
{
    EDMADRV_CHN_PRIORITY_0 = 0U,
    EDMADRV_CHN_PRIORITY_1 = 1U,
    EDMADRV_CHN_PRIORITY_2 = 2U,
    EDMADRV_CHN_PRIORITY_3 = 3U,
#ifndef FEATURE_DMA_4_CH_PRIORITIES
    EDMADRV_CHN_PRIORITY_4 = 4U,
    EDMADRV_CHN_PRIORITY_5 = 5U,
    EDMADRV_CHN_PRIORITY_6 = 6U,
    EDMADRV_CHN_PRIORITY_7 = 7U,
#ifndef FEATURE_DMA_8_CH_PRIORITIES
    EDMADRV_CHN_PRIORITY_8  = 8U,
    EDMADRV_CHN_PRIORITY_9  = 9U,
    EDMADRV_CHN_PRIORITY_10 = 10U,
    EDMADRV_CHN_PRIORITY_11 = 11U,
    EDMADRV_CHN_PRIORITY_12 = 12U,
    EDMADRV_CHN_PRIORITY_13 = 13U,
    EDMADRV_CHN_PRIORITY_14 = 14U,
    EDMADRV_CHN_PRIORITY_15 = 15U,
#endif
#endif
    EDMADRV_CHN_DEFAULT_PRIORITY = 255U
} EDmaDrv_ChannelPriorityType;

/*! \brief eDMA channel interrupts.
 */
typedef enum
{
    EDMADRV_CHN_ERR_INT = 0U,        /*!< Error interrupt */
    EDMADRV_CHN_HALF_MAJOR_LOOP_INT, /*!< Half major loop interrupt. */
    EDMADRV_CHN_MAJOR_LOOP_INT       /*!< Complete major loop interrupt. */
} EDmaDrv_ChannelInterruptType;

/*! \brief eDMA channel arbitration mode used for selection among channels.
 */
typedef enum
{
    EDMADRV_ARBITRATION_FIXED_PRIORITY = 0U, /*!< Fixed Priority */
    EDMADRV_ARBITRATION_ROUND_ROBIN          /*!< Round-Robin arbitration */
} EDmaDrv_ArbitrationModeType;

/*! \brief eDMA modulo configuration
 */
typedef enum
{
    EDMADRV_MODULO_OFF = 0U,
    EDMADRV_MODULO_2B,
    EDMADRV_MODULO_4B,
    EDMADRV_MODULO_8B,
    EDMADRV_MODULO_16B,
    EDMADRV_MODULO_32B,
    EDMADRV_MODULO_64B,
    EDMADRV_MODULO_128B,
    EDMADRV_MODULO_256B,
    EDMADRV_MODULO_512B,
    EDMADRV_MODULO_1KB,
    EDMADRV_MODULO_2KB,
    EDMADRV_MODULO_4KB
} EDmaDrv_ModuloType;

/*! \brief eDMA transfer configuration
 */
typedef enum
{
    EDMADRV_TRANSFER_SIZE_1B  = 0x0U,
    EDMADRV_TRANSFER_SIZE_2B  = 0x1U,
    EDMADRV_TRANSFER_SIZE_4B  = 0x2U,
    EDMADRV_TRANSFER_SIZE_16B = 0x4U,
    EDMADRV_TRANSFER_SIZE_32B = 0x5U
} EDmaDrv_TransferSizeType;

/*! \brief eDMA loop transfer configuration.
 *
 * This structure configures the basic minor/major loop attributes.
 */
typedef struct _EDmaDrv_LoopTransferConfigType_
{
    uint32_t majorLoopIterationCount; /*!< Number of major loop iterations. */
    bool srcOffsetEnable;             /*!< Selects whether the minor loop offset is applied to the
                                           source address upon minor loop completion. */
    bool dstOffsetEnable;             /*!< Selects whether the minor loop offset is applied to the
                                           destination address upon minor loop completion. */
    int32_t minorLoopOffset;          /*!< Sign-extended offset applied to the source or destination address
                                           to form the next-state value after the minor loop completes. */
    bool minorLoopChnLinkEnable;      /*!< Enables channel-to-channel linking on minor loop complete. */
    uint8_t minorLoopChnLinkNumber;   /*!< The number of the next channel to be started by DMA
                                           engine when minor loop completes. */
    bool majorLoopChnLinkEnable;      /*!< Enables channel-to-channel linking on major loop complete. */
    uint8_t majorLoopChnLinkNumber;   /*!< The number of the next channel to be started by DMA
                                           engine when major loop completes. */
} EDmaDrv_LoopTransferConfigType;

/*! \brief eDMA transfer size configuration.
 *
 * This structure configures the basic source/destination transfer attribute.
 */
typedef struct _EDmaDrv_TransferConfigType_
{
    uint32_t srcAddr;                                   /*!< Memory address pointing to the source data. */
    uint32_t destAddr;                                  /*!< Memory address pointing to the destination data. */
    EDmaDrv_TransferSizeType srcDestTransferSize;       /*!< Source/Destination data transfer size. */
    int16_t srcOffset;                                  /*!< Sign-extended offset applied to the current source address
                                                             to form the next-state value as each source read/write
                                                             is completed. */
    int16_t destOffset;                                 /*!< Sign-extended offset applied to the current destination
                                                             address to form the next-state value as each source
                                                             read/write is completed. */
    int32_t srcLastAddrAdjust;                          /*!< Last source address adjustment. */
    int32_t destLastAddrAdjust;                         /*!< Last destination address adjustment. Note here it is only
                                                             valid when scatter/gather feature is not enabled. */
    EDmaDrv_ModuloType srcModulo;                       /*!< Source address modulo. */
    EDmaDrv_ModuloType destModulo;                      /*!< Destination address modulo. */
    uint32_t minorByteTransferCount;                    /*!< Number of bytes to be transferred in each service request
                                                             of the channel. */
    bool scatterGatherEnable;                           /*!< Enable scatter gather feature. */
    uint32_t scatterGatherNextDescAddr;                 /*!< The address of the next descriptor to be used, when
                                                             scatter/gather feature is enabled.
                                                             Note: this value is not used when scatter/gather
                                                                   feature is disabled. */
    bool interruptEnable;                               /*!< Enable the interrupt request when the major loop
                                                             count completes */
    bool hardClrDone;                                   /*!< Enable Hard clear Done*/
    EDmaDrv_LoopTransferConfigType *loopTransferConfig; /*!< Pointer to loop transfer configuration structure
                                                          (defines minor/major loop attributes)
                                                          Note: this field is only used when minor loop mapping is
                                                                enabled from DMA configuration. */
} EDmaDrv_TransferConfigType;

typedef struct _EDmaDrv_SoftwareTcdType_
{
    uint32_t SADDR;
    int16_t SOFF;
    uint16_t ATTR;
    uint32_t NBYTES;
    int32_t SLAST;
    uint32_t DADDR;
    int16_t DOFF;
    uint16_t CITER;
    int32_t DLAST_SGA;
    uint16_t CSR;
    uint16_t BITER;
} EDmaDrv_SoftwareTcdType;

/*! \brief The user configuration structure for the eDMA driver.
 *
 * Use an instance of this structure with the EDmaDrv_Init() function. This allows the user to configure
 * settings of the EDMA peripheral with a single function call.
 */
typedef struct _EDmaDrv_UserConfigType_
{
    EDmaDrv_ChannelPriorityType channelPriority[EDMA_CHANNELS_INTERRUPT_LINES];
    EDmaDrv_ArbitrationModeType chnArbitration; /*!< eDMA channel arbitration. */
    bool haltOnError;                           /*!< Any error causes the HALT bit to set. Subsequently, all
                                                   service requests are ignored until the HALT bit is cleared. */
} EDmaDrv_ModuleConfigType;

/*! \brief Channel status for eDMA channel.
 *
 * A structure describing the eDMA channel status. The user can get the status by callback parameter
 * or by calling EDmaDrv_getStatus() function.
 */
typedef enum
{
    DMA_CHN_NORMAL = 0U, /*!< eDMA channel normal state. */
    DMA_CHN_ERROR        /*!< An error occurred in the eDMA channel. */
} EDmaDrv_ChnStatusType;

/*! \brief Definition for the eDMA channel callback function.
 *
 * Prototype for the callback function registered in the eDMA driver.
 */
typedef void (*EDmaDrv_CallBackType)(void *parameter, EDmaDrv_ChnStatusType status);

/*! \brief Data structure for the eDMA channel state.
 */
typedef struct _DmaDrv_ChnStateType_
{
    uint8_t chn;                           /*!< Channel number. */
    EDmaDrv_CallBackType callback;         /*!< Callback function pointer for the eDMA channel. It will
                                        be called at the eDMA channel complete and eDMA channel
                                        error. */
    void *parameter;                       /*!< Parameter for the callback function pointer. */
    volatile EDmaDrv_ChnStatusType status; /*!< eDMA channel status. */
} EDmaDrv_ChnStateType;

/*! \brief Runtime state structure for the eDMA driver.
 *
 * This structure holds data that is used by the eDMA peripheral driver to manage
 * multi eDMA channels.
 * The user passes the memory for this run-time state structure and the eDMA
 * driver populates the members.
 */
typedef struct _EDmaDrv_StateType_
{
    EDmaDrv_ChnStateType *volatile chnState[(uint32_t)EDMA_CHANNELS]; /*!< Pointer array storing channel state. */
} EDmaDrv_StateType;

/*! \brief Definition of configuration of Dma driver
 */
typedef struct _EDmaDrv_ChannelConfigType_
{
    uint8_t chnConfig;                           /*!< eDMA channel number */
    EDmaDrv_ChannelPriorityType channelPriority; /*!< eDMA channel priority - only used when channel
                                                arbitration mode is 'Fixed priority'. */
    EDma_RequestSourceType source;               /*!< Selects the source of the DMA request for this channel */
    EDmaDrv_CallBackType callback;               /*!< Callback that will be registered for this channel */
    void *callbackParam;                         /*!< Parameter passed to the channel callback */
    bool enableTrigger;                          /*!< Enables the periodic trigger capability for the DMA channel. */
} EDmaDrv_ChannelConfigType;

/*! \brief Transfer type for the DMA transfer.
 */
typedef enum
{
    EDMADRV_TRANSFER_PERIPH2MEM = 0U, /*!< Transfer from peripheral to memory */
    EDMADRV_TRANSFER_MEM2PERIPH,      /*!< Transfer from memory to peripheral */
    EDMADRV_TRANSFER_MEM2MEM,         /*!< Transfer from memory to memory */
    EDMADRV_TRANSFER_PERIPH2PERIPH    /*!< Transfer from peripheral to peripheral */
} EDmaDrv_TransferType;

/*! \brief Data structure for configuring a discrete memory transfer.
 */
typedef struct _EDmaDrv_ScatterGatherListType_
{
    uint32_t address;          /*!< Address of buffer. */
    uint32_t length;           /*!< Length of buffer. */
    EDmaDrv_TransferType type; /*!< Type of the DMA transfer */
} EDmaDrv_ScatterGatherListType;

/* Forward declaration of DMA register */
struct _EDmaRegType_;

/* Forward declaration of DMAMUX register */
struct _DmamuxRegType_;

/*! \brief The definition of DMA driver class
 */
typedef struct _EDmaDrvType_
{
    EDmaDrv_StateType *dmaState;
    struct _EDmaRegType_ *edmaReg;
    struct _DmamuxRegType_ *dmamuxReg;
} EDmaDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
/*! \brief Initializes the eDMA driver module
 *
 * This function initializes eDMA driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] dmaReg : pointer to eDMA register instance
 * \param[in] dmaReg : pointer to DMAMUX register instance
 */
extern void EDmaDrv_Init(EDmaDrvType *obj, struct _EDmaRegType_ *dmaReg, struct _DmamuxRegType_ *dmamuxReg);

/*! \brief Configures the eDMA module from a module configuration structure
 *
 * This function configures the eDMA module from a module configuration structure
 *
 * \param[out] moduleConfig : pointer to configuration structure
 */
extern void EDmaDrv_GetDefaultConfigure(EDmaDrv_ModuleConfigType *moduleConfig);

/*! \brief Configures the eDMA module from a channel configuration structure
 *
 * This function configures the eDMA module from a channel configuration structure
 *
 * \param[out] channelConfig : pointer to configuration structure
 */
extern void EDmaDrv_GetDefaultChannelConfigure(EDmaDrv_ChannelConfigType *channelConfig);

/*! \brief Configure the eDMA module.
 *
 * This function initializes the run-time state structure to provide the eDMA channel allocation
 * release, protect, and track the state for channels. This function also resets the eDMA modules,
 * initializes the module to user-defined settings and default settings.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] edmaState: The pointer to the eDMA peripheral driver state structure. The user passes
 * the memory for this run-time state structure and the eDMA peripheral driver populates the
 * members. This run-time state structure keeps track of the eDMA channels status. The memory must
 * be kept valid before calling the EDmaDrv_DeInit.
 * \param[in] moduleConfig: User configuration structure for eDMA peripheral drivers. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_Configure(EDmaDrvType *obj, EDmaDrv_StateType *edmaState, const EDmaDrv_ModuleConfigType *moduleConfig);

/*! \brief Configure the eDMA module.
 *
 * This function initializes the run-time state structure to provide the eDMA channel allocation
 * release, protect, and track the state for channels. This function also resets the eDMA modules,
 * initializes the module to user-defined settings and default settings.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] chnStateArray : Array of pointers to run-time state structures for eDMA channels;
 * will populate the state structures inside the eDMA driver state structure.
 * \param[in] chnConfig : pointers to channel initialization structures.
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_ConfigureChannel(EDmaDrvType *obj,
                                        EDmaDrv_ChnStateType *const chnStateArray[],
                                        const EDmaDrv_ChannelConfigType *const chnConfig);

/*! \brief De-initializes the eDMA module.
 *
 * This function resets the eDMA module to reset state and disables the interrupt to the core.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_Deinit(EDmaDrvType *obj);

/*! \brief Initializes an eDMA channel.
 *
 * This function initializes the run-time state structure for a eDMA channel, based on user
 * configuration. It will request the channel, set up the channel priority and install the
 * callback.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] edmaChannelState : Pointer to the eDMA channel state structure. The user passes
 * the memory for this run-time state structure and the eDMA peripheral driver populates the
 * members. This run-time state structure keeps track of the eDMA channel status. The memory must
 * be kept valid before calling the EDmaDrv_ReleaseChannel.
 * \param[in] edmaChannelConfig : User configuration structure for eDMA channel. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_ChannelInit(EDmaDrvType *obj,
                                   EDmaDrv_ChnStateType *edmaChannelState,
                                   const EDmaDrv_ChannelConfigType *edmaChannelConfig);

/*! \brief Releases an eDMA channel.
 *
 * This function stops the eDMA channel and disables the interrupt of this channel. The channel state
 * structure can be released after this function is called.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_ReleaseChannel(EDmaDrvType *obj, uint8_t channel);

/*! \brief Copies the channel configuration to the TCD registers.
 *
 * \param[in] channel : eDMA channel number
 * \param[in] tcd Pointer to the channel configuration structure.
 */
void EDmaDrv_PushConfigToReg(EDmaDrvType *obj, uint8_t channel, const EDmaDrv_TransferConfigType *tcd);

/*! \brief Copies the channel configuration to the software TCD structure.
 *
 * This function copies the properties from the channel configuration to the software TCD structure; the address
 * of the software TCD can be used to enable scatter/gather operation (pointer to the next TCD).
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] config : Pointer to the channel configuration structure.
 * \param[in] stcd : Pointer to the software TCD structure.
 */
void EDmaDrv_PushConfigToSTcd(const EDmaDrv_TransferConfigType *config, EDmaDrv_SoftwareTcdType *stcd);

/*! \brief Configures a simple single block data transfer with DMA.
 *
 * This function configures the descriptor for a single block transfer.
 * The function considers contiguous memory blocks, thus it configures the TCD
 * source/destination offset fields to cover the data buffer without gaps,
 * according to "transferSize" parameter (the offset is equal to the number of
 * bytes transferred in a source read/destination write).
 *
 * NOTE: For memory-to-peripheral or peripheral-to-memory transfers, make sure
 * the transfer size is equal to the data buffer size of the peripheral used,
 * otherwise only truncated chunks of data may be transferred (e.g. for a
 * communication IP with an 8-bit data register the transfer size should be 1B,
 * whereas for a 32-bit data register, the transfer size should be 4B). The
 * rationale of this constraint is that, on the peripheral side, the address
 * offset is set to zero, allowing to read/write data from/to the peripheral
 * in a single source read/destination write operation.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] type : Transfer type (M->M, P->M, M->P, P->P).
 * \param[in] srcAddr : A source register address or a source memory address.
 * \param[in] destAddr : A destination register address or a destination memory address.
 * \param[in] transferSize : The number of bytes to be transferred on every DMA write/read.
 *        Source/Dest share the same write/read size.
 * \param[in] dataBufferSize : The total number of bytes to be transferred.
 *
 * \return STATUS_ERROR or STATUS_SUCCESS
 */
extern EDmaDrv_Status EDmaDrv_ConfigSingleBlockTransfer(EDmaDrvType *obj,
                                                 uint8_t channel,
                                                 EDmaDrv_TransferType type,
                                                 uint32_t srcAddr,
                                                 uint32_t destAddr,
                                                 EDmaDrv_TransferSizeType transferSize,
                                                 uint32_t dataBufferSize,
                                                 bool enableHwClrDone);

/*! \brief Configures a multiple block data transfer with DMA.
 *
 * This function configures the descriptor for a multi-block transfer.
 * The function considers contiguous memory blocks, thus it configures the TCD
 * source/destination offset fields to cover the data buffer without gaps,
 * according to "transferSize" parameter (the offset is equal to the number of
 * bytes transferred in a source read/destination write). The buffer is divided
 * in multiple block, each block being transferred upon a single DMA request.
 *
 * NOTE: For transfers to/from peripherals, make sure
 * the transfer size is equal to the data buffer size of the peripheral used,
 * otherwise only truncated chunks of data may be transferred (e.g. for a
 * communication IP with an 8-bit data register the transfer size should be 1B,
 * whereas for a 32-bit data register, the transfer size should be 4B). The
 * rationale of this constraint is that, on the peripheral side, the address
 * offset is set to zero, allowing to read/write data from/to the peripheral
 * in a single source read/destination write operation.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] type : Transfer type (M->M, P->M, M->P, P->P).
 * \param[in] srcAddr : A source register address or a source memory address.
 * \param[in] destAddr : A destination register address or a destination memory address.
 * \param[in] transferSize : The number of bytes to be transferred on every DMA write/read.
 *        Source/Dest share the same write/read size.
 * \param[in] blockSize : The total number of bytes inside a block.
 * \param[in] blockCount : The total number of data blocks (one block is transferred upon a DMA request).
 * \param[in] disableReqOnCompletion : This parameter specifies whether the DMA channel should
 *        be disabled when the transfer is complete (further requests will remain untreated).
 *
 * \return STATUS_ERROR or STATUS_SUCCESS
 */
extern EDmaDrv_Status EDmaDrv_ConfigMultiBlockTransfer(EDmaDrvType *obj,
                                                uint8_t channel,
                                                EDmaDrv_TransferType type,
                                                uint32_t srcAddr,
                                                uint32_t destAddr,
                                                EDmaDrv_TransferSizeType transferSize,
                                                uint32_t blockSize,
                                                uint32_t blockCount,
                                                bool enableHwClrDone,
                                                bool disableReqOnCompletion);

/*! \brief Configures the DMA transfer in loop mode.
 *
 * This function configures the DMA transfer in a loop chain. The user passes a block of memory into this
 * function that configures the loop transfer properties (minor/major loop count, address offsets, channel linking).
 * The DMA driver copies the configuration to TCD registers, only when the loop properties are set up correctly
 * and minor loop mapping is enabled for the eDMA module.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] transferConfig : Pointer to the transfer configuration strucutre; this structure defines fields for setting
 * up the basic transfer and also a pointer to a memory strucure that defines the loop chain properties (minor/major).
 *
 * \return STATUS_ERROR or STATUS_SUCCESS
 */
extern EDmaDrv_Status EDmaDrv_ConfigLoopTransfer(EDmaDrvType *obj, uint8_t channel, const EDmaDrv_TransferConfigType *transferConfig);

/*! \brief Configures the DMA transfer in a scatter-gather mode.
 *
 * This function configures the descriptors into a single-ended chain. The user passes blocks of memory into
 * this function. The interrupt is triggered only when the last memory block is completed. The memory block
 * information is passed with the edma_scatter_gather_list_t data structure, which can tell
 * the memory address and length.
 * The DMA driver configures the descriptor for each memory block, transfers the descriptor from the
 * first one to the last one, and stops.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] stcd : Array of empty software TCD structures. The user must prepare this memory block. We don't need a
 * software TCD structure for the first descriptor, since the configuration is pushed directly to registers.The "stcd"
 * buffer must align with 32 bytes; if not, an error occurs in the eDMA driver. Thus, the required
 * memory size for "stcd" is equal to tcdCount * size_of(edma_software_tcd_t) - 1; the driver will take
 * care of the memory alignment if the provided memory buffer is big enough. For proper allocation of the
 * "stcd" buffer it is recommended to use STCD_SIZE macro.
 * \param[in] transferSize : The number of bytes to be transferred on every DMA write/read.
 * \param[in] bytesOnEachRequest Bytes to be transferred in each DMA request.
 * \param[in] srcList : Data structure storing the address, length and type of transfer (M->M, M->P, P->M, P->P) for
 * the bytes to be transferred for source memory blocks. If the source memory is peripheral, the length
 * is not used.
 * \param[in] destList : Data structure storing the address, length and type of transfer (M->M, M->P, P->M, P->P) for
 * the bytes to be transferred for destination memory blocks. In the memory-to-memory transfer mode, the
 * user must ensure that the length of the destination scatter gather list is equal to the source
 * scatter gather list. If the destination memory is a peripheral register, the length is not used.
 * \param[in] tcdCount : The number of TCD memory blocks contained in the scatter gather list.
 *
 * \return STATUS_ERROR or STATUS_SUCCESS
 */
extern EDmaDrv_Status EDmaDrv_ConfigScatterGatherTransfer(EDmaDrvType *obj,
                                                   uint8_t channel,
                                                   EDmaDrv_SoftwareTcdType *stcd,
                                                   EDmaDrv_TransferSizeType transferSize,
                                                   uint32_t bytesOnEachRequest,
                                                   bool  hardClrDone,
                                                   const EDmaDrv_ScatterGatherListType *srcList,
                                                   const EDmaDrv_ScatterGatherListType *destList,
                                                   const EDmaDrv_LoopTransferConfigType *loopTransferList,
                                                   uint8_t tcdCount);

/*! \brief Cancel the running transfer.
 *
 * This function cancels the current transfer, optionally signalling an error.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] bool : error If true, an error will be logged for the current transfer.
 */
void EDmaDrv_CancelTransfer(EDmaDrvType *obj, bool error);

/*! \brief Starts an eDMA channel.
 *
 * This function enables the eDMA channel DMA request.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_StartChannel(EDmaDrvType *obj, uint8_t channel);

/*! \brief Stops the eDMA channel.
 *
 * This function disables the eDMA channel DMA request.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_StopChannel(EDmaDrvType *obj, uint8_t channel);

/*! \brief Configures the DMA request for the eDMA channel.
 *
 * Selects which DMA source is routed to a DMA channel. The DMA sources are defined in the file
 * <MCU>_Features.h
 * Configures the periodic trigger capability for the triggered DMA channel.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] request : DMA request source.
 * \param[in] enableTrigger : DMA channel periodic trigger.
 *
 * \return STATUS_SUCCESS or STATUS_UNSUPPORTED.
 */
extern EDmaDrv_Status EDmaDrv_SetChannelRequestAndTrigger(EDmaDrvType *obj, uint8_t channel, uint8_t request, bool enableTrigger);

/*! \brief Clears all registers to 0 for the channel's TCD.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 */
extern void EDmaDrv_ClearTcd(EDmaDrvType *obj, uint8_t channel);

/*! \brief Configures the source address for the eDMA channel.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] address : The pointer to the source memory address.
 */
extern void EDmaDrv_SetSrcAddr(EDmaDrvType *obj, uint8_t channel, uint32_t address);

/*! \brief Configures the source address signed offset for the eDMA channel.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * source read is complete.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] offset : Signed-offset for source address.
 */
extern void EDmaDrv_SetSrcOffset(EDmaDrvType *obj, uint8_t channel, int16_t offset);

/*! \brief Configures the source data chunk size (transferred in a read sequence).
 *
 * Source data read transfer size (1/2/4/16/32 bytes).
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] size : Source transfer size.
 */
extern void EDmaDrv_SetSrcReadDestWriteChunkSize(EDmaDrvType *obj, uint8_t channel, EDmaDrv_TransferSizeType size);

/*! \brief Configures the source address last adjustment.
 *
 * Adjustment value added to the source address at the completion of the major iteration count. This
 * value can be applied to restore the source address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] adjust : Adjustment value.
 */
extern void EDmaDrv_SetSrcLastAddrAdjustment(EDmaDrvType *obj, uint8_t channel, int32_t adjust);

/*! \brief Configures the destination address for the eDMA channel.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] address :  The pointer to the destination memory address.
 */
extern void EDmaDrv_SetDestAddr(EDmaDrvType *obj, uint8_t channel, uint32_t address);

/*! \brief Configures the destination address signed offset for the eDMA channel.
 *
 * Sign-extended offset applied to the current destination address to form the next-state value as each
 * destination write is complete.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] offset : signed-offset
 */
extern void EDmaDrv_SetDestOffset(EDmaDrvType *obj, uint8_t channel, int16_t offset);

/*! \brief Configures the destination address last adjustment.
 *
 * Adjustment value added to the destination address at the completion of the major iteration count. This
 * value can be applied to restore the destination address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] adjust : Adjustment value.
 */
extern void EDmaDrv_SetDestLastAddrAdjustment(EDmaDrvType *obj, uint8_t channel, int32_t adjust);

/*! \brief Configures the number of bytes to be transferred in each service request of the channel.
 *
 * Sets the number of bytes to be transferred each time a request is received (one major loop iteration).
 * This number needs to be a multiple of the source/destination transfer size, as the data block will be
 * transferred within multiple read/write sequences (minor loops).
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] nbytes : Number of bytes to be transferred in each service request of the channel
 */
extern void EDmaDrv_SetMinorLoopBlockSize(EDmaDrvType *obj, uint8_t channel, uint32_t nbytes);

/*! \brief Configures the number of major loop iterations.
 *
 * Sets the number of major loop iterations; each major loop iteration will be served upon a request
 * for the current channel, transferring the data block configured for the minor loop (NBYTES).
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] majorLoopCount : Number of major loop iterations.
 */
extern void EDmaDrv_SetMajorLoopIterationCount(EDmaDrvType *obj, uint8_t channel, uint32_t majorLoopCount);

/*! \brief Returns the remaining major loop iteration count.
 *
 * Gets the number minor loops yet to be triggered (major loop iterations).
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \return number of major loop iterations yet to be triggered
 */
extern uint32_t EDmaDrv_GetRemainingMajorIterationsCount(EDmaDrvType *obj, uint8_t channel);

/*! \brief Configures the memory address of the next TCD, in scatter/gather mode.
 *
 * This function configures the address of the next TCD to be loaded form memory, when scatter/gather
 * feature is enabled. This address points to the beginning of a 0-modulo-32 byte region containing
 * the next transfer TCD to be loaded into this channel. The channel reload is performed as the
 * major iteration count completes. The scatter/gather address must be 0-modulo-32-byte. Otherwise,
 * a configuration error is reported.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] nextTCDAddr : The address of the next TCD to be linked to this TCD.
 */
extern void EDmaDrv_SetScatterGatherLink(EDmaDrvType *obj, uint8_t channel, uint32_t nextTCDAddr);

/*! \brief Disables/Enables the DMA request after the major loop completes for the TCD.
 *
 * If disabled, the eDMA hardware automatically clears the corresponding DMA request when the
 * current major iteration count reaches zero.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] disable : Disable (true)/Enable (false) DMA request after TCD complete.
 */
extern void EDmaDrv_DisableRequestsOnTransferComplete(EDmaDrvType *obj, uint8_t channel, bool disable);

/*! \brief Disables/Enables the channel interrupt requests.
 *
 * This function enables/disables error, half major loop and complete major loop interrupts
 * for the current channel.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 * \param[in] interrupt : Interrupt event (error/half major loop/complete major loop).
 * \param[in] enable : Enable (true)/Disable (false) interrupts for the current channel.
 */
extern void EDmaDrv_ConfigureInterrupt(EDmaDrvType *obj, uint8_t channel, EDmaDrv_ChannelInterruptType intSrc, bool enable);

/*! \brief Triggers a sw request for the current channel.
 *
 * This function starts a transfer using the current channel (sw request).
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number
 */
extern void EDmaDrv_TriggerSwRequest(EDmaDrvType *obj, uint8_t channel);

/*! \brief Registers the callback function and the parameter for eDMA channel.
 *
 * This function registers the callback function and the parameter into the eDMA channel state structure.
 * The callback function is called when the channel is complete or a channel error occurs. The eDMA
 * driver passes the channel status to this callback function to indicate whether it is caused by the
 * channel complete event or the channel error event.
 *
 * To un-register the callback function, set the callback function to "NULL" and call this
 * function.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number.
 * \param[in] callback : The pointer to the callback function.
 * \param[in] parameter : The pointer to the callback function's parameter.
 *
 * \return STATUS_ERROR or STATUS_SUCCESS.
 */
extern EDmaDrv_Status EDmaDrv_InstallCallback(EDmaDrvType *obj, uint8_t channel, EDmaDrv_CallBackType callback, void *parameter);

/*! \brief Gets the eDMA channel status.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number.
 *
 * \return Channel status.
 */
extern EDmaDrv_ChnStatusType EDmaDrv_GetChannelStatus(EDmaDrvType *obj, uint8_t channel);

/*! \brief DMA channel interrupt handler, implemented in driver c file.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number.
 */
extern void EDmaDrv_IRQHandler(EDmaDrvType *obj, uint8_t Channel);

/*! \brief DMA error interrupt handler, implemented in driver c file.
 *
 * \param[in] obj : pointer to eDMA driver instance
 * \param[in] channel : eDMA channel number.
 */
extern void EDmaDrv_ErrorIRQHandler(EDmaDrvType *obj, uint8_t channel);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _DMA_DRV_H_ */
