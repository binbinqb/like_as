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

#ifndef _FEE_EXTRA_H_
#define _FEE_EXTRA_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup Flash EEPROM Emulation
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*! \brief Define macros that express the address of a feed.
 */
#define Fee_AddressType      uint8_t *

/*! \brief Define N-byte aligned macros.
 */
#ifndef ALIGNBYTE
#define ALIGNBYTE(size, n) ((size + n - 1) & ~(n - 1))
#endif

/*! \brief Define 4-byte aligned macros.
 */
#ifndef ALIGN4BYTE
#define ALIGN4BYTE(size)     (ALIGNBYTE(size, 4))
#endif

/*! \brief Define 8-byte aligned macros.
 */
#ifndef ALIGN8BYTE
#define ALIGN8BYTE(size)     (ALIGNBYTE(size, 8))
#endif

/*! \brief Define 64-byte aligned macros.
 */
#ifndef ALIGN64BYTE
#define ALIGN64BYTE(size)    (ALIGNBYTE(size, 64))
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
    FEE_JOBENDNOTIFICATION      = 0x00,
    FEE_JOBERRORNOTIFICATION    = 0x01,
} Fee_NotificationType;

/*! \brief Define the type of return value for flash operations.
 */
typedef enum
{
    FLS_STATE_OK                = 0x00,
    FLS_STATE_NOT_WRITABLE      = 0x01,
    FLS_STATE_ECC_ERROR         = 0x02,
    FLS_STATE_READ_BACK_FAIL    = 0x04,
    FLS_STATE_PROGRAM_FAIL      = 0x05,
    FLS_STATE_ERASE_FAIL        = 0x05,
    FLS_STATE_NOT_WRITTEN       = 0x07,
    FLS_STATE_UNKNOW            = 0x08,
}Fls_StateType;

/*! \brief Define the type of virtual function for Notification.
 */
typedef void (*NotificationPtrType)(Fee_NotificationType notificationNumber);

/*! \brief Define the type of virtual function for writing flash operations.
 */
typedef Fls_StateType (*Fee_writeMethodType)(Fee_AddressType sAddr, uint8_t *buff, uint32_t size);

/*! \brief Define virtual function types for read flash operations.
 */
typedef Fls_StateType (*Fee_readMethodType)(Fee_AddressType sAddr, uint8_t *buff, uint32_t size);

/*! \brief Define virtual function types for erasing flash operations.
 */
typedef Fls_StateType (*Fee_eraseMethodType)(Fee_AddressType eraseAddr);

/*! \brief Define virtual function types to check whether flash is writable.
 */
typedef Fls_StateType (*Fee_isWriteableType)(Fee_AddressType sAddr, uint32_t size);

/*! \brief Define virtual function types for calculating crc8.
 */
typedef uint8_t (*Fee_calcCrc8Type)(void *sAddr, uint32_t size);

/*! \brief Define the type of the feed operation flash method.
 */
typedef struct _Fee_MethodType_
{
    Fee_writeMethodType write;
    Fee_readMethodType  read;
    Fee_eraseMethodType erase;
    Fee_isWriteableType isWriteable;
    Fee_calcCrc8Type    crc8;
} Fee_MethodType;

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

#endif /* _FEE_EXTRA_H_ */
