#ifndef LCD_H_
#define LCD_H_


#include "DIO_Types.h"
#include "DIO.h"

#define LCDPort DIO_PortB
#define RS DIO_ChannelF1
#define RW DIO_ChannelF2
#define EN DIO_ChannelF3

void delayMs(int n);
void delayUs(int n);

void LCD_Cmd(char cmd); // command to LCD
void LCD_Clear(void); // clear LCD
void LCD_Init(void); // intialize LCD
void LCD_Char(char data); // send character to LCD
void LCD_String(uint8 string[]); // send srting to LCD
void LCD_GoToString(uint8 line, uint8 pos, uint8 string[]); // send string at certain place
void LCD_Write_Int(int num); // write int to LCD


#endif 