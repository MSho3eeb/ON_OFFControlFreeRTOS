#include "DIO.h"
#include "types.h"
#include "DIO_Types.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ADC.h"
#include "Bit_Math.h"

void ADC0Init(void){
	Set_Bit(SYSCTL_RCGCGPIO_R, 4);
	Set_Bit(SYSCTL_RCGCADC_R, 0);
	Set_Bit(GPIO_PORTE_CR_R, 3); 
  Clear_Bit(GPIO_PORTE_DIR_R, 3);  // input
  Clear_Bit(GPIO_PORTE_DEN_R, 3);  // disaple the digital function
  //Set_Bit(GPIO_PORTE_PUR_R, 3);    // pullup resistance
	Set_Bit(GPIO_PORTE_AFSEL_R, 3);  // alternative function
	Set_Bit(GPIO_PORTE_AMSEL_R, 3);  // analog function
	Clear_Bit(ADC0_ACTSS_R, 3);      // disable SS3 during config
	ADC0_EMUX_R &=~ 0xF000; 
	ADC0_SSMUX3_R = 0;
	ADC0_SSCTL3_R |= 6;
	Set_Bit(ADC0_ACTSS_R, 3);
}

int ADC0Read(void){
	Set_Bit(ADC0_PSSI_R, 3);
	while((ADC0_RIS_R & 8) == 0);
	ADC0_ISC_R = 8;
	return ADC0_SSFIFO3_R;
	
}
