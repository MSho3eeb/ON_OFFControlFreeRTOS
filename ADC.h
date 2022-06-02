#ifndef ADC_H_
#define ADC_H_

#include "DIO.h"
#include "types.h"
#include "DIO_Types.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>




void ADC0Init(void);
int ADC0Read(void);


#endif