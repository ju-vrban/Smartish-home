/*
 * system_init.c
 *
 *  Created on: Jan 29, 2020
 *      Author: jurica
 */

#include "system_init.h"

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config (void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct =
    { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct =
    { 0 };
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct =
    { 0 };

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  //__HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK)
    Error_Handler ();

  /** Activate the Over-Drive mode
   */
  if (HAL_PWREx_EnableOverDrive () != HAL_OK)
    Error_Handler ();

  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    Error_Handler ();

  /** RTC clock initialization
   */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  HAL_RCCEx_PeriphCLKConfig (&PeriphClkInitStruct);

  /** Configure the Systick interrupt timer
   */
  HAL_SYSTICK_Config (HAL_RCC_GetHCLKFreq () / 1000);

  /** Configure the Systick
   */
  HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);

  /** Systick_IRQn interrupt configuration
   */
  HAL_NVIC_SetPriority (SysTick_IRQn, 0, 0);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
void GPIO_Init (void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin (GPIOD, GPIO_MAIN_ENTRANCE_LIGHT, GPIO_PIN_RESET);

  /**GPIO input configuration
   PD5      ------> GPIO_BATHROOM_PIR
   PD6      ------> GPIO_LIVING_ROOM_ENCODER_SW
   PD7      ------> GPIO_BEDROOM_ENCODER_SW
   PD10     ------> GPIO_MAIN_ENTRANCE_PIR
   PD14     ------> GPIO_AUTOMATIC_MODE
   */
  GPIO_InitStruct.Pin = GPIO_BATHROOM_PIR | GPIO_LIVING_ROOM_ENCODER_SW
      | GPIO_BEDROOM_ENCODER_SW | GPIO_MAIN_ENTRANCE_PIR | GPIO_AUTOMATIC_MODE;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  /**GPIO output configuration
   PD11     ------> GPIO_MAIN_ENTRANCE_LIGHT
   PD12     ------> GPIO_LIVING_ROOM_KITCHEN_LIGHT
   PD13     ------> GPIO_BATHROOM_LIGHT
   PD14     ------> GPIO_BEDROOM_LIGHT
   */
  GPIO_InitStruct.Pin = GPIO_MAIN_ENTRANCE_LIGHT
      | GPIO_LIVING_ROOM_KITCHEN_LIGHT | GPIO_BATHROOM_LIGHT
      | GPIO_BEDROOM_LIGHT;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  /**TIM3 encoder GPIO configuration
   PB4     ------> TIM3_LIVING_ROOM_ENCODER_CH1
   PB5     ------> TIM3_LIVING_ROOM_ENCODER_CH2
   */
  GPIO_InitStruct.Pin = TIM3_LIVING_ROOM_ENCODER_CH1
      | TIM3_LIVING_ROOM_ENCODER_CH2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);

  /**TIM4 encoder GPIO configuration
   PB6     ------> TIM4_BEDROOM_ENCODER_CH1
   PB7     ------> TIM4_BEDROOM_ENCODER_CH2
   */
  GPIO_InitStruct.Pin = TIM4_BEDROOM_ENCODER_CH1 | TIM4_BEDROOM_ENCODER_CH2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);

  /**TIM12 PWM GPIO Configuration
   PB14     ------> TIM12_PWM_CH1
   PB15     ------> TIM12_PWM_CH2
   */
  GPIO_InitStruct.Pin = TIM12_PWM_CH1 | TIM12_PWM_CH2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_TIM12;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief I2C1 in DMA mode initialization function for the
 *        external RTC and 16x1 LCD
 *
 * Clock speed is 100 kHz because of the max frequency of the pcf8574
 *
 * @param None
 * @retval None
 */
void I2C1_RTC_Init (void)
{
  __HAL_RCC_I2C1_CLK_ENABLE();

  /* I2C1 initialization */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
  hi2c1.Init.OwnAddress1 = 0x0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  /* Tx and Rx pin configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_9;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);

  HAL_I2C_Init (&hi2c1);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief I2C1 initialization function for the external RTC
 * @param None
 * @retval None
 */
void I2C2_LCD_Init (void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_I2C2_CLK_ENABLE();

  /* I2C1 initialization */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0x0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  /* Tx and Rx pin configuration */
  GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);

  HAL_I2C_Init (&hi2c2);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief Initialization function for TIM3 in encoder mode
 * @param None
 * @retval None
 */
void TIM3_Encoder_Living_Room_Init (void)
{
  __HAL_RCC_TIM3_CLK_ENABLE();

  TIM_Encoder_InitTypeDef Encoder =
    { 0 };
  TIM_MasterConfigTypeDef MasterConfig =
    { 0 };

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  Encoder.EncoderMode = TIM_ENCODERMODE_TI1;
  Encoder.IC1Polarity = TIM_ICPOLARITY_RISING;
  Encoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  Encoder.IC1Prescaler = TIM_ICPSC_DIV1;
  Encoder.IC1Filter = 0;
  Encoder.IC2Polarity = TIM_ICPOLARITY_RISING;
  Encoder.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  Encoder.IC2Prescaler = TIM_ICPSC_DIV1;
  Encoder.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init (&htim3, &Encoder) != HAL_OK)
    Error_Handler ();

  MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization (&htim3, &MasterConfig) != HAL_OK)
    Error_Handler ();
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief Initialization function for TIM4 in encoder mode
 * @param None
 * @retval None
 */
void TIM4_Encoder_Bedroom_Init (void)
{
  __HAL_RCC_TIM4_CLK_ENABLE();

  TIM_Encoder_InitTypeDef Encoder =
    { 0 };
  TIM_MasterConfigTypeDef MasterConfig =
    { 0 };

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  Encoder.EncoderMode = TIM_ENCODERMODE_TI1;
  Encoder.IC1Polarity = TIM_ICPOLARITY_RISING;
  Encoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  Encoder.IC1Prescaler = TIM_ICPSC_DIV1;
  Encoder.IC1Filter = 0;
  Encoder.IC2Polarity = TIM_ICPOLARITY_RISING;
  Encoder.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  Encoder.IC2Prescaler = TIM_ICPSC_DIV1;
  Encoder.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init (&htim4, &Encoder) != HAL_OK)
    Error_Handler ();

  MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization (&htim4, &MasterConfig) != HAL_OK)
    Error_Handler ();
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief Initialization function for TIM12 in PWM mode for channels 1 and 2
 *        with a frequency of 200 Hz
 * @param None
 * @retval None
 */
void TIM12_PWM_Living_Bedroom_Init (void)
{
  __HAL_RCC_TIM12_CLK_ENABLE();

  TIM_ClockConfigTypeDef ClockSourceConfig =
    { 0 };
  TIM_OC_InitTypeDef ConfigOC =
    { 0 };

  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 449;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 499;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init (&htim12) != HAL_OK)
    Error_Handler ();

  ClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource (&htim12, &ClockSourceConfig) != HAL_OK)
    Error_Handler ();

  if (HAL_TIM_PWM_Init (&htim12) != HAL_OK)
    Error_Handler ();

  ConfigOC.OCMode = TIM_OCMODE_PWM1;
  ConfigOC.Pulse = 0;
  ConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel (&htim12, &ConfigOC, TIM_CHANNEL_1) != HAL_OK)
    Error_Handler ();

  if (HAL_TIM_PWM_ConfigChannel (&htim12, &ConfigOC, TIM_CHANNEL_2) != HAL_OK)
    Error_Handler ();
}

