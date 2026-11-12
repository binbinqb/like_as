/**
 * @file    adc_cmd.c
 * @brief   `adc` 命令：读一次 ADC 探针组并打印原始值/换算电压
 *
 * @details 从 `main.c` 的 `AdcCmd_Probe()` 迁来（M-Shell 命令迁移）。
 *          存在的意义是**验证链路**，不是业务功能 ——
 *          在它出现之前，Adc 模块虽然编译通过，但整个被 --gc-sections 丢弃了
 *          （没有任何调用点），镜像里连一个 `Adc_*` 符号都没有。
 *
 * @note    用法：`adc`（读全部组）。要读单组加组号即可，如 `adc 0`。
 *
 * @author  binbina
 * @version V1.0.0
 */

#if !defined(SH_DISABLE_CMD_ADC)

#include "sh_cfg.h"   /* 含生成头：SH_DISABLE_CMD_* 与 SH_VERSION_STR */
#include "platform_cvm0146.h"
#include "Adc.h"
#include "Adc_Cfg.h"

/**
 * @brief 读一组并打印
 * @param[in] g 组号（调用方保证 < ADC_CFG_NUM_GROUPS）
 * @return 0 成功；-1 超时/读失败
 */
static int adc_cmd_read_group(uint8_t g)
{
	Adc_ValueGroupType raw[ADC_CFG_MAX_CH_PER_GROUP];
	uint8_t  n = Adc_Cfg_GroupChannels[g];
	Adc_StatusType st;
	uint32_t t0;
	uint8_t  i;

	Adc_StartGroupConversion((Adc_GroupType)g);

	/* 超时 5 ms 是**故意设小**的：一次 12 位转换只要几微秒，
	 * 5 ms 还没完成说明触发链路断了（PDB 未使能 / pretrigger 配错），
	 * 快速失败比慢速等待更容易定位。 */
	t0 = Platform_NowMs();
	do {
		st = Adc_GetGroupStatus((Adc_GroupType)g);
	} while ((st != ADC_COMPLETED) && ((Platform_NowMs() - t0) < 5u));

	if (st != ADC_COMPLETED) {
		sh_print("<-300, adc g%u timeout status=%u (PDB/trigger broken?)\r\n",
		         (unsigned)g, (unsigned)st);
		return -1;
	}

	if (Adc_ReadGroup((Adc_GroupType)g, raw) != E_OK) {
		sh_print("<-300, adc g%u read failed\r\n", (unsigned)g);
		return -1;
	}

	sh_print("  g%u:", (unsigned)g);
	for (i = 0u; i < n; i++) {
		/* 12 位满量程 4095 对应参考电压 3300 mV */
		sh_print(" %u(%umV)", (unsigned)raw[i],
		         (unsigned)(((uint32_t)raw[i] * 3300u) / 4095u));
	}
	sh_print("\r\n");
	return SH_OK;
}

/**
 * @brief adc [组号] —— 读探针组
 * @param[in] argc 参数个数
 * @param[in] argv argv[0]="adc"，可选 argv[1]=组号
 * @return 0 成功；非 0 失败
 */
static int sh_cmd_adc(int argc, char *argv[])
{
	uint32_t want = 0u;
	uint8_t  g;

	if (argc > 1) {
		if (!sh_parse_u32(argv[1], &want) || (want >= (uint32_t)ADC_CFG_NUM_GROUPS)) {
			sh_puts(SH_RET_PARA);
			return SH_ERR_PARAM;
		}
		if (adc_cmd_read_group((uint8_t)want) != SH_OK) {
			return SH_ERR;
		}
		sh_puts(SH_RET_OK);
		return SH_OK;
	}

	for (g = 0u; g < (uint8_t)ADC_CFG_NUM_GROUPS; g++) {
		(void)adc_cmd_read_group(g);
	}
	sh_puts(SH_RET_OK);
	return SH_OK;
}

SH_EXPORT_CMD(adc, sh_cmd_adc, "adc [group] -- read ADC probe group(s)");

#endif /* !SH_DISABLE_CMD_ADC */
