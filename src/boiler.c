/**
 * boiler.c
 *
 *  Created on: Feb 28, 2020
 *      Author: jurica
 */

#include "boiler.h"

 /**
     *  water temp sensor inserted inside the water heater, combined with
     *  an analog to digital converter
     */
void check_Boiler_Temp (void)
{
  const float waterTemp = 25.00;
  if (ds18b20.temperature <= waterTemp && ds18b20.temperature >= waterTemp)
    {
//      HAL_GPIO_WritePin(GPIOF, )
    }
}

/**
 * reads the temp and turns the boiler on depending on the selected preferences
 */
void set_Boiler_Temp (void)
{

}
