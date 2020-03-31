/*
 * RTC_ds3231.c
 *
 *  Created on: Feb 4, 2020
 *      Author: jurica
 */

#include "LCD_pcf8574.h"

/**
 * @brief Send a command to the LCD
 * @param cmd command to send to the LCD
 * @return None
 */
void LCD_Send_Cmd (char cmd)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (cmd & 0xf0);
  data_l = ((cmd << 4) & 0xf0);
  data_t[0] = data_u | 0x0C;  //en=1, rs=0
  data_t[1] = data_u | 0x08;  //en=0, rs=0
  data_t[2] = data_l | 0x0C;  //en=1, rs=0
  data_t[3] = data_l | 0x08;  //en=0, rs=0
  HAL_I2C_Master_Transmit (&hi2c2, LCD_WRITE_ADDRESS, (uint8_t*) data_t, 4,
                           100);
}

/**
 * @brief Send data to the LCD
 * @param data represents the data to be sent
 * @return None
 */
void LCD_Send_Data (char data)
{
  char data_u, data_l;
  uint8_t data_t[2];
  data_u = (data & 0xf0);
  data_l = ((data << 4) & 0xf0);
  data_t[0] = data_u | 0x0D;  //en=1, rs=1
  data_t[1] = data_u | 0x09;  //en=0, rs=1
  data_t[2] = data_l | 0x0D;  //en=1, rs=1
  data_t[3] = data_l | 0x09;  //en=0, rs=1
  HAL_I2C_Master_Transmit (&hi2c2, LCD_WRITE_ADDRESS, (uint8_t*) data_t, 4,
                           100);
}

/**
 * @brief Sends to the LCD an empty character to be displayed
 * @param None
 * @return None
 */
void LCD_Clear (void)
{
  LCD_Send_Cmd (0x80);
  for (int i = 0; i < 70; i++)
    {
      LCD_Send_Data (' ');
    }
}

/**
 * @brief Puts the cursor at the entered position
 * @param leftRightHalf, col are the left (0) or right (1) side of the LCD
 *        panel and column of the display
 * @return None
 */
void LCD_Put_Cur (int leftRightHalf, int col)
{

  switch (leftRightHalf)
    {
    case 0:
      col |= 0x80;
      break;
    case 1:
      col |= 0xC0;
      break;
    }

  LCD_Send_Cmd (col);
}

/**
 * @brief Sets the time in the DS3231 RTC
 * @param Inputs secounds, minutes, hour, day of the week, date month and year
 * @return None
 */
void LCD_Init (void)
{
  // 4 bit initialisation
  HAL_Delay (50);  // wait for >40ms
  LCD_Send_Cmd (0x30);
  HAL_Delay (5);  // wait for >4.1ms
  LCD_Send_Cmd (0x30);
  HAL_Delay (1);  // wait for >100us
  LCD_Send_Cmd (0x30);
  HAL_Delay (10);
  LCD_Send_Cmd (0x20);  // 4bit mode
  HAL_Delay (10);

  // dislay initialisation
  LCD_Send_Cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
  HAL_Delay (1);
  LCD_Send_Cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
  HAL_Delay (1);
  LCD_Send_Cmd (0x01);  // clear display
  HAL_Delay (1);
  HAL_Delay (1);
  LCD_Send_Cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
  HAL_Delay (1);
  LCD_Send_Cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}
/*
void LCD_Init (void)
{
  lcd_send_cmd (0x02);
  lcd_send_cmd (0x28);
  lcd_send_cmd (0x0c);
  lcd_send_cmd (0x80);
}
*/
/**
 * @brief Sets the time in the DS3231 RTC
 * @param Inputs secounds, minutes, hour, day of the week, date month and year
 * @return None
 */
void LCD_Send_String (char *str)
{
  while (*str)
    LCD_Send_Data (*str++);
}

/*/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////*/

/**
 * @brief Send a command to the LCD
 * @param cmd command to send to the LCD
 * @return None
 */
void LCD_Send_Cmd_2 (char cmd)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (cmd & 0xf0);
  data_l = ((cmd << 4) & 0xf0);
  data_t[0] = data_u | 0x0C;  //en=1, rs=0
  data_t[1] = data_u | 0x08;  //en=0, rs=0
  data_t[2] = data_l | 0x0C;  //en=1, rs=0
  data_t[3] = data_l | 0x08;  //en=0, rs=0
  HAL_I2C_Master_Transmit (&hi2c3, LCD_WRITE_ADDRESS, (uint8_t*) data_t, 4,
                           100);
}

/**
 * @brief Send data to the LCD
 * @param data represents the data to be sent
 * @return None
 */
void LCD_Send_Data_2 (char data)
{
  char data_u, data_l;
  uint8_t data_t[2];
  data_u = (data & 0xf0);
  data_l = ((data << 4) & 0xf0);
  data_t[0] = data_u | 0x0D;  //en=1, rs=1
  data_t[1] = data_u | 0x09;  //en=0, rs=1
  data_t[2] = data_l | 0x0D;  //en=1, rs=1
  data_t[3] = data_l | 0x09;  //en=0, rs=1
  HAL_I2C_Master_Transmit (&hi2c3, LCD_WRITE_ADDRESS, (uint8_t*) data_t, 4,
                           100);
}

/**
 * @brief Sends to the LCD an empty character to be displayed
 * @param None
 * @return None
 */
void LCD_Clear_2 (void)
{
  LCD_Send_Cmd_2 (0x80);
  for (int i = 0; i < 70; i++)
    {
      LCD_Send_Data_2 (' ');
    }
}

/**
 * @brief Puts the cursor at the entered position
 * @param leftRightHalf, col are the left (0) or right (1) side of the LCD
 *        panel and column of the display
 * @return None
 */
void LCD_Put_Cur_2 (int leftRightHalf, int col)
{

  switch (leftRightHalf)
    {
    case 0:
      col |= 0x80;
      break;
    case 1:
      col |= 0xC0;
      break;
    }

  LCD_Send_Cmd_2 (col);
}

/**
 * @brief Sets the time in the DS3231 RTC
 * @param Inputs secounds, minutes, hour, day of the week, date month and year
 * @return None
 */
void LCD_Init_2 (void)
{
  // 4 bit initialisation
  HAL_Delay (50);  // wait for >40ms
  LCD_Send_Cmd_2 (0x30);
  HAL_Delay (5);  // wait for >4.1ms
  LCD_Send_Cmd_2 (0x30);
  HAL_Delay (1);  // wait for >100us
  LCD_Send_Cmd_2 (0x30);
  HAL_Delay (10);
  LCD_Send_Cmd_2 (0x20);  // 4bit mode
  HAL_Delay (10);

  // dislay initialisation
  LCD_Send_Cmd_2 (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
  HAL_Delay (1);
  LCD_Send_Cmd_2 (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
  HAL_Delay (1);
  LCD_Send_Cmd_2 (0x01);  // clear display
  HAL_Delay (1);
  HAL_Delay (1);
  LCD_Send_Cmd_2 (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
  HAL_Delay (1);
  LCD_Send_Cmd_2 (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

/**
 * @brief Sets the time in the DS3231 RTC
 * @param Inputs secounds, minutes, hour, day of the week, date month and year
 * @return None
 */
void LCD_Send_String_2 (char *str)
{
  while (*str)
    LCD_Send_Data_2 (*str++);
}
