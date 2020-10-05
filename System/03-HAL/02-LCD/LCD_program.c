/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"

# define F_CPU 1000000UL
#include "avr/delay.h"

void LCD_voidInit(void)
{
	_delay_ms(40);
	LCD_voidSendCommand(FUNC_SET);
	LCD_voidSendCommand(DISPLAY_ON_CURSOR_OFF);
	LCD_voidSendCommand(INCREMENT_CURSORMOVE);
	LCD_voidSendCommand(CLR_DISPLAY);
	LCD_voidSendCommand(CURSOR_AT_HOME);
}
void LCD_voidSendChar( char Copy_u8Data)
{
	//send command
	DIO_voidSetPortValue(LCD_DATA,Copy_u8Data);
	DIO_voidSetPinValue(LCD_RS,HIGH);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	//set clock
	DIO_voidSetPinValue(LCD_E,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_E,LOW);
	_delay_ms(2);	
}
void LCD_voidSendCommand(u8 Copy_u8Command)
{	
	//send command
	DIO_voidSetPortValue(LCD_DATA,Copy_u8Command);
	DIO_voidSetPinValue(LCD_RS,LOW);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	//set clock
	DIO_voidSetPinValue(LCD_E,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_E,LOW);
	_delay_ms(2);
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
