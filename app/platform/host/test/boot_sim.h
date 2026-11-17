/**
 * @file    boot_sim.h
 * @brief   Boot 判定用例的共享夹具：1 MB 假 Flash + 现场构造
 *
 * @details 两个用例（`test_boot_meta.c` / `test_boot_choice.c`）用同一套现场
 *          构造方式，否则"A 槽坏镜像"在两处会被做成两种不同的坏法，
 *          断言就不可比。
 *
 *          实现放在 `boot_sim_flash.c`（单独一个 TU）：`Platform_FlashRead`
 *          等符号必须唯一，不能每个用例各定义一份。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：从 test_boot_meta.c 抽出 |
 */

#ifndef BOOT_SIM_H
#define BOOT_SIM_H

#include <stdint.h>

#include "boot_meta.h"
#include "boot_flash_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 用例里的镜像长度（够过"≥ phrase 且 4 字节对齐"两道检查） */
#define BOOTSIM_IMG_SIZE    (1024u)

/** @brief 一个"像话"的初始 MSP，落在 `BootMeta.c` 认定的 SRAM 区间内 */
#define BOOTSIM_IMG_SP      (0x20001000u)

/** @brief 整片 Flash 回到擦除态（等价于"刚出厂的片子"） */
void BootSim_EraseAll(void);

/** @brief 往指定地址写 32 位小端值（构造向量表用） */
void BootSim_PutU32(uint32_t addr, uint32_t v);

/**
 * @brief 往槽里铺一个镜像并写一条 meta
 *
 * @param[in] slot     槽号
 * @param[in] corrupt  非 0：铺完镜像后改坏一个字节（CRC 必然对不上）
 * @param[in] state    `Boot_SlotStateType`
 * @param[in] attempts `bootAttempts`
 * @param[in] rolling  `rollingCounter`
 * @param[in] badSp    非 0：把初始 MSP 换成非法值
 */
void BootSim_Program(uint8_t slot, int corrupt, uint8_t state,
                     uint8_t attempts, uint32_t rolling, int badSp);

/** @brief 把某个槽的主 meta 扇区写成垃圾（模拟擦写中断电） */
void BootSim_CorruptPrimaryMeta(uint8_t slot);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_SIM_H */
