/**
 * @file    cmd_api.h
 * @brief   旧单字符命令到新 cmd 实现的桥（M-Shell 迁移期）
 *
 * @details `main.c` 的 `CmdExec` 仍保留 `!x` 入口（旧验收脚本零改动），
 *          但实际逻辑已搬进 `cmd/xxx_cmd.c`。等脚本全部切到新命令后，
 *          删掉 main.c 的 case 与本头即可。
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef CMD_API_H
#define CMD_API_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ecum_cmd.c */
void EcumCmd_RequestPostRun(void);   /**< 旧 `!u`：RUN → POST_RUN */
void EcumCmd_RequestRun(void);       /**< 旧 `!U`：POST_RUN → RUN */
void EcumCmd_Mode(void);             /**< 旧 `!q`：模式查询 */
void EcumCmd_SleepOnce(void);        /**< 旧 `!z`：睡一次 */

/* nm_cmd.c */
void NmCmd_Request(void);            /**< 旧 `!a`：请求网络（走 ComM） */
void NmCmd_Release(void);            /**< 旧 `!R`：释放网络 */
void NmCmd_PassiveStartup(void);     /**< 旧 `!A`：模拟总线唤醒（被动启动） */
void NmCmd_DumpState(void);          /**< 旧 `!m`：ComM/CanNm 状态 */

/* storage_app.c（M4） */
void StorageCmd_Dump(void);          /**< 旧 `!d`：块状态 dump */
void StorageCmd_WriteAll(void);      /**< 旧 `!c`：脏块落盘 */
void StorageCmd_Touch(void);         /**< 旧 `!w`：改 RAM → 标脏 → WriteAll */
void StorageCmd_Stress(void);        /**< 旧 `!p`：400 次写，强制 GC */
void StorageCmd_Illegal(void);       /**< 旧 `!x`：非法块 id（DET） */
bool Storage_IsReady(void);          /**< 存储栈是否就绪 */

/* com_app.c（M10） */
void ComApp_Tick(void);              /**< 主循环 10 ms 节拍：更新 TX 信号 */
void ComCmd_DumpSignals(void);       /**< 旧 `!v`：信号 dump */
void ComCmd_GroupToggle(void);       /**< 旧 `!y`：IPdu 分组启停 */

#ifdef __cplusplus
}
#endif

#endif /* CMD_API_H */
