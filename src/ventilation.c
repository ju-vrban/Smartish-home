/*
 * ventilation.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jurica
 */

/**
 * @brief Source file for handling the ventilation of the house in case of
 * the presence of dangerous gases and detection of fires.
 */

#include "ventilation.h"

/**
 * @brief If dangerous gases are present the function returns a true statement
 * @param None
 * @retval true or false
 */
bool check_For_Gases (void)
{
  if (HAL_GPIO_ReadPin (GPIOG, GPIO_DANGEROUS_GASES) == GPIO_PIN_SET)
    return true;
  else
    return false;
}

/**
 * @brief Starts the ventilation system in case check_For_Gases function returns
 * a true value.
 *
 * @param None
 * @retval None
 */
void emergency_Ventilation (void)
{

}

/**
 * @brief if fire is present, returns a true value
 *
 * @param None
 * @retval true or false
 */
bool check_For_Fire (void)
{

}
