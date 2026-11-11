/**
 * @file    Pwm_Cfg.h
 * @brief   PWM 通道号定义与配置规模
 * @details 通道号是**配置表的下标**，与物理引脚没有固定关系 ——
 *          引脚由 `PwmAc.c` 的 pad 映射表决定。
 *
 *          业务层只引用这里的 `PWM_CFG_CH_*` 宏，不直接写数字：
 *          将来换引脚方案或增加通道时，改配置表与这里即可，
 *          业务代码不用动。
 *
 * @author  binbina
 * @version V1.0.0
 * @date    2026-11-11
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：顶灯渐亮 + 3 路验证通道 |
 */

#ifndef _PWM_CFG_H_
#define _PWM_CFG_H_

/* ============================ [ 通道号 ] ============================ */

/**
 * @brief 顶灯（内室灯）—— 渐亮/渐灭
 * @note  依据《福田 L1 平台 24V IDM 功能规范》IL001/IL002：
 *        **PWM 频率 100 Hz**，占空比 20% → 90% 线性变化，历时 2.5 s ±0.1 s，
 *        最后跳到 100%。渐灭反向。
 * @note  渐变的**时间轴由业务层负责**（每 20 ms 改一次占空比，
 *        2.5 s / 20 ms = 125 步，20%→90% 共 70% 需要 87.5 个 LSB 步进），
 *        本模块只提供"设占空比"。
 */
#define PWM_CFG_CH_DOME_LAMP        (0u)

/** @brief 验证通道 1（PTD1），固定 50% 占空比 */
#define PWM_CFG_CH_TEST1            (1u)

/** @brief 验证通道 2（PTE15），固定 25% 占空比 */
#define PWM_CFG_CH_TEST2            (2u)

/** @brief 验证通道 3（PTE16），固定 75% 占空比 */
#define PWM_CFG_CH_TEST3            (3u)

/** @brief 通道总数（配表时用于自检，少写一条会编译不过） */
#define PWM_CFG_NUM_CHANNELS        (4u)

/* ============================ [ 全局实例 ] ============================ */

/**
 * @brief 驱动初始化用的唯一配置实例（定义在 `Pwm_Cfg.c`）
 * @note  `EcuM_Cfg.c` 的初始化表要用它的地址作为表项的 `config` 字段，
 *        所以这里必须导出声明。
 */
extern const Pwm_ConfigType Pwm_Config;

#endif /* _PWM_CFG_H_ */
