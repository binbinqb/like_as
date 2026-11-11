/**
 * @file    Adc_Priv.h
 * @brief   ADC 驱动的配置结构与平台接口（模块私有头）
 * @details 三段式的中间一环：
 *          | 层 | 文件 | 职责 |
 *          |----|------|------|
 *          | 接口 | `Adc.h` | 标准 API、类型、错误码 |
 *          | **配置/边界** | **本文件** | **配置结构体 + 平台要实现的 `AdcAc_*()`** |
 *          | 实现 | `Adc.c` | DET 校验 + 查表 + 转发 |
 *          | 平台 | `AdcAc.c` | 真正操作 ADC/PDB/SIM 寄存器 |
 *
 *          **本文件是整个模块的分界线**：它之上是"芯片无关"，之下是"芯片相关"。
 *          `Adc.c` 里不允许出现任何寄存器名，`AdcAc.c` 之外不允许出现配置表。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：组/通道配置结构 + AdcAc 边界 |
 */
#ifndef _ADC_PRIV_H_
#define _ADC_PRIV_H_
/* ================================ [ INCLUDES  ] ============================================== */
#include "Std_Types.h"
#include "Modules.h"   /* MODULE_ID_ADC：DET_THIS_MODULE_ID 要用 */
#include "Adc.h"
#ifdef __cplusplus
extern "C" {
#endif
/* ================================ [ MACROS    ] ============================================== */
#define DET_THIS_MODULE_ID MODULE_ID_ADC

/** @brief 表示"本组不使用该字段"的哨兵值（配置表里填它即可） */
#define ADC_CHANNEL_NONE     (0xFFu)
/* ================================ [ TYPES     ] ============================================== */
/**
 * @brief 单个 ADC 通道的硬件属性
 *
 * @note 这些值**全部来自数据手册**，不是"随便填"：
 *       `samplingTime` 配小了读到的是上一个通道的残留电荷；
 *       `refVoltageMv` 填错则所有换算值等比偏移。
 */
typedef struct {
	uint8_t  hwChannel;      /**< 硬件通道号（ADCH 域，0~n） */
	uint8_t  resolution;     /**< 转换位数：8/10/12 */
	uint16_t samplingTime;   /**< 采样时间，单位=ADC 时钟周期数 */
	uint16_t refVoltageMv;   /**< 参考电压 mV（如 3300 / 5000） */
	uint8_t  diffMode;       /**< 0=单端，1=差分 */
} Adc_ChannelConfigType;

/**
 * @brief 一个转换组
 *
 * @note 组的语义（AUTOSAR）：一组通道**一次触发、依次转换**，
 *       全部完成后置 `ADC_COMPLETED` 并（若使能）回调通知。
 * @note `hwUnit` 放在组上而不是通道上：一组不能跨 ADC 单元。
 */
typedef struct {
	const Adc_ChannelConfigType *channels;      /**< 本组通道表 */
	uint8_t                      numOfChannels; /**< 通道数 */
	uint8_t                      hwUnit;        /**< ADC 硬件单元号（0=ADC0） */
	Adc_GroupConvModeType        convMode;      /**< 单次 / 连续 */
	Adc_TriggerSourceType        trigSrc;       /**< 软件 / 硬件触发 */
	Adc_NotificationType         notification;  /**< 完成通知，可为 NULL */
} Adc_GroupConfigType;

/**
 * @brief ADC 全局配置（`Adc_Init()` 的入参）
 * @note  `Adc_Cfg.c` 里定义唯一的 `const Adc_ConfigType Adc_Config` 实例。
 */
struct Adc_Config_s {
	const Adc_GroupConfigType *groups;      /**< 组表，下标即组号 */
	uint16_t                   numOfGroups; /**< 组数 */
};
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/*
 * 以下是**平台层必须实现**的边界函数（命名规则 `<模块>Ac_`，与 AS 的
 * `DioAc_` / `PortAc_` / `CanAc_` 一致）。
 *
 * 返回值统一用 `Std_ReturnType`：即使当前平台不会失败，也要留出失败通道 ——
 * ADC 初始化很容易因为时钟未开/PDB 未配置而"看起来成功但读不到值"。
 */
Std_ReturnType AdcAc_Init(const Adc_ConfigType *config);
void           AdcAc_DeInit(void);
Std_ReturnType AdcAc_StartGroupConversion(Adc_GroupType group);
Std_ReturnType AdcAc_StopGroupConversion(Adc_GroupType group);

/**
 * @brief 把组内已转换的原始值读出来
 * @param[in]  group 组号
 * @param[out] raw   长度 ≥ 该组通道数的缓冲区
 * @return E_OK 全部通道都有有效结果
 * @note 原始值**不做换算**：换算（raw → mV）是上层的事，
 *       因为换算需要"这个通道接的是什么分压网络"这种板级信息。
 */
Std_ReturnType AdcAc_ReadGroupRaw(Adc_GroupType group, uint16_t *raw);

/** @brief 查询组是否转换完成（平台侧只看硬件 COCO 标志） */
boolean AdcAc_IsGroupCompleted(Adc_GroupType group);
#ifdef __cplusplus
}
#endif
#endif /* _ADC_PRIV_H_ */
