#ifndef __ESP8266_H
#define __ESP8266_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define ESP8266_ADDR  0x60000d00

#define TXBUFFERSIZE  (COUNTOF(aTxBuffer) - 1)
#define RXBUFFERSIZE  TXBUFFERSIZE

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#ifdef __cplusplus
}
#endif

#endif
