/**
 * @file    com_cmd.c
 * @brief   `com` 命令：信号 dump / IPdu 分组启停（M10）
 *
 * @details 实现在 `app/app/src/com_app.c`，本文件只做命令路由：
 *          - 新：`com` / `com sig` / `com group`
 *          - 旧：`!v` / `!y`（main.c 转调同一批函数）
 *
 * @author  binbina
 * @version V1.0.0
 */

#if !defined(SH_DISABLE_CMD_COM)

#include "sh_cfg.h"   /* 含生成头：SH_DISABLE_CMD_* 与 SH_VERSION_STR */
#include "cmd_api.h"

#include <string.h>

/**
 * @brief com [sig|group] —— 信号层验收
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 * @note 不带参数等价于 `sig`。
 */
static int sh_cmd_com(int argc, char *argv[])
{
	const char *sub = (argc > 1) ? argv[1] : "sig";

	if (strcmp(sub, "sig") == 0) {
		ComCmd_DumpSignals();
	} else if (strcmp(sub, "group") == 0) {
		ComCmd_GroupToggle();
	} else if (strcmp(sub, "can1") == 0) {
		ComCmd_DumpCan1();
	} else {
		sh_puts(SH_RET_PARA);
		return SH_ERR_PARAM;
	}

	sh_puts(SH_RET_OK);
	return SH_OK;
}

SH_EXPORT_CMD(com, sh_cmd_com, "com [sig|group|can1] -- signal dump / ipdu group toggle / can1 pdu state");

#endif /* !SH_DISABLE_CMD_COM */
