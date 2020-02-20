#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define GPIO_BATHROOM_PIR           GPIO_PIN_5
#define GPIO_LIVING_ROOM_ENCODER_SW GPIO_PIN_6
#define GPIO_BEDROOM_ENCODER_SW     GPIO_PIN_7
#define GPIO_MAIN_ENTRANCE_PIR      GPIO_PIN_10
#define GPIO_MAIN_ENTRANCE_LIGHT    GPIO_PIN_11
#define GPIO_AUTOMATIC_MODE         GPIO_PIN_14


#define ON  1
#define OFF 0

  I2C_HandleTypeDef hi2c1;
  I2C_HandleTypeDef hi2c2;
  RTC_HandleTypeDef RTCHandle;
  RTC_AlarmTypeDef RTCAlarmA;
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_HandleTypeDef htim3;

  void SystemClock_Config (void);
  void GPIO_Init (void);
  void I2C1_Init (void);
  void I2C2_Init (void);
  void TIM3_Init(void);
  void TIM_PostInit(TIM_HandleTypeDef* htim);

#ifdef __cplusplus
}
#endif

#endif
