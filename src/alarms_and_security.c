/**
 * alarms_and_security.c
 *
 *  Created on: Feb 29, 2020
 *      Author: jurica
 */

#include "alarms_and_security.h"

/**
 * @brief Calculatesthe sine value according to the formula
 * sineVal=(sin(x*2*PI/ns)+1)*((DAC_Max_Digit_Value + 1)/2)
 *
 * where ns is number of samples, and DAC_Max_Digit_Value is 0xFFF for
 * right aligned 12 bit resolution. The Output frequeny of the audio sugnal is
 * 2500 Hz, and it Turns on once a second.
 *
 *@param None
 *@retval None
 */
void gnerate_Sine_Wave (void)
{
  uint32_t sineVal[40000];
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static long int lastConversion = 0;

  for (int i = 0; i < 40000; i++)
    {
      sineVal[i] = (sin (i * 2 * PI / 400) + 1) * ((4095 + 1) / 2);
    }
  if ((HAL_GetTick () - lastConversion >= 500L) && statusFlag1 == 0)
    {
      statusFlag1 = 1;
      HAL_DAC_Start_DMA (&hdac, DAC_CHANNEL_1, sineVal, 40000, DAC_ALIGN_12B_R);
    }
  else if ((HAL_GetTick () - lastConversion >= 1000L) && statusFlag2 == 0)
    {
      statusFlag2 = 1;
      HAL_DAC_Stop_DMA (&hdac, DAC_CHANNEL_1);
    }
  else if (HAL_GetTick () - lastConversion >= 1003L)
    {
      lastConversion = HAL_GetTick ();
      statusFlag1 = 0;
      statusFlag2 = 0;
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
  if (HAL_GPIO_ReadPin (GPIOG, GPIO_DANGEROUS_GASES) == GPIO_PIN_SET
      && HAL_GPIO_ReadPin (GPIOG, GPIO_FIRE_IR_SENSOR) == GPIO_PIN_SET)
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
//      raise_Blinds_Bedroom ();
      gnerate_Sine_Wave ();

      static uint32_t lastConversion = 0L;
      static int statusFlag1 = 0;
      static int statusFlag2 = 0;

      while (check_For_Fire () == true)
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
              && (HAL_GetTick () - lastConversion <= 1005L) && statusFlag2 == 0)
            {
              statusFlag2 = 1;
              HAL_TIM_PWM_Stop (&htim12, TIM12_PWM_CH1);
              HAL_TIM_PWM_Stop (&htim12, TIM12_PWM_CH2);
            }
          else if (HAL_GetTick () - lastConversion > 1005L)
            {
              lastConversion = HAL_GetTick ();
              statusFlag1 = 0;
              statusFlag1 = 0;
            }
        }
    }
  else if (check_For_Fire () == false)
    {
      HAL_DAC_Stop_DMA (&hdac, DAC_CHANNEL_1);
    }
}

/**
 * @brief If Reed switch looses contact while the security system is active,
 *  sound the alarm
 *
 * @param None
 * @retval true or false
 */
bool check_For_Forcefull_Entrance (void)
{
  static int alarmStatus = 0;
  alarmStatus = alarm_status ();

  if (HAL_GPIO_ReadPin (GPIOG, GPIO_FORCEFUL_ENTRY)
      == GPIO_PIN_SET&& alarmStatus == ON)
    return true;
  else
    return false;
}

/**
 * @brief Returns if the alarm is active or disabled
 *
 * @param None
 * @retval true or false
 */
bool alarm_status (void)
{

}

char read_Keypad (void)
{
  /* Make ROW 1 LOW and all other ROWs HIGH */
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_1, GPIO_PIN_RESET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_2, GPIO_PIN_SET);  // Pull the R2 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_3, GPIO_PIN_SET);  // Pull the R3 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_4, GPIO_PIN_SET);  // Pull the R4 High

  if (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))   // if the Col 1 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))
        ;   // wait till the button is pressed
      return '1';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))   // if the Col 2 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))
        ;   // wait till the button is pressed
      return '2';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))   // if the Col 3 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))
        ;   // wait till the button is pressed
      return '3';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))   // if the Col 4 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))
        ;   // wait till the button is pressed
      return 'A';
    }

  /* Make ROW 2 LOW and all other ROWs HIGH */
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_1, GPIO_PIN_SET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_2, GPIO_PIN_RESET);  // Pull the R2 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_3, GPIO_PIN_SET);  // Pull the R3 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_4, GPIO_PIN_SET);  // Pull the R4 High

  if (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))   // if the Col 1 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))
        ;   // wait till the button is pressed
      return '4';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))   // if the Col 2 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))
        ;   // wait till the button is pressed
      return '5';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))   // if the Col 3 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))
        ;   // wait till the button is pressed
      return '6';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))   // if the Col 4 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))
        ;   // wait till the button is pressed
      return 'B';
    }

  /* Make ROW 3 LOW and all other ROWs HIGH */
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_1, GPIO_PIN_SET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_2, GPIO_PIN_SET);  // Pull the R2 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_3, GPIO_PIN_RESET);  // Pull the R3 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_4, GPIO_PIN_SET);  // Pull the R4 High

  if (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))   // if the Col 1 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))
        ;   // wait till the button is pressed
      return '7';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))   // if the Col 2 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))
        ;   // wait till the button is pressed
      return '8';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))   // if the Col 3 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))
        ;   // wait till the button is pressed
      return '9';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))   // if the Col 4 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))
        ;   // wait till the button is pressed
      return 'C';
    }

  /* Make ROW 4 LOW and all other ROWs HIGH */
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_1, GPIO_PIN_SET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOG, KEYPAD_ROW_2, GPIO_PIN_SET);  // Pull the R2 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_3, GPIO_PIN_SET);  // Pull the R3 High
  HAL_GPIO_WritePin (GPIOE, KEYPAD_ROW_4, GPIO_PIN_RESET);  // Pull the R4 High

  if (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))   // if the Col 1 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOE, KEYPAD_COLUMN_1)))
        ;   // wait till the button is pressed
      return '*';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))   // if the Col 2 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_2)))
        ;   // wait till the button is pressed
      return '0';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))   // if the Col 3 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_3)))
        ;   // wait till the button is pressed
      return '#';
    }

  if (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))   // if the Col 4 is low
    {
      while (!(HAL_GPIO_ReadPin (GPIOF, KEYPAD_COLUMN_4)))
        ;   // wait till the button is pressed
      return 'D';
    }
}
