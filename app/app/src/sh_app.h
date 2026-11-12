/**
 * @file    sh_app.h
 * @brief   Shell 应用接入（平台绑定 + 主循环推进）
 *
 * @author  binbina
 * @version V1.0.0
 */

#ifndef SH_APP_H
#define SH_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 绑定控制台并初始化 shell（UART 初始化之后调用一次）
 * @pre  Platform_Init() 已完成（UART2 可用）
 */
void ShApp_Init(void);

/**
 * @brief 主循环推进（非阻塞，每圈调用）
 */
void ShApp_Task(void);

#ifdef __cplusplus
}
#endif

#endif /* SH_APP_H */
