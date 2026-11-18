/**
 * @file    mux_host_ops.c
 * @brief   Host 上的 MuxManager 硬件替身：模拟 ABC 选择 + COM 电平 + ADC 时序
 *
 * @details @section HOSTMUX_WHY 为什么能测出真问题
 *
 *          `mux.c` 是芯片无关的状态机，Host 与 Target 编同一份。
 *          本文件只模拟**硬件行为**，而且刻意模拟了两件真实器件才会暴露的事：
 *
 *          1. **COM 只有一根**：同一个 COM 在不同 ABC 上读到的是不同 Y 的电压。
 *             所以取值表按 `[com通道][abc]` 索引，而不是按"逻辑通道"—— 如果
 *             状态机在错误的 ABC 下取值，断言立刻发现。
 *          2. **ADC 有转换时间**：`HostMux_SetAdcReadyAfter(n)` 让转换延迟 n 次
 *             查询才完成。状态机若在这期间切了 ABC，`HostMux_GetAbcStabilityViolations()`
 *             就会计数 —— 这正是"转换期间 ABC 必须稳定"的可执行判据。
 *
 *          @section HOSTMUX_LIMIT 边界
 *
 *          - 只模拟一条 SelectBus、两片设备（一片 GPIO COM、一片 ADC COM）；
 *          - 不模拟模拟开关的 Ron/电荷注入/建立时间（那是 `settleTicks` 的事，
 *            由测试直接配置，真实取值必须来自器件手册）。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：ABC 记录、COM 取值表、ADC 延迟/超时/故障注入 |
 */

#include "mux.h"

#define HOST_COM_MAX    (8u)

/** @brief COM 电平：[COM 通道][ABC] —— 同一个 COM 在不同选择下读到不同 Y */
static boolean s_gpioVal[HOST_COM_MAX][MUX_Y_MAX];
static boolean s_gpioFail[HOST_COM_MAX];

/** @brief ADC 原始值：[COM 通道][ABC] */
static uint16 s_adcVal[HOST_COM_MAX][MUX_Y_MAX];
static boolean s_adcFail[HOST_COM_MAX];
static uint8  s_adcReadyAfter[HOST_COM_MAX];   /**< 查询多少次后才完成 */
static uint8  s_adcLeft[HOST_COM_MAX];
static uint8  s_adcPending[HOST_COM_MAX];
static uint8  s_adcStartAbc[HOST_COM_MAX];

/** @brief ABC 观测 */
static uint8  s_lastAbc;
static uint16 s_selectWrites;
static uint8  s_abcWrites[MUX_Y_MAX];
static uint16 s_abcViolations;
static uint16 s_inhWrites;

/* ============================ [ 测试控制接口 ] ============================ */

/** @brief 清计数与转换状态（保留配置值与注入标志） */
void HostMux_Reset(void)
{
	uint8 i;

	s_lastAbc = 0u;
	s_selectWrites = 0u;
	s_abcViolations = 0u;
	s_inhWrites = 0u;
	for (i = 0u; i < MUX_Y_MAX; i++) {
		s_abcWrites[i] = 0u;
	}
	for (i = 0u; i < HOST_COM_MAX; i++) {
		s_adcPending[i] = 0u;
		s_adcLeft[i] = 0u;
		s_adcStartAbc[i] = 0u;
	}
}

void HostMux_SetGpio(uint8 comCh, uint8 y, boolean level)
{
	if ((comCh < HOST_COM_MAX) && (y < MUX_Y_MAX)) {
		s_gpioVal[comCh][y] = level;
	}
}

void HostMux_SetGpioFail(uint8 comCh, boolean fail)
{
	if (comCh < HOST_COM_MAX) {
		s_gpioFail[comCh] = fail;
	}
}

void HostMux_SetAdc(uint8 comCh, uint8 y, uint16 raw)
{
	if ((comCh < HOST_COM_MAX) && (y < MUX_Y_MAX)) {
		s_adcVal[comCh][y] = raw;
	}
}

/** @brief 转换需要多少次查询才完成（0 = 下一次查询就绪） */
void HostMux_SetAdcReadyAfter(uint8 comCh, uint8 polls)
{
	if (comCh < HOST_COM_MAX) {
		s_adcReadyAfter[comCh] = polls;
	}
}

void HostMux_SetAdcFail(uint8 comCh, boolean fail)
{
	if (comCh < HOST_COM_MAX) {
		s_adcFail[comCh] = fail;
	}
}

uint16 HostMux_GetSelectWrites(void)
{
	return s_selectWrites;
}

uint8 HostMux_GetAbcWrites(uint8 abc)
{
	return (abc < MUX_Y_MAX) ? s_abcWrites[abc] : 0u;
}

uint16 HostMux_GetAbcStabilityViolations(void)
{
	return s_abcViolations;
}

uint16 HostMux_GetInhWrites(void)
{
	return s_inhWrites;
}

uint8 HostMux_GetLastAbc(void)
{
	return s_lastAbc;
}

/* ============================ [ HwOps 实现 ] ============================ */

static void hostmux_SelectWrite(uint8 bus, uint8 abc)
{
	(void)bus;                  /* 只有一条总线 */
	s_lastAbc = abc;
	s_selectWrites++;
	if (abc < MUX_Y_MAX) {
		s_abcWrites[abc]++;
	}
}

static void hostmux_InhWrite(uint8 ch, uint8 level)
{
	(void)ch;
	(void)level;
	s_inhWrites++;
}

static Std_ReturnType hostmux_GpioRead(uint16 ch, boolean *level)
{
	if ((ch >= HOST_COM_MAX) || (level == NULL)) {
		return E_NOT_OK;
	}
	if (s_gpioFail[ch]) {
		return E_NOT_OK;
	}
	*level = s_gpioVal[ch][s_lastAbc];
	return E_OK;
}

static Std_ReturnType hostmux_AdcStart(uint16 ch)
{
	if (ch >= HOST_COM_MAX) {
		return E_NOT_OK;
	}
	if (s_adcFail[ch]) {
		return E_NOT_OK;
	}
	s_adcPending[ch] = 1u;
	s_adcLeft[ch] = s_adcReadyAfter[ch];
	s_adcStartAbc[ch] = s_lastAbc;
	return E_OK;
}

static Std_ReturnType hostmux_AdcReady(uint16 ch, boolean *ready)
{
	if ((ch >= HOST_COM_MAX) || (ready == NULL)) {
		return E_NOT_OK;
	}
	if (s_adcPending[ch] == 0u) {
		*ready = FALSE;
		return E_OK;
	}
	if (s_adcLeft[ch] > 0u) {
		s_adcLeft[ch]--;
		*ready = FALSE;
	} else {
		*ready = TRUE;
	}
	return E_OK;
}

static Std_ReturnType hostmux_AdcRead(uint16 ch, uint16 *raw)
{
	if ((ch >= HOST_COM_MAX) || (raw == NULL) || (s_adcPending[ch] == 0u)) {
		return E_NOT_OK;
	}
	/* 核心断言：取值时 ABC 必须与启动转换时一致 */
	if (s_lastAbc != s_adcStartAbc[ch]) {
		s_abcViolations++;
	}
	*raw = s_adcVal[ch][s_lastAbc];
	s_adcPending[ch] = 0u;
	return E_OK;
}

/* ============================ [ 配置表 ] ============================ */

/*
 * 一条 SelectBus（A/B/C 用 Dio 0/1/2），两片设备共用：
 *   dev0 = GPIO COM（Dio 0），dev1 = ADC COM（group0 ch0）
 * 只启用 Y0..Y3（activeMask=0x0F），用来验证"未用到的 ABC 不扫描"。
 */
const Mux_BusCfgType Mux_BusCfgs[1] = {
	{ 0u, 1u, 2u, 0u, 3u, 0x0Fu }
};

const Mux_DeviceCfgType Mux_DeviceCfgs[2] = {
	{ 0u, (uint8)MUX_COM_GPIO, 0u, MUX_NO_CHANNEL, 0u, 0x0Fu },
	{ 0u, (uint8)MUX_COM_ADC,  0u, MUX_NO_CHANNEL, 0u, 0x0Fu }
};

const uint8 Mux_BusCount = 1u;
const uint8 Mux_DeviceCount = 2u;

const Mux_HwOpsType Mux_HwOps = {
	hostmux_SelectWrite,
	hostmux_InhWrite,
	hostmux_GpioRead,
	hostmux_AdcStart,
	hostmux_AdcReady,
	hostmux_AdcRead
};
