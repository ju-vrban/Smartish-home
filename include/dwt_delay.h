/*
 * Simple microseconds delay routine, utilizing ARM's DWT
 * (Data Watchpoint and Trace Unit) and HAL library.
 * Intended to use with gcc compiler, but I hope it can be used
 * with any other C compiler across the Universe (provided that
 * ARM and CMSIS already invented) :)
 * Max K
 *
 *
 * This file is part of DWT_Delay package.
 * DWT_Delay is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * us_delay is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License for more details.
 * http://www.gnu.org/licenses/.
 */

#include "main.h"

#ifndef INC_DWT_DELAY_H_
#define INC_DWT_DELAY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DWT_DELAY_NEWBIE 0


#define delayUS_ASM(us) do {\
  asm volatile (  "MOV R0,%[loops]\n\t"\
      "1: \n\t"\
      "SUB R0, #1\n\t"\
      "CMP R0, #0\n\t"\
      "BNE 1b \n\t" : : [loops] "r" (16*us) : "memory"\
          );\
} while(0)

void DWT_Init(void);
void DWT_Delay (uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* INC_DWT_DELAY_DWT_DELAY_H_ */
