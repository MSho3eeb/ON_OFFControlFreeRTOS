#include "DIO.h"
#include "types.h"
#include "DIO_Types.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "Bit_Math.h"
#include "LCD.h"

void delayMs(int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < 3180;j++)
			{}
	}
}
void delayUs(int n){
		int i, j;
	  for(i = 0; i < n; i++){
		  for(j = 0; j < 3;j++)
			  {}
	   }
}

void LCD_Cmd(char cmd){
	DIO_WritePin(RS, LOW);
	DIO_WritePin(RW, LOW);
	GPIO_PORTB_DATA_R = cmd;
	DIO_WritePin(EN, HIGH);
	delayUs(2);
	DIO_WritePin(EN, LOW);
}

void LCD_Clear(void){
	LCD_Cmd(0x01);
}

void LCD_Init(void){
	GPIO_PORTF_DIR_R |= 0x0F;
	GPIO_PORTF_DEN_R |= 0x0F;
	GPIO_PORTF_AFSEL_R = 0; 
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_AFSEL_R = 0; 
	GPIO_PORTB_PCTL_R = 0;
	GPIO_PORTB_AMSEL_R = 0;
	
	delayMs(40);
	LCD_Cmd(0x38);
	delayUs(50);
	LCD_Cmd(0x0E);
	delayUs(50);
	LCD_Cmd(0x01);
	delayMs(2);
	LCD_Cmd(0x0F);
	delayUs(4);
	LCD_Cmd(0x02);
}

void LCD_Char(char data){
	DIO_WritePin(RS, HIGH);
	DIO_WritePin(RW, LOW);
	GPIO_PORTB_DATA_R = data;
	DIO_WritePin(EN, HIGH);
	delayMs(10);
	//DIO_WritePin(RS, LOW);
	DIO_WritePin(EN, LOW);
	//DIO_WritePin(RS, LOW);
	delayMs(10);
	
}

void LCD_String(uint8 string[]){
	uint8* data = (uint8*) string;
	int i = 0;
	while(data[i] != '\0'){
		LCD_Char(data[i]);
		i++;
		delayMs(10);
	}
}

void LCD_GoToString(uint8 line, uint8 pos, uint8 string[]){
	delayMs(20);
	uint8 cmd;
	switch(line){
		case 1:
			cmd = 0x80 | (pos & 0x0F);
			LCD_Cmd(cmd);
		break;
		case 2:
			cmd = 0xC0 | (pos & 0x0F);
			LCD_Cmd(cmd);
		break;
	}
	LCD_String(string);
}

void LCD_Write_Int(int num){
	//LCD_Clear();
	char i = 0;
	char str[32];
  while(num != 0){
		str[i] = num % 10;
		num = num/10;
		i++;
	}
	for(int j = i-1; j >=0 ; j--)
		LCD_Char('0' + str[j]);
}
