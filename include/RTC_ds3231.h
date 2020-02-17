#ifndef __RTC_DS3231_H
#define __RTC_DS3231_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define DS3231_ADDRESS      0xD0  /** I2C 7-bit slave address
                                   *  shifted 1 bit to the left
                                   */
#define DS3231_CONTROL_REG 0x0E
#define DS3231_STATUS_REG   0x0F

#define DS3231_A1F_STATUS_BIT 0x01
#define DS3231_A1IE_CONTROL_BIT 0x01

  typedef enum
    {
      Monday = 1,
      Tuesday,
      Wednesday,
      Thursday,
      Friday,
      Saturday,
      Sunday
    }day;

  typedef enum
    {
      January = 1,
      February,
      March,
      April,
      May,
      June,
      July,
      August,
      September,
      October,
      November,
      December
    }month;

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
      uint8_t alarm1_seconds;
      uint8_t alarm1_minutes;
      uint8_t alarm1_hours;
      uint8_t alarm1_day;
      uint8_t alarm1_date;
    }DS3231_RegistersTypeDef;

  DS3231_RegistersTypeDef AlarmTime;
  DS3231_DateTypeDef Time;

  uint8_t dec_To_Bcd (int decimal);
  int bcd_To_Dec (uint8_t bcd);
  void set_Time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day,
      uint8_t date, uint8_t month, uint8_t year);
  void get_Time (void);
  float get_RTC_Temp (void);
  void force_Temp_Conversion(void);
  void set_Alarm1 (uint8_t sec, uint8_t min, uint8_t hour, uint8_t date);
  void clear_Alarm1 (void);
  void get_Alarm1_Time (void);
  void read_DS3231_Register(uint8_t regAddr, uint8_t *value);
  void write_DS3231_Register (uint8_t regAddr, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif

