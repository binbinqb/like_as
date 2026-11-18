/**
 * @file    IoHwAbAc.c
 * @brief   IoHwAb 的目标板能力实现（Dio / Adc / Pwm）
 *
 * @details @section IOHWABAC_WHY 为什么和 Core 分开
 *
 *          `app/app/src/iohwab.c` 是**芯片无关**的核心，Host 测试编同一份；
 *          本文件只在 Target 构建里参与编译，是"能力 ops"落到 CVM0146
 *          HAL 的唯一位置。换 MCU 只改本文件，Core 与业务不动。
 *
 *          @section IOHWABAC_POL 极性不在这里
 *
 *          Adapter 只收发**电气电平**（TRUE = 引脚高）。逻辑↔电气的转换
 *          统一由 Core 按表项 `activeLevel` 完成 —— 这里再取反一次就是
 *          双重反转（V1.0.0 的契约歧义，V1.0.1 已收敛）。
 *
 *          @section IOHWABAC_SEQ 样本序号
 *
 *          `seq` 只在**真的读到新样本**时才加 1：
 *          - GPIO 每次读都是即时电平，逐次 +1；
 *          - ADC 必须"转换完成"才 +1（不能用会重新触发转换的接口）。
 *
 *          @section IOHWABAC_HOST Host 通道在板上为什么是空桩
 *
 *          配置里 `source=host` 的通道用于 Host 测试。Target 构建必须也能
 *          链接（生成表引用了 `IoHwAb_Host*Ops`），所以在板上提供
 *          "函数指针全 NULL"的实例：调用方据此返回 `E_NOT_OK`。
 *          **不允许在这里返回假数据** —— 那会让"板上不可用"看起来像正常。
 *
 * @author  binbina
 * @version V1.0.1
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：GPIO 直连、PWM 换 0..0x8000、Host 空桩 |
 * | V1.0.1 | 2026-11-18 | binbina | 输入能力增加样本序号；明确极性归属 Core |
 */

#include "iohwab.h"

#include "Dio.h"
#include "Pwm.h"

/** @brief DIN 通道数上限（seq 计数器数组尺寸） */
#define IOHWABAC_DIN_MAX    (16u)

/* ============================ [ GPIO：数字输入 ] ============================ */

/** @brief 每通道样本序号：GPIO 每次读到的都是即时电平，故逐次 +1 */
static uint16 s_dinSeq[IOHWABAC_DIN_MAX];

/**
 * @brief 读电气电平
 * @param[in]  channel 物理通道（来自 Board.json 的 dioChannels 顺序）
 * @param[out] level   电气电平
 * @param[out] seq     样本序号
 * @return E_OK / E_NOT_OK
 * @note  `Dio_ReadChannel` 在 Port 层已配置为输入；通道号生成期算好，
 *        运行期不再查表。
 */
static Std_ReturnType iohwabac_DinRead(uint16 channel, boolean *level,
                                       uint16 *seq)
{
	if ((channel >= IOHWABAC_DIN_MAX) || (level == NULL) || (seq == NULL)) {
		return E_NOT_OK;
	}
	*level = (Dio_ReadChannel((Dio_ChannelType)channel) == STD_HIGH) ? TRUE : FALSE;
	s_dinSeq[channel]++;
	*seq = s_dinSeq[channel];
	return E_OK;
}

/* ============================ [ GPIO：数字输出 ] ============================ */

/**
 * @brief 输出锁存影子
 *
 * @warning 本芯片 `PinsDrv_ReadPin()` 读的是 **PDIR（输入数据）**，纯输出引脚
 *          在输入通路未使能时恒为 0 —— 直接回读会把"已写高"误判成低。
 *          所以这里保存**最后一次成功写入的电气电平**作为回读值。
 *
 *          ⚠ 它证明的是"写通路已执行"，**不是**"引脚真的到了该电平"。
 *          引脚级确认只能靠板级观察（LED）/示波器 —— 这一条不要对上层隐瞒：
 *          `io status` 的注释与 `doc/设计评审/IoHwAb-V2.0架构.md` 的验收分级
 *          都按"锁存影子"表述。
 *
 * @note  写入参数 `level` 是**电气电平**（Core 已做完极性转换），本层不再取反。
 */
static boolean s_doutLatch[16];

static Std_ReturnType iohwabac_DoutWrite(uint16 channel, boolean level)
{
	if (channel >= 16u) {
		return E_NOT_OK;
	}
	Dio_WriteChannel((Dio_ChannelType)channel,
	                 (level != FALSE) ? STD_HIGH : STD_LOW);
	s_doutLatch[channel] = (level != FALSE) ? TRUE : FALSE;
	return E_OK;
}

static Std_ReturnType iohwabac_DoutRead(uint16 channel, boolean *level)
{
	if ((channel >= 16u) || (level == NULL)) {
		return E_NOT_OK;
	}
	*level = s_doutLatch[channel];
	return E_OK;
}

/* ============================ [ ADC ] ============================ */

/**
 * @brief 读 ADC 原始值
 *
 * @note  V1.0 的 Board.json **没有直连 AIN 通道**（`io.ain` 全是 host），
 *        所以这里先返回 `E_NOT_OK`（"未实现"必须显式失败，不能给假值）。
 *        接入真实模拟量时按下面约定实现：
 *        - `channel = (group << 8) | index`，由生成器编码；
 *        - 只有该组**转换完成**时才 `(*seq)++`；未完成时返回上一次的 seq，
 *          Core 会据此判"没有新样本"而不是拿旧值反复滤波；
 *        - 取值用"读上次结果"的接口，**不要**用会重新触发转换的
 *          `Adc_ReadGroup()`，否则与 RS2260 的 ABC 时序冲突
 *          （见 IoHwAb-V2.0 架构 §7）。
 */
static Std_ReturnType iohwabac_AinReadRaw(uint16 channel, uint16 *raw,
                                          uint16 *seq)
{
	(void)channel;
	(void)raw;
	(void)seq;
	return E_NOT_OK;
}

/* ============================ [ PWM ] ============================ */

/**
 * @brief 写占空比
 * @note  IoHwAb 的 0..10000 映射到 AUTOSAR 的 0..0x8000；
 *        0 与满量程由 Pwm 驱动内部处理成静态电平
 */
static Std_ReturnType iohwabac_PwmSetDuty(uint16 channel, uint16 duty)
{
	uint32 scaled = ((uint32)duty * 0x8000u) / IOHWAB_PWM_FULL;

	Pwm_SetDutyCycle((Pwm_ChannelType)channel, (Pwm_DutyCycleType)scaled);
	return E_OK;
}

/* ============================ [ 能力实例 ] ============================ */

const IoHwAb_DinOpsType IoHwAb_GpioDinOps = {
	iohwabac_DinRead
};

const IoHwAb_DoutOpsType IoHwAb_GpioDoutOps = {
	iohwabac_DoutWrite,
	iohwabac_DoutRead
};

const IoHwAb_AinOpsType IoHwAb_AdcOps = {
	iohwabac_AinReadRaw
};

const IoHwAb_PwmOpsType IoHwAb_PwmOps = {
	iohwabac_PwmSetDuty
};

/* Host 通道在板上不可用：函数指针为 NULL，调用方返回 E_NOT_OK */
const IoHwAb_DinOpsType IoHwAb_HostDinOps = { NULL };
const IoHwAb_DoutOpsType IoHwAb_HostDoutOps = { NULL, NULL };
const IoHwAb_AinOpsType IoHwAb_HostAinOps = { NULL };
const IoHwAb_PwmOpsType IoHwAb_HostPwmOps = { NULL };
