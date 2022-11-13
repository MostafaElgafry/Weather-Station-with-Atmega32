/*
*Author     : Group T9 communications Engineering
*Date       : 8 SEP 2021
*Version    : V01
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include <stdio.h>

#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LDR_interface.h"
#include "LDR_config.h"
#include "CLOCK_interface.h"
#include "LCD_interface.h"

#include "Payload.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//#include "avr/delay.h"

void LDR(void)
{
	char value[20];
	u16 ADC_value = ADC_u16ReadChannel(LDR_PIN);
	sprintf(value, "V = %d", ADC_value);
	LCD_voidSetCursorPosition(0x09);
	if(ADC_value > 200)
	{
		LCD_voidSendString("Day");
		SensorsPayload[1] = 1; 
	}
	else
		LCD_voidSendString("Night");
		SensorsPayload[1] = 0;
}