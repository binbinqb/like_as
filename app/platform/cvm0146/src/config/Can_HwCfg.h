/**
 * @file    Can_HwCfg.h
 * @brief   CAN 硬件资源表（邮箱表 + 硬件发送对象表）的契约
 *
 * @details @section HWCFG_WHY 为什么单独一个头，而不是塞进 Can_Cfg.h
 *          `Can_Cfg.h` 会被 `infras/mcal/Can/Can.c` 直接包含，它的内容属于 **BSW 可见**，
 *          一旦出现邮箱/句柄这类硬件概念，MCAL 就被绑死在这颗芯片上。
 *          而邮箱表本质上是"这块板子的硬件资源分配"，只有 `CanAc.c`（AC 层）该看见。
 *
 *          所以拆成两个文件：
 *
 *          | 文件 | 内容 | 谁能看见 |
 *          |------|------|----------|
 *          | `Can_Cfg.h`   | 通道数、波特率、采样点 | BSW + 平台 |
 *          | `Can_HwCfg.h` | 邮箱表、HTH 表、报文 ID | **只有平台**（`CanAc.c` + `Can_Cfg.c`） |
 *
 *          @section HWCFG_NEUTRAL 为什么类型里没有 `FlexCanDrv_*`
 *          本文件被 `Can_Cfg.c` 包含，而 `Can_Cfg.c` 是用 **Can 库的编译参数**编的
 *          （`-Iinfras/include -Iinfras/mcal/Can -Isrc/config`，**没有 SDK 路径**）。
 *          写成厂商类型会直接编译失败 —— 这不是巧合，是构建脚本"配置源编进模块库"的必然结果。
 *
 *          因此这里用中性类型（`uint32_t` / `bool` / 自有枚举），
 *          由 `CanAc.c` 在初始化时翻译成 `FlexCanDrv_MsgCfgType`。
 *          代价是多一层翻译，收益是**配置表可以整体由 DBC 生成器替换**，且不碰 SDK。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：邮箱表从 CanAc.c 迁出，为 DBC 生成做准备 |
 */

#ifndef CAN_HWCFG_H
#define CAN_HWCFG_H

#include <stdint.h>
#include <stdbool.h>

#include "Can_Cfg.h"

/* ============================ [ 报文 ID ] ============================ */

/**
 * @brief M1 心跳帧：板子周期发送，Kvaser 观察数据递增
 * @note  M2 接 CanIf 后，这条报文仍保留，用来证明"MCAL 通道没被 CanIf 搞坏"
 */
#define CAN_HW_ID_HEARTBEAT     (0x123u)

/** @brief M1 接收帧：Kvaser 发送，板子回显 */
#define CAN_HW_ID_TESTRX        (0x321u)

/** @brief M2 新增：29-bit 扩展帧验证（J1939 格式，PGN=0xFF00） */
#define CAN_HW_ID_EXT_RX        (0x18FF0001u)

/** @brief M2 新增：29-bit 扩展帧发送 */
#define CAN_HW_ID_EXT_TX        (0x18FF0002u)

/* ---- M8：多扩展帧邮箱压力验证（模拟 Foton 49 条 J1939 报文的场景）---- */

/**
 * @brief 组 A：同一 PGN（0xFF01）、不同源地址 —— 验证**一条掩码收一组**
 * @note  J1939 的 29 位 ID = 优先级(3) + PGN(18) + 源地址(8)。
 *        `0x18FF01xx` 里 `0x18` 是优先级+PGN 高位，`0xFF01` 是 PGN，`xx` 是源地址。
 *        掩码 `0x1FFFFF00` 忽略最低 8 位，所以任意源地址都能进同一个邮箱。
 */
#define CAN_HW_ID_J1939_PGN     (0x18FF0100u)

/** @brief 组 B：四个**不同 PGN** 的报文 —— 验证多个独立邮箱并行工作 */
#define CAN_HW_ID_J1939_A       (0x18FEF100u)   /**< PGN 0xFEF1 */
#define CAN_HW_ID_J1939_B       (0x18FEC100u)   /**< PGN 0xFEC1 */
#define CAN_HW_ID_J1939_C       (0x18FEB100u)   /**< PGN 0xFEB1 */
#define CAN_HW_ID_J1939_D       (0x18FEA100u)   /**< PGN 0xFEA1 */

/**
 * @brief J1939 的 PGN 掩码：保留高 21 位，忽略最低 8 位（源地址）
 * @note  0x1FFFFFFF 是全掩码（ID 必须完全一致）；0x1FFFFF00 才允许源地址变化。
 */
#define CAN_HW_MASK_J1939_PGN   (0x1FFFFF00u)

/* ============================ [ M14：通信矩阵压测 ] ============================ */
/*
 * @section HWCFG_WHY_SEG 为什么是"段掩码"而不是"一条报文一个邮箱"
 *
 * Foton 通信矩阵有 49 条 J1939 报文。直觉做法是配 49 个邮箱，但那是错的：
 *
 *   1. **容量**：CAN0 的 `canRamNum=3` → 3 × 512 B / 16 B = 96 个邮箱，
 *      49 条 + TX + 诊断确实放得下，但 RAM 会被吃掉一半，而**没有任何收益**；
 *   2. **中断**：96 个邮箱要按 16 个一组共用中断线，配到 49 个就得开
 *      `CAN0_ORed_16_31_MB_Handler`、`_32_47_`、`_48_63_` 三条，每条都要遍历整组；
 *   3. **J1939 语义**：同一 PGN 的不同源地址本来就该由**上层**按 SA 区分，
 *      硬件层根本不需要知道有几种 SA。
 *
 * 所以正确做法是**按 PGN 段分组**：`0x18FFxxxx` 一个邮箱、
 * `0x18FExxxx` 一个邮箱，覆盖几十条报文，由 CanIf 的软件掩码再细分到具体 PGN。
 * 本工程实测：**49 条报文只需要 2~3 个接收邮箱**。
 *
 * @note 掩码 `0x1FFF0000` 保留 bit28-16（优先级 + PGN 高 8 位），
 *       忽略 bit15-0（PS 与 SA）。这意味着**同一 PGN 段内所有源地址、
 *       所有低字节都会被这个邮箱收进来** —— 正是我们要的。
 *
 * @warning 硬件掩码必须比软件掩码**宽**。若硬件只放行某一个 PGN，
 *          CanIf 里为其它 PGN 配的过滤项永远收不到帧，而且没有任何报错 ——
 *          症状是"配了 20 条，只有 1 条能收到"。
 */

/** @brief J1939 段 `0x18FFxxxx`：PGN 0xFF00~0xFFFF 全部（车辆/灯光/门锁/雨刮…） */
#define CAN_HW_ID_J1939_SEG_FF  (0x18FF0000u)

/** @brief J1939 段 `0x18FExxxx`：PGN 0xFE00~0xFEFF 全部（车速 FEF1 / 里程 FEE0…） */
#define CAN_HW_ID_J1939_SEG_FE  (0x18FE0000u)

/** @brief 段掩码：保留 bit28-16，忽略 PS 与 SA */
#define CAN_HW_MASK_J1939_SEG   (0x1FFF0000u)

/* ---- M14：8 邮箱现实下的极限压缩 ---- */
/*
 * @section HWCFG_8MB 这颗 FlexCAN 只有 **8 个邮箱**（mb0~mb7）
 *
 * 这一条是实测出来的，与 SDK 的计算不符：
 *
 * @code
 * FlexCanDrv_Configure():  msgBufNum = (512 / 16) * 3 = 96
 * !e 读到:                 MCR = 0x00830060 → MAXMB = 0x60 = 96
 * 实测:                    mb0~mb7 正常，mb8 及以上**一条帧都收不到**
 * @endcode
 *
 * 排查过程值得记下来，因为它伪装了两次：
 *  - 第一次把标准帧段配到 mb15/16/17，结果三条全哑，而同一套掩码放 mb15 时
 *    测试通过（0x0A0 段）—— 让人以为是掩码问题；
 *  - 把标准帧挪到 mb7/8/9 后，mb7 通、mb8/9 哑 —— 才确定是**编号上限**，不是掩码。
 *
 * 症状永远是"某几条报文静默收不到"，没有任何报错，`!e` 的错误计数也不涨。
 *
 * @warning 结论：**CAN0 可用邮箱 = mb0~mb7**。规划时按 8 个算，不要看 MAXMB。
 *          8 个邮箱要分给 TX（诊断响应 / NM / 业务）与 RX（诊断请求 / NM /
 *          J1939 / 标准帧），一个都不能浪费 —— 这就是下面用"超级段掩码"的原因。
 */

/**
 * @brief J1939 **全段**：只匹配 bit28-24（优先级 6 + DP/EDP=0），忽略 PGN 与 SA
 * @note  `0x18xxxxxx` 是 J1939 最常用的优先级段（P=6）。掩码 `0x1F000000`
 *        只保留 bit28-24，所以 `0x18FF0110`、`0x18FEE000`、`0x18FEA100`
 *        全部落进同一个邮箱，由 CanIf 按 PGN 细分。
 *
 * @warning 这个掩码会把**所有优先级 6 的扩展帧**都收进来（包括本工程不用
 *          的 PGN）。这是 8 邮箱约束下的必要代价：宁可多收进来让软件过滤，
 *          也不能因为邮箱不够而漏收。压测时正好用它检验软件过滤的分发能力。
 */
#define CAN_HW_ID_J1939_ALL     (0x18000000u)
#define CAN_HW_MASK_J1939_ALL   (0x1F000000u)

/**
 * @brief 标准帧**全段**：`0x000~0x3FF`（11 位标准 ID 的全部）
 *
 * @details 8 邮箱下标准帧只能占一个邮箱，而 BCM 的私有报文散落在
 *          0x0A0 / 0x100 / 0x110 / 0x201 / 0x321 —— 跨度覆盖整个标准 ID 空间，
 *          唯一的办法是一次全收，靠 CanIf 精确分发。
 *
 * @note 诊断请求 0x7E0 与 NM 0x500 **不在** 0x000~0x3FF 内，各自独立邮箱，
 *       所以不会被这个"全收"邮箱抢走。
 * @note 本机自发的心跳 0x123 / Com 0x200 不会进这个邮箱 ——
 *       `MCR.SRXDIS` 默认禁用自收。
 */
#define CAN_HW_ID_STD_ALL       (0x000u)
#define CAN_HW_MASK_STD_ALL     (0x400u)

/**
 * @brief J1939 段内**最大 PGN**：0x18FFFF00（PGN 0xFFFF，SA=0）
 * @note  原来写的是 29 位 ID 极值 `0x1FFFFF00`（优先级 7），但它的优先级
 *        不属于 `0x18` 段，会被 J1939 全段邮箱拒之门外 —— 这是配错，
 *        不是漏配。改用"段内最大"来验二分查找的右边界，语义不变。
 */
#define CAN_HW_ID_J1939_MAXPGN  (0x18FFFF00u)

/* ---- 标准帧（BCM 私有报文段）：同样用区间掩码合并 ---- */

/**
 * @brief 标准帧 ID 在 FlexCAN 寄存器里的位移
 *
 * @details `MESSAGE_BUFFER_ID_STD_ID_SHIFT = 18`（`sdk/reg/flexcan_reg.h:76`）：
 *          FlexCAN 把 11 位标准 ID 存在 ID 字的 **bit[28:18]**，而扩展帧
 *          存在 bit[28:0]（位移 0）。**掩码必须与 ID 处在同一位置**。
 *
 * @warning @parblock
 *          **标准帧的硬件掩码必须自己左移 18 位，SDK 不会帮你移** ——
 *          `FlexCanReg_SetRxIndividualMask()` 就是一句
 *          `obj->RXIMR[num] = mask;`（`flexcan_reg.h:3190`），原样写入。
 *
 *          传 11 位的 `0x7F8` 会发生什么：它落在 bit[10:3]，而 ID 域那几位
 *          **恒为 0**，于是硬件比对 `(来帧 & 0x7F8) == (邮箱ID & 0x7F8)`
 *          退化成 `0 == 0` —— 这个邮箱变成**全收邮箱**。
 *          FlexCAN 把一帧投给**编号最小的匹配邮箱**，所以排在它后面的
 *          同类邮箱一条都收不到，而且**没有任何报错、没有任何异常标志**。
 *
 *          M14 就是这么丢的：mb7 配了未移位的 `0x7F8`，结果 mb8/9/12/14
 *          四条全哑，症状表现为"某些报文收不到"而不是"配错了"。
 *          排查时一度误判成"这颗芯片只有 8 个邮箱"，直到发现早前 mb15
 *          当全收邮箱时是好的、才推翻了这个错误结论。
 *          @endparblock
 *
 * @note **软件层用的是 11 位原值。** `CanIf_Cfg.c` 里表的 `mask` 字段直接
 *       与 `canid`（未移位）比对，所以那里写 `0x7F8`。
 *       同一个语义、两个不同的数值 —— 这是本工程唯一一处
 *       "硬件值 ≠ 软件值"的配置，改一处必须同时改另一处。
 */
#define CAN_HW_STD_ID_SHIFT     (18u)

/** @brief 快变模拟量段 0x0A0~0x0A7（10 ms 周期，压中断用） */
#define CAN_HW_ID_STD_FAST      (0x0A0u)
/** @brief 硬件掩码：0x7F8 << 18 = 0x1FE00000（bit[28:21] 比对，低 3 位无关） */
#define CAN_HW_MASK_STD_FAST    (0x7F8u << CAN_HW_STD_ID_SHIFT)

/** @brief 灯光控制段 0x100~0x107 */
#define CAN_HW_ID_STD_LIGHT     (0x100u)
/** @brief 硬件掩码：同上，0x1FE00000 */
#define CAN_HW_MASK_STD_LIGHT   (0x7F8u << CAN_HW_STD_ID_SHIFT)

/** @brief 车身状态 0x110（单条，精确匹配） */
#define CAN_HW_ID_STD_BODY      (0x110u)

/*
 * 曾经在这里定义过 `CAN_HW_ID_J1939_MAXID = 0x1FFFFF00`（优先级 7 的 29 位极值），
 * 想用它验二分查找的右边界。**这个 ID 用不了**：它的 bit[28:16] 是 `0x1FFFF`，
 * 而 J1939 全段邮箱的掩码 `0x1FFF0000` 要求 bit[28:16] 必须是 `0x18FF0` ——
 * 硬件根本不会把这帧放进邮箱，软件表配得再对也收不到。
 * 验右边界改用 `CAN_HW_ID_J1939_MAXPGN`（段内最大 PGN），语义不变。
 */

/* ---- M9：CAN 网络管理（CanNm）---- */

/**
 * @brief NM 报文 ID：0x500，标准帧，8 字节
 *
 * @details @section CANHWCFG_NMID 为什么是 0x500
 *
 *          AUTOSAR 没有规定 NM 的 CAN ID，它由**整车网络设计**给定。
 *          常见分配是 0x400 / 0x500 / 0x600 段，避开车身信号区（0x000~0x3FF）
 *          和诊断区（0x7E0~0x7EF）。
 *
 *          本工程取 0x500 只是"一个不冲突的占位值"。接 Foton 项目时
 *          必须换成通信矩阵里给的 NM 报文 ID —— 猜错的现象是
 *          **板子自己发得挺欢，但整车网络里没人理它**（因为大家都在别的 ID 上）。
 *
 * @note TX 和 RX 用同一个 ID：NM 是"一方发送、多方接收"的广播语义，
 *       标准做法就是所有节点在同一个 ID 上收发。
 *       本机发出的帧不会被自己的接收邮箱收到（FlexCAN 的 `MCR.SRXDIS` 默认禁用自收），
 *       所以这条不会自激。
 */
#define CAN_HW_ID_NM            (0x500u)

/* ---- M10：Com 信号层测试报文 ---- */

/**
 * @brief 信号发送报文：0x200（本节点 → 总线，100 ms）
 * @note  接收用 **0x201**，不是同一个 ID。
 *
 *        最初为了"一路 Kvaser 同时看收发"把两者写成同一个 ID，
 *        结果是**没法做接收测试**：板子每 100 ms 也在发 0x200，
 *        Kvaser 一注入就撞车 —— 同 ID 同优先级，仲裁必然让一方
 *        反复重发，错误计数一路涨，抓到的帧内容也会互相污染。
 *
 *        拆开之后 TX/RX 互不干扰，也才符合真实总线（一个 ID 只有一个发送者）。
 */
#define CAN_HW_ID_COM_TX        (0x200u)

/** @brief 信号接收报文：0x201（总线 → 本节点） */
#define CAN_HW_ID_COM_RX        (0x201u)

/* ---- CAN1（通信 2）：与 CAN0 用不同 ID，Kvaser 上一眼能分清是哪一路 ---- */

/** @brief CAN1 发送：0x124（CAN0 是 0x123） */
#define CAN_HW_ID_CAN1_TX       (0x124u)

/** @brief CAN1 接收：0x322（CAN0 是 0x321） */
#define CAN_HW_ID_CAN1_RX       (0x322u)

/* ---- M3 诊断（ISO 15765-2 物理寻址）---- */

/** @brief 诊断请求（测试仪 → ECU）：0x7E0 */
#define CAN_HW_ID_DIAG_REQ      (0x7E0u)

/** @brief 诊断响应（ECU → 测试仪）：0x7E8 */
#define CAN_HW_ID_DIAG_RESP     (0x7E8u)

/* ============================ [ 类型 ] ============================ */

/**
 * @brief 邮箱方向
 * @note  取值刻意与 `FlexCanDrv_MsgType_t` 一致（TX=0, RX=1），翻译时可直接强转；
 *        这样写是为了让 `CanAc.c` 的翻译代码不用 switch。改 SDK 枚举顺序时这里要跟着改。
 */
typedef enum {
	CAN_HW_MB_TX = 0,   /**< 发送邮箱 */
	CAN_HW_MB_RX = 1    /**< 接收邮箱 */
} CanHw_MbDirType;

/**
 * @brief 单个邮箱的配置（中性类型，不含任何厂商类型）
 * @note  字段顺序与 `FlexCanDrv_MsgCfgType` 一一对应，但不是同一个类型 ——
 *        翻译在 `CanAc_TranslateMsgCfgs()` 里一次完成，运行期不再转换。
 */
typedef struct {
	uint16_t       msgBufId;        /**< 邮箱号（0 起） */
	uint16_t       msgBufLen;       /**< 邮箱深度，1=单帧；>1 表示同一邮箱收多帧 */
	uint32_t       msgId;           /**< 帧 ID（11 位或 29 位，由 isExt 决定） */
	bool           isExt;           /**< true=29 位扩展帧 */
	CanHw_MbDirType dir;            /**< 发送 / 接收 */
	uint8_t        dlc;             /**< 数据长度 0..8（经典 CAN） */
	bool           intEnable;       /**< RX 是否使能邮箱中断；TX 恒为 false */
	uint32_t       individualMask;  /**< RX 独立掩码；0xFFFFFFFF = ID 必须完全一致 */
} CanHw_MsgCfgType;

/**
 * @brief 硬件发送对象（HTH）：`Can_Write()` 的 `Hth` 即本表下标
 *
 * @warning **一个 HTH 只能发一个固定 ID**。厂商 `FlexCanDrv_SetTxMsg()` 只写数据区，
 *          不回写 ID 与 DLC（见 `flexcan_drv.c:1494`），所以 ID 在 `CfgMsgObj` 时就定死了。
 *          要发 N 条不同 ID 的报文，就得有 N 个 HTH + N 个邮箱。
 *          这条约束在 96 个邮箱的容量下不构成问题（BCM 的 TX 报文远少于 96）。
 */
typedef struct {
	uint8_t  controller;    /**< 0=CAN0, 1=CAN1 */
	uint16_t msgBufId;      /**< 该 HTH 占用的邮箱号 */
	uint32_t canId;         /**< 该邮箱的固定 ID（`Can_Write` 校验用） */
	uint8_t  dlc;           /**< 该邮箱固定 DLC（`Can_Write` 补齐用） */
} CanHw_HohType;

/** @brief 一个通道的邮箱表 */
typedef struct {
	const CanHw_MsgCfgType *cfgs;   /**< 邮箱配置数组 */
	uint8_t                 num;    /**< 数组长度 */
} CanHw_MsgTableType;

/* ============================ [ HTH 编号 ] ============================ */
/*
 * CanIf_Cfg.c 的 `hoh` 字段直接引用这些宏 —— 两处硬编码变成一个宏，
 * 邮箱表改号时不会出现"CanIf 指向了别的邮箱"这类静默错误。
 */

/** @brief HTH 0：CAN0 心跳帧 0x123 */
#define CAN_HW_HTH_CAN0_HEARTBEAT   (0u)

/** @brief HTH 1：CAN0 扩展帧 0x18FF0002 */
#define CAN_HW_HTH_CAN0_EXT_TX      (1u)

/** @brief HTH 2：CAN1 心跳帧 0x124 */
#define CAN_HW_HTH_CAN1_HEARTBEAT   (2u)

/** @brief HTH 3：CAN0 诊断响应 0x7E8（M3） */
#define CAN_HW_HTH_DIAG_RESP        (3u)

/**
 * @brief HTH 4：CAN0 网络管理报文 0x500（M9）
 * @note  NM 报文是周期发送的，`CanNm` 每 200 ms 调一次 `CanIf_Transmit()`。
 *        固定 ID 的约定见上面 `@warning` —— `SetTxMsg()` 只写数据区，
 *        所以 0x500 必须在 `CfgMsgObj()` 时就绑死在这个邮箱上。
 */
#define CAN_HW_HTH_NM               (4u)

/**
 * @brief HTH 5：CAN0 信号报文 0x200（M10）
 * @note  Com 每 100 ms 发一次。同样受"一个 HTH 只能发一个固定 ID"的约束。
 */
#define CAN_HW_HTH_COM              (5u)

/** @brief HTH 表长度 */
#define CAN_HW_HOH_NUM              (6u)

/* ============================ [ 表 ] ============================ */

/** @brief 每个通道的邮箱表，下标 = 通道号 */
extern const CanHw_MsgTableType CanHw_MsgTables[CAN_CFG_NUM_CHANNELS];

/** @brief HTH 表，下标 = `Can_Write()` 的 `Hth` */
extern const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM];

#endif /* CAN_HWCFG_H */
