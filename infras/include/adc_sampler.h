/**
 * @file    adc_sampler.h
 * @brief   AdcSampler：直连模拟通道的采样调度（异步设备自管节奏）
 *
 * @details @section ADCS_WHY 为什么不让 IoHwAb 直接读 ADC
 *
 *          `Adc_ReadGroup()` 只在"转换已完成"时才返回结果；如果每次读都
 *          先去启动、再忙等，等于把 10 ms 节拍交给一个微秒级外设，而且
 *          **一次转换只能服务一个读者**。所以按 V2.0 的分工：
 *          "异步输入设备自己负责采样和时间调度，IoHwAb 只消费样本"。
 *
 *          本模块按组轮转：启动 → 下一拍查完成 → 完成则整组读入并发布，
 *          每个通道 `seq` +1。IoHwAb 侧的 `IoHwAb_AdcOps` 只查已发布样本。
 *
 *          @section ADCS_OWNER 组的所有权
 *
 *          一个 ADC 组**只能有一个驱动者**：
 *          - 直连 AIN → 本模块；
 *          - MUX 的 ADC COM → MuxManager（它要自己控制转换时机）。
 *
 *          生成器 R15 会拒绝"同一组既做直连 AIN 又接 MUX"的配置。
 *          两个驱动者同时操作同一组，读到的可能是另一次转换的结果 ——
 *          这种错误在数据上看不出来（值都"合理"），必须靠配置期拦住。
 *
 *          @section ADCS_TIMEOUT 超时
 *
 *          转换迟迟不完成（触发链路坏了 / PDB 没使能）时，等
 *          `ADC_SAMPLER_TIMEOUT_TICKS` 拍就放弃本轮；`seq` 不变，
 *          IoHwAb 自然转 `STALE`。**不发布假值**。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：按组轮转 + 完成发布 + 超时丢弃 |
 */

#ifndef ADC_SAMPLER_H
#define ADC_SAMPLER_H

#include "Std_Types.h"

/** @brief 组数上限 */
#define ADC_SAMPLER_GROUP_MAX       (4u)
/** @brief 每组通道数上限 */
#define ADC_SAMPLER_CH_MAX          (8u)
/** @brief 单组转换等待上限（10 ms 拍） */
#define ADC_SAMPLER_TIMEOUT_TICKS   (5u)

/** @brief 一个组的采样配置 */
typedef struct {
	uint8 group;        /**< Adc 组号 */
	uint8 numChannels;  /**< 组内槽位数（对应 Adc_Cfg 的通道数） */
} AdcSampler_GroupCfgType;

/**
 * @brief 硬件访问表（Target 用 Adc HAL，Host 用模拟）
 * @note  只收发原始值，不做滤波/换算。
 */
typedef struct {
	/** @brief 启动一次组转换 */
	Std_ReturnType (*Start)(uint8 group);
	/** @brief 查询本轮是否完成 */
	Std_ReturnType (*Completed)(uint8 group, boolean *done);
	/** @brief 读整组结果（不重新触发转换），buf 长度 ≥ 组通道数 */
	Std_ReturnType (*Read)(uint8 group, uint16 *buf, uint8 n);
} AdcSampler_HwOpsType;

/* 配置表由平台提供（Target: AdcSamplerAc.c；Host: 测试替身） */
extern const AdcSampler_GroupCfgType AdcSampler_GroupCfgs[];
extern const uint8 AdcSampler_GroupCount;
extern const AdcSampler_HwOpsType AdcSampler_HwOps;

/** @brief 清状态（在 Adc_Init 之后调用） */
void AdcSampler_Init(void);

/**
 * @brief 10 ms 调度：启动/查完成/发布
 * @note  不阻塞；未完成的组在下一拍继续查。
 */
void AdcSampler_MainFunction(void);

/**
 * @brief 取一个通道的最新样本
 * @param[in]  group Adc 组号
 * @param[in]  slot  组内槽位
 * @param[out] raw   原始值
 * @param[out] seq   样本序号（每次发布 +1）
 * @return E_OK；组未配置 / 槽位越界 / 尚未采到 → E_NOT_OK
 */
Std_ReturnType AdcSampler_GetRaw(uint8 group, uint8 slot, uint16 *raw,
                                 uint16 *seq);

/** @brief 转换超时累计次数（诊断） */
uint32 AdcSampler_GetTimeouts(void);

#endif /* ADC_SAMPLER_H */
