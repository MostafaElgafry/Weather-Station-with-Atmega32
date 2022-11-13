/*
*Author     : Group T9 communications Engineering
*Date       : 28 AUG 2021
*Version    : V01
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SPI_interface.h"
#include "SPI_registers.h"
#include "SPI_config.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif



/*Initialize the SPI interface*/
void SPI_voidInit(void)
{
	SPCR = (SPI_INTERRUPT<<7)|(1<<6)|(SPI_DATA_ORDER<<5)|(SPI_MODE<<4)
	|(SPI_CLOCK_POLARITY<<3)|(SPI_CLOCK_PHASE<<2)|(SPI_PRESCALAR);
	
	CLR_BIT(SPSR,0);
	
	//DIO_voidSetPinDirection(6,PORTB,OUTPUT);
	DIO_voidSetPinDirection(7,PORTB,OUTPUT);
	DIO_voidSetPinDirection(8,PORTB,OUTPUT);
	SET_BIT(SPCR,0);
	
}

/*Send one byte and receive one byte*/
u8 SPI_u8SendReceiveSynch(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	
	while(!GET_BIT(SPSR,7));
	
	return SPDR;
}

void SPI_voidSendReceiveAsynch(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	while(!GET_BIT(SPSR,7));
	
}

void SPI_voidTransmitArraySynch(u8* Copy_u8Ptr, u16 Copy_u16Length)
{
	u16 i=0;
	while(i<Copy_u16Length)
	{
		SPI_u8SendReceiveSynch(*(Copy_u8Ptr+i));
		i++;
	}
}

void SPI_voidPtrSendReceiveArraySynch(u8* Copy_u8PtrTransmitBuffer, u8* Copy_u8PtrReceiveBuffer,u16 Copy_u16Length)
{
	u16 i=0;
	while(i<Copy_u16Length)
	{
		*(Copy_u8PtrReceiveBuffer+i) = SPI_u8SendReceiveSynch(*(Copy_u8PtrTransmitBuffer+i));
		i++;
	}
}

/*Enable interrupt*/
void SPI_voidEnableInterrupt()
{
	SET_BIT(SPCR,7);
}


/*Disable interrupt*/
void SPI_voidDisableInterrupt()
{
	CLR_BIT(SPCR,7);
}




/*Set callback for interrupt*/
/*
void SPI_voidSetCallBack(void(*Copy_ptr)(u8 Copy_u8ReceivedData))
{
	if (GET_BIT(SPSR,7) && SPI_CallBack !=0)
	SPI_CallBack(SPDR);
}
*/