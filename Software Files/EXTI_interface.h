/*
*Author     : Group T9 communications Engineering
*Date       : 30 AUG 2021
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
void EXTI2_voidSetCallBack(void (*ptr) (void));
u8 Global_u8Int1Counter ;
#endif