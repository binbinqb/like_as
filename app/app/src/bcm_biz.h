/**
 * @file    bcm_biz.h
 * @brief   业务骨架（A9）：一条端到端的业务，用来证明"形状"能跑通
 *
 * @details @section BIZ_WHY 为什么先做一条最小的业务
 *
 *          框架的价值不在"每个模块都能跑"，而在**一条业务能从输入走到输出**。
 *          只有走完一遍，才能知道层与层之间的接缝是否真的够用：
 *
 *          @code
 *            ① 输入：BcmSig_RxRead()      → 值 + 有效性（A2）
 *            ② 决策：本文件                → 纯逻辑，可单测
 *            ③ 输出：BcmSig_TxSet()       → 翻译成 raw 进 Com
 *            ④ 诊断：健康状态对外可见       → 上报点（受 D9 限制，见下）
 *          @endcode
 *
 *          本版选的业务是**驻车制动联动制动灯**，理由：
 *          1. 它是矩阵里已绑的接收信号（`CCVS.ParkingBrakeSwitch`）与
 *             已绑的发送信号（`BCM_LCSF.BrakelightST`）之间最短的一条链；
 *          2. 判据可以完全落在总线上（不用示波器、不用 GPIO 探针）；
 *          3. 它天然覆盖"输入丢失怎么办"这个真问题。
 *
 * @note    @section BIZ_DTC ④ 诊断这一段**当前接不上**，原因不是没写
 *
 *          `infras/diagnostic/Dem/Dem.c` 的 `Dem_StoreFailed()` 里 DTC 码是
 *          **写死的常量** `DEM_CFG_DTC_CAN_BUSOFF`（第 206 / 250 行），
 *          没有"事件 → DTC"的映射表。也就是说：现在不论报哪个事件，
 *          0x19 读出来都是 `C00100`。
 *
 *          要接真清单必须改 `infras/`，那是 D9（infras 改动权限）的范围。
 *          所以本文件**不调用** `Dem_SetEventStatus()`：宁可让诊断缺一段，
 *          也不能往 DTC 表里塞一个错的码 —— 那会让后续所有 0x19 的判据失效。
 *          上报点留在 `BcmBiz_BrakeHealth()` 上，命令层可读、将来可直接接。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef BCM_BIZ_H
#define BCM_BIZ_H

#include "Std_Types.h"

/**
 * @brief 业务健康状态（诊断上报点的载体）
 *
 * @details 与 `Bcm_SigValidityType` 的区别：那个是"输入值算不算数"，
 *          这个是"这条业务当前处于什么结论"。中间隔着决策逻辑，
 *          所以两者不能合并 —— 同一个 `TIMEOUT` 在去抖期内和下结论后，
 *          业务健康状态是不同的。
 */
typedef enum
{
	BCM_BIZ_INIT = 0,   /**< 上电至今还没收到过有效输入，输出保持关闭 */
	BCM_BIZ_OK,         /**< 输入有效，输出跟随输入 */
	BCM_BIZ_INVALID,    /**< 输入值落在无效域，输出保持上一次的值 */
	BCM_BIZ_PEER_ERROR, /**< 对方明确报故障，输出关闭 */
	BCM_BIZ_LOST        /**< 通信丢失已超过去抖时间，输出关闭 */
} Bcm_BizHealthType;

/**
 * @brief 初始化（在 `BcmSig_Init()` 之后调用）
 *
 * @note 不写输出：`BcmSig_Init()` 已把 11 个灯置 OFF 并写进 Com，
 *       这里再写一遍只会多一次重排，不改变任何状态。
 */
void BcmBiz_Init(void);

/**
 * @brief 业务周期任务（10 ms，在 `BcmSig_MainFunction()` **之后**、`Com_MainFunctionTx()` **之前**）
 *
 * @details 顺序不能反：`BcmSig_MainFunction()` 负责把总线值搬进 shadow，
 *          本函数读 shadow 做决策，然后 `BcmSig_TxSet()` 把结论写回发送 shadow。
 *          放反了决策就会用上一拍的输入。
 */
void BcmBiz_MainFunction(void);

/**
 * @brief 当前驻车制动业务健康状态（诊断上报点 / 命令层观察）
 */
Bcm_BizHealthType BcmBiz_BrakeHealth(void);

/**
 * @brief 打开 / 关闭本业务对输出信号的接管
 *
 * @param[in] on `TRUE` = 业务接管制动灯（按输入决策）；`FALSE` = 完全不碰
 *
 * @note  @warning **上电默认关闭**。理由不是"没做完"，而是"别抢信号"：
 *        `bcm all on|off` 这类验收命令直接写 11 个灯的发送 shadow，
 *        如果业务同时按输入决定制动灯，两者每 10 ms 互相覆盖 ——
 *        M23 的整帧对拍会变成随机失败。
 *
 *        这与 A3 的处理方式一致（`can auto on`）：**默认不干扰，
 *        要用的时候显式打开**。上车时这一行应该是 `TRUE`，
 *        并且那时也不该再有 `bcm all` 这种手工写灯的命令。
 */
void BcmBiz_SetEnabled(boolean on);

/**
 * @brief 业务是否在接管
 */
boolean BcmBiz_IsEnabled(void);

/**
 * @brief 健康状态的可读名字
 */
const char *BcmBiz_HealthName(Bcm_BizHealthType h);

#endif /* BCM_BIZ_H */
