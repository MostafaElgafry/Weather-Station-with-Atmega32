/*
*Author     : Moustafa ElGafry
*Date       : 5 AUG 2020
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SEVENSEG_interface.h"
#include "SEVENSEG_config.h"

const u8 SevenSegmentArray [10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SEVESEG_voidInit(void)
{
	DIO_voidSetPinDirection (SEVENSEG_PIN1,OUTPUT);		
	DIO_voidSetPinDirection (SEVENSEG_PIN2,OUTPUT);	
	DIO_voidSetPinDirection (SEVENSEG_PIN3,OUTPUT);		
	DIO_voidSetPinDirection (SEVENSEG_PIN4,OUTPUT);		
	DIO_voidSetPinDirection (SEVENSEG_PIN5,OUTPUT);		
	DIO_voidSetPinDirection (SEVENSEG_PIN6,OUTPUT);		
	DIO_voidSetPinDirection (SEVENSEG_PIN7,OUTPUT);		
}
void SEVESEG_u8Dispaly(u8 Copy_u8Number)
{
	DIO_voidSetPinValue(SEVENSEG_PIN1, GET_BIT(SevenSegmentArray[Copy_u8Number],0) );
	DIO_voidSetPinValue(SEVENSEG_PIN2, GET_BIT(SevenSegmentArray[Copy_u8Number],1) );
	DIO_voidSetPinValue(SEVENSEG_PIN3, GET_BIT(SevenSegmentArray[Copy_u8Number],2) );
	DIO_voidSetPinValue(SEVENSEG_PIN4, GET_BIT(SevenSegmentArray[Copy_u8Number],3) );
	DIO_voidSetPinValue(SEVENSEG_PIN5, GET_BIT(SevenSegmentArray[Copy_u8Number],4) );
	DIO_voidSetPinValue(SEVENSEG_PIN6, GET_BIT(SevenSegmentArray[Copy_u8Number],5) );
	DIO_voidSetPinValue(SEVENSEG_PIN7, GET_BIT(SevenSegmentArray[Copy_u8Number],6) );	
}
