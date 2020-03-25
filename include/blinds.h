#ifndef __BLINDS_H
#define __BLINDS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define LOWERED   1
#define RAISED    0

  int lower_Blinds_Living (void);
  int raise_Blinds_Living(void);
  void blinds_Living_Room (float dusk, float currentTime);
  void blinds_Living_Room_Manual(void);
  int lower_Blinds_Bedroom (void);
  int raise_Blinds_Bedroom (void);
  void blinds_Bedroom (float dusk, float currentTime);
  void blinds_Bedroom_Manual (void);

#ifdef __cplusplus
}
#endif

#endif
