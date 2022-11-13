/*
*Author     : Group T9 communications Engineering
*Date       : 24 AUG 2021
*Version    : V01
*/


#ifndef ADC_REGISTERS_H_
#define ADC_REGISTERS_H_

#define ADMUX		(*(volatile u8*)(0x27))
#define ADCSRA		(*(volatile u8*)(0x26))
#define ADCH		(*(volatile u8*)(0x25))
#define ADCL		(*(volatile u8*)(0x24))


#endif /* ADC_REGISTERS_H_ */