/**
 * @file    pwm_cmd.c
 * @brief   `pwm` 命令：演示扫描 / 恢复初值 / 单通道设占空比
 *
 * @details 从 `main.c` 的 `PwmCmd_Exec()` 迁来（M-Shell 命令迁移）。
 *
 *          为什么需要它：`Pwm` 模块像 `Adc` 一样，**编译通过不等于代码在跑** ——
 *          没有调用点时整模块被 `--gc-sections` 丢弃，镜像里不会有 `Pwm_*` 符号。
 *
 *          演示序列刻意做成**肉眼可见**：开发板 PTD0/PTE15/PTE16 各接 RGB 灯
 *          一个通道，改占空比直接看到颜色/亮度，不需要示波器。
 *
 * @note    用法：
 *          - `pwm`               演示（6 步，约 2.5 s）
 *          - `pwm reset`         恢复配置表初值
 *          - `pwm <ch> <pct>`    单通道设占空比（pct 0~100）
 *
 * @warning `pwm` 演示用忙等延时（`Platform_NowMs`）。若之前执行过
 *          `ecum sleep`（STOP 模式停过 tick），tick 恢复前不要发本命令，
 *          否则会死等。
 *
 * @author  binbina
 * @version V1.0.0
 */

#include "sh.h"
#include "platform_cvm0146.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"

/**
 * @brief 忙等若干毫秒
 * @param[in] ms 毫秒数
 * @note 只用于验收命令，不做业务逻辑 —— 忙等会占满 CPU。
 */
static void pwm_cmd_delay_ms(uint32_t ms)
{
	uint32_t t0 = Platform_NowMs();

	while ((Platform_NowMs() - t0) < ms) {
		/* 空转等待 */
	}
}

/**
 * @brief 百分比 → 0x8000 满量程占空比
 * @param[in] pct 0~100（>100 按 100）
 * @return 占空比
 * @note 换算只在这一处做，避免每个调用点各写一遍。
 */
static Pwm_DutyCycleType pwm_cmd_pct(uint32_t pct)
{
	if (pct > 100u) {
		pct = 100u;
	}
	return (Pwm_DutyCycleType)((pct * 0x8000u) / 100u);
}

/** @brief 恢复配置表初值 */
static void pwm_cmd_restore(void)
{
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP, pwm_cmd_pct(0u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST1, pwm_cmd_pct(50u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2, pwm_cmd_pct(25u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3, pwm_cmd_pct(75u));
}

/**
 * @brief pwm [reset | <ch> <pct>] —— PWM 验收命令
 * @param[in] argc 参数个数
 * @param[in] argv 参数数组
 * @return 0 成功；非 0 失败
 */
static int sh_cmd_pwm(int argc, char *argv[])
{
	uint16_t i;

	if ((argc == 2) && (argv[1][0] == 'r')) {   /* reset */
		pwm_cmd_restore();
		sh_puts("<+0, pwm restored: ch0=0% ch1=50% ch2=25% ch3=75%\r\n");
		return SH_OK;
	}

	if (argc == 3) {
		uint32_t ch, pct;

		if (!sh_parse_u32(argv[1], &ch) || (ch >= (uint32_t)PWM_CFG_NUM_CHANNELS) ||
		    !sh_parse_u32(argv[2], &pct) || (pct > 100u)) {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
		Pwm_SetDutyCycle((Pwm_ChannelType)ch, pwm_cmd_pct(pct));
		sh_print("<+0, pwm ch%u = %u%%\r\n", (unsigned)ch, (unsigned)pct);
		return SH_OK;
	}

	sh_print("  pwm: %u ch @ 100Hz on PwmLite0  init=%s\r\n",
	         (unsigned)PWM_CFG_NUM_CHANNELS,
	         Pwm_IsInitialized() ? "OK" : "**FAILED**");
	sh_puts("   pad0=PTD0(RED) pad1=PTD1 pad2=PTE15(GREEN) pad3=PTE16(BLUE)\r\n");

	/* 1) 全灭：0% 走静态电平分支，波形上应是恒低而不是极窄脉冲 */
	for (i = 0u; i < (uint16_t)PWM_CFG_NUM_CHANNELS; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)i, pwm_cmd_pct(0u));
	}
	sh_puts("   [1/6] all 0%\r\n");
	pwm_cmd_delay_ms(200u);

	/* 2) 顶灯渐亮：0→100% 分 10 步（真实 IL001 是 20%→90% 用 2.5 s） */
	sh_puts("   [2/6] ch0 ramp 0->100%\r\n");
	for (i = 0u; i <= 10u; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP,
		                 pwm_cmd_pct((uint32_t)i * 10u));
		pwm_cmd_delay_ms(150u);
	}

	/* 3) 绿（PTE15）渐亮 */
	sh_puts("   [3/6] ch2 (GREEN) ramp\r\n");
	for (i = 0u; i <= 5u; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2,
		                 pwm_cmd_pct((uint32_t)i * 20u));
		pwm_cmd_delay_ms(150u);
	}

	/* 4) 蓝（PTE16）渐亮 */
	sh_puts("   [4/6] ch3 (BLUE) ramp\r\n");
	for (i = 0u; i <= 5u; i++) {
		Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3,
		                 pwm_cmd_pct((uint32_t)i * 20u));
		pwm_cmd_delay_ms(150u);
	}

	/* 5) 三色同时 50%：多通道并发，肉眼接近白 */
	sh_puts("   [5/6] RGB all 50%\r\n");
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_DOME_LAMP, pwm_cmd_pct(50u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST2, pwm_cmd_pct(50u));
	Pwm_SetDutyCycle((Pwm_ChannelType)PWM_CFG_CH_TEST3, pwm_cmd_pct(50u));
	pwm_cmd_delay_ms(600u);

	/* 6) 恢复初值 */
	pwm_cmd_restore();
	sh_puts("   [6/6] done, restored\r\n");
	sh_puts(SH_RET_OK);
	return SH_OK;
}

SH_EXPORT_CMD(pwm, sh_cmd_pwm, "pwm [reset | <ch> <pct>] -- demo / restore / set duty");
