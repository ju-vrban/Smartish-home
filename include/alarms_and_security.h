#ifndef __ALARMS_AND_SECURITY_H
#define __ALARMS_AND_SECURITY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define PI 3.1415926

  bool check_For_Fire (void);
  void gnerate_Sine_Wave (void);
  void get_sin (void);
  void fire_Alarm(void);
  bool check_For_Forcefull_Entrance (void);
  bool alarm_status (void);
  char read_Keypad (void);

#ifdef __cplusplus
}
#endif

#endif
