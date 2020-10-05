/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H
/*
Select control pins connection as shown:
									0,PORTA
									1,PORTA
									2,PORTA	
										.
										.
										.
										.
*/
#define 	LCD_RS 			5,PORTD	
#define 	LCD_RW			6,PORTD
#define 	LCD_E			7,PORTD
/*
select data pins connection 
*/
#define 	LCD_DATA		PORTB

/*Selct Function set type as shown:
								FUNC_SET_8BIT_1LINE		
								FUNC_SET_8BIT_2LINE		
								FUNC_SET_4BIT_1LINE		
								FUNC_SET_8BIT_2LINE		
*/
#define 	FUNC_SET	FUNC_SET_8BIT_2LINE	
#endif