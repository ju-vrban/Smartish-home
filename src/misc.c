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
  if (y < 10)
    y = '0' + y;
  while (y >= power)
    power *= 10;
  int result;
  result=power;
  return x * power + y;
}

int concat (int x, int y)
{
  int temp = y;
  while (y != 0)
    {
      x *= 10;
      y /= 10;
    }
  return x + temp;
}
