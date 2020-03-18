#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

  /* GPIO switch*/
#define GPIO_BATHROOM_PIR                 GPIO_PIN_5
#define GPIO_LIVING_ROOM_ENCODER_SW       GPIO_PIN_6
#define GPIO_BEDROOM_ENCODER_SW           GPIO_PIN_7
#define GPIO_BATHROOM_SWITCH              GPIO_PIN_0
#define GPIO_MAIN_ENTRANCE_PIR            GPIO_PIN_10
#define GPIO_AUTOMATIC_MODE               GPIO_PIN_15
#define GPIO_LIVING_MICROWAVE_SEN         GPIO_PIN_6

  /*GPIO light*/
#define GPIO_MAIN_ENTRANCE_LIGHT          GPIO_PIN_11
#define GPIO_BATHROOM_LIGHT               GPIO_PIN_14

  /* Timer*/
#define TIM3_LIVING_ROOM_ENCODER_CH1      GPIO_PIN_4
#define TIM3_LIVING_ROOM_ENCODER_CH2      GPIO_PIN_5
#define TIM4_BEDROOM_ENCODER_CH1          GPIO_PIN_6
#define TIM4_BEDROOM_ENCODER_CH2          GPIO_PIN_13
#define TIM12_PWM_CH1                     GPIO_PIN_14
#define TIM12_PWM_CH2                     GPIO_PIN_15

  /* Blinds stepper*/
#define GPIO_ELECTROMAGNET_ONE_LIVING     GPIO_PIN_15
#define GPIO_ELECTROMAGNET_TWO_LIVING     GPIO_PIN_10
#define GPIO_ELECTROMAGNET_THREE_LIVING   GPIO_PIN_13
#define GPIO_ELECTROMAGNET_FOUR_LIVING    GPIO_PIN_11
#define GPIO_ELECTROMAGNET_ONE_BED        GPIO_PIN_2
#define GPIO_ELECTROMAGNET_TWO_BED        GPIO_PIN_8
#define GPIO_ELECTROMAGNET_THREE_BED      GPIO_PIN_9
#define GPIO_ELECTROMAGNET_FOUR_BED       GPIO_PIN_1
#define GPIO_LIVING_ROOM_SWITCH_RAISE     GPIO_PIN_11
#define GPIO_LIVING_ROOM_SWITCH_LOWER     GPIO_PIN_15
#define GPIO_BEDROOM_SWITCH_RAISE         GPIO_PIN_12
#define GPIO_BEDROOM_SWITCH_LOWER         GPIO_PIN_13

  /* Ventilation and fire detection */
#define GPIO_DANGEROUS_GASES              GPIO_PIN_12
#define GPIO_INTAKE_EXHAUST_FAN           GPIO_PIN_2
#define GPIO_FIRE_IR_SENSOR               GPIO_PIN_1
#define GPIO_FORCEFUL_ENTRY               GPIO_PIN_6

  /* Keypad*/
#define KEYPAD_ROW_1                      GPIO_PIN_2
#define KEYPAD_ROW_2                      GPIO_PIN_3
#define KEYPAD_ROW_3                      GPIO_PIN_2
#define KEYPAD_ROW_4                      GPIO_PIN_4
#define KEYPAD_COLUMN_1                   GPIO_PIN_5
#define KEYPAD_COLUMN_2                   GPIO_PIN_2
#define KEYPAD_COLUMN_3                   GPIO_PIN_8
#define KEYPAD_COLUMN_4                   GPIO_PIN_9


#define ON  1
#define OFF 0

  I2C_HandleTypeDef hi2c1;
  I2C_HandleTypeDef hi2c2;
  I2C_HandleTypeDef hi2c3;
  GPIO_InitTypeDef  GPIO_InitStruct;
  TIM_HandleTypeDef htim2;
  TIM_HandleTypeDef htim3;
  TIM_HandleTypeDef htim4;
  TIM_HandleTypeDef htim9;
  TIM_HandleTypeDef htim12;
  DAC_HandleTypeDef hdac;
  DMA_HandleTypeDef hdma_dac1;

  void SystemClock_Config (void);
  void GPIO_Init (void);
  void I2C1_RTC_Init (void);
  void I2C2_LCD_Init (void);
  void I2C3_LCD_Init (void);
  void TIM3_Init (void);
  void TIM3_Encoder_Living_Room_Init (void);
  void TIM4_Encoder_Bedroom_Init (void);
  void TIM12_PWM_Living_Bedroom_Init (void);
  void DAC_Init (void);
  void TIM2_dac_Init (void);
  void DMA_Init (void);
  void TIM9_us_delay_Init (void);


#ifdef __cplusplus
}
#endif

#endif
