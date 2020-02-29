#ifndef __DS18B20_WATER_TEMP_H
#define __DS18B20_WATER_TEMP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define DS18B20_SERIAL_PIN  GPIO_PIN_3

  typedef struct
  {
    uint8_t tempLow;
    uint8_t tempHigh;
    uint16_t temp;
    float temperature;
  }DS18B20;

  DS18B20 ds18b20;

  void GPIO_DS18B20_serial_input (void);
  void GPIO_DS18B20_serial_output (void);
  uint8_t DS18B20_Init (void);
  void DS18B20_Write_Data (uint8_t data);
  uint8_t DS18B20_Read_Data (void);

#ifdef __cplusplus
}
#endif

#endif
