#include "DIO.h"
#include "types.h"
#include "DIO_Types.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
///////////////////////////////////////////////////////////////
const DIO_PinCFG pinCFG[]={
	//portA
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	//portB
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	//portC
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	//portD
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
  //portE
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Input,LOW},// ADC
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
  //portF
	{Input,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Input,HIGH},
	{Output,HIGH},
	{Output,HIGH},
	{Output,HIGH}
};
//////////////////////////////////////////////////////////////
void DIO_Init(DIO_PortTypes portx){
    Set_Bit(SYSCTL_RCGCGPIO_R,0);
    Set_Bit(SYSCTL_RCGCGPIO_R,1); 
    Set_Bit(SYSCTL_RCGCGPIO_R,2); 
    Set_Bit(SYSCTL_RCGCGPIO_R,3); 
    Set_Bit(SYSCTL_RCGCGPIO_R,4);   
    Set_Bit(SYSCTL_RCGCGPIO_R,5); 
    while((Get_Bit(SYSCTL_PRGPIO_R,0)) == 0x00);
    while((Get_Bit(SYSCTL_PRGPIO_R,1)) == 0x00); 
    while((Get_Bit(SYSCTL_PRGPIO_R,2)) == 0x00); 
    while((Get_Bit(SYSCTL_PRGPIO_R,3)) == 0x00); 
    while((Get_Bit(SYSCTL_PRGPIO_R,4)) == 0x00); 
    while((Get_Bit(SYSCTL_PRGPIO_R,5)) == 0x00); 
    
    DIO_ChannelTypes channelpos;
    uint8 count = 0;
    for(count = DIO_ChannelA0; count<PinCount ;count++){
	  channelpos = (DIO_ChannelTypes)(count % 8);
	  switch(portx){
     case DIO_PortA:
         if(pinCFG[count].PinDir == Output){
             Set_Bit(GPIO_PORTA_CR_R, channelpos); 
             Set_Bit(GPIO_PORTA_DIR_R, channelpos); 
             Set_Bit(GPIO_PORTA_DEN_R, channelpos); 
          }else{
             Set_Bit(GPIO_PORTA_CR_R, channelpos); 
             Clear_Bit(GPIO_PORTA_DIR_R, channelpos); 
             Set_Bit(GPIO_PORTA_DEN_R, channelpos);
             Set_Bit(GPIO_PORTA_PUR_R, channelpos);
            }
          GPIO_PORTA_LOCK_R = 0x4C4F434B;
		 break;
     case DIO_PortB:
        if(pinCFG[count].PinDir == Output){
            Set_Bit(GPIO_PORTB_CR_R, channelpos); 
            Set_Bit(GPIO_PORTB_DIR_R, channelpos); 
            Set_Bit(GPIO_PORTB_DEN_R, channelpos); 
         }else{
            Set_Bit(GPIO_PORTB_CR_R, channelpos); 
            Clear_Bit(GPIO_PORTB_DIR_R, channelpos); 
            Set_Bit(GPIO_PORTB_DEN_R, channelpos);
            Set_Bit(GPIO_PORTB_PUR_R, channelpos);
           }
        GPIO_PORTB_LOCK_R = 0x4C4F434B;
		break;
    case DIO_PortC:
      if(pinCFG[count].PinDir == Output){
          Set_Bit(GPIO_PORTC_CR_R, channelpos); 
          Set_Bit(GPIO_PORTC_DIR_R, channelpos); 
          Set_Bit(GPIO_PORTC_DEN_R, channelpos); 
       }else{
         Set_Bit(GPIO_PORTC_CR_R, channelpos); 
          Clear_Bit(GPIO_PORTC_DIR_R, channelpos); 
          Set_Bit(GPIO_PORTC_DEN_R, channelpos);
          Set_Bit(GPIO_PORTC_PUR_R, channelpos);
         }
      GPIO_PORTC_LOCK_R = 0x4C4F434B;
		break;
    case DIO_PortD:
      if(pinCFG[count].PinDir == Output){
          Set_Bit(GPIO_PORTD_CR_R, channelpos); 
          Set_Bit(GPIO_PORTD_DIR_R, channelpos); 
          Set_Bit(GPIO_PORTD_DEN_R, channelpos); 
       }else{
          Set_Bit(GPIO_PORTD_CR_R, channelpos); 
          Clear_Bit(GPIO_PORTD_DIR_R, channelpos); 
          Set_Bit(GPIO_PORTD_DEN_R, channelpos);
          Set_Bit(GPIO_PORTD_PUR_R, channelpos);
         }
      GPIO_PORTD_LOCK_R = 0x4C4F434B;
		break;
    case DIO_PortE:
     if(pinCFG[count].PinDir == Output){
         Set_Bit(GPIO_PORTE_CR_R, channelpos); 
         Set_Bit(GPIO_PORTE_DIR_R, channelpos); 
         Set_Bit(GPIO_PORTE_DEN_R, channelpos); 
      }else{
         Set_Bit(GPIO_PORTE_CR_R, channelpos); 
         Clear_Bit(GPIO_PORTE_DIR_R, channelpos); 
         Set_Bit(GPIO_PORTE_DEN_R, channelpos);
         Set_Bit(GPIO_PORTE_PUR_R, channelpos);
        }
     GPIO_PORTE_LOCK_R = 0x4C4F434B;
		break;
    case DIO_PortF:
      if(pinCFG[count].PinDir == Output){
          Set_Bit(GPIO_PORTF_CR_R, channelpos); 
          Set_Bit(GPIO_PORTF_DIR_R, channelpos); 
          Set_Bit(GPIO_PORTF_DEN_R, channelpos); 
       }else{
          Set_Bit(GPIO_PORTF_CR_R, channelpos); 
          Clear_Bit(GPIO_PORTF_DIR_R, channelpos); 
          Set_Bit(GPIO_PORTF_DEN_R, channelpos);
          Set_Bit(GPIO_PORTF_PUR_R, channelpos);
         }
      GPIO_PORTF_LOCK_R = 0x4C4F434B;
		break;
			
		}
	}
	GPIO_PORTA_DATA_R = 0;
	GPIO_PORTB_DATA_R = 0;
	GPIO_PORTC_DATA_R = 0;
	GPIO_PORTD_DATA_R = 0;
	GPIO_PORTE_DATA_R = 0;
	GPIO_PORTF_DATA_R = 0;
}
/////////////////////////////////////////////////////////////

void DIO_WritePort(DIO_PortTypes portx , uint32 data){
  switch(portx){
    case DIO_PortA:
      GPIO_PORTA_DATA_R = data;
      break;
     case DIO_PortB:
      GPIO_PORTB_DATA_R = data;
      break;
     case DIO_PortC:
      GPIO_PORTC_DATA_R = data;
      break;
     case DIO_PortD:
      GPIO_PORTD_DATA_R = data;
      break;
     case DIO_PortE:
      GPIO_PORTE_DATA_R = data;
      break;
     case DIO_PortF:
      GPIO_PORTF_DATA_R = data;
      break;
  }
}
void DIO_WritePin(DIO_ChannelTypes channel, STD_Level level){
    DIO_PortTypes portx = (DIO_PortTypes)(channel / 8);
    DIO_ChannelTypes binNumber = (DIO_ChannelTypes)(channel % 8);
    switch(portx){
    case DIO_PortA:
    if(level == HIGH){
        Set_Bit(GPIO_PORTA_DATA_R, binNumber);
    }
    else{
        Clear_Bit(GPIO_PORTA_DATA_R, binNumber);
    }
    break;
    case DIO_PortB:
    if(level == HIGH){
        Set_Bit(GPIO_PORTB_DATA_R, binNumber);
    }
    else{
        Clear_Bit(GPIO_PORTB_DATA_R, binNumber);
    }
    break;
    case DIO_PortC:
    if(level == HIGH){
        Set_Bit(GPIO_PORTC_DATA_R, binNumber);
    }
    else{
        Clear_Bit(GPIO_PORTC_DATA_R, binNumber);
    }
    break;
    case DIO_PortD:
    if(level == HIGH){
        Set_Bit(GPIO_PORTD_DATA_R, binNumber);
    }
    else{
        Clear_Bit(GPIO_PORTD_DATA_R, binNumber);
    }
    break;
    case DIO_PortE:
    if(level == HIGH){
        Set_Bit(GPIO_PORTE_DATA_R, binNumber);
    }
    else{
        Clear_Bit(GPIO_PORTE_DATA_R, binNumber);
    }
    break;
    case DIO_PortF:
    if(level == HIGH){
        Set_Bit(GPIO_PORTF_DATA_R, binNumber);
    }
    else{
        Clear_Bit(GPIO_PORTF_DATA_R, binNumber);
    }
    break;
  }
    
    

}





uint8 DIO_Read(DIO_ChannelTypes channel){
        uint16 data = 0;
	DIO_PortTypes portx = (DIO_PortTypes)(channel/8);
	DIO_ChannelTypes channelpos = (DIO_ChannelTypes)(channel %8);
	switch(portx){
            case DIO_PortA:
            data = Get_Bit(GPIO_PORTA_DATA_R, channelpos);
            break;
            case DIO_PortB:
            data = Get_Bit(GPIO_PORTB_DATA_R, channelpos);
            break;
            case DIO_PortC:
            data = Get_Bit(GPIO_PORTC_DATA_R, channelpos);
            break;
            case DIO_PortD:
            data = Get_Bit(GPIO_PORTD_DATA_R, channelpos);
            break;
            case DIO_PortE:
            data = Get_Bit(GPIO_PORTE_DATA_R, channelpos);
            break;
            case DIO_PortF:
            data = Get_Bit(GPIO_PORTF_DATA_R, channelpos);
            break;	
	}
        return data;
}

uint8 DIO_ReadPort(DIO_PortTypes portx){
  uint8 data = 0;
  switch(portx){
    case DIO_PortA:
      data = GPIO_PORTA_DATA_R;
      break;
     case DIO_PortB:
      data = GPIO_PORTB_DATA_R;
      break;
     case DIO_PortC:
      data = GPIO_PORTC_DATA_R;
      break;
     case DIO_PortD:
      data = GPIO_PORTD_DATA_R;
      break;
     case DIO_PortE:
      data = GPIO_PORTE_DATA_R;
      break;
     case DIO_PortF:
      data = GPIO_PORTF_DATA_R;
      break;
  }
  return data;
}

