/**
 * @file    NvM_Cfg.h
 * @brief   NvM 块 id 与长度（**面向应用侧，零厂商类型**）
 *
 * @details @section NVMBLK_SPLIT 为什么这里一个厂商头都不 include
 *          本工程把存储栈切成两个面：
 *          | 文件 | 谁看得见 | 里面有什么 |
 *          |------|----------|------------|
 *          | `NvM_Cfg.h`（本文件） | 应用 / Dcm / Dem | 只有块 id、长度、数量 |
 *          | `NvM_Cfg.c` | 只在平台层编译 | 厂商块表 + `NvM_Port*` 实现 |
 *
 *          这样应用写 `NvM_ReadBlock(NVM_CFG_ID_VIN, buf)` 时，
 *          完全不会把 `Nvm_BlockItemType`、`FeeType` 这些厂商类型拖进编译单元。
 *          如果本文件去 include 厂商头，应用的每个 TU 都会被迫解析一遍
 *          `nvm_types.h` / `fee_types.h` —— 既拖慢编译，也让"应用不依赖厂商"
 *          这条约束变成一句空话。
 *
 *          @section NVMBLK_ID id 与块号是两回事
 *          - **id**（本文件定义的 `NVM_CFG_ID_*`）：AUTOSAR 的 `NvM_BlockIdType`，
 *            是从 0 开始的数组下标，上层只认它；
 *          - **块号**（`0x10 / 0x20 / ...`）：写进 DFlash 块头里的值，由 `Fee_Cfg.h` 定义。
 *          id 与块号的对应关系只在 `NvM_Cfg.c` 的块表里出现一次。
 *
 *          @section NVMBLK_SIZE 载荷长度 vs 缓冲长度
 *          `NVM_CFG_BLK_*_SIZE` 是**有效数据长度**（不含 CRC）。
 *          `NvM_GetBlockDataPtrAndLength()` 返回的就是它。
 *          但块在 RAM 里实际占的字节更多 —— 厂商引擎按
 *          `ALIGN8BYTE(载荷 + CRC)` 做 `memset/memcpy`，所以配置表里开的数组
 *          必须用 `NVM_CFG_BYTES()`。开小了不会报错，只会悄悄踩掉相邻数组。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：4 个块 |
 */

#ifndef NVM_CFG_H
#define NVM_CFG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 规模 ] ============================ */

/** @brief 块表项数（合法 id 范围 0 .. NVM_CFG_BLOCK_NUM-1） */
#define NVM_CFG_BLOCK_NUM           (4u)

/**
 * @brief 引擎的用户请求队列深度
 * @note  满了以后读写请求直接返回 `NVM_RETURN_NOT_OK`（**不排队等待**），
 *        而这个返回值和"块号非法"是同一个 —— 很难区分。
 *        所以 `NvM_WriteAll()` 是"投一个、等一个"，从不把队列塞满。
 */
#define NVM_CFG_QUEUE_NUM           (4u)

/**
 * @brief 一个块在 RAM 里实际占用的字节数（载荷 + CRC8，向上取 8 字节对齐）
 * @param[in] n 载荷字节数
 * @warning 不要用它当"有效数据长度"—— 有效长度是 `n`，多出来的是 CRC 与对齐填充。
 */
#define NVM_CFG_BYTES(n)            ((((n) + 1u) + 7u) & ~7u)

/* ============================ [ 块 id（= 数组下标） ] ============================ */

#define NVM_CFG_ID_BOOTCNT          (0u)   /**< 启动计数 → 块号 0x10 */
#define NVM_CFG_ID_CONFIG           (1u)   /**< 车辆配置字 → 块号 0x20 */
#define NVM_CFG_ID_VIN              (2u)   /**< VIN 码 → 块号 0x30 */
#define NVM_CFG_ID_DTC              (3u)   /**< 故障快照 → 块号 0x40 */

/* ============================ [ 载荷长度（不含 CRC） ] ============================ */

/** @brief 启动计数：`uint32 计数 + uint32 魔数`，魔数用来区分"新片"和"真值 0" */
#define NVM_CFG_BLK_BOOTCNT_SIZE    (8u)

/** @brief 配置字：留给 BCM 的一般配置（灯光/雨刮/门锁策略），先按 32 字节预留 */
#define NVM_CFG_BLK_CONFIG_SIZE     (32u)

/** @brief VIN：固定 17 字节 ASCII，不带终止符（与 UDS 22 F1 90 一致） */
#define NVM_CFG_BLK_VIN_SIZE        (17u)

/** @brief 故障快照：4 条 × 16 字节（DTC 码 + 状态 + 发生次数 + 快照数据） */
#define NVM_CFG_BLK_DTC_SIZE        (64u)

/* ============================ [ 调试钩子 ] ============================ */

/**
 * @brief 取底层 FEE 的原始状态码（**仅供 bring-up 排查**，业务代码不要用）
 * @return 厂商 `Fee_StatusType`：0=UNINIT 1=IDLE 2=READ 3=WRITE 4=GC 5=UNKNOW 6=ERROR
 * @note  "引擎卡住"时 AUTOSAR 侧只能看到 BUSY，看不出是 FEE 在扫扇区、在 GC 还是出错。
 *        实现在 `NvM_Cfg.c`（那里才看得见厂商头）。上板调通后可以删掉。
 */
uint8_t NvM_PortDbgFeeState(void);

/** @brief 立即读作业子状态（调试用，见 NvM_Cfg.c） */
uint8_t NvM_PortDbgReadJob(void);

/** @brief NvM 状态机状态（调试用，见 NvM_Cfg.c） */
uint8_t NvM_PortDbgNvmState(void);

/** @brief FEE 上次作业结果（调试用，见 NvM_Cfg.c） */
uint8_t NvM_PortDbgJobResult(void);

/** @brief 作业槽锁状态打包（调试用，见 NvM_Cfg.c） */
uint8_t NvM_PortDbgJobs(void);

/** @brief 引擎收到的写请求次数（调试用，见 NvM_Cfg.c） */
extern volatile uint32_t NvM_Cfg_WriteCount;

#ifdef __cplusplus
}
#endif

#endif /* NVM_CFG_H */
