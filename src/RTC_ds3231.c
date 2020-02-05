/*
 * RTC_ds3231.c
 *
 *  Created on: Feb 3, 2020
 *      Author: jurica
 */

#include "RTC_ds3231.h"

/**
 * @brief Transforms the decimal value to the binary coded decimal (bcd)
 *        time and date
 * @param val is the decimal value format
 * @return Bcd of the transformed date and time
 */
uint8_t decToBcd (int val)
{
  return (uint8_t) ((val / 10 * 16) + (val % 10));
}

/**
 * @brief Transforms the binary coded decimal (bcd) time and date to decimal
 * @param val is the bcd value format
 * @return Integer decimal value of the transformed date and time
 */
int bcdToDec (uint8_t val)
{
  return (int) ((val / 16 * 10) + (val % 16));
}

/**
 * @brief Sets the time in the DS3231 RTC
 * @param Inputs secounds, minutes, hour, day of the week, date month and year
 * @return None
 */
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

/**
 * @brief Reads the time the DS3231 RTC outputs
 * @param None
 * @return None
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

