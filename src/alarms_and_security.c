/**
 * alarms_and_security.c
 *
 *  Created on: Feb 29, 2020
 *      Author: jurica
 */

#include "alarms_and_security.h"

/**
 * @brief If IR sensor returns high value, the function returns a true value
 *
 * @param None
 * @retval true or false
 */
bool check_For_Fire (void)
{
  if (HAL_GPIO_ReadPin (GPIOG, GPIO_DANGEROUS_GASES) == GPIO_PIN_SET
      && HAL_GPIO_ReadPin (GPIOE, GPIO_FIRE_IR_SENSOR) == GPIO_PIN_SET)
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
