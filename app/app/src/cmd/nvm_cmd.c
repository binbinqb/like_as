/**
 * @file    nvm_cmd.c
 * @brief   `nvm` 命令：块状态 dump / 落盘 / 打脏 / GC 压测 / 非法 id（M4）
 *
 * @details 从 `main.c` 的「存储（M4）」区迁出（M-Shell 命令迁移）。
 *          实现在 `app/app/src/storage_app.c`，本文件只做命令路由：
 *          - 新：`nvm` / `nvm dump` / `nvm writeall` / `nvm touch` /
 *                `nvm stress` / `nvm illegal`
 *          - 旧：`!d` / `!c` / `!w` / `!p` / `!x`（main.c 转调同一批函数）
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh.h"
#include "cmd_api.h"

#include <string.h>

/**
 * @brief nvm [dump|writeall|touch|stress|illegal] —— 存储栈验收
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 *
 * @note 不带参数等价于 `dump`（最常用）。
 *       `stress` 会连写 400 次（约数秒），执行期间串口可能短暂无响应 ——
 *       这是阻塞式测试的预期行为，不是死机。
 */
static int sh_cmd_nvm(int argc, char *argv[])
{
	const char *sub = (argc > 1) ? argv[1] : "dump";

	if (!Storage_IsReady()) {
		sh_puts("<-300, nvm not ready\r\n");
		return SH_ERR;
	}

	if (strcmp(sub, "dump") == 0) {
		StorageCmd_Dump();
	} else if (strcmp(sub, "writeall") == 0) {
		StorageCmd_WriteAll();
	} else if (strcmp(sub, "touch") == 0) {
		StorageCmd_Touch();
	} else if (strcmp(sub, "stress") == 0) {
		StorageCmd_Stress();
	} else if (strcmp(sub, "illegal") == 0) {
		StorageCmd_Illegal();
	} else {
		sh_puts(SH_RET_PARA);
		return SH_ERR_PARAM;
	}

	sh_puts(SH_RET_OK);
	return SH_OK;
}

SH_EXPORT_CMD(nvm, sh_cmd_nvm, "nvm [dump|writeall|touch|stress|illegal] -- NvM checks");
