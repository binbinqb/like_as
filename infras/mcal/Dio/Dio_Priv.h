/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2024 Parai Wang <parai@foxmail.com>
 *
 * ref: Specification of DIO Driver AUTOSAR CP R19-11
 */
#ifndef DIO_PRIV_H
#define DIO_PRIV_H
/* ================================ [ INCLUDES  ] ============================================== */
#include "Std_Types.h"
#ifdef __cplusplus
extern "C" {
#endif
/* ================================ [ MACROS    ] ============================================== */
#define DET_THIS_MODULE_ID MODULE_ID_DIO

/* ================================ [ TYPES     ] ============================================== */
typedef struct {
  uint8_t port; /* the acutal Port Id */
  uint8_t pin;  /* the acutal Pin Id of the Port */
} Dio_ChannelConfigType;

typedef struct {
  const Dio_ChannelConfigType *channels;
  uint16_t numOfChannels;
} Dio_ConfigType;
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ ALIAS     ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/* 注意（本地新增注释，非 AS 原文）：
 * 这两个函数的实现不在 infras 里，由平台层提供（链接期绑定）。
 * 找实现：app/platform/cvm0146/src/DioAc.c */
void DioAc_WriteChannel(Dio_ChannelType ChannelId, const Dio_ChannelConfigType *config,
                        Dio_LevelType Level);
Dio_LevelType DioAc_ReadChannel(Dio_ChannelType ChannelId, const Dio_ChannelConfigType *config);
#ifdef __cplusplus
}
#endif
#endif /* DIO_PRIV_H */
