/*
*Author     : Group T9 communications Engineering
*Date       : 24 AUG 2021
*Version    : V01
*/


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*
SELECT Voltage Reference AS SHOWN
	*ADC_AREF_PIN		
	*ADC_AVCC_PIN		
	*ADC_INTERNAL_2_56_V 
*/
#define REFERENCE_VOLTAGE	ADC_AVCC_PIN

/*
SELECT Voltage Reference AS SHOWN
	*ADC_PRESCALAR_DIV_2	
	*ADC_PRESCALAR_DIV_4	
	*ADC_PRESCALAR_DIV_8	 
	*ADC_PRESCALAR_DIV_16
	*ADC_PRESCALAR_DIV_32
	*ADC_PRESCALAR_DIV_64
	*ADC_PRESCALAR_DIV_128
*/
/*Warning! : use a prescalar to get an ADC clock between 50 KHz and 200 KHz*/
#define ADC_PRESCALAR		ADC_PRESCALAR_DIV_128




#endif /* ADC_CONFIG_H_ */