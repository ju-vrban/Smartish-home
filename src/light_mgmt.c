/*
 * light_mgmt.c
 *
 *  Created on: Jan 27, 2020
 *      Author: jurica
 */

#include "stm32f4xx.h"
#include "light_mgmt.h"
#include "main.h"
#include <stdint.h>


/*
uint8_t calculate_Dusk_time (uint8_t todaysDate)
{
  get_Time ();
  uint8_t currentDate[3] =
    { Time.date, Time.month, Time.year };

  uint8_t duskTime[2];

  if (!(currentDate == todaysDate))
    {
      if (duskTime[1] > 0 && duskTime[1] < 60)
        {
          duskTime[1] -= 1;
        }
      else if (duskTime[1] == 0)
        {
          duskTime[1] = 59;
          duskTime[0] -= 1;
        }
      todaysDate = currentDate;
    }
  else
    {

    }

  return 1;
}


uint8_t calculate_Dusk_time (void)
{
  get_Time ();
  uint8_t currentTime[2] =
    { Time.hours, Time.minutes };
  uint8_t currentDate[2] =
    { Time.date, Time.month };

  if (currentDate[0]-)

    return 1;
}

int calculate_Dusk_Time (void)
{
  int date, month;
  int dailyUpdate;
  get_Time ();
  date = Time.date;
  month = Time.month;

  int duskTime[2] =
    { 19, 51 };

  if (presentDay - dayBefore == 1)
    switch (month)
      {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        if (duskTime[1] > 0 && duskTime[1] < 60)
          {
            duskTime[1] -= 1;
          }
        else if (duskTime[1] == 0)
          {
            duskTime[1] = 59;
            duskTime[0] -= 1;
          }
        break;

      case 6:
        if (date < 25)
          {
            if (duskTime[1] > 0 && duskTime[1] < 60)
              {
                duskTime[1] -= 1;
              }
            else if (duskTime[1] == 0)
              {
                duskTime[1] = 59;
                duskTime[0] -= 1;
              }
          }
        else
          {
            if (duskTime[1] >= 0 && duskTime[1] < 59)
              {
                duskTime[1] += 1;
              }
            else if (duskTime[1] == 59)
              {
                duskTime[1] = 0;
                duskTime[0] += 1;
              }
          }
        break;

      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
        if (duskTime[1] >= 0 && duskTime[1] < 59)
          {
            duskTime[1] += 1;
          }
        else if (duskTime[1] == 59)
          {
            duskTime[1] = 0;
            duskTime[0] += 1;
          }
        break;

      case 12:
        if (date > 10)
          {
            if (duskTime[1] > 0 && duskTime[1] < 60)
              {
                duskTime[1] -= 1;
              }
            else if (duskTime[1] == 0)
              {
                duskTime[1] = 59;
                duskTime[0] -= 1;
              }
          }
        else
          {
            if (duskTime[1] >= 0 && duskTime[1] < 59)
              {
                duskTime[1] += 1;
              }
            else if (duskTime[1] == 59)
              {
                duskTime[1] = 0;
                duskTime[0] += 1;
              }
          }
        break;
      }
  else
    {

    }
  return duskTime;
}


uint8_t main_Entrance_Light (uint8_t entrancePIR)
{
  int min, hour, date, month;

  get_Time ();
  min = Time.minutes;
  hour = Time.hours;
  date = Time.date;
  month = Time.month;

  uint8_t PIRInput = 0;
  uint8_t returnPIR;
  uint32_t currentTime;

  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_10) == PIRInput)
    {
      HAL_GPIO_WritePin (GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
    }
  else
    {
      HAL_GPIO_WritePin (GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
    }
}
*/
