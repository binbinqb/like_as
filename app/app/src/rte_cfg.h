/**
 * @file    rte_cfg.h
 * @brief   RTE 端口表（内部头：只有 `rte.c` / `rte_cfg.c` 该 include）
 *
 * @details 端口表是"业务语义名 → 后端信号/通道号"的唯一对照处：
 *
 *          | 层 | 知道什么 | 不知道什么 |
 *          |----|----------|------------|
 *          | `Rte_Ports.h`（生成） | 端口叫什么、第几号、数量 | 它绑到哪个信号/通道 |
 *          | `rte_cfg.c` | 端口绑哪个 `BcmSig` 信号 / `IoHwAb` 通道 | 信号在哪个报文、第几位 |
 *          | `bcm_sig_cfg.c` | 信号对应哪个 `COM_SID_xxx`、超时多少 | 业务怎么用它 |
 *
 *          三张表**故意不合并**：合并后改一个灯的业务名要动绑定表，
 *          改超时要动 RTE 表，两个人都改同一个文件，冲突不断。
 *
 * @author  binbina
 * @version V0.3.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：2 个端口（1 进 1 出） |
 * | V0.2.0 | 2026-11-18 | binbina | 表改由 Board.json 生成；增加 kind/ref，支持 DIN/AIN/DOUT |
 * | V0.3.0 | 2026-11-20 | binbina | 增加 runnable 调度项类型（表体由 rte_sched.c 展开） |
 */

#ifndef RTE_CFG_H
#define RTE_CFG_H

#include "Std_Types.h"
#include "rte.h"   /* Rte_PortIdType、RTE_PORT_NUM */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 端口方向：输入（业务只读） */
#define RTE_DIR_IN      ((uint8_t)0u)

/** @brief 端口方向：输出（业务只写） */
#define RTE_DIR_OUT     ((uint8_t)1u)

/* 绑定种类：决定 `ref` 怎么解释、走哪条后端通道。 */
#define RTE_KIND_COM_TX     ((uint8_t)0u)  /**< ref = Bcm_SigIdType */
#define RTE_KIND_COM_RX     ((uint8_t)1u)  /**< ref = Bcm_SigRxIdType */
#define RTE_KIND_DIN        ((uint8_t)2u)  /**< ref = IoHwAb_DinId */
#define RTE_KIND_AIN_RAW    ((uint8_t)3u)  /**< ref = IoHwAb_AinId（原始值） */
#define RTE_KIND_AIN_PHYS   ((uint8_t)4u)  /**< ref = IoHwAb_AinId（物理量） */
#define RTE_KIND_DOUT       ((uint8_t)5u)  /**< ref = IoHwAb_DoutId */

/**
 * @brief 一个端口的配置
 */
typedef struct
{
	uint8_t  dir;   /**< `RTE_DIR_IN` / `RTE_DIR_OUT` */
	uint8_t  kind;  /**< `RTE_KIND_*` */
	uint16_t ref;   /**< 按 @ref kind 解释的后端编号 */
} Rte_PortCfgType;

/** @brief 端口表，下标即 `Rte_PortIdType`；初始化列表来自生成的 `Rte_Ports.h` */
extern const Rte_PortCfgType Rte_PortCfg[RTE_PORT_NUM];

/** @brief runnable 入口签名：无参无返回的周期函数 */
typedef void (*Rte_SchedFunc)(void);

/**
 * @brief 一个 runnable 的调度项
 *
 * @note `reload` 是**基准拍数**（= period_ms / RTE_SCHED_BASE_MS），
 *       由生成器折算好；≥1 由生成规则 S2 保证。
 */
typedef struct
{
	uint8_t       reload;  /**< 重装值（基准拍数，≥1） */
	Rte_SchedFunc func;    /**< runnable 入口；空表占位为 NULL，跳过不执行 */
} Rte_SchedEntryType;

#ifdef __cplusplus
}
#endif

#endif /* RTE_CFG_H */
