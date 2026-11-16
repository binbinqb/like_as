/**
 * @file    rx_mon.h
 * @brief   CAN 接收到达监视（A2）：记下每条 RX PDU **最后一次到达**的时刻
 *
 * @details @section RXMON_WHY 为什么需要这一层
 *
 *          `Com_ReceiveSignal()` 的返回值**不携带"收到过没有"**：
 *          查 `infras/communication/Com/Com.c` 的 `comReceiveSignal()`，
 *          只要参数合法它就返回 `E_OK`，读到的可能只是报文缓冲里的
 *          `InitialValue`。所以业务层无法用 Com 的返回值回答两个问题：
 *
 *          | 问题 | 业务后果 |
 *          |------|----------|
 *          | "这个信号的值是不是真的从总线上来的？" | 上电后对方还没发帧，读到 `OFF` 却以为对方说"灭" |
 *          | "对方是不是已经掉线了？" | 停发 3 s 后仍读到最后一个值，业务按旧值继续动作 |
 *
 *          AUTOSAR 的原生答案是 Com 的 data status + `RTE_E_NEVER_RECEIVED`，
 *          那需要改 `infras/`（D9 未放行）。本层是**应用侧等价物**：
 *          在 CanIf 回调里记到达时刻，把"到达事件"变成可查询的事实。
 *
 * @note    @section RXMON_HONEST 本层能回答什么、不能回答什么
 *
 *          | 能 | 不能 |
 *          |----|------|
 *          | 这条 PDU 从来没到过（上电至今） | 对方在应用层"宣布自己无效"（那是数据的语义，由 raw 值回答） |
 *          | 距最后一次到达过了多少毫秒 | 报文里的 rolling counter / checksum 对不对（E2E 的职责） |
 *          | 到达是否已经超过配置的超时 | 丢了几帧（只记最后一次，不计数） |
 *
 *          "数据本身无效"（raw = 无效值）由绑定层按映射表回答，与本层无关。
 *          两者组合起来才是业务要的四态，见 `BcmSig_RxRead()`。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef RX_MON_H
#define RX_MON_H

#include "Std_Types.h"
#include "ComStack_Types.h" /* PduIdType */
#include "CanIf_Cfg.h"   /* CANIF_RX_PDU_NUM：表长由 CanIf 配置决定 */

/**
 * @brief `RxMon_AgeMs()` 的"从未到达"返回值
 *
 * @note  用 `0xFFFFFFFF` 而不是 0：0 是"刚刚到过"，两者语义相反，
 *        混用会让"没收到"看起来像"最新鲜"。调用者通常先问
 *        `RxMon_Seen()`，这个返回值只是兜底。
 */
#define RXMON_NEVER_MS      (0xFFFFFFFFu)

/**
 * @brief 清空全部到达记录
 *
 * @details 只在启动时调用一次（`EcuM` 起来之后、总线 ONLINE 之前）。
 *          清空的含义是"上电至今没有任何帧到过"，因此清空之后
 *          `RxMon_Seen()` 全部返回 `FALSE` —— 这正是我们要的初值。
 */
void RxMon_Init(void);

/**
 * @brief 记一次到达（**中断上下文调用**）
 *
 * @param[in] pduId CanIf 的 RX PDU 编号（`CANIF_RX_xxx`）
 *
 * @note  @warning 中断里只做两件事：置位 + 写时间戳。不做判断、不打印、
 *        不调用任何可能阻塞的接口 —— CanIf 的 RX 回调是在 CAN 中断里跑的，
 *        多花几微秒就可能丢掉下一帧。
 *
 * @note  写入是 32 位对齐单次写、置位是字节写，Cortex-M4 上都是原子的，
 *        所以本函数不需要关中断，也不需要临界区。
 *
 * @note  `pduId` 越界时直接忽略（不写 DET）：这属于配置错误，但
 *        在中断里调 DET 会引入不可预期的耗时；越界会表现为"永远收不到"，
 *        由 `bcm rx` 命令（`cmd/bcm_cmd.c`）连同超时门限一起打印出来。
 */
void RxMon_OnRx(PduIdType pduId);

/**
 * @brief 这条 PDU 上电至今有没有到过
 *
 * @param[in] pduId CanIf 的 RX PDU 编号
 * @retval TRUE  至少到过一次
 * @retval FALSE 从未到达（或 `pduId` 越界）
 */
boolean RxMon_Seen(PduIdType pduId);

/**
 * @brief 距最后一次到达过了多少毫秒
 *
 * @param[in] pduId CanIf 的 RX PDU 编号
 * @return 毫秒数；从未到达或 `pduId` 越界时返回 @ref RXMON_NEVER_MS
 *
 * @note 用无符号减法 `now - last`，32 位毫秒计数在 **49.7 天**回卷时
 *       结果依然正确（模运算），所以不必处理回卷。
 */
uint32_t RxMon_AgeMs(PduIdType pduId);

#endif /* RX_MON_H */
