/**
 * DHT11_humidity_temp.c
 *
 *  Created on: Feb 28, 2020
 *      Author: jurica
 */

#include "DHT11_humidity_temp.h"

/**DHT11 input/output configuration
 PE0      ------> DHT11_SERIAL_PIN
 */
void GPIO_DHT11_serial_input (void)
{
  GPIO_InitStruct.Pin = DHT11_SERIAL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);
}

void GPIO_DHT11_serial_output (void)
{
  GPIO_InitStruct.Pin = DHT11_SERIAL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init (GPIOE, &GPIO_InitStruct);
}

void DHT11_Init (void)
{
  static long int lastConversion = 0;

  GPIO_DHT11_serial_output ();

  HAL_GPIO_WritePin (GPIOE, DHT11_SERIAL_PIN, 0);

  if (HAL_GetTick () - lastConversion >= 18L)
    {
      lastConversion = HAL_GetTick ();
      GPIO_DHT11_serial_input ();
    }
}

uint8_t DHT11_Check_Response (void)
{
  uint8_t Response = 0;

  delay_us (40);

  if (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN) == GPIO_PIN_RESET)
    {
      delay_us (80);
      if (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN) == GPIO_PIN_SET)
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
      while (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN) == GPIO_PIN_RESET)
        {
        }

      delay_us (40);

      if (HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN) == GPIO_PIN_RESET)

        i &= ~(1 << (7 - j));   // write 0

      else
        i |= (1 << (7 - j)); // else write 1

      while ((HAL_GPIO_ReadPin (GPIOE, DHT11_SERIAL_PIN)))
        {
        }
    }

  return i;
}

int DHT11_Data_Transfer (void)
{
  DHT11_Init ();
  DHT11_Check_Response ();

  dht11.humidity = DHT11_Read ();
  dht11.humidity_dec = DHT11_Read ();
  dht11.temp = DHT11_Read ();
  dht11.temp_dec = DHT11_Read ();
  dht11.err_checksum = DHT11_Read ();

  if (!(dht11.err_checksum
      == dht11.humidity + dht11.humidity_dec + dht11.temp + dht11.temp_dec))
    return DHT11_CHECKSUM_ERR;
  else
    return DHT11_OK;
}
