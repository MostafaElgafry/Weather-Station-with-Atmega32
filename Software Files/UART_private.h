/*
*Author     : Group T9 communications Engineering
*Date       : 5 SEP 2021
*Version    : V01
*/

#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


#define UART_DISABLED				0
#define UART_ENABLED				1
#define UART_EVEN_PARITY			2
#define UART_ODD_PARITY				3

#define UART_1_BIT					0
#define UART_2_BIT					1

#define UART_DATA_5_BITS			0
#define UART_DATA_6_BITS			1
#define UART_DATA_7_BITS			2
#define UART_DATA_8_BITS			3

void (*RX_InterruptHandle)(void) = 0;
void (*TX_InterruptHandle)(void) = 0;
void (*UDR_InterruptHandle)(void) = 0;

#define UDR				(*(volatile u8*)0x2C)
#define UCSRA			(*(volatile u8*)0x2B)
#define UCSRB			(*(volatile u8*)0x2A)
#define UCSRC			(*(volatile u8*)0x40)
#define UBRRL			(*(volatile u8*)0x29)
#define UBRRH			(*(volatile u8*)0x40)




#endif

