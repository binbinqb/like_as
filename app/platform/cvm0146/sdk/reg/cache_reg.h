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

#ifndef _CACHE_REG_H_
#define _CACHE_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the CACHE Registers
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
#define CACHE_CTRL_R2_MODE_MASK   (0x200u)
#define CACHE_CTRL_R2_MODE_SHIFT  (9u)
#define CACHE_CTRL_R2_MODE_WIDTH  (1u)
#define CACHE_CTRL_R0_MODE_MASK   (0x100u)
#define CACHE_CTRL_R0_MODE_SHIFT  (8u)
#define CACHE_CTRL_R0_MODE_WIDTH  (1u)
#define CACHE_CTRL_HCNT_EN_MASK   (0x80u)
#define CACHE_CTRL_HCNT_EN_SHIFT  (7u)
#define CACHE_CTRL_HCNT_EN_WIDTH  (1u)
#define CACHE_CTRL_MCNT_EN_MASK   (0x40u)
#define CACHE_CTRL_MCNT_EN_SHIFT  (6u)
#define CACHE_CTRL_MCNT_EN_WIDTH  (1u)
#define CACHE_CTRL_DED_ERM_EN_MASK    (0x20u)
#define CACHE_CTRL_DED_ERM_EN_SHIFT   (5u)
#define CACHE_CTRL_DED_ERM_EN_WIDTH   (1u)
#define CACHE_CTRL_SEC_ERM_EN_MASK    (0x10u)
#define CACHE_CTRL_SEC_ERM_EN_SHIFT   (4u)
#define CACHE_CTRL_SEC_ERM_EN_WIDTH   (1u)
#define CACHE_CTRL_PFB_EN_MASK    (0x04u)
#define CACHE_CTRL_PFB_EN_SHIFT   (2u)
#define CACHE_CTRL_PFB_EN_WIDTH   (1u)
#define CACHE_CTRL_FLS_EN_MASK    (0x02u)
#define CACHE_CTRL_FLS_EN_SHIFT   (1u)
#define CACHE_CTRL_FLS_EN_WIDTH   (1u)
#define CACHE_CTRL_EN_MASK        (0x01u)
#define CACHE_CTRL_EN_SHIFT       (0u)
#define CACHE_CTRL_EN_WIDTH       (1u)

/* ST Bit Fields */
#define CACHE_ST_DEDF_MASK        (0x04u)
#define CACHE_ST_DEDF_SHIFT       (2u)
#define CACHE_ST_DEDF_WIDTH       (1u)
#define CACHE_ST_SECF_MASK        (0x02u)
#define CACHE_ST_SECF_SHIFT       (1u)
#define CACHE_ST_SECF_WIDTH       (1u)
#define CACHE_ST_ACC_ERR_MASK     (0x01u)
#define CACHE_ST_ACC_ERR_SHIFT    (0u)
#define CACHE_ST_ACC_ERR_WIDTH    (1u)

/* DBGC Bit Fields */
#define CACHE_DBGC_CL_GO_MASK     (0x1000000u)
#define CACHE_DBGC_CL_GO_SHIFT    (24u)
#define CACHE_DBGC_CL_GO_WIDTH    (1u)
#define CACHE_DBGC_CL_ADDR_MASK   (0x7FF00u)
#define CACHE_DBGC_CL_ADDR_SHIFT  (8u)
#define CACHE_DBGC_CL_ADDR_WIDTH  (11u)
#define CACHE_DBGC_TD_SEL_MASK    (0x02u)
#define CACHE_DBGC_TD_SEL_SHIFT   (1u)
#define CACHE_DBGC_TD_SEL_WIDTH   (1u)
#define CACHE_DBGC_WAY_SEL_MASK   (0x01u)
#define CACHE_DBGC_WAY_SEL_SHIFT  (0u)
#define CACHE_DBGC_WAY_SEL_WIDTH  (1u)

/* DBGR Bit Fields */
#define CACHE_DBGR_DBG_RES_MASK   (0xFFFFFFFFu)
#define CACHE_DBGR_DBG_RES_SHIFT  (0u)
#define CACHE_DBGR_DBG_RES_WIDTH  (32u)

/* MCNT Bit Fields */
#define CACHE_MCNT_MISS_CNT_MASK  (0xFFFFFFFFu)
#define CACHE_MCNT_MISS_CNT_SHIFT (0u)
#define CACHE_MCNT_MISS_CNT_WIDTH (32u)

/* HCNT Bit Fields */
#define CACHE_HCNT_HIT_CNT_MASK   (0xFFFFFFFFu)
#define CACHE_HCNT_HIT_CNT_SHIFT  (0u)
#define CACHE_HCNT_HIT_CNT_WIDTH  (32u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of CACHE registers
 */
typedef struct _CacheRegType_
{
    volatile uint32_t       CTRL; /*!< cache control register, offset: 0000H */
    volatile uint32_t       ST;   /*!< cache status register, offset: 0004H */
    volatile uint32_t       DBGC; /*!< cache debug configuration register, offset: 0008H */
    const volatile uint32_t DBGR; /*!< cache debug result register, offset: 000CH */
    const volatile uint32_t MCNT; /*!< cache access miss counter, offset: 0010H */
    const volatile uint32_t HCNT; /*!< cache access hit counter, offset: 0014H */
} CacheRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the region2 access mode
 *
 * This function gets the current region2 access mode.
 * cacheable or noncacheable selection
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return region2 access mode
 *         - 0b : non-cacheable access
 *         - 1b : cacheable access
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlR2Mode(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_R2_MODE_MASK) >> CACHE_CTRL_R2_MODE_SHIFT);
}

/*! \brief Sets the region2 access mode
 *
 * This function sets the region2 access mode.
 * cacheable or noncacheable selection
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of region2 access mode
 *                    - 0b : non-cacheable access
 *                    - 1b : cacheable access
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlR2Mode(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_R2_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_R2_MODE_SHIFT)) & CACHE_CTRL_R2_MODE_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the region0 access mode
 *
 * This function gets the current region0 access mode.
 * cacheable or noncacheable selection
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return region0 access mode
 *         - 0b : non-cacheable access
 *         - 1b : cacheable access
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlR0Mode(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_R0_MODE_MASK) >> CACHE_CTRL_R0_MODE_SHIFT);
}

/*! \brief Sets the region0 access mode
 *
 * This function sets the region0 access mode.
 * cacheable or noncacheable selection
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of region0 access mode
 *                    - 0b : non-cacheable access
 *                    - 1b : cacheable access
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlR0Mode(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_R0_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_R0_MODE_SHIFT)) & CACHE_CTRL_R0_MODE_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the cache hit counter enable
 *
 * This function gets the current cache hit counter enable.
 * enable cache hit counter to work
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache hit counter enable
 *         - 0b : disable cache hit counter
 *         - 1b : enable cache hit counter
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlHCntEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_HCNT_EN_MASK) >> CACHE_CTRL_HCNT_EN_SHIFT);
}

/*! \brief Sets the cache hit counter enable
 *
 * This function sets the cache hit counter enable.
 * enable cache hit counter to work
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache hit counter enable
 *                    - 0b : disable cache hit counter
 *                    - 1b : enable cache hit counter
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlHCntEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_HCNT_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_HCNT_EN_SHIFT)) & CACHE_CTRL_HCNT_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the cache miss counter enable
 *
 * This function gets the current cache miss counter enable.
 * enable cache miss counter to work
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache miss counter enable
 *         - 0b : disable cache miss counter
 *         - 1b : enable cache miss counter
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlMCntEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_MCNT_EN_MASK) >> CACHE_CTRL_MCNT_EN_SHIFT);
}

/*! \brief Sets the cache miss counter enable
 *
 * This function sets the cache miss counter enable.
 * enable cache miss counter to work
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache miss counter enable
 *                    - 0b : disable cache miss counter
 *                    - 1b : enable cache miss counter
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlMCntEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_MCNT_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_MCNT_EN_SHIFT)) & CACHE_CTRL_MCNT_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the configuration of cache ecc ded to erm 
 *
 * This function gets the current configuration of cache ecc ded to erm.
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache ecc ded to erm configuration
 *         - 0b : ecc ded to erm is disabled
 *         - 1b : ecc ded to erm is enabled
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlDedErmEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_DED_ERM_EN_MASK) >> CACHE_CTRL_DED_ERM_EN_SHIFT);
}

/*! \brief Sets the cache ecc ded to erm enable
 *
 * This function sets the cache ecc ded to erm enable.
 * control the enable for ecc ded to erm
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache ecc ded to erm enable
 *                    - 0b : disable ecc ded to erm 
 *                    - 1b : enable ecc ded to erm 
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlDedErmEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_DED_ERM_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_DED_ERM_EN_SHIFT)) & CACHE_CTRL_DED_ERM_EN_MASK);
    obj->CTRL = tmp;
}

 /*! \brief Gets the configuration of cache ecc sec to erm 
 *
 * This function gets the current configuration of cache ecc sec to erm.
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache ecc sec to erm configuration
 *         - 0b : ecc sec to erm is disabled
 *         - 1b : ecc sec to erm is enabled
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlSecErmEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_SEC_ERM_EN_MASK) >> CACHE_CTRL_SEC_ERM_EN_SHIFT);
}

 /*! \brief Sets the cache ecc sec to erm enable
 *
 * This function sets the cache ecc sec to erm enable.
 * control the enable for ecc sec to erm
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache ecc sec to erm enable
 *                    - 0b : disable ecc sec to erm 
 *                    - 1b : enable ecc sec to erm 
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlSecErmEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_SEC_ERM_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_SEC_ERM_EN_SHIFT)) & CACHE_CTRL_SEC_ERM_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the cache access prefetch enable
 *
 * This function gets the current cache access prefetch enable.
 * control the prefetch enable for cache access
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache access prefetch enable
 *         - 0b : disable cache prefetch access
 *         - 1b : enable cache prefetch access
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlPfbEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_PFB_EN_MASK) >> CACHE_CTRL_PFB_EN_SHIFT);
}

/*! \brief Sets the cache access prefetch enable
 *
 * This function sets the cache access prefetch enable.
 * control the prefetch enable for cache access
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache access prefetch enable
 *                    - 0b : disable cache prefetch access
 *                    - 1b : enable cache prefetch access
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlPfbEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_PFB_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_PFB_EN_SHIFT)) & CACHE_CTRL_PFB_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the cache access flush enable
 *
 * This function gets the current cache access flush enable.
 * control the flush enable for cache access
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache access flush enable
 *         - 0b : disable cache flush
 *         - 1b : enable cache flush
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlFlsEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_FLS_EN_MASK) >> CACHE_CTRL_FLS_EN_SHIFT);
}

/*! \brief Sets the cache access flush enable
 *
 * This function sets the cache access flush enable.
 * control the flush enable for cache access
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache access flush enable
 *                    - 0b : disable cache flush
 *                    - 1b : enable cache flush
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlFlsEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_FLS_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_FLS_EN_SHIFT)) & CACHE_CTRL_FLS_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the cache access enable
 *
 * This function gets the current cache access enable.
 * control the enable for cache access
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache access enable
 *         - 0b : bypass cache access
 *         - 1b : enable cache access
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetCtrlEn(const CacheRegType *obj)
{
    return ((obj->CTRL & CACHE_CTRL_EN_MASK) >> CACHE_CTRL_EN_SHIFT);
}

/*! \brief Sets the cache access enable
 *
 * This function sets the cache access enable.
 * control the enable for cache access
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache access enable
 *                    - 0b : bypass cache access
 *                    - 1b : enable cache access
 */
__attribute__((always_inline)) static inline void CacheReg_SetCtrlEn(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~CACHE_CTRL_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_CTRL_EN_SHIFT)) & CACHE_CTRL_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the ecc ded error flag
 *
 * This function gets the current ecc ded error flag.
 * cache ecc double bits error flag
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return ecc ded error flag
 *         - 0b : no ecc ded error
 *         - 1b : ecc ded error has occured
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetStDedF(const CacheRegType *obj)
{
    return ((obj->ST & CACHE_ST_DEDF_MASK) >> CACHE_ST_DEDF_SHIFT);
}

/*! \brief Sets the ecc ded error flag
 *
 * This function sets the ecc ded error flag.
 * cache ecc double bits error flag
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of ecc ded error flag
 *                    - 0b : no effect
 *                    - 1b : clear the error flag
 */
__attribute__((always_inline)) static inline void CacheReg_SetStDedF(CacheRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_ST_DEDF_SHIFT)) & CACHE_ST_DEDF_MASK);
    obj->ST = tmp;
}

/*! \brief Gets the ecc sec error flag
 *
 * This function gets the current ecc sec error flag.
 * cache ecc single bit error flag
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return ecc sec error flag
 *         - 0b : no ecc sec error
 *         - 1b : ecc sec error has occured
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetStSecF(const CacheRegType *obj)
{
    return ((obj->ST & CACHE_ST_SECF_MASK) >> CACHE_ST_SECF_SHIFT);
}

/*! \brief Sets the ecc sec error flag
 *
 * This function sets the ecc sec error flag.
 * cache ecc single bit error flag
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of ecc sec error flag
 *                    - 0b : no effect
 *                    - 1b : clear the error flag
 */
__attribute__((always_inline)) static inline void CacheReg_SetStSecF(CacheRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_ST_SECF_SHIFT)) & CACHE_ST_SECF_MASK);
    obj->ST = tmp;
}

/*! \brief Gets the cache access error
 *
 * This function gets the current cache access error.
 * cache access error flag
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache access error
 *         - 0b : no cache access error
 *         - 1b : cache access error has occurred
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetStAccErr(const CacheRegType *obj)
{
    return ((obj->ST & CACHE_ST_ACC_ERR_MASK) >> CACHE_ST_ACC_ERR_SHIFT);
}

/*! \brief Sets the cache access error
 *
 * This function sets the cache access error.
 * cache access error flag
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache access error
 *                    - 0b : no effect
 *                    - 1b : clear the error flag
 */
__attribute__((always_inline)) static inline void CacheReg_SetStAccErr(CacheRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_ST_ACC_ERR_SHIFT)) & CACHE_ST_ACC_ERR_MASK);
    obj->ST = tmp;
}

/*! \brief Gets the cache line debug go
 *
 * This function gets the current cache line debug go.
 * cache line debug work state
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache line debug go
 *         - 0b : cache line debug done
 *         - 1b : cache line debug is going
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetDbgCCLGo(const CacheRegType *obj)
{
    return ((obj->DBGC & CACHE_DBGC_CL_GO_MASK) >> CACHE_DBGC_CL_GO_SHIFT);
}

/*! \brief Sets the cache line debug go
 *
 * This function sets the cache line debug go.
 * cache line debug work state
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache line debug go
 *                    - 0b : cache line debug done
 *                    - 1b : cache line debug is going
 */
__attribute__((always_inline)) static inline void CacheReg_SetDbgCCLGo(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DBGC;

    tmp &= ~CACHE_DBGC_CL_GO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_DBGC_CL_GO_SHIFT)) & CACHE_DBGC_CL_GO_MASK);
    obj->DBGC = tmp;
}

/*! \brief Gets the cache line debug address
 *
 * This function gets the current cache line debug address.
 * cache ram physical address configuration
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache line debug address
 *         - 0h : cache ram address 0
 *         - 1h : cache ram address 1
 *         - 2h : cache ram address 2
 *         - 3h : cache ram address 3
 *         - others : cache ram address is the CL_ADDR register value
 */
__attribute__((always_inline)) static inline uint16_t CacheReg_GetDbgCCLAddr(const CacheRegType *obj)
{
    return ((obj->DBGC & CACHE_DBGC_CL_ADDR_MASK) >> CACHE_DBGC_CL_ADDR_SHIFT);
}

/*! \brief Sets the cache line debug address
 *
 * This function sets the cache line debug address.
 * cache ram physical address configuration
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache line debug address
 *                    - 0h : cache ram address 0
 *                    - 1h : cache ram address 1
 *                    - 2h : cache ram address 2
 *                    - 3h : cache ram address 3
 *                    - others : cache ram address is the CL_ADDR register value
 */
__attribute__((always_inline)) static inline void CacheReg_SetDbgCCLAddr(CacheRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->DBGC;

    tmp &= ~CACHE_DBGC_CL_ADDR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_DBGC_CL_ADDR_SHIFT)) & CACHE_DBGC_CL_ADDR_MASK);
    obj->DBGC = tmp;
}

/*! \brief Gets the cache line data or tag selection
 *
 * This function gets the current cache line data or tag selection.
 * cache line data or tag selection configuration
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache line data or tag selection
 *         - 0b : data
 *         - 1b : tag
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetDbgCTdSel(const CacheRegType *obj)
{
    return ((obj->DBGC & CACHE_DBGC_TD_SEL_MASK) >> CACHE_DBGC_TD_SEL_SHIFT);
}

/*! \brief Sets the cache line data or tag selection
 *
 * This function sets the cache line data or tag selection.
 * cache line data or tag selection configuration
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache line data or tag selection
 *                    - 0b : data
 *                    - 1b : tag
 */
__attribute__((always_inline)) static inline void CacheReg_SetDbgCTdSel(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DBGC;

    tmp &= ~CACHE_DBGC_TD_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_DBGC_TD_SEL_SHIFT)) & CACHE_DBGC_TD_SEL_MASK);
    obj->DBGC = tmp;
}

/*! \brief Gets the cache way selection
 *
 * This function gets the current cache way selection.
 * cache way selection configuration
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache way selection
 *         - 0b : way0
 *         - 1b : way1
 */
__attribute__((always_inline)) static inline uint8_t CacheReg_GetDbgCWaySel(const CacheRegType *obj)
{
    return ((obj->DBGC & CACHE_DBGC_WAY_SEL_MASK) >> CACHE_DBGC_WAY_SEL_SHIFT);
}

/*! \brief Sets the cache way selection
 *
 * This function sets the cache way selection.
 * cache way selection configuration
 *
 * \param[in] obj : pointer to CACHE register instance
 * \param[in] value : the value of cache way selection
 *                    - 0b : way0
 *                    - 1b : way1
 */
__attribute__((always_inline)) static inline void CacheReg_SetDbgCWaySel(CacheRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DBGC;

    tmp &= ~CACHE_DBGC_WAY_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CACHE_DBGC_WAY_SEL_SHIFT)) & CACHE_DBGC_WAY_SEL_MASK);
    obj->DBGC = tmp;
}

/*! \brief Gets the cache debug result
 *
 * This function gets the current cache debug result.
 * cache debug result
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache debug result
 *         - 0b : cache debug result
 */
__attribute__((always_inline)) static inline uint32_t CacheReg_GetDbgRDbgRes(const CacheRegType *obj)
{
    return ((obj->DBGR & CACHE_DBGR_DBG_RES_MASK) >> CACHE_DBGR_DBG_RES_SHIFT);
}

/*! \brief Gets the cache access miss counter
 *
 * This function gets the current cache access miss counter.
 * cache access miss counter
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache access miss counter
 *         - 0h : counter valus is 0
 *         - 1h : counter valus is 1
 *         - 2h : counter valus is 2
 *         - 3h : counter valus is 3
 *         - 4h : counter valus is 4
 *         - others : counter valus is MISS_CNT
 */
__attribute__((always_inline)) static inline uint32_t CacheReg_GetMCntMissCnt(const CacheRegType *obj)
{
    return ((obj->MCNT & CACHE_MCNT_MISS_CNT_MASK) >> CACHE_MCNT_MISS_CNT_SHIFT);
}

/*! \brief Gets the cache access hit counter
 *
 * This function gets the current cache access hit counter.
 * cache access hit counter
 *
 * \param[in] obj : pointer to CACHE register instance
 * \return cache access hit counter
 *         - 0h : counter valus is 0
 *         - 1h : counter valus is 1
 *         - 2h : counter valus is 2
 *         - 3h : counter valus is 3
 *         - 4h : counter valus is 4
 *         - others : counter valus is HIT_CNT
 */
__attribute__((always_inline)) static inline uint32_t CacheReg_GetHCntHitCnt(const CacheRegType *obj)
{
    return ((obj->HCNT & CACHE_HCNT_HIT_CNT_MASK) >> CACHE_HCNT_HIT_CNT_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CACHE_REG_H_ */
