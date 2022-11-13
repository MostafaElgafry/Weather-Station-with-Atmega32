/*
*Author     : Group T9 communications Engineering
*Date       : 5 SEP 2021
*Version    : V01
*/

#ifndef UART_CONFIG_H
#define UART_CONFIG_H


#define UART_CPU_CLOCK			16000000UL

#define UART_BAUD_RATE			9600

/*Options:	UART_ENABLED
			UART_DISABLED
			UART_EVEN_PARITY
			UART_ODD_PARITY		*/
#define UART_PARITY_MODE		UART_DISABLED

/*Options:	UART_1_BIT
			UART_2_BIT*/
#define UART_STOP_BITS			UART_1_BIT

/*Options:	UART_DATA_5_BITS
			UART_DATA_6_BITS
			UART_DATA_7_BITS
			UART_DATA_8_BITS*/
#define UART_DATA_BITS			UART_DATA_8_BITS


#endif

