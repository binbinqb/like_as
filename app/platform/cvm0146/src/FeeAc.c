/**
 * @file    FeeAc.c
 * @brief   Fee 的平台访问层：把厂商 FEE 中间件挂到 CVM0146 的 **DFlash** 上
 *
 * @details @section FEEAC_WHY 为什么需要这一层
 *          厂商的 `infras/memory/Fee` 是一个**与芯片无关**的 EEPROM 仿真状态机：
 *          它只认 `Fee_MethodType` 里的 5 个函数指针（读/写/擦/是否可写/算 CRC8），
 *          不知道 DFlash 在哪、扇区多大、ECC 怎么查。本文件就是这 5 个函数的
 *          CVM0146 实现 —— 对应厂商 `examples/CVM0146/demo_apps/nvm_demo/src/fee_internal.c`
 *          的角色，但按本工程的 AC 层命名与注释规范重写。
 *
 *          @section FEEAC_LAYOUT 用的是"专用 DFlash"，不是硬件模拟 EEPROM
 *          CVM0146 的 Flash 分三块（RM 表 32-2）：
 *          @code
 *          0x0000_0000 - 0x000F_FFFF   PFlash   1 MB      代码
 *          0x1000_0000 - 0x1001_FFFF   DFlash   128 KB    数据  ← 本文件只碰这里
 *          0x1002_0000 - 0x1003_FFFF   DFlash   128 KB    硬件模拟 EEPROM 备份区
 *          0x1400_0000 - 0x1400_0FFF   FlexRAM  4 KB      EEPROM 的 RAM 映像
 *          @endcode
 *          后 128 KB 在 `EEEVLD=1` 时被硬件当作 EEPROM 备份区，**AXBS 不可读**；
 *          所以本工程只用前 128 KB，且实际只占最前面的 24 KB（见 `Fee_Cfg.h`）。
 *          走 FEE 而不是硬件 EEPROM 的好处：备份区可随时当普通 DFlash 用，
 *          没有 FlexRAM 4 KB 的容量上限，也不需要专门的 EEPROM 命令序列。
 *
 *          @section FEEAC_CACHE 必须关 DFlash 缓存
 *          `LMEM.CACHE_CTRL`（`0xE0082000`）的 `EN` 位若为 1，DFlash 读会走缓存。
 *          FEE 的写流程是"擦除 → 写 → **回读校验**"，缓存会让回读拿到旧值，
 *          表现为 `FLS_STATE_READ_BACK_FAIL`，而且**只在使能过缓存的板子上复现**。
 *          本板复位后该寄存器全 0（缓存关），`FeeAc_Init()` 再写一次 0 是防御性的：
 *          将来若有人为提性能打开缓存，这里会把它关回去，而不是让存储悄悄坏掉。
 *
 *          @section FEEAC_ALIGN 8 字节是硬约束
 *          DFlash 的最小烧写单位是 **phrase = 8 字节**，SDK 的 `FlashDrv_*Phrase()`
 *          一律要求地址 8 字节对齐、长度 8 的整数倍。FEE 侧所有写入长度都已经
 *          `ALIGN8BYTE()` 过了（`FEE_BLOCKSIZE` / `FEE_BLOCK_HEAD_INFO_SIZE` /
 *          `FEE_SECTOR_HEAD_INFO_LEN` 全是 8 的倍数），所以这里只加一道断言式检查：
 *          长度不是 8 的倍数就直接返回失败，而不是把尾巴静默丢掉 ——
 *          静默丢尾巴会让 CRC 校验通过、数据却是错的，最难查。
 *
 *          @warning 本文件里的写/擦都会**阻塞**到 FTFC 命令完成。一次 1 KB 扇区擦除
 *          在 DFlash 上是毫秒级，期间 CPU 停等。所以 FEE 的擦除被设计成
 *          "每个 MainFunction 擦 1 KB"（`Fee_EraseSector()` 按 `eraseSectionIdx`
 *          分片），对外表现为后台慢慢擦，不卡主循环。**不要**把它改成一次性擦整扇区。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：DFlash 五方法（读/写/擦/可写/CRC8） |
 */

#include <stddef.h>
#include <string.h>

#include "mcu.h"
#include "drivers/flash/flash_drv.h"

#include "fee/fee_extra.h"

#include "platform_priv.h"

/* ============================ [ 私有定义 ] ============================ */

/** @brief DFlash 的 phrase 长度（最小烧写单位，字节） */
#define FEEAC_PHRASE_BYTES      (8u)

/**
 * @brief DFlash 的扇区长度（字节）
 * @note  驱动的 `SCTRD1S` / 擦除命令都以 1 KB 为单位，且**读/擦范围不得跨扇区**。
 *        这个常数必须等于 `FLASHDRV_DFLASH_SECTOR_SIZE`。
 */
#define FEEAC_SECTOR_BYTES      (FLASHDRV_DFLASH_SECTOR_SIZE)

/** @brief LMEM 缓存控制寄存器（`LMEM.CACHE_CTRL`，RM 30.3.2） */
#define FEEAC_CACHE_CTRL_ADDR   (0xE0082000u)

/** @brief `CACHE_CTRL.EN`：0=关闭缓存，1=使能 */
#define FEEAC_CACHE_CTRL_OFF    (0x00000000u)

/* ============================ [ CRC8 查表 ] ============================ */

/**
 * @brief CRC8 查找表（多项式 0x1D 反射，初值 0xFF，结果取反）
 * @note  与 NvM 用的是同一份表：`Nvm_MethodType.crc8` 也指向 `FeeAc_CalcCrc8()`，
 *        两边必须同源，否则 FEE 认为块完整、NvM 认为块损坏。
 */
static const uint8_t FeeAc_CrcTable8[256] = {
	0x00u, 0x1Du, 0x3Au, 0x27u, 0x74u, 0x69u, 0x4Eu, 0x53u, 0xE8u, 0xF5u, 0xD2u, 0xCFu, 0x9Cu, 0x81u, 0xA6u, 0xBBu,
	0xCDu, 0xD0u, 0xF7u, 0xEAu, 0xB9u, 0xA4u, 0x83u, 0x9Eu, 0x25u, 0x38u, 0x1Fu, 0x02u, 0x51u, 0x4Cu, 0x6Bu, 0x76u,
	0x87u, 0x9Au, 0xBDu, 0xA0u, 0xF3u, 0xEEu, 0xC9u, 0xD4u, 0x6Fu, 0x72u, 0x55u, 0x48u, 0x1Bu, 0x06u, 0x21u, 0x3Cu,
	0x4Au, 0x57u, 0x70u, 0x6Du, 0x3Eu, 0x23u, 0x04u, 0x19u, 0xA2u, 0xBFu, 0x98u, 0x85u, 0xD6u, 0xCBu, 0xECu, 0xF1u,
	0x13u, 0x0Eu, 0x29u, 0x34u, 0x67u, 0x7Au, 0x5Du, 0x40u, 0xFBu, 0xE6u, 0xC1u, 0xDCu, 0x8Fu, 0x92u, 0xB5u, 0xA8u,
	0xDEu, 0xC3u, 0xE4u, 0xF9u, 0xAAu, 0xB7u, 0x90u, 0x8Du, 0x36u, 0x2Bu, 0x0Cu, 0x11u, 0x42u, 0x5Fu, 0x78u, 0x65u,
	0x94u, 0x89u, 0xAEu, 0xB3u, 0xE0u, 0xFDu, 0xDAu, 0xC7u, 0x7Cu, 0x61u, 0x46u, 0x5Bu, 0x08u, 0x15u, 0x32u, 0x2Fu,
	0x59u, 0x44u, 0x63u, 0x7Eu, 0x2Du, 0x30u, 0x17u, 0x0Au, 0xB1u, 0xACu, 0x8Bu, 0x96u, 0xC5u, 0xD8u, 0xFFu, 0xE2u,
	0x26u, 0x3Bu, 0x1Cu, 0x01u, 0x52u, 0x4Fu, 0x68u, 0x75u, 0xCEu, 0xD3u, 0xF4u, 0xE9u, 0xBAu, 0xA7u, 0x80u, 0x9Du,
	0xEBu, 0xF6u, 0xD1u, 0xCCu, 0x9Fu, 0x82u, 0xA5u, 0xB8u, 0x03u, 0x1Eu, 0x39u, 0x24u, 0x77u, 0x6Au, 0x4Du, 0x50u,
	0xA1u, 0xBCu, 0x9Bu, 0x86u, 0xD5u, 0xC8u, 0xEFu, 0xF2u, 0x49u, 0x54u, 0x73u, 0x6Eu, 0x3Du, 0x20u, 0x07u, 0x1Au,
	0x6Cu, 0x71u, 0x56u, 0x4Bu, 0x18u, 0x05u, 0x22u, 0x3Fu, 0x84u, 0x99u, 0xBEu, 0xA3u, 0xF0u, 0xEDu, 0xCAu, 0xD7u,
	0x35u, 0x28u, 0x0Fu, 0x12u, 0x41u, 0x5Cu, 0x7Bu, 0x66u, 0xDDu, 0xC0u, 0xE7u, 0xFAu, 0xA9u, 0xB4u, 0x93u, 0x8Eu,
	0xF8u, 0xE5u, 0xC2u, 0xDFu, 0x8Cu, 0x91u, 0xB6u, 0xABu, 0x10u, 0x0Du, 0x2Au, 0x37u, 0x64u, 0x79u, 0x5Eu, 0x43u,
	0xB2u, 0xAFu, 0x88u, 0x95u, 0xC6u, 0xDBu, 0xFCu, 0xE1u, 0x5Au, 0x47u, 0x60u, 0x7Du, 0x2Eu, 0x33u, 0x14u, 0x09u,
	0x7Fu, 0x62u, 0x45u, 0x58u, 0x0Bu, 0x16u, 0x31u, 0x2Cu, 0x97u, 0x8Au, 0xADu, 0xB0u, 0xE3u, 0xFEu, 0xD9u, 0xC4u
};

/* ============================ [ 私有函数 ] ============================ */

/**
 * @brief 判断一段区域是否**仍处于擦除态**（全 0xFF）
 *
 * @details 按 1 KB 扇区边界切段，每段调一次 `FlashDrv_Read1sSection()`。
 *          驱动那个接口要求"读范围不得跨 1 KB 扇区"（`flash_drv.c:178`），
 *          而 FEE 的数据区是连续增长的 —— 一个块完全可能横跨两个 1 KB 扇区。
 *          切段既满足驱动约束，又保持"一次命令查一整段"。
 *
 *          @warning **不要**按 8 字节 phrase 逐片调它。`SCTRD1S` 是一条完整的
 *          FTFC 命令（内部会把整段 1 KB 读一遍并比较），每次调用都要等命令完成。
 *          逐 phrase 调用会把 1 条命令变成 128 条：初始化时扫描 2 × 12 KB 会变成
 *          三千多条命令，Fee 初始化直接拖到秒级，表现为 `NvM_ReadAll()` 超时、
 *          数据全走 ROM 默认值 —— 而且不报任何错误。
 *
 * @param[in] addr 起始地址（必须 8 字节对齐）
 * @param[in] size 长度（必须是 8 的整数倍）
 * @retval true  全 0xFF（可写 / 未写过）
 * @retval false 有非 0xFF 字节，或参数不合法，或驱动报错
 */
static bool FeeAc_IsErased(const uint8_t *addr, uint32_t size)
{
	uint32_t done = 0u;

	if ((size == 0u) || ((size % FEEAC_PHRASE_BYTES) != 0u)) {
		return false;
	}
	if ((((uint32_t)addr) % FEEAC_PHRASE_BYTES) != 0u) {
		return false;
	}

	while (done < size) {
		uint32_t cur      = (uint32_t)addr + done;
		uint32_t remain   = size - done;
		uint32_t toEnd    = FEEAC_SECTOR_BYTES - (cur % FEEAC_SECTOR_BYTES);
		uint32_t chunk    = (remain < toEnd) ? remain : toEnd;

		/* chunk 一定是 8 的倍数：cur 8 对齐，1 KB 也是 8 的倍数 */
		if (FlashDrv_Read1sSection(&g_mcu.flashDrv, (uint32_t *)cur,
		                           chunk) != FLASHDRV_STATUS_SUCCESS) {
			return false;
		}

		done += chunk;
	}

	return true;
}

/**
 * @brief 带 ECC 校验的拷贝：DFlash → RAM
 * @details 逐 phrase 先让 FTFC 做一次单比特纠错/双比特检错判定
 *          （`FlashDrv_CheckEccState()`），确认没坏再按字节搬。
 *          直接按字节搬也能读到数据，但**读不出 ECC 错误** —— 坏块会被当成好数据。
 * @param[in]  src  源地址（DFlash，8 字节对齐）
 * @param[out] dst  目的缓冲
 * @param[in]  size 长度（8 的整数倍）
 * @retval FLASHDRV_STATUS_SUCCESS 全部 phrase 校验通过且已拷贝
 * @retval FLASHDRV_STATUS_ERROR   任一片 ECC 报错，或参数不合法（此时 dst 内容不可信）
 */
static FlashDrv_Status FeeAc_CopyOutWithEcc(const uint8_t *src, uint8_t *dst, uint32_t size)
{
	uint32_t off;

	if ((size == 0u) || ((size % FEEAC_PHRASE_BYTES) != 0u)) {
		return FLASHDRV_STATUS_ERROR;
	}

	for (off = 0u; off < size; off += FEEAC_PHRASE_BYTES) {
		if (FlashDrv_CheckEccState(&g_mcu.flashDrv,
		                           (uint32_t *)(src + off)) != FLASHDRV_STATUS_SUCCESS) {
			return FLASHDRV_STATUS_ERROR;
		}
	}

	(void)memcpy(dst, src, (size_t)size);

	return FLASHDRV_STATUS_SUCCESS;
}

/* ============================ [ 方法表实现 ] ============================ */

/**
 * @brief 查询区域是否可写（即是否仍为擦除态）
 * @details FEE 用它来：① 判断整扇区是否已擦除；② 写每个 phrase 前的预检。
 * @param[in] sAddr 起始地址
 * @param[in] size  长度
 * @retval FLS_STATE_OK           全 0xFF，可写
 * @retval FLS_STATE_NOT_WRITABLE 已有数据（**不是**错误，是正常的"非空"信号）
 */
static Fls_StateType FeeAc_IsWriteable(Fee_AddressType sAddr, uint32_t size)
{
	return FeeAc_IsErased(sAddr, size) ? FLS_STATE_OK : FLS_STATE_NOT_WRITABLE;
}

/**
 * @brief 写入并回读校验（FEE 的唯一写入口）
 *
 * @details 三段式，缺一不可：
 *          1. **预检**：目标 phrase 必须是全 0xFF。DFlash 只能把 1 写成 0，
 *             对非擦除区再写会得到"按位与"的垃圾值，而且**不报错**；
 *          2. **烧写**：`FlashDrv_ProgramPhrase()`，硬件自动生成 ECC；
 *          3. **校验**：`FlashDrv_CheckPhrase()` 让 FTFC 把 Flash 内容与期望值逐位比对
 *             （含 ECC），确认真的写进去了。
 *
 * @param[in] sAddr 目标地址（DFlash，8 字节对齐）
 * @param[in] buff  源数据
 * @param[in] size  长度（8 的整数倍）
 * @retval FLS_STATE_OK              写入并校验通过
 * @retval FLS_STATE_NOT_WRITABLE    预检失败：目标区域没擦干净
 * @retval FLS_STATE_PROGRAM_FAIL    烧写命令失败
 * @retval FLS_STATE_READ_BACK_FAIL  烧写命令成功但回读不一致
 */
static Fls_StateType FeeAc_WriteCheck(Fee_AddressType sAddr, uint8_t *buff, uint32_t size)
{
	uint32_t off;

	if ((size == 0u) || ((size % FEEAC_PHRASE_BYTES) != 0u) || (buff == NULL)) {
		return FLS_STATE_PROGRAM_FAIL;
	}

	/* 预检整段一次（按 1 KB 切段），而不是逐 phrase 查 ——
	 * 每条 SCTRD1S 都是一次完整的 FTFC 命令，逐 phrase 会把一次判断拆成 N 条命令。
	 * 语义上等价：整段全 0xFF 等价于每片都全 0xFF。 */
	if (!FeeAc_IsErased(sAddr, size)) {
		return FLS_STATE_NOT_WRITABLE;
	}

	for (off = 0u; off < size; off += FEEAC_PHRASE_BYTES) {
		const uint8_t *src = &buff[off];
		uint8_t       *dst = &sAddr[off];

		if (FlashDrv_ProgramPhrase(&g_mcu.flashDrv, (uint32_t *)dst,
		                           (uint8_t *)src, true) != FLASHDRV_STATUS_SUCCESS) {
			return FLS_STATE_PROGRAM_FAIL;
		}
		if (FlashDrv_CheckPhrase(&g_mcu.flashDrv, (uint32_t *)dst,
		                         (uint8_t *)src) != FLASHDRV_STATUS_SUCCESS) {
			return FLS_STATE_READ_BACK_FAIL;
		}
	}

	return FLS_STATE_OK;
}

/**
 * @brief 读取并校验（FEE 的唯一读入口）
 *
 * @details 先判"未写过"，再带 ECC 拷贝，最后用 FTFC 的 PRSCHK 命令逐 phrase 复核。
 *          三步分别对应 FEE 需要的三种结果：
 *          | 情形 | 返回 | FEE 的处置 |
 *          |------|------|-------------|
 *          | 全 0xFF（从未写过） | `FLS_STATE_NOT_WRITTEN` | 该块无数据，用 ROM 默认值 |
 *          | ECC 报错 | `FLS_STATE_ECC_ERROR` | 该块损坏 |
 *          | 正常 | `FLS_STATE_OK` | 数据可用 |
 *
 * @param[in]  sAddr 源地址（DFlash，8 字节对齐）
 * @param[out] buff  目的缓冲
 * @param[in]  size  长度（8 的整数倍）
 * @return 见上表
 */
static Fls_StateType FeeAc_ReadCheckData(Fee_AddressType sAddr, uint8_t *buff, uint32_t size)
{
	uint32_t off;

	if ((size == 0u) || ((size % FEEAC_PHRASE_BYTES) != 0u) || (buff == NULL)) {
		return FLS_STATE_UNKNOW;
	}

	if (FeeAc_IsErased(sAddr, size)) {
		return FLS_STATE_NOT_WRITTEN;
	}

	if (FeeAc_CopyOutWithEcc(sAddr, buff, size) != FLASHDRV_STATUS_SUCCESS) {
		return FLS_STATE_ECC_ERROR;
	}

	/* 拷贝下来之后再让 FTFC 比对一遍：ECC 只能发现"存储位翻转"，
	 * 发现不了"读到的是别的块的数据"（地址算错时就是这样），
	 * 这一步用期望值兜住整条链路。 */
	for (off = 0u; off < size; off += FEEAC_PHRASE_BYTES) {
		if (FlashDrv_CheckPhrase(&g_mcu.flashDrv,
		                         (uint32_t *)(sAddr + off),
		                         &buff[off]) != FLASHDRV_STATUS_SUCCESS) {
			return FLS_STATE_READ_BACK_FAIL;
		}
	}

	return FLS_STATE_OK;
}

/**
 * @brief 擦除**一个 1 KB 扇区**并校验
 *
 * @details 注意签名：`Fee_eraseMethodType` 只收一个地址，没有长度 ——
 *          因为它就是"擦这个地址所在的 1 KB 扇区"。
 *          FEE 的扇区（默认 12 KB）由 `Fee_EraseSector()` 拆成 12 次调用，
 *          每次 `MainFunction` 擦一片，避免一次阻塞十几毫秒。
 *
 *          已经是擦除态时直接返回 OK、不重复擦：FEE 在初始化阶段会对每个扇区
 *          调一次判空，重复擦除会白白消耗擦写寿命。
 *
 * @param[in] eraseAddr 扇区起始地址（必须 1 KB 对齐）
 * @retval FLS_STATE_OK         已擦干净
 * @retval FLS_STATE_ERASE_FAIL 擦除命令失败，或擦完仍不是全 0xFF
 */
static Fls_StateType FeeAc_EraseCheckSector(Fee_AddressType eraseAddr)
{
	if (FeeAc_IsErased(eraseAddr, FLASHDRV_DFLASH_SECTOR_SIZE)) {
		return FLS_STATE_OK;
	}

	if (FlashDrv_EraseSector(&g_mcu.flashDrv, (uint32_t *)eraseAddr,
	                         FLASHDRV_SCTERS_RETRY) != FLASHDRV_STATUS_SUCCESS) {
		return FLS_STATE_ERASE_FAIL;
	}

	/* 擦除是"把 0 变回 1"，硬件不会告诉你有几片没擦干净，只能整片回读确认 */
	if (!FeeAc_IsErased(eraseAddr, FLASHDRV_DFLASH_SECTOR_SIZE)) {
		return FLS_STATE_ERASE_FAIL;
	}

	return FLS_STATE_OK;
}

/**
 * @brief 计算 CRC8（表驱动，初值 0xFF，结果取反）
 * @param[in] sAddr 数据起始地址
 * @param[in] size  字节数
 * @return CRC8 结果
 * @note  **NvM 与 FEE 必须用同一份实现**：FEE 用它校验"块头 vs 块数据"，
 *        NvM 用它校验"整块数据"。两份不同的 CRC 会让故障定位指向错误的那一层。
 *        所以本函数不 static，`NvM_Cfg.c` 的方法表直接引用它。
 */
uint8_t FeeAc_CalcCrc8(void *sAddr, uint32_t size)
{
	const uint8_t *p = (const uint8_t *)sAddr;
	uint8_t        crc = 0xFFu;
	uint32_t       i;

	if (p == NULL) {
		return 0u;
	}

	for (i = 0u; i < size; i++) {
		crc = FeeAc_CrcTable8[crc ^ p[i]];
	}

	return (uint8_t)(crc ^ 0xFFu);
}

/* ============================ [ 对外 ] ============================ */

/**
 * @brief FEE 的底层方法表（`FeeType.flsMethod` 指向它）
 * @note  字段顺序**必须**与 `Fee_MethodType` 的声明顺序一致，改顺序不会报错，
 *        但会把"写"当"读"用。这里用带字段名的初始化，就是为了让编译器帮忙卡住。
 */
const Fee_MethodType FeeAc_FlsMethod = {
	.write       = FeeAc_WriteCheck,
	.read        = FeeAc_ReadCheckData,
	.erase       = FeeAc_EraseCheckSector,
	.isWriteable = FeeAc_IsWriteable,
	.crc8        = FeeAc_CalcCrc8,
};

/**
 * @brief 存储栈的平台侧初始化（在 `Fee_Configure()` 之前调用一次）
 *
 * @details 只做两件事：
 *          1. 关 LMEM 缓存 —— 见文件头 `@ref FEEAC_CACHE`，这是**功能前提**，
 *             不是性能调优；
 *          2. 把 Flash 驱动配成"无回调"（`FlashDrv_Configure` 只认 callback 一个字段，
 *             其余参数在 `Mcu_Init()` 里已定死）。写在这里是为了让"用 DFlash
 *             必须先配 flash 驱动"这件事在代码里看得见。
 *
 * @note `Mcu_Init()`（`Platform_Init()` 里已调用）完成了 `FlashDrv_Init()`，
 *       本函数不重复初始化驱动对象 —— 重复 `Mcu_Init()` 会把已配好的外设全部复位。
 */
void FeeAc_Init(void)
{
	FlashDrv_ConfigType cfg;

	*((volatile uint32_t *)FEEAC_CACHE_CTRL_ADDR) = FEEAC_CACHE_CTRL_OFF;

	FlashDrv_GetDefaultConfig(&cfg);
	FlashDrv_Configure(&g_mcu.flashDrv, &cfg);
}
