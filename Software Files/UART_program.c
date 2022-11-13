/*
*Author     : Group T9 communications Engineering
*Date       : 5 SEP 2021
*Version    : V01
*/

#include <stdio.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

#include <avr/interrupt.h>


void UART_voidInit()
{
	/*SET The BaudRate*/
	u16 Local_16BaudRate = (UART_CPU_CLOCK)/(16*(u32)UART_BAUD_RATE);	
	UBRRH = ((Local_16BaudRate)>>8) &0x0F;
	UBRRL = Local_16BaudRate & 0xFF;
	
	/*cleared the UCSRC register*/
	UCSRC = (1<<7);
	
	/*Initialize the UART with selected options*/
	UCSRC |= (1<<7) | (UART_PARITY_MODE<<4) | (UART_STOP_BITS<<3) | (UART_DATA_BITS<<1);
	
	/*Enable the UART*/
	UCSRB |= 0x18; 		//Enable Transmit and Receive
	
	
}

u8 UART_u8DataAvailable()
{
	return GET_BIT(UCSRA,7);
}

void UART_voidPrintNewLine(void)
{
	UART_voidSendChar((char)13);
}

void UART_voidOnReceive(void (*Copy_PvoidOnReceiveFunction)(void))
{
	/*Set the Receive complete interrupt handler*/
	RX_InterruptHandle = Copy_PvoidOnReceiveFunction;
}

void UART_voidOnSend(void (*Copy_PvoidOnSendFunction)(void))
{
	/*Set the Transmit complete interrupt handler*/
	TX_InterruptHandle = Copy_PvoidOnSendFunction;
}

void UART_voidEnableRxInterrupt(void)
{
	/*Enable Receive Complete interrupt*/
	SET_BIT(UCSRB,7);
	
	/*Global interrupt enable*/
	SET_BIT(SREG,7);
}
void UART_voidEnableTxInterrupt(void)
{
	/*Enable Transmit Complete interrupt*/
	SET_BIT(UCSRB,6);
	
	/*Global interrupt enable*/
	SET_BIT(SREG,7);
}

void UART_voidDisableRxInterrupt(void)
{
	CLR_BIT(UCSRB,7);
}
void UART_voidDisableTxInterrupt(void)
{
	CLR_BIT(UCSRB,6);
}

void UART_voidSendChar(char Copy_u8Char)
{
	/*wait if there is a char in UDR*/
	while(!GET_BIT(UCSRA,5));
	UDR = Copy_u8Char;
}
void UART_voidSendStr(char *Copy_u8Str)
{
	while(*Copy_u8Str != '\0'){
		UART_voidSendChar(*Copy_u8Str);
		Copy_u8Str++;
	}
}


void UART_voidSendNumber(u32 Copy_u32Number)
{
	char Str[10];
	sprintf(Str,"%lx",Copy_u32Number);
	UART_voidSendStr(Str);
}

char UART_u8ReadChar(void)
{
	/*wait for reception*/
	while(!GET_BIT(UCSRA,7));
		return (char)UDR;
}

void UART_voidStoreChar(u8* Copy_Pu8CharLocation)
{
	*Copy_Pu8CharLocation = UART_u8ReadChar();
}

void UART_voidReadStr(char* Copy_Pu8StrLocation,u16 Copy_u8StrLen)
{
	/*Receive string with timeout, if timeout reaches zero then 
	there is nothing to receive and the reception is finished */
	
	u16 i = 0,Timout = 10000;
	while(Copy_u8StrLen--)
	{
		while (!GET_BIT(UCSRA,7) && Timout) Timout--;
		if(Timout == 0)
			Copy_Pu8StrLocation[i] = '\0';
		else
			Copy_Pu8StrLocation[i] = UDR;
		if(Copy_Pu8StrLocation[i] == '\0')
			break;
		i++;
	}
	
	
}


ISR(USART_RXC_vect)
{
	if(RX_InterruptHandle != 0)
		RX_InterruptHandle();
};

ISR(USART_UDRE_vect)
{
	if(UDR_InterruptHandle != 0)
		UDR_InterruptHandle();
};

ISR(USART_TXC_vect)
{	
	if(TX_InterruptHandle != 0)
		TX_InterruptHandle();
};