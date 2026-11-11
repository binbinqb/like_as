/**
 * @file    Adc_Cfg.h
 * @brief   ADC 配置的编译期常量
 * @details 结构体定义在 `Adc_Priv.h`，实例在 `Adc_Cfg.c`。
 *          本文件只放"数量"这类编译期常量，供 `Adc.c` 静态分配状态数组。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：1 个测试组（单通道） |
 */
#ifndef _ADC_CFG_H_
#define _ADC_CFG_H_
/* ================================ [ INCLUDES  ] ============================================== */
#include "Adc.h"
/* ================================ [ MACROS    ] ============================================== */
/**
 * @brief 组数
 * @warning 改这个数必须同步改 `Adc_Cfg.c` 的 `Adc_Groups[]` 长度 ——
 *          `Adc.c` 用它静态分配状态数组，多写少写都会越界或漏配。
 */
#define ADC_CFG_NUM_GROUPS      (1u)

/** @brief 组号定义（下标即组号，与 `Adc_Groups[]` 顺序一一对应） */
#define ADC_CFG_GROUP_PROBE     (0u)

/**
 * @brief 配置实例（定义在 `Adc_Cfg.c`）
 * @note  必须在配置头里对外声明：`Adc_Init()` 的入参就是它，
 *        而这个指针由**调用方**（EcuM 或 main）持有。
 *        只把它写在 `Adc.c` 里当 `extern` 的话，任何想初始化 ADC 的
 *        翻译单元都拿不到它 —— 看起来像"配置没编进来"。
 */
extern const Adc_ConfigType Adc_Config;
#endif /* _ADC_CFG_H_ */
