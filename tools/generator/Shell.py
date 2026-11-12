# SSAS - Simple Smart Automotive Software
# 从 config/Shell/Shell.json 生成 Shell_Cfg.h / Shell_Cfg.c
#
# 与 as-master 生成器同构：Gen(cfg) 读 JSON、写 GEN/、返回生成的文件列表。
# Shell 的配置目前全是编译期常量（提示符/容量/特性开关），所以只出宏定义头；
# Shell_Cfg.c 提供一个配置指纹常量，便于在镜像里确认配置版本。

import os
import json

from .helper import GenHeader

__all__ = ["Gen"]


def Gen_Shell(cfg, dir):
	H = open("%s/Shell_Cfg.h" % (dir), "w")
	GenHeader(H)
	H.write("#ifndef SHELL_CFG_H\n")
	H.write("#define SHELL_CFG_H\n")
	H.write("/* ================================ [ MACROS    ] ============================================== */\n")
	H.write("/* 本文件由 tools/generator/Shell.py 生成，勿手改；改 config/Shell/Shell.json */\n\n")

	H.write('#define SH_BOARD_NAME               "%s"\n' % cfg.get("boardName", "CVM014x-BCM"))
	H.write('#define SH_VERSION_STR              "%s"\n' % cfg.get("version", "1.0.0"))
	H.write('#define SH_PROMPT                   "%s"\n' % cfg.get("prompt", "CVM014x >> "))
	H.write("\n")
	H.write("#define SH_CMD_LINE_MAX             (%uU)\n" % cfg.get("lineMax", 128))
	H.write("#define SH_MAX_ARGS                 (%uU)\n" % cfg.get("maxArgs", 16))
	H.write("#define SH_TX_RING                  (%uU)\n" % cfg.get("txRing", 1024))
	H.write("#define SH_PRINT_BUF                (%uU)\n" % cfg.get("printBuf", 256))
	H.write("#define SH_HISTORY_DEPTH            (%uU)\n" % cfg.get("historyDepth", 8))
	H.write("#define SH_CTX_POOL                 (%uU)\n" % cfg.get("ctxPool", 2))
	H.write("\n")
	mode = cfg.get("defaultMode", "manual")
	H.write("#define SH_DEFAULT_MODE             (SH_MODE_%s)\n" % mode.upper())
	H.write("\n")
	H.write("/* 配置指纹：改 Shell.json 这个字符串就变 */\n")
	H.write('#define SH_CFG_ID                   "%s/%s/%s"\n' %
	        (cfg.get("boardName", "CVM014x-BCM"), cfg.get("version", "1.0.0"),
	         mode))
	H.write("/* ================================ [ TYPES     ] ============================================== */\n")
	H.write("/* ================================ [ DECLARES  ] ============================================== */\n")
	H.write("/* ================================ [ DATAS     ] ============================================== */\n")
	H.write("/* ================================ [ LOCALS    ] ============================================== */\n")
	H.write("/* ================================ [ FUNCTIONS ] ============================================== */\n")
	H.write("#endif /* SHELL_CFG_H */\n")
	H.close()

	C = open("%s/Shell_Cfg.c" % (dir), "w")
	GenHeader(C)
	C.write("/* ================================ [ INCLUDES  ] ============================================== */\n")
	C.write('#include "Shell_Cfg.h"\n')
	C.write("/* ================================ [ MACROS    ] ============================================== */\n")
	C.write("/* ================================ [ TYPES     ] ============================================== */\n")
	C.write("/* ================================ [ DECLARES  ] ============================================== */\n")
	C.write("/* ================================ [ DATAS     ] ============================================== */\n")
	C.write("/** @brief 配置指纹（镜像里可 grep 到，用于确认烧的是哪份配置） */\n")
	C.write("const char Shell_Cfg_Id[] = SH_CFG_ID;\n")
	C.write("/* ================================ [ LOCALS    ] ============================================== */\n")
	C.write("/* ================================ [ FUNCTIONS ] ============================================== */\n")
	C.close()


def Gen(cfg):
	dir = os.path.join(os.path.dirname(cfg), "GEN")
	os.makedirs(dir, exist_ok=True)
	with open(cfg, encoding="utf-8") as f:
		cfg = json.load(f)
	Gen_Shell(cfg, dir)
	return ["%s/Shell_Cfg.c" % (dir)]
