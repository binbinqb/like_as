/**
 * @file    rte.h
 * @brief   最小 RTE 运行时：业务组件与信号绑定层之间的**唯一**接口
 *
 * @details @section RTE_WHY 为什么需要这一层
 *
 *          现在 `bcm_biz.c` 直接调 `BcmSig_RxRead()` / `BcmSig_TxSet()`。
 *          这有两个问题：
 *
 *          | 问题 | 后果 |
 *          |------|------|
 *          | 业务看得到 `Bcm_SwStateType`、`Bcm_SigValidityType` | 换一种信号类型（数值、枚举），业务跟着改 |
 *          | 有效性靠"两个返回值"（值 + 四态）表达 | 每处调用都要自己处理 `if (v == VALID)`，漏一次就读到脏值 |
 *
 *          RTE 把这两件事收成 AUTOSAR 的形状：
 *
 *          ```c
 *          Rte_SwitchType on;
 *          if (RTE_E_OK == Rte_Read_ParkBrake(&on)) { ... }
 *          ```
 *
 *          值从指针里出，**有效性从返回值出**。业务不再接触 Com / CanIf /
 *          绑定的枚举，只认端口名和 `RTE_E_*`。
 *
 *          @section RTE_MAP 四态映射（这是本层唯一的实质逻辑）
 *
 *          | 绑定层 | RTE | 含义 |
 *          |--------|-----|------|
 *          | `BCM_SIG_VALID` | `RTE_E_OK` | 对方明确说了，值可用 |
 *          | `BCM_SIG_INVALID` | `RTE_E_INVALID` | 对方说"我现在是无效的" |
 *          | `BCM_SIG_TIMEOUT` | `RTE_E_MAX_AGE_EXCEEDED` | 太久没更新，值过期 |
 *          | `BCM_SIG_NEVER_RECEIVED` | `RTE_E_NEVER_RECEIVED` | 上电至今没收到 |
 *
 *          **四种状态一一对应，不做合并。** 合并（比如把 TIMEOUT 并进 INVALID）
 *          会让业务失去"是丢包还是对方报错"的判断依据 —— 这两种故障的处理
 *          方式不同（前者该保持输出，后者该进安全态）。
 *
 *          @note @section RTE_SCOPE V0.1 的范围（刻意很小）
 *
 *          - 只有 **switch 类型**（4 值）端口。数值信号（车速那类需要
 *            factor/offset 的）等"物理值转换层"落地时一起加，避免现在
 *            先造一个 `Rte_Read_uint16` 却没有 factor 可用的空壳。
 *          - **没有 runnable 调度**：`BcmBiz_MainFunction()` 仍由 `main.c`
 *            按拍调用。调度表是 10.5「验证缓存与执行顺序」的事，现在加
 *            只会多一层没人验证的间接。
 *          - **没有读缓存**：结论见 @ref RTE_SNAPSHOT。
 *          - **没有 init runnable**：TX 端口的初值由 `BcmSig_Init()` 统一写，
 *            保持"一个写者"。RTE 再写一次会出现两个初始化源，谁后跑谁赢。
 *
 *          @section RTE_SNAPSHOT 为什么不做读缓存（10.5 的结论，有代码证据）
 *
 *          看三处：
 *
 *          | 位置 | 事实 |
 *          |------|------|
 *          | `Com_Cfg.c:10819` | 信号的 `ptr` 直接指向 `Com_PduData_CCVS_RX`（**别名，不是副本**） |
 *          | `Com.c:635` | `Com_RxIndication()` 在中断上下文 `memcpy` 覆写这块缓冲 |
 *          | `bcm_sig.c` | `BcmSig_MainFunction()` 每拍把 Com 的值锁进 `s_rxState`，`BcmSig_RxRead()` 读影子 |
 *
 *          所以"一拍内两次读会不会不一样"的答案是：**RTE 层不会，因为
 *          快照已经在绑定层做过了**。RTE 再缓存一层只是把同一份数据存两遍，
 *          还要额外回答"缓存什么时候刷新"这个新问题。
 *
 *          @warning 已知边界：`BcmSig_MainFunction()` 遍历**同一帧的多个信号**
 *          时，中断仍可能换掉底层缓冲，导致同一帧内的信号来自两帧（撕裂）。
 *          当前绑定的 RX 信号都独占报文（手刹 1 个），不触发；**若将来一个
 *          决策要用同帧 ≥2 个信号，必须改成"整 PDU 快照后再解包"**，
 *          不是在 RTE 加缓存能解决的。
 *
 * @warning 端口是**单向**的：`Rte_Write()` 打到 RX 端口、`Rte_Read()` 读 TX
 *          端口都返回 `E_NOT_OK`。这不是防御性编程，是为了让"接反了"在
 *          第一次调用时就暴露，而不是等到总线上出现一条自己发给自己的报文。
 *
 * @author  binbina
 * @version V0.1.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V0.1.0 | 2026-11-17 | binbina | 首版：switch 端口、四态映射、单向校验 |
 */

#ifndef RTE_H
#define RTE_H

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================== [ 返回状态 ] ============================== */

/** @brief RTE 操作状态（S/R 接口的返回值） */
typedef uint8_t Rte_StatusType;

#define RTE_E_OK                 ((Rte_StatusType)0u) /**< 值可用 */
#define RTE_E_INVALID            ((Rte_StatusType)1u) /**< 对方声明值无效 */
#define RTE_E_MAX_AGE_EXCEEDED   ((Rte_StatusType)2u) /**< 值过期（超时） */
#define RTE_E_NEVER_RECEIVED     ((Rte_StatusType)3u) /**< 从未收到 */

/* ============================== [ 数据类型 ] ============================== */

/**
 * @brief 开关类信号（灯、门锁、使能）
 *
 * @note 与 `Bcm_SwStateType` 数值一致是**巧合驱动的优化**，不是契约：
 *       `rte.c` 里有显式转换表。将来绑定层改枚举顺序，这里不会跟着错。
 */
typedef enum
{
	RTE_SWITCH_OFF = 0,  /**< 灭 / 未激活 */
	RTE_SWITCH_ON,       /**< 亮 / 激活 */
	RTE_SWITCH_ERROR,    /**< 故障 / 对方报错 */
	RTE_SWITCH_INVALID   /**< 不可用（无效或未知） */
} Rte_SwitchType;

/* ============================== [ 端口编号 ] ============================== */

/**
 * @brief 端口编号（业务侧唯一可见的"地址"）
 *
 * @note  命名是**业务语义**，不是报文名。`RTE_PORT_PARK_BRAKE` 落在哪条报文、
 *        第几位，只有 `rte_cfg.c` 与绑定表知道。
 */
typedef enum
{
	RTE_PORT_PARK_BRAKE = 0, /**< 输入：驻车制动开关 */
	RTE_PORT_BRAKE_LAMP,     /**< 输出：制动灯状态 */
	RTE_PORT_NUM             /**< 端口总数（不是有效编号） */
} Rte_PortIdType;

/* ================================ [ 接口 ] ================================ */

/**
 * @brief 读一个输入端口
 *
 * @param[in]  port 端口号
 * @param[out] data 值；**仅在返回 `RTE_E_OK` 时有效**
 *
 * @return `RTE_E_OK` / `RTE_E_INVALID` / `RTE_E_MAX_AGE_EXCEEDED` /
 *         `RTE_E_NEVER_RECEIVED`；端口号越界、方向不对或 @p data 为 NULL
 *         时返回 `RTE_E_INVALID`
 *
 * @note  非 `RTE_E_OK` 时 @p data 仍会被写成 `RTE_SWITCH_INVALID`，
 *        但调用者**不应该**依赖它 —— 那是为了防止"忘了判返回值"时读到
 *        上一次的旧值，不是给"不判返回值"提供正当性。
 */
Rte_StatusType Rte_Read(Rte_PortIdType port, Rte_SwitchType *data);

/**
 * @brief 写一个输出端口
 *
 * @param[in] port 端口号
 * @param[in] data 值
 *
 * @return `E_OK`：已写入绑定层影子（**不是**已上总线，见下）；
 *         `E_NOT_OK`：端口越界、方向不对或值非法
 *
 * @warning 写入只更新绑定层的**影子**，真正进 Com 在下一拍
 *          `BcmSig_MainFunction()`。这条一拍延迟是刻意保留的（同一拍内
 *          多处写同一个灯时，最后一处生效，不会产生中间帧），
 *          已在 Host 用例里显式断言。
 */
Std_ReturnType Rte_Write(Rte_PortIdType port, Rte_SwitchType data);

/* ============================== [ 类型化封装 ] ============================== */

/**
 * @brief 类型化读端口（生成器将来从端口表生成，现在是手写）
 * @param[out] p `Rte_SwitchType *`
 */
#define Rte_Read_ParkBrake(p)   Rte_Read(RTE_PORT_PARK_BRAKE, (p))

/**
 * @brief 类型化写端口
 * @param[in] v `Rte_SwitchType`
 */
#define Rte_Write_BrakeLamp(v)  Rte_Write(RTE_PORT_BRAKE_LAMP, (v))

#ifdef __cplusplus
}
#endif

#endif /* RTE_H */
