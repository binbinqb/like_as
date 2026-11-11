/**
 * @file    Det.c
 * @brief   Default Error Tracer —— 参数错误 / 运行时错误的统一落点
 *
 * @details @section DET_WHY 为什么工程里需要它
 *          AUTOSAR 的每个模块都有 `DET_VALIDATE()` 参数检查，报错调用
 *          `Det_ReportError()`。本工程 `infras/include/Det.h` 一直只有声明、
 *          没有实现 —— 也就是说**所有**模块的 DET 检查在链接期都是悬空引用，
 *          一旦哪个模块真的把检查打开，就会 `undefined reference`。
 *
 *          当前真正调用它的只有 `infras/memory/NvM/NvM.c`（块 id 越界、
 *          未初始化就调用、空指针三类）。这三类错误如果不报，症状是
 *          "接口返回 E_NOT_OK，但不知道为什么不干活"，在板上排查代价很高。
 *
 *          @section DET_LOG 怎么看到错误
 *          `Det_ReportError()` 只做计数 + 记录最后一次的错误三元组，
 *          然后调一个**弱符号** `Det_Log()`。应用层覆盖 `Det_Log()`
 *          就能把错误打到串口（本工程 `app/app/src/main.c` 就是这么做的）：
 *          @code
 *          void Det_Log(uint16_t ModuleId, uint8_t ApiId, uint8_t ErrorId)
 *          {
 *              Platform_Printf("[det] mod=%u api=0x%02x err=0x%02x\n", ...);
 *          }
 *          @endcode
 *          弱符号的好处：不覆盖时零成本（一次空函数调用，会被内联掉），
 *          也不会因为 `infras` 层去 include 平台头而破坏分层
 *          （`infras` 里不许出现任何 `platform_*` / SDK 头）。
 *
 * @author  binbina
 * @version V1.0.0
 *
 * @par 修改记录
 * | 版本   | 日期       | 作者    | 变更说明 |
 * |--------|------------|---------|----------|
 * | V1.0.0 | 2026-11-10 | binbina | 首版：计数 + 最后一次错误 + 弱符号日志钩子 |
 */

#include <stddef.h>

#include "Det.h"

/* ============================ [ 调试可见量 ] ============================ */

/**
 * @brief 上报过的错误总数
 * @note  非 static：调试时可以直接在 `App.map` / 调试器里给这个符号下观察点，
 *        不需要改代码加打印。
 */
volatile uint32_t Det_ErrorCount;

/** @brief 最后一次错误的模块 ID（AUTOSAR Module ID） */
volatile uint16_t Det_LastModuleId;

/** @brief 最后一次错误的 API ID（模块内自增编号） */
volatile uint8_t Det_LastApiId;

/** @brief 最后一次错误的错误码（各模块的 `XXX_E_*`） */
volatile uint8_t Det_LastErrorId;

/* ============================ [ 弱符号钩子 ] ============================ */

/**
 * @brief DET 日志钩子（**弱符号**，应用层可覆盖）
 * @param[in] ModuleId 模块 ID
 * @param[in] ApiId    API ID
 * @param[in] ErrorId  错误码
 * @note  默认实现什么都不做。应用覆盖后即可把错误打到串口 / 存入故障存储。
 * @warning 本函数在**任意上下文**都可能被调用（含中断），覆盖时不要做阻塞操作。
 */
__attribute__((weak)) void Det_Log(uint16_t ModuleId, uint8_t ApiId, uint8_t ErrorId)
{
	(void)ModuleId;
	(void)ApiId;
	(void)ErrorId;
}

/* ============================ [ 接口实现 ] ============================ */

/**
 * @brief 初始化 DET
 * @param[in] ConfigPtr 配置指针（本工程无配置项，忽略）
 */
void Det_Init(const Det_ConfigType *ConfigPtr)
{
	(void)ConfigPtr;

	Det_ErrorCount  = 0u;
	Det_LastModuleId = 0u;
	Det_LastApiId    = 0u;
	Det_LastErrorId  = 0u;
}

/**
 * @brief 上报一个开发期错误
 * @param[in] ModuleId   模块 ID
 * @param[in] InstanceId 实例号（单实例传 0）
 * @param[in] ApiId      API 编号
 * @param[in] ErrorId    错误码
 * @return 恒为 `E_OK`（AUTOSAR 约定：DET 不改变调用方流程）
 */
Std_ReturnType Det_ReportError(uint16_t ModuleId, uint8_t InstanceId, uint8_t ApiId,
                               uint8_t ErrorId)
{
	(void)InstanceId;

	Det_ErrorCount++;
	Det_LastModuleId = ModuleId;
	Det_LastApiId    = ApiId;
	Det_LastErrorId  = ErrorId;

	Det_Log(ModuleId, ApiId, ErrorId);

	return E_OK;
}

/**
 * @brief 启动 DET（AUTOSAR 要求存在，本工程无额外动作）
 */
void Det_Start(void)
{
}

/**
 * @brief 上报运行时错误（与开发期错误同样处理）
 */
Std_ReturnType Det_ReportRuntimeError(uint16_t ModuleId, uint8_t InstanceId, uint8_t ApiId,
                                      uint8_t ErrorId)
{
	return Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId);
}

/**
 * @brief 上报瞬态故障（与开发期错误同样处理）
 */
Std_ReturnType Det_ReportTransientFault(uint16_t ModuleId, uint8_t InstanceId, uint8_t ApiId,
                                        uint8_t FaultId)
{
	return Det_ReportError(ModuleId, InstanceId, ApiId, FaultId);
}

/**
 * @brief 取版本信息
 * @param[out] versioninfo 版本结构
 */
void Det_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	if (versioninfo == NULL) {
		return;
	}

	versioninfo->vendorID         = 0u;
	versioninfo->moduleID         = 15u;   /* AUTOSAR: Det = 15 */
	versioninfo->sw_major_version = 1u;
	versioninfo->sw_minor_version = 0u;
	versioninfo->sw_patch_version = 0u;
}
