/**
 * @file    bcm_sig.c
 * @brief   车身信号绑定层的实现（M23）：表驱动的 raw ↔ 语义 翻译
 *
 * @details @section BCMSIGC_HOW 这一层怎么工作
 *
 *          只有一份通用逻辑，**零信号名硬编码**。所有"哪个信号在哪"的
 *          知识都在 `bcm_sig_cfg.c` 的表里。加信号不需要改本文件。
 *
 *          两趟扫描，每趟 10 ms 一次：
 *
 *          @code
 *           上行（收到什么）        下行（要求对方看到什么）
 *           Com_ReceiveSignal        业务 shadow
 *                ↓ raw                    ↓
 *           rxMap[raw] = 语义        txMap[语义] = raw
 *                ↓                        ↓
 *           s_rxState[i]             Com_SendSignal
 *          @endcode
 *
 *          @section BCMSIGC_SHADOW 为什么业务侧要留 shadow
 *
 *          三个理由，每个都是踩过的坑：
 *          1. `Com_ReceiveSignal()` 每次都重新解位（`Std_BitGetLittleEndian`），
 *             业务层一次业务判断读三四遍同一个信号就是三四次移位。
 *          2. 报文缓冲随时会被下一帧覆盖，**它不能当业务的状态存储** ——
 *             这条在 `com_app.c` 的 `s_comTxCounter` 注释里已经写过一次。
 *          3. 发送侧需要"业务期望值"与"已发出的值"分离：业务可能在一拍内
 *             连改两次，只有最后一拍的值有意义。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "bcm_sig_priv.h"

#include <string.h>

/* ============================ [ 影子存储 ] ============================ */

/**
 * @brief 发送侧影子：业务要求的语义值
 * @note  下标是 `Bcm_SigIdType`。取 `uint8_t` 而不是 `Bcm_SwStateType`：
 *        枚举的实际大小由编译器决定（C90 起可由 `-fshort-enums` 改变），
 *        显式用 `uint8_t` 才能保证 11 个字节就是 11 个字节。
 */
static uint8_t s_txState[BCM_SIG_TX_NUM];

/**
 * @brief 接收侧影子：上次解出来的语义值
 * @note  下标是 `Bcm_SigRxIdType`。
 */
static uint8_t s_rxState[BCM_SIG_RX_NUM];

/* ============================ [ 内部辅助 ] ============================ */

/**
 * @brief 取一条发送项的覆盖表，`NULL` 时退回默认表
 * @param[in] idx 表下标（调用者保证 < BCM_SIG_TX_NUM）
 * @return 长度 4 的映射表，下标是业务语义值
 */
static const uint8_t *txMapOf(uint16_t idx)
{
	const uint8_t *map = BcmSig_TxCfg[idx].map;

	return (NULL != map) ? map : BcmSig_TxMapDefault;
}

/**
 * @brief 取一条接收项的覆盖表，`NULL` 时退回默认表
 * @param[in] idx 表下标（调用者保证 < BCM_SIG_RX_NUM）
 * @return 长度 4 的映射表，下标是 raw 值
 */
static const uint8_t *rxMapOf(uint16_t idx)
{
	const uint8_t *map = BcmSig_RxCfg[idx].map;

	return (NULL != map) ? map : BcmSig_RxMapDefault;
}

/**
 * @brief 判断一个值是否落在 `Bcm_SwStateType` 的合法域内
 * @param[in] st 待检查值
 * @retval TRUE  合法
 * @retval FALSE 越界
 * @note  `BcmSig_TxSet()` 用它挡住非法调用。为什么不依赖编译器检查：
 *        业务层可能传强转后的整数（MISRA 也允许显式强转），编译器不会报。
 */
static boolean isValidState(uint8_t st)
{
	return (st <= (uint8_t)BCM_SW_STATE_FAULT) ? TRUE : FALSE;
}

/* ============================ [ 接口实现 ] ============================ */

void BcmSig_Init(void)
{
	uint16_t i;
	uint8_t raw;

	(void)memset(s_rxState, (int)BCM_SW_STATE_UNKNOWN, sizeof(s_rxState));

	/* 发送侧初始化为 OFF，并**立刻**写进 Com。
	 *
	 * 为什么不置 UNKNOWN：UNKNOWN 的 raw 是 3（"无效"），把它写进去等于
	 * 上电第一帧就告诉全车"我的灯状态无效"，仪表会点故障灯。而矩阵里
	 * 这些信号的 InitialValue 都是 0 = Inactive = OFF，所以写 OFF 与
	 * Com 缓冲的初值一致，上电不会在总线上产生任何跳变。 */
	for (i = 0u; i < (uint16_t)BCM_SIG_TX_NUM; i++)
	{
		s_txState[i] = (uint8_t)BCM_SW_STATE_OFF;
		raw = txMapOf(i)[s_txState[i]];
		(void)Com_SendSignal(BcmSig_TxCfg[i].comId, &raw);
	}
}

void BcmSig_MainFunction(void)
{
	uint16_t i;
	uint32_t raw32;
	uint8_t raw;

	/* ---- 上行：Com → 语义 ---- */
	for (i = 0u; i < (uint16_t)BCM_SIG_RX_NUM; i++)
	{
		raw32 = 0u;
		/* 传 uint32_t 的地址：Com 的 `comStoreSignalValue` 按信号类型
		 * 写 1/2/4 字节，本层绑的信号只有 2 bit，但传参类型必须够大，
		 * 否则 16 位信号会写坏栈上相邻字节。 */
		(void)Com_ReceiveSignal(BcmSig_RxCfg[i].comId, &raw32);

		raw = (uint8_t)raw32;
		if (raw > 3u)
		{
			/* 不该发生（绑的都是 2 bit），但保底：越界值一律当无效，
			 * 不能让 rxMapOf()[4] 越界读。 */
			s_rxState[i] = (uint8_t)BCM_SW_STATE_UNKNOWN;
		}
		else
		{
			s_rxState[i] = rxMapOf(i)[raw];
		}
	}

	/* ---- 下行：语义 → Com ---- */
	for (i = 0u; i < (uint16_t)BCM_SIG_TX_NUM; i++)
	{
		raw = txMapOf(i)[s_txState[i]];
		(void)Com_SendSignal(BcmSig_TxCfg[i].comId, &raw);
	}
}

Bcm_SwStateType BcmSig_RxGet(Bcm_SigRxIdType id)
{
	Bcm_SwStateType st;

	if ((uint32_t)id < (uint32_t)BCM_SIG_RX_NUM)
	{
		st = (Bcm_SwStateType)s_rxState[id];
	}
	else
	{
		st = BCM_SW_STATE_UNKNOWN;
	}

	return st;
}

Std_ReturnType BcmSig_TxSet(Bcm_SigIdType id, Bcm_SwStateType st)
{
	Std_ReturnType ret = E_NOT_OK;

	/* 两个条件都要查：编号在表内，且状态是合法枚举。
	 * 后者是"拦住越界值"的关键 —— 见 bcm_sig.h 的 BCMSIG_TXWHY。 */
	if (((uint32_t)id < (uint32_t)BCM_SIG_TX_NUM) &&
	        (TRUE == isValidState((uint8_t)st)))
	{
		s_txState[id] = (uint8_t)st;
		ret = E_OK;
	}

	return ret;
}

Bcm_SwStateType BcmSig_TxGet(Bcm_SigIdType id)
{
	Bcm_SwStateType st;

	if ((uint32_t)id < (uint32_t)BCM_SIG_TX_NUM)
	{
		st = (Bcm_SwStateType)s_txState[id];
	}
	else
	{
		st = BCM_SW_STATE_UNKNOWN;
	}

	return st;
}
