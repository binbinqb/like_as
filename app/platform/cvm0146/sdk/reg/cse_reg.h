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

#ifndef _CSE_REG_H_
#define _CSE_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the CSE Registers
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 * the defines
 ******************************************************************************/

/* CTRL Bit Fields */
#define CSE_CTRL_SWRST_MASK                 (0x80000000u)
#define CSE_CTRL_SWRST_SHIFT                (31u)
#define CSE_CTRL_SWRST_WIDTH                (1u)
#define CSE_CTRL_CMACLOAD_MASK              (0x08u)
#define CSE_CTRL_CMACLOAD_SHIFT             (3u)
#define CSE_CTRL_CMACLOAD_WIDTH             (1u)
#define CSE_CTRL_KEYLOAD_MASK               (0x04u)
#define CSE_CTRL_KEYLOAD_SHIFT              (2u)
#define CSE_CTRL_KEYLOAD_WIDTH              (1u)
#define CSE_CTRL_DMA_EN_MASK                (0x02u)
#define CSE_CTRL_DMA_EN_SHIFT               (1u)
#define CSE_CTRL_DMA_EN_WIDTH               (1u)
#define CSE_CTRL_START_MASK                 (0x01u)
#define CSE_CTRL_START_SHIFT                (0u)
#define CSE_CTRL_START_WIDTH                (1u)

/* CFG Bit Fields */
#define CSE_CFG_CMAC_AUTH_MASK              (0x80u)
#define CSE_CFG_CMAC_AUTH_SHIFT             (7u)
#define CSE_CFG_CMAC_AUTH_WIDTH             (1u)
#define CSE_CFG_FINAL_MASK                  (0x40u)
#define CSE_CFG_FINAL_SHIFT                 (6u)
#define CSE_CFG_FINAL_WIDTH                 (1u)
#define CSE_CFG_ENDIAN_TXT_MASK             (0x20u)
#define CSE_CFG_ENDIAN_TXT_SHIFT            (5u)
#define CSE_CFG_ENDIAN_TXT_WIDTH            (1u)
#define CSE_CFG_ENDIAN_KEY_MASK             (0x10u)
#define CSE_CFG_ENDIAN_KEY_SHIFT            (4u)
#define CSE_CFG_ENDIAN_KEY_WIDTH            (1u)
#define CSE_CFG_ENGINE_MASK                 (0x03u)
#define CSE_CFG_ENGINE_SHIFT                (0u)
#define CSE_CFG_ENGINE_WIDTH                (2u)

/* DMACTRL Bit Fields */
#define CSE_DMACTRL_DMA_ERRSEL_MASK         (0x100000u)
#define CSE_DMACTRL_DMA_ERRSEL_SHIFT        (20u)
#define CSE_DMACTRL_DMA_ERRSEL_WIDTH        (1u)
#define CSE_DMACTRL_DMA_SIZE_MASK           (0xFFFFFu)
#define CSE_DMACTRL_DMA_SIZE_SHIFT          (0u)
#define CSE_DMACTRL_DMA_SIZE_WIDTH          (20u)

/* IRQEN Bit Fields */
#define CSE_IRQEN_IRQEN_SECERR_MASK         (0x800u)
#define CSE_IRQEN_IRQEN_SECERR_SHIFT        (11u)
#define CSE_IRQEN_IRQEN_SECERR_WIDTH        (1u)
#define CSE_IRQEN_IRQEN_DMAERR_MASK         (0x20u)
#define CSE_IRQEN_IRQEN_DMAERR_SHIFT        (5u)
#define CSE_IRQEN_IRQEN_DMAERR_WIDTH        (1u)
#define CSE_IRQEN_IRQEN_READY_MASK          (0x08u)
#define CSE_IRQEN_IRQEN_READY_SHIFT         (3u)
#define CSE_IRQEN_IRQEN_READY_WIDTH         (1u)

/* STATUS Bit Fields */
#define CSE_STATUS_SECRET_ERR_MASK          (0x800u)
#define CSE_STATUS_SECRET_ERR_SHIFT         (11u)
#define CSE_STATUS_SECRET_ERR_WIDTH         (1u)
#define CSE_STATUS_CMAC_OK_MASK             (0x400u)
#define CSE_STATUS_CMAC_OK_SHIFT            (10u)
#define CSE_STATUS_CMAC_OK_WIDTH            (1u)
#define CSE_STATUS_KEY_ILLEGAL_MASK         (0x200u)
#define CSE_STATUS_KEY_ILLEGAL_SHIFT        (9u)
#define CSE_STATUS_KEY_ILLEGAL_WIDTH        (1u)
#define CSE_STATUS_KEY_VALID_MASK           (0x100u)
#define CSE_STATUS_KEY_VALID_SHIFT          (8u)
#define CSE_STATUS_KEY_VALID_WIDTH          (1u)
#define CSE_STATUS_CMAC_VALID_MASK          (0x80u)
#define CSE_STATUS_CMAC_VALID_SHIFT         (7u)
#define CSE_STATUS_CMAC_VALID_WIDTH         (1u)
#define CSE_STATUS_DAT_ILLEGAL_MASK         (0x40u)
#define CSE_STATUS_DAT_ILLEGAL_SHIFT        (6u)
#define CSE_STATUS_DAT_ILLEGAL_WIDTH        (1u)
#define CSE_STATUS_DMA_TRANS_ERR_MASK       (0x20u)
#define CSE_STATUS_DMA_TRANS_ERR_SHIFT      (5u)
#define CSE_STATUS_DMA_TRANS_ERR_WIDTH      (1u)
#define CSE_STATUS_READY_MASK               (0x08u)
#define CSE_STATUS_READY_SHIFT              (3u)
#define CSE_STATUS_READY_WIDTH              (1u)
#define CSE_STATUS_DMA_TRANS_DONE_MASK      (0x02u)
#define CSE_STATUS_DMA_TRANS_DONE_SHIFT     (1u)
#define CSE_STATUS_DMA_TRANS_DONE_WIDTH     (1u)
#define CSE_STATUS_INT_MASK                 (0x01u)
#define CSE_STATUS_INT_SHIFT                (0u)
#define CSE_STATUS_INT_WIDTH                (1u)

/* RADDR Bit Fields */
#define CSE_RADDR_DMA_RADDR_MASK            (0xFFFFFFFFu)
#define CSE_RADDR_DMA_RADDR_SHIFT           (0u)
#define CSE_RADDR_DMA_RADDR_WIDTH           (32u)

/* WADDR Bit Fields */
#define CSE_WADDR_DMA_WADDR_MASK            (0xFFFFFFFFu)
#define CSE_WADDR_DMA_WADDR_SHIFT           (0u)
#define CSE_WADDR_DMA_WADDR_WIDTH           (32u)

/* KEY_ADDR Bit Fields */
#define CSE_KEY_ADDR_KEY_ADDR_MASK          (0xFFFFFFFFu)
#define CSE_KEY_ADDR_KEY_ADDR_SHIFT         (0u)
#define CSE_KEY_ADDR_KEY_ADDR_WIDTH         (32u)

/* CMAC_ADDR Bit Fields */
#define CSE_CMAC_ADDR_CMAC_ADDR_MASK        (0xFFFFFFFFu)
#define CSE_CMAC_ADDR_CMAC_ADDR_SHIFT       (0u)
#define CSE_CMAC_ADDR_CMAC_ADDR_WIDTH       (32u)

/* KEYCFG Bit Fields */
#define CSE_KEYCFG_KEY_MASK                 (0xFFFFFFFFu)
#define CSE_KEYCFG_KEY_SHIFT                (0u)
#define CSE_KEYCFG_KEY_WIDTH                (32u)

/* MESSAGE Bit Fields */
#define CSE_MESSAGE_MESSAGE_MASK            (0xFFFFFFFFu)
#define CSE_MESSAGE_MESSAGE_SHIFT           (0u)
#define CSE_MESSAGE_MESSAGE_WIDTH           (32u)

/* DATAO Bit Fields */
#define CSE_DATAO_DATAO_MASK                (0xFFFFFFFFu)
#define CSE_DATAO_DATAO_SHIFT               (0u)
#define CSE_DATAO_DATAO_WIDTH               (32u)

/* SYMMCFG Bit Fields */
#define CSE_SYMMCFG_CMAC_RESULT_MASK        (0x80000u)
#define CSE_SYMMCFG_CMAC_RESULT_SHIFT       (19u)
#define CSE_SYMMCFG_CMAC_RESULT_WIDTH       (1u)
#define CSE_SYMMCFG_CMAC_SK_SEL_MASK        (0x40000u)
#define CSE_SYMMCFG_CMAC_SK_SEL_SHIFT       (18u)
#define CSE_SYMMCFG_CMAC_SK_SEL_WIDTH       (1u)
#define CSE_SYMMCFG_CMAC_SK_GEN_MASK        (0x20000u)
#define CSE_SYMMCFG_CMAC_SK_GEN_SHIFT       (17u)
#define CSE_SYMMCFG_CMAC_SK_GEN_WIDTH       (1u)
#define CSE_SYMMCFG_OPMODE_MASK             (0x70u)
#define CSE_SYMMCFG_OPMODE_SHIFT            (4u)
#define CSE_SYMMCFG_OPMODE_WIDTH            (3u)
#define CSE_SYMMCFG_ENC_MASK                (0x04u)
#define CSE_SYMMCFG_ENC_SHIFT               (2u)
#define CSE_SYMMCFG_ENC_WIDTH               (1u)
#define CSE_SYMMCFG_KEY_MODE_MASK           (0x03u)
#define CSE_SYMMCFG_KEY_MODE_SHIFT          (0u)
#define CSE_SYMMCFG_KEY_MODE_WIDTH          (2u)

/* SYMMIV0 Bit Fields */
#define CSE_SYMMIV0_IV0_MASK                (0xFFFFFFFFu)
#define CSE_SYMMIV0_IV0_SHIFT               (0u)
#define CSE_SYMMIV0_IV0_WIDTH               (32u)

/* SYMMIV1 Bit Fields */
#define CSE_SYMMIV1_IV1_MASK                (0xFFFFFFFFu)
#define CSE_SYMMIV1_IV1_SHIFT               (0u)
#define CSE_SYMMIV1_IV1_WIDTH               (32u)

/* SYMMIV2 Bit Fields */
#define CSE_SYMMIV2_IV2_MASK                (0xFFFFFFFFu)
#define CSE_SYMMIV2_IV2_SHIFT               (0u)
#define CSE_SYMMIV2_IV2_WIDTH               (32u)

/* SYMMIV3 Bit Fields */
#define CSE_SYMMIV3_IV3_MASK                (0xFFFFFFFFu)
#define CSE_SYMMIV3_IV3_SHIFT               (0u)
#define CSE_SYMMIV3_IV3_WIDTH               (32u)

/* KEYSECT Bit Fields */
#define CSE_KEYSECT_KEY_EXI_MASK            (0xFFFFF000u)
#define CSE_KEYSECT_KEY_EXI_SHIFT           (12u)
#define CSE_KEYSECT_KEY_EXI_WIDTH           (20u)
#define CSE_KEYSECT_KEY_IDERR_MASK          (0x02u)
#define CSE_KEYSECT_KEY_IDERR_SHIFT         (1u)
#define CSE_KEYSECT_KEY_IDERR_WIDTH         (1u)
#define CSE_KEYSECT_KEY_ANA_MASK            (0x01u)
#define CSE_KEYSECT_KEY_ANA_SHIFT           (0u)
#define CSE_KEYSECT_KEY_ANA_WIDTH           (1u)

/* LOCK Bit Fields */
#define CSE_LOCK_BOOT_PROT_MASK             (0xFFFFF000u)
#define CSE_LOCK_BOOT_PROT_SHIFT            (12u)
#define CSE_LOCK_BOOT_PROT_WIDTH            (20u)
#define CSE_LOCK_BOOT_LOCK_MASK             (0x01u)
#define CSE_LOCK_BOOT_LOCK_SHIFT            (0u)
#define CSE_LOCK_BOOT_LOCK_WIDTH            (1u)

/* KEY Bit Fields */
#define CSE_KEY_KEY_SECRET_MASK             (0x01u)
#define CSE_KEY_KEY_SECRET_SHIFT            (0u)
#define CSE_KEY_KEY_SECRET_WIDTH            (1u)


/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of CSE registers
 */
typedef struct _CseRegType_
{
    volatile uint32_t       CTRL;               /*!< control register, offset: 0000H */
    volatile uint32_t       CFG;                /*!< config register, offset: 0004H */
    volatile uint32_t       DMACTRL;            /*!< DMA control register, offset: 0008H */
    volatile uint32_t       IRQEN;              /*!< irq enable register, offset: 000CH */
    volatile uint32_t       STATUS;             /*!< status register, offset: 0010H */
    volatile uint32_t       RADDR;              /*!< read address register, offset: 0014H */
    volatile uint32_t       WADDR;              /*!< write address register, offset: 0018H */
    volatile uint32_t       KEY_ADDR;           /*!< key address register, offset: 001CH */
    volatile uint32_t       CMAC_ADDR;          /*!< CMAC address register, offset: 0020H */
    volatile uint32_t       KEYCFG;             /*!< key config register, offset: 0024H */
    volatile uint32_t       MESSAGE;            /*!< message register, offset: 0028H */
    const volatile uint32_t DATAO;              /*!< data out register, offset: 002CH */
    uint32_t                RESERVED0[116];     /*!< Reserverd block, offset: 0030H */
    volatile uint32_t       SYMMCFG;            /*!< symmetric config register, offset: 0200H */
    uint32_t                RESERVED1[3];       /*!< Reserverd block, offset: 0204H */
    volatile uint32_t       SYMMIV0;            /*!< symmetric initial vector 0 register, offset: 0210H */
    volatile uint32_t       SYMMIV1;            /*!< symmetric initial vector 1 register, offset: 0214H */
    volatile uint32_t       SYMMIV2;            /*!< symmetric initial vector 2 register, offset: 0218H */
    volatile uint32_t       SYMMIV3;            /*!< symmetric initial vector 3 register, offset: 021CH */
    uint32_t                RESERVED2[121];     /*!< Reserverd block, offset: 0220H */
    volatile uint32_t       KEYSECT;            /*!< CSE key sector register, offset: 0404H */
    volatile uint32_t       LOCK;               /*!< CSE lock register, offset: 0408H */
    volatile uint32_t       KEY;                /*!< CSE key register, offset: 040CH */
}CseRegType;


/*******************************************************************************
 * the globals
 ******************************************************************************/


/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the software reset
 *
 * This function gets the current software reset.
 * Reset all logics except registers
 *
 * \param[in] this : pointer to CSE register instance
 * \return software reset
 *         - 1b : Module is reset
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCtrlSwRst(const CseRegType *this)
{
    return ((this->CTRL & CSE_CTRL_SWRST_MASK) >> CSE_CTRL_SWRST_SHIFT);
}

/*! \brief Sets the software reset
 *
 * This function sets the software reset.
 * Reset all logics except registers
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of software reset
 *                    - 1b : Module is reset
 */
__attribute__((always_inline)) static inline void CseReg_SetCtrlSwRst(CseRegType *this)
{
    uint32_t tmp = this->CTRL;
    tmp &= ~CSE_CTRL_SWRST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1UL)) << CSE_CTRL_SWRST_SHIFT)) & CSE_CTRL_SWRST_MASK);
    this->CTRL = tmp;
}

/*! \brief Gets the CMAC_REF load
 *
 * This function gets the current CMAC_REF load.
 *
 * \param[in] this : pointer to CSE register instance
 * \return CMAC_REF load
 *         - 1b : load CMAC_REF enable
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCMacLoadEnable(const CseRegType *this)
{
    return ((this->CTRL & CSE_CTRL_CMACLOAD_MASK) >> CSE_CTRL_CMACLOAD_SHIFT);
}

/*! \brief Sets the CMAC_REF load
 *
 * This function sets the CMAC_REF load.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of CMAC_REF load
 *                    - 1b : load CMAC_REF enable
 */
__attribute__((always_inline)) static inline void CseReg_SetCMacLoadEnable(CseRegType *this, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = this->CTRL;
    tmp &= ~CSE_CTRL_CMACLOAD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CTRL_CMACLOAD_SHIFT)) & CSE_CTRL_CMACLOAD_MASK);
    this->CTRL = tmp;
}

/*! \brief Gets the key load
 *
 * This function gets the current key load.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key load
 *         - 1b : load key enable
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCtrlKeyLoad(const CseRegType *this)
{
    return ((this->CTRL & CSE_CTRL_KEYLOAD_MASK) >> CSE_CTRL_KEYLOAD_SHIFT);
}

/*! \brief Sets the key load
 *
 * This function sets the key load.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of key load
 *                    - 1b : load key enable
 */
__attribute__((always_inline)) static inline void CseReg_SetCtrlKeyLoad(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CTRL;
    tmp &= ~CSE_CTRL_KEYLOAD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CTRL_KEYLOAD_SHIFT)) & CSE_CTRL_KEYLOAD_MASK);
    this->CTRL = tmp;
}

/*! \brief Gets the DMA enable
 *
 * This function gets the current DMA enable.
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA enable
 *         - 0b : CPU mode
 *         - 1b : DMA mode
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCtrlDmaEn(const CseRegType *this)
{
    return ((this->CTRL & CSE_CTRL_DMA_EN_MASK) >> CSE_CTRL_DMA_EN_SHIFT);
}

/*! \brief Sets the DMA enable
 *
 * This function sets the DMA enable.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of DMA enable
 *                    - 0b : CPU mode
 *                    - 1b : DMA mode
 */
__attribute__((always_inline)) static inline void CseReg_SetCtrlDmaEn(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CTRL;

    tmp &= ~CSE_CTRL_DMA_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CTRL_DMA_EN_SHIFT)) & CSE_CTRL_DMA_EN_MASK);
    this->CTRL = tmp;
}

/*! \brief Gets the start
 *
 * This function gets the current start.
 *
 * \param[in] this : pointer to CSE register instance
 * \return start
 *         - 1b : crypt start
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCtrlStart(const CseRegType *this)
{
    return ((this->CTRL & CSE_CTRL_START_MASK) >> CSE_CTRL_START_SHIFT);
}

/*! \brief Sets the start
 *
 * This function sets the start.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of start
 *                    - 1b : crypt start
 */
__attribute__((always_inline)) static inline void CseReg_SetCtrlStart(CseRegType *this, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = this->CTRL;
    tmp &= ~CSE_CTRL_START_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CTRL_START_SHIFT)) & CSE_CTRL_START_MASK);
    this->CTRL = tmp;
}

/*! \brief Gets the CMAC authentication
 *
 * This function gets the current CMAC authentication.
 *
 * \param[in] this : pointer to CSE register instance
 * \return CMAC authentication
 *         - 0b : authentication disable when CMAC calculation
 *         - 1b : authentication enable when CMAC calculation
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCMacAuthEnable(const CseRegType *this)
{
    return ((this->CFG & CSE_CFG_CMAC_AUTH_MASK) >> CSE_CFG_CMAC_AUTH_SHIFT);
}

/*! \brief Sets the CMAC authentication
 *
 * This function sets the CMAC authentication.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of CMAC authentication
 *                    - 0b : authentication disable when CMAC calculation
 *                    - 1b : authentication enable when CMAC calculation
 */
__attribute__((always_inline)) static inline void CseReg_SetCMacAuthEnable(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CFG;

    tmp &= ~CSE_CFG_CMAC_AUTH_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CFG_CMAC_AUTH_SHIFT)) & CSE_CFG_CMAC_AUTH_MASK);
    this->CFG = tmp;
}

/*! \brief Gets the final
 *
 * This function gets the current final.
 *
 * \param[in] this : pointer to CSE register instance
 * \return final
 *         - 0b : NOT final message
 *         - 1b : final message
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCfgFinal(const CseRegType *this)
{
    return ((this->CFG & CSE_CFG_FINAL_MASK) >> CSE_CFG_FINAL_SHIFT);
}

/*! \brief Sets the final
 *
 * This function sets the final.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of final
 *                    - 0b : NOT final message
 *                    - 1b : final message
 */
__attribute__((always_inline)) static inline void CseReg_SetCfgFinal(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CFG;

    tmp &= ~CSE_CFG_FINAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CFG_FINAL_SHIFT)) & CSE_CFG_FINAL_MASK);
    this->CFG = tmp;
}

/*! \brief Gets the endian text
 *
 * This function gets the current endian text.
 *
 * \param[in] this : pointer to CSE register instance
 * \return endian text
 *         - 0b : big endian
 *         - 1b : little endian
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCfgEndianTxt(const CseRegType *this)
{
    return ((this->CFG & CSE_CFG_ENDIAN_TXT_MASK) >> CSE_CFG_ENDIAN_TXT_SHIFT);
}

/*! \brief Sets the endian text
 *
 * This function sets the endian text.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of endian text
 *                    - 0b : big endian
 *                    - 1b : little endian
 */
__attribute__((always_inline)) static inline void CseReg_SetTextEndian(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CFG;

    tmp &= ~CSE_CFG_ENDIAN_TXT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CFG_ENDIAN_TXT_SHIFT)) & CSE_CFG_ENDIAN_TXT_MASK);
    this->CFG = tmp;
}

/*! \brief Gets the endian key
 *
 * This function gets the current endian key.
 *
 * \param[in] this : pointer to CSE register instance
 * \return endian key
 *         - 0b : big endian
 *         - 1b : little endian
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCfgEndianKey(const CseRegType *this)
{
    return ((this->CFG & CSE_CFG_ENDIAN_KEY_MASK) >> CSE_CFG_ENDIAN_KEY_SHIFT);
}

/*! \brief Sets the endian key
 *
 * This function sets the endian key.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of endian key
 *                    - 0b : big endian
 *                    - 1b : little endian
 */
__attribute__((always_inline)) static inline void CseReg_SetKeyEndian(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CFG;

    tmp &= ~CSE_CFG_ENDIAN_KEY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CFG_ENDIAN_KEY_SHIFT)) & CSE_CFG_ENDIAN_KEY_MASK);
    this->CFG = tmp;
}

/*! \brief Gets the engine
 *
 * This function gets the current engine.
 *
 * \param[in] this : pointer to CSE register instance
 * \return engine
 *         - 00b : AES
 *         - 01b : HMAC
 *         - 10b : SM4
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCfgEngine(const CseRegType *this)
{
    return ((this->CFG & CSE_CFG_ENGINE_MASK) >> CSE_CFG_ENGINE_SHIFT);
}

/*! \brief Sets the engine
 *
 * This function sets the engine.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of engine
 *                    - 00b : AES
 *                    - 01b : HMAC
 *                    - 10b : SM4
 */
__attribute__((always_inline)) static inline void CseReg_SetCryptEngine(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->CFG;

    tmp &= ~CSE_CFG_ENGINE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CFG_ENGINE_SHIFT)) & CSE_CFG_ENGINE_MASK);
    this->CFG = tmp;
}

/*! \brief Gets the DMA error selection
 *
 * This function gets the current DMA error selection.
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA error selection
 *         - 0b : bus error interrupt, and terminate current transfer
 *         - 1b : bus error interrupt, and transfer continue until thewhole transfer done
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetDmaCtrlDmaErrSel(const CseRegType *this)
{
    return ((this->DMACTRL & CSE_DMACTRL_DMA_ERRSEL_MASK) >> CSE_DMACTRL_DMA_ERRSEL_SHIFT);
}

/*! \brief Sets the DMA error selection
 *
 * This function sets the DMA error selection.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of DMA error selection
 *                    - 0b : bus error interrupt, and terminate current transfer
 *                    - 1b : bus error interrupt, and transfer continue until thewhole transfer done
 */
__attribute__((always_inline)) static inline void CseReg_SetDmaCtrlDmaErrSel(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->DMACTRL;

    tmp &= ~CSE_DMACTRL_DMA_ERRSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_DMACTRL_DMA_ERRSEL_SHIFT)) & CSE_DMACTRL_DMA_ERRSEL_MASK);
    this->DMACTRL = tmp;
}

/*! \brief Gets the DMA size
 *
 * This function gets the current DMA size.
 * the unit is byt
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA size
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetDmaSize(const CseRegType *this)
{
    return ((this->DMACTRL & CSE_DMACTRL_DMA_SIZE_MASK) >> CSE_DMACTRL_DMA_SIZE_SHIFT);
}

/*! \brief Sets the DMA size
 *
 * This function sets the DMA size.
 * the unit is byt
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of DMA size
 */
__attribute__((always_inline)) static inline void CseReg_SetDmaSize(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->DMACTRL;

    tmp &= ~CSE_DMACTRL_DMA_SIZE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_DMACTRL_DMA_SIZE_SHIFT)) & CSE_DMACTRL_DMA_SIZE_MASK);
    this->DMACTRL = tmp;
}

/*! \brief Gets the interrupt enable for CSE_STATUS[CSE_SECRET_ERR]
 *
 * This function gets the current interrupt enable for CSE_STATUS[CSE_SECRET_ERR].
 *
 * \param[in] this : pointer to CSE register instance
 * \return interrupt enable for CSE_STATUS[CSE_SECRET_ERR]
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetIrqEnIrqEnSecErr(const CseRegType *this)
{
    return ((this->IRQEN & CSE_IRQEN_IRQEN_SECERR_MASK) >> CSE_IRQEN_IRQEN_SECERR_SHIFT);
}

/*! \brief Sets the interrupt enable for CSE_STATUS[CSE_SECRET_ERR]
 *
 * This function sets the interrupt enable for CSE_STATUS[CSE_SECRET_ERR].
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of interrupt enable for CSE_STATUS[CSE_SECRET_ERR]
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void CseReg_SetIrqEnIrqEnSecErr(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->IRQEN;

    tmp &= ~CSE_IRQEN_IRQEN_SECERR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_IRQEN_IRQEN_SECERR_SHIFT)) & CSE_IRQEN_IRQEN_SECERR_MASK);
    this->IRQEN = tmp;
}

/*! \brief Gets the interrupt enable for CSE_STATUS[DMA_TRANS_ERR]
 *
 * This function gets the current interrupt enable for CSE_STATUS[DMA_TRANS_ERR].
 *
 * \param[in] this : pointer to CSE register instance
 * \return interrupt enable for CSE_STATUS[DMA_TRANS_ERR]
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetIrqEnIrqEnDmaErr(const CseRegType *this)
{
    return ((this->IRQEN & CSE_IRQEN_IRQEN_DMAERR_MASK) >> CSE_IRQEN_IRQEN_DMAERR_SHIFT);
}

/*! \brief Sets the interrupt enable for CSE_STATUS[DMA_TRANS_ERR]
 *
 * This function sets the interrupt enable for CSE_STATUS[DMA_TRANS_ERR].
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of interrupt enable for CSE_STATUS[DMA_TRANS_ERR]
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void CseReg_SetIrqEnIrqEnDmaErr(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->IRQEN;

    tmp &= ~CSE_IRQEN_IRQEN_DMAERR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_IRQEN_IRQEN_DMAERR_SHIFT)) & CSE_IRQEN_IRQEN_DMAERR_MASK);
    this->IRQEN = tmp;
}

/*! \brief Gets the interrupt enable for CSE_STATUS[READY]
 *
 * This function gets the current interrupt enable for CSE_STATUS[READY].
 *
 * \param[in] this : pointer to CSE register instance
 * \return interrupt enable for CSE_STATUS[READY]
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetIrqEnReady(const CseRegType *this)
{
    return ((this->IRQEN & CSE_IRQEN_IRQEN_READY_MASK) >> CSE_IRQEN_IRQEN_READY_SHIFT);
}

/*! \brief Sets the interrupt enable for CSE_STATUS[READY]
 *
 * This function sets the interrupt enable for CSE_STATUS[READY].
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of interrupt enable for CSE_STATUS[READY]
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void CseReg_SetIrqEnReady(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->IRQEN;

    tmp &= ~CSE_IRQEN_IRQEN_READY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_IRQEN_IRQEN_READY_SHIFT)) & CSE_IRQEN_IRQEN_READY_MASK);
    this->IRQEN = tmp;
}

/*! \brief Gets the SECRET_KEY error
 *
 * This function gets the current SECRET_KEY error.
 *
 * \param[in] this : pointer to CSE register instance
 * \return SECRET_KEY error
 *         - 0b : status not detected
 *         - 1b : status detected
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusSecretErr(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_SECRET_ERR_MASK) >> CSE_STATUS_SECRET_ERR_SHIFT);
}

/*! \brief Sets the SECRET_KEY error
 *
 * This function sets the SECRET_KEY error.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of SECRET_KEY error
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void CseReg_SetStatusSecretErr(CseRegType *this, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_STATUS_SECRET_ERR_SHIFT)) & CSE_STATUS_SECRET_ERR_MASK);
    this->STATUS = tmp;
}

/*! \brief Gets the crypt CMAC ok
 *
 * This function gets the current crypt CMAC ok.
 *
 * \param[in] this : pointer to CSE register instance
 * \return crypt CMAC ok
 *         - 0b : FAIL
 *         - 1b : PASS
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCMacOkStatus(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_CMAC_OK_MASK) >> CSE_STATUS_CMAC_OK_SHIFT);
}

/*! \brief Gets the cryptkey illegal
 *
 * This function gets the current cryptkey illegal.
 *
 * \param[in] this : pointer to CSE register instance
 * \return cryptkey illegal
 *         - 0b : legal
 *         - 1b : illegal
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusKeyillegal(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_KEY_ILLEGAL_MASK) >> CSE_STATUS_KEY_ILLEGAL_SHIFT);
}

/*! \brief Gets the crypt key valid
 *
 * This function gets the current crypt key valid.
 *
 * \param[in] this : pointer to CSE register instance
 * \return crypt key valid
 *         - 0b : not done
 *         - 1b : done
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetKeyValidStatus(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_KEY_VALID_MASK) >> CSE_STATUS_KEY_VALID_SHIFT);
}

/*! \brief Gets the crypt CMAC valid
 *
 * This function gets the current crypt CMAC valid.
 *
 * \param[in] this : pointer to CSE register instance
 * \return crypt CMAC valid
 *         - 0b : not done
 *         - 1b : done
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusCMacValid(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_CMAC_VALID_MASK) >> CSE_STATUS_CMAC_VALID_SHIFT);
}

/*! \brief Gets the crypt data illegal
 *
 * This function gets the current crypt data illegal.
 *
 * \param[in] this : pointer to CSE register instance
 * \return crypt data illegal
 *         - 0b : legal
 *         - 1b : illegal
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetDataIllegalStatus(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_DAT_ILLEGAL_MASK) >> CSE_STATUS_DAT_ILLEGAL_SHIFT);
}

/*! \brief Gets the DMA transfer error
 *
 * This function gets the current DMA transfer error.
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA transfer error
 *         - 0b : status not detected
 *         - 1b : status detected
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusDmaTransErr(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_DMA_TRANS_ERR_MASK) >> CSE_STATUS_DMA_TRANS_ERR_SHIFT);
}

/*! \brief Sets the DMA transfer error
 *
 * This function sets the DMA transfer error.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of DMA transfer error
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void CseReg_SetStatusDmaTransErr(CseRegType *this, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_STATUS_DMA_TRANS_ERR_SHIFT)) & CSE_STATUS_DMA_TRANS_ERR_MASK);
    this->STATUS = tmp;
}

/*! \brief Gets the ready
 *
 * This function gets the current ready.
 *
 * \param[in] this : pointer to CSE register instance
 * \return ready
 *         - 0b : not ready
 *         - 1b : ready
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusReady(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_READY_MASK) >> CSE_STATUS_READY_SHIFT);
}

/*! \brief Sets the ready
 *
 * This function sets the ready.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of ready
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void CseReg_ClearStatusReady(CseRegType *this)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(1UL)) << CSE_STATUS_READY_SHIFT)) & CSE_STATUS_READY_MASK);
    this->STATUS = tmp;
}

/*! \brief Gets the DMA transfer done
 *
 * This function gets the current DMA transfer done.
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA transfer done
 *         - 0b : not done
 *         - 1b : done
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusDmaTransDone(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_DMA_TRANS_DONE_MASK) >> CSE_STATUS_DMA_TRANS_DONE_SHIFT);
}

/*! \brief Gets the interrupt
 *
 * This function gets the current interrupt.
 *
 * \param[in] this : pointer to CSE register instance
 * \return interrupt
 *         - 0b : no interrupt report to CPU
 *         - 1b : interrupt report to CPU
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetStatusInt(const CseRegType *this)
{
    return ((this->STATUS & CSE_STATUS_INT_MASK) >> CSE_STATUS_INT_SHIFT);
}

/*! \brief Gets the DMA read address
 *
 * This function gets the current DMA read address.
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA read address
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetDmaRAddr(const CseRegType *this)
{
    return ((this->RADDR & CSE_RADDR_DMA_RADDR_MASK) >> CSE_RADDR_DMA_RADDR_SHIFT);
}

/*! \brief Sets the DMA read address
 *
 * This function sets the DMA read address.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of DMA read address
 */
__attribute__((always_inline)) static inline void CseReg_SetDmaRAddr(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->RADDR;

    tmp &= ~CSE_RADDR_DMA_RADDR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_RADDR_DMA_RADDR_SHIFT)) & CSE_RADDR_DMA_RADDR_MASK);
    this->RADDR = tmp;
}

/*! \brief Gets the DMA write address
 *
 * This function gets the current DMA write address.
 *
 * \param[in] this : pointer to CSE register instance
 * \return DMA write address
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetDmaWAddr(const CseRegType *this)
{
    return ((this->WADDR & CSE_WADDR_DMA_WADDR_MASK) >> CSE_WADDR_DMA_WADDR_SHIFT);
}

/*! \brief Sets the DMA write address
 *
 * This function sets the DMA write address.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of DMA write address
 */
__attribute__((always_inline)) static inline void CseReg_SetDmaWAddr(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->WADDR;

    tmp &= ~CSE_WADDR_DMA_WADDR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_WADDR_DMA_WADDR_SHIFT)) & CSE_WADDR_DMA_WADDR_MASK);
    this->WADDR = tmp;
}

/*! \brief Gets the key region address
 *
 * This function gets the current key region address.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key region address
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetKeyAddr(const CseRegType *this)
{
    return ((this->KEY_ADDR & CSE_KEY_ADDR_KEY_ADDR_MASK) >> CSE_KEY_ADDR_KEY_ADDR_SHIFT);
}

/*! \brief Sets the key region address
 *
 * This function sets the key region address.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of key region address
 */
__attribute__((always_inline)) static inline void CseReg_SetKeyAddr(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->KEY_ADDR;

    tmp &= ~CSE_KEY_ADDR_KEY_ADDR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_KEY_ADDR_KEY_ADDR_SHIFT)) & CSE_KEY_ADDR_KEY_ADDR_MASK);
    this->KEY_ADDR = tmp;
}

/*! \brief Gets the CMAC_REF start address
 *
 * This function gets the current CMAC_REF start address.
 *
 * \param[in] this : pointer to CSE register instance
 * \return CMAC_REF start address
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetCMacAddr(const CseRegType *this)
{
    return ((this->CMAC_ADDR & CSE_CMAC_ADDR_CMAC_ADDR_MASK) >> CSE_CMAC_ADDR_CMAC_ADDR_SHIFT);
}

/*! \brief Sets the CMAC_REF start address
 *
 * This function sets the CMAC_REF start address.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of CMAC_REF start address
 */
__attribute__((always_inline)) static inline void CseReg_SetCMacAddr(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->CMAC_ADDR;

    tmp &= ~CSE_CMAC_ADDR_CMAC_ADDR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_CMAC_ADDR_CMAC_ADDR_SHIFT)) & CSE_CMAC_ADDR_CMAC_ADDR_MASK);
    this->CMAC_ADDR = tmp;
}

/*! \brief Sets the key
 *
 * This function sets the key.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of key
 */
__attribute__((always_inline)) static inline void CseReg_SetKey(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->KEYCFG;

    tmp &= ~CSE_KEYCFG_KEY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_KEYCFG_KEY_SHIFT)) & CSE_KEYCFG_KEY_MASK);
    this->KEYCFG = tmp;
}

/*! \brief Sets the message
 *
 * This function sets the message.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of message
 */
__attribute__((always_inline)) static inline void CseReg_SetMessage(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->MESSAGE;

    tmp &= ~CSE_MESSAGE_MESSAGE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_MESSAGE_MESSAGE_SHIFT)) & CSE_MESSAGE_MESSAGE_MASK);
    this->MESSAGE = tmp;
}

/*! \brief Gets the data output
 *
 * This function gets the current data output.
 *
 * \param[in] this : pointer to CSE register instance
 * \return data output
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetDataOutput(const CseRegType *this)
{
    return ((this->DATAO & CSE_DATAO_DATAO_MASK) >> CSE_DATAO_DATAO_SHIFT);
}

/*! \brief Gets the CMAC result
 *
 * This function gets the current CMAC result.
 *
 * \param[in] this : pointer to CSE register instance
 * \return CMAC result
 *         - 0b : not send out
 *         - 1b : send out
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetCMacResultOutEnable(const CseRegType *this)
{
    return ((this->SYMMCFG & CSE_SYMMCFG_CMAC_RESULT_MASK) >> CSE_SYMMCFG_CMAC_RESULT_SHIFT);
}

/*! \brief Sets the CMAC result
 *
 * This function sets the CMAC result.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of CMAC result
 *                    - 0b : not send out
 *                    - 1b : send out
 */
__attribute__((always_inline)) static inline void CseReg_SetCMacResultOutEnable(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->SYMMCFG;

    tmp &= ~CSE_SYMMCFG_CMAC_RESULT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMCFG_CMAC_RESULT_SHIFT)) & CSE_SYMMCFG_CMAC_RESULT_MASK);
    this->SYMMCFG = tmp;
}

/*! \brief Gets the CMAC subkey selection
 *
 * This function gets the current CMAC subkey selection.
 *
 * \param[in] this : pointer to CSE register instance
 * \return CMAC subkey selection
 *         - 0b : use K1 as subkey
 *         - 1b : use K2 as subkey
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetSymmCfgCMacSkSel(const CseRegType *this)
{
    return ((this->SYMMCFG & CSE_SYMMCFG_CMAC_SK_SEL_MASK) >> CSE_SYMMCFG_CMAC_SK_SEL_SHIFT);
}

/*! \brief Sets the CMAC subkey selection
 *
 * This function sets the CMAC subkey selection.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of CMAC subkey selection
 *                    - 0b : use K1 as subkey
 *                    - 1b : use K2 as subkey
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmCfgCMacSkSel(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->SYMMCFG;

    tmp &= ~CSE_SYMMCFG_CMAC_SK_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMCFG_CMAC_SK_SEL_SHIFT)) & CSE_SYMMCFG_CMAC_SK_SEL_MASK);
    this->SYMMCFG = tmp;
}

/*! \brief Gets the CMAC subkey generate
 *
 * This function gets the current CMAC subkey generate.
 *
 * \param[in] this : pointer to CSE register instance
 * \return CMAC subkey generate
 *         - 0b : disable
 *         - 1b : enable CMAC subkey generation
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetSymmCfgCMacSkGen(const CseRegType *this)
{
    return ((this->SYMMCFG & CSE_SYMMCFG_CMAC_SK_GEN_MASK) >> CSE_SYMMCFG_CMAC_SK_GEN_SHIFT);
}

/*! \brief Sets the CMAC subkey generate
 *
 * This function sets the CMAC subkey generate.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of CMAC subkey generate
 *                    - 0b : disable
 *                    - 1b : enable CMAC subkey generation
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmCfgCMacSkGen(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->SYMMCFG;

    tmp &= ~CSE_SYMMCFG_CMAC_SK_GEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMCFG_CMAC_SK_GEN_SHIFT)) & CSE_SYMMCFG_CMAC_SK_GEN_MASK);
    this->SYMMCFG = tmp;
}

/*! \brief Gets the operation mode
 *
 * This function gets the current operation mode.
 *
 * \param[in] this : pointer to CSE register instance
 * \return operation mode
 *         - 0h : ECB mode
 *         - 1h : CBC mode
 *         - 2h : MAC mode
 *         - 3h : MP mode
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetOpMode(const CseRegType *this)
{
    return ((this->SYMMCFG & CSE_SYMMCFG_OPMODE_MASK) >> CSE_SYMMCFG_OPMODE_SHIFT);
}

/*! \brief Sets the operation mode
 *
 * This function sets the operation mode.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of operation mode
 *                    - 0h : ECB mode
 *                    - 1h : CBC mode
 *                    - 2h : MAC mode
 *                    - 3h : MP mode
 */
__attribute__((always_inline)) static inline void CseReg_SetOpMode(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->SYMMCFG;

    tmp &= ~CSE_SYMMCFG_OPMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMCFG_OPMODE_SHIFT)) & CSE_SYMMCFG_OPMODE_MASK);
    this->SYMMCFG = tmp;
}

/*! \brief Gets the encryption
 *
 * This function gets the current encryption.
 *
 * \param[in] this : pointer to CSE register instance
 * \return encryption
 *         - 0b : decryption
 *         - 1b : encryption
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetSymmCfgEnc(const CseRegType *this)
{
    return ((this->SYMMCFG & CSE_SYMMCFG_ENC_MASK) >> CSE_SYMMCFG_ENC_SHIFT);
}

/*! \brief Sets the encryption
 *
 * This function sets the encryption.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of encryption
 *                    - 0b : decryption
 *                    - 1b : encryption
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmCfgEnc(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->SYMMCFG;

    tmp &= ~CSE_SYMMCFG_ENC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMCFG_ENC_SHIFT)) & CSE_SYMMCFG_ENC_MASK);
    this->SYMMCFG = tmp;
}

/*! \brief Gets the key mode
 *
 * This function gets the current key mode.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key mode
 *         - 00b : 128 bits
 *         - 01b : 192 bits
 *         - 10b : 256 bits
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetSymmCfgKeyMode(const CseRegType *this)
{
    return ((this->SYMMCFG & CSE_SYMMCFG_KEY_MODE_MASK) >> CSE_SYMMCFG_KEY_MODE_SHIFT);
}

/*! \brief Sets the key mode
 *
 * This function sets the key mode.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of key mode
 *                    - 00b : 128 bits
 *                    - 01b : 192 bits
 *                    - 10b : 256 bits
 */
__attribute__((always_inline)) static inline void CseReg_SetKeyMode(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->SYMMCFG;

    tmp &= ~CSE_SYMMCFG_KEY_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMCFG_KEY_MODE_SHIFT)) & CSE_SYMMCFG_KEY_MODE_MASK);
    this->SYMMCFG = tmp;
}

/*! \brief Sets the initial vector 0
 *
 * This function sets the initial vector 0.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of initial vector 0
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmIV0(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->SYMMIV0;

    tmp &= ~CSE_SYMMIV0_IV0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMIV0_IV0_SHIFT)) & CSE_SYMMIV0_IV0_MASK);
    this->SYMMIV0 = tmp;
}

/*! \brief Sets the initial vector 1
 *
 * This function sets the initial vector 1.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of initial vector 1
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmIV1(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->SYMMIV1;

    tmp &= ~CSE_SYMMIV1_IV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMIV1_IV1_SHIFT)) & CSE_SYMMIV1_IV1_MASK);
    this->SYMMIV1 = tmp;
}

/*! \brief Sets the initial vector 2
 *
 * This function sets the initial vector 2.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of initial vector 2
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmIV2(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->SYMMIV2;

    tmp &= ~CSE_SYMMIV2_IV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMIV2_IV2_SHIFT)) & CSE_SYMMIV2_IV2_MASK);
    this->SYMMIV2 = tmp;
}

/*! \brief Sets the initial vector 3
 *
 * This function sets the initial vector 3.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of initial vector 3
 */
__attribute__((always_inline)) static inline void CseReg_SetSymmIV3(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->SYMMIV3;

    tmp &= ~CSE_SYMMIV3_IV3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_SYMMIV3_IV3_SHIFT)) & CSE_SYMMIV3_IV3_MASK);
    this->SYMMIV3 = tmp;
}

/*! \brief Gets the key exist
 *
 * This function gets the current key exist.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key exist
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetKeyExi(const CseRegType *this)
{
    return ((this->KEYSECT & CSE_KEYSECT_KEY_EXI_MASK) >> CSE_KEYSECT_KEY_EXI_SHIFT);
}

/*! \brief Gets the key index error
 *
 * This function gets the current key index error.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key index error
 *         - 0b : key index in range
 *         - 1b : key index out of range
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetKeySectKeyIdErr(const CseRegType *this)
{
    return ((this->KEYSECT & CSE_KEYSECT_KEY_IDERR_MASK) >> CSE_KEYSECT_KEY_IDERR_SHIFT);
}

/*! \brief Gets the key analysis
 *
 * This function gets the current key analysis.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key analysis operation status
 *         - 0: no key analysis operating
 *         - 1: key analysis operating
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetKeyAnaStatus(const CseRegType *this)
{
    return ((this->KEYSECT & CSE_KEYSECT_KEY_ANA_MASK) >> CSE_KEYSECT_KEY_ANA_SHIFT);
}

/*! \brief Sets the key analysis
 *
 * This function sets the key analysis.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : key analysis enable
 *                    - 1b : enable key analysis
 */
__attribute__((always_inline)) static inline void CseReg_SetKeyAnaEnable(CseRegType *this, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_KEYSECT_KEY_ANA_SHIFT)) & CSE_KEYSECT_KEY_ANA_MASK);
    this->KEYSECT = tmp;
}

/*! \brief Gets the boot protect
 *
 * This function gets the current boot protect.
 *
 * \param[in] this : pointer to CSE register instance
 * \return boot protect
 *         - [x]==0b : key protect enable, can not be used
 *         - [x]==1b : key protect disable, can not be used 
 */
__attribute__((always_inline)) static inline uint32_t CseReg_GetBootKeyProt(const CseRegType *this)
{
    return ((this->LOCK & CSE_LOCK_BOOT_PROT_MASK) >> CSE_LOCK_BOOT_PROT_SHIFT);
}

/*! \brief Sets the boot protect
 *
 * This function sets the boot protect.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of boot protect
 *                    - [x]==0b : key protect enable, can not be used
 *                    - [x]==1b : key protect disable, can be used
 */
__attribute__((always_inline)) static inline void CseReg_SetBootKeyProt(CseRegType *this, uint32_t value)
{
    uint32_t tmp = this->LOCK;

    tmp &= ~CSE_LOCK_BOOT_PROT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_LOCK_BOOT_PROT_SHIFT)) & CSE_LOCK_BOOT_PROT_MASK);
    this->LOCK = tmp;
}

/*! \brief Gets the boot lock
 *
 * This function gets the current boot lock.
 *
 * \param[in] this : pointer to CSE register instance
 * \return boot lock
 *         - 0b : configureable
 *         - 1b : not configureable
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetLockBootLock(const CseRegType *this)
{
    return ((this->LOCK & CSE_LOCK_BOOT_LOCK_MASK) >> CSE_LOCK_BOOT_LOCK_SHIFT);
}

/*! \brief Sets the boot lock
 *
 * This function sets the boot lock.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of boot lock
 *                    - 0b : configureable
 *                    - 1b : not configureable
 */
__attribute__((always_inline)) static inline void CseReg_SetLockBootLock(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->LOCK;

    tmp &= ~CSE_LOCK_BOOT_LOCK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_LOCK_BOOT_LOCK_SHIFT)) & CSE_LOCK_BOOT_LOCK_MASK);
    this->LOCK = tmp;
}

/*! \brief Gets the key is SECRET_KEY
 *
 * This function gets the current key is SECRET_KEY.
 *
 * \param[in] this : pointer to CSE register instance
 * \return key is SECRET_KEY
 *         - 0b : no
 *         - 1b : yes
 */
__attribute__((always_inline)) static inline uint8_t CseReg_GetKeyKeySecret(const CseRegType *this)
{
    return ((this->KEY & CSE_KEY_KEY_SECRET_MASK) >> CSE_KEY_KEY_SECRET_SHIFT);
}

/*! \brief Sets the key is SECRET_KEY
 *
 * This function sets the key is SECRET_KEY.
 *
 * \param[in] this : pointer to CSE register instance
 * \param[in] value : the value of key is SECRET_KEY
 *                    - 0b : no
 *                    - 1b : yes
 */
__attribute__((always_inline)) static inline void CseReg_SetKeyKeySecret(CseRegType *this, uint8_t value)
{
    uint32_t tmp = this->KEY;

    tmp &= ~CSE_KEY_KEY_SECRET_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CSE_KEY_KEY_SECRET_SHIFT)) & CSE_KEY_KEY_SECRET_MASK);
    this->KEY = tmp;
}


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* _CSE_REG_H_ */
