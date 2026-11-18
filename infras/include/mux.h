/**
 * @file    mux.h
 * @brief   MuxManager：共享 SelectBus 的模拟开关扫描（RS2260 等）
 *
 * @details @section MUX_WHY 为什么单独一层
 *
 *          RS2260 一类的模拟多路开关由 **A/B/C 三根选择线** 选通，
 *          COM 端按芯片配置接到 MCU 的 GPIO 或 ADC。多片芯片可以共用
 *          同一组 A/B/C —— 这正是它便宜的原因，也是它危险的地方：
 *
 *          - ABC 是**共享资源**，任何时刻只能有一个写入者；
 *          - ADC 转换期间切换 ABC 会毁掉正在进行的采样；
 *          - 不同 COM 类型（GPIO/ADC）必须在同一个选择周期里完成。
 *
 *          这些是**硬件资源调度**问题，不该塞进 IoHwAb Core（它只认逻辑信号），
 *          也不该让每片 MUX 自己抢 ABC。所以单独一个 Manager。
 *
 *          @section MUX_MODEL 模型
 *
 *          @code
 *          SelectBus(ABC) ──┬── MuxDevice0 (COM → GPIO)  ── DIN 采样
 *                           ├── MuxDevice1 (COM → ADC)   ── AIN 采样
 *                           └── MuxDevice2 (COM → GPIO)
 *          @endcode
 *
 *          扫描以 **ABC 值** 为外层循环：一个 ABC 值下，所有属于该总线的
 *          设备同时取样（GPIO 直接读、ADC 启动转换），等 ADC 全部完成后
 *          才允许切到下一个 ABC。
 *
 *          @section MUX_OWNER 归属
 *
 *          | 事项 | 归属 |
 *          |------|------|
 *          | ABC 写入、扫描调度、ADC 等待 | 本模块 |
 *          | COM 的电平读取、ADC 启动/查询/取值 | `Mux_HwOps`（Target 用 Dio/Adc，Host 用模拟） |
 *          | 逻辑电平、消抖、滤波、极性 | IoHwAb Core（本模块只给**电气电平** + 样本序号） |
 *
 *          @section MUX_FRESH 与 IoHwAb 的衔接
 *
 *          每次发布样本 `seq` 加 1；IoHwAb 只在 `seq` 变化时推进消抖/滤波，
 *          所以 MUX 扫描比 10 ms 慢也不会被误判成"有数据"。
 *          扫描停摆（ADC 一直不完成）时 `seq` 不再增长，IoHwAb 自然转 `STALE`。
 *
 *          @section MUX_TODO 尚未确定（需器件手册）
 *
 *          - ABC 建立时间 → `settleTicks`（当前按拍数配置，Host 可设 0）
 *          - INH 的有效电平与是否需要脉冲 → `inhActiveLevel`（当前只做静态使能）
 *          - 通道切换后的稳定误差（模拟开关的 Ron/电荷注入）→ 影响 settle 取值
 *
 * @author  binbina
 * @version V1.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.1.0 | 2026-11-18 | binbina | 首版：SelectBus + 设备表 + 非阻塞扫描状态机 + 样本发布 |
 */

#ifndef MUX_H
#define MUX_H

#include "Std_Types.h"

/** @brief 设备数上限（pending 位图按 32 位算，够用） */
#define MUX_DEV_MAX             (4u)
/** @brief SelectBus 数上限 */
#define MUX_BUS_MAX             (2u)
/** @brief 每片 MUX 的 Y 通道数（1 of 8） */
#define MUX_Y_MAX               (8u)
/** @brief "不使用该引脚/通道" */
#define MUX_NO_CHANNEL          (0xFFu)
/** @brief 单次 MainFunction 内最多推进的状态步数（有界，不阻塞） */
#define MUX_STEPS_PER_TICK      (40u)

/** @brief COM 端类型 */
typedef enum {
	MUX_COM_GPIO = 0,   /**< COM 接 MCU GPIO（Dio） */
	MUX_COM_ADC         /**< COM 接 MCU ADC */
} Mux_ComType;

/** @brief 扫描状态（诊断用） */
typedef enum {
	MUX_STATE_IDLE = 0,     /**< 没有可扫描通道 */
	MUX_STATE_SET_SELECT,   /**< 正在写 A/B/C */
	MUX_STATE_WAIT_SETTLE,  /**< 等待选择线建立 */
	MUX_STATE_START,        /**< 读 GPIO / 启动 ADC */
	MUX_STATE_WAIT_SAMPLE,  /**< 等待 ADC 完成 */
	MUX_STATE_ADVANCE,      /**< 切下一个 ABC */
	MUX_STATE_COUNT
} Mux_StateType;

/** @brief 一组共享的 A/B/C 选择线 */
typedef struct {
	uint8 pinA;             /**< Dio 通道号 */
	uint8 pinB;             /**< Dio 通道号 */
	uint8 pinC;             /**< Dio 通道号 */
	uint8 settleTicks;      /**< 写 ABC 后等待的 10 ms 拍数（0 = 不等） */
	uint8 adcTimeoutTicks;  /**< ADC 完成超时拍数，超时丢弃本拍样本 */
	uint8 scanMask;         /**< 需要扫描的 ABC 位图（生成期由通道引用算出） */
} Mux_BusCfgType;

/** @brief 一片 MUX */
typedef struct {
	uint8  bus;             /**< 所属 SelectBus 索引 */
	uint8  comType;         /**< `Mux_ComType` */
	uint16 comChannel;      /**< GPIO：Dio 通道号；ADC：(group << 8) | channel */
	uint8  inhChannel;      /**< INH 的 Dio 通道号；`MUX_NO_CHANNEL` = 无 */
	uint8  inhActiveLevel;  /**< INH 有效电平（1 = 高有效） */
	uint8  activeMask;      /**< 实际使用的 Y 通道位图 */
} Mux_DeviceCfgType;

/**
 * @brief 硬件访问表（Target 用 Dio/Adc 实现，Host 用模拟实现）
 * @note  只收发**电气电平**与原始 ADC 值；逻辑转换不在这里。
 */
typedef struct {
	/** @brief 写 A/B/C（abc 的 bit0/1/2 = A/B/C） */
	void (*SelectWrite)(uint8 bus, uint8 abc);
	/** @brief 写 INH（可为 NULL = 本工程不用 INH） */
	void (*InhWrite)(uint8 ch, uint8 level);
	/** @brief 读 GPIO 电气电平 */
	Std_ReturnType (*GpioRead)(uint16 ch, boolean *level);
	/** @brief 启动一次 ADC 转换（通道编码 group<<8|ch） */
	Std_ReturnType (*AdcStart)(uint16 ch);
	/** @brief 查询转换是否完成 */
	Std_ReturnType (*AdcReady)(uint16 ch, boolean *ready);
	/** @brief 取本次转换结果（不重新触发转换） */
	Std_ReturnType (*AdcRead)(uint16 ch, uint16 *raw);
} Mux_HwOpsType;

/* 生成表与计数（Target/Host 各提供一份定义） */
extern const Mux_BusCfgType    Mux_BusCfgs[];
extern const Mux_DeviceCfgType Mux_DeviceCfgs[];
extern const uint8             Mux_BusCount;
extern const uint8             Mux_DeviceCount;
extern const Mux_HwOpsType     Mux_HwOps;

/** @brief 初始化：清样本、置 IDLE、写 INH 使能 */
void Mux_Init(void);

/**
 * @brief 扫描推进（10 ms 调用）
 * @note  单次调用最多推进 `MUX_STEPS_PER_TICK` 步，遇到等待立即返回 ——
 *        **不阻塞**，不在这里死等 ADC。
 */
void Mux_MainFunction(void);

/**
 * @brief 取数字通道样本（电气电平）
 * @param[in]  dev   设备索引
 * @param[in]  y     Y 通道（0..7）
 * @param[out] level 电气电平
 * @param[out] seq   样本序号（每次发布 +1）
 * @return E_OK；未采样过 / 通道未启用 / 参数越界 → E_NOT_OK
 */
Std_ReturnType Mux_GetDin(uint8 dev, uint8 y, boolean *level, uint16 *seq);

/**
 * @brief 取模拟通道样本（原始 ADC 值）
 * @param[in]  dev 设备索引
 * @param[in]  y   Y 通道
 * @param[out] raw 原始值
 * @param[out] seq 样本序号
 * @return E_OK；未采样过 / 通道未启用 / 参数越界 → E_NOT_OK
 */
Std_ReturnType Mux_GetAin(uint8 dev, uint8 y, uint16 *raw, uint16 *seq);

/** @brief 当前扫描状态（诊断） */
Mux_StateType Mux_GetState(void);

/** @brief 当前 ABC 值（诊断） */
uint8 Mux_GetAbc(void);

/** @brief 已完成的扫描轮数（诊断；每扫完一遍 ABC 全表 +1） */
uint32 Mux_GetScanRounds(void);

/**
 * @brief ADC 超时累计次数（诊断）
 * @note  单个设备一次超时 +1；用于判断扫描是否被某个器件拖住
 */
uint32 Mux_GetAdcTimeouts(void);

#endif /* MUX_H */
