/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#define 	SREG 	 (*(volatile u8*)(0x5F))
#define 	MCUCR 	 (*(volatile u8*)(0x55))
#define 	MCUCSR 	 (*(volatile u8*)(0x54))
#define 	GICR 	 (*(volatile u8*)(0x5B))
#define 	GIFR 	 (*(volatile u8*)(0x5A))



#endif