/*
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
  float timeConst[3] =
    { 1, 1.3, 1.6 };

  switch (Time.month)
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
        numOfDays = 243 + (float) Time.date * timeConst[82];
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
      if (HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_PIR) == GPIO_PIN_SET
          && isOccupied == 0)
        {
          isOccupied = 1;
          HAL_GPIO_WritePin (GPIOD, GPIO_BATHROOM_LIGHT, GPIO_PIN_SET); // PRomijeniti pin
        }
      else if (HAL_GPIO_ReadPin (GPIOD, GPIO_BATHROOM_PIR) == GPIO_PIN_RESET
          && isOccupied == 1)
        {
          if (HAL_GetTick () - currentTime >= 500L)
            {
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

/* U automatic nacinu duty racunati pomocu aplikacije */
void living_Room_Kitchen_Light (float dusk, float currentTime)
{
  static int lightState = OFF;
  static int encoderDuty = 0;
  static int livingRoomEncoderSwitch;
  static int switchState = OFF;

  bool automaticMode;
  automaticMode = automatic_Mode ();

  if (automaticMode == ON)
    {
      if ((currentTime >= dusk && currentTime <= BEFORE_MIDNIGHT)
          && lightState == OFF) //put inside main before function to not waste processor time
        {
          lightState = ON;
          HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_1);

          htim3.Instance->CCR1 = 50;
        }
      else if ((currentTime <= dusk && currentTime >= AFTER_MIDNIGHT)
          && lightState == ON)
        {
          lightState = OFF;
          HAL_TIM_PWM_Stop (&htim3, TIM_CHANNEL_1); //PROVJERITI KANAL I INICIJALIZIRATI
        }
    }
  else if (automaticMode == OFF)
    {
      livingRoomEncoderSwitch = HAL_GPIO_ReadPin (GPIOD,
      GPIO_LIVING_ROOM_ENCODER_SW);

      if (livingRoomEncoderSwitch == ON && switchState == OFF)
        {
          switchState = ON;
          HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_1);
          encoderDuty = __HAL_TIM_GET_COUNTER(&htim3);
          htim3.Instance->CCR1 = encoderDuty;
        }
      else if (switchState == ON && livingRoomEncoderSwitch == ON)
        {
          switchState = OFF;
          HAL_TIM_PWM_Stop (&htim3, TIM_CHANNEL_1);
        }
    }

  /* Vjerojatno negdje u main, s onim tim encoder modeom*/
  //Tim_DutyCycle (htim3, livingRoomEncoderDuty);
  /*--------------------------*/
}

/*  Pokrenuti tim4 rcc u main */

/* Nema senzora ali se more prek aplikacije ili ručno upravljati pwm */
void bedroom_Light (float currentTime)
{
  bool automaticMode = automatic_Mode ();
  int bedroomEncoderSwitch = HAL_GPIO_ReadPin (GPIOD, GPIO_BEDROOM_ENCODER_SW);

  static int switchState = OFF;
  static long int currentSystemTime;
  static uint8_t encoderDuty;

  if (automaticMode == OFF) // vjerojatno ne treba automstic  mode
    {
      if (bedroomEncoderSwitch == ON && switchState == OFF)
        {
          switchState = ON;
          /* start PWM and set duty cycle with rotary encoder */
          HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_2);
          encoderDuty = __HAL_TIM_GET_COUNTER(&htim4);
          htim3.Instance->CCR1 = encoderDuty;
        }
      else if (bedroomEncoderSwitch == ON && switchState == ON)
        {
          switchState = OFF;
          HAL_TIM_PWM_Stop (&htim3, TIM_CHANNEL_2);
        }
    }
  else
    {
      if (HAL_TIM_PWM_GetState (&htim3) == ON && currentTime >= AFTER_MIDNIGHT
          && currentTime <= DAWN)
        {
          if (HAL_GetTick () - currentSystemTime >= MINS_60)
            {
              currentSystemTime = HAL_GetTick ();
              HAL_TIM_PWM_Stop (&htim3, TIM_CHANNEL_2);
            }
        }
      else
        {
          //HAL_uart_();
        }
    }
}

