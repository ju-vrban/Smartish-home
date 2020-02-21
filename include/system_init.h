#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

  /* GPIO macros */
#define GPIO_BATHROOM_PIR               GPIO_PIN_5
#define GPIO_LIVING_ROOM_ENCODER_SW     GPIO_PIN_6
#define GPIO_BEDROOM_ENCODER_SW         GPIO_PIN_7
#define GPIO_MAIN_ENTRANCE_PIR          GPIO_PIN_10
#define GPIO_MAIN_ENTRANCE_LIGHT        GPIO_PIN_11
#define GPIO_LIVING_ROOM_KITCHEN_LIGHT  GPIO_PIN_12
#define GPIO_BATHROOM_LIGHT             GPIO_PIN_13
#define GPIO_BEDROOM_LIGHT              GPIO_PIN_14
#define GPIO_AUTOMATIC_MODE             GPIO_PIN_15

  /* Timer macros */
#define TIM3_LIVING_ROOM_ENCODER_CH1    GPIO_PIN_4
#define TIM3_LIVING_ROOM_ENCODER_CH2    GPIO_PIN_5
#define TIM4_BEDROOM_ENCODER_CH1        GPIO_PIN_6
#define TIM4_BEDROOM_ENCODER_CH2        GPIO_PIN_7
#define TIM12_PWM_CH1                   GPIO_PIN_14
#define TIM12_PWM_CH2                   GPIO_PIN_15

#define ON  1
#define OFF 0

  I2C_HandleTypeDef hi2c1;
  I2C_HandleTypeDef hi2c2;
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_HandleTypeDef htim3;
  TIM_HandleTypeDef htim4;
  TIM_HandleTypeDef htim12;

  void SystemClock_Config (void);
  void GPIO_Init (void);
  void I2C1_RTC_Init (void);
  void I2C2_LCD_Init (void);
  void TIM3_Init(void);
  void TIM3_Encoder_Living_Room_Init(void);
  void TIM4_Encoder_Bedroom_Init (void);
  void TIM12_PWM_Living_Bedroom_Init(void);

#ifdef __cplusplus
}
#endif

#endif
