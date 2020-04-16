#ifndef __VENTILATION_H
#define __VENTILATION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"


  bool check_For_Gases (void);
  void emergency_Ventilation(void);
  void heating_Cooling_control(float roomTemp);



#ifdef __cplusplus
}
#endif

#endif
