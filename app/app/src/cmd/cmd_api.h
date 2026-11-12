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

#ifdef __cplusplus
extern "C" {
#endif

/* ecum_cmd.c */
void EcumCmd_RequestPostRun(void);   /**< 旧 `!u`：RUN → POST_RUN */
void EcumCmd_RequestRun(void);       /**< 旧 `!U`：POST_RUN → RUN */
void EcumCmd_Mode(void);             /**< 旧 `!q`：模式查询 */
void EcumCmd_SleepOnce(void);        /**< 旧 `!z`：睡一次 */

#ifdef __cplusplus
}
#endif

#endif /* CMD_API_H */
