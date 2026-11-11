/**
 * @file    Pwm.h
 * @brief   PWM 驱动（PWM Driver）的 AUTOSAR 标准接口
 * @details 依据 AUTOSAR CP R25-11 `SWS_PWMDriver`（65 页）实现。
 *
 *          @section PWM_SCOPE 本模块的范围
 *          只提供"软件设定占空比 → 硬件输出波形"这一条能力。**不包含**：
 *          - 输入捕获（测频率/占空比）—— 那是 `Icu` 的职责
 *          - 输出比较单脉冲 —— 那是 `Gpt`/`Ocu` 的职责
 *          - 全桥/半桥的互补与死区 —— 那要靠 `Mft` 的 PWM 模式，
 *            本模块只做单路独立输出
 *
 *          @section PWM_DUTY 占空比的表示（最容易用错的地方）
 *          标准接口的占空比范围是 **0x0000 ~ 0x8000**，不是 0~100、也不是 0~1000：
 *
 *          | 传入值 | 含义 |
 *          |--------|------|
 *          | `0x0000` | 0 % |
 *          | `0x4000` | 50 % |
 *          | `0x8000` | 100 % |
 *
 *          换算：`percent = (uint32)DutyCycle * 100u / 0x8000u`
 *
 *          @warning 按 `[SWS_Pwm_00014]`，**0 % 与 100 % 必须输出静态电平**，
 *          不是"极窄的脉冲"。驱动内部要专门处理这两个边界，否则示波器上会看到
 *          一个尖峰 —— 而 `[SWS_Pwm_00018]` 明确要求"禁止 PWM 输出上的尖峰"。
 *
 * @author  binbina
 * @version V1.0.0
 * @date    2026-11-11
 *
 * @note    修改记录：
 *          | 版本   | 日期       | 作者    | 说明 |
 *          |--------|------------|---------|------|
 *          | V1.0.0 | 2026-11-11 | binbina | 首版：Init/DeInit/SetDutyCycle/SetPeriodAndDuty/SetOutputToIdle/GetOutputState |
 */

#ifndef _PWM_H_
#define _PWM_H_

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 错误码 ] ============================ */

/** @brief 初始化时参数错误（`[SWS_Pwm_00044]`） */
#define PWM_E_INIT_FAILED                0x10
/** @brief 模块未初始化就调用服务（`[SWS_Pwm_00045]`） */
#define PWM_E_UNINIT                     0x11
/** @brief 通道号非法（`[SWS_Pwm_00046]`） */
#define PWM_E_PARAM_CHANNEL              0x12
/** @brief 该通道的周期不可在运行期修改（`[SWS_Pwm_00047]`） */
#define PWM_E_PERIOD_UNCHANGEABLE        0x13
/** @brief 重复初始化（`[SWS_Pwm_00048]`） */
#define PWM_E_ALREADY_INITIALIZED        0x14
/** @brief 传入的指针为 NULL（`[SWS_Pwm_00049]`） */
#define PWM_E_PARAM_POINTER              0x15
/** @brief 上一次电源状态切换尚未完成（`[SWS_Pwm_00173]`） */
#define PWM_E_NOT_DISENGAGED             0x16
/** @brief 不支持请求的电源状态（`[SWS_Pwm_00174]`） */
#define PWM_E_POWER_STATE_NOT_SUPPORTED  0x17
/** @brief 电源状态切换非法（`[SWS_Pwm_00175]`） */
#define PWM_E_TRANSITION_NOT_POSSIBLE    0x18
/** @brief 外设未准备好（`[SWS_Pwm_00176]`） */
#define PWM_E_PERIPHERAL_NOT_PREPARED    0x19

/* ============================ [ 服务 ID ] ============================ */
/** @brief `Pwm_Init` 的服务 ID（`[SWS_Pwm_91002]`） */
#define PWM_SID_INIT                     0x00
/** @brief `Pwm_DeInit` 的服务 ID */
#define PWM_SID_DEINIT                   0x01
/** @brief `Pwm_SetDutyCycle` 的服务 ID */
#define PWM_SID_SET_DUTY_CYCLE           0x02
/** @brief `Pwm_SetPeriodAndDuty` 的服务 ID */
#define PWM_SID_SET_PERIOD_AND_DUTY      0x03
/** @brief `Pwm_SetOutputToIdle` 的服务 ID */
#define PWM_SID_SET_OUTPUT_TO_IDLE       0x04
/** @brief `Pwm_GetOutputState` 的服务 ID */
#define PWM_SID_GET_OUTPUT_STATE         0x05
/** @brief `Pwm_DisableNotification` 的服务 ID */
#define PWM_SID_DISABLE_NOTIFICATION     0x06
/** @brief `Pwm_EnableNotification` 的服务 ID */
#define PWM_SID_ENABLE_NOTIFICATION      0x07
/** @brief `Pwm_GetVersionInfo` 的服务 ID */
#define PWM_SID_GET_VERSION_INFO         0x08

/* ============================ [ 类型 ] ============================ */

/** @brief 配置实例的前置声明（由平台层 `Pwm_Cfg.c` 定义） */
typedef struct Pwm_Config_s Pwm_ConfigType;

/** @brief 通道号（0 ~ 通道数-1，与 `Pwm_Cfg.c` 的表顺序一一对应） */
typedef uint16_t Pwm_ChannelType;

/**
 * @brief 周期类型
 * @note  **必须是 32 位**。周期是"以定时器计数为单位"的值：
 *        `period = 定时器时钟 / PWM 频率`。40 MHz / 100 Hz = **400000**，
 *        远超 `uint16` 的 65535。用 16 位会在低频通道上静默溢出，
 *        表现是"设 100 Hz 出来是 610 Hz"（400000 & 0xFFFF = 6784）。
 */
typedef uint32_t Pwm_PeriodType;

/** @brief 占空比（0x0000 ~ 0x8000，0x8000 = 100%） */
typedef uint16_t Pwm_DutyCycleType;

/**
 * @brief 输出电平状态
 * @note  用于 `Pwm_GetOutputState()` 与 `Pwm_SetOutputToIdle()` 的语义描述。
 *        注意它是"当前电平"，不是"占空比"——占空比 50% 时读到哪个值
 *        取决于读的瞬间。
 */
typedef enum {
	PWM_LOW  = 0,  /**< 低电平 */
	PWM_HIGH = 1,  /**< 高电平 */
} Pwm_OutputStateType;

/** @brief 边沿通知类型 */
typedef enum {
	PWM_RISING_EDGE  = 0,  /**< 上升沿 */
	PWM_FALLING_EDGE = 1,  /**< 下降沿 */
	PWM_BOTH_EDGES   = 2,  /**< 双沿 */
} Pwm_EdgeNotificationType;

/** @brief 通道类别 */
typedef enum {
	PWM_FIXED_PERIOD         = 0,  /**< 周期固定，只改占空比 */
	PWM_VARIABLE_PERIOD      = 1,  /**< 周期可改（`Pwm_SetPeriodAndDuty`） */
	PWM_FIXED_PERIOD_SHIFTED = 2,  /**< 固定周期、相位可移（本工程未实现） */
} Pwm_ClassType;

/* ============================ [ API ] ============================ */

/**
 * @brief 初始化 PWM 驱动
 *
 * @details 由 `EcuM` 的 `DriverInitOne` 表调用。做四件事：
 *          1. 打开各 PwmLite 实例的时钟门控与对应端口的时钟
 *          2. 按配置切换引脚的复用功能
 *          3. 配置模块周期与同步方式
 *          4. 按配置给每个通道设初始占空比并使能
 *
 * @param[in] ConfigPtr 配置表指针，不能为 NULL
 *
 * @note 会校验每个实例内所有通道的**周期是否一致**：PwmLite 的周期是
 *       **模块级**（`PwmLiteDrv_ModuleConfig`），不是通道级。同一个实例里
 *       两个通道要不同频率，硬件上做不到，所以 `Init` 阶段直接拒绝并打印，
 *       而不是等到运行期波形不对再查。
 *
 * @warning 未调用本函数就调用其它服务，会通过 `Det_ReportError` 报
 *          `PWM_E_UNINIT`。本工程的 `Det` 只记录不 halt。
 */
void Pwm_Init(const Pwm_ConfigType *ConfigPtr);

/**
 * @brief 反初始化：所有通道输出恢复到空闲电平，并关闭模块
 * @note 空闲电平由配置的 `idleState` 决定（安全侧默认低电平）。
 */
void Pwm_DeInit(void);

/**
 * @brief 设置通道占空比
 *
 * @param[in] ChannelNumber 通道号
 * @param[in] DutyCycle     占空比，0x0000 ~ 0x8000（0x8000 = 100%）
 *
 * @note  超出 0x8000 会被钳到 0x8000，不报错 —— 与 `Adc` 的"超范围钳位"
 *        保持一致的处理风格。
 * @note  按 `[SWS_Pwm_00017]`，占空比在**周期末**生效，避免波形被切出毛刺。
 *        PwmLite 的 `PwmLiteDrv_UpdatePwmThresholdAtSync` 正是这个语义。
 *
 * @warning 0% 与 100% 走**静态电平**分支，不配置阈值。若用阈值实现，
 *          `threshold1 = 0` 会让"周期开始拉高"和"立即拉低"在同一时刻发生，
 *          输出一个纳秒级尖峰 —— 规范和硬件都不允许。
 */
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, Pwm_DutyCycleType DutyCycle);

/**
 * @brief 同时设置周期与占空比
 *
 * @param[in] ChannelNumber 通道号
 * @param[in] Period        周期（定时器计数单位）
 * @param[in] DutyCycle     占空比，0x0000 ~ 0x8000
 *
 * @note  只有配置为 `PWM_VARIABLE_PERIOD` 的通道允许调用；否则报
 *        `PWM_E_PERIOD_UNCHANGEABLE`。
 * @note  周期是模块级的，改一个通道的周期会**同时影响同实例的所有通道**。
 *        这一约束在 `Pwm_Init` 里已经强制"同实例周期一致"，所以运行期改
 *        周期时同实例的其它通道也一起变 —— 这是硬件限制，不是实现缺陷。
 */
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber,
                          Pwm_PeriodType Period,
                          Pwm_DutyCycleType DutyCycle);

/**
 * @brief 把通道输出设为空闲电平
 * @param[in] ChannelNumber 通道号
 * @note  空闲电平来自配置的 `idleState`。用于故障时把输出拉到安全状态
 *        （例如灯类负载断电、电机类负载停转）。
 */
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);

/**
 * @brief 读取通道当前输出电平
 * @param[in] ChannelNumber 通道号
 * @return 当前电平
 * @retval PWM_HIGH 高电平
 * @retval PWM_LOW  低电平（含通道号非法、模块未初始化等异常路径）
 * @note  读的是**引脚当前电平**，不是占空比。占空比 50% 时连续调用会
 *        得到交替结果，这是正常的。
 */
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);

/**
 * @brief 使能通道的边沿通知
 * @param[in] ChannelNumber 通道号
 * @param[in] Edge          要通知的边沿
 * @note  本工程未实现硬件边沿中断（BCM 没有"必须在 PWM 边沿做动作"的场景），
 *        函数体为空。保留接口是为了与标准一致，将来要用时不必改头文件。
 */
void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber,
                            Pwm_EdgeNotificationType Edge);

/**
 * @brief 关闭通道的边沿通知
 * @param[in] ChannelNumber 通道号
 */
void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);

/* ============================ [ 工程扩展 ] ============================ */

/**
 * @brief 把频率换算成 `Pwm_SetPeriodAndDuty()` 需要的周期计数
 *
 * @param[in] frequencyHz 目标频率（Hz），必须 > 0
 * @return 周期计数（定时器时钟 / 频率）；参数为 0 时返回 0
 *
 * @note  **非标准 API。** AUTOSAR 的 `Pwm_SetPeriodAndDuty()` 要求传"周期计数"，
 *        但业务层想的是"我要 200 Hz"。没有这个换算函数，每个调用点都要自己
 *        知道 APB 时钟是多少，那是把平台知识泄漏到业务层。
 *
 * @note  配置表 `Pwm_ChannelConfigType.frequencyHz` 用的是 Hz，平台层内部换算；
 *        只有运行期改周期（`Pwm_SetPeriodAndDuty`）才需要显式调本函数。
 *
 * @par 示例
 * @code
 * // 把通道 1 改成 200 Hz、50% 占空比
 * Pwm_SetPeriodAndDuty(1u, Pwm_CalcPeriod(200u), 0x4000u);
 * @endcode
 */
Pwm_PeriodType Pwm_CalcPeriod(uint32_t frequencyHz);

/**
 * @brief 查询模块是否已初始化成功
 * @return 已初始化返回 TRUE，否则 FALSE
 *
 * @note  **非标准 API。** 标准里没有"查初始化状态"的服务，因为正常系统不需要 ——
 *        初始化失败就应该停机。但本工程在调试阶段要用它区分两种情况：
 *
 *        | 现象 | `Pwm_IsInitialized()` | 含义 |
 *        |------|----------------------|------|
 *        | 波形的占空比不跟着变 | FALSE | `Pwm_Init()` 被拒（周期冲突/配置非法） |
 *        | 同上 | TRUE | 配置写进去了但硬件没输出（时钟/引脚复用/硬件问题） |
 *
 *        这两种情况的排查方向完全不同，靠"看波形"分不开。
 */
boolean Pwm_IsInitialized(void);

/**
 * @brief 读取模块版本信息
 * @param[out] versioninfo 版本信息输出
 */
void Pwm_GetVersionInfo(Std_VersionInfoType *versioninfo);

#ifdef __cplusplus
}
#endif

#endif /* _PWM_H_ */
