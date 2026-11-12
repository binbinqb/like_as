/**
 * @file    dtc_cmd.c
 * @brief   `dtc` 命令：故障快照 dump / 清除 / 注入
 *
 * @details 从 `main.c` 的旧 `!b/!B/!i` 迁出（M-Shell 命令迁移）。
 *          清除与注入直接调 `Fault_ClearDtc()` / `Fault_InjectBusOff()`：
 *          与 UDS 0x14 / 故障注入走同一条后端路径，不各写一份。
 *
 * @note    用法：
 *          - `dtc`          故障快照表（同 `dtc dump`）
 *          - `dtc clear`    走 Dem_SelectDTC + Dem_ClearDTC（与 0x14 同路径）
 *          - `dtc inject`   注入一条 bus-off 记录（单节点实验室造不出真 bus-off）
 *
 * @author  binbina
 * @version V1.0.0
 */

#if !defined(SH_DISABLE_CMD_DTC)

#include "sh_cfg.h"   /* 含生成头：SH_DISABLE_CMD_* 与 SH_VERSION_STR */
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
		Fault_ClearDtc();
	} else if (strcmp(sub, "inject") == 0) {
		Fault_InjectBusOff();
	} else {
		sh_puts(SH_RET_PARA);
		return SH_ERR_PARAM;
	}

	sh_puts(SH_RET_OK);
	return SH_OK;
}

SH_EXPORT_CMD(dtc, sh_cmd_dtc, "dtc [dump|clear|inject] -- DTC snapshot / clear / inject");

#endif /* !SH_DISABLE_CMD_DTC */
