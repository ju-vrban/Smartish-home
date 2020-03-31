/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "math.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "light_mgmt.h"
#include "system_init.h"
#include "RTC_ds3231.h"
#include "LCD_pcf8574.h"
#include "diag/Trace.h"
#include "misc.h"
#include "blinds.h"
#include "ventilation_and_heating.h"
#include "DHT11_humidity_temp.h"
#include "DS18B20_water_temp.h"
#include "alarms_and_security.h"
#include "boiler.h"
#include "esp8266.h"
#include "dwt_delay.h"

  void  Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
