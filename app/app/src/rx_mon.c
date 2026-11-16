/**
 * @file    rx_mon.c
 * @brief   CAN 接收到达监视的实现（A2）：一张时间戳表 + 一个已到达位图
 *
 * @details 为什么不用 `Std_TimerType`：
 *          `Std_TimerInit/IsTimeout` 是"一次性超时"语义，用完要重启；
 *          这里要的是"随时查询某个事件的年龄"，年龄才是原始事实，
 *          超时判断留给调用方（每个信号的门限不同）。
 *
 *          为什么位图与时间戳分开：
 *          `s_lastMs[pduId] == 0` 不能表示"没到过" —— 上电后第 0 毫秒
 *          收到一帧就是 0。位图是唯一无歧义的"到过"证据。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "rx_mon.h"

#include "platform_cvm0146.h"   /* Platform_NowMs()：1 ms 计数，SysTick 递增 */

#include <string.h>

/* ============================ [ 存储 ] ============================ */

/**
 * @brief 每条 RX PDU 最后一次到达的时刻（ms，来自 `Platform_NowMs()`）
 * @note  下标是 CanIf 的 `rxPduId`（`CANIF_RX_xxx`，0..CANIF_RX_PDU_NUM-1）。
 *        `PduIdType` 在当前配置下是 `uint16_t`，所以下标前要显式比较上界。
 */
static volatile uint32_t s_lastMs[CANIF_RX_PDU_NUM];

/**
 * @brief "到过"位图，1 bit / PDU
 * @note  57 条只需要 8 字节。用位图而不是 `boolean` 数组（57 字节）：
 *        这个数组与时间戳表同在 CAN 中断里被写，越小越不容易被别的
 *        ISR 打断到"写了一半"的状态。
 */
static volatile uint8_t s_seen[(CANIF_RX_PDU_NUM + 7u) / 8u];

/* ============================ [ 接口实现 ] ============================ */

void RxMon_Init(void)
{
	(void)memset((void *)s_lastMs, 0, sizeof(s_lastMs));
	(void)memset((void *)s_seen, 0, sizeof(s_seen));
}

void RxMon_OnRx(PduIdType pduId)
{
	uint16_t id = (uint16_t)pduId;

	if (id < (uint16_t)CANIF_RX_PDU_NUM)
	{
		/* 先写时间戳再置位：反过来会出现"已到达但时间是 0"的窗口，
		 * 此时 `AgeMs` 会算出一个巨大的年龄（now - 0 = now），
		 * 恰好和"刚收到"相反。 */
		s_lastMs[id] = Platform_NowMs();
		s_seen[id / 8u] |= (uint8_t)(1u << (id % 8u));
	}
}

boolean RxMon_Seen(PduIdType pduId)
{
	uint16_t id = (uint16_t)pduId;
	boolean seen = FALSE;

	if (id < (uint16_t)CANIF_RX_PDU_NUM)
	{
		seen = ((s_seen[id / 8u] & (uint8_t)(1u << (id % 8u))) != 0u) ? TRUE : FALSE;
	}

	return seen;
}

uint32_t RxMon_AgeMs(PduIdType pduId)
{
	uint16_t id = (uint16_t)pduId;
	uint32_t age = RXMON_NEVER_MS;

	if ((id < (uint16_t)CANIF_RX_PDU_NUM) && (TRUE == RxMon_Seen(pduId)))
	{
		/* 无符号减法，32 位毫秒计数回卷（49.7 天）时结果依然正确 */
		age = Platform_NowMs() - s_lastMs[id];
	}

	return age;
}
