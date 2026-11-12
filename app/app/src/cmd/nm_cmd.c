/**
 * @file    nm_cmd.c
 * @brief   `nm` 命令：网络请求/释放/被动启动/状态查询（M9）
 *
 * @details 从 `main.c` 的「网络管理（M9）」区迁来（M-Shell 命令迁移）。
 *          对外两种入口并存（迁移期）：
 *          - 新：`nm` / `nm req` / `nm rel` / `nm passive`
 *          - 旧：`!m` / `!a` / `!R` / `!A`（main.c 的 CmdExec 调本文件包装）
 *
 * @note    应用**只碰 Nm/ComM**，不直接调 CanNm ——
 *          越层调用会让 ComM 的 nmFlag 与通道状态长期不一致。
 *
 * @author  binbina
 * @version V1.0.0
 */

#if !defined(SH_DISABLE_CMD_NM)

#include "sh_cfg.h"   /* 含生成头：SH_DISABLE_CMD_* 与 SH_VERSION_STR */
#include "platform_cvm0146.h"
#include "Nm.h"
#include "NmStack_Types.h"
#include "CanNm.h"
#include "ComM.h"
#include "ComM_Cfg.h"
#include "Nm_Cfg.h"

#include <string.h>

/** @name ComM 状态名（下标 = `ComM_StateType` 取值） */
#define COMM_STATE_NAME_NUM     (5u)
static const char *const s_commStateName[COMM_STATE_NAME_NUM] = {
	"NO_COM_NO_PENDING",
	"NO_COM_REQUEST_PENDING",
	"FULL_COM_NETWORK_REQUESTED",
	"FULL_COM_READY_SLEEP",
	"SILENT_COM",
};

/** @name CanNm 状态名（下标 = `Nm_StateType` 取值） */
#define NM_STATE_NAME_NUM       (8u)
static const char *const s_nmStateName[NM_STATE_NAME_NUM] = {
	"UNINIT",
	"BUS_SLEEP",
	"PREPARE_BUS_SLEEP",
	"READY_SLEEP",
	"NORMAL_OPERATION",
	"REPEAT_MESSAGE",
	"SYNCHRONIZE",
	"OFFLINE",
};

/** @name CanNm 模式名（下标 = `Nm_ModeType` 取值） */
#define NM_MODE_NAME_NUM        (4u)
static const char *const s_nmModeName[NM_MODE_NAME_NUM] = {
	"BUS_SLEEP",
	"PREPARE_BUS_SLEEP",
	"SYNCHRONIZE",
	"NETWORK",
};

/**
 * @brief 打印 ComM/CanNm 当前状态（旧 `!m`）
 *
 * @note M9 时期这里有一个 `ComM_Log()` 弱符号覆盖，用来实时打印状态变化。
 *       M11 换成 as-master 的 ComM 之后它**没有这个钩子**（标准 ComM 只有
 *       `ComM_GetState` 查询），那段日志被删掉了。
 *       现在查当前状态用本命令；想要时间线就 Kvaser + 串口同录。
 */
void NmCmd_DumpState(void)
{
	Nm_StateType   nmState = NM_STATE_UNINIT;
	Nm_ModeType    nmMode  = NM_MODE_BUS_SLEEP;
	ComM_StateType comm    = COMM_NO_COM_NO_PENDING_REQUEST;

	(void)CanNm_GetState((NetworkHandleType)NM_CFG_CHANNEL_CAN0, &nmState, &nmMode);
	(void)ComM_GetState((NetworkHandleType)NM_CFG_CHANNEL_CAN0, &comm);

	sh_print("[nm] comm=%s(%u) cannm=%s(%u) mode=%s(%u)\r\n",
	         (comm < COMM_STATE_NAME_NUM) ? s_commStateName[comm] : "?",
	         (unsigned)comm,
	         (nmState < NM_STATE_NAME_NUM) ? s_nmStateName[nmState] : "?",
	         (unsigned)nmState,
	         (nmMode < NM_MODE_NAME_NUM) ? s_nmModeName[nmMode] : "?",
	         (unsigned)nmMode);
}

/**
 * @brief 请求网络（旧 `!a`）
 *
 * @note **M11 起走 ComM，不再直接调 `Nm_NetworkRequest`**。
 *       AUTOSAR 里应用不能绕过通信管理器直接操作某根总线：否则 ComM 认为
 *       "没有通信需求"，而 NM 已经在发报文，两边状态长期不一致。
 *       链路：ComM_RequestComMode → 仲裁 → Nm_NetworkRequest
 *             → CanNm_NetworkRequest → NM 报文发出
 */
void NmCmd_Request(void)
{
	Std_ReturnType rc = ComM_RequestComMode((ComM_UserHandleType)COMM_USER_APP,
	                                        (ComM_ModeType)COMM_FULL_COMMUNICATION);

	sh_print("[comm] RequestComMode(FULL) -> %s\r\n", (rc == E_OK) ? "accepted" : "FAIL");
}

/**
 * @brief 释放网络（旧 `!R`）
 */
void NmCmd_Release(void)
{
	Std_ReturnType rc = ComM_RequestComMode((ComM_UserHandleType)COMM_USER_APP,
	                                        (ComM_ModeType)COMM_NO_COMMUNICATION);

	sh_print("[comm] RequestComMode(NO_COM) -> %s\r\n", (rc == E_OK) ? "accepted" : "FAIL");
}

/**
 * @brief 模拟"总线活动把 ECU 唤醒"（旧 `!A`）
 *
 * @details 为什么不再直接调 `Nm_PassiveStartUp`：M9 时这里就是那么写的，
 *          接上 ComM 之后那是**越层调用** —— ComM 不知道有人被动启动，
 *          它的 `nmFlag` 与通道状态还是旧的，于是"NM 在发报文、ComM 认为没通信"。
 *
 *          标准链路：收发器检测总线活动 → EcuM_CheckWakeup
 *                → ComM_EcuM_WakeUpIndication(channel)
 *                → ComM 置 COMM_NM_FLAG_NETWORK_START
 *                → 下一拍 MainFunction 走 PassiveStartup
 *                → Nm_PassiveStartUp → CanNm 进 RepeatMessage
 *
 * @warning **as-master 的 ComM 没有实现 `ComM_EcuM_WakeUpIndication()`**
 *          （`ComM.h` 只有声明、全仓无定义，链接期才报错）。
 *          所以这里调同一条链路的后半段 `ComM_Nm_NetworkStartIndication()` ——
 *          它做的事完全一样（置 `COMM_NM_FLAG_NETWORK_START`，下一拍
 *          `ComM_MainFunction()` 就走 `COMM_NOCOM_STARTUP_PASSIVE`）。
 *          等收发器唤醒中断接上后，正确写法是在 EcuM 的 wakeup 处理里补一个
 *          `ComM_EcuM_WakeUpIndication()` 实现（一行转调），而不是继续调 Nm 侧入口。
 *
 * @note 被动启动不置 `CANNM_REQUEST_MASK`：报文里的 CBV 主动唤醒位是 0，
 *       表示"我是被叫醒的"；跑完 RepeatMessageTime 若本地无请求会自动睡回去。
 */
void NmCmd_PassiveStartup(void)
{
	ComM_Nm_NetworkStartIndication((NetworkHandleType)COMM_CHANNEL_CAN0);
	sh_puts("[comm] Nm NetworkStartIndication -> issued\r\n");
}

/**
 * @brief nm [req|rel|passive] —— 网络管理命令
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 */
static int sh_cmd_nm(int argc, char *argv[])
{
	if (argc == 1) {
		NmCmd_DumpState();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(argv[1], "req") == 0) {
		NmCmd_Request();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(argv[1], "rel") == 0) {
		NmCmd_Release();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}
	if (strcmp(argv[1], "passive") == 0) {
		NmCmd_PassiveStartup();
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	sh_puts(SH_RET_PARA);
	return SH_ERR_PARAM;
}

SH_EXPORT_CMD(nm, sh_cmd_nm, "nm [req|rel|passive] -- network management");

#endif /* !SH_DISABLE_CMD_NM */
