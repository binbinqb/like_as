/**
 * @file    bootperf_cmd.c
 * @brief   `bootperf` 命令：量"整镜像 CRC"的耗时（开发构建专用）
 *
 * @details @section BP_WHY 为什么不在 Boot 里打这个点
 *
 *          Boot 路径上量耗时的直觉做法是用 DWT 周期计数器（`PerfMon_Cycles()`），
 *          上板实测**不可用**：NVM / Flash 初始化之后 `DEMCR` 会被清成 0，
 *          `DWT_CTRL.CYCCNTENA` 随之失效，计数器冻结 —— 10 万次自旋循环走出的
 *          周期数是 0，CRC 算完也是 0：
 *
 *          @code
 *          [boot] DBG DEMCR=01000000 ... CYCCNT=00000066   // 刚初始化，还在走
 *          [boot] DBG spin cyc 773207 -> 773207 (delta=0)  demcr=00000000
 *          @endcode
 *
 *          App 侧同一个 `PerfMon_Cycles()` 是准的（与 SysTick 标定得
 *          119,599,765 Hz ≈ 120 MHz），所以把测速放到 App：SysTick 已经在跑，
 *          `Platform_NowMs()` 直接可用，1 ms 分辨率对 80 ms 量级的校验足够。
 *          （谁清了 DEMCR 尚未查清，记为 25.x 待办。）
 *
 *          @section BP_CTX 为什么分"关中断 / 开中断"两组
 *
 *          同一段代码在 Boot 里和在跑起来的 App 里耗时差 3 倍，上板实测：
 *
 *          | 场景 | 耗时（246 KB） |
 *          |------|----------------|
 *          | Boot 选槽（中断关、外设未起） | 81 ms |
 *          | App 起来后、中断全开 | 267 ms |
 *
 *          两个时基（SysTick 与 CYCCNT）给出同一个数，心跳间隔用主机时间戳核对
 *          也是 1.00 s/拍 —— 说明不是时基在骗人，而是**中断负载**把这段顺序计算
 *          拖慢了。所以要同时给两组数：`irq-off` 才是 Boot 选槽的等效值。
 *
 *          @section BP_WHY2 为什么要 direct / chunked 两条路径
 *
 *          - `direct`：`Crc_CalculateCRC32((const uint8_t *)base, ...)`，
 *            Boot 改造前的写法，Flash 内存映射直读；
 *          - `chunked`：`BootMeta_CalcImageCrc()`，经 `Platform_FlashRead()` 分段取数。
 *
 *          分段是为**离板可测**付的代价：Host 用例能真编译 `BootMeta.c` 跑选槽判定，
 *          靠的就是取数走平台层。这条命令把这个代价量出来（关中断下 77 → 81 ms）。
 *
 *          @note 只读镜像，不改任何状态；量产构建里整文件被剔除。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-17 | binbina | 首版：direct / chunked × 关中断 / 开中断 |
 */

#if !defined(SH_DISABLE_CMD_BOOTPERF) && !defined(BOOT_MODE_PRODUCTION)

#include <string.h>

#include "boot_flash_map.h"
#include "boot_meta.h"
#include "Crc.h"
#include "perf_mon.h"       /* 交叉校验时基：CYCCNT（App 里已标定 119.6 MHz） */
#include "platform_cvm0146.h"
#include "sh.h"             /* SH_OK / SH_EXPORT_CMD / sh_print */

/* ============================ [ 链接符号 ] ============================ */

/** @brief 镜像向量表起始（= 所在槽基址） */
extern const uint32_t __VECTOR_TABLE;

/** @brief 镜像末尾（链接脚本里的 __CUSTOM_END） */
extern const uint32_t __CUSTOM_END;

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief 关中断并返回原 PRIMASK
 *
 * @details 不引 `core_cm4.h`：SDK 里也有一份同名头，字段定义会打架
 *          （`platform_cvm0146.c` 因为同样原因改用裸地址访问 NVIC）。
 *
 * @return 进入前的 PRIMASK
 */
static uint32_t bp_irq_save(void)
{
	uint32_t primask;

	__asm volatile ("mrs %0, primask" : "=r" (primask));
	__asm volatile ("cpsid i" ::: "memory");
	return primask;
}

/**
 * @brief 恢复 PRIMASK
 * @param[in] primask `bp_irq_save()` 的返回值
 */
static void bp_irq_restore(uint32_t primask)
{
	__asm volatile ("msr primask, %0" :: "r" (primask) : "memory");
}

/* ============================ [ 命令实现 ] ============================ */

/**
 * @brief bootperf —— 量当前镜像的 CRC 耗时
 *
 * @param[in] argc 参数个数（本命令无参数）
 * @param[in] argv 参数数组
 * @return 0 成功
 */
static int sh_cmd_bootperf(int argc, char *argv[])
{
	uint32_t base = (uint32_t)&__VECTOR_TABLE;
	uint32_t size = (uint32_t)&__CUSTOM_END - base;
	uint32_t primask;
	uint32_t dtDirect;
	uint32_t dtChunk;
	uint32_t dtLoaded;
	uint32_t crcDirect;
	uint32_t crcChunk;

	(void)argc;
	(void)argv;

	if ((size == 0u) || (size > BOOT_SLOT_IMAGE_MAX)) {
		sh_print("<+1, image size %u out of range\r\n", (unsigned)size);
		return SH_OK;
	}

	/* ---- 关中断：等价于 Boot 选槽时的执行环境 ----
	 *
	 * ⚠ 时基必须用 CYCCNT，不能用 `Platform_NowMs()`：后者靠 SysTick 中断推进，
	 *   关中断期间它**原地不动**，量出来会是 0 ms（第一次上板就是这么骗人的）。 */
	primask = bp_irq_save();
	{
		uint32_t q0 = PerfMon_Cycles();
		uint32_t q1;

		crcDirect = Crc_CalculateCRC32((const uint8_t *)base, size, 0xFFFFFFFFu, TRUE);
		q1 = PerfMon_Cycles();
		dtDirect = PerfMon_CyclesToUs(q1 - q0);

		q0 = PerfMon_Cycles();
		crcChunk = BootMeta_CalcImageCrc(base, size);
		q1 = PerfMon_Cycles();
		dtChunk = PerfMon_CyclesToUs(q1 - q0);
	}
	bp_irq_restore(primask);

	/* ---- 开中断：同样的活，但外设中断在抢 CPU ---- */
	{
		uint32_t q0 = PerfMon_Cycles();
		uint32_t q1;

		(void)BootMeta_CalcImageCrc(base, size);
		q1 = PerfMon_Cycles();
		dtLoaded = PerfMon_CyclesToUs(q1 - q0);
	}

	sh_print("<+0, image %u B @ 0x%08X  (all times from CYCCNT)\r\n",
	         (unsigned)size, (unsigned)base);
	sh_print("     direct  irq-off : %5u us  crc=%08X\r\n",
	         (unsigned)dtDirect, (unsigned)crcDirect);
	sh_print("     chunked irq-off : %5u us  crc=%08X  %s\r\n",
	         (unsigned)dtChunk, (unsigned)crcChunk,
	         (crcDirect == crcChunk) ? "same" : "MISMATCH");
	sh_print("     chunked irq-on  : %5u us  crc=%08X\r\n",
	         (unsigned)dtLoaded, (unsigned)crcChunk);

	return SH_OK;
}

SH_EXPORT_CMD(bootperf, sh_cmd_bootperf,
              "dev only: measure image CRC time (irq off/on, direct/chunked)");

#endif /* !SH_DISABLE_CMD_BOOTPERF && !BOOT_MODE_PRODUCTION */
