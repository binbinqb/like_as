/**
 * @file    ecum_cmd.c
 * @brief   `ecum` 命令：RUN/POST_RUN 模式迁移、模式查询、睡一次
 *
 * @details 从 `main.c` 的 `EcuM_CmdExec()` 迁来（M-Shell 命令迁移）。
 *          对外两种入口并存（迁移期）：
 *          - 新：`ecum` / `ecum run` / `ecum postrun` / `ecum sleep`
 *          - 旧：`!q` / `!U` / `!u` / `!z`（main.c 的 CmdExec 调本文件的
 *                `EcumCmd_*` 包装，脚本 m11/m12 无需改动）
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh.h"
#include "platform_cvm0146.h"
#include "EcuM.h"
#include "EcuM_Externals.h"
#include "EcuM_Cfg.h"   /* ECUM_WKSOURCE_CAN0（唤醒源位定义） */

#include <string.h>   /* strcmp：子命令分派 */

/**
 * @brief 进入 POST_RUN（释放 RUN 后请求 POST_RUN）
 */
void EcumCmd_RequestPostRun(void)
{
	Std_ReturnType rc = EcuM_ReleaseRUN((EcuM_UserType)0u);

	if (rc == E_OK) {
		rc = EcuM_RequestPOST_RUN((EcuM_UserType)0u);
	}
	sh_print("[ecum] ReleaseRUN + RequestPOST_RUN -> %s\r\n",
	         (rc == E_OK) ? "accepted" : "FAIL");
}

/**
 * @brief 回到 RUN（释放 POST_RUN 后请求 RUN）
 */
void EcumCmd_RequestRun(void)
{
	Std_ReturnType rc = EcuM_ReleasePOST_RUN((EcuM_UserType)0u);

	if (rc == E_OK) {
		rc = EcuM_RequestRUN((EcuM_UserType)0u);
	}
	sh_print("[ecum] ReleasePOST_RUN + RequestRUN -> %s\r\n",
	         (rc == E_OK) ? "accepted" : "FAIL");
}

/**
 * @brief 打印当前 EcuM 模式
 */
void EcumCmd_Mode(void)
{
	sh_print("[ecum] mode=%u (0=OFF 1=STARTUP 2=RUN 3=POST_RUN 5=SLEEP)\r\n",
	         (unsigned)EcuM_AL_GetMode());
}

/**
 * @brief 手动睡一次（STOP/Sleep），醒来报告唤醒源
 *
 * @details 验的是 **WFI 通路 + 唤醒源读取**，不是低功耗指标：
 *          配 100 ms 兜底节拍 → WFI → 被 tick 唤醒 → 读唤醒源 → 恢复 1 ms 节拍。
 *
 * @warning **为什么不完全停掉 SysTick**：停了就有睡死风险 —— 本工程还没有可用的
 *          外部唤醒源（收发器 WAKE 引脚硬件没接，PTE4 端口唤醒也没配）。
 *          一旦睡死只能断电重启，这个代价不能由一条测试命令承担。
 *          把节拍放大到 100 ms 有两个好处：
 *          ① 兜底：100 ms 后一定醒，**不可能睡死**；
 *          ② 可测：1 ms 节拍下 WFI 几乎立刻返回，什么都量不出；
 *             100 ms 下能看到 `Platform_NowMs()` 只前进了 1，而实际过了约 100 ms
 *             —— 这就是"CPU 真的停过"的证据。
 *
 * @note 睡着期间所有 10 ms 节拍任务都停，醒来后 CanTp/Dcm/NM 的定时器会"跳"一下，
 *       这是停节拍的必然结果；正常运行路径不会睡。
 */
void EcumCmd_SleepOnce(void)
{
	uint32_t t0;

	sh_puts("[sleep] 进 STOP(Sleep) 模式，100 ms 兜底唤醒...\r\n");

	/* 走 EcuM 的标准接口使能唤醒源（当前只记录 + 打日志，
	 * 因为唯一能关的中断是 SysTick，而它是兜底，见 ecum_callout.c） */
	EcuM_EnableWakeupSources((EcuM_WakeupSourceType)ECUM_WKSOURCE_CAN0);

	t0 = Platform_NowMs();
	Platform_SetTickPeriodMs(100u);
	Platform_EnterStopMode();
	Platform_StartTick();

	sh_print("[sleep] 醒来: tick +%u (约 %u ms), 唤醒源=%s(%u)\r\n",
	         (unsigned)(Platform_NowMs() - t0),
	         (unsigned)((Platform_NowMs() - t0) * 100u),
	         Platform_GetWakeupSourceName(Platform_GetWakeupSource()),
	         (unsigned)Platform_GetWakeupSource());

	/* 走一遍标准唤醒链路：EcuM_CheckWakeup → ComM → Nm → CanNm。
	 * 即使这次是 tick 唤醒（不是 CAN），也要让它跑一遍 ——
	 * 验证接口可达，并且日志能说清"实际是什么唤醒的"。 */
	EcuM_CheckWakeup((EcuM_WakeupSourceType)ECUM_WKSOURCE_CAN0);
}

/**
 * @brief ecum [run|postrun|sleep] —— 模式迁移与睡眠测试
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 */
static int sh_cmd_ecum(int argc, char *argv[])
{
	if (argc == 1) {
		EcumCmd_Mode();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	if (strcmp(argv[1], "run") == 0) {
		EcumCmd_RequestRun();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(argv[1], "postrun") == 0) {
		EcumCmd_RequestPostRun();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(argv[1], "sleep") == 0) {
		EcumCmd_SleepOnce();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	sh_puts(SH_RET_PARA);
	return SH_ERR_PARAM;
}

SH_EXPORT_CMD(ecum, sh_cmd_ecum, "ecum [run|postrun|sleep] -- mode / sleep once");
