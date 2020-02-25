/*
 * blinds.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jurica
 */

#include "blinds.h"

/**
 * @brief Stepper motor control for lowering and raising the blinds
 *  in the living room
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */

void blinds_Living_Room (float dusk, float currentTime)
{
  static int lastConversion1 = 0;
  static int lastConversion2 = 0;
  static int lastConversion3 = 0;
  static int lastConversion4 = 0;
  static int blindsStatus = RAISED;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if (((currentTime >= dusk && currentTime <= BEFORE_MIDNIGHT)
          || (currentTime >= AFTER_MIDNIGHT && currentTime <= DAWN))
          && blindsStatus == RAISED)
        {
          blindsStatus = LOWERED;
          for (int i = 0; i < 512; i++)
            {
              if (HAL_GetTick () - lastConversion1 >= 2L)
                {
                  lastConversion1 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion2 >= 2L)
                {
                  lastConversion2 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                }

              if (HAL_GetTick () - lastConversion3 >= 2L)
                {
                  lastConversion3 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion4 >= 2L)
                {
                  lastConversion4 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_SET);
                }
            }
        }
      else if ((currentTime >= DAWN && currentTime <= dusk)
          && blindsStatus == LOWERED)
        {
          blindsStatus = RAISED;
          for (int i = 0; i < 512; i++)
            {
              if (HAL_GetTick () - lastConversion1 >= 2L)
                {
                  lastConversion1 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion2 >= 2L)
                {
                  lastConversion2 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                }

              if (HAL_GetTick () - lastConversion3 >= 2L)
                {
                  lastConversion3 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion4 >= 2L)
                {
                  lastConversion4 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_SET);
                }
            }
        }
    }
  else
    {
      blinds_Living_Room_Manual ();
    }
}

/**
 * @brief Manual stepper motor control for raising and lowering the blinds
 *  in the living room
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */
void blinds_Living_Room_Manual (void)
{
  static int lastConversion1 = 0;
  static int lastConversion2 = 0;
  static int lastConversion3 = 0;
  static int lastConversion4 = 0;
  static int switchStatus = RAISED;

  if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE) == GPIO_PIN_SET)
    {

      for (int i = 0; i < 512; i++)
        {
          if (HAL_GetTick () - lastConversion1 >= 2L)
            {
              lastConversion1 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_SET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion2 >= 2L)
            {
              lastConversion2 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_SET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
            }

          if (HAL_GetTick () - lastConversion3 >= 2L)
            {
              lastConversion3 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_SET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion4 >= 2L)
            {
              lastConversion4 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_SET);
            }
        }
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET && switchStatus == RAISED)
    {
      switchStatus = LOWERED;
      for (int i = 0; i < 512; i++)
        {
          if (HAL_GetTick () - lastConversion1 >= 2L)
            {
              lastConversion1 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_SET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion2 >= 2L)
            {
              lastConversion2 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_SET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
            }

          if (HAL_GetTick () - lastConversion3 >= 2L)
            {
              lastConversion3 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_SET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion4 >= 2L)
            {
              lastConversion4 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_SET);
            }
        }
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET
      && HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE)
      == GPIO_PIN_SET)
    {
      /* Do nothing until one of the switches is released */
    }
}

/**
 * @brief Stepper motor control for lowering and raising the blinds
 *  in the bedroom
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */

void blinds_Bedroom (float dusk, float currentTime)
{
  static int lastConversion1 = 0;
  static int lastConversion2 = 0;
  static int lastConversion3 = 0;
  static int lastConversion4 = 0;
  static int blindsStatus = RAISED;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if (((currentTime >= dusk && currentTime <= BEFORE_MIDNIGHT)
          || (currentTime >= AFTER_MIDNIGHT && currentTime <= DAWN))
          && blindsStatus == RAISED)
        {
          blindsStatus = LOWERED;
          for (int i = 0; i < 512; i++)
            {
              if (HAL_GetTick () - lastConversion1 >= 2L)
                {
                  lastConversion1 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion2 >= 2L)
                {
                  lastConversion2 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                }

              if (HAL_GetTick () - lastConversion3 >= 2L)
                {
                  lastConversion3 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion4 >= 2L)
                {
                  lastConversion4 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_SET);
                }
            }
        }
      else if ((currentTime >= DAWN && currentTime <= dusk)
          && blindsStatus == LOWERED)
        {
          blindsStatus = RAISED;
          for (int i = 0; i < 512; i++)
            {
              if (HAL_GetTick () - lastConversion1 >= 2L)
                {
                  lastConversion1 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion2 >= 2L)
                {
                  lastConversion2 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                }

              if (HAL_GetTick () - lastConversion3 >= 2L)
                {
                  lastConversion3 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_SET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_RESET);
                }
              if (HAL_GetTick () - lastConversion4 >= 2L)
                {
                  lastConversion4 = HAL_GetTick ();
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                     GPIO_PIN_RESET);
                  HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                     GPIO_PIN_SET);
                }
            }
        }
    }
  else
    {
      blinds_Bedroom_Manual ();
    }
}

/**
 * @brief Manual stepper motor control for raising and lowering the blinds
 *  in the bedroom
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */
void blinds_Bedroom_Manual (void)
{
  static int lastConversion1 = 0;
  static int lastConversion2 = 0;
  static int lastConversion3 = 0;
  static int lastConversion4 = 0;
  static int switchStatus = RAISED;

  if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE) == GPIO_PIN_SET)
    {

      for (int i = 0; i < 512; i++)
        {
          if (HAL_GetTick () - lastConversion1 >= 2L)
            {
              lastConversion1 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_SET); // IN1 is high
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion2 >= 2L)
            {
              lastConversion2 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_SET); // IN2 is high
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
            }

          if (HAL_GetTick () - lastConversion3 >= 2L)
            {
              lastConversion3 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_SET); // IN3 is high
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion4 >= 2L)
            {
              lastConversion4 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_SET); // IN4 is high
            }
        }
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET && switchStatus == RAISED)
    {
      switchStatus = LOWERED;
      for (int i = 0; i < 512; i++)
        {
          if (HAL_GetTick () - lastConversion1 >= 2L)
            {
              lastConversion1 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_SET);               // IN1 is high
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion2 >= 2L)
            {
              lastConversion2 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_SET);               // IN2 is high
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
            }

          if (HAL_GetTick () - lastConversion3 >= 2L)
            {
              lastConversion3 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_SET);               // IN3 is high
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_RESET);
            }
          if (HAL_GetTick () - lastConversion4 >= 2L)
            {
              lastConversion4 = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                                 GPIO_PIN_RESET);
              HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                                 GPIO_PIN_SET);               // IN4 is high
            }
        }
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET
      && HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE)
      == GPIO_PIN_SET)
    {
      /* Do nothing until one of the switches is released */
    }
}
