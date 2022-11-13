/*
*Author     : Group T9 communications Engineering
*Date       : 25 AUG 2021
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_registers.h"

void ADC_voidInit(void)
{
	/*Set the Selected Voltage Reference*/
	ADMUX 	= (REFERENCE_VOLTAGE << 6);
	
	/*Set the Selected Prescalar*/
	ADCSRA 	= ADC_PRESCALAR;
	
	/*Enable the ADC*/
	SET_BIT(ADCSRA,7);
}

void ADC_voidDisable(void)
{
	/*Disable the ADC*/
	CLR_BIT(ADCSRA,7);
}

u16 ADC_u16ReadChannel(u8 Channel)
{
	/*Enable the ADC*/
	SET_BIT(ADCSRA,7);
	
	/*Check for wrong channel number*/
	if (Channel >7 || Channel < 0)
	return -1;
	
	/*Right justified registers to read 10 bits*/
	CLR_BIT(ADMUX,5);
	
	
	/*clear the previous selected channel*/
	ADMUX &= 0xE0;
	/*Set the Selected ADC channel*/
	ADMUX |= Channel;
	
	/*Start Conversion*/
	SET_BIT(ADCSRA,6);
	
	/*Wait for the conversion to finish*/
	while(!GET_BIT(ADCSRA,4));
	
	/*Clear ADC flag*/
	CLR_BIT(ADCSRA,4);
	
	/*Disable the ADC*/
	CLR_BIT(ADCSRA,7);
	
	/*return converted Value*/
	return (ADCL | (ADCH<<8));
}