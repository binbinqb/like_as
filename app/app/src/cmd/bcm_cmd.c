/**
 * @file    bcm_cmd.c
 * @brief   `bcm` 命令：灯状态绑定层的设置与回读（M23）
 *
 * @details @section BCMCMD_WHY 为什么这条命令是 M23 的验收手段
 *
 *          绑定层全部价值在于"**业务语义 ↔ 总线 raw**"的映射方向没搞反。
 *          而映射搞反了**编译不会报错、日志也不会报错** ——
 *          只会让 `ON` 出现在总线的 `Fault` 位上。
 *
 *          所以这条命令刻意让三样东西同时出现在屏幕上：
 *          1. 业务侧看到的语义（`BcmSig_TxGet`）
 *          2. Com 发送缓冲里**此刻的真实字节**（`Com_Config.IPduConfigs[].ptr`）
 *          3. 用 Kvaser 抓到的帧（屏幕外）
 *
 *          三者对上，映射就是对的。用 `bcm all on` 一条命令就能一次性
 *          验证 11 个信号的位偏移 + 位序 + 映射方向，比逐个试快得多。
 *
 *          @section BCMCMD_EXPECT 期望值（11 个信号全设同一状态时的 LCSF 帧）
 *
 *          `BCM_LCSF` 0x18FE4021，11 个信号全为 2 bit 小端，位偏移分别是
 *          4/6/8/12/14/24/30/32/44/46/48。全设一档时整帧应为：
 *
 *          | 命令 | 期望 8 字节 |
 *          |------|-------------|
 *          | `bcm all off`     | `00 00 00 00 00 00 00 00` |
 *          | `bcm all on`      | `50 51 00 41 01 50 01 00` |
 *          | `bcm all fault`   | `A0 A2 00 82 02 A0 02 00` |
 *          | `bcm all unknown` | `F0 F3 00 C3 03 F0 03 00` |
 *
 *          **任何一个字节不对**，说明位偏移、位序、或映射方向有一个错。
 *          这四行是手算的，`bcm` 命令会把实测字节打在旁边直接对比。
 *
 * @author  binbina
 * @version V1.0.0
 */

#if !defined(SH_DISABLE_CMD_BCM)

#include "sh_cfg.h"          /* SH_EXPORT_CMD / SH_OK / SH_ERR_PARAM */
#include "bcm_sig.h"         /* 绑定层公共接口（业务侧唯一该 include 的头） */
#include "platform_cvm0146.h" /* Platform_Printf */
#include "Com.h"             /* Com_SignalIdType / Com_ConfigType（Com_Priv.h 依赖它） */
#include "Com_Cfg.h"         /* COM_CAN1_BCM_LCSF_TX */
#include "Com_Priv.h"        /* Com_Config：读发送缓冲里的真实字节 */

#include <string.h>
#include <stdbool.h>

/** @brief Com 的总配置表（`Com_Cfg.c` 里定义，生成物，只读） */
extern const Com_ConfigType Com_Config;

/* ============================ [ 名字表 ] ============================ */

/** @brief 一个灯的短名与业务编号（供命令行解析用） */
typedef struct
{
	const char *name;   /**< 命令行里用的短名 */
	Bcm_SigIdType id;   /**< 业务编号 */
} BcmCmd_LampType;

/**
 * @brief 名字 → 编号（命令解析用，**顺序无关**）
 * @note  这张表只管"用户输入哪个词对应哪个编号"，顺序随便排，
 *        按人的记忆习惯来（近光/远光/前雾/后雾/左转/右转…）。
 */
static const BcmCmd_LampType s_lamp[] =
{
	{ "low",   BCM_SIG_LOW_BEAM },   /* 近光 */
	{ "high",  BCM_SIG_HIGH_BEAM },  /* 远光 */
	{ "fogf",  BCM_SIG_FRONT_FOG },  /* 前雾 */
	{ "fogr",  BCM_SIG_REAR_FOG },   /* 后雾 */
	{ "turnl", BCM_SIG_TURN_L },     /* 左转 */
	{ "turnr", BCM_SIG_TURN_R },     /* 右转 */
	{ "drl",   BCM_SIG_DRL },        /* 日行 */
	{ "pos",   BCM_SIG_POSITION },   /* 位置灯 */
	{ "rev",   BCM_SIG_REVERSE },    /* 倒车 */
	{ "brake", BCM_SIG_BRAKE },      /* 制动 */
	{ "int",   BCM_SIG_INTERIOR }    /* 室内 */
};

/**
 * @brief 编号 → 名字（dump 用，**顺序必须与 `Bcm_SigIdType` 一致**）
 *
 * @note  为什么要两张表而不是一张：`s_lamp` 是"名字找编号"，
 *        遍历时要按下标取值就得保证顺序，而它的顺序按人记忆习惯排的，
 *        **和枚举不同**。早先只用一张表时，`dumpAll()` 会把
 *        "后雾"打成"右转" —— 名字错位不会报错，只会让人看错数据。
 *
 *        这里补一张按枚举下标排的表，`bcm_sig_cfg.c` 的表长断言
 *        只保证行数对得上；名字的顺序由下面这行注释 + 代码评审保证。
 */
static const char *const s_lampNameById[BCM_SIG_TX_NUM] =
{
	"low",   /* BCM_SIG_LOW_BEAM */
	"high",  /* BCM_SIG_HIGH_BEAM */
	"fogf",  /* BCM_SIG_FRONT_FOG */
	"turnr", /* BCM_SIG_TURN_R */
	"turnl", /* BCM_SIG_TURN_L */
	"drl",   /* BCM_SIG_DRL */
	"pos",   /* BCM_SIG_POSITION */
	"fogr",  /* BCM_SIG_REAR_FOG */
	"rev",   /* BCM_SIG_REVERSE */
	"brake", /* BCM_SIG_BRAKE */
	"int"    /* BCM_SIG_INTERIOR */
};

_Static_assert((sizeof(s_lampNameById) / sizeof(s_lampNameById[0])) ==
               (size_t)BCM_SIG_TX_NUM,
               "s_lampNameById 项数与 BCM_SIG_TX_NUM 不一致");

/* ============================ [ 辅助 ] ============================ */

/**
 * @brief 语义值的可读名字
 * @param[in] st 语义值
 * @return 静态字符串（永不返回 NULL，越界给 "?"）
 */
static const char *stateName(Bcm_SwStateType st)
{
	static const char *const s_names[] = { "UNKNOWN", "OFF", "ON", "FAULT" };

	return ((uint32_t)st <= (uint32_t)BCM_SW_STATE_FAULT) ? s_names[st] : "?";
}

/**
 * @brief 解析状态字符串
 * @param[in]  s   命令行参数（`on` / `off` / `fault` / `unknown`）
 * @param[out] out 解析结果
 * @retval true  解析成功
 * @retval false 无法识别
 * @note  大小写敏感（letter-shell 不做归一），与工程其他命令一致。
 */
static bool parseState(const char *s, Bcm_SwStateType *out)
{
	bool ok = true;

	if (strcmp(s, "on") == 0)
	{
		*out = BCM_SW_STATE_ON;
	}
	else if (strcmp(s, "off") == 0)
	{
		*out = BCM_SW_STATE_OFF;
	}
	else if (strcmp(s, "fault") == 0)
	{
		*out = BCM_SW_STATE_FAULT;
	}
	else if (strcmp(s, "unknown") == 0)
	{
		*out = BCM_SW_STATE_UNKNOWN;
	}
	else
	{
		ok = false;
	}

	return ok;
}

/**
 * @brief 打印 `BCM_LCSF` 发送缓冲里的真实字节
 *
 * @details 直接读 Com 的 IPdu 缓冲（`ptr`），**不经任何转换** ——
 *          这里要的就是"二进制长什么样"，一旦经过本层反而看不出映射对不对。
 */
static void dumpLcsfBytes(void)
{
	const Com_IPduConfigType *p = &Com_Config.IPduConfigs[COM_CAN1_BCM_LCSF_TX];
	const uint8_t *b = (const uint8_t *)p->ptr;
	uint8_t i;

	Platform_Printf("  LCSF(0x18FE4021) buf =");
	for (i = 0u; (i < p->length) && (i < 8u); i++)
	{
		Platform_Printf(" %02X", (unsigned)b[i]);
	}
	Platform_Puts("\n");
}

/**
 * @brief 有效性状态的可读名字
 * @param[in] v 有效性
 * @return 静态字符串（永不返回 NULL）
 */
static const char *validityName(Bcm_SigValidityType v)
{
	static const char *const s_names[] = { "VALID", "INVALID", "TIMEOUT", "NEVER" };

	return ((uint32_t)v <= (uint32_t)BCM_SIG_NEVER_RECEIVED) ? s_names[v] : "?";
}

/**
 * @brief 打印接收侧的"值 + 有效性 + 到达年龄"
 *
 * @details 这三项一起打是有原因的：只看值无法区分四种情况，
 *          而它们的排查方向完全不同 ——
 *
 *          | 看到 | 说明 | 下一步查什么 |
 *          |------|------|--------------|
 *          | `VALID` | 正常 | — |
 *          | `INVALID`（age 很小） | 帧在，但对方的值落在无效枚举 | 查发送方状态 |
 *          | `TIMEOUT`（age 很大） | 收到过，后来断了 | 查线束/发送方掉电 |
 *          | `NEVER`（age = --） | 上电至今没收到 | 查波特率/终端电阻/该节点在不在 |
 */
static void dumpRx(void)
{
	Bcm_SwStateType st;
	Bcm_SigValidityType v;
	uint32_t age;

	v = BcmSig_RxRead(BCM_SIG_RX_PARK_BRAKE, &st);
	age = BcmSig_RxAgeMs(BCM_SIG_RX_PARK_BRAKE);

	if (0xFFFFFFFFu == age)
	{
		Platform_Printf("  bcm rx park brake = %-7s [%-7s age=--]\n",
		                stateName(st), validityName(v));
	}
	else
	{
		Platform_Printf("  bcm rx park brake = %-7s [%-7s age=%u ms]\n",
		                stateName(st), validityName(v), (unsigned)age);
	}
}

/**
 * @brief dump 全部灯状态 + 手刹输入 + LCSF 字节
 */
static void dumpAll(void)
{
	uint8_t i;

	Platform_Puts("  bcm tx lamp states (业务语义 / 期望 raw)\n");
	for (i = 0u; i < (uint8_t)BCM_SIG_TX_NUM; i++)
	{
		Bcm_SwStateType st = BcmSig_TxGet((Bcm_SigIdType)i);

		/* 期望 raw 不在这里重算 —— 重算就是在本层之外复制一份映射规则，
		 * 两边一旦不同步，dump 会"自己证明自己正确"。所以只打语义，
		 * raw 由下面那行真实字节回答。 */
		Platform_Printf("   %-6s %s\n", s_lampNameById[i], stateName(st));
	}

	dumpRx();

	dumpLcsfBytes();
}

/* ============================ [ 命令入口 ] ============================ */

/**
 * @brief bcm [lamp|all] [on|off|fault|unknown] —— 灯状态设置与回读
 *
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 *
 * @note  用法：
 *        - `bcm`                  → dump 全部状态 + LCSF 字节
 *        - `bcm rx`               → 只打接收侧的值/有效性/到达年龄（A2）
 *        - `bcm all on`           → 11 个灯全设 ON
 *        - `bcm low on`           → 只设近光灯
 *        - `bcm low on  high off` → 不支持，一次只处理一个灯
 */
static int sh_cmd_bcm(int argc, char *argv[])
{
	Bcm_SwStateType st;
	uint8_t i;

	if (argc < 2)
	{
		dumpAll();
		return SH_OK;
	}

	/* 单参数形式：`bcm rx` 只回答"输入到底有没有来"
	 * （验收脚本里测四态时只想要这一行，不想要 11 个灯刷屏） */
	if (strcmp(argv[1], "rx") == 0)
	{
		dumpRx();
		return SH_OK;
	}

	if (argc < 3)
	{
		sh_puts(SH_RET_PARA);
		return SH_ERR_PARAM;
	}

	if (!parseState(argv[2], &st))
	{
		Platform_Puts("  state must be: on | off | fault | unknown\n");
		return SH_ERR_PARAM;
	}

	if (strcmp(argv[1], "all") == 0)
	{
		for (i = 0u; i < (uint8_t)BCM_SIG_TX_NUM; i++)
		{
			(void)BcmSig_TxSet((Bcm_SigIdType)i, st);
		}
		Platform_Printf("  all lamps -> %s\n", stateName(st));
		dumpLcsfBytes();
		return SH_OK;
	}

	for (i = 0u; i < (uint8_t)ARRAY_SIZE(s_lamp); i++)
	{
		if (strcmp(argv[1], s_lamp[i].name) == 0)
		{
			if (E_OK == BcmSig_TxSet(s_lamp[i].id, st))
			{
				Platform_Printf("  %s -> %s\n", s_lamp[i].name, stateName(st));
				dumpLcsfBytes();
				return SH_OK;
			}
			Platform_Puts("  set failed\n");
			return SH_ERR_PARAM;
		}
	}

	Platform_Puts("  lamp must be: low|high|fogf|fogr|turnl|turnr|drl|pos|rev|brake|int|all\n");
	return SH_ERR_PARAM;
}

SH_EXPORT_CMD(bcm, sh_cmd_bcm, "bcm [lamp|all] [on|off|fault|unknown] -- lamp binding set / dump");

#endif /* !SH_DISABLE_CMD_BCM */
