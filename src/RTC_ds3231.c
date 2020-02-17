/*
 * RTC_ds3231.c
 *
 *  Created on: Feb 3, 2020
 *      Author: jurica
 */

#include "RTC_ds3231.h"

/**
 * @brief Transforms the decimal value to the binary coded decimal (bcd)
 *        time and date.
 *
 *        Takes the first digit and shifts it by 4 places to the left
 *        to get the upper 4 bits, then it takes the modulo  of the decimal
 *        value as the the last 4 bits.
 * @param decimal is the decimal value format
 * @return Bcd of the transformed date and time
 */
uint8_t dec_To_Bcd (int decimal)
{
  return (uint8_t) ((decimal / 10 * 16) + (decimal % 10));
}

/**
 * @brief Transforms the binary coded decimal (bcd) time and date to decimal
 *
 *        Takes the BCD value of the RTC and shifts the first value 4 bits
 *        to the right to get the decimal tens digit, and performs a bitwise
 *        AND operation to get the ones digit of the number.
 * @param bcd is the bcd value format
 * @return Integer decimal value of the transformed date and time
 */
int bcd_To_Dec (uint8_t bcd)
{
  return (int) ((bcd / 16 * 10) + (bcd % 16));
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

  HAL_I2C_Mem_Write (&hi2c1, DS3231_ADDRESS, 0x00, 1, setTime, 7, 1000);
}

/**
 * @brief Reads the time the DS3231 RTC outputs
 * @param None
 * @return None
 */
void get_Time (void)
{
  uint8_t getTime[7];

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0x00, 1, getTime, 7, 1000);

  Time.seconds = bcd_To_Dec (getTime[0]);
  Time.minutes = bcd_To_Dec (getTime[1]);
  Time.hours = bcd_To_Dec (getTime[2]);
  Time.day = bcd_To_Dec (getTime[3]);
  Time.date = bcd_To_Dec (getTime[4]);
  Time.month = bcd_To_Dec (getTime[5]);
  Time.year = bcd_To_Dec (getTime[6]);
}

void get_Alarm1_Time (void)
{
  uint8_t getAlarm1Time[4];

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0x07, 1, getAlarm1Time, 4, 1000);

  AlarmTime.alarm1_seconds = bcd_To_Dec (getAlarm1Time[0] & 0x7F);
  AlarmTime.alarm1_minutes = bcd_To_Dec (getAlarm1Time[1] & 0x7F);
  AlarmTime.alarm1_hours = bcd_To_Dec (getAlarm1Time[2] & 0x3F);
  AlarmTime.alarm1_date = bcd_To_Dec (getAlarm1Time[3] & 0x3F);

}

float get_RTC_Temp (void)
{
  uint8_t temp[2];

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);

  return ((temp[0]) + (temp[1] >> 6) / 4.0);
}

void force_Temp_Conversion (void)
{
  uint8_t statusTemp = 0;
  uint8_t controlTemp = 0;

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, 0X0F, 1, &statusTemp, 1, 100);

  if (!(statusTemp & 0x04))
    {
      HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, DS3231_CONTROL_REG, 1,
                        &controlTemp, 1, 100);
      HAL_I2C_Mem_Write (&hi2c1, DS3231_ADDRESS, DS3231_CONTROL_REG, 1,
                         (uint8_t*) (controlTemp | (0x20)), 1, 100);
    }
}

void set_Alarm1 (uint8_t sec, uint8_t min, uint8_t hour, uint8_t date)
{
  uint8_t setAlarm1[4];
  uint8_t control = 0x00;

  setAlarm1[0] = dec_To_Bcd (sec);
  setAlarm1[1] = dec_To_Bcd (min) | 0x80;
  setAlarm1[2] = dec_To_Bcd (hour) | 0x80;
  setAlarm1[3] = dec_To_Bcd (date) | 0x80;

  HAL_I2C_Mem_Write (&hi2c1, DS3231_ADDRESS, 0x07, 1, setAlarm1, 4, 1000);

  HAL_I2C_Mem_Read (&hi2c1, DS3231_ADDRESS, DS3231_CONTROL_REG, 1, &control, 1,
                    200);
  HAL_I2C_Mem_Write (&hi2c1, DS3231_ADDRESS, DS3231_CONTROL_REG, 1,
                     (uint8_t*) (control | (0x05)), 1, 200);
}

void clear_Alarm1 (void)
{
  uint8_t controlReg;
  uint8_t statusReg;

  /* Clear Control Register */
  read_DS3231_Register (DS3231_CONTROL_REG, &controlReg);
  controlReg &= ~DS3231_A1IE_CONTROL_BIT;
  write_DS3231_Register (DS3231_CONTROL_REG, controlReg);

  /* Clear Status Register */
  read_DS3231_Register (DS3231_STATUS_REG, &statusReg);
  statusReg &= ~DS3231_A1F_STATUS_BIT;
  write_DS3231_Register (DS3231_STATUS_REG, statusReg);
}

void read_DS3231_Register (uint8_t regAddr, uint8_t *value)
{
  HAL_I2C_Master_Transmit (&hi2c1, DS3231_ADDRESS, &regAddr, 1, 100);
  HAL_I2C_Master_Receive (&hi2c1, DS3231_ADDRESS, value, 1, 100);
}

void write_DS3231_Register (uint8_t regAddr, uint8_t value)
{
  uint8_t buffer[2] =
    { regAddr, value };
  HAL_I2C_Master_Transmit (&hi2c1, DS3231_ADDRESS, buffer, sizeof(buffer), 100);
}
