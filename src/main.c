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
  I2C1_RTC_Init ();
  I2C2_LCD_Init ();
  LCD_Init ();
  TIM3_Encoder_Living_Room_Init ();
  TIM4_Encoder_Bedroom_Init ();
  TIM12_PWM_Living_Bedroom_Init ();

  //float RTCTempSens;
  char LCDCharBuffer[10];
  int timeOfUpdate[3] =
    { 03, 00, 00 };
  float dusk = 0;
  int sysRestart = 1;
  float currentTime = 0;
  int blindsState;

  //set_Time (30, 33, 16, 5, 13, 2, 20);

  //clear_Alarm1 ();
  //HAL_GPIO_WritePin (GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

  while (1)
    {
      get_Time ();

      if ((Time.hours == timeOfUpdate[0] && Time.minutes == timeOfUpdate[1]
          && Time.seconds == timeOfUpdate[3]) || sysRestart == 1)
        {
          dusk = calculate_Dusk_Time ();
          sysRestart = 0;
        }

      currentTime = (float) Time.hours + ((float) Time.minutes / 100);

      entrance_Light (dusk, currentTime);

      bathroom_Light ();

      living_Room_Kitchen_Light (dusk, currentTime);

      bedroom_Light (currentTime);

      blinds_Living_Room (dusk, currentTime);

      blinds_Bedroom (dusk, currentTime);

      sprintf (LCDCharBuffer, "%02d:%02d:%02d", Time.hours, Time.minutes,
               Time.seconds);

      LCD_Put_Cur (0, 0);
      LCD_Send_String (LCDCharBuffer);

      //  if (HAL_GetTick () - lastConversion > 500L)
      //    {
      //     lastConversion = HAL_GetTick ();
      //HAL_GPIO_TogglePin (GPIOD, GPIO_PIN_11);
      /*
       force_Temp_Conversion ();
       RTCTempSens = get_RTC_Temp ();

       sprintf (LCDCharBuffer, "%.2f C", RTCTempSens);
       LCD_Put_Cur (1, 1);
       LCD_Send_String (LCDCharBuffer);*/
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
