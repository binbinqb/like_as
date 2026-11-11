/**
 * @file    NvM_Port.h
 * @brief   NvM 引擎接口：AUTOSAR 外观（`NvM.c`）与厂商引擎之间的**唯一**通道
 *
 * @details @section NVMPORT_WHY 为什么必须有这一层
 *          本工程把两个东西拼在一起：
 *          - **外观**：标准的 `NvM_Init/NvM_ReadBlock/NvM_WriteBlock/...`（`NvM.c`）
 *          - **引擎**：厂商的 `Nvm_Read/Nvm_Write/Nvm_MainFunction/...`（`vendor/nvm`）
 *
 *          直接让外观 include 厂商头是不行的 —— **两边都定义了同名的 `NVM_REQ_*`**：
 *          @code
 *          infras/include/NvM.h:12   把 NVM_REQ_OK 定义成宏 ((NvM_RequestResultType)0x00)
 *          vendor/nvm/nvm_types.h    把 NVM_REQ_OK 定义成枚举成员 = 0x05
 *          @endcode
 *          同一个 .c 里先 include 谁都会出事：先 include 厂商头，宏会把后续所有
 *          `NVM_REQ_OK` 展开成 0（**而且不报错**，只是比较结果永远错）；先 include
 *          AUTOSAR 头，宏直接进到枚举定义里，编译不过。
 *
 *          所以中间插一层"不含任何厂商类型、也不含任何 AUTOSAR 类型"的接口：
 *          参数只有 `uint16_t` / `uint8_t` / `bool`，状态用本文件自己的枚举。
 *          谁想换引擎（比如将来换成 as-master 的 NvM），只改这一层的实现，
 *          外观和上层一行动不到。
 *
 *          @section NVMPORT_ID 两种编号不要混
 *          - **id**：AUTOSAR 的 `NvM_BlockIdType`，从 0 开始的**数组下标**，
 *            上层（Dcm / Dem / 应用）只认它；
 *          - **块号（blockNumber）**：厂商的 `0x10 / 0x20 / ...`，写进 Flash 头里的值。
 *          本头文件里所有函数**一律收 id**，块号的翻译在实现里做 ——
 *          这样调用方不需要知道厂商怎么编号，也就不会把两者搞混。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：id 制接口 + 块状态枚举 |
 */

#ifndef NVM_PORT_H
#define NVM_PORT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 类型 ] ============================ */

/**
 * @brief 请求受理结果
 * @note  只表示"仓库收下了这个作业"，不代表已完成。完成与否看
 *        `NvM_PortBlockState()`；这是 AUTOSAR NvM 一贯的异步语义。
 */
typedef enum {
	NVM_PORT_RET_OK     = 0,   /**< 已受理 */
	NVM_PORT_RET_NOT_OK = 1,   /**< 拒绝：块号非法 / 队列满 / 引擎未就绪 */
} NvM_PortRetType;

/**
 * @brief 块状态
 * @note  数值**刻意与厂商 `Nvm_BlockState` 对齐**，实现里一次强转即可，
 *        但语义以本枚举为准 —— 厂商改枚举顺序时只需改 `NvM_Cfg.c` 的映射，
 *        外观层不受影响。
 */
typedef enum {
	NVM_PORT_BLK_UNINIT           = 0x00,  /**< 从未读写过 */
	NVM_PORT_BLK_PENDING          = 0x01,  /**< 作业挂起中 */
	NVM_PORT_BLK_ERASE            = 0x02,  /**< 擦除中 */
	NVM_PORT_BLK_NOT_OK           = 0x03,  /**< 上次作业失败 */
	NVM_PORT_BLK_INTEGRITY_FAILED = 0x04,  /**< 校验失败（已回退 ROM 默认值） */
	NVM_PORT_BLK_OK               = 0x05,  /**< 上次作业成功 */
	NVM_PORT_BLK_ERROR            = 0xFF,  /**< 块不存在 / 引擎错误 */
} NvM_PortBlockStateType;

/* ============================ [ 生命周期 ] ============================ */

/**
 * @brief 初始化引擎（`Nvm_Configure`）
 * @pre   平台侧已完成 `FeeAc_Init()` 与 `Fee_Configure()`
 * @note  引擎的初始化 + 扇区扫描是**异步**的：本函数返回后引擎还没就绪，
 *        要一直调 `NvM_PortMainFunction()` 直到 `NvM_PortIsBusy()` 返回 false。
 *        期间投递的作业会排在队列里等，不会丢。
 */
void NvM_PortInit(void);

/**
 * @brief 引擎主函数（驱动状态机）
 * @warning 必须**周期性**调用。官方引擎的 NvM 层没有内部定时器，
 *          但它的作业推进完全依赖本函数被调到；不调 = 作业永远 PENDING。
 *          本工程放在 10 ms 的 BSW 调度里（与 `Fee_MainFunction()` 相邻）。
 */
void NvM_PortMainFunction(void);

/**
 * @brief 引擎是否忙（**不能**再投递新作业）
 * @retval true  队列里有未处理的作业，或有作业正在跑，或初始化未完成
 * @retval false 完全空闲
 * @note  为什么不用"IsIdle"：引擎的状态机在没有作业时也是 IDLE，但队列里可能
 *        还压着刚投递的作业（要等下一次 `NvM_PortMainFunction()` 才会被取走）。
 *        只查状态会把"刚投递"误判成"已完成"。本函数把队列也算进去，
 *        所以 `NvM_WriteAll()` 那种"投一个、等一个"的节奏才能正确推进。
 */
bool NvM_PortIsBusy(void);

/* ============================ [ 块信息 ] ============================ */

/** @brief 块总数（= AUTOSAR 合法 id 的上界） */
uint16_t NvM_PortBlockCount(void);

/**
 * @brief 取块的**有效数据长度**（不含 CRC、不含 8 字节对齐填充）
 * @param[in] id 块 id（0 起）
 * @return 长度；id 非法时返回 0
 */
uint16_t NvM_PortBlockSize(uint16_t id);

/**
 * @brief 取块的 RAM 映像地址（`NvM_WriteBlock(id, NULL)` 的写入源）
 * @param[in] id 块 id（0 起）
 * @return RAM 地址；id 非法时返回 NULL
 * @warning 该缓冲实际长度 ≥ `NvM_PortBlockSize()`，**尾部还有 CRC 与对齐填充**。
 *          上层按 `BlockSize` 用就行，不要整段 `memcpy` 出去。
 */
uint8_t *NvM_PortBlockRam(uint16_t id);

/* ============================ [ 作业 ] ============================ */

/**
 * @brief 请求读一个块
 * @param[in]  id  块 id
 * @param[out] dst 目的缓冲（长度必须 ≥ `NvM_PortBlockSize(id)`）
 * @return 受理结果
 */
NvM_PortRetType NvM_PortRead(uint16_t id, uint8_t *dst);

/**
 * @brief 请求写一个块
 * @param[in] id  块 id
 * @param[in] src 数据源（**不允许为 NULL**；`NvM_WriteBlock(id, NULL)` 的
 *                "写自己的 RAM 映像"语义由 `NvM.c` 翻译成 `NvM_PortBlockRam(id)`）
 * @return 受理结果
 */
NvM_PortRetType NvM_PortWrite(uint16_t id, const uint8_t *src);

/**
 * @brief 请求把**全部块**读进各自的 RAM 映像（上电快启动用）
 * @return 受理结果
 * @note  读不消耗 Flash 寿命，全部读一遍没有代价。
 */
NvM_PortRetType NvM_PortReadAll(void);

/**
 * @brief 查询块的当前状态
 * @param[in] id 块 id
 * @return 见 `NvM_PortBlockStateType`
 */
NvM_PortBlockStateType NvM_PortBlockState(uint16_t id);

#ifdef __cplusplus
}
#endif

#endif /* NVM_PORT_H */
