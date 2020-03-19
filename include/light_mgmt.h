#ifndef __LIGHT_MGMT_H
#define __LIGHT_MGMT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define DAWN              6.00f
#define BEFORE_MIDNIGHT   23.599f
#define AFTER_MIDNIGHT    00.00f
#define NOON              12.00f
#define MINS_60           3600000L
#define MINS_5            300000L


  float calculate_Dusk_Time (void);
  void mainEntranceLight(uint8_t entrancePIR);
  void entrance_Light (float dusk, float entranceTimeValue);
  void bathroom_Light (void);
  void living_Room_Kitchen_Light (float dusk, float currentTime);
  void bedroom_Light (float dusk, float currentTime);

#ifdef __cplusplus
}
#endif

#endif
