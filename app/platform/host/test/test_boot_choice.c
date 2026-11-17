/**
 * @file    test_boot_choice.c
 * @brief   Host 上的**选槽判定**用例：开发模式 / 量产模式各一套断言
 *
 * @details @section CHOICETEST_HOW 同一份源码编两次
 *
 *          `boot_choice.c` 的策略由编译期 `BOOT_MODE_PRODUCTION` 决定，所以
 *          这里用 `-D` 编出两个可执行文件，各自断言自己那一套：
 *
 *          | 用例 | 现场 | 开发模式（=0） | 量产模式（=1） |
 *          |------|------|----------------|----------------|
 *          | C1 | A 好镜像 | 跳 A | 跳 A |
 *          | C2 | A 陈旧 meta（坏镜像）+ B 好 | 降级跳 A | **判 A=INVALID，回滚 B** |
 *          | C3 | C2 连续上电 5 次 | 第 4 次后回滚 B | 第 1 次就回滚 B |
 *          | C4 | 无 meta + A 向量表像话 | 跳 A（首次烧写兜底） | **不跳，等刷写** |
 *          | C5 | 无 meta + 向量表也不像 | 等刷写 | 等刷写 |
 *          | C6 | A=TESTING 好镜像，连续启动失败 | 第 4 次判 INVALID 回滚 B | 同左 |
 *
 *          @note C3 是 22.3 的核心回归：开发模式下"降级照跳"必须仍然能被
 *          尝试计数兜住（否则 D1 复发），量产模式下第一次就不该跳坏镜像。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：6 组 × 两模式 |
 */

#include <stdio.h>

#include "boot_choice.h"
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

/** @brief 一次"上电"：重新读 meta，然后走一遍选槽判定 */
static Boot_ChoiceType power_on(void)
{
	BootMeta_Init();
	return Boot_ChooseSlot();
}

static void case_good_image(void)
{
	Boot_ChoiceType c;

	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);

	c = power_on();
	check(c.decision == BOOT_DECISION_JUMP, "C1 好镜像：决定跳转");
	check(c.slot == BOOT_SLOT_INDEX_A, "C1 好镜像：跳到 A");
}

/**
 * @brief C2/C3：陈旧 meta（meta 完好、镜像 CRC 不符）
 *
 * 开发模式：降级 TESTING 后照跳，靠尝试计数兜底
 * 量产模式：直接判 A=INVALID，回滚 B
 */
static void case_stale_meta(void)
{
	Boot_ChoiceType c;
	const Boot_SlotInfoType *info;

#if BOOT_MODE_PRODUCTION
	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 1, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	BootSim_Program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 9u, 0);

	c = power_on();
	check(c.decision == BOOT_DECISION_JUMP, "C2 量产：决定跳转");
	check(c.slot == BOOT_SLOT_INDEX_B, "C2 量产：**不跳坏镜像**，回滚到 B");

	info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
	check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_INVALID),
	      "C2 量产：A 被判 INVALID 落盘（下次上电不再选它）");

	c = power_on();
	check((c.decision == BOOT_DECISION_JUMP) && (c.slot == BOOT_SLOT_INDEX_B),
	      "C3 量产：再上电仍稳定跳 B");
#else
	uint8_t round;

	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 1, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 10u, 0);
	BootSim_Program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 9u, 0);

	c = power_on();
	check((c.decision == BOOT_DECISION_JUMP) && (c.slot == BOOT_SLOT_INDEX_A),
	      "C2 开发：陈旧 meta → 降级后**照跳 A**（保住 J-Link 重烧的自恢复）");

	info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
	check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_TESTING) &&
	      (info->meta.bootAttempts == 1u),
	      "C2 开发：A 已降级 TESTING、尝试次数=1");

	/* 模拟"跳进去起不来"：连续上电，计数必须累加，第 4 次判 INVALID 回滚 B */
	for (round = 0u; round < 5u; round++) {
		c = power_on();
	}

	check((c.decision == BOOT_DECISION_JUMP) && (c.slot == BOOT_SLOT_INDEX_B),
	      "C3 开发：连续 5 次上电后回滚到 B（计数没有被反复清零）");

	info = BootMeta_GetSlot(BOOT_SLOT_INDEX_A);
	check((info != NULL) && (info->meta.state == (uint8_t)BOOT_SLOT_INVALID),
	      "C3 开发：A 最终判 INVALID");
#endif
}

/** @brief C4/C5：没有任何有效 meta */
static void case_no_meta(void)
{
	Boot_ChoiceType c;

	/* C4：A 的向量表像话（首次烧写的典型现场） */
	BootSim_EraseAll();
	BootSim_PutU32(BOOT_SLOT_A_BASE + 0u, BOOTSIM_IMG_SP);
	BootSim_PutU32(BOOT_SLOT_A_BASE + 4u, BOOT_SLOT_A_BASE + 0x101u);

	c = power_on();
#if BOOT_ALLOW_VECTOR_FALLBACK
	check((c.decision == BOOT_DECISION_JUMP) && (c.slot == BOOT_SLOT_INDEX_A),
	      "C4 开发：无 meta 但向量表像话 → 跳 A（首次烧写兜底）");
#else
	check(c.decision == BOOT_DECISION_WAIT_FLASH,
	      "C4 量产：无 meta 一律不跳，等刷写（不做向量表兜底）");
#endif

	/* C5：向量表也不像话 */
	BootSim_EraseAll();
	c = power_on();
	check(c.decision == BOOT_DECISION_WAIT_FLASH, "C5 两槽都空：等刷写");
}

/** @brief C6：TESTING 好镜像 + 连续启动失败 → 第 4 次判 INVALID 回滚 */
static void case_testing_rollback(void)
{
	Boot_ChoiceType c;
	uint8_t round;

	BootSim_EraseAll();
	BootSim_Program(BOOT_SLOT_INDEX_A, 0, (uint8_t)BOOT_SLOT_TESTING, 0u, 10u, 0);
	BootSim_Program(BOOT_SLOT_INDEX_B, 0, (uint8_t)BOOT_SLOT_CONFIRMED, 0u, 9u, 0);

	for (round = 0u; round < 4u; round++) {
		c = power_on();
	}

	check((c.decision == BOOT_DECISION_JUMP) && (c.slot == BOOT_SLOT_INDEX_B),
	      "C6 TESTING 连续启动失败：第 4 次回滚到 B");
}

int main(void)
{
	(void)printf("== Boot 选槽判定（Host，%s）==\n",
	             (BOOT_MODE_PRODUCTION != 0) ? "量产模式 BOOT_MODE_PRODUCTION=1"
	                                         : "开发模式 BOOT_MODE_PRODUCTION=0");

	case_good_image();
	case_stale_meta();
	case_no_meta();
	case_testing_rollback();

	(void)printf("-- %u passed, %u failed\n", (unsigned)s_pass, (unsigned)s_fail);
	return (s_fail == 0u) ? 0 : 1;
}
