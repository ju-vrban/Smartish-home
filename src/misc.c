/*
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
