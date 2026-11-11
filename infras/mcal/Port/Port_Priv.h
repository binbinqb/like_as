/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2024 Parai Wang <parai@foxmail.com>
 *
 * ref: Specification of Port Driver AUTOSAR CP R22-11
 */
#ifndef PORT_PRIV_H
#define PORT_PRIV_H
/* ================================ [ INCLUDES  ] ============================================== */
#include "Std_Types.h"
#ifdef __cplusplus
extern "C" {
#endif
/* ================================ [ MACROS    ] ============================================== */
#define DET_THIS_MODULE_ID MODULE_ID_PORT

#define PORT_PIN_LEVEL_HIGH ((Port_PinLevelType)STD_HIGH)
#define PORT_PIN_LEVEL_LOW ((Port_PinLevelType)STD_LOW)

#define PORT_PIN_DEF(pinMode, pinDirection, pinLevel, port, pin, mode)                             \
  {                                                                                                \
    PORT_PIN_MODE_##pinMode, PORT_PIN_##pinDirection, PORT_PIN_LEVEL_##pinLevel, (uint8_t)port,    \
      (uint8_t)pin, (uint8_t)mode                                                                  \
  }
/* ================================ [ TYPES     ] ============================================== */
typedef uint8_t Port_PinLevelType;

typedef struct {
  Port_PinModeType pinMode; /* this may not used */
  Port_PinDirectionType pinDirection;
  Port_PinLevelType pinLevel;
  uint8_t port; /* the acutal Port Id */
  uint8_t pin;  /* the acutal Pin Id of the Port */
  uint8_t mode; /* the actual pin mode according to the Port MUX register definition */
} Port_PortPinConfigType;

struct Port_Config_s {
  const Port_PortPinConfigType *portPinConfigs;
  uint16_t numOfPortPins;
};
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ ALIAS     ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/* 注意（本地新增注释，非 AS 原文）：
 * 下面这些 `*Ac_*` 函数**只有声明，实现不在 infras 里** —— 它们由平台层提供，
 * 靠链接器把「未定义符号 U」与「已定义符号 T」配对（不是编译期 include）。
 * 读代码时直接去这里找实现：app/platform/cvm0146/src/PortAc.c */
void PortAc_PinInit(Port_PinType pinId, const Port_PortPinConfigType *config);
#ifdef __cplusplus
}
#endif
#endif /* PORT_PRIV_H */
