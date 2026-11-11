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

#ifndef _FEE_TRACE_H_
#define _FEE_TRACE_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

/*! \addtogroup Flash EEPROM Emulation
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
#ifndef FEE_DBG_MAIN_FSM_ERROR_ENTRY
#define FEE_DBG_MAIN_FSM_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_FSM_ERROR_ENTRY
#define FEE_DBG_GC_FSM_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_COPY_FSM_ERROR_ENTRY
#define FEE_DBG_GC_COPY_FSM_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_INITIALIZATION_FSM_ERROR_ENTRY
#define FEE_DBG_INITIALIZATION_FSM_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_SEARCH_MULTIPLE_VALID_SECTOR_ERROR_ENTRY
#define FEE_DBG_SEARCH_MULTIPLE_VALID_SECTOR_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_SEARCH_MULTIPLE_GC_SECTOR_ERROR_ENTRY
#define FEE_DBG_SEARCH_MULTIPLE_GC_SECTOR_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_STORAGE_ERROR_ENTRY
#define FEE_DBG_STORAGE_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_WRITE_BLOCK_DATA_ERROR_ENTRY
#define FEE_DBG_GC_WRITE_BLOCK_DATA_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_WRITE_BLOCK_HEAD_INFO_ERROR_ENTRY
#define FEE_DBG_GC_WRITE_BLOCK_HEAD_INFO_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_READ_BLOCK_DATA_ERROR_ENTRY
#define FEE_DBG_GC_READ_BLOCK_DATA_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_ERASE_ACTIVE_SECTOR_ERROR_ENTRY
#define FEE_DBG_GC_ERASE_ACTIVE_SECTOR_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_WRITE_INIT_MARK_ERROR_ENTRY
#define FEE_DBG_GC_WRITE_INIT_MARK_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_WRITE_START_MARK_ERROR_ENTRY
#define FEE_DBG_GC_WRITE_START_MARK_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_WRITE_END_MARK_ERROR_ENTRY
#define FEE_DBG_GC_WRITE_END_MARK_ERROR_ENTRY()
#endif

#ifndef FEE_DBG_GC_WRITE_ENABLE_MARK_ERROR_ENTRY
#define FEE_DBG_GC_WRITE_ENABLE_MARK_ERROR_ENTRY()
#endif

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

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

#endif /* _FEE_TRACE_H_ */
