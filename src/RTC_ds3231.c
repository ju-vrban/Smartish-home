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
uint8_t dec_To_Bcd (int val)
{
  return (uint8_t) ((val / 10 * 16) + (val % 10));
}

/**
 * @brief Transforms the binary coded decimal (bcd) time and date to decimal
 * @param val is the bcd value format
 * @return Integer decimal value of the transformed date and time
 */
int bcd_To_Dec (uint8_t val)
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

  setTime[0] = dec_To_Bcd (sec);
  setTime[1] = dec_To_Bcd (min);
  setTime[2] = dec_To_Bcd (hour);
  setTime[3] = dec_To_Bcd (day);
  setTime[4] = dec_To_Bcd (date);
  setTime[5] = dec_To_Bcd (month);
  setTime[6] = dec_To_Bcd (year);

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

  Time.seconds = bcd_To_Dec (getTime[0]);
  Time.minutes = bcd_To_Dec (getTime[1]);
  Time.hours = bcd_To_Dec (getTime[2]);
  Time.day = bcd_To_Dec (getTime[3]);
  Time.date = bcd_To_Dec (getTime[4]);
  Time.month = bcd_To_Dec (getTime[5]);
  Time.year = bcd_To_Dec (getTime[6]);
}

float get_RTC_Temp (void)
{
  uint8_t temp[2];

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0x11, 1, temp, 2, 500);

  return ((temp[0]) + (temp[1] >> 6) / 4.0);
}

void force_Temp_Conversion (void)
{
  uint8_t status = 0;
  uint8_t control = 0;

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0X0F, 1, &status, 1, 100);

  if (!(status & 0x04))
    {
      HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0X0E, 1, &control, 1, 100);
      HAL_I2C_Mem_Write (&hi2c1, DS3231_ADDRESS, 0X0E, 1,
                         (uint8_t *)(control|(0x20)), 1, 100);

    }

}

