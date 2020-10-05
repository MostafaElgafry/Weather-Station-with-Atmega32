/*
 * Hello_SevenSegment.c
 *
 * Created: 9/23/2020 10:35:06 PM
 * Author : G3fry
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SEVENSEG_interface.h"

int main(void)
{	
	u8 Local_u8Counter=0;
    /* Set Input pins for bush buttons  */
	DIO_voidSetPinDirection( 0,PORTA,INPUT_PULL_UP); //UP_Button
	DIO_voidSetPinDirection( 1,PORTA,INPUT_PULL_UP); //DOWN_Button
	DIO_voidSetPinDirection( 2,PORTA,INPUT_PULL_UP); //RESET_Button
	 /* Set pins for seven segment */
	 
	SEVESEG_voidInit();     
	
	SEVESEG_u8Dispaly(Local_u8Counter);   
    while (1) 
    {
		SEVESEG_u8Dispaly(Local_u8Counter);  
		
		if (!DIO_u8GetPinValue(0, PORTA))
		{
			Local_u8Counter++;
			while (!DIO_u8GetPinValue(0, PORTA)) ;
		}
		if (!DIO_u8GetPinValue(1, PORTA))
		{
			Local_u8Counter--;
			while (!DIO_u8GetPinValue(1, PORTA)) ;
		}
		if (!DIO_u8GetPinValue(2, PORTA))
		{
			Local_u8Counter=0;
			while (!DIO_u8GetPinValue(2, PORTA)) ;
		}
		
		SEVESEG_u8Dispaly(Local_u8Counter); 
    }
}

