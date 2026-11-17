/**
 * @file    test_boot_meta.c
 * @brief   Host 上的 Boot 启动判定用例：选槽、镜像校验、降级、尝试计数、回滚
 *
 * @details @section BOOTMETA_WHAT 这个用例要回答什么
 *
 *          22.3「复位恢复」的判据不能靠"读代码觉得对"。这里把**板上编译的
 *          同一份 `BootMeta.c`** 拿到 Host 上跑，只把 Flash 换成内存数组
 *          （见 `boot_sim/platform_cvm0146.h` 的说明）。
 *
 *          重点验证一条：**镜像 CRC 失败后降级成 TESTING 的那条路径，
 *          尝试计数到底会不会累加、能不能触发回滚**。
 *          代码注释写的是"3 次后判 INVALID 并回滚"，B4 就是去证伪它。
 *
 *          @section BOOTMETA_MATRIX 启动判定矩阵（本文件逐条断言）
 *
 *          | 编号 | 现场 | 期望 |
 *          |------|------|------|
 *          | B1 | 两槽全 0xFF（未烧写） | 无活动槽；meta 无效时**不**降级 |
 *          | B2 | A=CONFIRMED，镜像好 | 选 A，校验通过 |
 *          | B3 | A=CONFIRMED，镜像坏（meta 陈旧） | 校验失败、可降级、计数被清零 |
 *          | B4 | 上述状态连续上电 10 次 | 计数**不累加**，永不 INVALID（缺陷证据） |
 *          | B5 | A=TESTING，镜像好，连续上电 | 计数 1→2→3→4 超限 → INVALID（对照） |
 *          | B6 | A=INVALID，B=CONFIRMED 好 | 回滚到 B |
 *          | B7 | 两槽都 INVALID | 无活动槽（main 进 UDS） |
 *          | B8 | 主 meta 损坏、备 meta 好 | 主备择优，仍可用 |
 *          | B9 | 向量表 SP 非法但 CRC 对 | 校验失败（向量表检查独立于 CRC） |
 *
 * @warning B4 是**缺陷复现**，不是期望行为。它现在通过，说明代码确实有这个问题；
 *          修完 Boot 逻辑后 B4 必须改成"断言累加并回滚"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：9 组判定，含降级不计数的复现 |
 */

#include <stdio.h>
#include <string.h>

#include "boot_meta.h"
#include "boot_flash_map.h"
#include "Crc.h"

/* ============================ [ 假 Flash ] ============================ */

/** @brief 1 MB PFlash 的内存替身（地址就是下标，与板级映射一一对应） */
static uint8_t s_flash[BOOT_PFLASH_SIZE];

static uint32_t s_pass;
static uint32_t s_fail;

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

	/* 真 PFlash 只能往擦除态（0xFF）写，且只能把 1 变 0。
	 * 这里刻意**模拟这个约束**：不模拟就测不出"忘了擦就写"这类错 ——
	 * 而 `BootMeta_WriteOne` 正是靠"先擦后写"才成立的。 */
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

/* ============================ [ 断言 ] ============================ */

static void check(int cond, const char *what)
{
	if (cond != 0) {
		s_pass++;
		(void)printf("  [ OK ] %s\n", what);
	} else {
		s_fail++;
		(void)printf("  [FAIL] %s\n", what);
	}
}

/* ============================ [ 现场构造 ] ============================ */

/** @brief 用例里的镜像长度：够过"≥ phrase 且 4 字节对齐"两道检查即可 */
#define IMG_SIZE    (1024u)

/** @brief 一个"像话"的初始 MSP，落在 `BootMeta.c` 认定的 SRAM 区间内 */
#define IMG_SP      (0x20001000u)

static void put_u32(uint32_t addr, uint32_t v)
{
	s_flash[addr + 0u] = (uint8_t)(v & 0xFFu);
	s_flash[addr + 1u] = (uint8_t)((v >> 8) & 0xFFu);
	s_flash[addr + 2u] = (uint8_t)((v >> 16) & 0xFFu);
	s_flash[addr + 3u] = (uint8_t)((v >> 24) & 0xFFu);
}

/** @brief 整片 Flash 回到擦除态（等价于"刚出厂的片子"） */
static void flash_erase_all(void)
{
	(void)memset(s_flash, 0xFF, sizeof(s_flash));
}

/**
 * @brief 往槽里铺一个镜像，并写一条 meta
 *
 * @param[in] slot     槽号
 * @param[in] corrupt  非 0：铺完镜像后改坏一个字节（CRC 必然对不上）
 * @param[in] state    `Boot_SlotStateType`
 * @param[in] attempts `bootAttempts`
 * @param[in] rolling  `rollingCounter`
 * @param[in] badSp    非 0：把初始 MSP 换成非法值（向量表检查该拦）
 */
static void slot_program(uint8_t slot, int corrupt, uint8_t state,
                         uint8_t attempts, uint32_t rolling, int badSp)
{
	uint32_t base = BOOT_SLOT_BASE(slot);
	uint32_t i;
	uint32_t crc;
	Boot_MetaType meta;

	for (i = 0u; i < IMG_SIZE; i++) {
		s_flash[base + i] = (uint8_t)((i * 7u) & 0xFFu);
	}
	put_u32(base + 0u, (badSp != 0) ? 0x30000000u : IMG_SP);
	put_u32(base + 4u, base + 0x101u);      /* Reset_Handler，落在槽内 */

	/* CRC 按**改坏之前**的镜像算 —— 这样才能构造出
	 * "meta 里的 CRC 是旧镜像的、槽里是新/坏的镜像"这个真实场景。 */
	crc = Crc_CalculateCRC32(&s_flash[base], IMG_SIZE, 0xFFFFFFFFu, TRUE);

	if (corrupt != 0) {
		s_flash[base + 0x40u] ^= 0xFFu;
	}

	(void)memset(&meta, 0, sizeof(meta));
	meta.rollingCounter = rolling;
	meta.imageSize      = IMG_SIZE;
	meta.imageCrc       = crc;
	meta.state          = state;
	meta.bootAttempts   = attempts;
	meta.reserved[0]    = (uint8_t)BOOT_META_REQ_NONE;
	(void)BootMeta_Write(slot, &meta);
}

/** @brief 把某个槽的主 meta 扇区写成垃圾（模拟擦写中断电 / 位翻转） */
static void meta_corrupt_primary(uint8_t slot)
{
	(void)memset(&s_flash[BOOT_SLOT_META_PRIMARY(slot)], 0x5A, sizeof(Boot_MetaType));
}

/* ============================ [ 用例 ] ============================ */

static void case_empty(void)
{
	flash_erase_all();
	BootMeta_Init();

	check(BOOT_NO_ACTIVE_SLOT == BootMeta_GetActiveSlot(), "B1 空槽：无活动槽");
	check(E_NOT_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B1 空槽：A 校验失败");
	check(E_NOT_OK == BootMeta_DemoteToTesting(BOOT_SLOT_INDEX_A),
	      "B1 空槽：meta 无效时**不**降级（不会盲目跳转）");
}

static void case_good_image(void)
{
	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	BootMeta_Init();

	check(BOOT_SLOT_INDEX_A == BootMeta_GetActiveSlot(), "B2 A=CONFIRMED：选中 A");
	check(E_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B2 镜像完好：CRC + 向量表通过");
}

static void case_stale_meta(void)
{
	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 1, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	BootMeta_Init();

	check(BOOT_SLOT_INDEX_A == BootMeta_GetActiveSlot(), "B3 镜像坏但 meta 好：仍选中 A");
	check(E_NOT_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B3 镜像 CRC 失败");
	check(E_OK == BootMeta_DemoteToTesting(BOOT_SLOT_INDEX_A),
	      "B3 **降级仍返回成功**（陈旧 meta 与真损坏在此不可区分）");

	{
		const Boot_SlotInfoType *info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);

		check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_TESTING) &&
		      (info->meta.bootAttempts == 0u),
		      "B3 降级后：state=TESTING 且尝试次数被**清零**");
	}
}

/**
 * @brief B4：复刻 `boot/main.c` 第 707~721 行的降级循环，连续上电 10 次
 *
 * @details 每轮只做 main 在"校验失败且可降级"分支里做的事：
 *          `CheckImage` → `DemoteToTesting` → `PrepareJump`。
 *          若注释里"3 次后判 INVALID 并回滚"成立，第 4 轮之后计数必须超限。
 */
static void case_demote_loop(void)
{
	uint8_t round;
	uint8_t stateAlwaysTesting = 1u;
	uint8_t attemptsNeverGrow = 1u;
	uint8_t attemptsLast = 0u;

	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 1, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);

	for (round = 0u; round < 10u; round++) {
		const Boot_SlotInfoType *info;

		BootMeta_Init();                     /* 等价于一次上电 */

		if (BootMeta_GetActiveSlot() != BOOT_SLOT_INDEX_A) {
			stateAlwaysTesting = 0u;
		}
		if (BootMeta_CheckImage(BOOT_SLOT_INDEX_A) == E_OK) {
			stateAlwaysTesting = 0u;         /* 这里本就不该通过 */
		}
		if (BootMeta_DemoteToTesting(BOOT_SLOT_INDEX_A) != E_OK) {
			attemptsNeverGrow = 0u;
		}
		if (BootMeta_PrepareJump(BOOT_SLOT_INDEX_A) != E_OK) {
			attemptsNeverGrow = 0u;
		}

		info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
		if (info == NULL) {
			stateAlwaysTesting = 0u;
			break;
		}
		if (info->meta.state != (uint8_t)BOOT_SLOT_TESTING) {
			stateAlwaysTesting = 0u;
		}
		if (info->meta.bootAttempts != 1u) {
			attemptsNeverGrow = 0u;
		}
		attemptsLast = info->meta.bootAttempts;
	}

	check(stateAlwaysTesting != 0u, "B4 10 轮降级启动：始终 TESTING（从不 INVALID）");
	check(attemptsNeverGrow != 0u, "B4 10 轮降级启动：尝试次数每轮都被清回 1（不累加）");
	check(attemptsLast == 1u, "B4 第 10 轮后计数仍为 1 → **永不回滚**（缺陷复现）");
	check(BOOT_SLOT_INDEX_A == BootMeta_GetActiveSlot(),
	      "B4 A 仍是活动槽：降级路径绕过了尝试计数");
}

static void case_testing_counter(void)
{
	uint8_t round;
	uint8_t invalid = 0u;

	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_TESTING, 0u, 10u, 0);

	for (round = 0u; round < 4u; round++) {
		BootMeta_Init();
		if (BootMeta_CheckImage(BOOT_SLOT_INDEX_A) != E_OK) {
			break;
		}
		if (BootMeta_PrepareJump(BOOT_SLOT_INDEX_A) != E_OK) {
			invalid = 1u;
		}
	}

	check(invalid != 0u, "B5 对照组：镜像好的 TESTING，第 4 次跳转被判 INVALID");
	{
		const Boot_SlotInfoType *info;

		BootMeta_Init();
		info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
		check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_INVALID),
		      "B5 INVALID 落盘（复位后仍有效）");
		check(BOOT_NO_ACTIVE_SLOT == BootMeta_GetActiveSlot(),
		      "B5 判 INVALID 后该槽不再被选中");
	}
}

static void case_rollback(void)
{
	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_INVALID, 0u, 10u, 0);
	slot_program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 9u, 0);
	BootMeta_Init();

	check(BOOT_SLOT_INDEX_B == BootMeta_GetActiveSlot(), "B6 A 无效 + B 有效：回滚到 B");
	check(E_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_B), "B6 B 槽镜像校验通过");
}

static void case_all_invalid(void)
{
	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_INVALID, 0u, 10u, 0);
	slot_program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_INVALID, 0u, 9u, 0);
	BootMeta_Init();

	check(BOOT_NO_ACTIVE_SLOT == BootMeta_GetActiveSlot(),
	      "B7 两槽都 INVALID：无活动槽（main 停在 UDS）");
}

static void case_backup_meta(void)
{
	const Boot_SlotInfoType *info;

	flash_erase_all();
	slot_program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	meta_corrupt_primary(BOOT_SLOT_INDEX_A);
	BootMeta_Init();

	info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
	check((info != NULL) && (info->metaValid != 0u),
	      "B8 主 meta 损坏、备 meta 好：仍判定有效（主备择优）");
	check(E_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B8 镜像仍可校验通过");
}

static void case_bad_vector(void)
{
	flash_erase_all();
	/* 初始 MSP 越界，但 CRC 是按这份内容算的 —— CRC 对，向量表不对 */
	slot_program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 1);
	BootMeta_Init();

	check(E_NOT_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A),
	      "B9 CRC 正确但初始 MSP 越界：校验失败（向量表检查独立）");
}

int main(void)
{
	(void)printf("== Boot 启动判定（Host，真编译 BootMeta.c）==\n");

	case_empty();
	case_good_image();
	case_stale_meta();
	case_demote_loop();
	case_testing_counter();
	case_rollback();
	case_all_invalid();
	case_backup_meta();
	case_bad_vector();

	(void)printf("-- %u passed, %u failed\n", (unsigned)s_pass, (unsigned)s_fail);
	return (s_fail == 0u) ? 0 : 1;
}
