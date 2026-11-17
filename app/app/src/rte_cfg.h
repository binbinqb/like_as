/**
 * @file    rte_cfg.h
 * @brief   RTE 端口表（内部头：只有 `rte.c` 该 include）
 *
 * @details 端口表是"业务语义名 → 绑定层信号号"的唯一对照处。与
 *          `bcm_sig_cfg.c` 的分工：
 *
 *          | 层 | 知道什么 | 不知道什么 |
 *          |----|----------|------------|
 *          | `rte_cfg.c` | 端口叫 `PARK_BRAKE`，对应绑定层第几号信号，是进还是出 | 这个信号在哪个报文、第几位 |
 *          | `bcm_sig_cfg.c` | 信号对应哪个 `COM_SID_xxx`、哪个 RX PDU、超时多少 | 业务怎么用它 |
 *
 *          两张表**故意不合并**：合并后改一个灯的业务名要动绑定表，改超时要动
 *          RTE 表，两个人都改同一个文件，冲突不断。
 *
 * @author  binbina
 * @version V0.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：2 个端口（1 进 1 出） |
 */

#ifndef RTE_CFG_H
#define RTE_CFG_H

#include "Std_Types.h"
#include "rte.h"   /* RTE_PORT_NUM：表长由端口枚举决定 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 端口方向：输入（业务只读） */
#define RTE_DIR_IN      ((uint8_t)0u)

/** @brief 端口方向：输出（业务只写） */
#define RTE_DIR_OUT     ((uint8_t)1u)

/**
 * @brief 一个端口的配置
 */
typedef struct
{
	uint8_t dir;      /**< `RTE_DIR_IN` / `RTE_DIR_OUT` */
	uint8_t signalId; /**< 按 @ref dir 解释：IN → `Bcm_SigRxIdType`，OUT → `Bcm_SigIdType` */
} Rte_PortCfgType;

/** @brief 端口表，下标即 `Rte_PortIdType` */
extern const Rte_PortCfgType Rte_PortCfg[RTE_PORT_NUM];

#ifdef __cplusplus
}
#endif

#endif /* RTE_CFG_H */
