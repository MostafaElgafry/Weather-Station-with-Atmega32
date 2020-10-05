/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"



#define		 NULL	(void * )0
static void (* EXTI0_CallBack) (void) = NULL ;  //pointer to the function which is executed when EXTI0 is fired
static void (* EXTI1_CallBack) (void) = NULL ;  //pointer to the function which is executed when EXTI0 is fired
