#ifndef __ESP8266_H
#define __ESP8266_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define ESP8266_ADDR              0x60000d00

#define ESP8266_CONTROL_PIN       GPIO_PIN_2
#define ESP8266_DATA_PIN          GPIO_PIN_3

  typedef enum {
    LivingRoomLightON = 1,
    LivingRoomLightOFF,
    LivingRoomHeatingON,
    LivingRoomHeatingOFF,
    LivingRoomBlindsDown,
    LivingRoomBlindsUp,
    BedroomLightON,
    BedroomLightOFF,
    BedroomBlindsDown,
    BedroomBlindsUp,
    BathroomLightON,
    BathroomLightOFF,
    BathroomHeatingON,
    BathroomHeatingOFF,
    WaterHeaterON,
    WaterHeaterOFF,
    AutomaticModeON,
    AutomaticaModeOFF,
  }ESP8266;

  typedef struct
  {
    int ESP8266InputData;
  }ESP8266Input;

  ESP8266Input esp8266input;

  void GPIO_ESP8266_Serial_Input (void);
  int ESP8266_Read_Data (void);
  void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



#ifdef __cplusplus
}
#endif

#endif
