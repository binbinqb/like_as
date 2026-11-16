/**
 * @file    bcm_sig_cfg.c
 * @brief   车身信号绑定表（M23）：业务编号 → Com 信号号 + raw 映射
 *
 * @details 本文件是**纯数据表，零逻辑**。逻辑全在 `bcm_sig.c`。
 *          加一个信号 = 在 `bcm_sig.h` 的枚举里加一项 + 在表里加一行
 *          （顺序必须一致，下面的表长断言会在编译期拦住漏改）。
 *
 *          @section BCMSIGCFG_DEFAULT 默认映射规则
 *
 *          矩阵里 281 个 `VAL_` 表有 89 种写法，但**数值语义高度一致**：
 *          绝大多数 2 bit 状态信号都是
 *          `0 = 灭/未激活`、`1 = 亮/激活`、`2 = 故障/报错`、`3 = 无效`，
 *          只是叫法不同（`Inactive/Active/Fault/Invalid` 与
 *          `Off/On/Error/Invalid` 与 `off/up/down/not used` …）。
 *
 *          所以这里不逐个信号写映射，而是两条**默认表**：
 *
 *          | 方向 | 下标 | 取值 |
 *          |------|------|------|
 *          | 上行 raw→语义 | raw 0 / 1 / 2 / 3 | OFF / ON / FAULT / UNKNOWN |
 *          | 下行 语义→raw | UNKNOWN / OFF / ON / FAULT | 3 / 0 / 1 / 2 |
 *
 *          @warning 注意两条表的**下标语义不同**：上行表的下标是 raw 值，
 *          下行表的下标是 `Bcm_SwStateType` 枚举值。看反了不会编译错，
 *          只会让 `ON` 翻译成 `FAULT`，这类错误只能靠上板对拍抓。
 *
 *          `map == NULL` 表示"用默认表"。例外信号才给一张覆盖表。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "bcm_sig_priv.h"
#include "CanIf_Cfg.h"   /* CANIF_RX_CAN1_CCVS：接收项的到达监视要知道 PDU 号 */

/* ============================ [ 默认映射表 ] ============================ */

const uint8_t BcmSig_RxMapDefault[4] =
{
	(uint8_t)BCM_SW_STATE_OFF,     /**< raw 0：灭 / 未激活 */
	(uint8_t)BCM_SW_STATE_ON,      /**< raw 1：亮 / 激活 */
	(uint8_t)BCM_SW_STATE_FAULT,   /**< raw 2：故障 / 报错 */
	(uint8_t)BCM_SW_STATE_UNKNOWN  /**< raw 3：无效 / 未实现 */
};

const uint8_t BcmSig_TxMapDefault[4] =
{
	3u, /**< [BCM_SW_STATE_UNKNOWN] → 无效 */
	0u, /**< [BCM_SW_STATE_OFF]     → 灭 */
	1u, /**< [BCM_SW_STATE_ON]      → 亮 */
	2u  /**< [BCM_SW_STATE_FAULT]   → 故障 */
};

/**
 * @brief 为什么现在没有任何信号用覆盖表，机制却要留着
 *
 * @details 例外是**已知会有**的，有实证：`BCM_Ctrl.CentralLockSw` 的枚举是
 *          `0=off 1=lock 2=unlock 3=not used` —— raw 1 和 2 是**两个不同的
 *          动作**，不是"亮 / 故障"。套默认表的话，`unlock`（raw 2）会被翻成
 *          `FAULT`，业务层会把"用户按了解锁"当成"门锁坏了"。
 *
 *          这类信号需要的是一张自己的表：
 *          @code
 *          static const uint8_t s_mapCentralLock[4] = {
 *              (uint8_t)BCM_SW_STATE_OFF,      // raw 0 = off
 *              (uint8_t)BCM_SW_STATE_ON,       // raw 1 = lock
 *              (uint8_t)BCM_SW_STATE_ON,       // raw 2 = unlock
 *              (uint8_t)BCM_SW_STATE_UNKNOWN,  // raw 3 = not used
 *          };
 *          @endcode
 *          但这只是"能跑"，并没有解决"lock 与 unlock 怎么区分"——
 *          那需要一个**动作枚举**，不是硬塞进开关枚举。等做门锁业务
 *          （设计评审第 4.6 批）时再定，本版不猜。
 *
 *          留 `map` 字段的成本：12 行表每行多一个指针（48 B），换来将来
 *          加例外时**不必改表结构**（改结构要动全部 372 行）。
 */

/* ============================ [ 发送表 ] ============================ */

/**
 * @brief 发送信号绑定表（11 个灯状态，全在 `BCM_LCSF` 0x18FE4021）
 *
 * @note  顺序与 `Bcm_SigIdType` 严格一一对应。
 *        这 11 个信号在矩阵里的枚举写法不同（8 个 `Inactive/Active`、
 *        3 个 `Off/On`），但 raw 数值语义完全一致，因此**全部用默认表**。
 */
const BcmSig_TxCfgType BcmSig_TxCfg[BCM_SIG_TX_NUM] =
{
	/* Com 信号号                                        覆盖表 */
	{ (Com_SignalIdType)COM_SID_BCM_LowBeamSts,        NULL }, /* 近光灯 */
	{ (Com_SignalIdType)COM_SID_BCM_HighBeamSts,       NULL }, /* 远光灯 */
	{ (Com_SignalIdType)COM_SID_BCM_FrontFogSts,       NULL }, /* 前雾灯 */
	{ (Com_SignalIdType)COM_SID_BCM_TurnRLightSts,     NULL }, /* 右转向 */
	{ (Com_SignalIdType)COM_SID_BCM_TurnLLightSts,     NULL }, /* 左转向 */
	{ (Com_SignalIdType)COM_SID_BCM_DRLSts,            NULL }, /* 日行灯 */
	{ (Com_SignalIdType)COM_SID_BCM_PositionLightSts,  NULL }, /* 位置灯 */
	{ (Com_SignalIdType)COM_SID_BCM_RearFogSts,        NULL }, /* 后雾灯 */
	{ (Com_SignalIdType)COM_SID_BackUpLightSt,         NULL }, /* 倒车灯 */
	{ (Com_SignalIdType)COM_SID_BrakelightST,          NULL }, /* 制动灯 */
	{ (Com_SignalIdType)COM_SID_InteriorLampSt,        NULL }  /* 室内灯 */
};

/* ============================ [ 接收表 ] ============================ */

/**
 * @brief 接收信号绑定表
 *
 * @note  只绑 1 条做通路对照：`CCVS`（0x18FEF121）的 `ParkingBrakeSwitch`，
 *        枚举是 `0=ParkingBrakeNotSet 1=ParkingBrakeSet 2=Error
 *        3=NotAvailable`，与默认表完全一致。
 *
 *        @warning 本版**故意不绑**其余接收信号，原因分两类，都要先确认：
 *        1. **矩阵没给枚举**。`IC_MSG.DoorOpenSw`（0x18FF0917，`12|2@1+`）
 *           在 dbc 里查不到 `VAL_` 表 —— raw 0..3 的语义只有矩阵原文知道。
 *           凭"门开应该是 0 关 1 开"去猜，猜错就是安全隐患。
 *        2. **模拟量需要 factor/offset 换算**。`TachographVehicleSpeed`
 *           是 `(0.00390625, 0)`，Com 返回 raw 4660，物理值是 18.2 km/h。
 *           本层目前没有承载它的能力（表结构里没有 factor 字段），
 *           而暂时也没有业务消费它。
 */
const BcmSig_RxCfgType BcmSig_RxCfg[BCM_SIG_RX_NUM] =
{
	/* Com 信号号                                覆盖表  CanIf PDU 号                  超时(ms) */
	{ (Com_SignalIdType)COM_SID_ParkingBrakeSwitch, NULL, CANIF_RX_CAN1_CCVS,      300u } /* 手刹开关 */
};

/**
 * @brief 超时门限为什么是 300 ms
 *
 * @details `CCVS`（0x18FEF121）在 `dbc/can1.dbc` 里的 `GenMsgCycleTime`
 *          是 **100 ms**（第 509 行）。300 ms = 3 个周期 —— 允许丢两帧
 *          再判超时。
 *
 *          为什么不用 2 倍：车身总线上一次仲裁拥塞 + 一次 FEE 擦除抖动
 *          （`NvM` 单次写可达几毫秒）就可能连丢一帧，2 倍门限会在正常
 *          工况下偶发误报。
 *
 *          为什么不用 5 倍：`ParkingBrakeSwitch` 参与起步/驻车判断，
 *          500 ms 才认掉线太迟；对端真正断电时，300 ms 内必须让业务
 *          知道"这个值不再可信"。
 *
 *          门限写成每信号一项而不是每 PDU 一项：同一帧里不同信号的
 *          容忍度不一样（比如未来绑 `WheelBasedVehicleSpeed`，它参与
 *          车速计算，门限就该更紧）。代价是每条多 2 字节。
 */

/* ============================ [ 编译期自检 ] ============================ */

/**
 * @brief 表长断言：表的行数必须等于枚举里的 `*_NUM`
 * @note  加信号时若只改了表忘了改枚举（或反之），这里直接编译失败，
 *        不会出现"表比枚举长、多出来的行被静默忽略"这种查不出来的问题。
 */
_Static_assert((sizeof(BcmSig_TxCfg) / sizeof(BcmSig_TxCfg[0])) ==
               (size_t)BCM_SIG_TX_NUM,
               "BcmSig_TxCfg 行数与 BCM_SIG_TX_NUM 不一致");
_Static_assert((sizeof(BcmSig_RxCfg) / sizeof(BcmSig_RxCfg[0])) ==
               (size_t)BCM_SIG_RX_NUM,
               "BcmSig_RxCfg 行数与 BCM_SIG_RX_NUM 不一致");
