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

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init ();

  /* Configure the system clock */
  SystemClock_Config ();

  /* Initialize all configured peripherals */

  GPIO_Init ();
  I2C1_Init ();
  RTC_Init ();
  LCD_Init ();
  /*
   setTime.Hours = 23;
   setTime.Minutes = 59;
   setTime.Seconds = 45;
   HAL_RTC_SetTime (&RTCHandle, &setTime, RTC_FORMAT_BIN);

   setDate.Date = 31;
   setDate.Month = RTC_MONTH_JANUARY;
   setDate.Year = 20;
   setDate.WeekDay = RTC_WEEKDAY_FRIDAY;
   HAL_RTC_SetDate (&RTCHandle, &setDate, RTC_FORMAT_BIN);
   */
  char charBuffer[10];
  //set_Time (30, 13, 18, 3, 4, 2, 20);

  while (1)
    {
      get_Time ();
      sprintf (charBuffer, "%02d:%02d:%02d", Time.hours, Time.minutes,
               Time.seconds);
    //  trace_printf ("\n%02d:%02d:%02d", Time.hours, Time.minutes,
    //                Time.seconds);
      LCD_PutCur (0, 0);
      LCD_SendString (charBuffer);

  //    sprintf (charBuffer, "%02d-%02d-%02d", Time.date, Time.month,
   //            Time.year);
 //     trace_printf ("\n%02d-%02d-%02d", Time.date, Time.month,
 //                    Time.year);
 //     LCD_PutCur (0, 0);
 //   LCD_SendString (charBuffer);
      HAL_Delay (1000);
      /*
       HAL_RTC_SetTime (&RTCHandle, &setTime, RTC_FORMAT_BIN);
       HAL_RTC_SetDate (&RTCHandle, &setDate, RTC_FORMAT_BIN);
       HAL_Delay (400);
       HAL_GPIO_TogglePin (GPIOD, GPIO_PIN_11);


       mainEntranceLight(0x01);
       HAL_Delay(500);
       mainEntranceLight(0x00);
       HAL_Delay(500);
       */
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
