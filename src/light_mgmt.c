/**
 * light_mgmt.c
 *
 *  Created on: Jan 27, 2020
 *      Author: jurica
 */

#include "light_mgmt.h"

float calculate_Dusk_Time (void)
{
  get_Time ();

  int numOfDays = 0;
  float timeConst[12] =
    { 1.2, 1.5, 2.7 };

  int Month = Time.month;

  switch (Month)
    {
    case January:
      numOfDays = 0 + (float) Time.date * timeConst[1];
      break;
    case February:
      numOfDays = 31 * timeConst[1] + (float) Time.date * timeConst[1];
      break;
    case March:
      if (Time.year % 4 == 0)
        numOfDays = 60 + (float) Time.date * timeConst[2];
      else
        numOfDays = 59 + (float) Time.date * timeConst[2];
      break;
    case April:
      if (Time.year % 4 == 0)
        numOfDays = 91 + (float) Time.date * timeConst[2];
      else
        numOfDays = 90 + (float) Time.date * timeConst[2];
      break;
    case May:
      if (Time.year % 4 == 0)
        numOfDays = 121 + (float) Time.date * timeConst[1];
      else
        numOfDays = 120 + (float) Time.date * timeConst[1];
      break;
    case June:
      if (Time.year % 4 == 0)
        numOfDays = 152 + (float) Time.date * timeConst[0];
      else
        numOfDays = 151 + (float) Time.date * timeConst[0];
      break;
    case July:
      if (Time.year % 4 == 0)
        numOfDays = 182 + (float) Time.date * timeConst[0];
      else
        numOfDays = 181 + (float) Time.date * timeConst[0];
      break;
    case August:
      if (Time.year % 4 == 0)
        numOfDays = 213 + (float) Time.date * timeConst[1];
      else
        numOfDays = 212 + (float) Time.date * timeConst[1];
      break;
    case September:
      if (Time.year % 4 == 0)
        numOfDays = 244 + (float) Time.date * timeConst[2];
      else
        numOfDays = 243 + (float) Time.date * timeConst[2];
      break;
    case October:
      if (Time.year % 4 == 0)
        numOfDays = 274 + (float) Time.date * timeConst[2];
      else
        numOfDays = 273 + (float) Time.date * timeConst[2];
      break;
    case November:
      if (Time.year % 4 == 0)
        numOfDays = 305 + (float) Time.date * timeConst[1];
      else
        numOfDays = 304 + (float) Time.date * timeConst[1];
      break;
    case December:
      if (Time.year % 4 == 0)
        numOfDays = 335 + (float) Time.date * timeConst[0];
      else
        numOfDays = 334 + (float) Time.date * timeConst[0];
      break;

    default:
      numOfDays = 1;
      break;
    }

  int dayOfSolstice[2] =
    { 176, 345 };
  int duskTimeJanury[2] =
    { 16, 22 };
  int duskTimeJune[2] =
    { 19, 51 };
  int duskTimeDecember[2] =
    { 16, 12 };
  static int duskTime[2];
  int mins, hrs;

  if (numOfDays < dayOfSolstice[0])
    {
      mins = numOfDays % 60;
      hrs = numOfDays / 60;

      duskTimeJanury[0] += hrs;
      duskTimeJanury[1] += mins;

      if (duskTimeJanury[1] > 59)
        {
          duskTimeJanury[1] = duskTimeJanury[1] - 60;
          duskTimeJanury[0] += 1;
        }

      duskTime[0] = duskTimeJanury[0];
      duskTime[1] = duskTimeJanury[1];
    }
  else if (numOfDays > dayOfSolstice[0] && numOfDays < dayOfSolstice[1])
    {
      numOfDays -= dayOfSolstice[0];

      mins = numOfDays % 60;
      hrs = numOfDays / 60;

      duskTimeJune[0] -= hrs;
      duskTimeJune[1] -= mins;

      if (duskTimeJune[1] < 0)
        {
          duskTimeJune[1] = 60 + duskTimeJune[1];
          duskTimeJune[0] -= 1;
        }

      duskTime[0] = duskTimeJune[0];
      duskTime[1] = duskTimeJune[1];
    }
  else
    {
      numOfDays -= dayOfSolstice[1];

      mins = numOfDays % 60;
      hrs = numOfDays / 60;

      duskTimeDecember[0] += hrs;
      duskTimeDecember[1] += mins;

      if (duskTimeJune[1] > 59)
        {
          duskTimeDecember[1] = duskTimeDecember[1] - 60;
          duskTimeDecember[0] += 1;
        }

      duskTime[0] = duskTimeDecember[0];
      duskTime[1] = duskTimeDecember[1];
    }

  numOfDays = 0;

  float dusk;
  dusk = (float) duskTime[0] + ((float) duskTime[1]) / 100;

  return dusk;
}

void entrance_Light (float dusk, float entranceTimeValue)
{
  if ((entranceTimeValue >= dusk)
      && HAL_GPIO_ReadPin (GPIOD, GPIO_MAIN_ENTRANCE_PIR) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin (GPIOD, GPIO_MAIN_ENTRANCE_LIGHT, GPIO_PIN_SET);
    }
  else if ((entranceTimeValue >= dusk)
      && HAL_GPIO_ReadPin (GPIOD, GPIO_MAIN_ENTRANCE_PIR) == GPIO_PIN_RESET)
    {
      HAL_GPIO_WritePin (GPIOD, GPIO_MAIN_ENTRANCE_LIGHT, GPIO_PIN_RESET);
    }
}

void bathroom_Light (void)
{
  static int isOccupied = 0;
  static int currentTime = 0;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      /* Sensor */
      if ((HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_PIR) == GPIO_PIN_SET
          && isOccupied == 0)
          || HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_SWITCH) == GPIO_PIN_SET)
        {
          isOccupied = 1;
          HAL_GPIO_WritePin (GPIOD, GPIO_BATHROOM_LIGHT, GPIO_PIN_SET);
        }
      else if ((HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_PIR) == GPIO_PIN_RESET
          && isOccupied == 1)
          || HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_SWITCH) == GPIO_PIN_RESET)
        {
          if (HAL_GetTick () - currentTime >= 500L)
            {
              isOccupied = 0;
              currentTime = HAL_GetTick ();
              HAL_GPIO_WritePin (GPIOD, GPIO_BATHROOM_LIGHT, GPIO_PIN_RESET);
            }
        }
    }
  else
    {
      if (HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_SWITCH) == GPIO_PIN_SET)
        {
          HAL_GPIO_WritePin (GPIOD, GPIO_BATHROOM_LIGHT, GPIO_PIN_SET);
        }
      else if (HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_SWITCH) == GPIO_PIN_RESET)
        {
          HAL_GPIO_WritePin (GPIOD, GPIO_BATHROOM_LIGHT, GPIO_PIN_RESET);
        }
    }
}

void living_Room_Kitchen_Light (float dusk, float currentTime)
{
  static int lightState = OFF;
  static int encoderDuty = 0;
  static int livingRoomEncoderSwitch = ON;
  static int switchState = OFF;
  static int lastConversion = 0;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if ((HAL_GPIO_ReadPin (GPIOF,
      GPIO_LIVING_MICROWAVE_SEN) == GPIO_PIN_SET && currentTime >= dusk
          && currentTime <= BEFORE_MIDNIGHT && lightState == OFF)
          || HAL_GPIO_ReadPin (GPIOC, GPIO_LIVING_ROOM_ENCODER_SW) == ON)
        {
          if (HAL_GPIO_ReadPin (GPIOC, GPIO_LIVING_ROOM_ENCODER_SW) == ON)
            {
              switchState = ON;
            }
          lightState = ON;
          lastConversion = HAL_GetTick ();
          HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_1);
          htim12.Instance->CCR1 = 50;
        }
      else if (HAL_GPIO_ReadPin (GPIOF, GPIO_LIVING_MICROWAVE_SEN) == ON
          && lightState == ON && switchState == OFF)
        {
          lastConversion = HAL_GetTick ();
        }
      else if ((currentTime >= dusk && currentTime <= BEFORE_MIDNIGHT)
          && lightState == ON && (HAL_GetTick () - lastConversion >= MINS_1)
          && switchState == OFF)
        {
          lastConversion = HAL_GetTick ();
          lightState = OFF;
          HAL_TIM_PWM_Stop (&htim12, TIM_CHANNEL_1);
        }
      else if ((currentTime <= dusk && currentTime >= AFTER_MIDNIGHT)
          && lightState == ON)
        {
          lightState = OFF;
          HAL_TIM_PWM_Stop (&htim12, TIM_CHANNEL_1);
        }
      else if (HAL_GPIO_ReadPin (GPIOC, GPIO_LIVING_ROOM_ENCODER_SW) == ON)
        {
          switchState = OFF;
        }
    }
  else if (automaticMode == OFF)
    {
      livingRoomEncoderSwitch = HAL_GPIO_ReadPin (GPIOC,
      GPIO_LIVING_ROOM_ENCODER_SW);

      if (HAL_GPIO_ReadPin (GPIOC, GPIO_LIVING_ROOM_ENCODER_SW) == ON
          && switchState == OFF)
        {
          switchState = ON;
          HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_1);
//          encoderDuty = __HAL_TIM_GET_COUNTER(&htim3);
          htim12.Instance->CCR1 = 100;
        }
      else if (switchState == ON
          && HAL_GPIO_ReadPin (GPIOC, GPIO_LIVING_ROOM_ENCODER_SW) == OFF)
        {
          switchState = OFF;
          HAL_TIM_PWM_Stop (&htim12, TIM_CHANNEL_1);
        }
    }
}

void bedroom_Light (float dusk, float currentTime)
{

  static int switchState = OFF;
  static long int currentSystemTime = 0;
  static uint8_t encoderDuty;
  bool automaticMode;
  static int bedroomEncoderSwitch = OFF;

  automaticMode = automatic_Mode ();
  bedroomEncoderSwitch = HAL_GPIO_ReadPin (GPIOC, GPIO_BEDROOM_ENCODER_SW);

  if (automaticMode == OFF)
    {
      encoderDuty = __HAL_TIM_GET_COUNTER(&htim4);
      if (bedroomEncoderSwitch == ON && switchState == OFF)
        {
          switchState = ON;
          HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_2);
          htim12.Instance->CCR2 = 100;
        }
      else if (bedroomEncoderSwitch == OFF && switchState == ON)
        {
          switchState = OFF;
          HAL_TIM_PWM_Stop (&htim12, TIM_CHANNEL_2);
        }
    }
  else
    {
      if (bedroomEncoderSwitch == ON && switchState == OFF)
        {

          if (currentTime >= DAWN && currentTime <= NOON && switchState == OFF)
            {
              switchState = ON;
              HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_2);
              htim12.Instance->CCR2 = 35;
            }
          else if (currentTime >= NOON
              && currentTime <= dusk&& switchState == OFF)
            {
              switchState = ON;
              HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_2);
              htim12.Instance->CCR2 = 50;
            }
          else if ((currentTime >= dusk) && currentTime <= BEFORE_MIDNIGHT
              && switchState == OFF)
            {
              switchState = ON;
              HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_2);
              htim12.Instance->CCR2 = 35;
            }
          else if (currentTime >= AFTER_MIDNIGHT && currentTime <= DAWN
              && switchState == OFF)
            {
              switchState = ON;
              HAL_TIM_PWM_Start (&htim12, TIM_CHANNEL_2);
              htim12.Instance->CCR2 = 15;
            }
        }
      else if (bedroomEncoderSwitch == ON && switchState == ON)
        {
          switchState = OFF;
          HAL_TIM_PWM_Stop (&htim12, TIM_CHANNEL_2);
        }
      else if (switchState == ON
          && (currentTime >= AFTER_MIDNIGHT && currentTime <= DAWN))
        {
          if (HAL_GetTick () - currentSystemTime >= MINS_5)
            {
              switchState = OFF;
              currentSystemTime = HAL_GetTick ();
              HAL_TIM_PWM_Stop (&htim12, TIM_CHANNEL_2);
            }
        }
      else if ((switchState == ON && (currentTime >= dusk)
          && currentTime <= BEFORE_MIDNIGHT))
        {
          htim12.Instance->CCR2 = 35;
        }
      else if ((switchState == ON && (currentTime >= AFTER_MIDNIGHT)
          && currentTime <= DAWN))
        {
          htim12.Instance->CCR2 = 15;
        }
    }
}

