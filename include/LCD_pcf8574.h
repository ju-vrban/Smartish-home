#ifndef __LCD_PCF8574_H
#define __LCD_PCF8574_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define CLEAR_DISP 0x01
#define LCD_WRITE_ADDRESS 0x4E

I2C_HandleTypeDef hi2c1;

void LCD_Init (void);
void LCD_Send_Cmd (char cmd);
void LCD_Send_Data (char data);
void LCD_Send_String (char *str);
void LCD_Put_Cur (int leftRightHalf, int col); // put cursor at the entered position row (0), col (0-15);
void LCD_Clear (void);


#ifdef __cplusplus
}
#endif

#endif
