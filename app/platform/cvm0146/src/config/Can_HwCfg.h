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

/* ---- 真实矩阵：CAN1 整车网按 PF 分组（M19）---- */

/**
 * @section HWCFG_PF_GROUP 按 PDU Format 分组：34 条报文 → 7 个邮箱
 *
 * Foton L1 通信矩阵的 34 条 BCM 接收报文全部是 J1939 扩展帧，且**每条报文的
 * PGN 都不同**（`PS` 字节各不相同）。若一条报文一个邮箱要 34 个；
 * 按 **PF 分组** 只要 7 个：
 *
 * | mb | PF | 覆盖的 PGN | 条数 |
 * |----|----|-----------|------|
 * | 6 | 0xEB | TP.DT（传输协议数据） | 1 |
 * | 7 | 0xEC | TP.CM（传输协议连接管理） | 1 |
 * | 8 | 0xEE | ACL | 1 |
 * | 9 | 0xF0 | EEC1/EEC3/ERC1/ERC3/EBC1/ETC2/CRASH | 6 |
 * | 10 | 0xFD | EOI/DLCC1/EBC5 | 3 |
 * | 11 | 0xFE | CCVS/CCVS1/VDC1/AMB/TCO1/DM1_TPMS/TIRE_COND/ETC5 | 8 |
 * | 12 | 0xFF | ESCL1/ESCLM/PEPS1/PEPS2/ID1~3/DW/EEC3/ECC2/VCU4/ESCL_NM | 14 |
 *
 * 软件层（CanIf）再用 `0x1FFFFF00` 精确到 PGN，屏蔽源地址 —— 有些 PGN
 * 矩阵里就是**同 PGN 多个 SA**（如 0xFEF1 有 SA=0x00 和 0x21 两条）。
 *
 * @warning **掩码必须屏蔽优先级 bit28:26。** 矩阵里同一条报文的优先级从 3 到 6
 *          都有（`0x0CF00400` 是 P=3、`0x18FEF100` 是 P=6）。若沿用 CAN0 测试
 *          通道的 `0x1FFF0000`（含 bit28:26），P 不一致的帧会被硬件直接丢掉，
 *          且**没有任何报错** —— 症状是"某些 PGN 收得到、某些收不到"。
 *
 * @note 掩码取 `0x00FF0000` 而不是 `0x03FF0000`：后者会额外要求
 *       bit25(R 保留位) 与 bit24(DP 数据页) 匹配 0。当前矩阵全是 DP=0，
 *       但 J1939 里 DP=1 的 PGN（`0x1xxxxx`）是合法存在的，
 *       屏蔽掉两位可以让硬件层对未来扩展免疫 —— 硬件宽、软件窄。
 */
#define CAN_HW_MASK_J1939_PF    (0x00FF0000u)

/** @brief PF=0xEB：J1939 TP.DT（传输协议数据传送，多帧载荷） */
#define CAN_HW_ID_PF_EB         (0x18EB0000u)
/** @brief PF=0xEC：J1939 TP.CM（传输协议连接管理，多帧握手） */
#define CAN_HW_ID_PF_EC         (0x18EC0000u)
/** @brief PF=0xEE：ACL（0x98EEFF00，SA=0x00） */
#define CAN_HW_ID_PF_EE         (0x18EE0000u)
/** @brief PF=0xF0：发动机/制动/变速箱相关（EEC1、ERC1、EBC1…） */
#define CAN_HW_ID_PF_F0         (0x18F00000u)
/** @brief PF=0xFD：直接灯控/制动（DLCC1、EOI、EBC5） */
#define CAN_HW_ID_PF_FD         (0x18FD0000u)
/** @brief PF=0xFE：车速/环境/胎压（CCVS、AMB、VDC1、TCO1…） */
#define CAN_HW_ID_PF_FE         (0x18FE0000u)
/** @brief PF=0xFF：BCM 相关（ESCL、PEPS、ID1~3、DW、VCU） */
#define CAN_HW_ID_PF_FF         (0x18FF0000u)

/* ---- 真实矩阵：CAN1 的 6 条发送报文（BCM → 总线）---- */

/** @brief 0x18FE4021 BCM_LCSF：灯光控制状态反馈 */
#define CAN_HW_ID_TX_LCSF       (0x18FE4021u)
/** @brief 0x18FF0C21 BCM_CTRL：车身控制命令 */
#define CAN_HW_ID_TX_CTRL       (0x18FF0C21u)
/** @brief 0x0CFDCC21 BCM_OEL：外部照明（P=3，高优先级） */
#define CAN_HW_ID_TX_OEL        (0x0CFDCC21u)
/** @brief 0x18FDCD21 BCM_OWW：雨刮/洗涤 */
#define CAN_HW_ID_TX_OWW        (0x18FDCD21u)
/** @brief 0x18FE4E21 BCM_DOOR_CTRL：门锁控制 */
#define CAN_HW_ID_TX_DOOR       (0x18FE4E21u)
/** @brief 0x18FECA21 BCM_DM1：诊断信息（TPMS 相关） */
#define CAN_HW_ID_TX_DM1        (0x18FECA21u)

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
	bool           intEnable;       /**< 是否使能邮箱中断。
	                                     **TX 也必须为 true**：发送完成中断是
	                                     `CanAc.c` 里 `s_txPending[]` 的**唯一**
	                                     释放点，它同时驱动 `CanIf_TxConfirmation()`。
	                                     置 false 的症状极隐蔽：该邮箱能发出
	                                     **第一帧**，之后 `Can_Write()` 永远返回
	                                     `CAN_BUSY`，上层只看得到"周期报文不发、
	                                     bTxRetry 恒为 1"。2026-11-18 在 mb11/mb13
	                                     （0x500 / 0x200）上踩过，见
	                                     `doc/设计评审/Com周期发送异常.md`。 */
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

/* ---- M19：CAN1 真实矩阵的 6 条发送报文 ---- */
/*
 * 为什么从 6 开始而不是从 2 开始重排：HTH 2 已经被 CAN1 的测试心跳 0x124
 * 占用（M8 验证过），把它挪走会让 `CanTest_SendCan1()` 与 M8 回归脚本失效。
 * **追加编号比重排便宜** —— HTH 只是表下标，中间不空就行。
 */

/** @brief HTH 6：CAN1 `0x18FE4021` BCM_LCSF（灯光控制状态反馈） */
#define CAN_HW_HTH_CAN1_LCSF        (6u)

/** @brief HTH 7：CAN1 `0x18FF0C21` BCM_CTRL（车身控制命令） */
#define CAN_HW_HTH_CAN1_CTRL        (7u)

/** @brief HTH 8：CAN1 `0x0CFDCC21` BCM_OEL（外部照明，P=3 高优先级） */
#define CAN_HW_HTH_CAN1_OEL         (8u)

/** @brief HTH 9：CAN1 `0x18FDCD21` BCM_OWW（雨刮/洗涤） */
#define CAN_HW_HTH_CAN1_OWW         (9u)

/** @brief HTH 10：CAN1 `0x18FE4E21` BCM_DOOR_CTRL（门锁控制） */
#define CAN_HW_HTH_CAN1_DOOR        (10u)

/** @brief HTH 11：CAN1 `0x18FECA21` BCM_DM1（诊断信息） */
#define CAN_HW_HTH_CAN1_DM1         (11u)

/** @brief HTH 表长度
 *  @warning 必须等于 `Can/Can.json` 里所有 TX 邮箱的条数。
 *          偏大不会报错——数组尾部补 0 条目，而 0 条目恰好是
 *          `{ctrl0, mb0, id0}`，等于**把 HTH0 覆盖成空邮箱**，表现为
 *          "心跳帧发不出去"；偏小是编译错误。
 *          一致性由 `tools/can_table_check.py` 校验。 */
#define CAN_HW_HOH_NUM              (12u)

/* ============================ [ 表 ] ============================ */

/** @brief 每个通道的邮箱表，下标 = 通道号 */
extern const CanHw_MsgTableType CanHw_MsgTables[CAN_CFG_NUM_CHANNELS];

/** @brief HTH 表，下标 = `Can_Write()` 的 `Hth` */
extern const CanHw_HohType CanHw_Hohs[CAN_HW_HOH_NUM];

#endif /* CAN_HWCFG_H */
