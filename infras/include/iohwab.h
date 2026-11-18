/**
 * @file    iohwab.h
 * @brief   IoHwAb：ECU 逻辑 IO 抽象（V1.0.1）
 *
 * @details @section IOHWAB_WHY 为什么需要这一层
 *
 *          应用组件（灯光/雨刮/门锁）只应看到"某个逻辑通道是高还是低、
 *          电压多少"，不应该知道它接在 MCU 的哪个引脚、经过哪颗扩展芯片。
 *          本层把这条边界钉死：
 *
 *          @code
 *          业务组件
 *              ↓ 只 include 本文件 + IoHwAb_Cfg.h（拿通道名）
 *          IoHwAb Core —— 逻辑值、消抖、滤波、安全状态、极性
 *              ↓ 能力 ops 表（编译期 const，无动态注册）
 *          Capability Adapter —— GPIO / ADC / PWM / 未来的 HSD、LSD、MUX
 *              ↓
 *          HAL（Dio / Adc / Pwm）
 *          @endcode
 *
 *          @section IOHWAB_OWNER 四条归属约定（V1.0.1 收敛，不得再两头都做）
 *
 *          | 事项 | 归属 | 理由 |
 *          |------|------|------|
 *          | **极性**（高有效/低有效） | **Core** | 表项带 `activeLevel`，Core 负责逻辑↔电气双向转换；Adapter 只收发**电气电平**，**禁止二次取反** |
 *          | 消抖、滤波、有效性、样本新鲜度 | 本层 | 与芯片无关，属于信号质量 |
 *          | 采样时序（何时读一次总线/ADC） | 异步设备自己的 Manager | 例如 RS2260 的 ABC 扫描，见 V2.0 架构 §7 |
 *          | 开短路/过流诊断 | V1.1 的器件驱动 | 依赖具体器件能力，本层只保留状态位 |
 *
 *          @section IOHWAB_FRESH 样本新鲜度（V1.0.1 新增，V1.1 的前置）
 *
 *          输入能力返回**样本序号 `seq`**：后端每产生一个新样本就 +1
 *          （允许 16 位回绕）。Core 只在 `seq` 变化时推进消抖/滤波；
 *          `seq` 连续不变超过通道的 `staleTicks` 判 `STALE`。
 *
 *          这样 MUX / I2C 扩展器这类"不是每 10 ms 都有新数据"的后端
 *          不会被反复消抖同一个旧样本，超时也不会被错误刷新。
 *
 *          @section IOHWAB_STATUS 数据有效性
 *          `E_OK` 只代表"调用合法"，**不代表数据可用**。应用必须同时看
 *          `IoHwAb_StatusType`：`NEVER`（还没有样本）、`STALE`（超时）、
 *          `ERROR`（后端失败）都不可用。
 *
 * @author  binbina
 * @version V1.0.1
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-18 | binbina | 首版：DIN/AIN/DOUT/PWM 四类逻辑通道 + 能力 ops 表 |
 * | V1.0.1 | 2026-11-18 | binbina | 极性归属收敛到 Core；输入 ops 增加样本序号 `seq`；Init 增加运行期守卫并拆出 ReInit；SetAllSafe 返回结果并可按通道查故障；DIN 增加 staleTicks |
 */

#ifndef IOHWAB_H
#define IOHWAB_H

#include "Std_Types.h"

/**
 * @brief 逻辑通道 ID
 * @note  具体取值与枚举名在 `IoHwAb_Cfg.h`（由 Board.json 生成）。
 *        这里用裸类型，避免通用接口头反过来依赖项目生成物。
 */
typedef uint16 IoHwAb_DinId;
typedef uint16 IoHwAb_AinId;
typedef uint16 IoHwAb_DoutId;
typedef uint16 IoHwAb_PwmId;

/** @brief 逻辑电平（已消抖/已去极性） */
typedef enum {
	IOHWAB_LEVEL_LOW = 0,   /**< 逻辑 0 */
	IOHWAB_LEVEL_HIGH = 1   /**< 逻辑 1 */
} IoHwAb_LevelType;

/** @brief 数据有效性（四态，语义与 BcmSig 同源） */
typedef enum {
	IOHWAB_STATUS_NEVER = 0,  /**< 尚未取得有效样本 */
	IOHWAB_STATUS_VALID,      /**< 当前样本有效 */
	IOHWAB_STATUS_STALE,      /**< 样本超时（曾经有效） */
	IOHWAB_STATUS_ERROR       /**< 后端采样/通信失败 */
} IoHwAb_StatusType;

/** @brief 通道来源（生成期决定，运行期只读） */
typedef enum {
	IOHWAB_SOURCE_DIRECT = 0, /**< MCU 直连（GPIO/ADC/PWM） */
	IOHWAB_SOURCE_HOST        /**< Host 模拟（Target 构建下为不可用桩） */
} IoHwAb_SourceType;

/* ============================ [ 能力 ops 表 ] ============================ */
/*
 * 按能力拆表，不做一个"什么都能干"的巨型结构。
 * 每个能力只声明自己真正需要的操作；不支持的操作为 NULL，
 * 上层必须据此返回 E_NOT_OK —— **不允许伪造正常值**。
 *
 * 极性：Adapter 只收发**电气电平**，逻辑↔电气的转换由 Core 统一完成。
 *       新增 HSD/LSD/Relay 适配时**不要**再按 activeLevel 取反一次。
 */

/** @brief 数字输入能力 */
typedef struct {
	/**
	 * @brief 读取电气电平
	 * @param[in]  channel 物理通道
	 * @param[out] level   电气电平（TRUE = 高）
	 * @param[out] seq     样本序号：每产生一个新样本 +1（可回绕）
	 * @return E_OK 读取成功；E_NOT_OK 失败（不得返回旧值充数）
	 */
	Std_ReturnType (*Read)(uint16 channel, boolean *level, uint16 *seq);
} IoHwAb_DinOpsType;

/** @brief 模拟输入能力 */
typedef struct {
	/**
	 * @brief 读取原始 ADC 值（未换算、未滤波）
	 * @param[in]  channel 物理通道
	 * @param[out] raw     原始值
	 * @param[out] seq     样本序号：**仅在转换真正完成时** +1
	 * @return E_OK / E_NOT_OK
	 * @note  直接读 ADC 组的实现必须用"取上次转换结果"的接口，
	 *        不能在本函数里重新启动转换（会打乱 MUX 的 ABC 时序）。
	 */
	Std_ReturnType (*ReadRaw)(uint16 channel, uint16 *raw, uint16 *seq);
} IoHwAb_AinOpsType;

/** @brief 数字输出能力 */
typedef struct {
	/** @brief 写电气电平（极性由 Core 在调用前应用） */
	Std_ReturnType (*Write)(uint16 channel, boolean level);
	/** @brief 回读电气电平；不支持时为 NULL */
	Std_ReturnType (*Read)(uint16 channel, boolean *level);
} IoHwAb_DoutOpsType;

/** @brief PWM 输出能力 */
typedef struct {
	/** @brief 设置占空比，0..IOHWAB_PWM_FULL */
	Std_ReturnType (*SetDuty)(uint16 channel, uint16 duty);
} IoHwAb_PwmOpsType;

/* 生成表引用的 ops 实例：Target 与 Host 各实现一份，链接期二选一 */
extern const IoHwAb_DinOpsType IoHwAb_GpioDinOps;   /**< MCU 直连数字输入 */
extern const IoHwAb_DinOpsType IoHwAb_HostDinOps;   /**< Host 模拟输入 */
extern const IoHwAb_AinOpsType IoHwAb_AdcOps;       /**< MCU ADC */
extern const IoHwAb_AinOpsType IoHwAb_HostAinOps;   /**< Host 模拟 ADC */
extern const IoHwAb_DoutOpsType IoHwAb_GpioDoutOps; /**< MCU 直连输出 */
extern const IoHwAb_DoutOpsType IoHwAb_HostDoutOps; /**< Host 模拟输出 */
extern const IoHwAb_PwmOpsType IoHwAb_PwmOps;       /**< MCU PWM */
extern const IoHwAb_PwmOpsType IoHwAb_HostPwmOps;   /**< Host 模拟 PWM */

/** @brief PWM 满占空比（万分之一） */
#define IOHWAB_PWM_FULL                 (10000u)

/* ============================ [ 配置表类型 ] ============================ */
/*
 * 由 `tools/generator/IoHwAb.py` 生成的静态 const 表使用。
 * `activeLevel` 用 0/1 而不是枚举，是为了让生成物与 Board.json 的
 * "HIGH"/"LOW" 字符串一眼对得上。
 */

/** @brief 数字输入表项 */
typedef struct {
	IoHwAb_SourceType source;            /**< 来源 */
	const IoHwAb_DinOpsType *ops;        /**< 能力实现（编译期选定） */
	uint16 channel;                      /**< 物理通道号 */
	uint8  activeLevel;                  /**< 1 = 高有效，0 = 低有效 */
	uint16 debounceTicks;                /**< 消抖拍数（10 ms/拍） */
	uint16 staleTicks;                   /**< 超过该拍数无新样本判 STALE */
} IoHwAb_DinCfgType;

/** @brief 模拟输入表项 */
typedef struct {
	IoHwAb_SourceType source;            /**< 来源 */
	const IoHwAb_AinOpsType *ops;        /**< 能力实现 */
	uint16 group;                        /**< ADC 组（直连时有效） */
	uint16 channel;                      /**< ADC 通道 */
	uint8  filterShift;                  /**< 一阶滤波右移位数，0 = 不滤 */
	sint32 factor;                       /**< 物理量系数（千分之一） */
	sint32 offset;                       /**< 物理量偏移 */
	uint16 staleTicks;                   /**< 超过该拍数无新样本判 STALE */
} IoHwAb_AinCfgType;

/** @brief 数字输出表项 */
typedef struct {
	IoHwAb_SourceType source;            /**< 来源 */
	const IoHwAb_DoutOpsType *ops;       /**< 能力实现 */
	uint16 channel;                      /**< 物理通道号 */
	uint8  activeLevel;                  /**< 1 = 高有效，0 = 低有效 */
	uint8  safeLevel;                    /**< 安全状态的逻辑值 */
} IoHwAb_DoutCfgType;

/** @brief PWM 输出表项 */
typedef struct {
	IoHwAb_SourceType source;            /**< 来源 */
	const IoHwAb_PwmOpsType *ops;        /**< 能力实现 */
	uint16 channel;                      /**< PWM 通道号 */
	uint16 safeDuty;                     /**< 安全占空比 */
} IoHwAb_PwmCfgType;

/* 生成表与计数（定义在 IoHwAb_Cfg.c）；用不完整数组，避免头文件依赖计数宏 */
extern const IoHwAb_DinCfgType  IoHwAb_DinCfgs[];
extern const IoHwAb_AinCfgType  IoHwAb_AinCfgs[];
extern const IoHwAb_DoutCfgType IoHwAb_DoutCfgs[];
extern const IoHwAb_PwmCfgType  IoHwAb_PwmCfgs[];

/* ============================ [ API：生命周期 ] ============================ */

/**
 * @brief 首次初始化：清空消抖/滤波上下文，并把所有输出置安全状态
 * @return E_OK 初始化完成（含安全状态全部写成功）；E_NOT_OK 部分输出写失败
 * @note  **运行期重复调用是空操作**（不清状态、不动输出），返回 E_OK。
 *        这是 V1.0.1 的行为变更：V1.0.0 每次调用都会把输出拉回安全值，
 *        车辆运行中若有代码重复调用 Init，会意外关灯。
 * @note  需要"重新初始化"语义时用 IoHwAb_ReInit()，且只能由 EcuM /
 *        诊断复位等明确的生命周期节点调用。
 */
Std_ReturnType IoHwAb_Init(void);

/**
 * @brief 显式重新初始化：清状态 + 输出回安全状态
 * @return 同 IoHwAb_Init()
 * @warning 会丢弃消抖/滤波上下文并把负载拉回安全值。**禁止**在正常
 *          运行路径里调用；只用于初始化失败重试、诊断例程等场景。
 */
Std_ReturnType IoHwAb_ReInit(void);

/**
 * @brief 是否已完成首次初始化
 * @return TRUE / FALSE
 */
boolean IoHwAb_IsInitialized(void);

/**
 * @brief 10 ms 周期任务：DIN 消抖、AIN 滤波与超时判定
 * @note  读接口不直接访问硬件，只取这里维护的缓存
 * @note  只在后端返回**新样本**（`seq` 变化）时推进消抖/滤波
 */
void IoHwAb_MainFunction(void);

/* ============================ [ API：输入 ] ============================ */

/**
 * @brief 读取数字输入（消抖后）
 * @param[in]  id     逻辑通道
 * @param[out] value  逻辑电平
 * @param[out] status 数据有效性（可为 NULL）
 * @return E_OK 参数合法且读取成功；E_NOT_OK 越界或后端失败
 */
Std_ReturnType IoHwAb_DinRead(IoHwAb_DinId id, boolean *value,
                              IoHwAb_StatusType *status);

/**
 * @brief 读取模拟输入原始值（已滤波）
 * @param[in]  id     逻辑通道
 * @param[out] value  原始 ADC 值
 * @param[out] status 数据有效性（可为 NULL）
 * @return E_OK / E_NOT_OK
 * @note  status 为 `STALE` 时仍返回最后一个有效值，由调用方决定是否使用
 */
Std_ReturnType IoHwAb_AinReadRaw(IoHwAb_AinId id, uint16 *value,
                                 IoHwAb_StatusType *status);

/**
 * @brief 读取模拟输入物理量（定点：raw×factor/1000 + offset）
 * @param[in]  id     逻辑通道
 * @param[out] value  物理量（定点，乘以 1000 的整数表示）
 * @param[out] status 数据有效性（可为 NULL）
 * @return E_OK / E_NOT_OK
 * @note  中间计算用 `int64_t`（Std_Types 未提供 sint64）；超出 `sint32`
 *        范围时**饱和**到 INT32_MIN/MAX，
 *        不返回错误（与"限幅到量程"语义一致），需要区分截断时用原始值判断。
 * @note  除法朝零取整（C 语言整数除法语义），负因子时同样成立。
 */
Std_ReturnType IoHwAb_AinReadPhys(IoHwAb_AinId id, sint32 *value,
                                  IoHwAb_StatusType *status);

/* ============================ [ API：输出 ] ============================ */

/**
 * @brief 写数字输出（逻辑值，极性由 Core 应用）
 * @param[in] id 逻辑通道
 * @param[in] on 逻辑状态
 * @return E_OK / E_NOT_OK（越界、后端失败、本构建不适用）
 * @note  后端真实写失败时该通道故障位置位，可用 IoHwAb_DoutGetFault() 查询；
 *        `ops` 为 NULL（本构建不适用）时返回 `E_NOT_OK` 但不置故障位
 */
Std_ReturnType IoHwAb_DoutWrite(IoHwAb_DoutId id, boolean on);

/**
 * @brief 回读数字输出（用于"写后确认"）
 * @param[in]  id 逻辑通道
 * @param[out] on 逻辑状态
 * @return E_OK；后端不支持回读时返回 E_NOT_OK（不伪造）
 */
Std_ReturnType IoHwAb_DoutReadBack(IoHwAb_DoutId id, boolean *on);

/**
 * @brief 查询某路输出最近一次写入是否失败
 * @param[in]  id      逻辑通道
 * @param[out] faulted TRUE = 最近一次写失败（或从未成功）
 * @return E_OK / E_NOT_OK（越界）
 * @note  ops 为 NULL 的通道表示"该能力在本构建不适用"（如 Target 上的
 *        Host 桩、Host 上的 GPIO 桩），此时写接口返回 `E_NOT_OK` 但
 *        **不置故障位** —— "不适用"不是"坏了"，故障位只反映真实写失败。
 */
Std_ReturnType IoHwAb_DoutGetFault(IoHwAb_DoutId id, boolean *faulted);

/**
 * @brief 设置 PWM 占空比
 * @param[in] id  逻辑通道
 * @param[in] duty 0..IOHWAB_PWM_FULL
 * @return E_OK / E_NOT_OK（越界、后端失败）
 */
Std_ReturnType IoHwAb_PwmSetDuty(IoHwAb_PwmId id, uint16 duty);

/**
 * @brief 所有输出回到配置的安全状态
 * @return E_OK 全部适用通道写成功；E_NOT_OK 至少一路**真实写失败**
 * @note  ops 为 NULL 的通道（本构建不适用）直接跳过，不计入失败 ——
 *        否则 Target 上的 Host 桩会让 `io safe` 永远报错，反而淹没真实故障。
 * @note  只保证"软件已下发安全值"，不保证硬件已进入安全状态；
 *        关键负载仍需硬件失效安全措施（默认电平、上拉/下拉、驱动使能）
 */
Std_ReturnType IoHwAb_SetAllSafe(void);

#endif /* IOHWAB_H */
