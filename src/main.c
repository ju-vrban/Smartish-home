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
  I2C3_LCD_Init ();

  LCD_Init ();
  LCD_Init_2 ();

  TIM2_DAC_Init ();
  TIM3_Encoder_Living_Room_Init ();
  TIM4_Encoder_Bedroom_Init ();
  TIM9_us_delay_Init ();
  TIM12_PWM_Living_Bedroom_Init ();

  DMA_Init ();
  DAC_Init ();
  DWT_Init ();

  char LCDCharBuffer[10];

  //float RTCTempSens;
  float dusk = 0;
  float currentTime = 0;
  float Temperature;
  float Humidity;

  int timeOfUpdate[3] =
    { 03, 00, 00 };
  int sysRestart = 1;
  int statusFlag1 = 0;
  int statusFlag2 = 0;
  int keySet = 0;
  int DHT11Checksum = 0;
  int DHT11StatusFlag = 0;

  uint8_t key;
  uint8_t TEMP;
  uint8_t RH;

  uint32_t lastConversion = 0;

  HAL_TIM_Base_Start (&htim2);

//  set_Time (00, 30, 14, 1, 16, 3, 20);

  HAL_TIM_Base_Start (&htim9);
//
//  LCD_Clear ();
//  HAL_Delay (1000);
//  LCD_Send_Data ('A');
//  HAL_Delay (1000);
//  LCD_Put_Cur (1, 0);
//  LCD_Send_Data ('l');
//  HAL_Delay (1000);
//  LCD_Put_Cur (1, 11);
//  LCD_Send_Data ('3');
//  HAL_Delay (1000);
//  LCD_Put_Cur (0, 5);
//  LCD_Send_Data ('Q');
//  LCD_Clear ();
  int row = 0, col = 0;

  while (1)
    {
      /*
       HAL_Delay (1500);
       LCD_Put_Cur_2 (0, 0);
       LCD_Clear_2 ();
       HAL_Delay (50);
       LCD_Clear_2 ();
       while (1)
       {
       for (int i = 0; i < 128; i++)
       {
       LCD_Put_Cur_2 (row, col);
       LCD_Send_Data_2 (i + 33);
       col++;
       if (col > 15)
       {
       col = 0;
       row++;
       }
       if (row > 1)
       row = 0;
       HAL_Delay (250);
       }
       LCD_Clear_2 ();
       HAL_Delay (1500);
       }
       */
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
      bedroom_Light (dusk, currentTime);

      blinds_Living_Room (dusk, currentTime);
//      blinds_Bedroom (dusk, currentTime);

      fire_Alarm ();
      emergency_Ventilation ();
      /*
       key = read_Keypad ();

       if (key != 0x01)
       {
       keySet = 1;
       LCD_Send_Cmd (0x85);
       LCD_Put_Cur (0, 0);
       LCD_Send_Data (key);
       }
       if (keySet == 1)
       {
       if (HAL_GetTick () - lastConversion >= 500L)
       {
       lastConversion = HAL_GetTick ();
       keySet = 0;
       key = 0x01;
       LCD_Clear ();
       }
       }
       */

      sprintf (LCDCharBuffer, "%02d:%02d:%02d", Time.hours, Time.minutes,
               Time.seconds);
      LCD_Send_Cmd (0x80|0x00);
      LCD_Send_String (LCDCharBuffer);

      if (HAL_GetTick () - lastConversion >= 1500L)
        {
          lastConversion = HAL_GetTick ();
          DHT11Checksum = DHT11_Data_Transfer ();
          DHT11StatusFlag = 0;
        }

      if (DHT11Checksum == DHT11_OK && DHT11StatusFlag == 0)
        {
          DHT11StatusFlag = 1;
//          LCD_Send_Cmd_2 (0x80 | 0x05);

          LCD_Send_String_2 ("T: ");
          LCD_Send_Data_2 ((dht11.temp / 10) + 48);
          LCD_Send_Data_2 ((dht11.temp_dec % 10) + 48);
          LCD_Send_String_2 (" C");

//          LCD_Send_Cmd_2 (0x80 | 0x40);
          LCD_Send_String_2 ("RH: ");
          LCD_Send_Data_2 ((dht11.humidity / 10) + 48);
          LCD_Send_Data_2 ((dht11.humidity_dec % 10) + 48);
          LCD_Send_String_2 (" %");
        }
      /*
       force_Temp_Conversion ();
       RTCTempSens = get_RTC_Temp ();

       sprintf (LCDCharBuffer, "%.2f C", RTCTempSens);
       LCD_Put_Cur (1, 1);
       LCD_Send_String (LCDCharBuffer);
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
void assert_failed (uint8_t *file, uint32_t line)
{
  printf ("Wrong parameters value: file %s on line %lu\r\n", file, line);
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
