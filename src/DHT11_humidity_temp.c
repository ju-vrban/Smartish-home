/*
 * DHT11_humidity_temp.c
 *
 *  Created on: Feb 28, 2020
 *      Author: jurica
 */

#include "DHT11_humidity_temp.h"

void GPIO_serial_input (void)
{
  GPIO_InitStruct.Pin = DHT11_SERIAL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);
}

void GPIO_serial_output (void)
{
  GPIO_InitStruct.Pin = DHT11_SERIAL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);
}

void DHT11_Start (void)
{
  static long int lastConversion = 0;

  GPIO_serial_output ();

  HAL_GPIO_WritePin (GPIOE, DHT11_SERIAL_PIN, 0);

  if (HAL_GetTick () - lastConversion >= 18L)
    {
      lastConversion = HAL_GetTick ();
      GPIO_serial_input ();
    }
}

uint8_t DHT11_Check_Response (void)
{
  uint8_t Response = 0;

  delay_us (40);

  if (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN) == GPIO_PIN_RESET)
    {
      delay_us (80);
      if (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN)
          == GPIO_PIN_SET)
        Response = 1;
      else
        Response = -1;
    }
  while (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN) == GPIO_PIN_SET)
    {
    }

  return Response;
}

uint8_t DHT11_Read (void)
{
  uint8_t i = 0;
  uint8_t j;

  for (j = 0; j < 8; j++)
    {
      while (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN)
          == GPIO_PIN_RESET)
        {
        }

      delay_us (40);

      if (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN)== GPIO_PIN_RESET)

        i &= ~(1 << (7 - j));   // write 0

      else
        i |= (1 << (7 - j)); // else write 1

      while ((HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN)))
        {
        }
    }

  return i;
}
