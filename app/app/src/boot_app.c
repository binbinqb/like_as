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

#include "platform.h"          /* Platform_NowMs / Platform_Reset（芯片无关契约） */
#include "platform_cvm0146.h"  /* Platform_FlashWrite：BootMeta 依赖 */
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
	 * 代价是每次启动多算一次 CRC（245 KB 实测约 77 ms，见 `bootperf`），换来的是
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

		/* ---- 3b) 版本对账 ----
		 *
		 * 为什么需要它：UDS 刷写（`0x37`）写 meta 时不带版本字段 ——
		 * `FlashLoader_TransferExit()` 是 `memset` 之后逐字段赋值的，
		 * 只填 rollingCounter / imageSize / imageCrc / programmingCounter /
		 * state / attempts，版本停在 0.0.0。
		 *
		 * 而本分支说明 `imageSize/imageCrc` 与 meta 完全一致，所以**不会**
		 * 走下面的 self-register —— 版本就永远补不上。上板实测：
		 * 刷写前 `v2.8.0`，刷写后 `v0.0.0`，之后再怎么复位都还是 0.0.0。
		 *
		 * 只补版本这三个字节，**其余字段一字不动**：rollingCounter 参与选槽，
		 * state/bootAttempts 参与回滚，动它们等于改变启动行为。
		 * 只有"版本不一致"才写，所以正常启动不会反复擦 meta。 */
		if ((info->meta.versionMajor != (uint8_t)APP_VERSION_MAJOR) ||
		    (info->meta.versionMinor != (uint8_t)APP_VERSION_MINOR) ||
		    (info->meta.versionPatch != (uint8_t)APP_VERSION_PATCH)) {
			Boot_MetaType vmeta = info->meta;

			vmeta.versionMajor = (uint8_t)APP_VERSION_MAJOR;
			vmeta.versionMinor = (uint8_t)APP_VERSION_MINOR;
			vmeta.versionPatch = (uint8_t)APP_VERSION_PATCH;

			if (BootMeta_Write(s_slot, &vmeta) == E_OK) {
				Platform_Printf("[app] meta version -> %u.%u.%u\n",
				                (unsigned)vmeta.versionMajor,
				                (unsigned)vmeta.versionMinor,
				                (unsigned)vmeta.versionPatch);
			} else {
				Platform_Puts("[app] meta version write failed\n");
			}
		}
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

/* ==================== [ App → Boot 刷写交接 ] ==================== */

/**
 * @brief 等正响应发出去的时间（ms）
 *
 * @details 为什么不是 0：`Dcm_SessionChangeIndication()` 是在**正响应组包之前**
 *          被调用的（见 `Dcm_Dsp.c` 的调用点），此刻复位会让诊断仪收不到
 *          `50 03`，工具报超时。
 *          为什么不是 1000：刷写工具那边本来就要等 ECU 重启，多等 1 s 只是
 *          让整个刷写流程变慢，没有收益。
 *          150 ms 覆盖"单帧响应 + 总线仲裁失败重传几次"。
 */
#define BOOTAPP_FLASH_DELAY_MS      (150u)

/** @brief 交接状态：0=空闲 1=已请求（等响应） 2=已处理（不再动作） */
static uint8_t  s_flashReq;

/** @brief 请求时刻（`Platform_NowMs()`） */
static uint32_t s_flashReqAt;

void BootApp_RequestFlashMode(void)
{
	if (0u != s_flashReq) {
		return;   /* 幂等：重复进编程会话不重置计时 */
	}

	s_flashReq   = 1u;
	s_flashReqAt = Platform_NowMs();

	Platform_Puts("[app] programming session -> will reboot into bootloader\n");
}

void BootApp_MainFunction(void)
{
	const Boot_SlotInfoType *info;
	Boot_MetaType meta;

	if (1u != s_flashReq) {
		return;
	}

	/* 等 `50 03` 上总线。这里不能用"进入本函数就说明响应已发"这种假设 ——
	 * Dcm 的 indication 回调发生在响应组包之前。 */
	if ((uint32_t)(Platform_NowMs() - s_flashReqAt) < BOOTAPP_FLASH_DELAY_MS) {
		return;
	}

	/* 先置 2 再写 Flash：写失败也**不重试**。理由见 boot_app.h 的说明 ——
	 * 重试会反复擦 meta 扇区（每次擦都是一次寿命 + 一次掉电风险窗口），
	 * 而失败原因基本只有"Flash 坏"，重试不会改变结果。 */
	s_flashReq = 2u;

	info = BootMeta_GetSlot(s_slot);
	if ((info == NULL) || (0u == info->metaValid)) {
		Platform_Puts("[app] meta invalid, cannot hand over to bootloader\n");
		return;
	}

	/* 只改 reserved[0]，其余字段（含 rollingCounter / state / CRC）原样保留：
	 * boot 用 rollingCounter 选槽，这里动了它等于改变"谁是活动槽"。 */
	meta = info->meta;
	meta.reserved[0] = (uint8_t)BOOT_META_REQ_FLASH;

	if (BootMeta_Write(s_slot, &meta) != E_OK) {
		Platform_Puts("[app] write flash request FAILED, staying in app\n");
		return;
	}

	Platform_Puts("[app] flash request written, resetting into boot\n");

	/* 让串口那行字发完（115200 下约 1 ms / 10 字节，这里给足余量）。
	 * 不能用 Platform_NowMs() 等：SysTick 可能已被下面的复位流程影响，
	 * 而且这是最后几毫秒，忙等最简单可靠。 */
	{
		volatile uint32_t d = 40000u;
		while (d-- > 0u) {
		}
	}

	Platform_Reset();
}
