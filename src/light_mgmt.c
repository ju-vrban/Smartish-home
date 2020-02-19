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
  dusk = (float) duskTime[0] + ((float)duskTime[1])/100;

  return dusk;
}

int laserTripSwitch = 0; //place inside main()
/* Could use the other sensor and possibly without laser trip switch */
void bathroom_Light (void)
{
  int isTripped = 0;  //place inside main
  if(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
    && isTripped == 0)
    {
      isTripped = 1;
      laserTripSwitch += 1;
    }
  else if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
    && isTripped == 1)
    {
      isTripped = 0;
    }

  int isOccupied = 0; // place in header as global
  int currentTime = 0; 

/* Sensor */
  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_5, GPIO_PIN_SET)
    && isOccupied == 0)
    {
      isOccupied = 1;
      HAL_GPIO_WritePin (GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
    }
  else if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)
    && isOccupied == 1)
    {
      if (HAL_GetTick() - currentTime >= 500L)
        {
          currentTime = HAL_GetTick();
          HAL_GPIO_WritePin (GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
        }
    }
}


/* Ovo staviti u misc.c */
bool automatic_Mode(void)
{
  int automaticMode;
  if (GPIO_ReadPin(GPIOD, GPIO_AUTOMATIC_MODE) == GPIO_PIN_SET)
    return automaticMode = true;
  else
    return automaticMode = false;
}
/* misc.c ---------------*/


/* U automatic nacinu duty racunati pomocu aplikacije */
void living_Room_Light (float dusk, float currentTime)
{
/* Vjerojtno bolje u mainu to racunati*/
  get_Time();

  float currentTime = 0;
  currentTime = (float) Time.hours + (float) Time.minutes/100;
/*------------------------------------*/ 

  static int lightActive = 0;

/*U header--------------*/
#define ON  1
#define OFF 0
/*-----------------------*/

  bool automaticMode;
  automatciMode = automatic_Mode();
  
if (atomaticMode == ON )
{
  if ((currentTime >= dusk && currentTime <= MIDNIGHT)
    && lightActive == 0) //put inside main before function to not waste processor time
    {
      lightActive = 1;
      TIM_Start_PWM (htim3);
    }
  else if ((currentTime <= dusk && currentTime >= MIDNIGHT)
    && lightActive == 1)
    {
      lightActive = 0;
      TIM_Stop_PWM (htim3);
    }
}
else if (automaticMode == OFF)
{
  bool livingRoomEncoderSwitch = GPIO_ReadPin();

  if (livingRoomEncoderSwitch == ON)
    TIM_Start_PWM(htim3);
  else
    TIM_Stop_PWM(htim3);
}

/* Vjerojatno negdje u main, s onim tim encoder modeom*/
  Tim_DutyCycle(htim3, livingRoomEncoderDuty);
/*--------------------------*/
}


/*  Pokrenuti tim4 rcc u main */

/* Nema senzora ali se more prek aplikacije ili ručno upravljati pwm */
void bedroom_Light (float dusk, float currentTime)
{
  bool automaticMode = automatic_Mode();
  int bedroomEncoderSwitch = GPIO_ReadPin();
  if ( automaticMode == ON) // vjerojatno ne treba automstic  mode
    {
      if(bedroomEncoderSwitch == ON)
        {
          TIM_Start_PWM(htim4);
          TIM_DutyCycle(htim4, dutyCycle);
        }
      else
        {
          TIM_Stop_PWM(htim4);
        }
    }
}

