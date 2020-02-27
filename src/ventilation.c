/**
 *  Created on: Feb 25, 2020
 *  Author    : jurica
 *
 ******************************************************************************
 * @file  : ventilation.c
 * @brief : Source file for handling the ventilation of the house in case of
 * the presence of dangerous gases and detection and handling of fires.
 ******************************************************************************
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
  static int gasesPresent = 0;
  static long int lastConversion = 0;
  if (check_For_Gases () == true && gasesPresent == 0)
    {
      gasesPresent = 1;
      HAL_GPIO_WritePin (GPIOH, GPIO_INTAKE_FAN, GPIO_PIN_SET);
      HAL_GPIO_WritePin (GPIOE, GPIO_EXHAUST_FAN, GPIO_PIN_SET);
    }
  else if ((check_For_Gases () == false) && gasesPresent == 1)
    {
      if (HAL_GetTick () - lastConversion >= 10000L)
        {
          gasesPresent = 0;
          HAL_GPIO_WritePin (GPIOH, GPIO_INTAKE_FAN, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOE, GPIO_EXHAUST_FAN, GPIO_PIN_RESET);
        }
    }
}

/**
 * @brief If IR sensor returns high value, the function returns a true value
 *
 * @param None
 * @retval true or false
 */
bool check_For_Fire (void)
{
  if (HAL_GPIO_ReadPin (GPIOG, GPIO_DANGEROUS_GASES) == GPIO_PIN_SET)
    return true;
  else
    return false;
}

/**
 * @brief Raises the blinds, starts the alarm, and starts blinking the light
 *        at 1 Hz to make inhabitants aware of the fire
 *
 * @param None
 * @retval None
 */
void fire_Alarm (void)
{
  if (check_For_Fire () == true)
    {
      raise_Blinds_Living ();
      raise_Blinds_Bedroom ();
      gnerate_Sine_Wave ();

      static long int lastConversion = 0L;
      static int statusFlag1 = 0;
      static int statusFlag2 = 0;

      while (check_For_Fire ())
        {
          if ((HAL_GetTick () - lastConversion >= 500L)
              && (HAL_GetTick () - lastConversion <= 1000L) && statusFlag1 == 0)
            {
              statusFlag1 = 1;
              HAL_TIM_PWM_Start (&htim12, TIM12_PWM_CH1);
              htim12.Instance->CCR1 = 100;
              HAL_TIM_PWM_Start (&htim12, TIM12_PWM_CH2);
              htim12.Instance->CCR2 = 100;
            }
          else if ((HAL_GetTick () - lastConversion >= 1000L)
              && (HAL_GetTick () - lastConversion <= 1015L) && statusFlag2 == 0)
            {
              statusFlag2 = 1;
              HAL_TIM_PWM_Stop (&htim12, TIM12_PWM_CH1);
              HAL_TIM_PWM_Stop (&htim12, TIM12_PWM_CH2);
            }
          else if (HAL_GetTick () - lastConversion >= 1015L)
            {
              lastConversion = HAL_GetTick ();
              statusFlag1 = 0;
              statusFlag1 = 0;
            }
        }
    }
}
