/**
 * @file    io_cmd.c
 * @brief   `io` 命令：IoHwAb 上板自检（LED 与通道状态）
 *
 * @details @section IOCMD_WHY 为什么需要这条命令
 *
 *          IoHwAb V1.0 在板上唯一可验证的直连输出是三个 LED。
 *          没有命令入口，`IoHwAb_Init()` 会被链接器的 `--gc-sections`
 *          整段丢掉（曾经出现过：改了代码但 `text` 尺寸一字不变）。
 *
 *          @section IOCMD_USAGE 用法
 *
 *          | 命令 | 作用 |
 *          |------|------|
 *          | `io` | 打印所有逻辑通道的配置与当前值 |
 *          | `io led r on` / `io led g off` | 写一个 LED（逻辑值，极性由表项处理） |
 *          | `io safe` | 所有输出回安全状态 |
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：LED 写/安全状态/状态打印 |
 */

#if !defined(SH_DISABLE_CMD_IO)

#include "sh_cfg.h"
#include "sh.h"

#include <string.h>

#include "iohwab.h"
#include "IoHwAb_Cfg.h"

/** @brief 名称 → LED 通道号；找不到返回 -1 */
static int io_cmd_led_id(const char *s)
{
	if ((s[0] == 'r') || (s[0] == 'R')) {
		return (int)IOHWAB_DOUT_LED_R;
	}
	if ((s[0] == 'g') || (s[0] == 'G')) {
		return (int)IOHWAB_DOUT_LED_G;
	}
	if ((s[0] == 'b') || (s[0] == 'B')) {
		return (int)IOHWAB_DOUT_LED_B;
	}
	return -1;
}

/**
 * @brief `io` 命令实现
 * @param[in] argc 参数个数
 * @param[in] argv 参数
 * @return 0 成功
 */
static int sh_cmd_io(int argc, char *argv[])
{
	const char *sub = (argc > 1) ? argv[1] : "";
	boolean v;
	IoHwAb_StatusType st;

	if ((sub[0] == '\0') || (0 == strcmp(sub, "status"))) {
		uint16 i;
		boolean fault;

		sh_print("  init    = %u\r\n", (unsigned)IoHwAb_IsInitialized());
		for (i = 0u; i < IOHWAB_DOUT_COUNT; i++) {
			fault = FALSE;
			(void)IoHwAb_DoutGetFault((IoHwAb_DoutId)i, &fault);
			if (IoHwAb_DoutReadBack((IoHwAb_DoutId)i, &v) == E_OK) {
				sh_print("  dout[%u] = %u%s\r\n", (unsigned)i, (unsigned)v,
				         (fault != FALSE) ? "  (write failed)" : "");
			} else {
				sh_print("  dout[%u] = n/a%s（不支持回读或后端失败）\r\n",
				         (unsigned)i,
				         (fault != FALSE) ? " write failed" : "");
			}
		}
		(void)IoHwAb_DinRead((IoHwAb_DinId)0, &v, &st);
		sh_print("  din[0]  = %u (status=%u)\r\n", (unsigned)v, (unsigned)st);
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	if (0 == strcmp(sub, "safe")) {
		if (IoHwAb_SetAllSafe() != E_OK) {
			sh_puts("<-300, some outputs failed (see io status)\r\n");
			return SH_ERR;
		}
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	if (0 == strcmp(sub, "led")) {
		int id;

		if (argc < 4) {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
		id = io_cmd_led_id(argv[2]);
		if (id < 0) {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
		if (IoHwAb_DoutWrite((IoHwAb_DoutId)id,
		                     (boolean)(0 == strcmp(argv[3], "on"))) != E_OK) {
			sh_puts("<-300, write failed\r\n");
			return SH_ERR;
		}
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	sh_puts(SH_RET_PARA);
	return SH_ERR_PARAM;
}

SH_EXPORT_CMD(io, sh_cmd_io, "io [status | safe | led r|g|b on|off] -- IoHwAb 自检");

#endif /* SH_DISABLE_CMD_IO */
