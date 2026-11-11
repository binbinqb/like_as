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

#ifndef _CSE_DRV_H_
#define _CSE_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of CSE
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup cse_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define KEY_SECTOR_START_ADD      (0x00101000UL)
#define CSE_PRV_CSE_RAM_START_ADD (0x14001000UL)
#define CSE_PRV_CPU_RAM_START_ADD (0x14000000UL)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief type for key length select
 */
typedef enum
{
    CSEDRV_KEY_LEN_128BIT, /*!< 128-bit key length */
    CSEDRV_KEY_LEN_192BIT, /*!< 192-bit key length */
    CSEDRV_KEY_LEN_256BIT, /*!< 256-bit key length */
} CseDrv_KeyLenType;

/*! \brief type for crypt / decrypt engine
 */
typedef enum
{
    CSEDRV_CRYPT_ENGINE_AES,  /*!< AES encrypt / decrypt engine */
    CSEDRV_CRYPT_ENGINE_HMAC, /*!< HMAC encrypt / decrypt engine */
    CSEDRV_CRYPT_ENGINE_SM4,  /*!< SM4 encrypt / decrypt engine */
} CseDrv_CryptEngineType;

/*! \brief type for CMAC subkey select
 */
typedef enum
{
    CSEDRV_SUBKEYSEL_K1, /*!< CMAC subkey K1 */
    CSEDRV_SUBKEYSEL_K2, /*!< CMAC subkey K2 */
} CseDrv_SubKeySelType;

/*! \brief type for operation mode
 */
typedef enum
{
    CSEDRV_OP_MODE_ECB,  /*!< ECB operation mode */
    CSEDRV_OP_MODE_CBC,  /*!< CBC operation mode */
    CSEDRV_OP_MODE_CMAC, /*!< CMAC operation mode */
    CSEDRV_OP_MODE_MP,   /*!< MP operaiton mode */
} CseDrv_OpModeType;

/*! \brief type for key index in key sector
 */
typedef enum
{
    CSEDRV_KEY_ID_MASTER_ECU_KEY, /*!< key index - ECU key, in key sector */
    CSEDRV_KEY_ID_BOOT_MAC_KEY,   /*!< key index - BOOT MAC key, in key sector */
    CSEDRV_KEY_ID_BOOT_MAC,       /*!< key index - BOOT MAC, in key sector */
    CSEDRV_KEY_ID_KEY01,          /*!< key index - user key 01, in key sector */
    CSEDRV_KEY_ID_KEY02,          /*!< key index - user key 02, in key sector */
    CSEDRV_KEY_ID_KEY03,          /*!< key index - user key 03, in key sector */
    CSEDRV_KEY_ID_KEY04,          /*!< key index - user key 04, in key sector */
    CSEDRV_KEY_ID_KEY05,          /*!< key index - user key 05, in key sector */
    CSEDRV_KEY_ID_KEY06,          /*!< key index - user key 06, in key sector */
    CSEDRV_KEY_ID_KEY07,          /*!< key index - user key 07, in key sector */
    CSEDRV_KEY_ID_KEY08,          /*!< key index - user key 08, in key sector */
    CSEDRV_KEY_ID_KEY09,          /*!< key index - user key 09, in key sector */
    CSEDRV_KEY_ID_KEY10,          /*!< key index - user key 10, in key sector */
    CSEDRV_KEY_ID_KEY11,          /*!< key index - user key 11, in key sector */
    CSEDRV_KEY_ID_KEY12,          /*!< key index - user key 12, in key sector */
    CSEDRV_KEY_ID_KEY13,          /*!< key index - user key 13, in key sector */
    CSEDRV_KEY_ID_KEY14,          /*!< key index - user key 14, in key sector */
    CSEDRV_KEY_ID_KEY15,          /*!< key index - user key 15, in key sector */
    CSEDRV_KEY_ID_KEY16,          /*!< key index - user key 16, in key sector */
    CSEDRV_KEY_ID_KEY17,          /*!< key index - user key 17, in key sector */
} CseDrv_KeyIdType;

/*! \brief type for key or input message endian
 */
typedef enum
{
    CSEDRV_ENDIAN_BIG,    /*!< Big endian */
    CSEDRV_ENDIAN_LITTLE, /*!< Little endian */
} CseDrv_EndianType;

/*! \brief type for key or input message load mode
 */
typedef enum
{
    CSEDRV_LOAD_MODE_CPU, /*!< CPU load mode */
    CSEDRV_LOAD_MODE_DMA, /*!< DMA load mode */
} CseDrv_LoadModeType;

/*! \brief CSE encrypt / decrypt operation configuration data structure
 *
 * This structure configures all the attributes for encrypt / decrypt operation
 */
typedef struct _CseDrv_CfgType_
{
    CseDrv_OpModeType      opMode;        /*!< encrypt / deccrypt operation mode (ECB or CBC) */
    CseDrv_CryptEngineType cryptEngine;   /*!< encrypt / decrypt engine (AES or SM4) */
    uint32_t               inputAddr;     /*!< input message address */
    uint32_t               inputLen;      /*!< input message length */
    CseDrv_EndianType      inputEndian;   /*!< input message endian (little or big) */
    CseDrv_LoadModeType    inputLoadMode; /*!< input load mode (DMA or CPU) */
    uint32_t               outputAddr;    /*!< output result address */
    uint32_t               keyAddr;       /*!< encrypt / decrypt key address */
    CseDrv_EndianType      keyEndian;     /*!< key endian (little or big) */
    CseDrv_KeyLenType      keyLen;        /*!< key length type */
    CseDrv_LoadModeType    keyLoadMode;   /*!< key load mode (DMA or CPU) */
    uint32_t               initVector[4]; /*!< init vector (only necessary in CBC mode) */
    bool                   isEncrypt;     /*!< encrypt or decrypt */
    bool                   intEnable;     /*!< enable crypt ready interrupt */
} CseDrv_CfgType;

/* Forward declaration of related register */
struct _CseRegType_;

/*! \brief The definition of CSE driver class
 */
typedef struct _CseDrvType_
{
    struct _CseRegType_ *cseReg; /*!< pointer to CSE register */
} CseDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the CSE driver module
 *
 * This function initializes CSE driver by setting the register
 * instances to it.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] cseReg : pointer to CSE register instance
 */
extern void CseDrv_Init(CseDrvType *obj, struct _CseRegType_ *cseReg);

/*! \brief Get key existance information for a specific key index in key sector
 *
 * This function get the key existance information for a specific key index
 * in key sector.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] keyId : key slot index in key secor
 * \return: key existance result
 *          - 0: key slot is empty
 *          - 1: key exist in the specified key slot
 */
extern bool CseDrv_IskeyExist(CseDrvType *obj, CseDrv_KeyIdType keyId);

/*! \brief Run a CMAC authentication operation
 *
 * This function run a CMAC authentication operaion with the user specified
 * CMAC informaion e.g. key, input message, data length etc. And get the CMAC
 * authentication result.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] keyAddr : CMAC key address
 * \param[in] inpDataAddr: input message address
 * \param[in] dataSize: input message data size
 * \param[in] refValAddr: reference CMAC value address
 * \param[in] oupResAddr: CMAC calculated output result address
 * \param[out] isAuthPass: result for CMAC authentication
 *
 */
extern void CseDrv_CMacHandler(CseDrvType *obj,
                               uint32_t    keyAddr,
                               uint32_t    inpDataAddr,
                               uint32_t    dataSize,
                               uint32_t    refValAddr,
                               uint32_t    oupResAddr,
                               bool       *isAuthPass);

/*! \brief Run a encrypt / decrypt operaion
 *
 * This function run a generic encrypt / decrypt operation with the specific
 * algorithm and operation mode specificed in cfg object.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] cfg : pointer to encrypt / decrypt configuration
 *
 */
extern void CseDrv_Operation(CseDrvType *obj, const CseDrv_CfgType *cfg);

/*! \brief Run a encrypt operation with ECB mode
 *
 * This function run a ECB mode encrypt operation with the specific algorithm
 * and related data specified in cfg objec.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] cfg : pointer to encrypt configuration
 *
 */
extern void CseDrv_EncryptEcb(CseDrvType *obj, CseDrv_CfgType *cfg);

/*! \brief Run a decrypt operation with ECB mode
 *
 * This function run a ECB mode decrypt operation with the specific algorithm
 * and related data specified in cfg objec.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] cfg : pointer to decrypt configuration
 *
 */
extern void CseDrv_DecryptEcb(CseDrvType *obj, CseDrv_CfgType *cfg);

/*! \brief Run a encrypt operation with CBC mode
 *
 * This function run a CBC mode encrypt operation with the specific algorithm
 * and related data specified in cfg objec.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] cfg : pointer to encrypt configuration
 *
 */
extern void CseDrv_EncryptCbc(CseDrvType *obj, CseDrv_CfgType *cfg);

/*! \brief Run a decrypt operation with CBC mode
 *
 * This function run a CBC mode decrypt operation with the specific algorithm
 * and related data specified in cfg objec.
 *
 * \param[in] obj : pointer to CSE driver instance
 * \param[in] cfg : pointer to decrypt configuration
 *
 */
extern void CseDrv_DecryptCbc(CseDrvType *obj, CseDrv_CfgType *cfg);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _CSE_DRV_H_ */
