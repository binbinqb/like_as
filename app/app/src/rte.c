/**
 * @file    rte.c
 * @brief   最小 RTE 运行时：端口读写 + 四态映射 + 方向校验
 *
 * @details @section RTEIMPL_THIN 这一层为什么这么薄
 *
 *          它不是"又一层封装"，而是**唯一做语义转换的地方**：
 *
 *          | 转换 | 在哪做 | 为什么不能省 |
 *          |------|--------|--------------|
 *          | `Bcm_SwStateType` ↔ `Rte_SwitchType` | 本文件 `toRte` / `toBcm` | 两个枚举数值现在相同，但归属不同层；靠"数值一样"省掉转换，改一个就会静默错位 |
 *          | `Bcm_SigValidityType` → `Rte_StatusType` | 本文件 `toStatus` | 业务不该知道"绑定层有四态"，只该知道"这个值能不能用、为什么不能用" |
 *          | 端口号 → 信号号 | `rte_cfg.c` 表 | 业务只认端口名 |
 *
 *          @note 本文件**没有**缓冲、没有缓存、没有 runnable 表。加缓存需要
 *          先回答"一拍内多次读是否要求同值"（10.5 的一致性快照），
 *          没回答之前加缓存只是把问题藏起来。
 *
 * @author  binbina
 * @version V0.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：读/写、四态映射、方向与越界校验 |
 */

#include "rte.h"
#include "rte_cfg.h"

#include "bcm_sig.h"
#include "iohwab.h"

/* ================================ [ 宏 ] ================================ */

/* ============================== [ 内部函数 ] ============================== */

/**
 * @brief 绑定层状态 → RTE 开关值
 * @param[in] st 绑定层语义值
 * @return RTE 开关值
 */
static Rte_SwitchType toRte(Bcm_SwStateType st)
{
	Rte_SwitchType ret;

	switch (st)
	{
	case BCM_SW_STATE_OFF:
		ret = RTE_SWITCH_OFF;
		break;
	case BCM_SW_STATE_ON:
		ret = RTE_SWITCH_ON;
		break;
	case BCM_SW_STATE_FAULT:
		ret = RTE_SWITCH_ERROR;
		break;
	case BCM_SW_STATE_UNKNOWN:
	default:
		ret = RTE_SWITCH_INVALID;
		break;
	}

	return ret;
}

/**
 * @brief RTE 开关值 → 绑定层状态
 * @param[in] s RTE 开关值
 * @return 绑定层语义值
 */
static Bcm_SwStateType toBcm(Rte_SwitchType s)
{
	Bcm_SwStateType ret;

	switch (s)
	{
	case RTE_SWITCH_OFF:
		ret = BCM_SW_STATE_OFF;
		break;
	case RTE_SWITCH_ON:
		ret = BCM_SW_STATE_ON;
		break;
	case RTE_SWITCH_ERROR:
		ret = BCM_SW_STATE_FAULT;
		break;
	case RTE_SWITCH_INVALID:
	default:
		ret = BCM_SW_STATE_UNKNOWN;
		break;
	}

	return ret;
}

/**
 * @brief 绑定层四态 → RTE 返回状态
 * @param[in] v 绑定层有效性
 * @return RTE 状态
 *
 * @note 四态**一一对应**，不合并。TIMEOUT 与 INVALID 对业务是两件事：
 *       前者该保持输出（可能是丢帧），后者该进安全态（对方明确报错）。
 */
static Rte_StatusType toStatus(Bcm_SigValidityType v)
{
	Rte_StatusType ret;

	switch (v)
	{
	case BCM_SIG_VALID:
		ret = RTE_E_OK;
		break;
	case BCM_SIG_INVALID:
		ret = RTE_E_INVALID;
		break;
	case BCM_SIG_TIMEOUT:
		ret = RTE_E_MAX_AGE_EXCEEDED;
		break;
	case BCM_SIG_NEVER_RECEIVED:
	default:
		ret = RTE_E_NEVER_RECEIVED;
		break;
	}

	return ret;
}

/* ================================ [ 接口 ] ================================ */

/**
 * @brief IoHwAb 四态 → RTE 返回状态
 * @param[in] s IoHwAb 状态
 * @return RTE 状态
 * @note 与 `toStatus()`（BcmSig 四态）是同一套语义，只是来源不同。
 */
static Rte_StatusType toRteStatus(IoHwAb_StatusType s)
{
	Rte_StatusType ret;

	switch (s)
	{
	case IOHWAB_STATUS_VALID:
		ret = RTE_E_OK;
		break;
	case IOHWAB_STATUS_STALE:
		ret = RTE_E_MAX_AGE_EXCEEDED;
		break;
	case IOHWAB_STATUS_ERROR:
		ret = RTE_E_INVALID;
		break;
	case IOHWAB_STATUS_NEVER:
	default:
		ret = RTE_E_NEVER_RECEIVED;
		break;
	}

	return ret;
}

/**
 * @brief 校验端口：越界与方向
 * @param[in] port 端口号
 * @param[in] dir  期望方向
 * @return TRUE 合法
 */
static boolean portOk(Rte_PortIdType port, uint8_t dir)
{
	if ((uint32_t)port >= (uint32_t)RTE_PORT_NUM)
	{
		return FALSE;
	}
	if (Rte_PortCfg[port].dir != dir)
	{
		/* 方向接反必须在第一次调用就暴露，不能"顺手改成读/写"。 */
		return FALSE;
	}
	return TRUE;
}

Rte_StatusType Rte_Read(Rte_PortIdType port, Rte_SwitchType *data)
{
	Rte_StatusType ret = RTE_E_INVALID;
	Bcm_SwStateType st = BCM_SW_STATE_UNKNOWN;
	Bcm_SigValidityType v = BCM_SIG_NEVER_RECEIVED;
	IoHwAb_StatusType ioSt = IOHWAB_STATUS_NEVER;
	boolean ioVal = FALSE;

	if ((NULL == data) || (portOk(port, RTE_DIR_IN) == FALSE))
	{
		return RTE_E_INVALID;
	}

	switch (Rte_PortCfg[port].kind)
	{
	case RTE_KIND_COM_RX:
		v = BcmSig_RxRead((Bcm_SigRxIdType)Rte_PortCfg[port].ref, &st);
		ret = toStatus(v);
		/* 非 OK 时也写 INVALID：防止调用者忘判返回值就读到上一轮旧值。 */
		*data = (RTE_E_OK == ret) ? toRte(st) : RTE_SWITCH_INVALID;
		break;

	case RTE_KIND_DIN:
		ioSt = IOHWAB_STATUS_NEVER;
		if (IoHwAb_DinRead((IoHwAb_DinId)Rte_PortCfg[port].ref, &ioVal,
		                   &ioSt) != E_OK)
		{
			*data = RTE_SWITCH_INVALID;
			return RTE_E_INVALID;
		}
		ret = toRteStatus(ioSt);
		*data = (RTE_E_OK == ret)
		        ? ((ioVal != FALSE) ? RTE_SWITCH_ON : RTE_SWITCH_OFF)
		        : RTE_SWITCH_INVALID;
		break;

	default:
		/* 数值型端口不能按 switch 读 */
		*data = RTE_SWITCH_INVALID;
		return RTE_E_INVALID;
	}

	return ret;
}

Rte_StatusType Rte_ReadU16(Rte_PortIdType port, uint16_t *data)
{
	IoHwAb_StatusType ioSt = IOHWAB_STATUS_NEVER;
	Rte_StatusType ret;

	if ((NULL == data) || (portOk(port, RTE_DIR_IN) == FALSE) ||
	    (Rte_PortCfg[port].kind != RTE_KIND_AIN_RAW))
	{
		return RTE_E_INVALID;
	}

	if (IoHwAb_AinReadRaw((IoHwAb_AinId)Rte_PortCfg[port].ref, data,
	                      &ioSt) != E_OK)
	{
		return RTE_E_INVALID;
	}
	ret = toRteStatus(ioSt);
	return ret;
}

Rte_StatusType Rte_ReadS32(Rte_PortIdType port, sint32_t *data)
{
	IoHwAb_StatusType ioSt = IOHWAB_STATUS_NEVER;
	Rte_StatusType ret;

	if ((NULL == data) || (portOk(port, RTE_DIR_IN) == FALSE) ||
	    (Rte_PortCfg[port].kind != RTE_KIND_AIN_PHYS))
	{
		return RTE_E_INVALID;
	}

	if (IoHwAb_AinReadPhys((IoHwAb_AinId)Rte_PortCfg[port].ref, data,
	                       &ioSt) != E_OK)
	{
		return RTE_E_INVALID;
	}
	ret = toRteStatus(ioSt);
	return ret;
}

Std_ReturnType Rte_Write(Rte_PortIdType port, Rte_SwitchType data)
{
	if (portOk(port, RTE_DIR_OUT) == FALSE)
	{
		return E_NOT_OK;
	}

	if ((uint32_t)data > (uint32_t)RTE_SWITCH_INVALID)
	{
		return E_NOT_OK;
	}

	switch (Rte_PortCfg[port].kind)
	{
	case RTE_KIND_COM_TX:
		return BcmSig_TxSet((Bcm_SigIdType)Rte_PortCfg[port].ref, toBcm(data));

	case RTE_KIND_DOUT:
		/* ERROR / INVALID 不是"关"，是"不知道" —— 不去驱动输出。
		 * 把故障当 OFF 会让灯在故障时安静地灭掉，仪表却显示正常。 */
		if (RTE_SWITCH_ON == data)
		{
			return IoHwAb_DoutWrite((IoHwAb_DoutId)Rte_PortCfg[port].ref, TRUE);
		}
		if (RTE_SWITCH_OFF == data)
		{
			return IoHwAb_DoutWrite((IoHwAb_DoutId)Rte_PortCfg[port].ref, FALSE);
		}
		return E_NOT_OK;

	default:
		return E_NOT_OK;
	}
}
