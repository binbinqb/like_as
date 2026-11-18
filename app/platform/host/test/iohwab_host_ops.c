/**
 * @file    iohwab_host_ops.c
 * @brief   Host 上的 IoHwAb 能力实现（内存模拟）与故障注入
 *
 * @details @section HOSTOPS_WHY 为什么 Host 要单独实现能力
 *
 *          `iohwab.c` 是芯片无关的核心，Host 与 Target 编的是**同一份源码**。
 *          差别只在链接进来的 ops 实例：Host 用本文件的内存数组，
 *          Target 用 `IoHwAbAc.c` 的 Dio/Adc/Pwm。
 *
 *          这样 Host 测试证明的是**核心逻辑**（消抖/滤波/极性/安全状态），
 *          不是"我又实现了一遍硬件"。
 *
 *          @section HOSTOPS_SEQ 样本序号与"冻结"
 *
 *          默认每次成功读取都算一个新样本（`seq` +1），与真实 GPIO 一致。
 *          `HostIo_SetDinFrozen()` / `HostIo_SetAinFrozen()` 把通道冻住：
 *          读取仍返回 `E_OK`，但 `seq` 不再变 —— 用来模拟 MUX / I2C 扩展器
 *          "这一拍没有新数据"，验证 Core 不会拿旧样本反复消抖、并能判 `STALE`。
 *
 *          @section HOSTOPS_LIMIT 边界
 *          本文件里的 GPIO/ADC/PWM 实例是空桩（函数指针 NULL）——
 *          配置中 `source=direct` 的 LED 通道在 Host 上应当返回 `E_NOT_OK`。
 *          这正好用来验证"不支持的能力不得伪造正常值"。
 *
 * @author  binbina
 * @version V1.0.1
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：DIN/AIN/DOUT/PWM 模拟 + 故障注入 |
 * | V1.0.1 | 2026-11-18 | binbina | 增加样本序号与"冻结"控制、DOUT 写失败注入 |
 */

#include "iohwab.h"

#define HOST_CH_MAX   (8u)

static boolean s_hDin[HOST_CH_MAX];
static boolean s_hDinFail[HOST_CH_MAX];
static boolean s_hDinFrozen[HOST_CH_MAX];
static uint16  s_hDinSeq[HOST_CH_MAX];

static uint16  s_hAin[HOST_CH_MAX];
static boolean s_hAinFail[HOST_CH_MAX];
static boolean s_hAinFrozen[HOST_CH_MAX];
static uint16  s_hAinSeq[HOST_CH_MAX];

static boolean s_hDout[HOST_CH_MAX];
static boolean s_hDoutFail[HOST_CH_MAX];
static uint16  s_hPwm[HOST_CH_MAX];

/* ============================ [ 测试控制接口 ] ============================ */

void HostIo_SetDin(uint16 ch, boolean level)
{
	if (ch < HOST_CH_MAX) {
		s_hDin[ch] = level;
	}
}

void HostIo_SetDinFail(uint16 ch, boolean fail)
{
	if (ch < HOST_CH_MAX) {
		s_hDinFail[ch] = fail;
	}
}

/** @brief 冻结/解冻 DIN：冻结后读取仍 E_OK，但 seq 不变（模拟无新样本） */
void HostIo_SetDinFrozen(uint16 ch, boolean frozen)
{
	if (ch < HOST_CH_MAX) {
		s_hDinFrozen[ch] = frozen;
	}
}

void HostIo_SetAin(uint16 ch, uint16 raw)
{
	if (ch < HOST_CH_MAX) {
		s_hAin[ch] = raw;
	}
}

void HostIo_SetAinFail(uint16 ch, boolean fail)
{
	if (ch < HOST_CH_MAX) {
		s_hAinFail[ch] = fail;
	}
}

/** @brief 冻结/解冻 AIN：冻结后读取仍 E_OK，但 seq 不变 */
void HostIo_SetAinFrozen(uint16 ch, boolean frozen)
{
	if (ch < HOST_CH_MAX) {
		s_hAinFrozen[ch] = frozen;
	}
}

/** @brief 注入 DOUT 写失败（用于验证 SetAllSafe / DoutGetFault 的错误反馈） */
void HostIo_SetDoutFail(uint16 ch, boolean fail)
{
	if (ch < HOST_CH_MAX) {
		s_hDoutFail[ch] = fail;
	}
}

/** @brief 读回 Host 输出的**电气电平**（用于验证极性转换在 Core 完成） */
boolean HostIo_GetDoutLevel(uint16 ch)
{
	return (ch < HOST_CH_MAX) ? s_hDout[ch] : FALSE;
}

uint16 HostIo_GetPwm(uint16 ch)
{
	return (ch < HOST_CH_MAX) ? s_hPwm[ch] : 0u;
}

/* ============================ [ Host 能力实现 ] ============================ */

static Std_ReturnType hostDinRead(uint16 ch, boolean *level, uint16 *seq)
{
	if ((ch >= HOST_CH_MAX) || (level == NULL) || (seq == NULL)) {
		return E_NOT_OK;
	}
	if (s_hDinFail[ch]) {
		return E_NOT_OK;
	}
	*level = s_hDin[ch];
	if (!s_hDinFrozen[ch]) {
		s_hDinSeq[ch]++;
	}
	*seq = s_hDinSeq[ch];
	return E_OK;
}

static Std_ReturnType hostAinRead(uint16 ch, uint16 *raw, uint16 *seq)
{
	if ((ch >= HOST_CH_MAX) || (raw == NULL) || (seq == NULL)) {
		return E_NOT_OK;
	}
	if (s_hAinFail[ch]) {
		return E_NOT_OK;
	}
	*raw = s_hAin[ch];
	if (!s_hAinFrozen[ch]) {
		s_hAinSeq[ch]++;
	}
	*seq = s_hAinSeq[ch];
	return E_OK;
}

static Std_ReturnType hostDoutWrite(uint16 ch, boolean level)
{
	if (ch >= HOST_CH_MAX) {
		return E_NOT_OK;
	}
	if (s_hDoutFail[ch]) {
		/* 注入失败：**不**更新电气状态，模拟"命令没到器件" */
		return E_NOT_OK;
	}
	s_hDout[ch] = level;
	return E_OK;
}

static Std_ReturnType hostDoutRead(uint16 ch, boolean *level)
{
	if ((ch >= HOST_CH_MAX) || (level == NULL)) {
		return E_NOT_OK;
	}
	*level = s_hDout[ch];
	return E_OK;
}

static Std_ReturnType hostPwmSet(uint16 ch, uint16 duty)
{
	if (ch >= HOST_CH_MAX) {
		return E_NOT_OK;
	}
	s_hPwm[ch] = duty;
	return E_OK;
}

const IoHwAb_DinOpsType IoHwAb_HostDinOps = { hostDinRead };
const IoHwAb_AinOpsType IoHwAb_HostAinOps = { hostAinRead };
const IoHwAb_DoutOpsType IoHwAb_HostDoutOps = { hostDoutWrite, hostDoutRead };
const IoHwAb_PwmOpsType IoHwAb_HostPwmOps = { hostPwmSet };

/* ============================ [ 目标能力的空桩 ] ============================ */
/*
 * 配置里 `source=direct` 的通道（本板 3 个 LED）在 Host 上没有 GPIO，
 * 必须提供符号以便链接，但**所有操作返回 E_NOT_OK**：
 * 这正是"Host 不该假装能点亮 LED"的正确语义。
 */
const IoHwAb_DinOpsType IoHwAb_GpioDinOps = { NULL };
const IoHwAb_DoutOpsType IoHwAb_GpioDoutOps = { NULL, NULL };
const IoHwAb_AinOpsType IoHwAb_AdcOps = { NULL };
const IoHwAb_PwmOpsType IoHwAb_PwmOps = { NULL };
