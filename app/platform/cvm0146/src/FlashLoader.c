/**
 * @file    flash_loader.c
 * @brief   A/B 分区刷写业务实现：分片擦除、对齐写入、CRC 校验、meta 落盘
 *
 * @details @section FL_SAFE 三条安全边界，每一条都对应一种真实的"刷坏"方式
 *
 *          | 边界 | 不加会怎样 |
 *          |------|------------|
 *          | 只允许擦/写**非活动槽** | 刷到一半掉电，两个槽都没了，只能拆壳接调试器 |
 *          | 地址必须**正好等于**槽基址 | 上位机算错一个偏移就擦到 meta 或另一个槽 |
 *          | 写入前**逐块对齐 + 预检全 0xFF** | 对未擦净区域重写会得到"按位与"的垃圾值，硬件不报错 |
 *
 *          @section FL_TAIL 为什么代码里到处在算"尾巴"
 *          Flash 最小写入单位是 phrase = **8 字节**，而 UDS 传输的数据长度由
 *          上位机决定（哪怕我们把块长报告成 120，最后一块也可能是 4 字节）。
 *          不足 8 字节的部分不能直接写，只能：
 *            - 攒着等下一块拼满（跨 0x36 调用保存状态），或
 *            - 在 `TransferExit` 时补 0xFF 凑满一个 phrase 再写。
 *          两条路径都实现了。补 0xFF 的原因：0xFF 是擦除态，补进去不会改变
 *          CRC 覆盖范围之外的内容，也不会让"这块数据"看起来像被改过。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版 |
 */

#include <string.h>

#include "FlashLoader.h"
#include "platform_cvm0146.h"
#include "boot_meta.h"
#include "boot_flash_map.h"
#include "Crc.h"

/* ============================ [ 内部类型 ] ============================ */

/** @brief 擦除作业上下文 */
typedef struct {
	uint8_t  active;   /**< 是否有进行中的擦除 */
	uint8_t  slot;     /**< 目标槽 */
	uint32_t base;     /**< 槽基址 */
	uint32_t size;     /**< 请求擦除的字节数 */
	uint32_t done;     /**< 已擦除字节数（按扇区递增） */
} FlashLoader_EraseType;

/** @brief 下载作业上下文 */
typedef struct {
	uint8_t  active;   /**< 是否有进行中的下载 */
	uint8_t  slot;     /**< 目标槽 */
	uint32_t base;     /**< 槽基址 */
	uint32_t size;     /**< 镜像总字节数 */
	uint32_t offset;   /**< 已接收字节数 */
	uint32_t tailAddr; /**< 待写 phrase 的地址 */
	uint8_t  tail[8];  /**< 不足一个 phrase 的尾巴 */
	uint8_t  tailLen;  /**< 尾巴长度 0..7 */
} FlashLoader_DlType;

/* ============================ [ 内部数据 ] ============================ */

static FlashLoader_EraseType s_erase;
static FlashLoader_DlType    s_dl;

/** @brief 活动槽（`FlashLoader_Init` 时锁定，0xFF = 未知） */
static uint8_t s_activeSlot = BOOT_NO_ACTIVE_SLOT;

/* ============================ [ 内部函数 ] ============================ */

/**
 * @brief 从大端字节流解析 32 位无符号数
 * @param[in] p 指向 4 字节
 * @return 解析结果
 * @note  UDS 的地址与长度一律大端，别用 memcpy —— 小端机器上会读反。
 */
static uint32_t FlashLoader_ReadBe32(const uint8_t *p)
{
	return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) | ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

/**
 * @brief 判断地址是否是某个槽的基址
 * @param[in]  addr 待判断地址
 * @param[out] slot 命中的槽索引
 * @retval 1 是槽基址
 * @retval 0 不是
 */
static uint8_t FlashLoader_MatchSlotBase(uint32_t addr, uint8_t *slot)
{
	uint8_t i;

	for (i = 0u; i < BOOT_SLOT_NUM; i++) {
		if (addr == BOOT_SLOT_BASE(i)) {
			*slot = i;
			return 1u;
		}
	}

	return 0u;
}

/**
 * @brief 判断某个槽是否是当前活动槽（活动槽不许擦）
 * @param[in] slot 槽索引
 * @retval 1 是活动槽
 * @retval 0 不是（或活动槽未知 —— 未知时也按"是"处理更安全，
 *            但那样首次烧写就没法刷了，所以这里按"不是"处理）
 */
static uint8_t FlashLoader_IsActiveSlot(uint8_t slot)
{
	return (slot == s_activeSlot) ? 1u : 0u;
}

/**
 * @brief 把不足一个 phrase 的尾巴补 0xFF 写下去
 * @param[in] addr    尾巴所在地址（8 字节对齐）
 * @param[in] tail    尾巴数据
 * @param[in] tailLen 长度 1..7
 * @retval E_OK     写入并校验通过
 * @retval E_NOT_OK 写失败
 */
static Std_ReturnType FlashLoader_FlushTail(uint32_t addr, const uint8_t *tail, uint8_t tailLen)
{
	uint8_t buf[BOOT_PFLASH_PHRASE_SIZE];

	if ((tailLen == 0u) || (tailLen >= BOOT_PFLASH_PHRASE_SIZE)) {
		return E_OK;
	}

	(void)memset(buf, 0xFF, sizeof(buf));
	(void)memcpy(buf, tail, (size_t)tailLen);

	return Platform_FlashWrite(addr, buf, (uint32_t)sizeof(buf));
}

/* ============================ [ 对外接口 ] ============================ */

void FlashLoader_Init(void)
{
	uint8_t active;

	/* meta 可能已被 `BootApp_Init()` 扫过，这里再扫一次是幂等的（纯读） */
	BootMeta_Init();
	active = BootMeta_GetActiveSlot();

	/* 没有任何有效槽（首次烧写）时，允许刷任意槽 —— 否则产线无法首次写入 */
	s_activeSlot = active;

	(void)memset(&s_erase, 0, sizeof(s_erase));
	(void)memset(&s_dl, 0, sizeof(s_dl));
}

Std_ReturnType FlashLoader_EraseStart(const uint8_t *dataIn, Dcm_OpStatusType opStatus,
                                      uint8_t *dataOut, uint16_t *len,
                                      Dcm_NegativeResponseCodeType *nrc)
{
	uint32_t eraseEnd;

	/* ---- 取消：把状态清干净，别让下一次请求接上残留的 done ---- */
	if (opStatus == DCM_CANCEL) {
		s_erase.active = 0u;
		return E_NOT_OK;
	}

	/* ---- 首次：解析并校验参数 ---- */
	if (opStatus == DCM_INITIAL) {
		uint32_t addr;
		uint32_t size;
		uint8_t  slot = 0u;

		if ((len == NULL) || (*len != 8u)) {
			*nrc = DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
			return E_NOT_OK;
		}

		addr = FlashLoader_ReadBe32(&dataIn[0]);
		size = FlashLoader_ReadBe32(&dataIn[4]);

		if (FlashLoader_MatchSlotBase(addr, &slot) == 0u) {
			/* 只接受槽基址：允许任意地址等于把"擦错地方"的风险交给上位机 */
			*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
			return E_NOT_OK;
		}

		if ((size == 0u) || (size > BOOT_SLOT_IMAGE_MAX)) {
			*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
			return E_NOT_OK;
		}

		if (FlashLoader_IsActiveSlot(slot) != 0u) {
			/* 活动槽正在跑（本函数就是从它里面执行的），擦它等于自杀 */
			*nrc = DCM_E_CONDITIONS_NOT_CORRECT;
			return E_NOT_OK;
		}

		s_erase.slot = slot;
		s_erase.base = addr;
		s_erase.size = size;
		s_erase.done = 0u;
		s_erase.active = 1u;
	}

	if (s_erase.active == 0u) {
		*nrc = DCM_E_REQUEST_SEQUENCE_ERROR;
		return E_NOT_OK;
	}

	/* ---- 每次进入擦 1 个扇区（约 25 ms，关中断） ---- */
	eraseEnd = (s_erase.size + (BOOT_PFLASH_SECTOR_SIZE - 1u)) & ~(BOOT_PFLASH_SECTOR_SIZE - 1u);

	if (s_erase.done < eraseEnd) {
		if (Platform_FlashEraseSector(s_erase.base + s_erase.done) != E_OK) {
			s_erase.active = 0u;
			*nrc = DCM_E_GENERAL_PROGRAMMING_FAILURE;
			return E_NOT_OK;
		}
		s_erase.done += BOOT_PFLASH_SECTOR_SIZE;
	}

	if (s_erase.done < eraseEnd) {
		*nrc = DCM_E_RESPONSE_PENDING;   /* 让 Dcm 记 pending，下一周期再来 */
		return E_NOT_OK;
	}

	s_erase.active = 0u;
	dataOut[0] = 0u;   /* 0 = 成功（保留 1 表示失败） */
	*len = 1u;

	return E_OK;
}

Std_ReturnType FlashLoader_CheckStart(const uint8_t *dataIn, Dcm_OpStatusType opStatus,
                                      uint8_t *dataOut, uint16_t *len,
                                      Dcm_NegativeResponseCodeType *nrc)
{
	uint32_t addr;
	uint32_t size;
	uint32_t expect;
	uint32_t actual;

	(void)opStatus;

	if ((len == NULL) || (*len != 12u)) {
		*nrc = DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
		return E_NOT_OK;
	}

	addr   = FlashLoader_ReadBe32(&dataIn[0]);
	size   = FlashLoader_ReadBe32(&dataIn[4]);
	expect = FlashLoader_ReadBe32(&dataIn[8]);

	if ((addr >= BOOT_PFLASH_SIZE) || (size == 0u) || (size > BOOT_SLOT_IMAGE_MAX) ||
	    (size > (BOOT_PFLASH_SIZE - addr))) {
		*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
		return E_NOT_OK;
	}

	actual = Crc_CalculateCRC32((const uint8_t *)addr, size, 0xFFFFFFFFu, TRUE);

	dataOut[0] = (actual == expect) ? 0u : 1u;
	*len = 1u;

	return E_OK;
}

Std_ReturnType FlashLoader_RequestDownload(Dcm_OpStatusType opStatus, uint8_t dfi, uint8_t memId,
                                           uint32_t addr, uint32_t size, uint32_t *blockLen,
                                           Dcm_NegativeResponseCodeType *nrc)
{
	uint8_t slot = 0u;

	(void)opStatus;
	(void)memId;

	/* dataFormatIdentifier：bit0..3 压缩、bit4..7 加密，都要求为 0 */
	if (dfi != 0u) {
		*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
		return E_NOT_OK;
	}

	if ((blockLen == NULL) || (FlashLoader_MatchSlotBase(addr, &slot) == 0u)) {
		*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
		return E_NOT_OK;
	}

	if ((size == 0u) || (size > BOOT_SLOT_IMAGE_MAX)) {
		*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
		return E_NOT_OK;
	}

	if (FlashLoader_IsActiveSlot(slot) != 0u) {
		*nrc = DCM_E_CONDITIONS_NOT_CORRECT;
		return E_NOT_OK;
	}

	if ((s_erase.active != 0u) && (s_erase.slot == slot)) {
		/* 还在擦这个槽就开始下载 —— 上位机跳步了 */
		*nrc = DCM_E_REQUEST_SEQUENCE_ERROR;
		return E_NOT_OK;
	}

	s_dl.slot     = slot;
	s_dl.base     = addr;
	s_dl.size     = size;
	s_dl.offset   = 0u;
	s_dl.tailLen  = 0u;
	s_dl.tailAddr = addr;
	s_dl.active   = 1u;

	*blockLen = FLASH_LOADER_BLOCK_SIZE;

	return E_OK;
}

Dcm_ReturnWriteMemoryType FlashLoader_WriteData(Dcm_OpStatusType opStatus, uint8_t memId,
                                                uint32_t addr, uint32_t size, uint8_t * const data,
                                                Dcm_NegativeResponseCodeType *nrc)
{
	uint32_t pos = 0u;
	uint32_t remain;
	uint32_t aligned;

	(void)opStatus;
	(void)memId;

	if ((s_dl.active == 0u) || (data == NULL) || (size == 0u)) {
		*nrc = DCM_E_REQUEST_SEQUENCE_ERROR;
		return DCM_WRITE_FAILED;
	}

	/* 地址必须严格连续：跳块会让中间留空洞，而 CRC 是通过的（空洞恰好是 0xFF
	 * 时）——这种镜像刷进去能过校验，跑起来随机崩，比直接失败危险得多。 */
	if (addr != (s_dl.base + s_dl.offset)) {
		*nrc = DCM_E_REQUEST_OUT_OF_RANGE;
		return DCM_WRITE_FAILED;
	}

	if ((size > (s_dl.size - s_dl.offset))) {
		*nrc = DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
		return DCM_WRITE_FAILED;
	}

	/* ---- 1) 先补上一块留下的尾巴 ---- */
	if (s_dl.tailLen > 0u) {
		while ((s_dl.tailLen < BOOT_PFLASH_PHRASE_SIZE) && (pos < size)) {
			s_dl.tail[s_dl.tailLen] = data[pos];
			s_dl.tailLen++;
			pos++;
		}

		if (s_dl.tailLen == BOOT_PFLASH_PHRASE_SIZE) {
			if (Platform_FlashWrite(s_dl.tailAddr, s_dl.tail, BOOT_PFLASH_PHRASE_SIZE) != E_OK) {
				*nrc = DCM_E_GENERAL_PROGRAMMING_FAILURE;
				return DCM_WRITE_FAILED;
			}
			s_dl.tailAddr += BOOT_PFLASH_PHRASE_SIZE;
			s_dl.tailLen = 0u;
		}
	}

	/* ---- 2) 整 phrase 的部分直接批量写 ---- */
	remain  = size - pos;
	aligned = remain & ~(BOOT_PFLASH_PHRASE_SIZE - 1u);

	if (aligned > 0u) {
		if (Platform_FlashWrite(addr + pos, &data[pos], aligned) != E_OK) {
			*nrc = DCM_E_GENERAL_PROGRAMMING_FAILURE;
			return DCM_WRITE_FAILED;
		}
		pos += aligned;
	}

	/* ---- 3) 余下的存成尾巴，等下一块或 TransferExit ---- */
	if (pos < size) {
		if (s_dl.tailLen == 0u) {
			s_dl.tailAddr = addr + pos;
		}
		(void)memcpy(&s_dl.tail[s_dl.tailLen], &data[pos], (size_t)(size - pos));
		s_dl.tailLen = (uint8_t)(s_dl.tailLen + (size - pos));
	}

	s_dl.offset += size;

	return DCM_WRITE_OK;
}

Std_ReturnType FlashLoader_TransferExit(Dcm_OpStatusType opStatus,
                                        Dcm_NegativeResponseCodeType *nrc)
{
	uint32_t    crc;
	Boot_MetaType meta;
	const Boot_SlotInfoType *other;
	uint32_t    nextCounter = 1u;
	uint8_t     otherSlot;

	(void)opStatus;

	if (s_dl.active == 0u) {
		*nrc = DCM_E_REQUEST_SEQUENCE_ERROR;
		return E_NOT_OK;
	}

	if (s_dl.offset != s_dl.size) {
		/* 声明要传 size 字节，实际只到了 offset —— 不能就这么写 meta */
		s_dl.active = 0u;
		*nrc = DCM_E_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
		return E_NOT_OK;
	}

	/* ---- 1) 尾巴补 0xFF 写下去 ---- */
	if (FlashLoader_FlushTail(s_dl.tailAddr, s_dl.tail, s_dl.tailLen) != E_OK) {
		s_dl.active = 0u;
		*nrc = DCM_E_GENERAL_PROGRAMMING_FAILURE;
		return E_NOT_OK;
	}
	s_dl.tailLen = 0u;

	/* ---- 2) 从 Flash 读回来算 CRC（不是算 RAM） ---- */
	crc = Crc_CalculateCRC32((const uint8_t *)s_dl.base, s_dl.size, 0xFFFFFFFFu, TRUE);

	/* ---- 3) 写 meta：TESTING + rollingCounter = 另一槽 + 1 ---- */
	otherSlot = (s_dl.slot == BOOT_SLOT_INDEX_A) ? BOOT_SLOT_INDEX_B : BOOT_SLOT_INDEX_A;
	other = BootMeta_GetSlot(otherSlot);
	if ((other != NULL) && (other->metaValid != 0u)) {
		nextCounter = other->meta.rollingCounter + 1u;
	}

	(void)memset(&meta, 0, sizeof(meta));
	meta.rollingCounter = nextCounter;
	meta.imageSize      = s_dl.size;
	meta.imageCrc       = crc;
	/* programmingCounter：本槽累计烧写次数。上一个值读不到就从 1 开始 ——
	 * 这里的目的只是寿命统计，不参与启动决策，不必强求连续。 */
	{
		const Boot_SlotInfoType *self = BootMeta_GetSlot(s_dl.slot);
		meta.programmingCounter = ((self != NULL) && (self->metaValid != 0u))
		                          ? (self->meta.programmingCounter + 1u) : 1u;
	}
	meta.state = (uint8_t)BOOT_SLOT_TESTING;
	meta.bootAttempts = 0u;

	if (BootMeta_Write(s_dl.slot, &meta) != E_OK) {
		s_dl.active = 0u;
		*nrc = DCM_E_GENERAL_PROGRAMMING_FAILURE;
		return E_NOT_OK;
	}

	s_dl.active = 0u;

	return E_OK;
}

void FlashLoader_PerformReset(void)
{
	/* 先把中断关掉：复位前如果还有 CAN 中断在跑，可能在复位序列中间
	 * 又进一次收发，把最后一条响应挤掉（上位机会看到"刷完没回应答"）。 */
	__asm volatile ("cpsid i" ::: "memory");

	/* AIRCR.SYSRESETREQ：写 0x05FA 到上半字（VECTKEY），bit2 置 1 */
	(*(volatile uint32_t *)0xE000ED0Cu) = 0x05FA0004u;

	/* 等复位生效；真复位了走不到这里 */
	for (;;) {
		__asm volatile ("nop");
	}
}
