#ifndef __LIGHT_MGMT_H
#define __LIGHT_MGMT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

  float calculate_Dusk_Time (void);
  void mainEntranceLight(uint8_t entrancePIR);

#ifdef __cplusplus
}
#endif

#endif
