/*
*Author     : Group T9 communications Engineering
*Date       : 23 AUG 2021
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
#define 	LCD_RS 			6,PORTC		
#define 	LCD_RW			5,PORTC
#define 	LCD_E			4,PORTC	
/*
select data pins connection 
*/
//#define 	LCD_DATA		PORTA

#define     D4              3,PORTC	
#define     D5              2,PORTC	
#define     D6              1,PORTC	
#define     D7              0,PORTC	
/*

								FUNC_SET_8BIT_1LINE		
								FUNC_SET_8BIT_2LINE		
								FUNC_SET_4BIT_1LINE		
								FUNC_SET_4BIT_2LINE		
*/
#define 	FUNC_SET	 FUNC_SET_4BIT_2LINE
#endif