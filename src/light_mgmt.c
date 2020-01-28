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

void mainEntranceLight(uint8_t entrancePIR)
  {
    if(entrancePIR == 1)
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
  }
