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
#include "iohwab.h"
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
	sint32_t mv = 0;
	uint16_t raw = 0u;

	extern void HostIo_SetDin(uint16 ch, boolean level);
	extern void HostIo_SetAin(uint16 ch, uint16 value);

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

	/* ---------- 10. 一拍内一致性：影子即快照 ---------- */
	inject_park_brake(1u);
	BcmSig_MainFunction();
	(void)Rte_Read_ParkBrake(&v);          /* 本拍读到 ON */
	/* 模拟中断在拍中改掉底层缓冲，但**不跑** BcmSig_MainFunction：
	 * 绑定层影子没刷新，所以本拍后续读必须还是 ON。 */
	HostCom_SetRx((Com_SignalIdType)COM_SID_ParkingBrakeSwitch, 0u);
	st = Rte_Read_ParkBrake(&v);
	check((RTE_E_OK == st) && (RTE_SWITCH_ON == v),
	      "拍中改动底层缓冲 → 本拍读值不变（影子即快照）");

	/* ---------- 11. 恢复后重新可用 ---------- */
	inject_park_brake(1u);
	BcmSig_MainFunction();
	st = Rte_Read_ParkBrake(&v);
	check((RTE_E_OK == st) && (RTE_SWITCH_ON == v), "重新收到帧 → 恢复 OK + ON");

	/* ---------- 12. IO 端口：DIN（Host 后端） ---------- */
	(void)IoHwAb_Init();
	HostIo_SetDin(0u, TRUE);       /* 引脚高；activeLevel=LOW → 逻辑 0 */
	st = Rte_Read(RTE_PORT_DOOR_FL, &v);
	check((RTE_E_NEVER_RECEIVED == st) && (RTE_SWITCH_INVALID == v),
	      "DIN 未采样 → NEVER_RECEIVED");
	IoHwAb_MainFunction();
	IoHwAb_MainFunction();          /* debounceMs=20 → 2 拍 */
	st = Rte_Read(RTE_PORT_DOOR_FL, &v);
	check((RTE_E_OK == st) && (RTE_SWITCH_OFF == v),
	      "DIN 采样完成 → OK + OFF（引脚高、低有效 → 逻辑 0）");

	HostIo_SetDin(0u, FALSE);
	IoHwAb_MainFunction();
	IoHwAb_MainFunction();
	st = Rte_Read(RTE_PORT_DOOR_FL, &v);
	check((RTE_E_OK == st) && (RTE_SWITCH_ON == v),
	      "DIN 引脚拉低 → OK + ON（极性由 IoHwAb 处理，RTE 不取反）");

	/* ---------- 13. IO 端口：AIN 物理量 / 原始值 ---------- */
	HostIo_SetAin(1u, 30000u);      /* TEMP：factor=100 offset=-4000 shift=2 */
	{
		int i;
		for (i = 0; i < 30; i++) {
			IoHwAb_MainFunction();
		}
	}
	st = Rte_ReadS32(RTE_PORT_TEMP_MC, &mv);
	check((RTE_E_OK == st) && (mv >= -1002) && (mv <= -998),
	      "AIN 物理量端口 → OK，约 -1000（定点，RTE 不二次换算）");
	st = Rte_ReadU16(RTE_PORT_TEMP_RAW, &raw);
	/* 30 拍后一阶滤波残差约 7 个计数（shift=2） */
	check((RTE_E_OK == st) && (raw >= 29985u) && (raw <= 30000u),
	      "AIN 原始值端口 → OK，约 30000（含滤波残差）");

	/* ---------- 14. 类型/方向不符必须被拒 ---------- */
	check(RTE_E_INVALID == Rte_ReadS32(RTE_PORT_PARK_BRAKE, &mv),
	      "对 switch 端口读 S32 被拒");
	check(RTE_E_INVALID == Rte_ReadU16(RTE_PORT_TEMP_MC, &raw),
	      "对物理量端口读 U16 被拒");
	check(RTE_E_INVALID == Rte_ReadS32(RTE_PORT_BRAKE_LAMP, &mv),
	      "对输出端口读 S32 被拒");

	/* ---------- 15. DOUT：Host 上直连 LED 不可用 → 明确失败 ---------- */
	check(E_NOT_OK == Rte_Write(RTE_PORT_LED_R, RTE_SWITCH_ON),
	      "直连 LED 在 Host 返回 E_NOT_OK（不适用，不伪造成功）");

	(void)printf("-- %d passed, %d failed\n", s_pass, s_fail);

	return (0 == s_fail) ? 0 : 1;
}
