#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

  I2C_HandleTypeDef hi2c1;
  I2C_HandleTypeDef hi2c2;
  RTC_HandleTypeDef RTCHandle;
  RTC_AlarmTypeDef RTCAlarmA;
  GPIO_InitTypeDef GPIO_InitStruct;

  void SystemClock_Config (void);
  void GPIO_Init (void);
  void I2C1_Init (void);
  void I2C2_Init (void);

#ifdef __cplusplus
}
#endif

#endif
