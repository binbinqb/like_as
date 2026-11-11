/**
 * @file    Fee_Cfg.h
 * @brief   FEE 配置：DFlash 扇区划分、块表、块号定义
 *
 * @details @section FEECFG_LAYOUT DFlash 用哪一段
 *          整颗 CVM0146 的 DFlash 是 256 KB（0x1000_0000 起），但**后 128 KB
 *          （0x1002_0000–0x1003_FFFF）在 `EEEVLD=1` 时是硬件模拟 EEPROM 的备份区，
 *          AXBS 读不到**（RM 表 32-2）。所以本工程只用前 128 KB，且实际只占最前面 24 KB：
 *
 *          @code
 *          0x1000_0000  ┌──────────────────────────┐
 *                       │ FEE sector 0   12 KB     │  活动扇区（新数据写这里）
 *          0x1000_3000  ├──────────────────────────┤
 *                       │ FEE sector 1   12 KB     │  备份扇区（GC 时整扇区搬过去）
 *          0x1000_6000  ├──────────────────────────┤
 *                       │ 预留 104 KB              │  DTC 快照 / 未来扩展
 *          0x1002_0000  └──────────────────────────┘
 *          @endcode
 *
 *          @section FEECFG_SECTOR 为什么是"2 个扇区 × 12 KB"而不是"1 个 24 KB"
 *          FEE 是**日志式**存储：每次写都在活动扇区尾部追加，旧数据不覆盖。
 *          活动扇区写满后，要把每个块的最新版本搬到备份扇区、再把活动扇区擦掉
 *          （这就是 GC）。两个扇区是这套机制的最小可行配置：
 *            - 只有一个扇区 → 写满即无法回收，只能全擦，掉电必丢全部数据；
 *            - 扇区越大 → 单次 GC 搬的数据越多、擦除时间越长；
 *            - 扇区太小 → GC 频繁，擦写寿命消耗快。
 *          12 KB 是按"BCM 的 NVM 总量几百字节"估的：一次全量重写约 216 字节，
 *          能撑 50 多次全量写才触发一次 GC，留有余量。
 *
 *          @section FEECFG_BLOCK 块长为什么是"载荷 + 1"
 *          NvM 在每块数据末尾追加 1 字节 CRC8（`NVM_CRC8`），FEE 只认字节数、
 *          不管语义，所以 `Fee` 侧的块长 = NvM 的载荷长 + 1。
 *          两侧数字在文件末尾用 `#if` 做了**编译期对账**，改一处漏改另一处会直接
 *          报 `#error`，而不是运行时读到错位的数据。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：2×12 KB DFlash 扇区 + 4 个块 |
 */

#ifndef FEE_CFG_H
#define FEE_CFG_H

/*
 * 厂商 fee_sector.h:571 有一处 `bool gcSectorCnt; ... gcSectorCnt++;`
 * （`Fee_SearchGcSector()` 里数"有几个候选备份扇区"），GCC 10 的 `-Wall`
 * 会报 `-Wbool-operation`。这是厂商代码里真实存在的小瑕疵：
 * bool 自增会饱和在 1，不过在本工程 2 个扇区的配置下不会触发
 * （候选扇区最多 1 个），行为无影响。
 *
 * 处理方式：**不改厂商文件**（升级时整目录覆盖），在包含处关掉这一条告警。
 * 全工程就只有这一处会触发它，所以只在本地关，不污染全局 CFLAGS。
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbool-operation"
#include "fee/fee_types.h"
#pragma GCC diagnostic pop

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 扇区 ] ============================ */

/** @brief 扇区个数：活动 + 备份，最小可行配置（见文件头说明） */
#define FEE_CFG_SECTOR_NUM              (2u)

/** @brief 单个扇区字节数（12 KB）。必须是 `FEE_SECTION_LENGTH`（1 KB）的整数倍 */
#define FEE_CFG_SECTOR_BYTES            (0x3000u)

/**
 * @brief 单个扇区含几个 1 KB 擦除片
 * @note  FEE 擦扇区是**分片**的：每次 `Fee_MainFunction()` 只擦 1 KB，
 *        12 片分 12 次擦完，避免一次阻塞十几毫秒把主循环卡死。
 *        必须等于 `FEE_CFG_SECTOR_BYTES / 1024`。
 */
#define FEE_CFG_ERASE_SECTION_NUM       (12u)

/** @brief 活动扇区 0 基址 */
#define FEE_CFG_SECTOR0_ADDR            (0x10000000u)

/** @brief 备份扇区 1 基址 */
#define FEE_CFG_SECTOR1_ADDR            (FEE_CFG_SECTOR0_ADDR + FEE_CFG_SECTOR_BYTES)

/**
 * @brief FEE 内部中转缓存（RAM）
 *
 * @warning **长度必须 ≥ 最大的块长（8 字节对齐后）**，不是"几十字节够拼包头"。
 *
 *          厂商 FEE 在 GC 搬块时用它当中转：
 *          @code
 *          fee.c:776  read (oldBlockAddr, obj->buff, blocksize)   // 读一整块
 *          fee.c:799  write(newBlockAddr, obj->buff, blocksize)   // 写一整块
 *          @endcode
 *          也就是说这块缓存要能放下一整个块的数据，而不是 16 字节的块头。
 *
 *          **踩过的坑**：最初按厂商 demo 抄了 64 字节。日常写（只拼 16 字节块头）
 *          完全正常；跑到第 200 多次、活动扇区写满触发第一次 GC 时，
 *          72 字节的 DTC 块把后面 8 字节冲掉 —— 而紧邻的正是
 *          `NvM_Initialized`，于是 `NvM_GetStatus()` 从此返回 `MEMIF_UNINIT`，
 *          所有读写全部失效，**没有任何报错**。
 *          症状是"跑几分钟后存储突然全哑"。
 *
 *          所以这里直接取最大块长，并在下面用 `#if` 逐块校验。
 */
#define FEE_CFG_MAX_BLOCK_BYTES         (ALIGN8BYTE(FEE_CFG_BLK_DTC_BYTES))

/** @brief FEE 内部中转缓存长度（= 最大块长，见上） */
#define FEE_CFG_CACHE_BYTES             (FEE_CFG_MAX_BLOCK_BYTES)

/* 逐块校验：任何一个块的 8 字节对齐长度超过缓存，编译期直接失败。
 * 新增块时忘了改缓存，会在这里被拦住，而不是运行时冲掉别的变量。 */
#if (FEE_CFG_CACHE_BYTES < ALIGN8BYTE(FEE_CFG_BLK_BOOTCNT_BYTES))
#error "FEE_CFG_CACHE_BYTES 小于 BOOTCNT 块长，GC 搬块时会越界"
#endif
#if (FEE_CFG_CACHE_BYTES < ALIGN8BYTE(FEE_CFG_BLK_CONFIG_BYTES))
#error "FEE_CFG_CACHE_BYTES 小于 CONFIG 块长，GC 搬块时会越界"
#endif
#if (FEE_CFG_CACHE_BYTES < ALIGN8BYTE(FEE_CFG_BLK_VIN_BYTES))
#error "FEE_CFG_CACHE_BYTES 小于 VIN 块长，GC 搬块时会越界"
#endif
#if (FEE_CFG_CACHE_BYTES < ALIGN8BYTE(FEE_CFG_BLK_DTC_BYTES))
#error "FEE_CFG_CACHE_BYTES 小于 DTC 块长，GC 搬块时会越界"
#endif

/* ============================ [ 块号 ] ============================ */
/*
 * 块号必须是 **16 的整数倍**：厂商 NvM 把块号的低 4 位当作"数据集编号"
 * （`NVM_DATASET_SELECTION_BITS = 4`），`NVM_GET_BLOCKNUMBER()` 会把低 4 位抹掉。
 * 写成 0x11 的话，NvM 找块时会去搜 0x10，永远搜不到，而且不报错 —— 只是读不到。
 *
 * 编号留了间隔（0x10/0x20/0x30/0x40），每个块最多可带 16 个数据集。
 */

/** @brief 启动计数（AC 每次上电 +1，用来证明"数据真的掉电保持"） */
#define FEE_CFG_BLK_BOOTCNT             (0x10u)

/** @brief 车辆配置字（BCM 的一般配置，掉电保持） */
#define FEE_CFG_BLK_CONFIG              (0x20u)

/** @brief VIN 码（17 字节 ASCII） */
#define FEE_CFG_BLK_VIN                 (0x30u)

/** @brief 故障快照（非立即写，靠 `Nvm_WriteAll()` 在停机前统一落盘） */
#define FEE_CFG_BLK_DTC                 (0x40u)

/** @brief 块表项数（必须与 `Fee_Cfg.c` 的数组长度一致） */
#define FEE_CFG_BLOCK_NUM               (4u)

/* ============================ [ 块长（FEE 侧 = NvM 载荷 + CRC8） ] ============================ */

/** @brief 启动计数：载荷 8 + CRC8 1 */
#define FEE_CFG_BLK_BOOTCNT_BYTES       (9u)

/** @brief 配置字：载荷 32 + CRC8 1 */
#define FEE_CFG_BLK_CONFIG_BYTES        (33u)

/** @brief VIN：载荷 17 + CRC8 1 */
#define FEE_CFG_BLK_VIN_BYTES           (18u)

/** @brief 故障快照：载荷 64 + CRC8 1 */
#define FEE_CFG_BLK_DTC_BYTES           (65u)

/* ============================ [ 对外对象 ] ============================ */

/**
 * @brief FEE 驱动实例（供 `Fee_Configure()` / `Fee_MainFunction()` 使用）
 * @note  叫 `Driver` 而不是 `Config`：`FeeType` 里除了配置还有运行期状态，
 *        不是一份只读表。踩过的坑：把它当 const 配置传进 `Fee_Write()`，
 *        块指针会被写坏。
 */
extern const FeeType Fee_Driver;

/* ============================ [ 平台 AC 层（定义在 src/FeeAc.c） ] ============================ */

/**
 * @brief FEE 的底层方法表：把"读/写/擦/可写/CRC8"落到 CVM0146 的 DFlash
 * @note  厂商 `Fee_Configure()` 不检查这个指针是否为空 —— 传 NULL 会在第一次
 *        读扇区时跳到地址 0（HardFault）。所以它必须是编译期就绑定好的常量表。
 */
extern const Fee_MethodType FeeAc_FlsMethod;

/**
 * @brief 存储栈的平台侧初始化（关 LMEM 缓存 + 配 flash 驱动）
 * @pre   必须已调用 `Platform_Init()`（它里面的 `Mcu_Init()` 才填好 `g_mcu.flashDrv`）
 * @note  必须在 `Fee_Configure()` **之前**调用
 */
void FeeAc_Init(void);

/**
 * @brief CRC8（表驱动，初值 0xFF，结果取反）
 * @param[in] sAddr 数据起始地址
 * @param[in] size  字节数
 * @return CRC8 结果
 * @note  FEE 与 NvM **共用这一份**。两层各写一份相同的表看似无害，
 *        实际会在升级时漂移：改了一层的初值，另一层就永远校验失败。
 */
uint8_t FeeAc_CalcCrc8(void *sAddr, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* FEE_CFG_H */
