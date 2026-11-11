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

#ifndef _MSCM_REG_H_
#define _MSCM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the MSCM Registers
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

/* CPU_TYPE Bit Fields */
#define MSCM_CPU_TYPE_TYPE_MASK          (0xFFFFFF00u)
#define MSCM_CPU_TYPE_TYPE_SHIFT         (8u)
#define MSCM_CPU_TYPE_TYPE_WIDTH         (24u)
#define MSCM_CPU_TYPE_REVISION_MASK      (0xFFu)
#define MSCM_CPU_TYPE_REVISION_SHIFT     (0u)
#define MSCM_CPU_TYPE_REVISION_WIDTH     (8u)

/* CPU_NUM Bit Fields */
#define MSCM_CPU_NUM_CPNX_MASK           (0x01u)
#define MSCM_CPU_NUM_CPNX_SHIFT          (0u)
#define MSCM_CPU_NUM_CPNX_WIDTH          (1u)

/* CPU_CNT Bit Fields */
#define MSCM_CPU_CNT_PCNT_MASK           (0x03u)
#define MSCM_CPU_CNT_PCNT_SHIFT          (0u)
#define MSCM_CPU_CNT_PCNT_WIDTH          (2u)

/* CPU_CACHE Bit Fields */
#define MSCM_CPU_CACHE_ICACHE_SIZE_MASK  (0xFF000000u)
#define MSCM_CPU_CACHE_ICACHE_SIZE_SHIFT (24u)
#define MSCM_CPU_CACHE_ICACHE_SIZE_WIDTH (8u)
#define MSCM_CPU_CACHE_ICACHE_WAYS_MASK  (0xFF0000u)
#define MSCM_CPU_CACHE_ICACHE_WAYS_SHIFT (16u)
#define MSCM_CPU_CACHE_ICACHE_WAYS_WIDTH (8u)
#define MSCM_CPU_CACHE_DCACHE_SIZE_MASK  (0xFF00u)
#define MSCM_CPU_CACHE_DCACHE_SIZE_SHIFT (8u)
#define MSCM_CPU_CACHE_DCACHE_SIZE_WIDTH (8u)
#define MSCM_CPU_CACHE_DCACHE_WAYS_MASK  (0xFFu)
#define MSCM_CPU_CACHE_DCACHE_WAYS_SHIFT (0u)
#define MSCM_CPU_CACHE_DCACHE_WAYS_WIDTH (8u)

/* CPU_MEM Bit Fields */
#define MSCM_CPU_MEM_SRAMU_SIZE_MASK     (0xFF000000u)
#define MSCM_CPU_MEM_SRAMU_SIZE_SHIFT    (24u)
#define MSCM_CPU_MEM_SRAMU_SIZE_WIDTH    (8u)
#define MSCM_CPU_MEM_SRAML_SIZE_MASK     (0xFF00u)
#define MSCM_CPU_MEM_SRAML_SIZE_SHIFT    (8u)
#define MSCM_CPU_MEM_SRAML_SIZE_WIDTH    (8u)

/* CPU_CFG Bit Fields */
#define MSCM_CPU_CFG_BUS_PORTS_MASK      (0x300u)
#define MSCM_CPU_CFG_BUS_PORTS_SHIFT     (8u)
#define MSCM_CPU_CFG_BUS_PORTS_WIDTH     (2u)
#define MSCM_CPU_CFG_BB_MASK             (0x40u)
#define MSCM_CPU_CFG_BB_SHIFT            (6u)
#define MSCM_CPU_CFG_BB_WIDTH            (1u)
#define MSCM_CPU_CFG_SMPU_MASK           (0x20u)
#define MSCM_CPU_CFG_SMPU_SHIFT          (5u)
#define MSCM_CPU_CFG_SMPU_WIDTH          (1u)
#define MSCM_CPU_CFG_MMU_MASK            (0x10u)
#define MSCM_CPU_CFG_MMU_SHIFT           (4u)
#define MSCM_CPU_CFG_MMU_WIDTH           (1u)
#define MSCM_CPU_CFG_TRUST_ZONE_MASK     (0x08u)
#define MSCM_CPU_CFG_TRUST_ZONE_SHIFT    (3u)
#define MSCM_CPU_CFG_TRUST_ZONE_WIDTH    (1u)
#define MSCM_CPU_CFG_JAZ_MASK            (0x04u)
#define MSCM_CPU_CFG_JAZ_SHIFT           (2u)
#define MSCM_CPU_CFG_JAZ_WIDTH           (1u)
#define MSCM_CPU_CFG_SIMD_MASK           (0x02u)
#define MSCM_CPU_CFG_SIMD_SHIFT          (1u)
#define MSCM_CPU_CFG_SIMD_WIDTH          (1u)
#define MSCM_CPU_CFG_FPU_MASK            (0x01u)
#define MSCM_CPU_CFG_FPU_SHIFT           (0u)
#define MSCM_CPU_CFG_FPU_WIDTH           (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of MSCM registers
 */
typedef struct _MscmRegType_
{
    const volatile uint32_t CPU_TYPE;     /*!< Processor info register, offset: 0x00 */
    const volatile uint32_t CPU_NUM;      /*!< Process NUMBER, offset: 0x04 */
    uint32_t                RESERVED0[1]; /*!< Reserverd block, offset: 0x08 */
    const volatile uint32_t CPU_CNT;      /*!< Total number of processor cores, offset: 0x0C */
    const volatile uint32_t CPU_CACHE;    /*!< CPU cache info register, offset: 0x10 */
    const volatile uint32_t CPU_MEM;      /*!< System memory info register, offset: 0x14 */
    const volatile uint32_t CPU_CFG;      /*!< CPU configuration register, offset: 0x18 */
} MscmRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the CPU type name
 *
 * This function gets the current CPU type name.
 * The default value 0x434D34 is ASICC of "CM4"
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return CPU type name
 */
__attribute__((always_inline)) static inline uint32_t MscmReg_GetCpuTypeType(const MscmRegType *obj)
{
    return ((obj->CPU_TYPE & MSCM_CPU_TYPE_TYPE_MASK) >> MSCM_CPU_TYPE_TYPE_SHIFT);
}

/*! \brief Gets the revision of processor
 *
 * This function gets the current revision of processor.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return revision of processor
 *         - 0b : r0p0
 *         - 1b : r0p1
 *         - other : reserved
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuTypeRevision(const MscmRegType *obj)
{
    return ((obj->CPU_TYPE & MSCM_CPU_TYPE_REVISION_MASK) >> MSCM_CPU_TYPE_REVISION_SHIFT);
}

/*! \brief Gets the Processor x Number
 *
 * This function gets the current Processor x Number.
 * This zero-filled word defines the logical processor number for CPUx.
 * If single core configuration, then CPN = 0
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Processor x Number
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuNumCpnx(const MscmRegType *obj)
{
    return ((obj->CPU_NUM & MSCM_CPU_NUM_CPNX_MASK) >> MSCM_CPU_NUM_CPNX_SHIFT);
}

/*! \brief Gets the Processor Count
 *
 * This function gets the current Processor Count.
 * This read-only field defines the processor count for the chip configuration
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Processor Count
 *         -  00b : single core
 *         -  01b : dual cores
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCntPCnt(const MscmRegType *obj)
{
    return ((obj->CPU_CNT & MSCM_CPU_CNT_PCNT_MASK) >> MSCM_CPU_CNT_PCNT_SHIFT);
}

/*! \brief Gets the Instruction cache Size
 *
 * This function gets the current Instruction cache Size.
 * ICACHE_SIZE=0 means no memory, else memory size(byte) is 2^(8+ICACHE_SIZE)
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Instruction cache Size
 *         - 0h : no cache
 *         - 1h : 512
 *         - 2h : 1K
 *         - 3h : 2K
 *         - 4h : 4K
 *         - 5h : 8K
 *         - 6h : 16K
 *         - 7h : 32K
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCacheICacheSize(const MscmRegType *obj)
{
    return ((obj->CPU_CACHE & MSCM_CPU_CACHE_ICACHE_SIZE_MASK) >> MSCM_CPU_CACHE_ICACHE_SIZE_SHIFT);
}

/*! \brief Gets the Instruction cache Ways
 *
 * This function gets the current Instruction cache Ways.
 * This read-only field provides the number of cache ways for the Instruction cache.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Instruction cache Ways
 *         - 0h : not present.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCacheICacheWays(const MscmRegType *obj)
{
    return ((obj->CPU_CACHE & MSCM_CPU_CACHE_ICACHE_WAYS_MASK) >> MSCM_CPU_CACHE_ICACHE_WAYS_SHIFT);
}

/*! \brief Gets the Data Cache Size
 *
 * This function gets the current Data Cache Size.
 * DCACHE_SIZE=0 means no memory, else memory size(byte) is 2^(8+DCACHE_SIZE)
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Data Cache Size
 *         - 0h : no cache
 *         - 1h : 512
 *         - 2h : 1K
 *         - 3h : 2K
 *         - 4h : 4K
 *         - 5h : 8K
 *         - 6h : 16K
 *         - 7h : 32K
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCacheDCacheSize(const MscmRegType *obj)
{
    return ((obj->CPU_CACHE & MSCM_CPU_CACHE_DCACHE_SIZE_MASK) >> MSCM_CPU_CACHE_DCACHE_SIZE_SHIFT);
}

/*! \brief Gets the Data Cache Ways
 *
 * This function gets the current Data Cache Ways.
 * This read-only field provides the number of cache ways for the Data Cache.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Data Cache Ways
 *         - 0h : not present.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCacheDCacheWays(const MscmRegType *obj)
{
    return ((obj->CPU_CACHE & MSCM_CPU_CACHE_DCACHE_WAYS_MASK) >> MSCM_CPU_CACHE_DCACHE_WAYS_SHIFT);
}

/*! \brief Gets the SRAMU Size
 *
 * This function gets the current SRAMU Size.
 * SRAMU_SIZE=0 means no memory,else memory size(byte) is 2^(8+SRAMU_SIZE) -4
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return SRAMU Size
 *         -  0h : no sramu
 *         -  8h : 60Kbyte
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuMemSRamUSize(const MscmRegType *obj)
{
    return ((obj->CPU_MEM & MSCM_CPU_MEM_SRAMU_SIZE_MASK) >> MSCM_CPU_MEM_SRAMU_SIZE_SHIFT);
}

/*! \brief Gets the SRAML Size
 *
 * This function gets the current SRAML Size.
 * SRAML_SIZE=0 means no memory, else memory size(byte) is 2^(8+SRAML_SIZE)
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return SRAML Size
 *         - 0h : no cache
 *         - 1h : 512byte
 *         - 2h : 1Kbyte
 *         - 3h : 2Kbyte
 *         - 4h : 4Kbyte
 *         - 5h : 8Kbyte
 *         - 6h : 16Kbyte
 *         - 7h : 32Kbyte
 *         - 8h : 64Kbyte
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuMemSRamLSize(const MscmRegType *obj)
{
    return ((obj->CPU_MEM & MSCM_CPU_MEM_SRAML_SIZE_MASK) >> MSCM_CPU_MEM_SRAML_SIZE_SHIFT);
}

/*! \brief Gets the System Bus Ports
 *
 * This function gets the current System Bus Ports.
 * This field defines the number of physical connections to the system bus fabric for this processor
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return System Bus Ports
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgBusPorts(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_BUS_PORTS_MASK) >> MSCM_CPU_CFG_BUS_PORTS_SHIFT);
}

/*! \brief Gets the Bit Banding enable
 *
 * This function gets the current Bit Banding enable.
 * This field defines if the processor supports "bit banding".
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Bit Banding enable
 *         - 0b : Bit Banding is not supported.
 *         - 1b : Bit Banding is supported.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgBB(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_BB_MASK) >> MSCM_CPU_CFG_BB_SHIFT);
}

/*! \brief Gets the Core Memory Protection unit
 *
 * This function gets the current Core Memory Protection unit.
 * This field indicates if the core memory protection hardware is included in the processor.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Core Memory Protection unit
 *         - 0b : Core Memory Protection is not included.
 *         - 1b : Core Memory Protection is included.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgSmpu(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_SMPU_MASK) >> MSCM_CPU_CFG_SMPU_SHIFT);
}

/*! \brief Gets the Memory Management Unit
 *
 * This function gets the current Memory Management Unit.
 * This field indicates if the virtual memory management capabilities are supported in the processor.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Memory Management Unit
 *         - 0b : MMU support is not included.
 *         - 1b : MMU support is included.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgMmu(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_MMU_MASK) >> MSCM_CPU_CFG_MMU_SHIFT);
}

/*! \brief Gets the Trust Zone
 *
 * This function gets the current Trust Zone.
 * This field indicates if the Trust Zone capabilities are supported in the processor..
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Trust Zone
 *         - 0b : Trust Zone support is not included.
 *         - 1b : Trust Zone support is included.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgTrustZone(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_TRUST_ZONE_MASK) >> MSCM_CPU_CFG_TRUST_ZONE_SHIFT);
}

/*! \brief Gets the Jazelle support
 *
 * This function gets the current Jazelle support.
 * This field indicates if Jazelle hardware is supported in the processor.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return Jazelle support
 *         - 0b : Jazelle support is not included.
 *         - 1b : Jazelle support is included.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgJaz(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_JAZ_MASK) >> MSCM_CPU_CFG_JAZ_SHIFT);
}

/*! \brief Gets the SIMD/NEON instruction support
 *
 * This function gets the current SIMD/NEON instruction support.
 * This field indicates if the instruction set extensions supporting SIMD and/or NEON capabilities
 * are supported in the processor.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return SIMD/NEON instruction support
 *         - 0b : SIMD/NEON support is not included.
 *         - 1b : SIMD/NEON support is included.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgSimd(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_SIMD_MASK) >> MSCM_CPU_CFG_SIMD_SHIFT);
}

/*! \brief Gets the FPU support
 *
 * This function gets the current FPU support.
 *
 * \param[in] obj : pointer to MSCM register instance
 * \return FPU support
 *         - 0b : FPU support is not included.
 *         - 1b : FPU support is included.
 */
__attribute__((always_inline)) static inline uint8_t MscmReg_GetCpuCfgFpu(const MscmRegType *obj)
{
    return ((obj->CPU_CFG & MSCM_CPU_CFG_FPU_MASK) >> MSCM_CPU_CFG_FPU_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _MSCM_REG_H_ */
