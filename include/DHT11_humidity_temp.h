#ifndef __DHT11_HUMIDITY_TEMP_H
#define __DHT11_HUMIDITY_TEMP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define DHT11_SERIAL_PIN    GPIO_PIN_0

  typedef struct
    {
      uint8_t humidity;
      uint8_t humidity_dec;
      uint8_t temp;
      uint8_t temp_dec;
      uint8_t err_checksum;
    }DHT11;

  DHT11 dht11;

  void GPIO_Serial_Input(void);
  void GPIO_Serial_Output (void);
  void DHT11_Start (void);
  uint8_t DHT11_Check_Response (void);
  uint8_t DHT11_Read (void);
  void DHT11_Data_Transfer(void);

#ifdef __cplusplus
}
#endif

#endif
