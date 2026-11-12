/**
 * @file    board_cmd.c
 * @brief   `board` 命令：板级信息（槽位 / 构建时间 / 控制台）
 *
 * @details 本文件是 **cmd 模块化模式**的第一个样板：
 *          - 命令文件独立成 `cmd/xxx_cmd.c`，只依赖 `sh.h` 与平台头；
 *          - 通过 `SH_EXPORT_CMD` 落入 `hal_sh_cmd` 段，无需任何注册表；
 *          - 不参与编译（模块裁剪/未 glob）时，`help` 里自然看不到该命令，
 *            编译链接都不会报错。
 *
 * @note    输出带 SCPI 风格应答头 `<+0, ...`，上位机脚本可直接抓。
 *
 * @author  binbina
 * @version V1.0.0
 */

#if !defined(SH_DISABLE_CMD_BOARD)

#include "sh_cfg.h"   /* SH_VERSION_STR / SH_BOARD_NAME（内部已 include sh.h） */
#include "platform_cvm0146.h"
#include "Board_Cfg.h"   /* 板级身份表（Board.json 生成） */

#ifndef APP_SLOT_INDEX
#define APP_SLOT_INDEX 0
#endif

/**
 * @brief board —— 打印板级信息
 * @param[in] argc 参数个数（未使用）
 * @param[in] argv 参数数组（未使用）
 * @return 0 成功
 */
static int sh_cmd_board(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	sh_print("<+0, board=%s (%s) slot=%c build=%s %s\r\n",
	         Board_Cfg_Info.name, Board_Cfg_Info.mcu,
	         (APP_SLOT_INDEX == 0) ? 'A' : 'B',
	         __DATE__, __TIME__);
	sh_print("     core=%uMHz console=UART%u/%u can=%u pwm=%uch@%uHz adcGroups=%u shell=sh-%s\r\n",
	         (unsigned)(Board_Cfg_Info.coreClockHz / 1000000u),
	         (unsigned)Board_Cfg_Info.consoleUart,
	         (unsigned)Board_Cfg_Info.consoleBaud,
	         (unsigned)Board_Cfg_Info.canCount,
	         (unsigned)Board_Cfg_Info.pwmChannels,
	         (unsigned)Board_Cfg_Info.pwmFreqHz,
	         (unsigned)Board_Cfg_Info.adcGroups,
	         SH_VERSION_STR);
	return SH_OK;
}

SH_EXPORT_CMD(board, sh_cmd_board, "board info: slot / build / console");

#endif /* !SH_DISABLE_CMD_BOARD */
