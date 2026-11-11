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

#ifndef _PRNG_REG_H_
#define _PRNG_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the PRNG Registers
 */

/******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * the defines
 ******************************************************************************/

#define PRNG_CTRL_CMD_SHIFT             (0UL)
#define PRNG_CTRL_CMD_MASK              (7UL << PRNG_CTRL_CMD_SHIFT)
#define PRNG_CTRL_CMD_WIDTH             (3UL)

#define PRNG_STAT_RAND_RESEEDING_SHIFT  (31UL)
#define PRNG_STAT_RAND_RESEEDING_MASK   (1UL << PRNG_STAT_RAND_RESEEDING_SHIFT)
#define PRNG_STAT_RAND_RESEEDING_WIDTH  (1UL)
#define PRNG_STAT_RAND_GENERATING_SHIFT (30UL)
#define PRNG_STAT_RAND_GENERATING_MASK  (1UL << PRNG_STAT_RAND_GENERATING_SHIFT)
#define PRNG_STAT_RAND_GENERATING_WIDTH (1UL)
#define PRNG_STAT_SRVC_RQST_SHIFT       (27UL)
#define PRNG_STAT_SRVC_RQST_MASK        (1UL << PRNG_STAT_SRVC_RQST_SHIFT)
#define PRNG_STAT_SRVC_RQST_WIDTH       (1UL)
#define PRNG_STAT_LAST_RESEED_SHIFT     (16UL)
#define PRNG_STAT_LAST_RESEED_MASK      (7UL << PRNG_STAT_LAST_RESEED_SHIFT)
#define PRNG_STAT_LAST_RESEED_WIDTH     (1UL)
#define PRNG_STAT_SEEDED_SHIFT          (9UL)
#define PRNG_STAT_SEEDED_MASK           (1UL << PRNG_STAT_SEEDED_SHIFT)
#define PRNG_STAT_SEEDED_WIDTH          (1UL)
#define PRNG_STAT_SECURE_SHIFT          (8UL)
#define PRNG_STAT_SECURE_MASK           (1UL << PRNG_STAT_SECURE_SHIFT)
#define PRNG_STAT_SECURE_WIDTH          (1UL)
#define PRNG_STAT_R256_SHIFT            (3UL)
#define PRNG_STAT_R256_MASK             (1UL << PRNG_STAT_R256_SHIFT)
#define PRNG_STAT_R256_WIDTH            (1UL)
#define PRNG_STAT_NONCE_SHIFT           (2UL)
#define PRNG_STAT_NONCE_MASK            (1UL << PRNG_STAT_NONCE_SHIFT)
#define PRNG_STAT_NONCE_WIDTH           (1UL)

#define PRNG_MODE_R256_SHIFT            (3UL)
#define PRNG_MODE_R256_MASK             (1UL << PRNG_MODE_R256_SHIFT)
#define PRNG_MODE_R256_WIDTH            (1UL)

#define PRNG_SMODE_SECURE_EN_SHIFT      (8UL)
#define PRNG_SMODE_SECURE_EN_MASK       (1UL << PRNG_SMODE_SECURE_EN_SHIFT)
#define PRNG_SMODE_SECURE_EN_WIDTH      (1UL)
#define PRNG_SMODE_NONCE_MODE_SHIFT     (2UL)
#define PRNG_SMODE_NONCE_MODE_MASK      (1UL << PRNG_SMODE_NONCE_MODE_SHIFT)
#define PRNG_SMODE_NONCE_MODE_WIDTH     (1UL)

#define PRNG_IE_GLBL_EN_SHIFT           (31UL)
#define PRNG_IE_GLBL_EN_MASK            (1UL << PRNG_IE_GLBL_EN_SHIFT)
#define PRNG_IE_GLBL_EN_WIDTH           (1UL)
#define PRNG_IE_LFSR_LOCKUP_EN_SHIFT    (4UL)
#define PRNG_IE_LFSR_LOCKUP_EN_MASK     (1UL << PRNG_IE_LFSR_LOCKUP_EN_SHIFT)
#define PRNG_IE_LFSR_LOCKUP_EN_WIDTH    (1UL)
#define PRNG_IE_RAND_RDY_EN_SHIFT       (0UL)
#define PRNG_IE_RAND_RDY_EN_MASK        (1UL << PRNG_IE_RAND_RDY_EN_SHIFT)
#define PRNG_IE_RAND_RDY_EN_WIDTH       (1UL)

#define PRNG_ISTAT_LFSR_LOCKUP_SHIFT    (4UL)
#define PRNG_ISTAT_LFSR_LOCKUP_MASK     (1UL << PRNG_ISTAT_LFSR_LOCKUP_SHIFT)
#define PRNG_ISTAT_LFSR_LOCKUP_WIDTH    (1UL)
#define PRNG_ISTAT_RAND_RDY_SHIFT       (0UL)
#define PRNG_ISTAT_RAND_RDY_MASK        (1UL << PRNG_ISTAT_RAND_RDY_SHIFT)
#define PRNG_ISTAT_RAND_RDY_WIDTH       (1UL)

/*****************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of PRNG registers
 */
typedef struct _PrngRegType_
{
    volatile uint32_t CTRL;         /*!< module control register, offset: 0000H */
    volatile uint32_t STAT;         /*!< status register, offset: 0004H */
    volatile uint32_t MODE;         /*!< mode register, offset: 0008H */
    volatile uint32_t SMODE;        /*!< secure mode register, offset: 000CH */
    volatile uint32_t IE;           /*!< interrupt enable register, offset: 0010H */
    volatile uint32_t ISTAT;        /*!< interrupt status register, offset: 0014H */
    volatile uint32_t RESERVED1[2]; /*!< reserved registers, offset: 0018H */
    volatile uint32_t RAND[4];      /*!< random value registers, offset: 0020H */
    volatile uint32_t RESERVED2[4]; /*!< reserved registers, offset: 0030H */
    volatile uint32_t SEED[8];      /*!< seed registers, offset: 0040H */
} PrngRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Set command to PRNG
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] cmd : command
 *              -0h: NOP
 *              -1h: Generate a random number
 * .            -3h: Execute a NONCE reseed
 */
__attribute__((always_inline)) static inline void PrngReg_SetCmd(PrngRegType *obj, uint8_t cmd)
{
    uint32_t tempReg;
    tempReg = obj->CTRL;
    tempReg &= (~PRNG_CTRL_CMD_MASK);
    tempReg |= (((uint32_t)cmd) << PRNG_CTRL_CMD_SHIFT) & PRNG_CTRL_CMD_MASK;

    obj->CTRL = tempReg;
}

/*! \brief Get PRNG command
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return command
 *              -0h: NOP
 *              -1h: Generate a random number
 * .            -3h: Execute a NONCE reseed
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetCmd(PrngRegType *obj)
{
    return (uint8_t)((obj->CTRL & PRNG_CTRL_CMD_MASK) >> PRNG_CTRL_CMD_SHIFT);
}

/*! \brief Get random reseed status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return random reseed status
 *              -0h: no random reseed in progress
 *              -1h: random reseed in progress
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetRandReseedSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_RAND_RESEEDING_MASK) >> PRNG_STAT_RAND_RESEEDING_SHIFT);
}

/*! \brief Get random generation status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return random generation status
 *              -0h: no random number generation in progress
 *              -1h: random number generation in progress
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetRandGenSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_RAND_GENERATING_MASK) >> PRNG_STAT_RAND_GENERATING_SHIFT);
}

/*! \brief Get service request status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return service request status
 *              -0h: no unacknowledged service request indicator
 *              -1h: Unacknowledged service request indicator
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetSrvReqSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_SRVC_RQST_MASK) >> PRNG_STAT_SRVC_RQST_SHIFT);
}

/*! \brief Get last reseed status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return last reseed status
 *              -0h: reseeded by host command
 *              -3h: reseeded by nonce
 * .            -4h: reseeded by I_reseed command
 *              -7h: Unseeded (reset)
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetLastReseedSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_LAST_RESEED_MASK) >> PRNG_STAT_LAST_RESEED_SHIFT);
}

/*! \brief Get seeded status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return last reseed status
 *              -0h: no seed operated
 *              -1h: at least one seed operated
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetSeedSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_SEEDED_MASK) >> PRNG_STAT_SEEDED_SHIFT);
}

/*! \brief Get secure status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return secure status
 *              -0h: TODO ???
 *              -1h: TODO ???
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetSecureSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_SECURE_MASK) >> PRNG_STAT_SECURE_SHIFT);
}

/*! \brief Get R256 status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return R256 status
 *              -0h: TODO ???
 *              -1h: TODO ???
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetR256Sts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_R256_MASK) >> PRNG_STAT_R256_SHIFT);
}

/*! \brief Get NONCE mode status
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return NONCE mode status
 *              -0h: NONCE mode disable
 *              -1h: NONCE mode enable
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetNonceModeSts(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_STAT_NONCE_MASK) >> PRNG_STAT_NONCE_SHIFT);
}

/*! \brief Set random length
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] mode : random length
 *              -0h: 128-bit
 *              -1h: 256-bit
 */
__attribute__((always_inline)) static inline void PrngReg_SetRandLen(PrngRegType *obj, uint8_t mode)
{
    uint32_t tempReg;
    tempReg = obj->MODE;
    tempReg &= (~PRNG_MODE_R256_MASK);
    tempReg |= (((uint32_t)mode) << PRNG_MODE_R256_SHIFT) & PRNG_MODE_R256_MASK;

    obj->MODE = tempReg;
}

/*! \brief Get random mode
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return random length
 *              -0h: 128-bit
 *              -1h: 256-bit
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetRandLen(PrngRegType *obj)
{
    return (uint8_t)((obj->STAT & PRNG_MODE_R256_MASK) >> PRNG_MODE_R256_SHIFT);
}

/*! \brief Set secure mode
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] mode : random length mode
 *              -0h: promiscuous mode (access to internal state and test field)
 *              -1h: secure mode (no access to internal state and test field)
 */
__attribute__((always_inline)) static inline void PrngReg_SetSecureMode(PrngRegType *obj, uint8_t mode)
{
    uint32_t tempReg;
    tempReg = obj->SMODE;
    tempReg &= (~PRNG_SMODE_SECURE_EN_MASK);
    tempReg |= (((uint32_t)mode) << PRNG_SMODE_SECURE_EN_SHIFT) & PRNG_SMODE_SECURE_EN_MASK;

    obj->SMODE = tempReg;
}

/*! \brief Get secure mode
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return secure mode
 *              -0h: promiscuous mode (access to internal state and test field)
 *              -1h: secure mode (no access to internal state and test field)
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetSecureMode(PrngRegType *obj)
{
    return (uint8_t)((obj->SMODE & PRNG_SMODE_SECURE_EN_MASK) >> PRNG_SMODE_SECURE_EN_SHIFT);
}

/*! \brief Set NONCE mode enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] enable : NONCE mode enable
 *              -0h: NONCE mode disable
 *              -1h: NONCE mode enable
 */
__attribute__((always_inline)) static inline void PrngReg_SetNonceModeEnable(PrngRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->SMODE;
    tempReg &= (~PRNG_SMODE_NONCE_MODE_MASK);
    tempReg |= (((uint32_t)enable) << PRNG_SMODE_NONCE_MODE_SHIFT) & PRNG_SMODE_NONCE_MODE_MASK;

    obj->SMODE = tempReg;
}

/*! \brief Get NONCE mode enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return NONCE mode enable
 *              -0h: NONCE mode disable
 *              -1h: NONCE mode enable
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetNonceModeEnable(PrngRegType *obj)
{
    return (uint8_t)((obj->SMODE & PRNG_SMODE_NONCE_MODE_MASK) >> PRNG_SMODE_NONCE_MODE_SHIFT);
}

/*! \brief Set global interrupt enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] enable : global interrupt enable
 *              -0h: global interrupt disable
 *              -1h: global interrupt enable
 */
__attribute__((always_inline)) static inline void PrngReg_SetGloalIntEnable(PrngRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->IE;
    tempReg &= (~PRNG_IE_GLBL_EN_MASK);
    tempReg |= (((uint32_t)enable) << PRNG_IE_GLBL_EN_SHIFT) & PRNG_IE_GLBL_EN_MASK;

    obj->IE = tempReg;
}

/*! \brief Get global interrupt enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return global interrupt enable
 *              -0h: global interrupt disable
 *              -1h: global interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetGloalIntEnable(PrngRegType *obj)
{
    return (uint8_t)((obj->SMODE & PRNG_IE_GLBL_EN_MASK) >> PRNG_IE_GLBL_EN_SHIFT);
}

/*! \brief Set LFSR lockup interrupt enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] enable : LFSR lockup interrupt enable
 *              -0h: LFSR lockup interrupt disable
 *              -1h: LFSR lockup interrupt enable
 */
__attribute__((always_inline)) static inline void PrngReg_SetLFSRIntEnable(PrngRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->IE;
    tempReg &= (~PRNG_IE_LFSR_LOCKUP_EN_MASK);
    tempReg |= (((uint32_t)enable) << PRNG_IE_LFSR_LOCKUP_EN_SHIFT) & PRNG_IE_LFSR_LOCKUP_EN_MASK;

    obj->IE = tempReg;
}

/*! \brief Get LFSR lockup interrupt enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return LFSR lockup interrupt enable
 *              -0h: LFSR lockup interrupt disable
 *              -1h: LFSR lockup interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetLFSRIntEnable(PrngRegType *obj)
{
    return (uint8_t)((obj->IE & PRNG_IE_LFSR_LOCKUP_EN_MASK) >> PRNG_IE_LFSR_LOCKUP_EN_SHIFT);
}

/*! \brief Set random number ready interrupt enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] enable : random number ready interrupt enable
 *              -0h: random number ready interrupt disable
 *              -1h: random number ready interrupt enable
 */
__attribute__((always_inline)) static inline void PrngReg_SetRandRdyIntEnable(PrngRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->IE;
    tempReg &= (~PRNG_IE_RAND_RDY_EN_MASK);
    tempReg |= (((uint32_t)enable) << PRNG_IE_RAND_RDY_EN_SHIFT) & PRNG_IE_RAND_RDY_EN_MASK;

    obj->IE = tempReg;
}

/*! \brief Get LFSR lockup interrupt enable
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return random number ready interrupt enable
 *              -0h: random number ready interrupt disable
 *              -1h: random number ready interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetRandRdyIntEnable(PrngRegType *obj)
{
    return (uint8_t)((obj->IE & PRNG_IE_RAND_RDY_EN_MASK) >> PRNG_IE_RAND_RDY_EN_SHIFT);
}

/*! \brief Clear LFSR lockup interrupt flag
 *
 * \param[in] obj : pointer to PRNG register instance
 */
__attribute__((always_inline)) static inline void PrngReg_ClearLFSRIntFlag(PrngRegType *obj)
{
    obj->ISTAT = PRNG_ISTAT_LFSR_LOCKUP_MASK;
}

/*! \brief Get LFSR lockup interrupt flag
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return LFSR lockup interrupt flag
 *              -0h: LFSR lockup interrupt deassert
 *              -1h: LFSR lockup interrupt assert
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetLFSRIntFlag(PrngRegType *obj)
{
    return (uint8_t)((obj->ISTAT & PRNG_ISTAT_LFSR_LOCKUP_MASK) >> PRNG_ISTAT_LFSR_LOCKUP_SHIFT);
}

/*! \brief Clear random ready flag
 *
 * \param[in] obj : pointer to PRNG register instance
 */
__attribute__((always_inline)) static inline void PrngReg_ClearRandRdyFlag(PrngRegType *obj)
{
    obj->ISTAT = PRNG_ISTAT_RAND_RDY_MASK;
}

/*! \brief Get random ready interrupt flag
 *
 * \param[in] obj : pointer to PRNG register instance
 * \return random ready interrupt flag
 *              -0h: random ready interrupt deassert
 *              -1h: random ready interrupt assert
 */
__attribute__((always_inline)) static inline uint8_t PrngReg_GetRandRdyFlag(PrngRegType *obj)
{
    return (uint8_t)((obj->ISTAT & PRNG_ISTAT_RAND_RDY_MASK) >> PRNG_ISTAT_RAND_RDY_SHIFT);
}

/*! \brief Get random value
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[out] randPtr : random uint32 pointer
 */
__attribute__((always_inline)) static inline void PrngReg_GetRandValFlag(PrngRegType *obj, uint32_t *randPtr)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        randPtr[i] = obj->RAND[i];
    }
}

/*! \brief Set seed value
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[in] seedPtr : seed uint32 pointer
 */
__attribute__((always_inline)) static inline void PrngReg_SetSeedVal(PrngRegType *obj, uint32_t *seedPtr)
{
    for(uint8_t i = 0; i < 8; i++)
    {
        obj->SEED[i] = seedPtr[i];
    }
}

/*! \brief Get seed value
 *
 * \param[in] obj : pointer to PRNG register instance
 * \param[out] seedPtr : seed uint32 pointer
 */
__attribute__((always_inline)) static inline void PrngReg_GetSeedVal(PrngRegType *obj, uint32_t *seedPtr)
{
    for(uint8_t i = 0; i < 8; i++)
    {
        *seedPtr = obj->SEED[i];
    }
}

#endif
