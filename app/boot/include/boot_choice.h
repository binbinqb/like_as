/**
 * @file    boot_choice.h
 * @brief   Boot 的选槽判定（从 `main.c` 抽出，便于离板验证）
 *
 * @details @section CHOICE_WHY 为什么单独成一个单元
 *
 *          这段判定是"镜像坏了会怎样"的唯一出口，也是最需要反复回归的地方。
 *          留在 `main.c` 里的问题：它和 `Platform_Init` / UDS / 跳转混在一起，
 *          只能上板才能验证。抽出来之后，`test_boot_choice.c` 在 Host 上就能
 *          把**开发模式与量产模式**各跑一遍（同一份源码，用
 *          `-DBOOT_MODE_PRODUCTION=0/1` 编两次）。
 *
 *          @note 本文件**不做**跳转、不进 UDS，只回答"该跳哪一槽 / 该等刷写"。
 *          副作用只有两类：写 meta（降级 / 判 INVALID / 尝试计数）与串口打印。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 从 main.c 抽出选槽判定，支持开发/量产两套策略 |
 */

#ifndef BOOT_CHOICE_H
#define BOOT_CHOICE_H

#include "Std_Types.h"
#include "boot_flash_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 选槽的结论类型 */
typedef enum {
	BOOT_DECISION_JUMP       = 0u,  /**< 跳到 `slot` 指定的槽 */
	BOOT_DECISION_WAIT_FLASH = 1u   /**< 没有可用镜像：停在 UDS 等刷写 */
} Boot_DecisionType;

/** @brief `Boot_ChooseSlot()` 的结果 */
typedef struct {
	Boot_DecisionType decision;  /**< 跳转 / 等刷写 */
	uint8_t           slot;      /**< `decision == BOOT_DECISION_JUMP` 时有效 */
} Boot_ChoiceType;

/**
 * @brief 按两个槽的 meta 与镜像校验结果决定"跳哪一槽"
 *
 * @details 调用前必须先 `BootMeta_Init()`。本函数会**写 meta**：
 *          - 开发模式：镜像校验失败时降级为 TESTING（保留尝试次数）
 *          - 量产模式：镜像校验失败时直接判 INVALID
 *          - 两种情况都会在跳转前累加 TESTING 的尝试次数，超限判 INVALID
 *
 * @return 判定结果（跳转槽号，或"等刷写"）
 *
 * @pre `BootMeta_Init()` 已调用
 */
Boot_ChoiceType Boot_ChooseSlot(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_CHOICE_H */
