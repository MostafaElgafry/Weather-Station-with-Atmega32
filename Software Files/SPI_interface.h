/*
*Author     : Group T9 communications Engineering
*Date       : 27 AUG 2021
*Version    : V01
*/


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*Mode Options*/
#define SPI_SLAVE_MODE						0
#define SPI_MASTER_MODE						1

/*PreScalar Options*/
#define SPI_DEV_4							0
#define SPI_DEV_16							1
#define SPI_DEV_64							2
#define SPI_DEV_128							3


#define SPI_ENABLE							1
#define SPI_DISABLE							0

/*Options For Clock Polarity*/
#define SPI_IDLE_LOW						0
#define SPI_IDLE_HIGH						1

/*Options For Clock Phase*/
#define SPI_SAMPLE_ON_RISING_EDGE			0
#define SPI_SAMPLE_ON_FALLING_EDGE			1

/*Options For Data Order*/
#define SPI_MSB_FIRST						0
#define SPI_LSB_FIRST						1


//u8 (* SPI_CallBack)(u8 Copy_u8RecievedData)=0;

void SPI_voidInit(void);

/*Send one byte and receive one byte*/
u8 SPI_u8SendReceiveSynch(u8 Copy_u8Data);

void SPI_voidSendReceiveAsynch(u8 Copy_u8Data);

void SPI_voidTransmitArraySynch(u8* Copy_u8Ptr, u16 Copy_u16Length);

void SPI_voidPtrSendReceiveArraySynch(u8* Copy_u8PtrTransmitBuffer, u8* Copy_u8PtrReceiveBuffer,u16 Copy_u16Length);

/*Enable interrupt*/
void SPI_voidEnableInterrupt();

/*Disable interrupt*/
void SPI_voidDisableInterrupt();

/*Set callback for interrupt*/
void SPI_voidSetCallBack(void(*Copy_ptr)(u8 Copy_u8ReceivedData));

#endif /* SPI_INTERFACE_H_ */