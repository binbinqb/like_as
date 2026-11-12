/**
 * @file    dtc_cmd.c
 * @brief   `dtc` 命令：故障快照 dump / 清除 / 注入
 *
 * @details 从 `main.c` 的旧 `!b/!B/!i` 迁出（M-Shell 命令迁移）。
 *          清除与注入**复用 `CanTest_CmdExec` 的实现**（`'B'`/`'i'`）：
 *          旧入口与新命令必须走同一条后端路径，不能各写一份，
 *          否则会出现"串口清掉了、诊断仪还读得到"这类两套行为。
 *
 * @note    用法：
 *          - `dtc`          故障快照表（同 `dtc dump`）
 *          - `dtc clear`    走 Dem_SelectDTC + Dem_ClearDTC（与 0x14 同路径）
 *          - `dtc inject`   注入一条 bus-off 记录（单节点实验室造不出真 bus-off）
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh.h"
#include "can_test.h"

#include <string.h>

/**
 * @brief dtc [dump|clear|inject] —— 故障码操作
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 */
static int sh_cmd_dtc(int argc, char *argv[])
{
	const char *sub = (argc > 1) ? argv[1] : "dump";

	if (strcmp(sub, "dump") == 0) {
		Fault_Dump();
	} else if (strcmp(sub, "clear") == 0) {
		/* 复用旧分支：Dem_SelectDTC + Dem_ClearDTC（与 UDS 0x14 同一条后端） */
		CanTest_CmdExec('B');
	} else if (strcmp(sub, "inject") == 0) {
		CanTest_CmdExec('i');
	} else {
		sh_puts(SH_RET_PARA);
		return SH_ERR_PARAM;
	}

	sh_puts(SH_RET_OK);
	return SH_OK;
}

SH_EXPORT_CMD(dtc, sh_cmd_dtc, "dtc [dump|clear|inject] -- DTC snapshot / clear / inject");
