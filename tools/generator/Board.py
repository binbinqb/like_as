# 从 config/Board/Board.json 生成 Board_Cfg.h / Board_Cfg.c
#
# 板级抽象的第一步：把"这块板是什么、有哪些资源"收敛成一份 JSON。
# 实际板子出来时新建一个 Board.json（或改这份的值），驱动代码不动。
# 引脚级映射仍留在 Port/Dio/Adc/Pwm 各自的配置表里，后续再逐步收进来。

import os
import json

from .helper import GenHeader
from .IoHwAb import Gen_Tables

__all__ = ["Gen"]


def Gen_Board(cfg, dir):
	H = open("%s/Board_Cfg.h" % (dir), "w", newline="\n")
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
	# 每通道波特率：Can_Cfg.c 直接引用这里，不再自己在 Can_Cfg.h 里写一份
	# （02.1 唯一来源：Board.json 的 can[].bitrate）。
	for _i, _c in enumerate(cfg.get("can", [])):
		H.write("#define BOARD_CAN%u_BITRATE          (%uU)\n"
		        % (_i, _c.get("bitrate", 500000)))
	H.write("#define BOARD_PWM_FREQ_HZ           (%uU)\n" % cfg.get("pwm", {}).get("frequencyHz", 100))
	H.write("#define BOARD_PWM_CHANNELS          (%uU)\n" % cfg.get("pwm", {}).get("channels", 0))
	H.write("#define BOARD_ADC_GROUPS            (%uU)\n" % cfg.get("adc", {}).get("groups", 0))
	# ── 引脚表（Port_Cfg.c 用）：PIN 名 → PORT_PIN_DEF 展开 ──────
	H.write("\n/* 引脚表：Port_Cfg.c 直接把这张表填进 Port_PortPinConfigs */\n")
	H.write("#define BOARD_PINS_TABLE \\\n")
	pins = cfg.get("pins", [])
	for i, pin in enumerate(pins):
		tail = "" if i == len(pins) - 1 else ", \\"
		H.write('\tPORT_PIN_DEF(%s, %s, %s, PORT_PORT_%s, %uu, %uu)%s\n' %
		        (pin.get("mode", "DIO"), pin.get("dir", "OUT"), pin.get("level", "LOW"),
		         pin.get("port", "A"), pin.get("pin", 0), pin.get("mux", 1), tail))
	H.write("\n/* Dio 通道表：按名字引用上面的引脚，顺序即通道号 */\n")
	H.write("#define BOARD_DIO_CHANNELS \\\n")
	chans = cfg.get("dioChannels", [])
	by_name = {p.get("name"): p for p in pins}
	for i, name in enumerate(chans):
		pin = by_name.get(name, {"port": "A", "pin": 0})
		tail = "" if i == len(chans) - 1 else ", \\"
		H.write('\t{ (uint8_t)PORT_PORT_%s, %uu }%s\n' %
		        (pin.get("port", "A"), pin.get("pin", 0), tail))
	H.write("\n")
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
	C = open("%s/Board_Cfg.c" % (dir), "w", newline="\n")
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
	# 逻辑 IO 通道表与板级身份同源（Board.json），但生成逻辑独立在 IoHwAb.py：
	# V1.1 加 devices/selectBuses 时只改那个文件，不碰本文件。
	files = ["%s/Board_Cfg.c" % (dir)]
	files += Gen_Tables(cfg, dir)
	return files
