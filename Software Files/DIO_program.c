/*
*Author     : Group T9 communications Engineering
*Date       : 23 AUG 2021
*Version    : V01
*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_registers.h"


void DIO_voidSetPinDirection (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Direction)
{
	switch (Copy_u8PortNumber)
	{
		case PORTA:
			if(Copy_u8Direction == OUTPUT)
			{
				SET_BIT(DDRA_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT)
			{
				CLR_BIT(DDRA_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT_PULL_UP)
			{
				SET_BIT(PORTA_REG , Copy_u8PinNumber);
				CLR_BIT(DDRA_REG , Copy_u8PinNumber);
			}
			break;

		case PORTB:
			if(Copy_u8Direction == OUTPUT)
			{
				SET_BIT(DDRB_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT)
			{
				CLR_BIT(DDRB_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT_PULL_UP)
			{
				SET_BIT(PORTB_REG , Copy_u8PinNumber);
				CLR_BIT(DDRB_REG , Copy_u8PinNumber);
			}
			break;

		case PORTC:
			if(Copy_u8Direction == OUTPUT)
			{
				SET_BIT(DDRC_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT)
			{
				CLR_BIT(DDRC_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT_PULL_UP)
			{
				SET_BIT(PORTC_REG , Copy_u8PinNumber);
				CLR_BIT(DDRC_REG , Copy_u8PinNumber);
			}
			break;

		case PORTD:
			if(Copy_u8Direction == OUTPUT)
			{
				SET_BIT(DDRD_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT)
			{
				CLR_BIT(DDRD_REG , Copy_u8PinNumber);
			}
			else if (Copy_u8Direction == INPUT_PULL_UP)
			{
				SET_BIT(PORTD_REG , Copy_u8PinNumber);
				CLR_BIT(DDRD_REG , Copy_u8PinNumber);
			}
			break;
	}
}

void DIO_voidSetPortDirection (u8 Copy_u8PortNumber, u8 Copy_u8PortDirection)
{
	switch (Copy_u8PortNumber)
	{
		case PORTA:

			if(Copy_u8PortDirection == OUTPUT)
			{	
				DDRA_REG=0xFF;
			}
			else if (Copy_u8PortDirection == INPUT)
			{
				DDRA_REG=0x00;
			}
			else if (Copy_u8PortDirection == INPUT_PULL_UP)
			{
				PORTA_REG=0xFF;
				DDRA_REG=0x00;
			}
			break;

		case PORTB:

			if(Copy_u8PortDirection == OUTPUT)
			{	
				DDRB_REG=0xFF;
			}
			else if (Copy_u8PortDirection == INPUT)
			{
				DDRB_REG=0x00;
			}
			else if (Copy_u8PortDirection == INPUT_PULL_UP)
			{
				PORTB_REG=0xFF;
				DDRB_REG=0x00;
			}
			break;

		case PORTC:

			if(Copy_u8PortDirection == OUTPUT)
			{	
				DDRC_REG=0xFF;
			}
			else if (Copy_u8PortDirection == INPUT)
			{
				DDRC_REG=0x00;
			}
			else if (Copy_u8PortDirection == INPUT_PULL_UP)
			{
				PORTC_REG=0xFF;
				DDRC_REG=0x00;
			}
			break;

		case PORTD:

			if(Copy_u8PortDirection == OUTPUT)
			{	
				DDRD_REG=0xFF;
			}
			else if (Copy_u8PortDirection == INPUT)
			{
				DDRD_REG=0x00;
			}
			else if (Copy_u8PortDirection == INPUT_PULL_UP)
			{
				PORTD_REG=0xFF;
				DDRD_REG=0x00;
			}
			break;
	}

}


void DIO_voidSetPinValue (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8Value)
{
	switch (Copy_u8PortNumber)
	{
		case PORTA:

			if( Copy_u8Value == HIGH)
			{
				SET_BIT(PORTA_REG , Copy_u8PinNumber);
			}
			else if ( Copy_u8Value ==LOW)
			{
				CLR_BIT(PORTA_REG , Copy_u8PinNumber);
			}
			break;

		case PORTB:

			if( Copy_u8Value == HIGH)
			{
				SET_BIT(PORTB_REG , Copy_u8PinNumber);
			}
			else if ( Copy_u8Value ==LOW)
			{
				CLR_BIT(PORTB_REG , Copy_u8PinNumber);
			}
			break;

		case PORTC:

			if( Copy_u8Value == HIGH)
			{
				SET_BIT(PORTC_REG , Copy_u8PinNumber);
			}
			else if ( Copy_u8Value ==LOW)
			{
				CLR_BIT(PORTC_REG , Copy_u8PinNumber);
			}
			break;

		case PORTD:

			if( Copy_u8Value == HIGH)
			{
				SET_BIT(PORTD_REG , Copy_u8PinNumber);
			}
			else if ( Copy_u8Value ==LOW)
			{
				CLR_BIT(PORTD_REG , Copy_u8PinNumber);
			}
			break;
	}
}

void DIO_voidSetPortValue (u8 Copy_u8PortNumber, u8 Copy_u8Value)
{
	switch(Copy_u8PortNumber)
	{
		case PORTA:
			PORTA_REG=Copy_u8Value;
			break;

		case PORTB:
			PORTB_REG=Copy_u8Value;
			break;

		case PORTC:
			PORTC_REG=Copy_u8Value;
			break;

		case PORTD:
			PORTD_REG=Copy_u8Value;
			break;

	}
}


u8 DIO_u8GetPinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber)
{
	switch (Copy_u8PortNumber)
	{
		case PORTA:
			return GET_BIT(PINA_REG , Copy_u8PinNumber);

		case PORTB:
			return GET_BIT(PINB_REG , Copy_u8PinNumber);

		case PORTC:
			return GET_BIT(PINC_REG , Copy_u8PinNumber);

		case PORTD:
			return GET_BIT(PIND_REG , Copy_u8PinNumber);

	}
	return 0;  //34an el warning :D
}

u8 DIO_u8GetPortValue(u8 Copy_u8PortNumber)
{
	switch (Copy_u8PortNumber)
	{
		case PORTA:
			return PINA_REG;

		case PORTB:
			return PINB_REG;

		case PORTC:
			return PINC_REG;

		case PORTD:
			return PIND_REG;
	}
	return 0;   //34an el warning tany :D
}


void DIO_voidTogglePinValue (u8 Copy_u8PinNumber, u8 Copy_u8PortNumber)
{
	switch (Copy_u8PortNumber)
	{
		case PORTA:

		TOG_BIT(PORTA_REG , Copy_u8PinNumber);

		case PORTB:

		TOG_BIT(PORTB_REG , Copy_u8PinNumber);

		case PORTC:

		TOG_BIT(PORTC_REG , Copy_u8PinNumber);
		
		case PORTD:

		TOG_BIT(PORTD_REG , Copy_u8PinNumber);
	}
}
