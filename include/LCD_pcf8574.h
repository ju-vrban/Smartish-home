#include "stm32f4xx_hal.h"

#define CLEAR_DISP 0x01
#define LCD_WRITE_ADDRESS 0x4E

I2C_HandleTypeDef hi2c1;

void LCD_Init (void);
void LCD_SendCmd (char cmd);
void LCD_SendData (char data);
void LCD_SendString (char *str);
void LCD_PutCur (int row, int col); // put cursor at the entered position row (0), col (0-15);
void LCD_Clear (void);
