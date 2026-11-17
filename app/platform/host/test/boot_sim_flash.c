/**
 * @file    boot_sim_flash.c
 * @brief   1 MB 假 PFlash + 现场构造（Boot 判定用例共用的实现）
 *
 * @details @section SIM_WHAT 替身替到哪一层
 *
 *          只替 `Platform_FlashRead` / `Platform_FlashWrite` /
 *          `Platform_FlashEraseSector` 三个函数，以及串口打印。被验证的
 *          `BootMeta.c` 与 `boot_choice.c` 是**板上编译的同一份源码**。
 *
 *          @warning `Platform_FlashWrite` 刻意模拟真 Flash 的约束：只能往
 *          擦除态（0xFF）写。不模拟就测不出"忘了先擦"这类错 —— 而
 *          `BootMeta_WriteOne` 正是靠"先擦后写"才成立的。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：从 test_boot_meta.c 抽出并加打印 |
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boot_sim.h"
#include "Crc.h"
#include "perf_mon.h"
#include "Std_Types.h"

/* ============================ [ 假 Flash ] ============================ */

/** @brief 1 MB PFlash 的内存替身（地址就是下标，与板级映射一一对应） */
static uint8_t s_flash[BOOT_PFLASH_SIZE];

void Platform_FlashRead(uint32_t addr, void *buf, uint32_t len)
{
	(void)memcpy(buf, &s_flash[addr], (size_t)len);
}

Std_ReturnType Platform_FlashWrite(uint32_t addr, const void *data, uint32_t len)
{
	const uint8_t *p = (const uint8_t *)data;
	uint32_t i;

	if ((addr + len) > BOOT_PFLASH_SIZE) {
		return E_NOT_OK;
	}

	for (i = 0u; i < len; i++) {
		if (s_flash[addr + i] != 0xFFu) {
			return E_NOT_OK;
		}
	}

	(void)memcpy(&s_flash[addr], data, (size_t)len);
	return E_OK;
}

Std_ReturnType Platform_FlashEraseSector(uint32_t addr)
{
	if (((addr % BOOT_PFLASH_SECTOR_SIZE) != 0u) ||
	    ((addr + BOOT_PFLASH_SECTOR_SIZE) > BOOT_PFLASH_SIZE)) {
		return E_NOT_OK;
	}

	(void)memset(&s_flash[addr], 0xFF, (size_t)BOOT_PFLASH_SECTOR_SIZE);
	return E_OK;
}

/* ============================ [ 串口替身 ] ============================ */

/**
 * @brief 打印替身
 *
 * @note 用例失败时最需要看到的就是 boot 自己打的那几行（"boot anyway as
 *       TESTING" / "image rejected"），所以这里**不静音**，直接透到 stdout。
 *       需要安静时把环境变量 `BOOTSIM_QUIET=1` 设上。
 */
int Platform_Printf(const char *fmt, ...)
{
	va_list ap;

	if (getenv("BOOTSIM_QUIET") != NULL) {
		return 0;
	}

	va_start(ap, fmt);
	(void)vprintf(fmt, ap);
	va_end(ap);
	return 0;
}

void Platform_Puts(const char *s)
{
	if (getenv("BOOTSIM_QUIET") != NULL) {
		return;
	}
	(void)fputs(s, stdout);
}

/* ============================ [ PerfMon 替身 ] ============================ */

/**
 * @brief 周期计数器替身
 *
 * @details 真实现读 DWT->CYCCNT，Host 上没有这个寄存器。这里给一个**确定性**
 *          的递增计数器：每读一次前进 1200 周期（= 10 µs @120 MHz）。
 *          目的是让 `Boot_CheckImageTimed()` 那条打印能算出数来，
 *          **不是**用来断言"校验耗时多少" —— 那个数只有板上才有意义。
 */
static uint32_t s_cyc;

uint32_t PerfMon_Cycles(void)
{
	s_cyc += 1200u;
	return s_cyc;
}

/** @brief 周期 → 微秒（主频 120 MHz，与 Board.json 的 coreClockHz 一致） */
uint32_t PerfMon_CyclesToUs(uint32_t cycles)
{
	return cycles / 120u;
}

/* ============================ [ 现场构造 ] ============================ */

void BootSim_EraseAll(void)
{
	(void)memset(s_flash, 0xFF, sizeof(s_flash));
}

void BootSim_PutU32(uint32_t addr, uint32_t v)
{
	s_flash[addr + 0u] = (uint8_t)(v & 0xFFu);
	s_flash[addr + 1u] = (uint8_t)((v >> 8) & 0xFFu);
	s_flash[addr + 2u] = (uint8_t)((v >> 16) & 0xFFu);
	s_flash[addr + 3u] = (uint8_t)((v >> 24) & 0xFFu);
}

void BootSim_Program(uint8_t slot, int corrupt, uint8_t state,
                     uint8_t attempts, uint32_t rolling, int badSp)
{
	uint32_t base = BOOT_SLOT_BASE(slot);
	uint32_t i;
	uint32_t crc;
	Boot_MetaType meta;

	for (i = 0u; i < BOOTSIM_IMG_SIZE; i++) {
		s_flash[base + i] = (uint8_t)((i * 7u) & 0xFFu);
	}
	BootSim_PutU32(base + 0u, (badSp != 0) ? 0x30000000u : BOOTSIM_IMG_SP);
	BootSim_PutU32(base + 4u, base + 0x101u);

	/* CRC 按**改坏之前**的镜像算 —— 这样才能构造出"meta 里的 CRC 是旧镜像的、
	 * 槽里是新/坏的镜像"这个真实场景。 */
	crc = Crc_CalculateCRC32(&s_flash[base], BOOTSIM_IMG_SIZE, 0xFFFFFFFFu, TRUE);

	if (corrupt != 0) {
		s_flash[base + 0x40u] ^= 0xFFu;
	}

	(void)memset(&meta, 0, sizeof(meta));
	meta.rollingCounter = rolling;
	meta.imageSize      = BOOTSIM_IMG_SIZE;
	meta.imageCrc       = crc;
	meta.state          = state;
	meta.bootAttempts   = attempts;
	meta.reserved[0]    = (uint8_t)BOOT_META_REQ_NONE;
	(void)BootMeta_Write(slot, &meta);
}

void BootSim_CorruptPrimaryMeta(uint8_t slot)
{
	(void)memset(&s_flash[BOOT_SLOT_META_PRIMARY(slot)], 0x5A, sizeof(Boot_MetaType));
}
