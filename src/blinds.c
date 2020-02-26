/*
 * blinds.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jurica
 */

#include "blinds.h"

void lower_Blinds_Living (void)
{
  static long int lastConversion = 0L;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;

  for (int i = 0; i < 512; i++)
    {
      if ((HAL_GetTick () - lastConversion >= 2L)
          && (HAL_GetTick () - lastConversion < 4L) && statusFlag1 == 0)
        {

          statusFlag1 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 4L)
          && (HAL_GetTick () - lastConversion < 6L) && statusFlag2 == 0)
        {
          statusFlag2 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_RESET);
        }

      else if ((HAL_GetTick () - lastConversion >= 6L)
          && (HAL_GetTick () - lastConversion < 8L) && statusFlag3 == 0)
        {
          statusFlag3 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 8L)
          && (HAL_GetTick () - lastConversion < 10L) && statusFlag4 == 0)
        {
          statusFlag4 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_SET);
        }
      else if (HAL_GetTick () - lastConversion >= 10L)
        {
          lastConversion = HAL_GetTick ();
          statusFlag1 = 0;
          statusFlag2 = 0;
          statusFlag3 = 0;
          statusFlag4 = 0;
        }
    }
}

void raise_Blinds_Living (void)
{
  static long int lastConversion = 0;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;

  for (int i = 0; i < 512; i++)
    {
      if ((HAL_GetTick () - lastConversion >= 2L)
          && (HAL_GetTick () - lastConversion < 4L) && statusFlag1 == 0)
        {
          statusFlag1 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 4L)
          && (HAL_GetTick () - lastConversion < 6L) && statusFlag2 == 0)
        {
          statusFlag2 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 6L)
          && (HAL_GetTick () - lastConversion < 8L) && statusFlag3 == 0)
        {
          statusFlag3 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 8L)
          && (HAL_GetTick () - lastConversion < 10L) && statusFlag4 == 0)
        {
          statusFlag4 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_LIVING,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_LIVING,
                             GPIO_PIN_SET);
        }
      else if (HAL_GetTick () - lastConversion >= 10L)
        {
          lastConversion = HAL_GetTick ();
          statusFlag1 = 0;
          statusFlag2 = 0;
          statusFlag3 = 0;
          statusFlag4 = 0;
        }
    }
}

/**
 * @brief Stepper motor control for lowering and raising the blinds
 *  in the living room
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */
void blinds_Living_Room (float dusk, float currentTime)
{

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
          lower_Blinds_Living ();
        }
      else if ((currentTime >= DAWN && currentTime <= dusk)
          && blindsStatus == LOWERED)
        {
          blindsStatus = RAISED;
          raise_Blinds_Living ();
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
  static int blindsStatus = RAISED;

  if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE)
      == GPIO_PIN_SET&& blindsStatus == LOWERED)
    {
      raise_Blinds_Living ();
      blindsStatus = RAISED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET && blindsStatus == RAISED)
    {
      lower_Blinds_Living ();
      blindsStatus = LOWERED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET
      && HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE)
          == GPIO_PIN_SET)
    {
      /* Do nothing until one of the switches is released */
    }
}

void lower_Blinds_Bedroom (void)
{
  static long int lastConversion = 0L;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;

  for (int i = 0; i < 512; i++)
    {
      if ((HAL_GetTick () - lastConversion >= 2L)
          && (HAL_GetTick () - lastConversion < 4L) && statusFlag1 == 0)
        {
          statusFlag1 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 4L)
          && (HAL_GetTick () - lastConversion < 6L) && statusFlag2 == 0)
        {
          statusFlag2 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 6L)
          && (HAL_GetTick () - lastConversion < 8L) && statusFlag3 == 0)
        {
          statusFlag3 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 8L)
          && (HAL_GetTick () - lastConversion < 10L) && statusFlag4 == 0)
        {
          statusFlag4 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED, GPIO_PIN_SET);
        }
      else if (HAL_GetTick () - lastConversion >= 10L)
        {
          lastConversion = HAL_GetTick ();
          statusFlag1 = 0;
          statusFlag2 = 0;
          statusFlag3 = 0;
          statusFlag4 = 0;
        }
    }
}

void raise_Blinds_Bedroom (void)
{
  static long int lastConversion = 0L;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;

  for (int i = 0; i < 512; i++)
    {
      if ((HAL_GetTick () - lastConversion >= 2L)
          && (HAL_GetTick () - lastConversion < 4L) && statusFlag1 == 0)
        {
          statusFlag1 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 4L)
          && (HAL_GetTick () - lastConversion < 6L) && statusFlag2 == 0)
        {
          statusFlag2 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 6L)
          && (HAL_GetTick () - lastConversion < 8L) && statusFlag3 == 0)
        {
          statusFlag3 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 8L)
          && (HAL_GetTick () - lastConversion < 10L) && statusFlag4 == 0)
        {
          statusFlag4 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_SET);
        }
      else if (HAL_GetTick () - lastConversion >= 10L)
        {
          lastConversion = HAL_GetTick ();
          statusFlag1 = 0;
          statusFlag2 = 0;
          statusFlag3 = 0;
          statusFlag4 = 0;
        }
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
          lower_Blinds_Bedroom ();
        }
      else if ((currentTime >= DAWN && currentTime <= dusk)
          && blindsStatus == LOWERED)
        {
          blindsStatus = RAISED;
          raise_Blinds_Bedroom ();
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

  static int blindsStatus = RAISED;

  if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE)
      == GPIO_PIN_SET&& blindsStatus == LOWERED)
    {
      raise_Blinds_Bedroom ();
      blindsStatus = RAISED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET && blindsStatus == RAISED)
    {
      lower_Blinds_Bedroom ();
      blindsStatus = LOWERED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER)
      == GPIO_PIN_SET
      && HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE)
          == GPIO_PIN_SET)
    {
      /* Do nothing until one of the switches is released */
    }
}
