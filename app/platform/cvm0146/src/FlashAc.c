/**
 * @file    FlashAc.c
 * @brief   PFlash 擦除 / 写入 / 校验（boot 与 app 共用的最底层接口）
 *
 * @details @section FLASHAC_WHY 为什么单独一层
 *          boot 要写槽尾 meta，app 要写"非活动槽"的镜像。两边如果各自
 *          `#include "mcu.h"` 直接怼 `FlashDrv_*`，就会出现两份对齐规则、
 *          两份关中断范围、两份回读校验 —— 升级时改了一处漏了另一处，
 *          症状是"boot 写得进、app 写不进"或者反过来。
 *
 *          所以这里只做三件事：**对齐检查、关中断、写完回读确认**，
 *          上层（boot_core / 刷写业务）只管"擦哪个地址、写哪段数据"。
 *
 *          @section FLASHAC_CRITICAL 为什么必须关中断
 *          厂商的 `FlashDrv_CommandSequence()` 是纯忙等：
 *          @code
 *          FtfcReg_SetFstatCcif(reg, 1);
 *          while (0U == FtfcReg_GetFstatCcif(reg)) { }   // 期间没有任何超时
 *          @endcode
 *          命令执行期间 FTFC 会占住 Flash 阵列。此时若来一个中断，
 *          CPU 要去 Flash 里取中断向量和 ISR 指令 —— 轻则被硬件 stall
 *          几十毫秒（CAN 收帧直接丢），重则取到无效数据。
 *
 *          所以擦/写期间一律 `cpsid i`，操作完按**进入前的 PRIMASK**
 *          恢复（不是无脑 `cpsie i`：可能本来就在临界区里）。
 *          擦 2 KB 扇区约 20~40 ms，这是可以接受的中断延迟上限；
 *          整片擦除必须由上层分片（每片之间开中断喂狗），不要指望这里。
 *
 *          @section FLASHAC_PFLASH 只做 PFlash，不做 DFlash
 *          DFlash 已有 `FeeAc.c`（FEE 专用，带 FEE 的 Fls_State 语义）。
 *          本文件只管代码区 0x00000000–0x000FFFFF，两套互不干扰。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：PFlash 扇区擦/写/判空/读 |
 */

#include <string.h>

#include "platform_cvm0146.h"
#include "platform_priv.h"
#include "boot_flash_map.h"

/* ============================ [ 宏 ] ============================ */

/** @brief PFlash 扇区字节数 */
#define FLASHAC_SECTOR_BYTES    (BOOT_PFLASH_SECTOR_SIZE)

/** @brief 最小写入粒度（phrase） */
#define FLASHAC_PHRASE_BYTES    (BOOT_PFLASH_PHRASE_SIZE)

/**
 * @brief 判空时的分片长度
 * @note  `FlashDrv_Read1sSection()` 一次至少覆盖一个 FTFC 命令，
 *        按 1 KB 切段与 `FeeAc.c` 保持一致（PFlash 扇区 2 KB，正好两片）。
 */
#define FLASHAC_CHUNK_BYTES     (1024u)

/* ============================ [ 内部：临界区 ] ============================ */

/**
 * @brief 关全局中断并返回进入前的 PRIMASK
 * @return 进入前的 PRIMASK（0 = 原本开着中断，1 = 原本已在临界区）
 */
static uint32_t FlashAc_EnterCritical(void)
{
	uint32_t primask;

	__asm volatile ("mrs %0, primask" : "=r" (primask) :: "memory");
	__asm volatile ("cpsid i" ::: "memory");

	return primask;
}

/**
 * @brief 恢复进入前的 PRIMASK
 * @param[in] primask `FlashAc_EnterCritical()` 的返回值
 */
static void FlashAc_ExitCritical(uint32_t primask)
{
	__asm volatile ("msr primask, %0" :: "r" (primask) : "memory");
}

/* ============================ [ 内部：通用 ] ============================ */

/**
 * @brief 判断一段区域是否全为擦除态（0xFF）
 *
 * @param[in] addr 起始地址
 * @param[in] len  字节数
 * @retval 1 全 0xFF（可写）
 * @retval 0 有非 0xFF 字节，或硬件判空命令失败
 *
 * @note 用 `FlashDrv_Read1sSection()` 而不是逐字节比较：前者是 FTFC 的
 *       SCTRD1S 命令，由硬件整片比较（含 ECC），比 CPU 循环快两个数量级，
 *       而且能发现"ECC 已损坏但数据看起来是 0xFF"的情况。
 *
 * @warning **必须按扇区边界切段**，这是踩过的坑：
 *          `FlashDrv_Read1sSection()` 内部有这么一句
 *          @code
 *          if (ALIGNED(dest + rdsize - 1, sctsz) > ALIGNED(dest, sctsz))
 *              ret = FLASHDRV_STATUS_ERROR;      // 跨扇区直接拒绝
 *          @endcode
 *          最初只按 1 KB 固定切段，结果写到第 18 块（偏移 2040，地址 0x807F8）
 *          时这一段正好跨过 0x80800 扇区边界 —— 判空返回 ERROR，
 *          被上层当成"目标区没擦干净"，于是回 NRC 0x72 编程失败。
 *          现象是"前面十几块都正常，突然在某个固定偏移开始全失败"。
 */
static uint8_t FlashAc_IsErased(uint32_t addr, uint32_t len)
{
	uint32_t off;

	if ((len == 0u) || ((addr % FLASHAC_PHRASE_BYTES) != 0u) ||
	    ((len % FLASHAC_PHRASE_BYTES) != 0u)) {
		return 0u;
	}

	for (off = 0u; off < len; ) {
		uint32_t cur = addr + off;
		uint32_t sectorLeft = FLASHAC_SECTOR_BYTES - (cur % FLASHAC_SECTOR_BYTES);
		uint32_t chunk = len - off;
		FlashDrv_Status st;

		if (chunk > FLASHAC_CHUNK_BYTES) {
			chunk = FLASHAC_CHUNK_BYTES;
		}
		if (chunk > sectorLeft) {
			chunk = sectorLeft;   /* 不跨扇区 —— 见 @warning */
		}

		st = FlashDrv_Read1sSection(&g_mcu.flashDrv, (uint32_t *)cur, chunk);
		if (st == FLASHDRV_STATUS_WARNING) {
			/* WARNING 是"ECC 纠错后仍然一致"，数据本身是 0xFF，可以写 */
			off += chunk;
			continue;
		}
		if (st != FLASHDRV_STATUS_SUCCESS) {
			return 0u;
		}

		off += chunk;
	}

	return 1u;
}

/* ============================ [ 对外接口 ] ============================ */

Std_ReturnType Platform_FlashIsErased(uint32_t addr, uint32_t len)
{
	if ((addr >= BOOT_PFLASH_SIZE) || (len > (BOOT_PFLASH_SIZE - addr))) {
		return E_NOT_OK;
	}

	return (FlashAc_IsErased(addr, len) != 0u) ? E_OK : E_NOT_OK;
}

Std_ReturnType Platform_FlashEraseSector(uint32_t addr)
{
	uint32_t primask;
	Std_ReturnType ret;

	/* 只接受扇区边界：不对齐时 FTFC 会自己向下取整，
	 * 那等于"悄悄擦了相邻扇区"，比报错危险得多。 */
	if ((addr >= BOOT_PFLASH_SIZE) || ((addr % FLASHAC_SECTOR_BYTES) != 0u)) {
		return E_NOT_OK;
	}

	/* 已经是擦除态就直接返回：重复擦除白白消耗擦写寿命
	 * （CVM0146 PFlash 保证 10 万次，但没人愿意拿它做无意义消耗）。 */
	if (FlashAc_IsErased(addr, FLASHAC_SECTOR_BYTES) != 0u) {
		return E_OK;
	}

	primask = FlashAc_EnterCritical();
	{
		FlashDrv_Status st = FlashDrv_EraseSector(&g_mcu.flashDrv, (uint32_t *)addr,
		                                          FLASHDRV_SCTERS_RETRY);
		ret = (st == FLASHDRV_STATUS_SUCCESS) ? E_OK : E_NOT_OK;
	}
	FlashAc_ExitCritical(primask);

	if (ret != E_OK) {
		return E_NOT_OK;
	}

	/* 擦除是"把 0 变回 1"，硬件不告诉你哪一位没擦干净，只能整扇区回读 */
	return (FlashAc_IsErased(addr, FLASHAC_SECTOR_BYTES) != 0u) ? E_OK : E_NOT_OK;
}

Std_ReturnType Platform_FlashWrite(uint32_t addr, const void *data, uint32_t len)
{
	uint32_t primask;
	uint32_t off;
	Std_ReturnType ret = E_OK;
	const uint8_t *src = (const uint8_t *)data;

	if ((data == NULL) || (len == 0u) ||
	    ((addr % FLASHAC_PHRASE_BYTES) != 0u) || ((len % FLASHAC_PHRASE_BYTES) != 0u) ||
	    (addr >= BOOT_PFLASH_SIZE) || (len > (BOOT_PFLASH_SIZE - addr))) {
		return E_NOT_OK;
	}

	/* 预检整段：对非擦除区再写会得到"按位与"的垃圾值，而且硬件不报错。
	 * 这一步是唯一能在写坏之前拦住它的机会。 */
	if (FlashAc_IsErased(addr, len) == 0u) {
		return E_NOT_OK;
	}

	primask = FlashAc_EnterCritical();
	for (off = 0u; off < len; off += FLASHAC_PHRASE_BYTES) {
		uint32_t dst = addr + off;

		if (FlashDrv_ProgramPhrase(&g_mcu.flashDrv, (uint32_t *)dst,
		                           (uint8_t *)&src[off], true) != FLASHDRV_STATUS_SUCCESS) {
			ret = E_NOT_OK;
			break;
		}
	}
	FlashAc_ExitCritical(primask);

	if (ret != E_OK) {
		return E_NOT_OK;
	}

	/* 回读确认：`CheckPhrase` 让 FTFC 用期望值逐位比对（含 ECC），
	 * 比 `memcmp` 严格 —— 后者读不出 ECC 层面的问题。 */
	for (off = 0u; off < len; off += FLASHAC_PHRASE_BYTES) {
		if (FlashDrv_CheckPhrase(&g_mcu.flashDrv, (uint32_t *)(addr + off),
		                         (uint8_t *)&src[off]) != FLASHDRV_STATUS_SUCCESS) {
			return E_NOT_OK;
		}
	}

	return E_OK;
}

void Platform_FlashRead(uint32_t addr, void *buf, uint32_t len)
{
	if ((buf == NULL) || (len == 0u) || (addr >= BOOT_PFLASH_SIZE) ||
	    (len > (BOOT_PFLASH_SIZE - addr))) {
		return;
	}

	/* PFlash 在 CPU 地址空间里可直接寻址，读不需要走 FTFC 命令。
	 * 注意：这也意味着**正在被擦写的扇区读不到** —— 调用方必须保证
	 * 读的地址不在本次擦除范围内。 */
	(void)memcpy(buf, (const void *)addr, (size_t)len);
}
