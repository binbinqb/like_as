/**
 * @file    platform_cvm0146.h
 * @brief   **Host 测试专用**的 CVM0146 平台头替身：只留 Flash 三个函数
 *
 * @details @section BOOTSIM_WHY 为什么可以替身，替换的到底是什么
 *
 *          `BootMeta.c`（被测代码）只碰平台的三个 Flash 函数：
 *          `Platform_FlashRead` / `Platform_FlashWrite` / `Platform_FlashEraseSector`。
 *          其余平台能力（时钟、串口、CAN）它一概不用。
 *
 *          所以这里**只替身"Flash 器件"这一层**，把 PFlash 换成一块 1 MB 的
 *          内存数组（见 `test_boot_meta.c`）。被验证的选槽 / 校验 / 计数 /
 *          回滚判定，全部是被板上编译的同一份 `BootMeta.c` 原样执行 ——
 *          不是按理解重写一个模型。
 *
 *          @warning 本目录**只**参与 Host 的 `boot_meta` 用例，靠
 *          `-I app/platform/host/include/boot_sim` 排在真实平台头**之前**
 *          来生效。板级构建（SCons）的 include 路径里没有它，
 *          因此不可能污染固件。
 *
 * @note    刻意**不**包含任何 SDK 头：那会把寄存器定义拉进 Host 编译，
 *          而本用例要证明的恰恰是"判定逻辑与芯片无关"。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：Flash 三函数的声明替身 |
 */

#ifndef PLATFORM_CVM0146_H
#define PLATFORM_CVM0146_H

#include <stdint.h>

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ======================== [ 与真实平台同签名 ] ======================== */

/** @brief 读 Flash（真实实现在 `platform_cvm0146.c`：直读映射地址） */
void Platform_FlashRead(uint32_t addr, void *buf, uint32_t len);

/** @brief 写 Flash（真实实现按 8 字节 phrase 写；这里按字节 memcpy） */
Std_ReturnType Platform_FlashWrite(uint32_t addr, const void *data, uint32_t len);

/** @brief 擦除一个扇区（真实实现按 2 KB 扇区；这里按 2 KB 填 0xFF） */
Std_ReturnType Platform_FlashEraseSector(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_CVM0146_H */
