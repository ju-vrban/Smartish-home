/**
 * esp8266.c
 *
 *  Created on: Mar 4, 2020
 *      Author: jurica
 */

#include "esp8266.h"

void GPIO_ESP8266_Serial_Input (void)
{
  /*Configure GPIO pin : PG2 */
  GPIO_InitStruct.Pin = ESP8266_DATA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ESP8266_CONTROL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority (EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ (EXTI2_IRQn);
}

int ESP8266_Read_Data (void)
{
  static int inputData = 0;
  while (HAL_GPIO_ReadPin (GPIOG, ESP8266_CONTROL_PIN))
    {

      if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN))
        {
          esp8266input.ESP8266InputData += 1;
        }
      while (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN))
        {
          ;
        }
    }

  inputData = esp8266input.ESP8266InputData + 1;
  esp8266input.ESP8266InputData = 0;
  //      statusFlag = 0;
  return inputData;

}


