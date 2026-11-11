/**
 * @file    boot_app.c
 * @brief   应用侧的 A/B 配合：槽地址对账、首次自注册、启动确认
 *
 * @details 本文件是 app 与 boot 之间**唯一的耦合点**，刻意做得很薄：
 *          只调 `BootMeta_*` 那五个接口，不碰 Flash、不碰分区算术。
 *          分区变了只改 `boot_flash_map.h`，这里一行不用动。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：自注册 + 启动确认 |
 */

#include "boot_app.h"

#include "platform_cvm0146.h"
#include "boot_meta.h"
#include "Crc.h"

/* ============================ [ 链接期符号 ] ============================ */

/**
 * @brief 本镜像向量表地址（= 槽基址，由链接脚本 `m_interrupts` 段给出）
 * @note  用它与 `APP_SLOT_INDEX` 对账，能立刻抓住"烧错文件"。
 */
extern const uint32_t __VECTOR_TABLE;

/**
 * @brief 本镜像 ROM 内容的末尾（`.customSectionBlock` 的 ROM 副本终点）
 * @note  链接脚本里 `__CUSTOM_END = __CUSTOM_ROM + (...)  `，是最后一个
 *        带 ROM 内容的段的结束地址。用它算镜像长度比"读 map 文件"可靠。
 */
extern const uint32_t __CUSTOM_END;

/* ============================ [ 内部 ] ============================ */

/** @brief 本镜像所属的槽（编译期由 `APP_SLOT_INDEX` 决定） */
static uint8_t s_slot = (uint8_t)APP_SLOT_INDEX;

/** @brief 是否已初始化过（防止重复注册） */
static uint8_t s_initialized = 0u;

/**
 * @brief 算本镜像的 CRC32
 * @param[in] base 镜像基址
 * @param[in] size 字节数
 * @return CRC32
 * @note  与 boot 侧 `BootMeta_CheckImage` 用**同一份算法**（`Crc_CalculateCRC32`，
 *        初值 0xFFFFFFFF）。两边算法不一致时，症状是"每次上电都判 CRC 失败"，
 *        但 meta 结构本身又是好的 —— 极难定位。
 */
static uint32_t BootApp_CalcImageCrc(uint32_t base, uint32_t size)
{
	return Crc_CalculateCRC32((const uint8_t *)base, size, 0xFFFFFFFFu, TRUE);
}

/* ============================ [ 对外接口 ] ============================ */

uint8_t BootApp_GetSlot(void)
{
	return s_slot;
}

void BootApp_Init(void)
{
	uint32_t base;
	uint32_t size;
	uint32_t expect;
	uint32_t crc;
	const Boot_SlotInfoType *info;

	if (s_initialized != 0u) {
		return;
	}

	base   = (uint32_t)&__VECTOR_TABLE;
	size   = (uint32_t)&__CUSTOM_END - base;
	expect = BOOT_SLOT_BASE(s_slot);

	/* ---- 1) 槽地址对账 ---- */
	if (base != expect) {
		/* 烧错文件：镜像链接在别的槽。继续跑会在第一次解引用全局变量时跳飞，
		 * 那种"偶发 HardFault"在现场几乎无法定位，所以宁可就地停住。 */
		Platform_Printf("\n[app] FATAL: image linked at 0x%08X but slot %c is 0x%08X\n",
		                (unsigned)base,
		                (s_slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
		                (unsigned)expect);
		Platform_Puts("[app] wrong image for this slot (App vs AppB). HALT.\n");
		for (;;) {
			__asm volatile ("nop");
		}
	}

	/* ---- 2) 兜底长度检查 ---- */
	if ((size < BOOT_PFLASH_PHRASE_SIZE) || (size > BOOT_SLOT_IMAGE_MAX)) {
		Platform_Printf("[app] FATAL: image size %u out of range\n", (unsigned)size);
		for (;;) {
			__asm volatile ("nop");
		}
	}

	/* ---- 3) 读 meta，与当前镜像对账；缺失或不符则自注册 ----
	 *
	 * 为什么要比对 imageCrc 而不是只看 meta 存在：
	 * 用 J-Link 重烧 app（开发时天天做）不会更新槽尾 meta，
	 * 于是 meta 里记的还是上一版镜像的 CRC —— boot 下次校验必然失败，
	 * 表现是"刚烧完还能跑，一复位就 HALT: no valid image"。
	 * 这类问题会让人误以为 boot 有 bug。
	 *
	 * 代价是每次启动多算一次 CRC（159 KB 约 8 ms），换来的是
	 * "J-Link 烧完直接能跑"，值。
	 */
	BootMeta_Init();
	info = BootMeta_GetSlot(s_slot);

	crc = BootApp_CalcImageCrc(base, size);

	if ((info != NULL) && (info->metaValid != 0u) &&
	    (info->meta.imageSize == size) && (info->meta.imageCrc == crc)) {
		Platform_Printf("[app] slot %c meta ok  state=%u  rc=%u  crc=%08X\n",
		                (s_slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
		                (unsigned)info->meta.state,
		                (unsigned)info->meta.rollingCounter,
		                (unsigned)crc);
	} else {
		Platform_Printf("[app] slot %c meta %s, self-register  size=%u crc=%08X\n",
		                (s_slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B',
		                ((info != NULL) && (info->metaValid != 0u)) ? "mismatch" : "missing",
		                (unsigned)size, (unsigned)crc);

		(void)BootMeta_Register(s_slot, size, crc,
		                        (uint8_t)APP_VERSION_MAJOR,
		                        (uint8_t)APP_VERSION_MINOR,
		                        (uint8_t)APP_VERSION_PATCH);
	}

	s_initialized = 1u;
}

void BootApp_Confirm(void)
{
	if (s_initialized == 0u) {
		return;
	}

	if (BootMeta_Confirm(s_slot) == E_OK) {
		Platform_Printf("[app] boot confirmed for slot %c\n",
		                (s_slot == BOOT_SLOT_INDEX_A) ? 'A' : 'B');
	} else {
		Platform_Puts("[app] boot confirm failed (meta write error)\n");
	}
}
