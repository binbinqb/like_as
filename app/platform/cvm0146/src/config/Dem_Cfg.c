/**
 * @file    Dem_Cfg.c
 * @brief   Dem 配置的编译期对账（没有运行期代码）
 *
 * @details @section DEMCFGC_WHY 为什么一个"空"的 .c 文件
 *          三个理由，都不是为了凑数：
 *
 *          1. **`$Dem_Cfg` 这个头文件路径要有个注册点**。框架的
 *             `RegisterConfig` 需要一个非空 source 才能推出目录，
 *             光有 `Dem_Cfg.h` 注册不进来。
 *
 *          2. **对账必须是编译期**。DTC 块长、记录长度、表容量
 *             三者一旦不自洽，症状是"写进去的 DTC 读出来是另一条"
 *             —— 这种错位在运行期只表现为数据乱码，几乎无法定位。
 *             放在这里用 `#error` 卡死，改一处漏改另一处直接编译不过。
 *             这与 `NvM_Cfg.c` 顶部那段 `#if` 是同一个思路。
 *
 *          3. **将来换成完整 Dem 时，配置自然会落在这里**。
 *             那时这个文件会从 30 行长到几百行（事件表、DTC 表、
 *             去抖参数、冻结帧），但文件位置和职责不变。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：块长/记录长度/表容量对账 |
 */

#include "Dem_Cfg.h"

/* ============================ [ 编译期对账 ] ============================ */

/** @brief 块长必须是记录长度的整数倍，否则最后一条会被截断 */
#if ((DEM_CFG_NVM_BLOCK_BYTES % DEM_CFG_DTC_RECORD_BYTES) != 0u)
#error "DTC 块长必须是记录长度（16 字节）的整数倍"
#endif

/** @brief 表容量不能为 0，也不该没有上限（上限防止误改块长把 RAM 吃光） */
#if (DEM_CFG_MAX_DTC == 0u)
#error "DTC 表容量为 0 —— 检查 NVM_CFG_BLK_DTC_SIZE 是否被改成小于 16"
#endif
#if (DEM_CFG_MAX_DTC > 32u)
#error "DTC 表容量超过 32 —— 检查 NVM_CFG_BLK_DTC_SIZE 是否被误改大"
#endif

/**
 * @brief 状态可用掩码这里**不做 `#if` 对账**
 * @note  `DEM_UDS_STATUS_*` 在 `Dem.h` 里是
 *        `#define DEM_UDS_STATUS_TF ((Dem_UdsStatusByteType)0x01)`
 *        —— 带强制类型转换，预处理阶段展开后是
 *        `missing binary operator before token`，编译不过。
 *        这条改由 `m6_check.py` 在板上验：0x19 的响应第 2 字节必须等于
 *        `0xAF`（TF|TFTOC|PDTC|CDTC|WIR），不等于就说明宏配错了。
 */

/** @brief 事件号必须从 0 连续 —— Dem 用事件号直接查通道，留空洞会静默失配 */
#if (DEM_CFG_EVENT_CAN0_BUSOFF != 0u) || (DEM_CFG_EVENT_CAN1_BUSOFF != 1u)
#error "事件号必须从 0 连续（0=CAN0, 1=CAN1），否则 Dem_EventToChannel 会失配"
#endif
#if (DEM_CFG_EVENT_NUM != 2u)
#error "事件数量与事件号定义不一致"
#endif
