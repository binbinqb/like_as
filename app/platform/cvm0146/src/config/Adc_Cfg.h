/**
 * @file    Adc_Cfg.h
 * @brief   ADC 配置的编译期常量
 * @details 结构体定义在 `Adc_Priv.h`，实例在 `Adc_Cfg.c`。
 *          本文件只放"数量"这类编译期常量，供 `Adc.c` 静态分配状态数组。
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：1 个测试组（单通道） |
 * | V1.1.0 | 2026-11-11 | binbina | 扩成 2 组：ADC0 双通道（POT1+VBAT）+ ADC1 单通道（POT2） |
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
#define ADC_CFG_NUM_GROUPS      (2u)

/** @brief 组号定义（下标即组号，与 `Adc_Groups[]` 顺序一一对应） */
#define ADC_CFG_GROUP_ADC0      (0u)   /**< ADC0：POT1(ch12) + VBAT(ch13)，双通道 */
#define ADC_CFG_GROUP_ADC1      (1u)   /**< ADC1：POT2(ch2)，单通道 */

/**
 * @brief 单组最多通道数
 * @note  用来给"读一组"的临时缓冲区定长。当前最多 2 路，
 *        留到 8 是为了 MUX 场景（一个 RS2260 的 8 个 Y 通道若各自占一个 ADC 通道）。
 */
#define ADC_CFG_MAX_CH_PER_GROUP (8u)

/**
 * @brief 配置实例（定义在 `Adc_Cfg.c`）
 * @note  必须在配置头里对外声明：`Adc_Init()` 的入参就是它，
 *        而这个指针由**调用方**（EcuM 或 main）持有。
 *        只把它写在 `Adc.c` 里当 `extern` 的话，任何想初始化 ADC 的
 *        翻译单元都拿不到它 —— 看起来像"配置没编进来"。
 */
extern const Adc_ConfigType Adc_Config;

/**
 * @brief 每组的通道数（下标 = 组号）
 * @note  上层要用定长缓冲区读一组结果时必须知道长度。
 *        不暴露配置结构体（那在 `Adc_Priv.h`，属于模块私有），
 *        只给一个纯数字表 —— 这是 `cfg` 层"只出数据、不出结构"的用法。
 */
extern const uint8_t Adc_Cfg_GroupChannels[ADC_CFG_NUM_GROUPS];
#endif /* _ADC_CFG_H_ */
