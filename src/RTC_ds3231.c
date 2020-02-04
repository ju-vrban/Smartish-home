/*
 * RTC_ds3231.c
 *
 *  Created on: Feb 3, 2020
 *      Author: jurica
 */

#include "RTC_ds3231.h"



uint8_t decToBcd (int val)
{
  return (uint8_t) ((val / 10 * 16) + (val % 10));
}

int bcdToDec (uint8_t val)
{
  return (int) ((val / 16 * 10) + (val % 16));
}

void set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t day,
               uint8_t date, uint8_t month, uint8_t year)
{
  uint8_t setTime[7];

  setTime[0] = decToBcd (sec);
  setTime[1] = decToBcd (min);
  setTime[2] = decToBcd (hour);
  setTime[3] = decToBcd (day);
  setTime[4] = decToBcd (date);
  setTime[5] = decToBcd (month);
  setTime[6] = decToBcd (year);

  HAL_I2C_Mem_Write (&hi2c1, DS3231_ADDRESS, 0x00, 1, setTime, 7, 500);
}
/*
 void DS3231_ReadRawDate (DS3231_DateTypeDef *date)
 {
 uint8_t dataBuffer[7];

 HAL_I2C_Master_Transmit (&hi2c1, DS3231_ADDRESS, dataBuffer, 1, 50);
 HAL_I2C_Master_Receive (&hi2c1, DS3231_ADDRESS, dataBuffer, 7, 50);
 }
 */
void get_Time (void)
{
  uint8_t getTime[7];

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0x00, 1, getTime, 7, 500);

  Time.seconds = bcdToDec (getTime[0]);
  Time.minutes = bcdToDec (getTime[1]);
  Time.hours = bcdToDec (getTime[2]);
  Time.day = bcdToDec (getTime[3]);
  Time.date = bcdToDec (getTime[4]);
  Time.month = bcdToDec (getTime[5]);
  Time.year = bcdToDec (getTime[6]);
}

