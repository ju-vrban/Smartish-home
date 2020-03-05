/**
 * esp8266.c
 *
 *  Created on: Mar 4, 2020
 *      Author: jurica
 */

#include "esp8266.h"

void GPIO_ESP8266_Control_Input (void)
{
  /*Configure GPIO pin : PG2 */
  GPIO_InitStruct.Pin = ESP8266_CONTROL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority (EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ (EXTI2_IRQn);

}
void GPIO_ESP8266_Data_Input (void)
{
  /*Configure GPIO pin : PG2 */
  GPIO_InitStruct.Pin = ESP8266_DATA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init (GPIOG, &GPIO_InitStruct);
}

int ESP8266_Read_Data (void)
{
  static int inputData = 0;
  if (HAL_GPIO_ReadPin (GPIOG, ESP8266_CONTROL_PIN))
    {
      HAL_Delay(1);
      for (int i = 0; i < 18; i++)
        {

          if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == GPIO_PIN_SET)
            {
              esp8266input.ESP8266InputData += 1;   // write 1

            }
          HAL_Delay (200);
        }
    }
  inputData = esp8266input.ESP8266InputData;
  return inputData;
}
/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
  if (GPIO_Pin == ESP8266_CONTROL_PIN)
    {
      static int statusFlag1 = 0;
      static int statusFlag2 = 0;
      int i = 1;
      int b = 1;
      long int lastConversion = 0;

      for (i = 0; i < 18; i++)
        {
          while (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == GPIO_PIN_RESET)
            {
            }

          if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == GPIO_PIN_SET)

            esp8266input.ESP8266InputData++;   // write 1

          while ((HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN)))
            {
            }
        }

      /*     while (i <= 18)
       {
       if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == 1
       && statusFlag1 == 0)
       {
       esp8266input.ESP8266InputData += 1;
       statusFlag1 = 1;
       statusFlag2 = 0;
       i++;
       }
       else if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == 0
       && statusFlag2 == 0)
       {
       statusFlag1 = 0;
       statusFlag2 = 1;
       b++;
       lastConversion = HAL_GetTick ();
       }
       else if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == 0
       && statusFlag2 == 1)
       {
       if (HAL_GetTick () - lastConversion >= 3L)
       {
       break;
       }
       }
       }
       while (currentTime - startTime <= 30L)
       {
       currentTime = HAL_GetTick ();
       if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == 1
       && statusFlag1 == 0)
       {
       ESP8266InputData += 1;
       statusFlag1 = 1;
       statusFlag2 = 0;
       }
       else if (HAL_GPIO_ReadPin (GPIOG, ESP8266_DATA_PIN) == 0
       && statusFlag2 == 0)
       {
       statusFlag1 = 0;
       statusFlag2 = 1;
       }
       }*/
    }
}
