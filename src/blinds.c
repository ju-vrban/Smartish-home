/**
 * blinds.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jurica
 */

#include "blinds.h"

int lower_Blinds_Living (void)
{
  static uint32_t lastTimeLowerLiving = 0;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;
  static int i = 0;

  if (i < 512)
    {
      if ((HAL_GetTick () - lastTimeLowerLiving >= 2L) && statusFlag1 == 0)
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
      else if ((HAL_GetTick () - lastTimeLowerLiving >= 4L) && statusFlag2 == 0)
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

      else if ((HAL_GetTick () - lastTimeLowerLiving >= 6L) && statusFlag3 == 0)
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
      else if ((HAL_GetTick () - lastTimeLowerLiving >= 8L) && statusFlag4 == 0)
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
      else if (HAL_GetTick () - lastTimeLowerLiving >= 10L)
        {
          lastTimeLowerLiving = HAL_GetTick ();
          statusFlag1 = 0;
          statusFlag2 = 0;
          statusFlag3 = 0;
          statusFlag4 = 0;
          i++;
        }
    }
  else if (i == 512)
    {
      i = 0;
      return 1;
    }

  return 0;
}

int raise_Blinds_Living (void)
{
  static uint32_t lastTimeRaiseLiving = 0;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;
  static int i = 0;

  if (i < 512)
    {
      if ((HAL_GetTick () - lastTimeRaiseLiving >= 2L) && statusFlag1 == 0)
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
      else if ((HAL_GetTick () - lastTimeRaiseLiving >= 4L) && statusFlag2 == 0)
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
      else if ((HAL_GetTick () - lastTimeRaiseLiving >= 6L) && statusFlag3 == 0)
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
      else if ((HAL_GetTick () - lastTimeRaiseLiving >= 8L) && statusFlag4 == 0)
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
      else if (HAL_GetTick () - lastTimeRaiseLiving >= 10L)
        {
          lastTimeRaiseLiving = HAL_GetTick ();
          statusFlag1 = 0;
          statusFlag2 = 0;
          statusFlag3 = 0;
          statusFlag4 = 0;
          i++;
        }
    }
  else if (i == 512)
    {
      i = 0;
      return 1;
    }

  return 0;
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
  static int checkBlindsStatus = 0;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if (((currentTime >= dusk && currentTime <= BEFORE_MIDNIGHT)
          || (currentTime >= AFTER_MIDNIGHT && currentTime <= DAWN))
          && blindsStatus == RAISED)
        {
          checkBlindsStatus = lower_Blinds_Living ();
          if (checkBlindsStatus == 1)
            blindsStatus = LOWERED;
        }
      else if ((currentTime >= DAWN && currentTime <= dusk)
          && blindsStatus == LOWERED)
        {

          checkBlindsStatus = raise_Blinds_Living ();
          if (checkBlindsStatus == 1)
            blindsStatus = RAISED;
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
  static int checkBlindsStatus = 0;

  if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE) == ON
      && blindsStatus == LOWERED)
    {
      checkBlindsStatus = raise_Blinds_Living ();
      if (checkBlindsStatus == 1)
        blindsStatus = RAISED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER) == ON
      && blindsStatus == RAISED)
    {
      checkBlindsStatus = lower_Blinds_Living ();
      if (checkBlindsStatus == 1)
        blindsStatus = LOWERED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER) == ON
      && HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE) == ON)
    {
      ; /* Do nothing until one of the switches is released */
    }
}

/*
int lower_Blinds_Bedroom (void)
{
  static uint32_t lastConversion = 0L;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;
  static int i = 0;
  if (i < 512)
    {
      if ((HAL_GetTick () - lastConversion >= 2L) && statusFlag1 == 0)
        {
          statusFlag1 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 4L) && statusFlag2 == 0)
        {
          statusFlag2 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 6L) && statusFlag3 == 0)
        {
          statusFlag3 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 8L) && statusFlag4 == 0)
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
          i++;
        }
    }
  else if (i == 512)
    {
      i = 0;
      return 1;
    }
  return 0;
}

int raise_Blinds_Bedroom (void)
{
  static uint32_t lastConversion = 0L;
  static int statusFlag1 = 0;
  static int statusFlag2 = 0;
  static int statusFlag3 = 0;
  static int statusFlag4 = 0;
  static int i = 0;

  if (i < 512)
    {
      if ((HAL_GetTick () - lastConversion >= 2L) && statusFlag1 == 0)
        {
          statusFlag1 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 4L) && statusFlag2 == 0)
        {
          statusFlag2 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 6L) && statusFlag3 == 0)
        {
          statusFlag3 = 1;
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_FOUR_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_THREE_BED,
                             GPIO_PIN_RESET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_TWO_BED, GPIO_PIN_SET);
          HAL_GPIO_WritePin (GPIOG, GPIO_ELECTROMAGNET_ONE_BED, GPIO_PIN_RESET);
        }
      else if ((HAL_GetTick () - lastConversion >= 8L) && statusFlag4 == 0)
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
          i++;
        }
    }
  else if (i == 512)
    {
      i = 0;
      return 1;
    }
  return 0;
}
*/

/**
 * @brief Stepper motor control for lowering and raising the blinds
 *  in the bedroom
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */
/*
void blinds_Bedroom (float dusk, float currentTime)
{
  static int blindsStatus = RAISED;
  static int checkBlindsStatus = 0;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if (((currentTime >= dusk && currentTime <= BEFORE_MIDNIGHT)
          || (currentTime >= AFTER_MIDNIGHT && currentTime <= DAWN))
          && blindsStatus == RAISED)
        {
          checkBlindsStatus = lower_Blinds_Bedroom ();
          if (checkBlindsStatus == 1)
            blindsStatus = LOWERED;
        }
      else if ((currentTime >= DAWN && currentTime <= dusk)
          && blindsStatus == LOWERED)
        {
          checkBlindsStatus = raise_Blinds_Bedroom ();
          if (checkBlindsStatus == 1)
            blindsStatus = RAISED;
        }
    }
  else
    {
      blinds_Bedroom_Manual ();
    }
}
*/

/**
 * @brief Manual stepper motor control for raising and lowering the blinds
 *  in the bedroom
 *
 * 512 bits represent 360 degrees of rotation. The motor turns until
 * the blinds switch the leaver switch, and then it stops.
 */
/*
void blinds_Bedroom_Manual (void)
{
  static int blindsStatus = RAISED;
  static int checkBlindsStatus = 0;

  if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE) == ON
      && blindsStatus == LOWERED)
    {
      checkBlindsStatus = raise_Blinds_Bedroom ();
      if (checkBlindsStatus == 1)
        blindsStatus = RAISED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER) == ON
      && blindsStatus == RAISED)
    {
      checkBlindsStatus = lower_Blinds_Bedroom ();
      if (checkBlindsStatus == 1)
        blindsStatus = LOWERED;
    }
  else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_LOWER) == ON
      && HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_ROOM_SWITCH_RAISE) == ON)
    {
      ;
    }
}
*/
