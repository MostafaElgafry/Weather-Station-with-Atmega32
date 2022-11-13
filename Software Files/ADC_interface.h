/*
*Author     : Group T9 communications Engineering
*Date       : 24 AUG 2021
*Version    : V01
*/



#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*ADC Channels*/
#define ADC0		0
#define ADC1		1
#define ADC2		2
#define ADC3		3
#define ADC4		4
#define ADC5		5
#define ADC6		6
#define ADC7		7

/*Voltage Reference Options*/
#define ADC_AREF_PIN					0
#define	ADC_AVCC_PIN					1
#define	ADC_INTERNAL_2_56_V 			3


/*Prescalar Selection Options*/
#define ADC_PRESCALAR_DIV_2				1
#define ADC_PRESCALAR_DIV_4				2
#define ADC_PRESCALAR_DIV_8				3
#define ADC_PRESCALAR_DIV_16			4
#define ADC_PRESCALAR_DIV_32			5
#define ADC_PRESCALAR_DIV_64			6
#define ADC_PRESCALAR_DIV_128			7

/*Functions' Prototypes*/
void ADC_voidInit(void);				/*Initialize the ADC*/
void ADC_voidDisable(void);				/*Disable the ADC*/
u16	ADC_u16ReadChannel(u8 Channel);		/*Read 10-bit resolution value from a channel*/
u8 ADC_u8ReadChannel(u8 Channel);		/*Read 8-bit resolution value from a channel*/

#endif /* ADC_INTERFACE_H_ */