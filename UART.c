#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "Bit_Math.h"




void UART_init(void){
	SYSCTL_RCGCUART_R  |= 1<<0 ;                      //initiallizing uart0
	SYSCTL_RCGCGPIO_R  |= 1<<0 ;                      //initiallizing portA pins 
	GPIO_PORTA_AFSEL_R |= (1<<0 | 1<<1);              //choosing the alternative function for pins 0 & 1 (Tx & Rx)
	GPIO_PORTA_PCTL_R  |= (1<<(0*4) | 1<<(1*4));      //choosing the alternative function to the pin
	GPIO_PORTA_DEN_R   |= (1<<0 | 1<<1);              //openning digital enable for pins 0 & 1 in PortA
	UART0_CTL_R &=~ 1<<0;     
	
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	UART0_LCRH_R = 0x60;
	UART0_CC_R =0x0;
	
	UART0_CTL_R = 0x301;              
}

char UARTReceive(void){
	char c;
	while((UART0_FR_R & 0x10) != 0);
	c = UART0_DR_R;
	return c;
}

void UARTSend(char c){
	while((UART0_FR_R & 0x20) != 0);
	UART0_DR_R = c;
}

void UARTSendString(char string[]){
	char* data = (char*) string;
	int i = 0;
	while(data[i] != '\0'){
		UARTSend(data[i]);
		i++;
		delayMs(10);
   }
}

char UARTReceive2Digits(void){
	char d0 = UARTReceive();
	UARTSend(d0);
	char d1 = UARTReceive();
	UARTSend(d1);
	UARTSend('\r');
	UARTSend('\n');
  return (d0-'0')*10 + (d1-'0');
}