/*
*Author     : Group T9 communications Engineering
*Date       : 23 AUG 2021
*Version    : V01
*/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define		 FUNC_SET_8BIT_1LINE		0x30
#define		 FUNC_SET_8BIT_2LINE		0x38
#define		 FUNC_SET_4BIT_1LINE		0x20
#define		 FUNC_SET_4BIT_2LINE		0x28

#define		 CLR_DISPLAY				0x01

#define		 INCREMENT_CURSORMOVE		0x06

#define		DISPLAY_OFF_CURSOR_OFF			 0x08
#define		DISPLAY_ON_CURSOR_ON			 0x0E
#define		DISPLAY_ON_CURSOR_OFF			 0x0C
#define		DISPLAY_ON_CURSOR_BLINKING       0x08
 
#define		CURSOR_AT_HOME					 0x80
#define		SHIFT_ENTIRE_DISPLAY_LEFT		 0X18
#define		SHIFT_ENTIRE_DISPLAY_RIGHT		 0X1C

#define		MOVE_CURSOR_LEFT_ONE_CHAR		 0x10
#define		MOVE_CURSOR_RIGHT_ONE_CHAR		 0x14

			



void LCD_voidInit(void);
void LCD_voidSendChar( char Copy_u8Data);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendString(char* PtrStrig);
void LCD_voidSendNumber(u8* PtrString);
void LCD_voidClear();
void LCD_voidSetCursorPosition(u8 CopyPosition);


#endif