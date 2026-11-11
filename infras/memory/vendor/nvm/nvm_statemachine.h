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

#ifndef _NVM_STATEMACHINE_H_
#define _NVM_STATEMACHINE_H_

/*! \brief Contains public interface to various functions related
 *         to the NVM (NVRAM Manager) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "nvm_types.h"

/*! \addtogroup NVRAM Manager
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

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

void Nvm_StateMachine_Idle(const NvmType *obj);
void Nvm_StateMachine_Read_Entry(const NvmType *obj);
void Nvm_StateMachine_Read(const NvmType *obj);
void Nvm_StateMachine_Write_Entry(const NvmType *obj);
void Nvm_StateMachine_Write(const NvmType *obj);
void Nvm_StateMachine_ReadAll_Entry(const NvmType *obj);
void Nvm_StateMachine_ReadAll(const NvmType *obj);
void Nvm_StateMachine_WriteAll_Entry(const NvmType *obj);
void Nvm_StateMachine_WriteAll(const NvmType *obj);
void Nvm_StateMachine_EraseAll_Entry(const NvmType *obj);
void Nvm_StateMachine_EraseAll(const NvmType *obj);
void Nvm_StateMachine_Erase_Entry(const NvmType *obj);
void Nvm_StateMachine_Erase(const NvmType *obj);
void Nvm_ReadNotification(const NvmType *obj, NVM_NotificationType notificationNumber);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _NVM_STATEMACHINE_H_ */
