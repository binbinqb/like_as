/**
 * @file    bcm_sig_priv.h
 * @brief   车身信号绑定层的**私有**头（只有 bcm_sig.c / bcm_sig_cfg.c 包含）
 *
 * @details @section BCMSIGPRIV_WHY 为什么要单独一个私有头
 *
 *          `bcm_sig.h` 是给业务层看的契约，只依赖 `Std_Types.h`。
 *          但绑定表里必然出现 `Com_SignalIdType`（那是 Com 的类型），
 *          一旦写进公共头，业务层为了 include 它就得连带 include
 *          `Com.h` —— 于是"业务层看不见 Com"这条约束就名存实亡了。
 *
 *          所以把表结构和 `extern` 表收在这里，与 HAL 的做法一致：
 *          **接口头零 SDK，实现目录内部才看得见平台类型**。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef BCM_SIG_PRIV_H
#define BCM_SIG_PRIV_H

#include "bcm_sig.h"
#include "Com.h"      /* Com_SignalIdType */
#include "Com_Cfg.h"  /* COM_SID_xxx */

/* ============================ [ 表结构 ] ============================ */

/**
 * @brief 一条发送信号的绑定项
 */
typedef struct
{
	Com_SignalIdType comId; /**< Com 信号号（`COM_SID_xxx`） */
	const uint8_t *map;     /**< 语义→raw 覆盖表，`NULL` = 用默认表 */
} BcmSig_TxCfgType;

/**
 * @brief 一条接收信号的绑定项
 */
typedef struct
{
	Com_SignalIdType comId;  /**< Com 信号号（`COM_SID_xxx`） */
	const uint8_t *map;      /**< raw→语义 覆盖表，`NULL` = 用默认表 */
	PduIdType canIfPduId;    /**< 该信号所在 PDU 的 CanIf 编号（到达监视用） */
	uint16_t timeoutMs;      /**< 超过这个时长没收到就判超时（0 = 不判） */
} BcmSig_RxCfgType;

/* ============================ [ 表（bcm_sig_cfg.c 定义） ] ============================ */

/**
 * @brief 发送绑定表
 * @note  长度 == `BCM_SIG_TX_NUM`，`bcm_sig_cfg.c` 里有编译期断言。
 *        直接 `extern` 数组而不是"const 指针指向数组" —— 少一层间接，
 *        少一次指针解引用，也少一个可能为 `NULL` 的东西。
 */
extern const BcmSig_TxCfgType BcmSig_TxCfg[BCM_SIG_TX_NUM];

/** @brief 接收绑定表，长度 == `BCM_SIG_RX_NUM` */
extern const BcmSig_RxCfgType BcmSig_RxCfg[BCM_SIG_RX_NUM];

/** @brief 上行默认表：raw(0..3) → 语义，长度 4 */
extern const uint8_t BcmSig_RxMapDefault[4];

/** @brief 下行默认表：语义 → raw，长度 4，下标是 `Bcm_SwStateType` */
extern const uint8_t BcmSig_TxMapDefault[4];

#endif /* BCM_SIG_PRIV_H */
