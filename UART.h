#ifndef UART_H_
#define UART_H_

void UART_init(void); // intialize UART
char UARTReceive(void); // Recieve char
void UARTSend(char c); // send send a char
char UARTReceive2Digits(void); // recieve 2 digits integer
void UARTSendString(char string[]); // send string


#endif