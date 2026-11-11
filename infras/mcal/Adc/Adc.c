/**
 * @file    Adc.c
 * @brief   ADC 驱动的芯片无关实现（AUTOSAR MCAL）
 * @details 本文件**只做四件事**，与 as-master 的 `Dio.c` / `Port.c` 同一套路：
 *          1. DET 参数校验；
 *          2. 维护每组的状态机与结果缓冲；
 *          3. 查配置表；
 *          4. 转发给平台 `AdcAc_*()`。
 *
 *          @warning **这里不允许出现任何寄存器名或芯片型号**。
 *                   一旦在 `Adc.c` 里看到 `ADC0` / `SC1` / `PDB`，分层就破了 ——
 *                   换芯片时要改的就是这一层，那就失去了分层的意义。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：Init/组转换/读结果/通知 |
 */
#ifdef USE_ADC
/* ================================ [ INCLUDES  ] ============================================== */
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Adc_Priv.h"
#include "Det.h"
#include "Std_Debug.h"
/* ================================ [ MACROS    ] ============================================== */
#define AS_LOG_ADC 0
#define AS_LOG_ADCI 0
#define AS_LOG_ADCE 3

#define ADC_CONFIG (&Adc_Config)
/* ================================ [ TYPES     ] ============================================== */
/**
 * @brief 单组的运行期状态
 * @note  配置（ROM）与状态（RAM）严格分开：配置表是 `const`，
 *        运行期只改这个结构，避免"跑着跑着把配置改了"这类难查的问题。
 */
typedef struct {
	Adc_ValueGroupType *buffer;              /**< 绑定的结果缓冲，NULL=未绑定 */
	Adc_StatusType      status;              /**< 当前状态 */
	boolean             notificationEnabled; /**< 是否要发完成通知 */
	boolean             notified;            /**< 本轮是否已通知过（防重复） */
} Adc_GroupStateType;
/* ================================ [ DECLARES  ] ============================================== */
extern const Adc_ConfigType Adc_Config;
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
static Adc_GroupStateType s_groupState[ADC_CFG_NUM_GROUPS];
static boolean s_initialized = FALSE;
/* ================================ [ ALIAS     ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/**
 * @brief 推进一组的完成状态，并在状态从 BUSY 迁到 COMPLETED 时发一次通知
 *
 * @param[in] Group 组号（已由调用方校验过范围）
 *
 * @note 本工程的 ADC 完成检测是**轮询式**（CVM014x 的 SDK 未提供转换完成中断的
 *       封装，只有 `AdcDrv_GetCocon()` 标志位）。所以通知只能在"有人来查状态"
 *       的那一刻补发，而不是硬实时地发。
 *
 * @warning 若将来改用 COCO 中断触发，**必须把通知改到 ISR 里发**，
 *          并把这里的 `notified` 逻辑一起搬过去 —— 否则会出现"中断里发一次、
 *          轮询又发一次"的重复通知。
 */
static void Adc_AdvanceState(Adc_GroupType Group) {
	Adc_GroupStateType *st = &s_groupState[Group];

	if (st->status != ADC_BUSY) {
		return;
	}
	if (!AdcAc_IsGroupCompleted(Group)) {
		return;
	}

	st->status = ADC_COMPLETED;

	if (st->notificationEnabled && (!st->notified)) {
		st->notified = TRUE;
		if (ADC_CONFIG->groups[Group].notification != NULL) {
			ADC_CONFIG->groups[Group].notification(Group);
		}
	}
}

void Adc_Init(const Adc_ConfigType *ConfigPtr) {
	uint16_t i;

	DET_VALIDATE(!s_initialized, ADC_SID_INIT, ADC_E_ALREADY_INITIALIZED, return);
	DET_VALIDATE(ConfigPtr != NULL, ADC_SID_INIT, ADC_E_PARAM_POINTER, return);

	for (i = 0; i < (uint16_t)ADC_CFG_NUM_GROUPS; i++) {
		s_groupState[i].buffer = NULL;
		s_groupState[i].status = ADC_IDLE;
		s_groupState[i].notificationEnabled = FALSE;
		s_groupState[i].notified = FALSE;
	}

	if (AdcAc_Init(ConfigPtr) == E_OK) {
		s_initialized = TRUE;
		ASLOG(ADC, ("[adc] init ok, %u group(s)\n", (unsigned)ADC_CFG_NUM_GROUPS));
	} else {
		ASLOG(ADCE, ("[adc] AdcAc_Init failed\n"));
	}
}

void Adc_DeInit(void) {
	DET_VALIDATE(s_initialized, ADC_SID_DEINIT, ADC_E_UNINIT, return);

	AdcAc_DeInit();
	s_initialized = FALSE;
}

Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group,
                                     Adc_ValueGroupType *BufferPtr) {
	DET_VALIDATE(s_initialized, ADC_SID_SETUP_RESULT_BUFFER, ADC_E_UNINIT, return E_NOT_OK);
	DET_VALIDATE(Group < (Adc_GroupType)ADC_CFG_NUM_GROUPS,
	             ADC_SID_SETUP_RESULT_BUFFER, ADC_E_PARAM_GROUP, return E_NOT_OK);
	DET_VALIDATE(BufferPtr != NULL, ADC_SID_SETUP_RESULT_BUFFER,
	             ADC_E_PARAM_POINTER, return E_NOT_OK);

	s_groupState[Group].buffer = BufferPtr;
	return E_OK;
}

void Adc_StartGroupConversion(Adc_GroupType Group) {
	DET_VALIDATE(s_initialized, ADC_SID_START_GROUP_CONV, ADC_E_UNINIT, return);
	DET_VALIDATE(Group < (Adc_GroupType)ADC_CFG_NUM_GROUPS,
	             ADC_SID_START_GROUP_CONV, ADC_E_PARAM_GROUP, return);

	if (AdcAc_StartGroupConversion(Group) == E_OK) {
		s_groupState[Group].status = ADC_BUSY;
		s_groupState[Group].notified = FALSE;
	}
}

void Adc_StopGroupConversion(Adc_GroupType Group) {
	DET_VALIDATE(s_initialized, ADC_SID_STOP_GROUP_CONV, ADC_E_UNINIT, return);
	DET_VALIDATE(Group < (Adc_GroupType)ADC_CFG_NUM_GROUPS,
	             ADC_SID_STOP_GROUP_CONV, ADC_E_PARAM_GROUP, return);

	(void)AdcAc_StopGroupConversion(Group);
	s_groupState[Group].status = ADC_IDLE;
}

Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr) {
	Adc_ValueGroupType *dst;

	DET_VALIDATE(s_initialized, ADC_SID_READ_GROUP, ADC_E_UNINIT, return E_NOT_OK);
	DET_VALIDATE(Group < (Adc_GroupType)ADC_CFG_NUM_GROUPS,
	             ADC_SID_READ_GROUP, ADC_E_PARAM_GROUP, return E_NOT_OK);

	/* 允许两种用法：显式传缓冲区，或用 SetupResultBuffer 绑定的那个 */
	dst = (DataBufferPtr != NULL) ? DataBufferPtr : s_groupState[Group].buffer;
	if (dst == NULL) {
		ASLOG(ADCE, ("[adc] group %u has no result buffer\n", (unsigned)Group));
		return E_NOT_OK;
	}

	Adc_AdvanceState(Group);
	if (s_groupState[Group].status != ADC_COMPLETED) {
		return E_NOT_OK;
	}

	return AdcAc_ReadGroupRaw(Group, dst);
}

Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group) {
	if ((!s_initialized) || (Group >= (Adc_GroupType)ADC_CFG_NUM_GROUPS)) {
		return ADC_IDLE;
	}

	Adc_AdvanceState(Group);
	return s_groupState[Group].status;
}

void Adc_EnableGroupNotification(Adc_GroupType Group) {
	DET_VALIDATE(s_initialized, 0x13, ADC_E_UNINIT, return);
	DET_VALIDATE(Group < (Adc_GroupType)ADC_CFG_NUM_GROUPS, 0x13, ADC_E_PARAM_GROUP, return);

	s_groupState[Group].notificationEnabled = TRUE;
}

void Adc_DisableGroupNotification(Adc_GroupType Group) {
	DET_VALIDATE(s_initialized, 0x14, ADC_E_UNINIT, return);
	DET_VALIDATE(Group < (Adc_GroupType)ADC_CFG_NUM_GROUPS, 0x14, ADC_E_PARAM_GROUP, return);

	s_groupState[Group].notificationEnabled = FALSE;
}

void Adc_GetVersionInfo(Std_VersionInfoType *versioninfo) {
	DET_VALIDATE(versioninfo != NULL, 0x12, ADC_E_PARAM_POINTER, return);

	versioninfo->vendorID = 0;
	versioninfo->moduleID = MODULE_ID_ADC;
	versioninfo->sw_major_version = 1;
	versioninfo->sw_minor_version = 0;
	versioninfo->sw_patch_version = 0;
}
#endif /* USE_ADC */
