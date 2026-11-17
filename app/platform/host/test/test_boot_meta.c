/**
 * @file    test_boot_meta.c
 * @brief   Host 上的 Boot 元数据用例：选槽、镜像校验、降级、尝试计数、回滚
 *
 * @details @section BOOTMETA_WHAT 这个用例回答什么
 *
 *          22.3「复位恢复」的判据不能靠"读代码觉得对"。这里把**板上编译的
 *          同一份 `BootMeta.c`** 拿到 Host 上跑，只把 Flash 换成内存数组
 *          （见 `boot_sim_flash.c`）。
 *
 *          @section BOOTMETA_MATRIX 判据矩阵（本文件逐条断言）
 *
 *          | 编号 | 现场 | 期望 |
 *          |------|------|------|
 *          | B1 | 两槽全 0xFF（未烧写） | 无活动槽；meta 无效时**不**降级 |
 *          | B2 | A=CONFIRMED，镜像好 | 选 A，校验通过（分段 CRC 与一次性等价） |
 *          | B3 | A=CONFIRMED，镜像坏（meta 陈旧） | 校验失败、可降级、**尝试次数保留** |
 *          | B4 | 上述状态连续上电 | 计数累加，第 4 次判 INVALID（回滚能触发） |
 *          | B5 | A=TESTING，镜像好，连续上电 | 计数 1→2→3→4 超限 → INVALID |
 *          | B6 | A=INVALID，B=CONFIRMED 好 | 回滚到 B |
 *          | B7 | 两槽都 INVALID | 无活动槽（main 进 UDS） |
 *          | B8 | 主 meta 损坏、备 meta 好 | 主备择优，仍可用 |
 *          | B9 | 向量表 SP 非法但 CRC 对 | 校验失败（向量表检查独立于 CRC） |
 *
 *          @warning B3/B4 是 22.3 缺陷 D1 的回归。修复前 `DemoteToTesting`
 *          会把 `bootAttempts` 清零，B4 表现为"计数恒为 1、永不 INVALID"；
 *          修复后必须累加。这两条一旦回退，说明有人又把清零加回去了。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：9 组判定 |
 * | V1.1.0 | 2026-11-17 | binbina | D1 修复后反转 B3/B4 断言；夹具抽到 boot_sim |
 */

#include <stdio.h>

#include "boot_meta.h"
#include "boot_flash_map.h"
#include "boot_sim.h"

static uint32_t s_pass;
static uint32_t s_fail;

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

/* ============================ [ 用例 ] ============================ */

static void case_empty(void)
{
	BootSim_EraseAll();
	BootMeta_Init();

	check(BOOT_NO_ACTIVE_SLOT == BootMeta_GetActiveSlot(), "B1 空槽：无活动槽");
	check(E_NOT_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B1 空槽：A 校验失败");
	check(E_NOT_OK == BootMeta_DemoteToTesting(BOOT_SLOT_INDEX_A),
	      "B1 空槽：meta 无效时**不**降级（不会盲目跳转）");
}

static void case_good_image(void)
{
	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	BootMeta_Init();

	check(BOOT_SLOT_INDEX_A == BootMeta_GetActiveSlot(), "B2 A=CONFIRMED：选中 A");
	check(E_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A),
	      "B2 镜像完好：分段 CRC 与向量表均通过（＝与一次性算等价）");
}

static void case_stale_meta(void)
{
	const Boot_SlotInfoType *info;

	BootSim_EraseAll();
	/* attempts 刻意给 2：用来证明降级**不清零** */
	BootSim_Program(BOOT_SLOT_INDEX_A, 1, (uint8_t)BOOT_SLOT_CONFIRMED, 2u, 10u, 0);
	BootMeta_Init();

	check(BOOT_SLOT_INDEX_A == BootMeta_GetActiveSlot(), "B3 镜像坏但 meta 好：仍选中 A");
	check(E_NOT_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B3 镜像 CRC 失败");
	check(E_OK == BootMeta_DemoteToTesting(BOOT_SLOT_INDEX_A),
	      "B3 降级返回成功（陈旧 meta 与真损坏在此不可区分）");

	info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
	check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_TESTING) &&
	      (info->meta.bootAttempts == 2u),
	      "B3 降级后：state=TESTING 且尝试次数**保留为 2**（D1 回归点）");
}

/**
 * @brief B4：复刻"镜像坏 → 降级 → 跳转 → 起不来 → 复位"的循环
 *
 * @details 修复前：每次降级都把计数清零，10 轮后仍是 1，永不 INVALID。
 *          修复后：计数累加，第 4 轮 `PrepareJump` 返回失败并判 INVALID。
 */
static void case_demote_loop(void)
{
	uint8_t round;
	uint8_t invalidAt = 0u;
	uint8_t attempts[5];
	const Boot_SlotInfoType *info;

	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 1, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);

	for (round = 0u; round < 5u; round++) {
		BootMeta_Init();                    /* 等价于一次上电 */

		(void)BootMeta_CheckImage(BOOT_SLOT_INDEX_A);   /* 必然失败 */
		(void)BootMeta_DemoteToTesting(BOOT_SLOT_INDEX_A);

		if (BootMeta_PrepareJump(BOOT_SLOT_INDEX_A) != E_OK) {
			if (invalidAt == 0u) {
				invalidAt = (uint8_t)(round + 1u);
			}
			attempts[round] = 0xFFu;
			continue;
		}

		info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
		attempts[round] = (info != NULL) ? info->meta.bootAttempts : 0xFEu;
	}

	check((attempts[0] == 1u) && (attempts[1] == 2u) && (attempts[2] == 3u),
	      "B4 计数逐轮累加 1→2→3（不再被降级清零）");
	check(invalidAt == 4u, "B4 第 4 轮判 INVALID（回滚可被触发）");

	{
		BootMeta_Init();
		info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
		check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_INVALID),
		      "B4 INVALID 落盘（复位后仍有效）");
		check(BOOT_NO_ACTIVE_SLOT == BootMeta_GetActiveSlot(),
		      "B4 判 INVALID 后该槽不再被选中");
	}
}

static void case_testing_counter(void)
{
	uint8_t round;
	uint8_t invalid = 0u;

	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_TESTING, 0u, 10u, 0);

	for (round = 0u; round < 4u; round++) {
		BootMeta_Init();
		if (BootMeta_CheckImage(BOOT_SLOT_INDEX_A) != E_OK) {
			break;
		}
		if (BootMeta_PrepareJump(BOOT_SLOT_INDEX_A) != E_OK) {
			invalid = 1u;
		}
	}

	check(invalid != 0u, "B5 镜像好的 TESTING：第 4 次跳转被判 INVALID");
}

static void case_rollback(void)
{
	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_INVALID, 0u, 10u, 0);
	BootSim_Program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 9u, 0);
	BootMeta_Init();

	check(BOOT_SLOT_INDEX_B == BootMeta_GetActiveSlot(), "B6 A 无效 + B 有效：回滚到 B");
	check(E_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_B), "B6 B 槽镜像校验通过");
}

static void case_all_invalid(void)
{
	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_INVALID, 0u, 10u, 0);
	BootSim_Program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_INVALID, 0u, 9u, 0);
	BootMeta_Init();

	check(BOOT_NO_ACTIVE_SLOT == BootMeta_GetActiveSlot(),
	      "B7 两槽都 INVALID：无活动槽（main 停在 UDS）");
}

static void case_backup_meta(void)
{
	const Boot_SlotInfoType *info;

	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	BootSim_CorruptPrimaryMeta(BOOT_SLOT_INDEX_A);
	BootMeta_Init();

	info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
	check((info != NULL) && (info->metaValid != 0u),
	      "B8 主 meta 损坏、备 meta 好：仍判定有效（主备择优）");
	check(E_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A), "B8 镜像仍可校验通过");
}

static void case_bad_vector(void)
{
	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 1);
	BootMeta_Init();

	check(E_NOT_OK == BootMeta_CheckImage(BOOT_SLOT_INDEX_A),
	      "B9 CRC 正确但初始 MSP 越界：校验失败（向量表检查独立）");
}

int main(void)
{
	(void)printf("== Boot 元数据与镜像校验（Host，真编译 BootMeta.c）==\n");

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
