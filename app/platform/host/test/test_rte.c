/**
 * @file    test_rte.c
 * @brief   Host 上的 RTE 用例：端口读写、四态映射、方向校验
 *
 * @details @section RTETEST_WHAT 覆盖什么
 *
 *          | 用例 | 期望 |
 *          |------|------|
 *          | 上电未收到 | `RTE_E_NEVER_RECEIVED`，值被写成 INVALID |
 *          | raw=1 | `RTE_E_OK` + `RTE_SWITCH_ON` |
 *          | raw=2（对方报错） | `RTE_E_OK` + `RTE_SWITCH_ERROR`（**值是有效的**，只是内容为故障） |
 *          | raw=3（对方说无效） | `RTE_E_INVALID` |
 *          | 超 300 ms 无帧 | `RTE_E_MAX_AGE_EXCEEDED` |
 *          | 写输出端口 | `E_OK`，绑定层影子同步 |
 *          | 写输入端口 / 读输出端口 | 拒绝（接反要第一次就暴露） |
 *          | 端口号越界 / NULL | 拒绝 |
 *
 *          `raw=2` 与 `raw=3` 的区别是这一层最容易做错的地方：
 *          前者是**有效的坏消息**，后者是**没有消息**。合并成一个错误码，
 *          业务就无法区分"对方报故障"和"对方掉线"。
 *
 * @author  binbina
 * @version V0.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：10 组断言 |
 */

#include <stdio.h>

#include "rte.h"
#include "bcm_sig.h"
#include "rx_mon.h"
#include "com_stub.h"
#include "Com_Cfg.h"
#include "platform_host.h"
#include "CanIf_Cfg.h"

/* ============================ [ 断言框架 ] ============================ */

static int s_pass = 0;
static int s_fail = 0;

/**
 * @brief 一条断言
 * @param[in] cond 条件
 * @param[in] what 描述
 */
static void check(int cond, const char *what)
{
	if (0 != cond)
	{
		s_pass++;
		(void)printf("  PASS  %s\n", what);
	}
	else
	{
		s_fail++;
		(void)printf("  FAIL  %s\n", what);
	}
}

/**
 * @brief 模拟一帧 CCVS 到达（与 test_bcm.c 同一手法）
 * @param[in] raw 手刹开关原始值
 */
static void inject_park_brake(uint8_t raw)
{
	HostCom_SetRx((Com_SignalIdType)COM_SID_ParkingBrakeSwitch, raw);
	RxMon_OnRx((PduIdType)CANIF_RX_CAN1_CCVS);
}

/* ============================== [ 用例 ] ============================== */

int main(void)
{
	Rte_SwitchType v = RTE_SWITCH_INVALID;
	Rte_StatusType st;

	(void)printf("== like_as host test: RTE ==\n");

	Host_ResetClock();
	HostCom_Reset();
	RxMon_Init();
	BcmSig_Init();

	/* ---------- 1. 从未收到 ---------- */
	st = Rte_Read_ParkBrake(&v);
	check((RTE_E_NEVER_RECEIVED == st) && (RTE_SWITCH_INVALID == v),
	      "未收到 → NEVER_RECEIVED，值不可用");

	/* ---------- 2. 有效 ON ---------- */
	inject_park_brake(1u);
	BcmSig_MainFunction();
	st = Rte_Read_ParkBrake(&v);
	check((RTE_E_OK == st) && (RTE_SWITCH_ON == v), "raw=1 → OK + ON");

	/* ---------- 3. 有效但内容是故障 ---------- */
	inject_park_brake(2u);
	BcmSig_MainFunction();
	st = Rte_Read_ParkBrake(&v);
	check((RTE_E_OK == st) && (RTE_SWITCH_ERROR == v),
	      "raw=2 → OK + ERROR（有效的坏消息）");

	/* ---------- 4. 对方声明无效 ---------- */
	inject_park_brake(3u);
	BcmSig_MainFunction();
	st = Rte_Read_ParkBrake(&v);
	check(RTE_E_INVALID == st, "raw=3 → INVALID（没有消息）");

	/* ---------- 5. 超时 ---------- */
	inject_park_brake(1u);
	Host_AdvanceMs(400u);
	BcmSig_MainFunction();
	st = Rte_Read_ParkBrake(&v);
	check(RTE_E_MAX_AGE_EXCEEDED == st, "超时 300 ms → MAX_AGE_EXCEEDED");

	/* ---------- 6. 写输出端口 ---------- */
	check(E_OK == Rte_Write_BrakeLamp(RTE_SWITCH_ON), "写制动灯端口 → E_OK");
	check(BCM_SW_STATE_ON == BcmSig_TxGet(BCM_SIG_BRAKE),
	      "写入后绑定层影子 = ON");

	/* ---------- 7. 方向接反 ---------- */
	check(E_NOT_OK == Rte_Write(RTE_PORT_PARK_BRAKE, RTE_SWITCH_ON),
	      "写输入端口被拒");
	check(RTE_E_INVALID == Rte_Read(RTE_PORT_BRAKE_LAMP, &v),
	      "读输出端口被拒");

	/* ---------- 8. 越界与空指针 ---------- */
	check(E_NOT_OK == Rte_Write((Rte_PortIdType)RTE_PORT_NUM, RTE_SWITCH_ON),
	      "端口号越界（写）被拒");
	check(RTE_E_INVALID == Rte_Read((Rte_PortIdType)99, &v),
	      "端口号越界（读）被拒");
	check(RTE_E_INVALID == Rte_Read(RTE_PORT_PARK_BRAKE, NULL),
	      "空指针被拒");

	/* ---------- 9. 非法枚举值 ---------- */
	check(E_NOT_OK == Rte_Write(RTE_PORT_BRAKE_LAMP, (Rte_SwitchType)9),
	      "越界枚举值（9）被拒");

	/* ---------- 10. 恢复后重新可用 ---------- */
	inject_park_brake(1u);
	BcmSig_MainFunction();
	st = Rte_Read_ParkBrake(&v);
	check((RTE_E_OK == st) && (RTE_SWITCH_ON == v), "重新收到帧 → 恢复 OK + ON");

	(void)printf("-- %d passed, %d failed\n", s_pass, s_fail);

	return (0 == s_fail) ? 0 : 1;
}
