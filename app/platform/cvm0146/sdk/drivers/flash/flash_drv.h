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

#ifndef _FLASH_DRV_H_
#define _FLASH_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of FLASH
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Macro for high and low position separation of the memory address.
 *
 * The 32-bit address need to be sperated to 8-bit and then programmed to
 * specific fccob registers.
 */
#define FCCOBADDRLOW(addr)          ((uint8_t)(((uint32_t)(addr)) & 0xFFU))
#define FCCOBADDRMDLOW(addr)        ((uint8_t)((((uint32_t)(addr)) >> 8) & 0xFFU))
#define FCCOBADDRMDHIG(addr)        ((uint8_t)((((uint32_t)(addr)) >> 16) & 0xFFU))
#define FCCOBADDRHIG(addr)          ((uint8_t)(((uint32_t)(addr)) >> 24))

/*! \brief Macro for the alignment requirement.
 *
 * The address need to be n-aligned.
 */
#define ALIGNED(val, alncnt)        (((uint32_t)val) & ~(alncnt - 1))
#define IS_ALIGNED(val, alncnt)     ((((uint32_t)val) & (alncnt - 1)) == 0x0 ? true : false)

/*! \brief Macro for pflash sector size
 *
 * Sector size is 2048.
 */
#define FLASHDRV_PFLASH_SECTOR_SIZE (2048U)

/*! \brief Macro for dflash sector size
 *
 * Sector size is 1024.
 */
#define FLASHDRV_DFLASH_SECTOR_SIZE (1024U)

/*! \brief Macro for the byte count of phrase-write and phrase-read
 *
 * phrase-write/phrase-read size
 */
#define FLASHDRV_PHRASE_SIZE        (8U)

/*! \brief Macro for the flexram address
 *
 * fastram address
 */
#define FLASHDRV_FLEXRAM_ADDR       (0x14000000UL)

/*! \brief Macro for the flexram size
 *
 * fastram size
 */
#define FLASHDRV_FLEXRAM_SIZE       (4096U)

/*! \brief Macro for the cse key-sector address
 *
 * cse key-sector address
 */
#define FLASHDRV_KEYSECTOR_ADDR     (0x00101000UL)

/*! \brief Macro for key sector size
 *
 * Sector size is 1024.
 */
#define FLASHDRV_KEY_SECTOR_SIZE    (1024U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Status return codes.
 * Common error codes will be a unified enumeration (C enum) that will contain
 * all error codes (common and specific). There will be separate "error values
 * spaces" (or slots), each of 256 positions, allocated per functionality.
 */
typedef enum
{
    /* Generic error codes */
    FLASHDRV_STATUS_SUCCESS     = 0x000U, /*!< Generic operation success status */
    FLASHDRV_STATUS_ERROR       = 0x001U, /*!< Generic operation failure status */
    FLASHDRV_STATUS_BUSY        = 0x002U, /*!< Generic operation busy status */
    FLASHDRV_STATUS_TIMEOUT     = 0x003U, /*!< Generic operation timeout status */
    FLASHDRV_STATUS_UNSUPPORTED = 0x004U, /*!< Generic operation unsupported status */
    FLASHDRV_STATUS_WARNING     = 0x006U, /*!< Generic operation warning status: about ecc status */
} FlashDrv_Status;

/*! \brief FLASH type of operation cmd
 */
typedef enum
{
    FLASHDRV_OPCMD_BLKRD1S    = 0x00, /*!< Block Read 1s command*/
    FLASHDRV_OPCMD_SCTRD1S    = 0x01, /*!< Section Read 1s command*/
    FLASHDRV_OPCMD_PRSCHK     = 0x02, /*!< Phrase check command*/
    FLASHDRV_OPCMD_PRSPGM     = 0x03, /*!< Phrase Program command*/
    FLASHDRV_OPCMD_BLKERS     = 0x04, /*!< Block Erase command*/
    FLASHDRV_OPCMD_SCTERS     = 0x05, /*!< Sector Erase command*/
    FLASHDRV_OPCMD_SCTPGM     = 0x06, /*!< Program section command*/
    FLASHDRV_OPCMD_ALBLKRD1S  = 0x07, /*!< Read 1s ALL Blocks command*/
    FLASHDRV_OPCMD_RDINFORG   = 0x08, /*!< Read info region command: for info region read*/
    FLASHDRV_OPCMD_PGMINFORG  = 0x09, /*!< Program info region command: for info region program*/
    FLASHDRV_OPCMD_ALBLKERS   = 0x0A, /*!< Erase ALL blocks command*/
    FLASHDRV_OPCMD_VRFYKEY    = 0x0B, /*!< Verify backdoor access key command*/
    FLASHDRV_OPCMD_ALBLKUERS  = 0x0C, /*!< Erase All Blocks unsecure command*/
    FLASHDRV_OPCMD_SETFRAM    = 0x0D, /*!< Set Flaxram command*/
    FLASHDRV_OPCMD_CSE_SCTPGM = 0x0E, /*!< CSE Key sector: sector program command*/
    FLASHDRV_OPCMD_CSE_SCTERS = 0x0F, /*!< CSE Key sector: sector erase command*/
} FlashDrv_Opcmd_t;

/*! \brief FLASH specific region type
 */
typedef enum
{
    FLASHDRV_INFORG0 = 0x00, /*!<secure info region, size 2k,     phrase_index: 0 ~ 255,all-block erase cmd can erase*/
    FLASHDRV_INFORG1 = 0x01, /*!<program-once region, size 2k,    phrase_index: 0 ~ 255,no erase cmd*/
    FLASHDRV_INFORG2 = 0x02, /*!<program-partition region,size 1k,phrase_index: 0 ~ 127,all-block erase cmd can erase*/
} FlashDrv_InfoRegion_t;

/*! \brief FLASH sector erase type
 */
typedef enum
{
    FLASHDRV_SCTERS_ONEPULSE = 0x00, /*!< one-pulse erase */
    FLASHDRV_SCTERS_RETRY    = 0x01, /*!< retry erase     */
} FlashDrv_SectorErase_t;

/*! \brief Definition for the flash cmd done callback function.
 *
 * Prototype for the callback function registered in the flash driver.
 */
typedef void (*FlashDrv_CallBackType)(void);

/*! \brief Definition of configuration of FLASH driver
 */
typedef struct _FlashDrv_ConfigType_
{
    uint32_t              pflashbase;     /*!< The base address of P-Flash memory */
    uint32_t              pflashsize;     /*!< The size in byte of P-Flash memory */
    uint32_t              dflashbase;     /*!< The base address of D-Flash memory */
    uint32_t              dflashsize;     /*!< The size in byte of P-Flash memory */
    bool                  eeevld;         /*!< emualted ee function enabled flag*/
    FlashDrv_CallBackType callback;       /*!< Call back function to service the time critical events. Any code reachable from this function
                                           *   must not be placed in a Flash block targeted for a program/erase operation */
} FlashDrv_ConfigType;

/* Forward declaration of flash ftfc register */
struct _FtfcRegType_;

/*! \brief The definition of flash driver class
 */
typedef struct _FlashDrvType_
{
    struct _FtfcRegType_ *reg;
    uint32_t              pflashbase;     /*!< The base address of P-Flash memory */
    uint32_t              pflashsize;     /*!< The size in byte of P-Flash memory */
    uint32_t              dflashbase;     /*!< The base address of D-Flash memory */
    uint32_t              dflashsize;     /*!< The size in byte of P-Flash memory */
    bool                  eeevld;         /*!< emualted ee function enabled flag*/
    FlashDrv_CallBackType callback;       /*!< Call back function to service the time critical events. Any code reachable from this function
                                           *   must not be placed in a Flash block targeted for a program/erase operation */
} FlashDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the Flash driver module
 *
 * This function initializes Flash driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] reg : pointer to Flash register instance
 */
extern void FlashDrv_Init(FlashDrvType *obj, struct _FtfcRegType_ *reg);

/*! \brief Get configures of the Flash module currently
 *
 * This function gets configures of the Flash module currently
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void FlashDrv_GetConfig(const FlashDrvType  *obj,
                               FlashDrv_ConfigType *userconfig);

/*! \brief Get default configures the Flash module for configuration structure
 *
 * This function gets default configures the Flash module for user configuration
 * structure
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void FlashDrv_GetDefaultConfig(FlashDrv_ConfigType *userconfig);

/*! \brief Configures the Flash module from a user configuration structure
 *
 * This function configures the Flash module from a user configuration structure
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void FlashDrv_Configure(FlashDrvType              *obj,
                               const FlashDrv_ConfigType *userconfig);

/*! \brief Verify the Pflash or Dfalsh erased
 *
 * This function verify pflash or dflash is erased.
 *
 * NOTE:if dflash is seleced and emulated ee valid , the read1s sequence will be aborted.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] destaddr : pointer to a memory address in pflash/dflash
 */
extern FlashDrv_Status FlashDrv_Read1sBlock(FlashDrvType *obj,
                                            uint32_t     *destaddr);

/*! \brief Verify a section erased
 *
 * This function verify a section erased. The section should located in a sector
 * or should be a total sector. Both the start addr and the size of the section
 * are supposed to be 8-aligned.
 *
 * NOTE:if the target section is in eee backup region, the read1s sequence will be aborted.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] destaddr : pointer to a memory address in pflash or dflash:8-aligned.
 * \param[in] rdsize : length of read/verified memory in bytes:8-aligned.
 */
extern FlashDrv_Status FlashDrv_Read1sSection(FlashDrvType *obj,
                                              uint32_t     *destaddr,
                                              uint32_t      rdsize);

/*! \brief Check a phrase programmed as expected value
 *
 * This function checked a phrase-data[8bytes] progrmmed as expected value.
 * The phrase addr is supposed to be 8-aligned.
 *
 * NOTE:if the target phrae is in eee backup region, the check sequence will be aborted.
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] destaddr : pointer to a memory address in pflash or dflash,8-aligned.
 * \param[in] expdata : pointor to expected data, 8 bytes
 */
extern FlashDrv_Status FlashDrv_CheckPhrase(FlashDrvType *obj,
                                            uint32_t     *destaddr,
                                            uint8_t      *expdata);

/*! \brief Check a phrase has ecc ded error
 *
 * This function checked a phrase-data[8bytes] has ecc ded error.
 *
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] destaddr : pointer to a memory address in pflash or dflash, 8-aligned.
 */
extern FlashDrv_Status FlashDrv_CheckEccState(FlashDrvType *obj,
                                                uint32_t     *destaddr);

/*! \brief Program a phrase as expected value
 *
 * This function checked a phrase-data[8bytes/9bytes] progrmmed as expected
 * value. The phrase addr is supposed to be 8-aligned.
 *
 * NOTE: 1.make sure targeted phrase is erased and not proteted before
 * programmed; 2.if the target phrase is in eee backup region, the check sequence will be aborted.
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] destaddr : pointer to a memory address in dflash,8-aligned.
 * \param[in] expdata : pointor to programmed data, 8 bytes or 9 bytes
 * \param[in] hweccen : true: first 8 bytes will be programmed, ecc byte programmed by hardware;
 *                      false: 9 bytes(ecc byte included) will be programmed;
 */
extern FlashDrv_Status FlashDrv_ProgramPhrase(FlashDrvType *obj,
                                              uint32_t     *destaddr,
                                              uint8_t      *expdata,
                                              bool          hweccen);

/*! \brief Erase Pflash or Dfalsh(keysector included)
 *
 * This function erase pflash or dflash. .
 *
 * NOTE:
 *    1.Any code reachable from this function must not be placed in a Flash
 *      block targeted for this erase operation.
 *   2.if dflash is seleced and EEEVLD == 1, the erase sequence will be aborted.
 *   3.if there is protection region in targeted block, the erase sequence will be aborted
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] destaddr : pointer to a memory address of pflash or dflash, 8-aligned
 * \param[in] erasetype: erase type
 */
extern FlashDrv_Status FlashDrv_EraseBlock(FlashDrvType          *obj,
                                           uint32_t              *destaddr,
                                           FlashDrv_SectorErase_t erasetype);
/*! \brief Erase a sector
 *
 * This function erase a sector located in the pflash or dflash.
 *
 * NOTE:
 *    1.Any code reachable from this function must not be placed in a Flash
 * sector targeted for this erase operation.
 *    2.if the targeted sector is in the eee backup region, the erase sequence will be aborted.
 *    3.if the targeted sector is in protection region, the erase sequence will be aborted
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] destaddr : pointer to a memory address in the targeted sector
 * \param[in] erasetype: erase type
 */
extern FlashDrv_Status FlashDrv_EraseSector(FlashDrvType          *obj,
                                            uint32_t              *destaddr,
                                            FlashDrv_SectorErase_t erasetype);

/*! \brief Program a section
 *
 * This function programs a section. The section should located in a sector or
 * should be a total sector. Both the start addr and the size of the section are
 * supposed to be 256-aligned.
 *
 * NOTE: 1.make sure targeted section is erased and not proteted before
 * programmed; 2.if the target section is in eee backup region, the program sequence
 * will be aborted.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] destaddr : pointer to a memory address in the targeted sector,256-aligned
 * \param[in] len : length of programmed data in bytes, 256-aligned
 * \param[in] databuf : pointer to source data
 */
extern FlashDrv_Status FlashDrv_ProgramSection(FlashDrvType *obj,
                                               uint32_t     *destaddr,
                                               uint32_t      len,
                                               uint8_t      *databuf);

/*! \brief Programs a section
*
* This function programs a section fastly. The section should located in a sector or
* should be a total sector. Both the start addr and the size of the section are
* supposed to be 256-aligned. The programmed data is supposed to be prepared already in the flexram.
*
* NOTE: 1.make sure targeted section is erased and not proteted before
* programmed; 2.if the target section is in eee backup region,
* the program sequence will be aborted.3.the programmed data has been placed in the flexram with
* correct offset(offset = dest & (FLASHDRV_SECTOR_SIZE - 1)) while ram ready.
*
* \param[in] obj : pointer to Flash driver instance
* \param[in] destaddr : pointer to a memory address in the targeted sector,256-aligned
* \param[in] len : length of programmed data in bytes, 256-aligned
*/
extern FlashDrv_Status FlashDrv_ProgramSectionFast(FlashDrvType *obj, uint32_t *destaddr, uint32_t len);

/*! \brief verify all blocks erased.
 *
 * This function verify all blocks [pflash,dflash, keysector,pflash info region
 * and dflash info region]erased.
 *
 * \param[in] obj : pointer to Flash driver instance
 */
extern FlashDrv_Status FlashDrv_Read1sAllBlock(FlashDrvType *obj);

/*! \brief Read a phrase(8 bytes) from sepcific info region
 *
 * This function Read a phrase(8 bytes) from sepcific info region: secure info region,
 * program-once info region, program-patition info region.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] regionid : FlashDrv_InfoRegion_t
 * \param[in] phraseid : index of the phrase in the info region sector, 0~255 or 0 ~ 127
 * \param[in] databuf  : pointer to a 8-byte-len buffer which data read from info region and write to
 */
extern FlashDrv_Status FlashDrv_ReadInfoRegion(FlashDrvType         *obj,
                                               FlashDrv_InfoRegion_t regionid,
                                               uint32_t              phraseid,
                                               uint8_t              *databuf);

/*! \brief Erase all blocks.
 *
 * This function erase pflash,dflash(eee backup region),flexram,
 * sepcific info region(secure info region,program-once info region)
 *
 * NOTE:
 *    1.Any code reachable from this function must not be placed in a Flash
 * block targeted for this erase operation. 2.Between the POR and
 * allblock-erased operations, remind to program secure info region
 * to proper value.Otherwise, system will enter security state, swd cannot be
 * connected. 3.if there is protection region in flash, the erase sequence will be aborted
 *
 * \param[in] obj : pointer to Flash driver instance
 */
extern FlashDrv_Status FlashDrv_EraseAllBlock(FlashDrvType *obj);

/*! \brief Erase all blocks and update security bit in secure info region.
 *
 * This function erase pflash,dflash(eee backup region),flexram,
 * sepcific info region(secure info region,program-once info region),
 * and then program the security bit in flash security info field.
 *
 * NOTE:
 *    1.Any code reachable from this function must not be placed in a Flash
 * block targeted for this erase operation. 2.if MEEN disbled, the erase sequence will be
 * aborted
 *
 * \param[in] obj : pointer to Flash driver instance
 */
extern FlashDrv_Status FlashDrv_EraseAllBlockUnsecure(FlashDrvType *obj);

/*! \brief Program a phrase(8 bytes) to pflash info region or dflash info region
 * with expected data
 *
 * This function program a phrase(8 bytes) to pflash info region or dflash info
 * region.
 *
 * NOTE: 1.make sure targeted phrase is erased before programmed;
 *       2.if the targeted phrase is in program-once info region,
 *       make sure the targeted phrase can be programmed only one time through the lifecycle;
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] regionid : FlashDrv_InfoRegion_t
 * \param[in] phraseid : index of the phrase in the info region sector, 0~255 or 0~ 127
 * \param[in] databuf  : pointer to a 8-byte-len buffer which expected data carried
 */
extern FlashDrv_Status FlashDrv_ProgramInfoRegion(FlashDrvType         *obj,
                                                  FlashDrv_InfoRegion_t regionid,
                                                  uint32_t              phraseid,
                                                  uint8_t              *databuf);

/*! \brief Erase cse key sector
 *
 * This function erase cse key sector.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] erasetype: erase type
 */
extern FlashDrv_Status FlashDrv_EraseCseSector(FlashDrvType          *obj,
                                               FlashDrv_SectorErase_t erasetype);

/*! \brief Program a section in key sector
 *
 * This function programs some keys into key-sector. The section should located
 * in a sector or should be a total sector. Both the start addr and the size of
 * the section are supposed to be 16-aligned.
 *
 * NOTE: 1.make sure targeted section is erased before this program operation;
         2.make sure the expected keys wrote to key-ram by cse before this program oeration.
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] destaddr : pointer to a phrase address in the key sector,16-aligned
 * \param[in] len : length of programmed data in bytes, 16-aligned
 */
extern FlashDrv_Status FlashDrv_ProgramCseSection(FlashDrvType *obj,
                                                  uint32_t     *destaddr,
                                                  uint32_t      len);

/*! \brief Verify the user backdoor key and make the system enter unsecurity
 * state if pass.
 *
 * This function verify the user backdoor key stored in secure info region with expected
 * data.If the verified pass,the system will enter un-security state.
 *
 * NOTE: 1.if the KEY-EN disabled, this sequence will be aborted;
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] expdata : pointor to expected key-value, 8 bytes, supposed not to
 *                      be all-0s or all-1s.
 */
extern FlashDrv_Status FlashDrv_VerifyUserKey(FlashDrvType *obj,
                                              uint8_t      *expdata);

/*! \brief flash command done interrupt handler.
 *
 * \param[in] obj : pointer to Flash driver instance.
 */
extern void FlashDrv_IRQHandler(FlashDrvType *obj);

/*! \brief flash command done interrupt enable in flash driver side.
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] en  : control flag for the flash command done interrupter enable or disable
 */
extern void FlashDrv_SetCmdDoneIrqEn(FlashDrvType *obj, bool en);

/*! \brief sets the flexram as eee-ram or system-ram.
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] eeeramen  : control eee_ram enabled or disabled,
 *                        --if eee_ram enabled, UpdateEeRam will take effect;
 *                        --if eee_ram disabled, the flex_ram will be used as system ram
 */
extern FlashDrv_Status FlashDrv_SetFlexRam(FlashDrvType *obj, bool eeeramen);

/*! \brief updates eee_ram with expected data
 *
 *NOTE: 1.the auto_gc(SCG0_Inst:TRIM_AUTO_GC_EN) enabled in this function
 *      2.makesure the eee-ram is enabled otherwise the new data will be lost
 *
 * \param[in] obj : pointer to Flash driver instance.
 * \param[in] offset : indicates the targeted position in the eee-ram, range is [0 ~ 4096]
 * \param[in] srcdata : pointer to srcdata which will be wrote into eee-ram
 * \param[in] sz: len of srcdata in byte
 */
extern FlashDrv_Status FlashDrv_UpdateEeeRam(FlashDrvType *obj, uint32_t offset, uint8_t *srcdata, uint32_t sz);

/*! \brief Gets eee auto GC enable state
 *
 * This function gets the eee auto GC enable state
 *
 * \param[in] obj : pointer to Flash driver instance
 * \return eee auto GC enable state
 *         - false : eee auto GC disabled
 *         - true  : eee auto GC enabled
 */
extern bool FlashDrv_GetEeeAutoGcEn(FlashDrvType *obj);

/*! \brief Sets eee auto GC enable
 *
 * This function sets the eee auto GC enabled or disabled
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[in] eeegcen  : control eee auto gc enabled or disabled,
 *             -false : the eee auto gc disabled
 *             -true :  the eee auto gc enabled
 */
extern void FlashDrv_SetEeeAutoGcEn(FlashDrvType *obj, bool eeegcen);

/*! \brief Get eee enable state
 *
 * This function gets the eee enable state
 *
 * \param[in] obj : pointer to Flash driver instance
 * \return eee enable state
 *         - false : eee not enabled in eeeprom Cfg field.If EEE enable expected, progroram InfoRegion with correct data and then POR
 *         - true  : eee enabled in eeeprom Cfg field
 */
extern bool FlashDrv_GetEeeEn(FlashDrvType *obj);

/*! \brief Get eee_ram ready state
 *
 * This function gets the eeerst enable state
 *
 * \param[in] obj : pointer to Flash driver instance
 * \return eee_ram ready state
 *         - false : eee_ram not ready.
 *         - true  : eee_ram ready.
 */
extern bool FlashDrv_GetEeeRamRdy(FlashDrvType *obj);

/*! \brief Gets eee_ram protection property
 *
 * This function gets the eee_ram protection property
 *
 * \param[in] obj : pointer to Flash driver instancee
 * \param[out] protectStatus : pointer to protection status
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_GetEeeRamProtection(FlashDrvType *obj, uint8_t *protectstatus);

/*! \brief Gets PFlash protection property
 *
 * This function gets the PFlash protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] protectStatus0 : pointer to protection status
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 * \param[out] protectStatus1 : pointer to protection status
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_GetPFlashProtection(FlashDrvType *obj, uint32_t *protectstatus0, uint32_t *protectstatus1);

/*! \brief Gets DFlash protection property
 *
 * This function gets the DFlash protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] protectStatus : pointer to protection status
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_GetDFlashProtection(FlashDrvType *obj, uint16_t *protectstatus);

/*! \brief Gets secinforegion protection property
 *
 * This function gets the secinforegion protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] protectStatus : pointer to protection status
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_GetSecProtection(FlashDrvType *obj, uint8_t *protectstatus);

/*! \brief Sets secinforegion protection property
 *
 * This function gets the secinforegion protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] protectStatus : pointer to protection status
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_SetSecProtection(FlashDrvType *obj, uint8_t prctval);

/*! \brief Sets eee_ram protection property
 *
 * This function sets the eee_ram protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] prctval : protection value
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_SetEeeRamProtection(FlashDrvType *obj, uint8_t prctval);

/*! \brief Gets PFlash protection property
 *
 * This function gets the PFlash protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] prctval0 : protection setting value
 *                    - 0b : corresponding area is unprotect
 *                    - 1b : corresponding area is protect
 * \param[out] prctval1 : protection setting value
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_SetPFlashProtection(FlashDrvType *obj, uint32_t prctval0, uint32_t prctval1);

/*! \brief Sets DFlash protection property
 *
 * This function sets the DFlash protection property
 *
 * \param[in] obj : pointer to Flash driver instance
 * \param[out] prctval : protection setting value
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
extern FlashDrv_Status FlashDrv_SetDFlashProtection(FlashDrvType *obj, uint16_t prctval);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _FLASH_DRV_H_ */
