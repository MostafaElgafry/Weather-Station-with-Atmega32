/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define 	EXTI0					0
#define 	EXTI1					1
#define 	EXTI2					2

#define 	FALLING_EDGE			0
#define 	RISING_EDGE				1
#define 	ANY_LOGICAL_CHANGE		2
#define 	LOW_LEVEL				3

void EXTI_voidEnableInterrupt(u8 Copy_u8IntID);
void EXTI0_voidSetCallBack(void (*ptr) (void));
void EXTI1_voidSetCallBack(void (*ptr) (void));
u8 Global_u8Int1Counter ;
#endif