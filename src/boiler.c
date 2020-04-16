/**
 * boiler.c
 *
 *  Created on: Feb 28, 2020
 *      Author: jurica
 */

#include "boiler.h"

/**
 * @brief Reads the water temp and turns on/off the boiler via a relay
 * @param currentTime
 * @retval None
 */
void boiler_Control (float currentTime)
{
  static int statusFlag = 0;
  float boilerTemp = 20; //for demonstration it is 20 C but usually it is >= 40
  bool automaticMode;

  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if ((currentTime <= 7.30 || (currentTime >= 18.00 && currentTime <= 20.00))
          && ds18b20.temperature <= boilerTemp && statusFlag == 0)
        {
          statusFlag = 1;
          HAL_GPIO_WritePin (GPIOC, GPIO_BOILER, GPIO_PIN_SET);
        }
      else if (ds18b20.temperature > boilerTemp && statusFlag == 1)
        {
          statusFlag = 0;
          HAL_GPIO_WritePin (GPIOC, GPIO_BOILER, GPIO_PIN_RESET);
        }
    }
}
