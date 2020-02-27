/**
 * misc.c
 *
 *  Created on: Feb 14, 2020
 *      Author: jurica
 */

#include "misc.h"

int concatenate (int x, int y)
{
  int power = 10;
  while (y >= power)
    power *= 10;
  return x * power + y;
}

bool automatic_Mode (void)
{
  if (HAL_GPIO_ReadPin (GPIOD, GPIO_AUTOMATIC_MODE) == true)
    return true;
  else
    return false;
}

/**
 * @brief Calculatesthe sine value according to the formula
 * sineVal=(sin(x*2*PI/ns)+1)*((DAC_Max_Digit_Value + 1)/2)
 *
 * where ns is number of samples, and DAC_Max_Digit_Value is 0xFFF for
 *  right aligned 12 bit resolution
 *
 *@param None
 *@retval None
 */
void gnerate_Sine_Wave (void)
{
  uint32_t sineVal[400];
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static long int lastConversion = 0;

  for (int i = 0; i < 400; i++)
    {
      sineVal[i] = (sin (i * 2 * PI / 400) + 1) * ((4095 + 1) / 2);
    }
  if ((HAL_GetTick () - lastConversion >= 1000L)
      && (HAL_GetTick () - lastConversion < 2000L) && statusFlag1 == 0)
    {
      statusFlag1 = 1;
      HAL_TIM_Base_Start (&htim2);
      HAL_DAC_Start_DMA (&hdac, DMA_CHANNEL_7, sineVal, 100, DAC_ALIGN_12B_R);
//      HAL_DAC_SetValue (&hdac, DMA_CHANNEL_7, DAC_ALIGN_12B_R, sineVal);
    }
  else if ((HAL_GetTick () - lastConversion >= 2000L)
      && (HAL_GetTick () - lastConversion < 2005L) && statusFlag2 == 0)
    {
      statusFlag2 = 1;
      HAL_DAC_Stop_DMA (&hdac, DMA_CHANNEL_7);
    }
  else if (HAL_GetTick () - lastConversion >= 2005L)
    {
      lastConversion = HAL_GetTick ();
      statusFlag1 = 0;
      statusFlag2 = 0;
    }
}

