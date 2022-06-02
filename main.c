// libraries
#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "ADC.h"// our ADC
#include "LCD.h"// our LCD
#include "UART.h" // Our UART

// the oven controlling Pin
#define theoven DIO_ChannelA2


// we have 3 tasks
void mainTask(void *pvParameters);// for ON OFF of the oven
void uartTask(void *pvParameters);// for reading data from UART
void lcdTask(void *pvParameters);// for displaying data on LCD

// we hava 3 queues
xQueueHandle UartQueue; // UART data setpoint
xQueueHandle setpointQueue; // send setpoint from main to LCD
xQueueHandle LCDQueue; // Send realtemp to LCD



int main(void){
	DIO_Init(DIO_PortA);// for Oven
	DIO_Init(DIO_PortB);// for data of the LCD
	DIO_Init(DIO_PortE);// for ADC
	DIO_Init(DIO_PortF);// for Control of LCD
	
	ADC0Init();// ADC intialization
	LCD_Init();// LCD intialization
	UART_init();// UART intialization
	
	UartQueue = xQueueCreate(3, sizeof(long));
	LCDQueue = xQueueCreate(3, sizeof(long));
	setpointQueue = xQueueCreate(3, sizeof(long));
	
	if(UartQueue != NULL){
		xTaskCreate(mainTask, "main", 128, NULL, 1, NULL);
		xTaskCreate(uartTask, "uart", 128, NULL, 1, NULL);
		xTaskCreate(lcdTask, "lcd", 128, NULL, 1, NULL);
		vTaskStartScheduler();
	}
	while(1);
}
/*-------------------------------MAIN TASK--------------------*/
void mainTask(void *pvParameters){
	char Setpoint = 0;
	float RealTemp = 0;
	
	for(;;){
		xQueueReceive(UartQueue, &Setpoint, 0);// setpoint from UART
		RealTemp = (ADC0Read()/4095.0) * 100.0;// Mapping of ADC from 4095 to 100
		if(Setpoint > RealTemp) // if setpoint is greater than realtemp oven on
			DIO_WritePin(theoven, HIGH);
		else
			DIO_WritePin(theoven, LOW);
		// Send data to LCD
		xQueueSendToBack(setpointQueue, &Setpoint, 10/portTICK_RATE_MS);
		xQueueSendToBack(LCDQueue, &RealTemp, 10/portTICK_RATE_MS);
	}
}
/*----------------------------UART TASK-----------------------*/
void uartTask(void *pvParameters){
	int Setpoint = 0;
	
	for(;;){
		UARTSendString("Enter New SetPoint: ");//the print of screen
		Setpoint = UARTReceive2Digits();// Setpoint read
		xQueueSendToBack(UartQueue, &Setpoint, 10/portTICK_RATE_MS);
	}
}
/*------------------------------LCD TASK---------------------*/
void lcdTask(void *pvParameters){
	float RealTemp = 0;
	char Setpoint = 0;
	
	LCD_GoToString(1,0,"Setpoint:");// first line 
	LCD_GoToString(2,0,"RealTemp:");// second line
	
	for(;;){
		// data from main
		xQueueReceive(setpointQueue, &Setpoint, portMAX_DELAY);
		xQueueReceive(LCDQueue, &RealTemp, 0);
		
		LCD_GoToString(2,9,"");
		LCD_Write_Int((int)RealTemp);
		LCD_GoToString(1,9,"");
		LCD_Write_Int((int)Setpoint);
	}
}