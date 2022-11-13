/*
*Author     : Group T9 communications Engineering
*Date       : 23 AUG 2021
*Version    : V01
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CLOCK_interface.h"
#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//#include "avr/delay.h"

void LCD_voidInit(void)
{
	MCLOCK_voidDelayMS(40);
	LCD_voidSendCommand(0x02);
	LCD_voidSendCommand(FUNC_SET);
	LCD_voidSendCommand(DISPLAY_ON_CURSOR_OFF);
	LCD_voidSendCommand(INCREMENT_CURSORMOVE);
	LCD_voidSendCommand(CLR_DISPLAY);
	LCD_voidSendCommand(CURSOR_AT_HOME);
}
void LCD_voidSendChar( char Copy_u8Data)
{
	
	//send the lift 4bit of the data
	u8 data =  Copy_u8Data & 0xF0;
	DIO_voidSetPinValue(D7,GET_BIT(data,7));
	DIO_voidSetPinValue(D6,GET_BIT(data,6));
	DIO_voidSetPinValue(D5,GET_BIT(data,5));
	DIO_voidSetPinValue(D4,GET_BIT(data,4));
	DIO_voidSetPinValue(LCD_RS,HIGH);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	//set clock
	DIO_voidSetPinValue(LCD_E,HIGH);
	MCLOCK_voidDelayMS(2);
	DIO_voidSetPinValue(LCD_E,LOW);
	MCLOCK_voidDelayMS(2);
		
	//send the right 4bit of the data
	data = ( ( Copy_u8Data<<4) & 0xF0);
	DIO_voidSetPinValue(D7,GET_BIT(data,7));
	DIO_voidSetPinValue(D6,GET_BIT(data,6));
	DIO_voidSetPinValue(D5,GET_BIT(data,5));
	DIO_voidSetPinValue(D4,GET_BIT(data,4));
	DIO_voidSetPinValue(LCD_RS,HIGH);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	//set clock
	DIO_voidSetPinValue(LCD_E,HIGH);
	MCLOCK_voidDelayMS(2);
	DIO_voidSetPinValue(LCD_E,LOW);
	MCLOCK_voidDelayMS(2);
}
void LCD_voidSendCommand(u8 Copy_u8Command)
{	
	//send the lift 4bit of the command
	u8 command = Copy_u8Command & 0xF0;
	DIO_voidSetPinValue(D7,GET_BIT(command,7));
	DIO_voidSetPinValue(D6,GET_BIT(command,6));
	DIO_voidSetPinValue(D5,GET_BIT(command,5));
	DIO_voidSetPinValue(D4,GET_BIT(command,4));
	DIO_voidSetPinValue(LCD_RS,LOW);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	//set clock
	DIO_voidSetPinValue(LCD_E,HIGH);
	MCLOCK_voidDelayMS(2);
	DIO_voidSetPinValue(LCD_E,LOW);
	MCLOCK_voidDelayMS(2);
	
	//send the Right 4bit of the command
	command = ( (Copy_u8Command<<4) & 0xF0);
	DIO_voidSetPinValue(D7,GET_BIT(command,7));
	DIO_voidSetPinValue(D6,GET_BIT(command,6));
	DIO_voidSetPinValue(D5,GET_BIT(command,5));
	DIO_voidSetPinValue(D4,GET_BIT(command,4));
	DIO_voidSetPinValue(LCD_RS,LOW);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	//set clock
	DIO_voidSetPinValue(LCD_E,HIGH);
	MCLOCK_voidDelayMS(2);
	DIO_voidSetPinValue(LCD_E,LOW);
	MCLOCK_voidDelayMS(2);
}
void LCD_voidSendString(char* PtrStrig)
{

	u8 Local_u8Couter ;
	for(Local_u8Couter=0; PtrStrig[Local_u8Couter]!=0;Local_u8Couter++)		
	/* Send each char of string till the NULL */
	{
			LCD_voidSendChar( PtrStrig[Local_u8Couter]);
	}
}
void LCD_voidClear()
{
	LCD_voidSendCommand (CLR_DISPLAY);	     	/* clear display */
	LCD_voidSendCommand (CURSOR_AT_HOME);		/* cursor at home position */
}	
void LCD_voidSetCursorPosition(u8 CopyPosition)
{
	LCD_voidSendCommand (0x80 + CopyPosition);	     	
}

void LCD_voidSendNumber(u8* PtrString)
{
	
	
	
}
