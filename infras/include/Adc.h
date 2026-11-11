/**
 * @file    Adc.h
 * @brief   ADC 驱动标准接口（AUTOSAR CP MCAL）
 * @details 依据 `AUTOSAR_CP_SWS_ADCDriver.pdf`（R25-11）。
 *
 *          本文件只声明**标准 API 与类型**，不涉及任何芯片细节：
 *          | 内容 | 归属 |
 *          |------|------|
 *          | 类型、错误码、API 声明 | 本文件 |
 *          | 配置结构体 `Adc_ConfigType` 的实际定义 | `Adc_Priv.h` |
 *          | 寄存器操作 | 平台 `AdcAc.c` |
 *          | 配置数据 | `Adc_Cfg.c` |
 *
 *          这个划分与 as-master 的 `Port.h` / `Port_Priv.h` / `Port.c` /
 *          `PortAc.c` 完全同构 —— 移植时照抄结构，只换平台实现。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：ADC 标准接口子集（组转换 + 通知） |
 */
#ifndef _ADC_H_
#define _ADC_H_
/* ================================ [ INCLUDES  ] ============================================== */
#include "Std_Types.h"
#ifdef __cplusplus
extern "C" {
#endif
/* ================================ [ MACROS    ] ============================================== */
/* @SWS_Adc_00515 ~ 00524：开发错误码 */
#define ADC_E_UNINIT                 0x0A
#define ADC_E_BUSY                   0x0B
#define ADC_E_IDLE                   0x0C
#define ADC_E_ALREADY_INITIALIZED    0x0D
#define ADC_E_PARAM_GROUP            0x0E
#define ADC_E_ILLEGAL_PARAM          0x0F
#define ADC_E_PARAM_POINTER          0x10
#define ADC_E_WRONG_CONV_MODE        0x16
#define ADC_E_WRONG_TRIGG_SRC        0x17
#define ADC_E_NOT_DISENGAGED         0x1A
#define ADC_E_TRANSITION_NOT_POSSIBLE 0x1C

/** @brief 服务 ID（DET 上报用，与 SWS 的 Service ID 一致） */
#define ADC_SID_INIT                 0x00
#define ADC_SID_DEINIT               0x01
#define ADC_SID_START_GROUP_CONV     0x03
#define ADC_SID_STOP_GROUP_CONV      0x04
#define ADC_SID_READ_GROUP           0x05
#define ADC_SID_SETUP_RESULT_BUFFER  0x0D
/* ================================ [ TYPES     ] ============================================== */
/** @brief 配置结构体的实际定义在 `Adc_Priv.h`（与 AS 的 Port 同款前置声明） */
typedef struct Adc_Config_s Adc_ConfigType;

/* @SWS_Adc_00506 */
typedef uint16_t Adc_ChannelType;

/* @SWS_Adc_00507 */
typedef uint16_t Adc_GroupType;

/* @SWS_Adc_00508 */
typedef uint16_t Adc_ValueGroupType;

/* @SWS_Adc_00509 */
typedef uint8_t Adc_StreamNumSampleType;

/* @SWS_Adc_00511 */
typedef uint16_t Adc_SamplingTimeType;

/* @SWS_Adc_00512 */
typedef uint8_t Adc_ResolutionType;

/* @SWS_Adc_00514：0 最低优先级 */
typedef uint8_t Adc_GroupPriorityType;

/**
 * @brief 组转换状态
 * @note  取值必须与 SWS 一致，上层（如 IoHwAb）会按这些值判状态。
 */
typedef enum {
	ADC_IDLE = 0x00,             /**< 未启动，无结果 */
	ADC_BUSY = 0x01,             /**< 转换进行中 */
	ADC_COMPLETED = 0x02,        /**< 一轮转换完成，结果可用 */
	ADC_STREAM_COMPLETED = 0x03, /**< 连续模式下的缓冲区已满 */
} Adc_StatusType;

/* @SWS_Adc_00516 */
typedef enum {
	ADC_TRIGG_SRC_SW = 0x00,     /**< 软件触发（本工程实际经 PDB 转发，见 AdcAc.c） */
	ADC_TRIGG_SRC_HW = 0x01,     /**< 硬件触发（PDB / TRGMUX） */
} Adc_TriggerSourceType;

/* @SWS_Adc_00518 */
typedef enum {
	ADC_CONV_MODE_ONESHOT = 0x00,    /**< 单次：转换一轮后停 */
	ADC_CONV_MODE_CONTINUOUS = 0x01, /**< 连续：自动重复 */
} Adc_GroupConvModeType;

/* @SWS_Adc_00519 */
typedef enum {
	ADC_STREAM_BUFFER_LINEAR = 0x00,  /**< 线性缓冲，满了就停 */
	ADC_STREAM_BUFFER_CIRCULAR = 0x01,/**< 环形缓冲，覆盖最旧 */
} Adc_StreamBufferModeType;

/**
 * @brief 组转换完成通知
 * @param[in] Group 完成的组号
 * @note  由平台层在结果就绪后调用（`AdcAc.c` 里在 COCO 置位后调）。
 *        配置为 NULL 表示该组不要通知。
 */
typedef void (*Adc_NotificationType)(Adc_GroupType Group);
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/**
 * @brief 初始化 ADC 驱动与硬件单元
 * @param[in] ConfigPtr 配置表指针，不能为 NULL
 * @note 重复调用会报 `ADC_E_ALREADY_INITIALIZED`（SWS 要求，不静默放过）。
 */
void Adc_Init(const Adc_ConfigType *ConfigPtr);

/** @brief 反初始化：关闭 ADC 单元并释放内部状态 */
void Adc_DeInit(void);

/**
 * @brief 为组绑定结果缓冲区
 * @param[in]  Group      组号
 * @param[out] BufferPtr  结果缓冲区，长度必须 ≥ 该组的通道数
 * @return E_OK / E_NOT_OK
 * @warning 缓冲区由**调用方**提供并保持有效（AUTOSAR 不做内部拷贝）。
 */
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group,
                                     Adc_ValueGroupType *BufferPtr);

/**
 * @brief 启动一次组转换
 * @param[in] Group 组号
 * @note  软件触发组的实现细节：`CVM014x` 的 SDK **没有**"软触发 ADC"的入口，
 *        必须经 PDB 的 `SWTRIG` 转发（见 `AdcAc.c` 的说明）。
 */
void Adc_StartGroupConversion(Adc_GroupType Group);

/** @brief 停止组转换 */
void Adc_StopGroupConversion(Adc_GroupType Group);

/**
 * @brief 读取组结果到已绑定的缓冲区
 * @param[in] Group 组号
 * @return E_OK 结果已就绪并拷出；E_NOT_OK 尚未完成或未绑定缓冲区
 */
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);

/** @brief 查询组状态 */
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);

/** @brief 使能组转换完成通知 */
void Adc_EnableGroupNotification(Adc_GroupType Group);

/** @brief 关闭组转换完成通知 */
void Adc_DisableGroupNotification(Adc_GroupType Group);

/** @brief 取版本信息 */
void Adc_GetVersionInfo(Std_VersionInfoType *versioninfo);
#ifdef __cplusplus
}
#endif
#endif /* _ADC_H_ */
