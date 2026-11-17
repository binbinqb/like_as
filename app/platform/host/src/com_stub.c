/**
 * @file    com_stub.c
 * @brief   Com 替身实现：一张按信号号索引的原始值表
 *
 * @details 容量按 `COM_STUB_CAPACITY` 固定，越界信号号直接拒绝（返回
 *          `E_NOT_OK`），不静默丢弃——静默丢弃会让"业务没读到值"看起来
 *          像"业务逻辑错了"，是最难查的一类假失败。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版 |
 */

#include "com_stub.h"

#include <string.h>

/**
 * @brief 信号表容量
 * @note  当前工程 372 个信号、最大信号号约 380；取 1024 留余量。
 *        表是静态的，不占栈。
 */
#define COM_STUB_CAPACITY   (1024u)

/** @brief 原始值表（下标 = 信号号） */
static uint8_t s_value[COM_STUB_CAPACITY];

/** @brief 是否被写过（区分"写过 0"与"从没写过"） */
static uint8_t s_written[COM_STUB_CAPACITY];

void HostCom_Reset(void)
{
	(void)memset(s_value, 0, sizeof(s_value));
	(void)memset(s_written, 0, sizeof(s_written));
}

void HostCom_SetRx(Com_SignalIdType id, uint8_t raw)
{
	if ((uint32_t)id < COM_STUB_CAPACITY)
	{
		s_value[id] = raw;
		s_written[id] = 1u;
	}
}

uint8_t HostCom_GetTx(Com_SignalIdType id)
{
	if ((uint32_t)id < COM_STUB_CAPACITY)
	{
		return s_value[id];
	}

	return 0u;
}

Std_ReturnType Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
	Std_ReturnType ret = E_NOT_OK;

	if (((uint32_t)SignalId < COM_STUB_CAPACITY) && (NULL != SignalDataPtr))
	{
		s_value[SignalId] = *(const uint8_t *)SignalDataPtr;
		s_written[SignalId] = 1u;
		ret = E_OK;
	}

	return ret;
}

Std_ReturnType Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
	Std_ReturnType ret = E_NOT_OK;

	if (((uint32_t)SignalId < COM_STUB_CAPACITY) && (NULL != SignalDataPtr))
	{
		/* 只写 1 字节：与真 Com 对 UINT8 信号的行为一致。
		 * 调用方（`bcm_sig.c`）在调用前把 uint32 清零，所以高字节保持 0。 */
		*(uint8_t *)SignalDataPtr = s_value[SignalId];
		ret = E_OK;
	}

	return ret;
}
