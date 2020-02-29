/**
 * DS18B20_water_temp.c
 *
 *  Created on: Feb 29, 2020
 *      Author: jurica
 */

#include "DS18B20_water_temp.h"

void GPIO_DS18B20_serial_input (void)
{
  GPIO_InitStruct.Pin = DS18B20_SERIAL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);
}

void GPIO_DS18B20_serial_output (void)
{
  GPIO_InitStruct.Pin = DS18B20_SERIAL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);
}

uint8_t DS18B20_Init (void)
{
  GPIO_DS18B20_serial_output ();
  HAL_GPIO_WritePin (GPIOE, DS18B20_SERIAL_PIN, GPIO_PIN_RESET);
  delay_us (480);

  GPIO_DS18B20_serial_input ();
  delay_us (80);

  if (HAL_GPIO_ReadPin (GPIOE, DS18B20_SERIAL_PIN) == GPIO_PIN_RESET)
    {
      delay_us (400);
      return 0;
    }
  else
    {
      delay_us (400);  // wait for 400 us
      return 1;
    }
}

void DS18B20_Write_Data (uint8_t data)
{
  GPIO_DS18B20_serial_output ();

  for (int i = 0; i < 8; i++)
    {
      if ((data & (1 << i)) != 0)  // if the bit is high
        {
          // write 1
          GPIO_DS18B20_serial_output ();
          HAL_GPIO_WritePin (GPIOE, DS18B20_SERIAL_PIN, GPIO_PIN_RESET);
          delay_us (1);

          GPIO_DS18B20_serial_input ();
          delay_us (60);
        }
      else  // if the bit is low
        {

          GPIO_DS18B20_serial_output ();
          HAL_GPIO_WritePin (GPIOE, DS18B20_SERIAL_PIN, GPIO_PIN_RESET);
          delay_us (60);

          GPIO_DS18B20_serial_input ();
        }
    }
}

uint8_t DS18B20_Read_Data (void)
{
  uint8_t value = 0;

  GPIO_DS18B20_serial_input ();

  for (int i = 0; i < 8; i++)
    {
      GPIO_DS18B20_serial_output ();

      HAL_GPIO_WritePin (GPIOE, DS18B20_SERIAL_PIN, GPIO_PIN_RESET);
      delay_us (2);

      GPIO_DS18B20_serial_input ();
      if (HAL_GPIO_ReadPin (GPIOE, DS18B20_SERIAL_PIN) == GPIO_PIN_SET)
        {
          value |= 1 << i;  // read = 1
        }
      delay_us (60);
    }
  return value;
}

void DS18B20_Transfer (void)
{
  static long int lastConversion = 0;
  static int statusFlag = 0;

  DS18B20_Init ();

  if (statusFlag == 0)
    {
      statusFlag = 1;
      DS18B20_Write_Data (0xCC);  // skip ROM
      DS18B20_Write_Data (0x44);  // convert t
    }
  else if (HAL_GetTick () - lastConversion >= 800L)
    {
      lastConversion = HAL_GetTick ();
      statusFlag = 0;

      DS18B20_Init ();
      DS18B20_Write_Data (0xCC);  // skip ROM
      DS18B20_Write_Data (0xBE);  // Read Scratchpad

      ds18b20.tempLow = DS18B20_Read_Data ();
      ds18b20.tempHigh = DS18B20_Read_Data ();

      ds18b20.temp = (ds18b20.tempHigh << 8) | ds18b20.tempLow;
      ds18b20.temperature = (float) ds18b20.temp / 16;
    }
}
