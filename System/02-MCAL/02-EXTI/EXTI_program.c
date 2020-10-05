/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

#include <avr/interrupt.h>

#define		 NULL	(void * )0
static void (* EXTI0_CallBack) (void) = NULL ;  //pointer to the function which is executed when EXTI0 is fired
static void (* EXTI1_CallBack) (void) = NULL ;  //pointer to the function which is executed when EXTI0 is fired

void EXTI_voidEnableInterrupt(u8 Copy_u8IntID)
{
	switch(Copy_u8IntID)
	{
		case EXTI0:	
					//external0 interrupt enable
					SET_BIT(GICR,6);
					//global interrupt enable
					SET_BIT(SREG,7);
					//set interrupt type
					if(EXTI0_TYPE==FALLING_EDGE)
					{
						CLR_BIT(MCUCR,0);	
						SET_BIT(MCUCR,1);		
					}
					else if(EXTI0_TYPE==RISING_EDGE)
					{
						SET_BIT(MCUCR,0);	
						SET_BIT(MCUCR,1);		
					}
					else if(EXTI0_TYPE==ANY_LOGICAL_CHANGE)
					{
						SET_BIT(MCUCR,0);	
						CLR_BIT(MCUCR,1);		
					}
					else if(EXTI0_TYPE==LOW_LEVEL)
					{
						CLR_BIT(MCUCR,0);	
						CLR_BIT(MCUCR,1);	
					}
					break;
		case EXTI1:	
					//external1 interrupt enable
					SET_BIT(GICR,7);
					//global interrupt enable
					SET_BIT(SREG,7);
					//set interrupt type
					if(EXTI1_TYPE==FALLING_EDGE)
					{
						CLR_BIT(MCUCR,2);	
						SET_BIT(MCUCR,3);		
					}
					else if(EXTI1_TYPE==RISING_EDGE)
					{
						SET_BIT(MCUCR,2);	
						SET_BIT(MCUCR,3);		
					}
					else if(EXTI1_TYPE==ANY_LOGICAL_CHANGE)
					{
						SET_BIT(MCUCR,2);	
						CLR_BIT(MCUCR,3);		
					}
					else if(EXTI1_TYPE==LOW_LEVEL)
					{
						CLR_BIT(MCUCR,2);	
						CLR_BIT(MCUCR,3);	
					}
					break;		
	}
}

//handling EXTI0 request
void EXTI0_voidSetCallBack(void (*ptr) (void)) 
{
	EXTI0_CallBack = ptr ; //assign the function address which is been sent to the EXTI0_CallBack
}
ISR(INT0_vect)
{
	EXTI0_CallBack();   //execute the function which is been sent
}



//handling EXTI1 request
void EXTI1_voidSetCallBack(void (*ptr) (void)) 
{
	EXTI1_CallBack = ptr ; //assign the function address which is been sent to the EXTI0_CallBack
}

ISR(INT1_vect)
{	
	Global_u8Int1Counter ++;
	EXTI1_CallBack();  //execute the function which is been sent
	
	if(Global_u8Int1Counter > 3) //repeat to SPEED 1
	{
		Global_u8Int1Counter=1;
	}
}