/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "main.h"

RTC_HandleTypeDef RTCHandle;
RTC_TimeTypeDef setTime;
RTC_DateTypeDef setDate;

/**
 * @brief  The application entry point.
 * @retval int
 */
int main (void)
{
  HAL_GetTick ();
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init ();

  /* Configure the system clock */
  SystemClock_Config ();

  /* Initialize all configured peripherals */
  GPIO_Init ();
  I2C1_Init ();
  LCD_Init ();

  float RTCTempSens;
  char LCDCharBuffer[10];
  uint32_t lastConversion = 0;
  uint8_t todaysDate[3] =
    { 01, 01, 00 };
  //set_Time (30, 13, 18, 3, 4, 2, 20);
  //set_Alarm1(30,30,16);
  activate_Alarm1();

  while (1)
    {
      get_Time ();


      if (HAL_GetTick () - lastConversion > 500L)
        {
          lastConversion = HAL_GetTick ();
          HAL_GPIO_TogglePin (GPIOD, GPIO_PIN_11);

          sprintf (LCDCharBuffer, "%02d:%02d:%02d", Time.hours, Time.minutes,
                   Time.seconds);
          LCD_Put_Cur (0, 0);
          LCD_Send_String (LCDCharBuffer);
          /*
           sprintf (LCDCharBuffer, "%02d-%02d-%02d", Time.date, Time.month,
           Time.year);
           LCD_Put_Cur (0,0);
           LCD_Send_String (LCDCharBuffer);

          force_Temp_Conversion ();
          RTCTempSens = get_RTC_Temp ();

          sprintf (LCDCharBuffer, "%.2f C", RTCTempSens);
          LCD_Put_Cur (1, 1);
          LCD_Send_String (LCDCharBuffer);*/
        }
    }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler (void)
{
  /* User can add his own implementation to report the HAL error return state */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
