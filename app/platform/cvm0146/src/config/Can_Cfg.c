/**
 * @file    Can_Cfg.c
 * @brief   CAN 通道配置表（波特率 / STB 引脚 / 硬件实例映射）
 *
 * @details 字段顺序按 `Can_Priv.h` 的 `Can_ChannelConfigType` 在
 *          **定义了 `USE_PORT`** 时的布局：
 *          `{ context, baudrate, TrcvPinSTB, samplePoint, hwInstanceId, NormalValueOfTrcvPinSTB }`
 *
 *          @section CANCFG_USE_PORT 为什么走 USE_PORT 分支
 *          定义了 `USE_PORT` 后，AS 的 Can 驱动用 `Dio_WriteChannel()` 控制收发器 STB，
 *          而不是自己维护一张 `CtrlPins` 表。好处：引脚 MUX 与电平控制都归 Port/Dio 管，
 *          Can 配置里只剩一个通道号，CAN 通道加一个也不用再抄一份引脚描述。
 *
 *          @section CANCFG_STB STB 极性
 *          TJA1044：**STB 低 = Normal，高 = Standby**。所以
 *          `NormalValueOfTrcvPinSTB = STD_LOW`，
 *          `CanIf_SetTrcvMode(NORMAL)` 会把它拉低，`SLEEP` 则拉回高。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：CAN0 500 kbps + PTC1 STB |
 */

#include "Can.h"
#include "Can_Cfg.h"
#include "Can_Priv.h"
#include "Can_HwCfg.h"
#include "Board_Cfg.h"   /* BOARD_CANx_BITRATE：波特率唯一来源是 Board.json */

#include "Dio_Cfg.h"

/* ============================ [ 数据 ] ============================ */

/** @brief 每个通道的运行上下文（状态机 + 收发器模式），驱动运行期改写 */
static Can_ChannelContextType Can_ChannelContexts[CAN_CFG_NUM_CHANNELS];

/**
 * @brief 通道配置表
 * @warning 字段顺序由 `Can_Priv.h` 的结构体决定，**不是**按名字初始化。
 *          若将来打开 `CAN_USE_CTRL_AC_CONFIG_TYPE`，要在 context 后插入 acCfg。
 */
static const Can_ChannelConfigType Can_ChannelConfigs[CAN_CFG_NUM_CHANNELS] = {
	{
		&Can_ChannelContexts[0],              /* context */
		BOARD_CAN0_BITRATE,                   /* baudrate（来自 Board.json） */
		DIO_CHANNEL_CAN0_STB,                 /* TrcvPinSTB（USE_PORT 分支） */
		(uint8_t)CAN_CFG_SAMPLE_POINT,        /* samplePoint，单位 1% */
		0u,                                   /* hwInstanceId = CAN0 */
		STD_LOW,                              /* NormalValueOfTrcvPinSTB：低=正常 */
	},
	{
		&Can_ChannelContexts[1],              /* context */
		BOARD_CAN1_BITRATE,                   /* baudrate（来自 Board.json） */
		DIO_CHANNEL_CAN1_STB,                 /* TrcvPinSTB：PTE13 */
		(uint8_t)CAN_CFG_SAMPLE_POINT,        /* samplePoint */
		1u,                                   /* hwInstanceId = CAN1 */
		STD_LOW,                              /* 低=正常 */
	},
};

/**
 * @brief 硬件实例 → 通道号映射
 * @details `hwIns2ChlMap[0] = 0` 表示"硬件 CAN0 对应通道 0"。
 *          多控制器时这里描述物理实例与逻辑通道的重排（AS 的做法：
 *          产品可能把 CTRL2 当 CAN0 用，映射表就是为这种情况准备的）。
 */
static const uint8_t Can_HwIns2ChlMap[2] = { 0u, 1u };

const Can_ConfigType Can_Config = {
	Can_ChannelConfigs,
	Can_HwIns2ChlMap,
	(uint8_t)CAN_CFG_NUM_CHANNELS,
	(uint8_t)ARRAY_SIZE(Can_HwIns2ChlMap),
};

/* ============================ [ 邮箱表 ] ============================ */

/**
 * @brief CAN0 邮箱表
 *
 * @warning **本表由 `tools/sync_can.py` 从 `Can/Can.json` 生成，不要手改。**
 *          区间内的任何手工修改都会在下次生成时被覆盖；要加/改邮箱请改 JSON，
 *          然后 `python tools/sync_can.py && python tools/can_table_check.py`。
 *
 * @details @section CANCFG_MB0_14 按段分组，不是一条报文一个邮箱
 *
 * | mb | 方向 | 覆盖范围 | 承载报文数 |
 * |----|------|----------|-----------|
 * | 2 | RX | `0x18FFxxxx` 全段（PGN 0xFF00~0xFFFF） | 车辆/灯光/门锁/雨刮/报警… |
 * | 6 | RX | `0x18FExxxx` 全段（PGN 0xFE00~0xFEFF） | 车速/里程/… |
 * | 7 | RX | `0x0A0~0x0A7` | 快变模拟量段 |
 * | 8 | RX | `0x100~0x107` | 灯光控制段 |
 * | 9 | RX | `0x110` | 车身状态 |
 *
 * 49 条报文的 Foton 矩阵用这套结构也是 **6 个接收邮箱**就够。
 *
 * @warning **真正要小心的不是邮箱号，是掩码的位位置。**
 *
 *          M14 在这里误判过一次：把标准帧段配到 mb7/8/9 后，mb8/mb9 一条都收不到
 *          （连带 mb12/mb14 的 NM、Com 也哑了）。当时读到 `MCR[MAXMB]=96`
 *          却只有 mb0~mb7 有计数，就判断成"这颗芯片只实现了 8 个邮箱"——
 *          **这个结论是错的**。真相是 `CAN_HW_MASK_STD_FAST` 少了 18 位移位：
 *          11 位的 `0x7F8` 落在 bit[10:3]，而那几位在 ID 域里恒为 0，于是
 *          mb7 变成**全收邮箱**，把排在它后面的所有标准帧都截走了。
 *          推翻"8 邮箱"的证据是：早前 mb15 配同一套掩码时**它自己是好的**
 *          （只有它后面的 mb16/17 收不到）——说明 mb15 完全可用。
 *
 *          教训：**"某个邮箱收不到"优先怀疑掩码/邮箱序号配错，而不是先怀疑
 *          硬件容量。** 全收邮箱没有任何报错，只表现为"后面的报文全丢"。
 *
 * @note  邮箱 10、15 空着不用，留给"某条报文必须独占邮箱"的场合
 *        （将来接 CAN FD 或需要独立时间戳的报文）。
 * @note  ID、扩展位、DLC 三者在 `CfgMsgObj` 时写死，运行期改不了
 *        （厂商 `SetTxMsg` 只写数据区），所以一条报文一个邮箱。
 */
/* @generated BEGIN: CAN0 mailboxes */
static const CanHw_MsgCfgType CanHw_MsgCfgs0[] = {
	{  0u, 1u,       0x123u, false, CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb0  HEARTBEAT    TX 0x123 */
	{  1u, 1u,       0x321u, false, CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu },   /**< mb1  TESTRX       RX 0x321 */
	{  2u, 1u,  0x18FF0000u, true , CAN_HW_MB_RX, 8u, true ,  0x1FFF0000u },   /**< mb2  J1939_SEG_FF RX 0x18FF0000 */
	{  3u, 1u,  0x18FF0002u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb3  EXT_TX       TX 0x18FF0002 */
	{  4u, 1u,       0x7E8u, false, CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb4  DIAG_RESP    TX 0x7E8 */
	{  5u, 1u,       0x7E0u, false, CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu },   /**< mb5  DIAG_REQ     RX 0x7E0 */
	{  6u, 1u,  0x18FE0000u, true , CAN_HW_MB_RX, 8u, true ,  0x1FFF0000u },   /**< mb6  J1939_SEG_FE RX 0x18FE0000 */
	{  7u, 1u,        0xA0u, false, CAN_HW_MB_RX, 8u, true ,       0x7F8u },   /**< mb7  STD_FAST     RX 0xA0 */
	{  8u, 1u,       0x100u, false, CAN_HW_MB_RX, 8u, true ,       0x7F8u },   /**< mb8  STD_LIGHT    RX 0x100 */
	{  9u, 1u,       0x110u, false, CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu },   /**< mb9  STD_BODY     RX 0x110 */
	/* NM 发送：与 mb12 同一 ID，方向不同（FlexCAN 邮箱方向配置期定死）。int 必须为 true：发送完成中断是 s_txPending 的唯一释放点，关掉会让首帧之后永久 CAN_BUSY。 */
	{ 11u, 1u,       0x500u, false, CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb11 NM_TX        TX 0x500 */
	{ 12u, 1u,       0x500u, false, CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu },   /**< mb12 NM_RX        RX 0x500 */
	/* Com 测试报文：与 mb14 配对，避免注入测试与自发报文撞车。int 必须为 true（同 NM_TX）：否则 0x200 只出首帧，Com 的 bTxRetry 永远为 1。 */
	{ 13u, 1u,       0x200u, false, CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb13 COM_TX       TX 0x200 */
	{ 14u, 1u,       0x201u, false, CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu },   /**< mb14 COM_RX       RX 0x201 */
};
/* @generated END: CAN0 mailboxes */

/**
 * @brief CAN1 邮箱表：**实车整车网**（Foton L1 通信矩阵）
 *
 * @warning **本表由 `tools/sync_can.py` 从 `Can/Can.json` 生成，不要手改。**
 *
 * @details @section CANCFG_CAN1_LAYOUT 15 个邮箱承载 M8 测试 + 真实矩阵
 *
 * | mb | 方向 | 内容 | 说明 |
 * |----|------|------|------|
 * | 0 / 1 | TX / RX | `0x124` / `0x322` | M8 验证过的测试报文，**保留作为对照物** |
 * | 2~7 | TX | 6 条真实发送报文 | 一条报文一个邮箱（ID 在 CfgMsgObj 时写死） |
 * | 8~14 | RX | 7 个 PF 段 | 覆盖 34 条接收报文 |
 *
 * **为什么保留 0x124/0x322**：上板验证真实矩阵时，需要一个"确实能收发"的
 * 参照物。如果全部换成真实报文，就分不清"新配置生效了"还是"某条路径恰好还在跑"。
 * 而且 M8 的回归脚本依赖它们。
 *
 * @warning **邮箱号从 0 重新开始**：每个控制器有自己的邮箱 RAM，互不干扰。
 *          CAN0 用 mb0~mb14，CAN1 也从 mb0 开始，不冲突。
 */
/* @generated BEGIN: CAN1 mailboxes */
static const CanHw_MsgCfgType CanHw_MsgCfgs1[] = {
	{  0u, 1u,       0x124u, false, CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb0  TEST_TX      TX 0x124 */
	{  1u, 1u,       0x322u, false, CAN_HW_MB_RX, 8u, true ,  0xFFFFFFFFu },   /**< mb1  TEST_RX      RX 0x322 */
	{  2u, 1u,  0x18FE4021u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb2  TX_LCSF      TX 0x18FE4021 */
	{  3u, 1u,  0x18FF0C21u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb3  TX_CTRL      TX 0x18FF0C21 */
	{  4u, 1u,   0xCFDCC21u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb4  TX_OEL       TX 0xCFDCC21 */
	{  5u, 1u,  0x18FDCD21u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb5  TX_OWW       TX 0x18FDCD21 */
	{  6u, 1u,  0x18FE4E21u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb6  TX_DOOR      TX 0x18FE4E21 */
	{  7u, 1u,  0x18FECA21u, true , CAN_HW_MB_TX, 8u, true ,         0x0u },   /**< mb7  TX_DM1       TX 0x18FECA21 */
	{  8u, 1u,  0x18EB0000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb8  RX_PF_EB     RX 0x18EB0000 */
	{  9u, 1u,  0x18EC0000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb9  RX_PF_EC     RX 0x18EC0000 */
	{ 10u, 1u,  0x18EE0000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb10 RX_PF_EE     RX 0x18EE0000 */
	{ 11u, 1u,  0x18F00000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb11 RX_PF_F0     RX 0x18F00000 */
	{ 12u, 1u,  0x18FD0000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb12 RX_PF_FD     RX 0x18FD0000 */
	{ 13u, 1u,  0x18FE0000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb13 RX_PF_FE     RX 0x18FE0000 */
	{ 14u, 1u,  0x18FF0000u, true , CAN_HW_MB_RX, 8u, true ,    0xFF0000u },   /**< mb14 RX_PF_FF     RX 0x18FF0000 */
};
/* @generated END: CAN1 mailboxes */

/** @brief 每个通道一张邮箱表，下标 = 通道号 */
const CanHw_MsgTableType CanHw_MsgTables[CAN_CFG_NUM_CHANNELS] = {
	{ CanHw_MsgCfgs0, (uint8_t)ARRAY_SIZE(CanHw_MsgCfgs0) },   /* 0 = CAN0 */
	{ CanHw_MsgCfgs1, (uint8_t)ARRAY_SIZE(CanHw_MsgCfgs1) },   /* 1 = CAN1 */
};

/**
 * @brief 硬件发送对象表：下标即 `Can_Write()` 的 `Hth`
 * @note  `CanIf_Cfg.c` 的 `hoh` 字段引用 `CAN_HW_HTH_*` 宏，不要写裸数字。
 */
/* @generated BEGIN: HTH table */
const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM] = {
	{ 0u,  0u,       0x123u, 8u },   /**< HTH0  CAN0 mb0  HEARTBEAT    0x123 */
	{ 0u,  3u,  0x18FF0002u, 8u },   /**< HTH1  CAN0 mb3  EXT_TX       0x18FF0002 */
	{ 1u,  0u,       0x124u, 8u },   /**< HTH2  CAN1 mb0  TEST_TX      0x124 */
	{ 0u,  4u,       0x7E8u, 8u },   /**< HTH3  CAN0 mb4  DIAG_RESP    0x7E8 */
	{ 0u, 11u,       0x500u, 8u },   /**< HTH4  CAN0 mb11 NM_TX        0x500 */
	{ 0u, 13u,       0x200u, 8u },   /**< HTH5  CAN0 mb13 COM_TX       0x200 */
	{ 1u,  2u,  0x18FE4021u, 8u },   /**< HTH6  CAN1 mb2  TX_LCSF      0x18FE4021 */
	{ 1u,  3u,  0x18FF0C21u, 8u },   /**< HTH7  CAN1 mb3  TX_CTRL      0x18FF0C21 */
	{ 1u,  4u,   0xCFDCC21u, 8u },   /**< HTH8  CAN1 mb4  TX_OEL       0xCFDCC21 */
	{ 1u,  5u,  0x18FDCD21u, 8u },   /**< HTH9  CAN1 mb5  TX_OWW       0x18FDCD21 */
	{ 1u,  6u,  0x18FE4E21u, 8u },   /**< HTH10 CAN1 mb6  TX_DOOR      0x18FE4E21 */
	{ 1u,  7u,  0x18FECA21u, 8u },   /**< HTH11 CAN1 mb7  TX_DM1       0x18FECA21 */
};
/* @generated END: HTH table */
