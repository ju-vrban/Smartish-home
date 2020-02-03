#ifndef __RTC_DS3231_H
#define __RTC_DS3231_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>

#include "main.h"
#include "stm32f4xx_hal.h"
#include "system_init.h"

#define DS3231_ADDRESS      0xD0  /** I2C 7-bit slave address
                                   *  shifted for 1 bit to the left
                                   */
#define DS3231_SECONDS      0x00
#define DS3231_ALARM1_HOURS 0x09
#define DS3231_CONTROLL     0x0E
#define DS3231_MSB_TEMP     0x11

  char *dayOfWeek[] =
    { "Ponedjeljak", "Utorak", "Srijeda", "Četvrtak", "Petak", "Subota",
      "Nedjelja"};

  volatile uint8_t transmissionReady = 0;
  volatile uint8_t conf_mode = 0;

  typedef struct
    {
      uint8_t seconds;
      uint8_t minutes;
      uint8_t hours;
      uint8_t day;
      uint8_t date;
      uint8_t month;
      uint8_t year;
    }DS3231_DateTypeDef;

  typedef struct
    {
      DS3231_DateTypeDef date;
      uint8_t alarm1_seconds;
      uint8_t alarm1_minutes;
      uint8_t alarm1_hours;
      uint8_t alarm1_day;
      uint8_t alarm1_date;
      uint8_t alarm2_seconds;
      uint8_t alarm2_minutes;
      uint8_t alarm2_hours;
      uint8_t alarm2_day;
      uint8_t alarm2_date;
      uint8_t control;
      uint8_t status;
      uint8_t aging_offset;
      uint8_t MSB_of_temp;
      uint8_t LSB_of_temp;
    }DS3231_RegistersTypeDef;

  typedef struct
    {
      uint8_t Seconds;
      uint8_t Minutes;
      uint8_t Hours;
      uint8_t Day;
      uint8_t Date;
      uint8_t Year;
      uint8_t dayOfWeek;
    }DS3231_HumanReadableFormat_TypeDef;

  DS3231_DateTypeDef Time;

  int bcdToBin(uint8_t val);
  uint8_t decToBcd(int val);
  void set_Time(uint8_t sec, uint8_t min, uint8_t  hour, uint8_t day,
                uint8_t date, uint8_t month, uint8_t year);
  void DS3231_ReadRawDate(DS3231_DateTypeDef* date);

#ifdef __cplusplus
}
#endif

#endif

