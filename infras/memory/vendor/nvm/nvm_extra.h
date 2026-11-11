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

#ifndef _NVM_EXTRA_H_
#define _NVM_EXTRA_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
/*! \addtogroup NVRAM Manager
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Define N-byte aligned macros.
 */
#ifndef ALIGNBYTE
#define ALIGNBYTE(size, n) ((size + n - 1) & ~(n - 1))
#endif

/*! \brief Define 4-byte aligned macros.
 */
#ifndef ALIGN4BYTE
#define ALIGN4BYTE(size) (ALIGNBYTE(size, 4))
#endif

/*! \brief Define 8-byte aligned macros.
 */
#ifndef ALIGN8BYTE
#define ALIGN8BYTE(size) (ALIGNBYTE(size, 8))
#endif

/*! \brief Define 64-byte aligned macros.
 */
#ifndef ALIGN64BYTE
#define ALIGN64BYTE(size) (ALIGNBYTE(size, 64))
#endif

/*! \brief Define address aligned macros.
 */
#ifndef ALIGNED
#define ALIGNED(val, alncnt) (((uint32_t)val) & ~(alncnt - 1))
#endif
/*******************************************************************************
 * the typedefs
 ******************************************************************************/
/*! \brief Define the type of the Notification return value.
 */
typedef enum
{
    NVM_JOBFINISHNOTIFICATION = 0x00,
    NVM_JOBERRORNOTIFICATION  = 0x01,
} NVM_NotificationType;

/*! \brief Define the type of return value for lower level module operations.
 */
typedef enum
{
    NVM_JOB_RESULT_OK              = 0x00,
    NVM_JOB_RESULT_NOT_OK          = 0x01,
    NVM_JOB_RESULT_PENDING         = 0x02,
    NVM_JOB_RESULT_BL_INCONSISTENT = 0x03,
    NVM_JOB_RESULT_BL_INVALID      = 0x04,
} NVM_JobResultType;

/*! \brief Define the type of return value for lower level module status.
 */
typedef enum
{
    NVM_STATUS_IDLE   = 0x01,
    NVM_STATUS_READ   = 0x02,
    NVM_STATUS_WRITE  = 0x03,
    NVM_STATUS_GC     = 0x04,
    NVM_STATUS_UNKNOW = 0x05,
    NVM_STATUS_ERROR  = 0x06,
} Nvm_StatusType;

/*! \brief Define the type of virtual function for Notification.
 */
typedef void (*NvmNotificationPtrType)(NVM_NotificationType notificationNumber);

/*! \brief Define the type of virtual function for writing lower level module operations.
 */
typedef bool (*Nvm_writeMethodType)(uint16_t blockNumber, uint8_t *dataBuffer, NvmNotificationPtrType notificationPtr);

/*! \brief Define virtual function types for read lower level module operations.
 */
typedef bool (*Nvm_readMethodType)(uint16_t blockNumber, uint16_t blockOffset, uint8_t *dataBuffer, NvmNotificationPtrType notificationPtr);

/*! \brief Define virtual function types for calculating crc8.
 */
typedef uint8_t (*Nvm_calcCrc8Type)(void *sAddr, uint32_t size);

/*! \brief Define virtual function types for lower level module job handle result.
 */
typedef NVM_JobResultType (*Nvm_getJobResultType)(void);

/*! \brief Define virtual function types for lower level module module status.
 */
typedef Nvm_StatusType (*Nvm_GetStatusType)(void);

/*! \brief Define the type of the nvm operation lower level module method.
 */
typedef struct _Nvm_MethodType_
{
    Nvm_writeMethodType  write;
    Nvm_readMethodType   read;
    Nvm_calcCrc8Type     crc8;
    Nvm_getJobResultType getJobResult;
    Nvm_GetStatusType    getStatus;
} Nvm_MethodType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _NVM_EXTRA_H_ */
