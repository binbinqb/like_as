/**
 * @file    can_cmd.c
 * @brief   `can` 命令：控制面（PDU/控制器/收发器）、计数、寄存器、突发、矩阵发送
 *
 * @details 从 `main.c` 的旧 `!o/!n/!s/!g/!t/!r/!e/!k/!K/!f/!M` 迁出
 *          （M-Shell 命令迁移）。实现在 `can_test.c`，本文件只做命令路由与回读打印。
 *
 * @note 用法：
 *       - `can`                     状态（PDU / 控制器模式）
 *       - `can pdu offline|online`  PDU 模式
 *       - `can ctrl stop|start`     控制器模式
 *       - `can trcv sleep|normal`   收发器模式
 *       - `can counters [clear]`    接收计数（按邮箱 / 按 PDU）
 *       - `can regs`                寄存器现场（TEC/REC/BOFFMSK/FLTCONF）
 *       - `can burst [n]`           高频突发（默认 100 帧，制造位错误）
 *       - `can matrix`              CAN1 真实矩阵发送（M19，6 条）
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh.h"
#include "can_test.h"

#include "Can.h"
#include "Can_Cfg.h"   /* CanAc_DbgDump（平台寄存器快照） */
#include "CanIf.h"
#include "platform_cvm0146.h"

#include <string.h>

/**
 * @brief 打印当前 PDU / 控制器模式
 */
static void can_cmd_state(void)
{
	CanIf_PduModeType      pdu  = CANIF_OFFLINE;
	Can_ControllerStateType ctrl = CAN_CS_UNINIT;

	(void)CanIf_GetPduMode(0u, &pdu);
	(void)CanIf_GetControllerMode(0u, &ctrl);
	sh_print("[can] pduMode=%u (0=OFFLINE 1=TX_OFFLINE 2=TX_OFFLINE_ACTIVE 3=ONLINE) "
	         "ctrlMode=%u (1=STARTED 2=STOPPED)\r\n",
	         (unsigned)pdu, (unsigned)ctrl);
}

/**
 * @brief 设置 PDU / 控制器 / 收发器模式并回读
 * @param[in] kind "pdu" / "ctrl" / "trcv"
 * @param[in] val  子命令值
 * @return 0 成功；非 0 失败
 */
static int can_cmd_set(const char *kind, const char *val)
{
	Std_ReturnType rc = E_NOT_OK;

	if (strcmp(kind, "pdu") == 0) {
		if (strcmp(val, "offline") == 0) {
			rc = CanIf_SetPduMode(0u, CANIF_OFFLINE);
		} else if (strcmp(val, "online") == 0) {
			rc = CanIf_SetPduMode(0u, CANIF_ONLINE);
		} else {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
	} else if (strcmp(kind, "ctrl") == 0) {
		if (strcmp(val, "stop") == 0) {
			rc = CanIf_SetControllerMode(0u, CAN_CS_STOPPED);
		} else if (strcmp(val, "start") == 0) {
			rc = CanIf_SetControllerMode(0u, CAN_CS_STARTED);
		} else {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
	} else if (strcmp(kind, "trcv") == 0) {
		if (strcmp(val, "sleep") == 0) {
			rc = CanIf_SetTrcvMode(0u, CANTRCV_TRCVMODE_SLEEP);
		} else if (strcmp(val, "normal") == 0) {
			rc = CanIf_SetTrcvMode(0u, CANTRCV_TRCVMODE_NORMAL);
		} else {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
	} else {
		sh_puts(SH_RET_PARA);
		return SH_ERR_PARAM;
	}

	if (rc == E_OK) {
		sh_puts("<+0, OK!\r\n");
		can_cmd_state();
		return SH_OK;
	}
	sh_print("<-300, set failed rc=%u\r\n", (unsigned)rc);
	return SH_ERR;
}

/**
 * @brief can [子命令] —— CAN 控制面与压测
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 */
static int sh_cmd_can(int argc, char *argv[])
{
	const char *sub = (argc > 1) ? argv[1] : "";

	if (sub[0] == '\0') {
		can_cmd_state();
		return SH_OK;
	}
	if (strcmp(sub, "counters") == 0) {
		if ((argc > 2) && (strcmp(argv[2], "clear") == 0)) {
			CanTest_ClearCounters();
		} else {
			CanTest_DumpRxCounters();
		}
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(sub, "regs") == 0) {
		CanAc_DbgDump(0u);
		return SH_OK;
	}
	if (strcmp(sub, "burst") == 0) {
		uint32_t n = 100u;

		if ((argc > 2) && (!sh_parse_u32(argv[2], &n) || (n > 1000u))) {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
		CanTest_Burst((uint16_t)n);
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(sub, "matrix") == 0) {
		CanTest_SendRealMatrix();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (argc > 2) {
		return can_cmd_set(sub, argv[2]);
	}

	sh_puts(SH_RET_PARA);
	return SH_ERR_PARAM;
}

SH_EXPORT_CMD(can, sh_cmd_can, "can [pdu|ctrl|trcv|counters|regs|burst|matrix] -- CAN control");
