/**
 * @file    test_iohwab.c
 * @brief   Host 上的 IoHwAb Core 用例：消抖、极性、滤波、四态、安全状态、样本新鲜度
 *
 * @details @section IOHWABTEST_WHAT 覆盖什么
 *
 *          | # | 用例 | 期望 |
 *          |---|------|------|
 *          | 1 | 上电未采样 | 读 DIN 返回 E_OK 但 status=NEVER，值不可当 LOW 用 |
 *          | 2 | DIN 消抖 | 跳变后未满 2 拍不提交；满拍后 VALID |
 *          | 3 | DIN 极性 | activeLevel=LOW：引脚低 → 逻辑 1 |
 *          | 4 | DIN 无新样本 | 冻结后不推进消抖；超 staleTicks 判 STALE；解冻恢复 |
 *          | 5 | AIN 滤波（上行） | 从 0 向 2048 收敛 |
 *          | 6 | AIN 滤波（下行） | 负差值同样收敛（右移朝零舍入可移植） |
 *          | 7 | AIN 定点换算 | phys = raw×factor/1000 + offset |
 *          | 8 | AIN 负偏移 | TEMP：factor=100/offset=-4000 → 负物理量 |
 *          | 9 | AIN 溢出饱和 | raw×factor 超 sint32 → 饱和到 INT32_MAX |
 *          | 10 | AIN 失败超时 | 连续失败 staleTicks → STALE，两倍 → ERROR |
 *          | 11 | AIN 无新样本 | 冻结后判 STALE，而不是拿旧值反复滤波 |
 *          | 12 | Init 运行期幂等 | 重复 Init 不清状态、不动输出 |
 *          | 13 | ReInit | 显式重新初始化：输出回安全值、状态回 NEVER |
 *          | 14 | 极性归属 Core | 低有效通道写逻辑 1 → **电气 0**，Adapter 不二次取反 |
 *          | 15 | 安全状态反馈 | 写失败 → DoutGetFault=TRUE、SetAllSafe=E_NOT_OK |
 *          | 16 | 不适用 ≠ 失败 | 直连 LED 在 Host 返回 E_NOT_OK 但故障位保持 FALSE |
 *
 * @author  binbina
 * @version V1.0.1
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：7 组断言 |
 * | V1.0.1 | 2026-11-18 | binbina | 补样本新鲜度、Init 幂等/ReInit、极性归属、安全状态反馈、溢出饱和 |
 */

#include <stdio.h>

#include "iohwab.h"
#include "IoHwAb_Cfg.h"   /* 通道枚举（Board.json 生成） */

/* Host 后端的故障注入接口（iohwab_host_ops.c） */
extern void HostIo_SetDin(uint16 ch, boolean level);
extern void HostIo_SetDinFail(uint16 ch, boolean fail);
extern void HostIo_SetDinFrozen(uint16 ch, boolean frozen);
extern void HostIo_SetAin(uint16 ch, uint16 raw);
extern void HostIo_SetAinFail(uint16 ch, boolean fail);
extern void HostIo_SetAinFrozen(uint16 ch, boolean frozen);
extern void HostIo_SetDoutFail(uint16 ch, boolean fail);
extern boolean HostIo_GetDoutLevel(uint16 ch);
extern uint16 HostIo_GetPwm(uint16 ch);

static int s_pass;
static int s_fail;

/**
 * @brief 断言
 * @param[in] cond 条件
 * @param[in] what 描述
 */
static void check(int cond, const char *what)
{
	if (0 != cond) {
		s_pass++;
		(void)printf("  PASS  %s\n", what);
	} else {
		s_fail++;
		(void)printf("  FAIL  %s\n", what);
	}
}

/** @brief 跑 N 个 10 ms 节拍 */
static void run_ticks(int n)
{
	int i;

	for (i = 0; i < n; i++) {
		IoHwAb_MainFunction();
	}
}

int main(void)
{
	boolean v = FALSE;
	boolean fault = TRUE;
	IoHwAb_StatusType st = IOHWAB_STATUS_NEVER;
	sint32 phys = 0;
	uint16 raw = 0;

	(void)printf("== IoHwAb Core（Host，V1.0.1）==\n");

	/* ---- 1) 上电未采样 ---- */
	HostIo_SetDin(0u, TRUE);        /* 高电平；activeLevel=LOW → 逻辑 0 */
	check(IoHwAb_Init() == E_OK, "首次 Init 返回 E_OK（不适用通道不计失败）");
	check(IoHwAb_IsInitialized() == TRUE, "IsInitialized = TRUE");
	check(IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK,
	      "DIN 读调用合法（E_OK）");
	check(st == IOHWAB_STATUS_NEVER,
	      "DIN 未采样时 status=NEVER（不能当 LOW 用）");

	/* ---- 2) 消抖：debounceMs=20 → 2 拍（10 ms/拍） ---- */
	run_ticks(1);
	check(IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK
	      && (st == IOHWAB_STATUS_NEVER),
	      "DIN 1 拍（< 消抖 2 拍）仍为 NEVER");
	run_ticks(1);
	check((IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK)
	      && (st == IOHWAB_STATUS_VALID) && (v == FALSE),
	      "DIN 满 2 拍后 VALID，逻辑值 0（引脚高、低有效）");

	/* ---- 3) 极性：引脚低 → 逻辑 1 ---- */
	HostIo_SetDin(0u, FALSE);
	run_ticks(2);
	check((IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK)
	      && (st == IOHWAB_STATUS_VALID) && (v == TRUE),
	      "DIN 低有效：引脚低 → 逻辑 1");

	/* ---- 4) 无新样本：不推进消抖，超时判 STALE ---- */
	HostIo_SetDinFrozen(0u, TRUE);
	HostIo_SetDin(0u, TRUE);        /* 逻辑 0，但被冻结：不应被消抖提交 */
	run_ticks(3);
	check((IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK)
	      && (st == IOHWAB_STATUS_VALID) && (v == TRUE),
	      "冻结 3 拍：不拿旧样本重复消抖，仍是上次提交的 TRUE");
	run_ticks(47);                  /* staleMs=500 → 50 拍 */
	(void)IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st);
	check(st == IOHWAB_STATUS_STALE, "冻结 50 拍（staleMs=500）→ STALE");
	HostIo_SetDinFrozen(0u, FALSE);
	run_ticks(2);
	check((IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st) == E_OK)
	      && (st == IOHWAB_STATUS_VALID) && (v == FALSE),
	      "解冻后新样本重新消抖 → VALID，逻辑 0");

	/* ---- 5) AIN 上行滤波 ---- */
	HostIo_SetAin(0u, 2048u);
	run_ticks(30);                   /* shift=3：时间常数约 8 拍 */
	check(IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_VBAT, &raw, &st) == E_OK
	      && (st == IOHWAB_STATUS_VALID) && (raw > 1900u) && (raw <= 2048u),
	      "AIN_VBAT 30 拍滤波后接近 2048");

	/* ---- 6) AIN 下行滤波：负差值必须同样收敛 ---- */
	HostIo_SetAin(0u, 512u);
	run_ticks(30);
	check(IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_VBAT, &raw, &st) == E_OK
	      && (raw >= 500u) && (raw < 600u),
	      "AIN_VBAT 下行 30 拍收敛到 512（负差值舍入可移植）");

	/* ---- 7) 定点换算：512×33/1000 ≈ 16 ---- */
	check(IoHwAb_AinReadPhys((IoHwAb_AinId)IOHWAB_AIN_VBAT, &phys, &st) == E_OK
	      && (phys >= 15) && (phys <= 17),
	      "AIN_VBAT phys = raw×33/1000（定点，允许滤波残差）");

	/* ---- 8) 负偏移：TEMP factor=100 offset=-4000 ---- */
	HostIo_SetAin(1u, 30000u);
	run_ticks(30);
	check(IoHwAb_AinReadPhys((IoHwAb_AinId)IOHWAB_AIN_TEMP, &phys, &st) == E_OK
	      && (phys >= -1002) && (phys <= -998),
	      "AIN_TEMP phys = raw×100/1000-4000（结果为负）");

	/* ---- 9) 溢出饱和：65535×1e8 = 6.5e12（sint32 乘积早已溢出），
	 *         /1000 后 6.5e9 仍超 INT32_MAX → 必须饱和 ---- */
	HostIo_SetAin(2u, 65535u);
	run_ticks(1);
	check(IoHwAb_AinReadPhys((IoHwAb_AinId)IOHWAB_AIN_AIN_OVF, &phys, &st) == E_OK
	      && (phys == INT32_MAX),
	      "AIN_OVF 换算溢出 → 饱和到 INT32_MAX（不 UB、不回绕）");

	/* ---- 10) 失败超时：STALE → ERROR ---- */
	HostIo_SetAinFail(1u, TRUE);
	run_ticks(50);                   /* staleMs=500 → 50 拍 */
	check(IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_TEMP, &raw, &st) == E_OK
	      && (st == IOHWAB_STATUS_STALE),
	      "AIN_TEMP 失败 50 拍 → E_OK 但 status=STALE（应用必须看状态）");
	run_ticks(60);
	(void)IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_TEMP, &raw, &st);
	check(st == IOHWAB_STATUS_ERROR, "AIN_TEMP 失败 110 拍 → ERROR");
	HostIo_SetAinFail(1u, FALSE);

	/* ---- 11) 无新样本：AIN 判 STALE，不重复滤波 ---- */
	HostIo_SetAinFrozen(0u, TRUE);
	run_ticks(50);
	(void)IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_VBAT, &raw, &st);
	check(st == IOHWAB_STATUS_STALE,
	      "AIN_VBAT 冻结 50 拍 → STALE（旧值不刷新超时）");
	HostIo_SetAinFrozen(0u, FALSE);
	run_ticks(10);
	(void)IoHwAb_AinReadRaw((IoHwAb_AinId)IOHWAB_AIN_VBAT, &raw, &st);
	check(st == IOHWAB_STATUS_VALID, "解冻后恢复 VALID");

	/* ---- 12) Init 运行期幂等：不清状态、不动输出 ---- */
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_HOST0, TRUE) == E_OK
	      && (HostIo_GetDoutLevel(0u) == TRUE), "Host0 写逻辑 1 → 电气 1");
	run_ticks(1);
	check(IoHwAb_Init() == E_OK, "重复 Init 返回 E_OK");
	check(HostIo_GetDoutLevel(0u) == TRUE,
	      "重复 Init **不**把输出拉回安全值（V1.0.0 会关灯）");
	(void)IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st);
	check(st == IOHWAB_STATUS_VALID, "重复 Init 不清消抖上下文");

	/* ---- 13) ReInit：显式重新初始化 ---- */
	check(IoHwAb_ReInit() == E_OK, "ReInit 返回 E_OK");
	check(HostIo_GetDoutLevel(0u) == FALSE, "ReInit 把 Host0 拉回安全值");
	(void)IoHwAb_DinRead((IoHwAb_DinId)IOHWAB_DIN_DOOR_FL, &v, &st);
	check(st == IOHWAB_STATUS_NEVER, "ReInit 清消抖上下文 → NEVER");

	/* ---- 14) 极性归属 Core：低有效通道写逻辑 1 → 电气 0 ---- */
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_HOST_LOW, TRUE) == E_OK
	      && (HostIo_GetDoutLevel(1u) == FALSE),
	      "HOST_LOW 低有效：写逻辑 1 → 电气 0（Adapter 只见电气电平）");
	check(IoHwAb_DoutReadBack((IoHwAb_DoutId)IOHWAB_DOUT_HOST_LOW, &v) == E_OK
	      && (v == TRUE),
	      "低有效通道回读仍还原为逻辑 1");

	/* ---- 15) 安全状态反馈 ---- */
	HostIo_SetDoutFail(0u, TRUE);
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_HOST0, TRUE) == E_NOT_OK,
	      "注入写失败：DoutWrite 返回 E_NOT_OK");
	check(IoHwAb_DoutGetFault((IoHwAb_DoutId)IOHWAB_DOUT_HOST0, &fault) == E_OK
	      && (fault == TRUE), "Host0 故障位 = TRUE");
	check(IoHwAb_SetAllSafe() == E_NOT_OK, "有真实写失败 → SetAllSafe 返回 E_NOT_OK");
	check(IoHwAb_DoutGetFault((IoHwAb_DoutId)IOHWAB_DOUT_HOST_LOW, &fault) == E_OK
	      && (fault == FALSE), "未失败的通道故障位仍为 FALSE");
	HostIo_SetDoutFail(0u, FALSE);
	check(IoHwAb_SetAllSafe() == E_OK, "故障解除后 SetAllSafe 返回 E_OK");
	check(HostIo_GetDoutLevel(0u) == FALSE, "SetAllSafe 把 Host0 拉回安全值");

	/* ---- 16) PWM、越界与"不适用 ≠ 失败" ---- */
	check(IoHwAb_PwmSetDuty((IoHwAb_PwmId)IOHWAB_PWM_DIM_HOST, 5000u) == E_OK
	      && (HostIo_GetPwm(0u) == 5000u), "PWM 50% 生效");
	check(IoHwAb_PwmSetDuty((IoHwAb_PwmId)IOHWAB_PWM_DIM_HOST, 10001u) == E_NOT_OK,
	      "PWM duty 越界被拒");
	check(IoHwAb_DinRead((IoHwAb_DinId)99, &v, &st) == E_NOT_OK,
	      "非法 DIN ID 被拒");
	check(IoHwAb_DoutWrite((IoHwAb_DoutId)IOHWAB_DOUT_LED_R, TRUE) == E_NOT_OK,
	      "直连 LED 在 Host 返回 E_NOT_OK（不伪造成功）");
	check(IoHwAb_DoutGetFault((IoHwAb_DoutId)IOHWAB_DOUT_LED_R, &fault) == E_OK
	      && (fault == FALSE),
	      "但故障位保持 FALSE（不适用 ≠ 失败）");

	(void)printf("-- %d 通过，%d 失败\n", s_pass, s_fail);
	return (s_fail == 0) ? 0 : 1;
}
