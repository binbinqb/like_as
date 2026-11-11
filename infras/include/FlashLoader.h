/**
 * @file    flash_loader.h
 * @brief   A/B 分区刷写业务：擦除非活动槽、写镜像、写元数据
 *
 * @details @section FL_WHO 本模块在 Dcm 与平台之间的位置
 *          @code
 *          Dcm (0x31 / 0x34 / 0x36 / 0x37)
 *            └─► flash_loader.c      本模块：槽校验、分片擦除、对齐写入、meta 落盘
 *                  ├─► Platform_Flash*  单扇区擦 / phrase 写 / 回读校验
 *                  └─► BootMeta_*       读活动槽、写槽尾 meta
 *          @endcode
 *          Dcm 只管协议解析，不知道"槽"是什么；平台层只管裸地址擦写。
 *          "能不能刷这个槽""刷完怎么让 boot 认"这类业务判断全在这里。
 *
 *          @section FL_FLOW 一次完整升级的时序
 *          @code
 *          10 03                     扩展会话
 *          27 01 / 27 02             解锁（当前 CompareKey 恒通过，见 Dcm_Cfg.c）
 *          31 01 FF00 <addr> <size>  擦除非活动槽（**分片**，见下）
 *          34 00 44 <addr> <size>    请求下载（校验槽与长度）
 *          36 <seq> <data>           逐块写入（每块最多 120 字节）
 *          37                        写 meta → 新槽变 TESTING，rc+1
 *          11 01                     复位 → boot 跳新槽
 *          @endcode
 *
 *          @section FL_ERASE 擦除为什么要分片
 *          一个槽 448 KB = 224 个扇区，每扇区擦除约 25 ms，一次擦完要 5.6 秒。
 *          而 UDS 的 P2（ECU 收到请求到给出响应的最长时间）只有 50 ms，
 *          P2*（发过 0x78 之后）5 秒 —— 同步擦完必然超时。
 *
 *          所以擦除例程每次 `MainFunction` 只擦 **1 个扇区**，返回
 *          `E_NOT_OK + nrc=0x78`；Dcm 的 `Dsd_HandleRequest` 在
 *          `DCM_PENDING` 状态下每个主循环周期会重新调用本函数，直到返回 `E_OK`。
 *          这期间 Dcm 会按 P2/P2* 自动补发 0x78，上位机不会超时。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-11 | binbina | 首版：擦除/下载/校验例程 + meta 落盘 |
 */

#ifndef FLASH_LOADER_H
#define FLASH_LOADER_H

#include "Dcm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================ [ 常量 ] ============================ */

/**
 * @brief 0x31 例程号：擦除非活动槽
 * @note  请求参数为 8 字节：`<起始地址 4B> <字节数 4B>`，**大端**。
 *        地址必须正好等于某个槽的基址，否则拒绝 —— 允许任意地址擦除
 *        等于把"擦错槽"这种事故留给上位机去犯。
 */
#define FLASH_LOADER_RID_ERASE      (0xFF00u)

/**
 * @brief 0x31 例程号：校验已写入的镜像
 * @note  请求参数 12 字节：`<起始地址 4B> <字节数 4B> <期望CRC32 4B>`。
 *        响应 1 字节：0 = 一致，1 = 不一致。
 */
#define FLASH_LOADER_RID_CHECK      (0xFF01u)

/**
 * @brief 0x36 每块的最大数据字节数
 *
 * @details 由 `DCM_RX_BUF_SIZE`(128) 反推：请求帧 = SID(1) + blockSeq(1) + data，
 *          所以理论上最多 126 字节。这里取 **120** 而不是 126，是因为
 *          120 是 8 的倍数 —— 每次 `Platform_FlashWrite` 都能整 phrase 写，
 *          少一次"攒尾巴"的路径，也就少一个出错点。
 *          （除最后一块外；最后一块的余数由本模块补 0xFF 后写入。）
 */
#define FLASH_LOADER_BLOCK_SIZE     (120u)

/* ============================ [ 接口 ] ============================ */

/**
 * @brief 初始化：扫描两个槽的 meta，缓存活动槽
 * @pre  `BootMeta_Init()` 已调用（`BootApp_Init()` 里已经调过）
 * @note 刷写期间**不允许切换活动槽**，所以这里只扫一次；如果运行中被别的
 *       路径改了 meta，判断会失真 —— 当前没有这种路径。
 */
void FlashLoader_Init(void);

/**
 * @brief 0x31 例程 `FF00`：擦除非活动槽（分片，可 pending）
 * @param[in]     dataIn  `&reqData[3]`，即例程号之后的参数
 * @param[in]     opStatus `DCM_INITIAL` 首次 / `DCM_PENDING` 续做 / `DCM_CANCEL` 放弃
 * @param[out]    dataOut  `&resData[3]`，写 1 字节状态（0 = 成功）
 * @param[in,out] len      入：可用长度；出：实际写入长度
 * @param[out]    nrc      负响应码（返回 E_NOT_OK 时必须填）
 * @retval E_OK     擦除完成
 * @retval E_NOT_OK 参数错 / 正在擦活动槽 / 擦除失败 / 未完成（nrc=0x78）
 */
Std_ReturnType FlashLoader_EraseStart(const uint8_t *dataIn, Dcm_OpStatusType opStatus,
                                      uint8_t *dataOut, uint16_t *len,
                                      Dcm_NegativeResponseCodeType *nrc);

/**
 * @brief 0x31 例程 `FF01`：校验镜像 CRC32（同步完成，不需要 pending）
 * @param[in]     dataIn  `<addr 4B> <size 4B> <crc 4B>`
 * @param[in]     opStatus 未使用
 * @param[out]    dataOut  1 字节：0 = 一致 / 1 = 不一致
 * @param[in,out] len      入：可用长度；出：1
 * @param[out]    nrc      负响应码
 * @retval E_OK     校验执行完毕（**结果在 dataOut 里**，不是返回值）
 * @retval E_NOT_OK 参数错
 */
Std_ReturnType FlashLoader_CheckStart(const uint8_t *dataIn, Dcm_OpStatusType opStatus,
                                      uint8_t *dataOut, uint16_t *len,
                                      Dcm_NegativeResponseCodeType *nrc);

/**
 * @brief 0x34：请求下载，登记目标槽与长度
 * @param[in]     opStatus 未使用
 * @param[in]     dfi      dataFormatIdentifier，必须为 0（不压缩不加密）
 * @param[in]     memId    未使用（按 SWS_Dcm_91070 固定传 0）
 * @param[in]     addr     目标地址，必须正好是某个槽的基址
 * @param[in]     size     镜像字节数
 * @param[in,out] blockLen 出：每块最大字节数（`FLASH_LOADER_BLOCK_SIZE`）
 * @param[out]    nrc      负响应码
 * @retval E_OK     可以开始传
 * @retval E_NOT_OK 地址非法 / 长度越界 / 目标是活动槽
 */
Std_ReturnType FlashLoader_RequestDownload(Dcm_OpStatusType opStatus, uint8_t dfi, uint8_t memId,
                                           uint32_t addr, uint32_t size, uint32_t *blockLen,
                                           Dcm_NegativeResponseCodeType *nrc);

/**
 * @brief 0x36：写一块数据
 * @param[in]  opStatus 未使用（写单块是同步完成的）
 * @param[in]  memId    未使用
 * @param[in]  addr     本块起始地址（由 Dcm 按已偏移量算好）
 * @param[in]  size     本块字节数
 * @param[in]  data     数据
 * @param[out] nrc      负响应码
 * @return `DCM_WRITE_OK` / `DCM_WRITE_FAILED`
 * @note  不足 8 字节的尾巴会暂存，等下一块拼满或由 `TransferExit` 补 0xFF 写入。
 */
Dcm_ReturnWriteMemoryType FlashLoader_WriteData(Dcm_OpStatusType opStatus, uint8_t memId,
                                                uint32_t addr, uint32_t size, uint8_t * const data,
                                                Dcm_NegativeResponseCodeType *nrc);

/**
 * @brief 0x37：结束传输 —— 写尾巴、算 CRC、写 meta
 *
 * @details 三件事，顺序不能变：
 *          1. 把不足一个 phrase 的尾巴补 0xFF 写入（否则 CRC 会算到未写区域）；
 *          2. 从 **Flash 读回来**算 CRC32（不是算 RAM 里的，那样验证不了"真的写进去了"）；
 *          3. 写 meta：`state = TESTING`、`rollingCounter = 另一槽 + 1`。
 *             写完这一刻起，新槽就是 boot 眼中的"更新的版本"。
 *
 * @param[in]  opStatus 未使用
 * @param[out] nrc      负响应码
 * @retval E_OK     完成，下次复位 boot 会跳新槽
 * @retval E_NOT_OK 没有进行中的下载 / 数据没传完 / 写 meta 失败
 * @warning 本函数不校验"新镜像能不能跑" —— 那由 boot 的 TESTING/attempts
 *          机制保证（三次起不来自动回滚）。
 */
Std_ReturnType FlashLoader_TransferExit(Dcm_OpStatusType opStatus,
                                        Dcm_NegativeResponseCodeType *nrc);

/**
 * @brief 复位请求（0x11 用）
 * @note  先清 `NVIC_SystemReset` 前的待处理状态；调用后不返回。
 */
void FlashLoader_PerformReset(void);

#ifdef __cplusplus
}
#endif

#endif /* FLASH_LOADER_H */
