#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "stm32f4xx_hal.h"

  I2C_HandleTypeDef hi2c1;
  RTC_HandleTypeDef RTCHandle;
  RTC_AlarmTypeDef RTCAlarmA;
  GPIO_InitTypeDef GPIO_InitStruct;

  void SystemClock_Config (void);
  void GPIO_Init (void);
  void I2C1_Init (void);
  void RTC_Init (void);
  void TC_ALARM_IRQHandler (void);
  void SysTick_Handler (void);

#ifdef __cplusplus
}
#endif

#endif
