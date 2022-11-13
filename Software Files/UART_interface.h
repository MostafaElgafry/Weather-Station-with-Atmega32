/*
*Author     : Group T9 communications Engineering
*Date       : 5 SEP 2021
*Version    : V01
*/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void UART_voidInit();

u8 UART_u8DataAvailable();

void UART_voidOnReceive(void (*Copy_PvoidOnReceiveFunction)(void));
void UART_voidOnSend(void (*Copy_PvoidOnSendFunction)(void));

void UART_voidSendChar(char Copy_u8Char);
void UART_voidSendStr(char *Copy_u8Str);

void UART_voidSendNumber(u32 Copy_u32Number);

void UART_voidPrintNewLine(void);

char UART_u8ReadChar(void);

void UART_voidStoreChar(u8* Copy_Pu8CharLocation);
void UART_voidReadStr(char* Copy_Pu8StrLocation,u16 Copy_u8StrLen);

void UART_voidEnableRxInterrupt(void);
void UART_voidEnableTxInterrupt(void);

void UART_voidDisableRxInterrupt(void);
void UART_voidDisableTxInterrupt(void);
#endif

