#ifndef __ALARMS_AND_SECURITY_H
#define __ALARMS_AND_SECURITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

  bool check_For_Fire (void);
  void gnerate_Sine_Wave (void);
  void fire_Alarm(void);
  bool check_For_Forcefull_Entrance (void);
  bool alarm_status (void);
  char read_Keypad (void);

#ifdef __cplusplus
}
#endif

#endif
