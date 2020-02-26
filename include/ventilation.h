#ifndef __VENTILATION_H
#define __VENTILATION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"


  bool check_For_Gases (void);
  void emergency_Ventilation(void);
  bool check_For_Fire (void);
  void fire_Alarm(void);


#ifdef __cplusplus
}
#endif

#endif
