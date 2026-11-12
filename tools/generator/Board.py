# 从 config/Board/Board.json 生成 Board_Cfg.h / Board_Cfg.c
#
# 板级抽象的第一步：把"这块板是什么、有哪些资源"收敛成一份 JSON。
# 实际板子出来时新建一个 Board.json（或改这份的值），驱动代码不动。
# 引脚级映射仍留在 Port/Dio/Adc/Pwm 各自的配置表里，后续再逐步收进来。

import os
import json

from .helper import GenHeader

__all__ = ["Gen"]


def Gen_Board(cfg, dir):
	H = open("%s/Board_Cfg.h" % (dir), "w")
	GenHeader(H)
	H.write("#ifndef BOARD_CFG_H\n")
	H.write("#define BOARD_CFG_H\n")
	H.write("/* ================================ [ INCLUDES  ] ============================================== */\n")
	H.write("#include <stdint.h>\n")
	H.write("/* ================================ [ MACROS    ] ============================================== */\n")
	H.write('/* 本文件由 tools/generator/Board.py 生成；改 config/Board/Board.json */\n')
	H.write("#define BOARD_NAME                  \"%s\"\n" % cfg.get("boardName", "unknown"))
	H.write("#define BOARD_MCU                   \"%s\"\n" % cfg.get("mcu", "unknown"))
	H.write("#define BOARD_CORE_CLOCK_HZ         (%uU)\n" % cfg.get("coreClockHz", 120000000))
	H.write("#define BOARD_CONSOLE_UART          (%uU)\n" % cfg.get("console", {}).get("uart", 2))
	H.write("#define BOARD_CONSOLE_BAUD          (%uU)\n" % cfg.get("console", {}).get("baud", 115200))
	H.write("#define BOARD_CAN_NUM               (%uU)\n" % len(cfg.get("can", [])))
	H.write("#define BOARD_PWM_FREQ_HZ           (%uU)\n" % cfg.get("pwm", {}).get("frequencyHz", 100))
	H.write("#define BOARD_PWM_CHANNELS          (%uU)\n" % cfg.get("pwm", {}).get("channels", 0))
	H.write("#define BOARD_ADC_GROUPS            (%uU)\n" % cfg.get("adc", {}).get("groups", 0))
	H.write("/* ================================ [ TYPES     ] ============================================== */\n")
	H.write("/** @brief 板级身份与资源概览（只读表，命令与自检用） */\n")
	H.write("typedef struct {\n")
	H.write("\tconst char *name;            /**< 板名 */\n")
	H.write("\tconst char *mcu;             /**< MCU 型号 */\n")
	H.write("\tuint32_t    coreClockHz;     /**< 内核时钟 */\n")
	H.write("\tuint16_t    consoleUart;     /**< 控制台 UART 实例 */\n")
	H.write("\tuint32_t    consoleBaud;     /**< 控制台波特率 */\n")
	H.write("\tuint8_t     canCount;        /**< CAN 控制器数 */\n")
	H.write("\tuint8_t     pwmChannels;     /**< PWM 通道数 */\n")
	H.write("\tuint16_t    pwmFreqHz;       /**< PWM 频率 */\n")
	H.write("\tuint8_t     adcGroups;       /**< ADC 组数 */\n")
	H.write("} Board_InfoType;\n")
	H.write("/* ================================ [ DECLARES  ] ============================================== */\n")
	H.write("extern const Board_InfoType Board_Cfg_Info;\n")
	H.write("/* ================================ [ DATAS     ] ============================================== */\n")
	H.write("/* ================================ [ LOCALS    ] ============================================== */\n")
	H.write("/* ================================ [ FUNCTIONS ] ============================================== */\n")
	H.write("#endif /* BOARD_CFG_H */\n")
	H.close()

	cans = cfg.get("can", [])
	C = open("%s/Board_Cfg.c" % (dir), "w")
	GenHeader(C)
	C.write("/* ================================ [ INCLUDES  ] ============================================== */\n")
	C.write('#include "Board_Cfg.h"\n')
	C.write("/* ================================ [ MACROS    ] ============================================== */\n")
	C.write("/* ================================ [ TYPES     ] ============================================== */\n")
	C.write("/* ================================ [ DECLARES  ] ============================================== */\n")
	C.write("/* ================================ [ DATAS     ] ============================================== */\n")
	C.write("const Board_InfoType Board_Cfg_Info = {\n")
	C.write("\t.name        = BOARD_NAME,\n")
	C.write("\t.mcu         = BOARD_MCU,\n")
	C.write("\t.coreClockHz = BOARD_CORE_CLOCK_HZ,\n")
	C.write("\t.consoleUart = BOARD_CONSOLE_UART,\n")
	C.write("\t.consoleBaud = BOARD_CONSOLE_BAUD,\n")
	C.write("\t.canCount    = BOARD_CAN_NUM,\n")
	C.write("\t.pwmChannels = BOARD_PWM_CHANNELS,\n")
	C.write("\t.pwmFreqHz   = BOARD_PWM_FREQ_HZ,\n")
	C.write("\t.adcGroups   = BOARD_ADC_GROUPS,\n")
	C.write("};\n")
	C.write("/* ================================ [ LOCALS    ] ============================================== */\n")
	C.write("/* ================================ [ FUNCTIONS ] ============================================== */\n")
	C.close()


def Gen(cfg):
	dir = os.path.join(os.path.dirname(cfg), "GEN")
	os.makedirs(dir, exist_ok=True)
	with open(cfg, encoding="utf-8") as f:
		cfg = json.load(f)
	Gen_Board(cfg, dir)
	return ["%s/Board_Cfg.c" % (dir)]
