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
    {
      Error_Handler ();
    }
  /** Activate the Over-Drive mode
   */
  if (HAL_PWREx_EnableOverDrive () != HAL_OK)
    {
      Error_Handler ();
    }
  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
      Error_Handler ();
    }
  /** RTC clock initialization
   */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  HAL_RCCEx_PeriphCLKConfig (&PeriphClkInitStruct);

  /** COnfigure the Systick interrupt timer
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
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin (GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief I2C1 initialization function
 * @param None
 * @retval None
 */
void I2C1_Init (void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_I2C1_CLK_ENABLE();

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0x0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_9;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);

  HAL_I2C_Init (&hi2c1);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief RTC configuration and alarm initialization function
 * @param None
 * @retval None
 */
void RTC_Init (void)
{
  __HAL_RCC_RTC_ENABLE();

  /* RTC configuration */
  RTCHandle.Instance = RTC;
  RTCHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RTCHandle.Init.AsynchPrediv = 127;
  RTCHandle.Init.SynchPrediv = 255;
  RTCHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  HAL_RTC_Init (&RTCHandle);

  /* RTC alarm configuration */
  RTCAlarmA.Alarm = RTC_ALARM_A;
  RTCAlarmA.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  RTCAlarmA.AlarmTime.Hours = 0;
  RTCAlarmA.AlarmTime.Minutes = 0;
  RTCAlarmA.AlarmTime.Seconds = 10;
  RTCAlarmA.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  RTCAlarmA.AlarmDateWeekDay = 1;
  HAL_RTC_SetAlarm_IT (&RTCHandle, &RTCAlarmA, RTC_FORMAT_BIN);

  HAL_NVIC_SetPriority (RTC_Alarm_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ (RTC_Alarm_IRQn);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief RTC alarm interrupt handler.
 *
 * This function is called because the HAL IRQ handler exists in the separate
 * stm32f4xx_hal_rtc source file, but is not linked to by the
 * startup_stm32f429xx.S file. In it's stead this function is called so we
 * need to link them together.
 *
 * @param None
 * @retval None
 */
void RTC_ALARM_IRQHandler (void)
{
  HAL_RTC_AlarmIRQHandler (&RTCHandle);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
 * @brief SysTick incrementing and interrupt handler.
 *
 * This function is called to increment the SysTick and because the HAL IRQ
 * handler exists in the separate stm32f4xx_hal_coretex source file, but is
 * not linked to by the startup_stm32f429xx.S file. In it's stead this function
 * is called so we need to link them together.
 *
 * @param None
 * @retval None
 */
/*void
 SysTick_Handler (void)
 {
 HAL_IncTick ();
 HAL_SYSTICK_IRQHandler ();
 }
 */
