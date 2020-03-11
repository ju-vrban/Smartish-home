/**
 *  Created on: Feb 25, 2020
 *  Author    : jurica
 *
 ******************************************************************************
 * @file  : ventilation_and_heating.c
 * @brief : Source file for handling the ventilation of the house in case of
 * the presence of dangerous gases and detection and handling of fires.
 ******************************************************************************
 */

#include <ventilation_and_heating.h>

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
  static int gasesPresent = 0;
  static long int lastConversion = 0;
  if (check_For_Gases () == true && gasesPresent == 0)
    {
      gasesPresent = 1;
      HAL_GPIO_WritePin (GPIOH, GPIO_INTAKE_EXHAUST_FAN, GPIO_PIN_SET);
    }
  else if ((check_For_Gases () == false) && gasesPresent == 1)
    {
      if (HAL_GetTick () - lastConversion >= 10000L)
        {
          gasesPresent = 0;
          HAL_GPIO_WritePin (GPIOH, GPIO_INTAKE_EXHAUST_FAN, GPIO_PIN_RESET);
        }
    }
}


