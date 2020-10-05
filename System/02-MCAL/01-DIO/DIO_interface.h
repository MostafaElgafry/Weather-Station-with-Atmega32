/*
*Author     : Moustafa ElGafry
*Date       : 5 AUG 2020
*Version    : V01
*/


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULL_UP 2

#define HIGH 1
#define LOW 0

		
void DIO_voidSetPinDirection (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Direction);	
void DIO_voidSetPortDirection (u8 Copy_u8PortNumber, u8 Copy_u8PortDirection);	

void DIO_voidSetPinValue (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Value);	
void DIO_voidSetPortValue (u8 Copy_u8PortNumber, u8 Copy_u8Value);	

u8 DIO_u8GetPinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber);	
u8 DIO_u8GetPortValue(u8 Copy_u8PortNumber);	

void DIO_voidTogglePinValue (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber);	
	
	
	
	
	
#endif 
