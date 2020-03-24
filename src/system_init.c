/**
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin (GPIOD, GPIO_MAIN_ENTRANCE_LIGHT | GPIO_BATHROOM_LIGHT,
                     GPIO_PIN_RESET);

  HAL_GPIO_WritePin (
      GPIOG,
      GPIO_ELECTROMAGNET_ONE_LIVING | GPIO_ELECTROMAGNET_TWO_LIVING
          | GPIO_ELECTROMAGNET_THREE_LIVING | GPIO_ELECTROMAGNET_FOUR_LIVING
          | GPIO_ELECTROMAGNET_FOUR_BED,
      GPIO_PIN_RESET);

  HAL_GPIO_WritePin (
      GPIOF,
      GPIO_ELECTROMAGNET_ONE_BED | GPIO_ELECTROMAGNET_TWO_BED
          | GPIO_ELECTROMAGNET_THREE_BED,
      GPIO_PIN_RESET);

  HAL_GPIO_WritePin (GPIOH, GPIO_INTAKE_EXHAUST_FAN, GPIO_PIN_RESET);

  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_3 | KEYPAD_ROW_4, GPIO_PIN_RESET);

  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_1 | KEYPAD_ROW_2, GPIO_PIN_RESET);

  /**GPIO PIR/switch input configuration
   PD5      ------> GPIO_BATHROOM_PIR           #
   PD0      ------> GPIO_BATHROOM_SWITCH        #
   PD10     ------> GPIO_MAIN_ENTRANCE_PIR      #
   PD15     ------> GPIO_AUTOMATIC_MODE         #
   */
  GPIO_InitStruct.Pin = GPIO_BATHROOM_PIR | GPIO_MAIN_ENTRANCE_PIR | GPIO_AUTOMATIC_MODE
      | GPIO_BATHROOM_SWITCH;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  /**GPIO microwave radar sensor input configuration
     PF6      ------> GPIO_LIVING_MICROWAVE_SEN #
     */
    GPIO_InitStruct.Pin = GPIO_LIVING_MICROWAVE_SEN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init (GPIOF, &GPIO_InitStruct);

  /**GPIO switch input configuration
   PD6      ------> GPIO_LIVING_ROOM_ENCODER_SW #
   PD7      ------> GPIO_BEDROOM_ENCODER_SW     #
   */
  GPIO_InitStruct.Pin = GPIO_LIVING_ROOM_ENCODER_SW
      | GPIO_BEDROOM_ENCODER_SW;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);

  /**GPIO light output configuration
   PD11     ------> GPIO_MAIN_ENTRANCE_LIGHT    #
   PD14     ------> GPIO_BATHROOM_LIGHT         #
   */
  GPIO_InitStruct.Pin = GPIO_MAIN_ENTRANCE_LIGHT | GPIO_BATHROOM_LIGHT;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  /**TIM3 encoder GPIO configuration
   PB4     ------> TIM3_LIVING_ROOM_ENCODER_CH1 #
   PB5     ------> TIM3_LIVING_ROOM_ENCODER_CH2 #
   */
  GPIO_InitStruct.Pin = TIM3_LIVING_ROOM_ENCODER_CH1
      | TIM3_LIVING_ROOM_ENCODER_CH2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);


  /**TIM4 encoder GPIO configuration
   PD12    ------> TIM4_BEDROOM_ENCODER_CH1 #
   PD13    ------> TIM4_BEDROOM_ENCODER_CH2 #
   */
  GPIO_InitStruct.Pin = TIM4_BEDROOM_ENCODER_CH1|TIM4_BEDROOM_ENCODER_CH2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  /**TIM12 PWM GPIO Configuration
   PB14     ------> TIM12_PWM_CH1    LIVING ROOM #
   PB15     ------> TIM12_PWM_CH2    BEDROOM     #
   */
  GPIO_InitStruct.Pin = TIM12_PWM_CH1 | TIM12_PWM_CH2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_TIM12;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);

  /**GPIO stepper motor output configuration

   PG10     ------> GPIO_ELECTROMAGNET_TWO_LIVING   #
   PG11     ------> GPIO_ELECTROMAGNET_FOUR_LIVING  #
   PG13     ------> GPIO_ELECTROMAGNET_THREE_LIVING #
   PG15     ------> GPIO_ELECTROMAGNET_ONE_LIVING   #
   */
  GPIO_InitStruct.Pin = GPIO_ELECTROMAGNET_ONE_LIVING
      | GPIO_ELECTROMAGNET_TWO_LIVING | GPIO_ELECTROMAGNET_THREE_LIVING
      | GPIO_ELECTROMAGNET_FOUR_LIVING;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);

  /**GPIO blinds switch input configuration
   PF11     ------> GPIO_LIVING_ROOM_SWITCH_RAISE #
   PF12     ------> GPIO_BEDROOM_SWITCH_RAISE     #
   PF13     ------> GPIO_BEDROOM_SWITCH_LOWER     #
   PF15     ------> GPIO_LIVING_ROOM_SWITCH_LOWER #
   */
  GPIO_InitStruct.Pin = GPIO_LIVING_ROOM_SWITCH_RAISE
      | GPIO_BEDROOM_SWITCH_RAISE | GPIO_BEDROOM_SWITCH_LOWER
      | GPIO_LIVING_ROOM_SWITCH_LOWER;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOF, &GPIO_InitStruct);

  /**GPIO dangerous gasses input configuration
   PG12     ------> GPIO_DANGEROUS_GASES  #
   */
  GPIO_InitStruct.Pin = GPIO_DANGEROUS_GASES;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);

  /**GPIO intake fan output configuration
   PH2      ------> GPIO_INTAKE_EXHAUST_FAN #
   */
  GPIO_InitStruct.Pin = GPIO_INTAKE_EXHAUST_FAN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOH, &GPIO_InitStruct);

  /**GPIO IR fire sensor input configuration
   PG1      ------> GPIO_FIRE_IR_SENSOR #
   */
  GPIO_InitStruct.Pin = GPIO_FIRE_IR_SENSOR;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);

  /**GPIO Reed relay input configuration
   PE6      ------> GPIO_FORCEFUL_ENTRY #
   */
  GPIO_InitStruct.Pin = GPIO_FORCEFUL_ENTRY;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);

  /**GPIO keypad output configuration
   PE2      ------> KEYPAD_ROW_3  #
   PE4      ------> KEYPAD_ROW_4  #
   */
  GPIO_InitStruct.Pin = KEYPAD_ROW_3 | KEYPAD_ROW_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);

  /**GPIO keypad intput configuration
   PE5     ------> KEYPAD_COLUMN_1  #
   */
  GPIO_InitStruct.Pin = KEYPAD_COLUMN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);

  /**GPIO keypad intput configuration
   PF2     ------> KEYPAD_COLUMN_2  #
   PF8     ------> KEYPAD_COLUMN_3  #
   PF9     ------> KEYPAD_COLUMN_4  #
   */
  GPIO_InitStruct.Pin = KEYPAD_COLUMN_2 | KEYPAD_COLUMN_3 | KEYPAD_COLUMN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init (GPIOF, &GPIO_InitStruct);

  /**GPIO keypad output configuration
   PG2      ------> KEYPAD_ROW_1  #
   PG3      ------> KEYPAD_ROW_2  #
   */
  GPIO_InitStruct.Pin = KEYPAD_ROW_1 | KEYPAD_ROW_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief I2C1 initialization function for the
 *        external RTC
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

  /**GPIO I2C1 pin configuration
   PB6     ------> I2C1 SCL #
   PB9     ------> I2C1 SDA #
   */
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
 * @brief I2C2 16x1 LCD initialization
 *
 *Clock speed is 100 kHz because of the max frequency of the pcf8574
 *
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

  /**GPIO  I2C2 pin configuration
   PB10      ------> I2C2 SCL #
   PB11      ------> I2C2 SDA #
   */
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
 * @brief I2C3 Initialization Function
 * @param None
 * @retval None
 */
void I2C3_LCD_Init (void)
{
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init (&hi2c3) != HAL_OK)
    Error_Handler ();

  /** Configure Analogue filter
   */
  if (HAL_I2CEx_ConfigAnalogFilter (&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    Error_Handler ();

  /** Configure Digital filter
   */
  if (HAL_I2CEx_ConfigDigitalFilter (&hi2c3, 0) != HAL_OK)
    Error_Handler ();
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
  htim3.Init.Period = 100;
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

  HAL_TIM_Encoder_Start (&htim3, TIM_CHANNEL_ALL);
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
  htim4.Init.Period = 100;
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

  HAL_TIM_Encoder_Start (&htim4, TIM_CHANNEL_ALL);
}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  **/
void TIM5_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 899;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 499;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim5);

}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief Initialization function for TIM12 in PWM mode for channels 1 and 2
 *        with a frequency of 200 Hz for the living room and bedroom light
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

/**
 * @brief DAC Initialization Function
 * @param None
 * @retval None
 */
void DAC_Init (void)
{
  DAC_ChannelConfTypeDef Config =
    { 0 };

  /** DAC Initialization
   */
  hdac.Instance = DAC;
  if (HAL_DAC_Init (&hdac) != HAL_OK)
    Error_Handler ();

  /** DAC channel OUT1 config
   */
  Config.DAC_Trigger = DAC_TRIGGER_T2_TRGO;
  Config.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel (&hdac, &Config, DAC_CHANNEL_1) != HAL_OK)
    Error_Handler ();

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
void TIM2_dac_Init (void)
{
  TIM_ClockConfigTypeDef ClockSourceConfig =
    { 0 };
  TIM_MasterConfigTypeDef MasterConfig =
    { 0 };

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 89;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 399;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init (&htim2) != HAL_OK)
    Error_Handler ();

  ClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource (&htim2, &ClockSourceConfig) != HAL_OK)
    Error_Handler ();

  MasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization (&htim2, &MasterConfig) != HAL_OK)
    Error_Handler ();
}

/**
 * Enable DMA controller clock
 */
void DMA_Init (void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority (DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ (DMA1_Stream5_IRQn);

}

void TIM9_us_delay_Init (void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig =
    { 0 };

  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 180 - 1;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 0xffff - 1;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init (&htim9) != HAL_OK)
    Error_Handler ();

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource (&htim9, &sClockSourceConfig) != HAL_OK)
    Error_Handler ();
}

