#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

  void
  SystemClock_Config (void);
  void
  GPIO_Init (void);
  void
  I2C1_Init (void);
  void
  RTC_Init (void);
  void
  RTC_ALARM_IRQHandler (void);
  void
  SysTick_Handler (void);

#ifdef __cplusplus
}
#endif

#endif
