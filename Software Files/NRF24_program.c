/*
*Author     : Group T9 communications Engineering
*Date       : 10 SEP 2021
*Version    : V01
*/

#define F_CPU			16000000UL

#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "UART_interface.h"


#include "NRF24_interface.h"
#include "NRF24_private.h"

void PNRF24_voidWritePayload(NRF24_t* N, u8* Payload, u8 PayloadLen){
	u8 i = 0;
	//u8 pkt[33];
	
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,LOW);
	SPI_u8SendReceiveSynch(NRF_COM_W_TX_PAYLOAD);
	while(i<PayloadLen){
		SPI_u8SendReceiveSynch(Payload[i++]);
	}
	SPI_u8SendReceiveSynch(0);
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,HIGH);
}

void PNRF24_voidReadPayload(NRF24_t*N, u8* Buffer ,u8 BuffLen){
	
}

void PNRF24_voidWriteCommand(NRF24_t* N, u8 Command,u8* Buffer, u8 BuffLen){
	
	u8 i = 0;
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,LOW);
	SPI_u8SendReceiveSynch(Command);
	while(i<BuffLen){
		Buffer[i] = SPI_u8SendReceiveSynch(0xff);
		i++;
	}
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,HIGH);
	
	
}

void PNRF24_voidFlipBuffer(u8* Buffer, u8 BuffLen){
	u8 i = 0;
	for (i = 0; i < BuffLen/2; i++){
		u8 Temp = Buffer[i];
		Buffer[i] = Buffer[BuffLen-i-1];
		Buffer[BuffLen-i-1] = Temp;
	}
}

void PNRF24_voidWriteRegister(NRF24_t* N, u8 Register, u8* Data, u8 DataLength){
	
	//UART_voidSendStr(UART0,"In Write Register Function\n");
	
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,LOW);
	SPI_u8SendReceiveSynch(NRF_COM_W_REGESTER|Register);
	u8 i = 0;
	while (i<DataLength){
		SPI_u8SendReceiveSynch(Data[i]);
		i++;
	}
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,HIGH);
}

void PNRF24_voidReadRegister(NRF24_t* N, u8 Register, u8* ReceivedData, u8 DataLength)
{
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,LOW);
	SPI_u8SendReceiveSynch(NRF_COM_R_REGESTER|Register);
	u8 i = 0;
	while (i<DataLength){
		ReceivedData[i] = SPI_u8SendReceiveSynch(0xff);
		i++;
	}
	DIO_voidSetPinValue(N->CSNPinNumber,N->CSNPortID,HIGH);
}

void HNRF24_voidInit(NRF24_t* N){
	
	
	u8 config = 0;
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,&config,1);
	char str[100];
	if(config > 127){
		sprintf(str,"config = %x\n",config);
		UART_voidSendStr(str);
		sprintf(str,"NRF Board Not Connected!!\nConfig = %X\n",config);
		UART_voidSendStr(str);
		while(1);
	}
	sprintf(str,"NRF Board Connected!!\n");
	UART_voidSendStr(str);
	
	//Set PWR_UP to 1, enable CRC by default
	//Entered Standby mode
	u8 RegValue = 0x0F;
	PNRF24_voidWriteRegister(N,NRF_REG_CONFIG,&RegValue,1);
	
	/*Set Address Width*/
	
	RegValue = 3;
	PNRF24_voidWriteRegister(N,NRF_REG_SETUP_AW,&RegValue,1);
	
	//set auto retransmission & duration by default
	RegValue = 0x0F;
	PNRF24_voidWriteRegister(N,NRF_REG_SETUP_RETR,&RegValue,1);	
	RegValue = 0x01;
	//FLUSH TX and RX
	PNRF24_voidWriteCommand(N,NRF_COM_FLUSH_TX,0,0);
	PNRF24_voidWriteCommand(N,NRF_COM_FLUSH_RX,0,0);
	
	RegValue = 0x3F;
	//enable Dynamic payload
	PNRF24_voidWriteRegister(N,NRF_REG_DYNPD,&RegValue,1);	
	
}

void HNRF24_voidConfigureRF(NRF24_t* N, u8 bitRate, u8 TransmitterPower){
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_RF_SETUP,&RegVal,1);
	RegVal &= 0xD1;
	RegVal |= (bitRate<<3)|(TransmitterPower<<1);
	PNRF24_voidWriteRegister(N,NRF_REG_RF_SETUP,&RegVal,1);
}

void HNRF24_voidSetChannel(NRF24_t* N, u8 ChannelNumber){
	u8 RegVal = ChannelNumber&0x7F;
	PNRF24_voidWriteRegister(N,NRF_REG_RF_CH,&RegVal,1);
}

u8 HNRF24_u8Listen(NRF24_t* N){
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_STATUS,&RegVal,1);
	return GET_BIT(RegVal,6);
}

u8 HNRF24_u8IsPacketTransmitted(NRF24_t* N){
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_STATUS,&RegVal,1);
	return GET_BIT(RegVal,5);
}

void HNRF24_voidSetPrimaryPipe(NRF24_t* N, u8* Address, u8 DynamicLenEnable){
	//Enable pipe
	u8 RegVal = 0;
	PNRF24_voidReadRegister(N,NRF_REG_EN_RXADDR,&RegVal,1);
	SET_BIT(RegVal,0);
	PNRF24_voidWriteRegister(N,NRF_REG_EN_RXADDR,&RegVal,1);
	
	//set Address
	PNRF24_voidWriteRegister(N,NRF_REG_RX_ADDR_P0,Address,5);
	
	//Set Tx address
	//PNRF24_voidWriteRegister(N,NRF_REG_TX_ADDR,Address,5);
	
	//Auto Ack on pipe
	PNRF24_voidReadRegister(N,NRF_REG_EN_AA,&RegVal,1);
	SET_BIT(RegVal,0);
	PNRF24_voidWriteRegister(N,NRF_REG_EN_AA,&RegVal,1);
	
	if (DynamicLenEnable == NRF_ENABLE){
		//Enable Dynamic Length in Feature Register
		PNRF24_voidReadRegister(N,NRF_REG_FEATURE,&RegVal,1);
		SET_BIT(RegVal,2);
		PNRF24_voidWriteRegister(N,NRF_REG_FEATURE,&RegVal,1);
		
		//Enable Dynamic length on pipe
		PNRF24_voidReadRegister(N,NRF_REG_DYNPD,&RegVal,1);
		SET_BIT(RegVal,0);
		PNRF24_voidWriteRegister(N,NRF_REG_DYNPD,&RegVal,1);
		
	}
	else{
		//fix receive length
		PNRF24_voidWriteRegister(N,NRF_REG_RX_PW_P0,&DynamicLenEnable,1);
	}
}

void HNRF24_voidSetSecondaryPipe(NRF24_t* N, u8 PipeNum,  u8* Address, u8 DynamicLenEnable){
	//Enable pipe
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_EN_RXADDR,&RegVal,1);
	SET_BIT(RegVal,PipeNum);
	PNRF24_voidWriteRegister(N,NRF_REG_EN_RXADDR,&RegVal,1);
	
	//Address
	PNRF24_voidWriteRegister(N,NRF_REG_RX_ADDR_P0+PipeNum,Address,5);
	
	
	//Auto Ack on pipe
	PNRF24_voidReadRegister(N,NRF_REG_EN_AA,&RegVal,1);
	SET_BIT(RegVal,PipeNum);
	PNRF24_voidWriteRegister(N,NRF_REG_EN_AA,&RegVal,1);
	
	if (DynamicLenEnable == NRF_ENABLE){
		//Enable Dynamic Length in Feature Register
		PNRF24_voidReadRegister(N,NRF_REG_FEATURE,&RegVal,1);
		SET_BIT(RegVal,2);
		PNRF24_voidWriteRegister(N,NRF_REG_FEATURE,&RegVal,1);
		
		//Enable Dynamic length on pipe
		PNRF24_voidReadRegister(N,NRF_REG_DYNPD,&RegVal,1);
		SET_BIT(RegVal,PipeNum);
		PNRF24_voidWriteRegister(N,NRF_REG_DYNPD,&RegVal,1);
		
	}
	else{
		//fix receive length
		PNRF24_voidWriteRegister(N,NRF_REG_RX_PW_P0+PipeNum,&DynamicLenEnable,1);
	}
}



void HNRF24_voidDisableAutoAck(NRF24_t* N, u8 PipeNum){
	u8 RegVal;
	//read Auto Ack Register
	PNRF24_voidReadRegister(N,NRF_REG_EN_AA,&RegVal,1);
	//disable Auto ack on pipe
	CLR_BIT(RegVal,PipeNum);
	//Write new value to Auto Ack Register
	PNRF24_voidWriteRegister(N,NRF_REG_EN_AA,&RegVal,1);
}

void HNRF24_voidConfigureAutoRetransmission(NRF24_t* N, u8 RetryNumber, u8 AckDuration){
	u8 RegVal = AckDuration<<4 | RetryNumber;
	PNRF24_voidWriteRegister(N,NRF_REG_SETUP_RETR,&RegVal,1);
}

void HNRF24_voidDisablePipe(NRF24_t* N,u8 PipeNum){
	u8 RegVal;
	//Read Enable Rx address register
	PNRF24_voidReadRegister(N,NRF_REG_EN_RXADDR,&RegVal,1);
	//Disable pipe 
	CLR_BIT(RegVal,PipeNum);
	//Write new value
	PNRF24_voidWriteRegister(N,NRF_REG_EN_RXADDR,&RegVal,1);
}

u8 HNRF24_u8GetAvailableBytes(NRF24_t* N, u8 PipeNum){
	if (PipeNum>5)
		return 0;
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_RX_PW_P0+PipeNum,&RegVal,1);
	return RegVal;
}

void HNRF24_voidReadReceivedData(NRF24_t* N, u8* Buffer, u8 BuffLen){
	
	PNRF24_voidWriteCommand(N,NRF_COM_R_RX_PAYLOAD,Buffer,BuffLen);
	
}

u8 HNRF24_u8TransmitPacket(NRF24_t* N, u8* Address, u8* Packet, u8 PacketLen){
	
	u8 RegVal;

	//	1- Set PRIM_RX to low in config register
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,&RegVal,1);
	CLR_BIT(RegVal,0);
	PNRF24_voidWriteRegister(N,NRF_REG_CONFIG,&RegVal,1);
	
	PNRF24_voidWriteCommand(N,NRF_COM_FLUSH_TX,0,0);
	u8 config = 0;
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,&config,1);
	if(GET_BIT(config,0))
		UART_voidSendStr("Mode Set to RX\n");
	else
		UART_voidSendStr("Mode Set to TX\n");
	
	//	2- Write Address
	PNRF24_voidWriteRegister(N,NRF_REG_TX_ADDR,Address,5);
	u8 Buffer[5];
	PNRF24_voidReadRegister(N,NRF_REG_TX_ADDR,Buffer,5);
	
	//char str[100];
	/*sprintf(str,"TX address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(UART0,str);
	
	PNRF24_voidWriteRegister(N,NRF_REG_RX_ADDR_P0,Address,5);
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P0,Buffer,5);
	
	sprintf(str,"RX address P0	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(UART0,str);
	*/
	u8 FStatus = 0;
	PNRF24_voidReadRegister(N,NRF_REG_FIFO_STATUS,&FStatus,1);
	char *v = GET_BIT(FStatus,4)?	"Empty":"Not Empty";
	char str[500];
	sprintf(str,"Tx Fifo Status: %s\n",v);
	UART_voidSendStr(str);
	UART_voidSendStr("Writing to Tx Fifo...\n");
	//	3- Write Data onto TX FIFO
	PNRF24_voidWritePayload(N,Packet,PacketLen);
	
	FStatus = 0;
	PNRF24_voidReadRegister(N,NRF_REG_FIFO_STATUS,&FStatus,1);
	v = GET_BIT(FStatus,4)?	"Empty":"Not Empty";
	sprintf(str,"Tx Fifo Status After Writing: %s\n",v);
	UART_voidSendStr(str);
	//	4- Configure pipe0 for auto Ack
	//HNRF24_voidPrintDetails(N);
	UART_voidSendStr("****Before Pipe 0 Address\n****n");
	//HNRF24_voidSetPrimaryPipe(N,Address,NRF_ENABLE);
	//	5- pulse CE pin for more than 10 us
	DIO_voidSetPinValue(N->CEPinNumber,N->CEPortID,HIGH);
	_delay_us(15);
	DIO_voidSetPinValue(N->CEPinNumber,N->CEPortID,LOW);
	//	6- Read Status Register
	//HNRF24_voidPrintDetails(N);
	while (1){
		u8 FifoStatus = 0;
		PNRF24_voidReadRegister(N,NRF_REG_FIFO_STATUS,&FifoStatus,1);
		PNRF24_voidReadRegister(N,NRF_REG_STATUS,&RegVal,1);
		sprintf(str,"In Function: Status = %X\nIn Function Fifo Status = %X\n",RegVal,FifoStatus);
		UART_voidSendStr(str);
		_delay_ms(100);
		if (GET_BIT(RegVal,5)){	//Transmission success with ACK
			//Clear all interrupts Interrupt
			RegVal |= 0x70;
			PNRF24_voidWriteRegister(N,NRF_REG_STATUS,&RegVal,1);
			UART_voidSendStr("Transmission SUCCEEDED With ACK Received!!\n");
			return NRF_TRANS_STATE_SUCCEED;
		}
		if(GET_BIT(FifoStatus,4)){	//Transmission Succeeded With no ACK
			UART_voidSendStr("Transmission SUCCEEDED With No ACK !!\n");
			return NRF_TRANS_STATE_SUCCEED;
		}
		if (GET_BIT(RegVal,4)){	//Max retransmission exceeded
			RegVal |= 0x70;
			PNRF24_voidWriteRegister(N,NRF_REG_STATUS,&RegVal,1);
			UART_voidSendStr("Max Retransmission Reached!!\n");
			return NRF_TRANS_STATE_MAX_RT;
		}
		if(GET_BIT(RegVal,0)){	//TX Fifo Full
			PNRF24_voidWriteCommand(N,NRF_COM_FLUSH_TX,0,0);
			UART_voidSendStr("TX Fifo Full\n");
			return 10;
		}
		//u8 config = 0;
		//PNRF24_void
	}
}

u8 HNRF24_u8ReceivePacket(NRF24_t* N, u8* Packet, u8* PacketLen, u8* ReceivePipeNum){
	
	u8 RegVal;
	//Dynamic Packet Length enable on all pipes
	
	
	//	1- Set PRIM_RX in CONFIG register
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,&RegVal,1);
	SET_BIT(RegVal,0);
	PNRF24_voidWriteRegister(N,NRF_REG_CONFIG,&RegVal,1);
	

	
	
	
	
	//	2- Set CE
	DIO_voidSetPinValue(N->CEPinNumber,N->CEPortID,HIGH);
	
	while(1){
		PNRF24_voidReadRegister(N,NRF_REG_STATUS,&RegVal,1);
		
		if (GET_BIT(RegVal,6)){//Data Received Successfully
			*ReceivePipeNum = (RegVal>>1) & 7;
			
			//	3- Clear CE
			DIO_voidSetPinValue(N->CEPinNumber,N->CEPortID,LOW);
			
			//	4- Read Received Data Len
			PNRF24_voidWriteCommand(N,NRF_COM_R_RX_PL_LENGTH,PacketLen,1);
			
			//	5- Read Packet
			PNRF24_voidWriteCommand(N,NRF_COM_R_RX_PAYLOAD,Packet,*PacketLen);
			
			return 1;
		}
		HNRF24_voidPrintDetails(N);
		_delay_ms(3000);
	}
}


void HNRF24_voidPrintDetails(NRF24_t* N){
	u8 Status;
	u8 Buffer[5];
	char str[50];
	
	//Channel
	PNRF24_voidReadRegister(N,NRF_REG_RF_CH,Buffer,1);
	sprintf(str,"Channel		=	%u\n",Buffer[0]);
	UART_voidSendStr(str);
	
	//DataRate
	PNRF24_voidReadRegister(N,NRF_REG_RF_SETUP,Buffer,1);
	sprintf(str,"Data Rate		=	");
	if (GET_BIT(Buffer[0],5))
		strcat(str,"250 KbPS\n");
	else if (GET_BIT(Buffer[0],3))
		strcat(str,"2 MbPS\n");
	else
		strcat(str,"1 MbPS\n");
	UART_voidSendStr(str);
	
	//Power Amp level
	sprintf(str,"Power Amp Level		=	");
	if((Buffer[0] & 6) == 0)
		strcat(str,"-18 dBm\n");
	else if((Buffer[0] & 6) == 1)
		strcat(str,"-12 dBm\n");
	else if((Buffer[0] & 6) == 2)
		strcat(str,"-6 dBm\n");
	else
		strcat(str,"0 dBm\n");
	UART_voidSendStr(str);
	
		
	//CRC length
	PNRF24_voidReadRegister(N,NRF_REG_STATUS,&Status,1);
	sprintf(str,"CRC Length		=	");
	if ((Status & 4) == 0)
		strcat(str,"8 Bits\n");
	else
		strcat(str,"16 Bits\n");
	UART_voidSendStr(str);
	
	
	//Address Length
	PNRF24_voidReadRegister(N,NRF_REG_SETUP_AW,&Status,1);
	sprintf(str,"Address Width		=	");
	if ((Status & 3) == 1)
		strcat(str,"3 Bytes\n");
	else if ((Status & 3) == 2)
		strcat(str,"4 Bytes\n");
	else 
		strcat(str,"5 Bytes\n");
	UART_voidSendStr(str);
	
	//Auto Retry delay
	PNRF24_voidReadRegister(N,NRF_REG_SETUP_RETR,Buffer,1);
	u16 D = ((Buffer[0]>>4)+1) * 250;
	sprintf(str,"Auto Retry Delay	=	%d\n",D);
	UART_voidSendStr(str);
	
	
	//Auto Retry Count
	sprintf(str,"Auto Retry Count	=	%d\n",Buffer[0]&15);
	UART_voidSendStr(str);
	
	//Dynamic Payloads
	PNRF24_voidReadRegister(N,NRF_REG_FEATURE,Buffer,1);
	sprintf(str,"Dynamic Payloads	=	");
	if(GET_BIT(Buffer[0],2))
		strcat(str,"Enabled\n");
	else 
		strcat(str,"Disabled\n");
	UART_voidSendStr(str);
	
	//Auto Ack
	PNRF24_voidReadRegister(N,NRF_REG_EN_AA,Buffer,1);
	sprintf(str,"Auto Ack	=	");
	if((Buffer[0] & 0x3f) > 0)
		strcat(str,"Enabled\n");
	else
		strcat(str,"Disabled\n");
	UART_voidSendStr(str);
	
	//TX Address
	PNRF24_voidReadRegister(N,NRF_REG_TX_ADDR,Buffer,5);
	sprintf(str,"TX address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	
	//Pipe0 Address
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P0,Buffer,5);
	sprintf(str,"Pipe 0 address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	//Pipe1 Address
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P1,Buffer,5);
	sprintf(str,"Pipe 1 address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	//Pipe2 Address
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P2,Buffer,5);
	sprintf(str,"Pipe 2 address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	//Pipe3 Address
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P3,Buffer,5);
	sprintf(str,"Pipe 3 address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	//Pipe4 Address
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P4,Buffer,5);
	sprintf(str,"Pipe 4 address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	//Pipe5 Address
	PNRF24_voidReadRegister(N,NRF_REG_RX_ADDR_P5,Buffer,5);
	sprintf(str,"Pipe 5 address	=	%X%X%X%X%X%X%X%X%X%X\n",Buffer[0]>>4,Buffer[0]&0xf,Buffer[1]>>4,Buffer[1]&0xf,Buffer[2]>>4,Buffer[2]&0xf,Buffer[3]>>4,Buffer[3]&0xf,Buffer[4]>>4,Buffer[4]&0xf);
	UART_voidSendStr(str);
	
	//Primary Mode
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,Buffer,1);
	if(GET_BIT(Buffer[0],0) == 1)
	UART_voidSendStr("Primary Mode Receiver\n");
	else
	UART_voidSendStr("Primary Mode Transmitter\n");
	
	//Enabled Pipes
	PNRF24_voidReadRegister(N,NRF_REG_EN_AA,Buffer,1);
	UART_voidSendStr("Enabled Pipes:	");
	UART_voidSendNumber(Buffer[0]);
	UART_voidSendChar('\n');
	
	//Enabled Rx Addresses
	PNRF24_voidReadRegister(N,NRF_REG_EN_RXADDR,Buffer,1);
	UART_voidSendStr("Enabled Rx Address:	");
	UART_voidSendNumber(Buffer[0]);
	UART_voidSendChar('\n');
	
	//TX FIFO status
	PNRF24_voidReadRegister(N,NRF_REG_FIFO_STATUS,Buffer,1);
	UART_voidSendStr("Tx FIFO		=	");
	if(GET_BIT(Buffer[0],5))
		UART_voidSendStr("FULL\n");
	else
		UART_voidSendStr("EMPTY\n");
	
	//Rx FIFO Status
	UART_voidSendStr("Rx FIFO		=	");
	if(GET_BIT(Buffer[0],1))
	UART_voidSendStr("FULL\n");
	else
	UART_voidSendStr("EMPTY\n");
	
	
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,Buffer,1);
	sprintf(str,"PWR_UP = %u\n",GET_BIT(Buffer[0],1));
	UART_voidSendStr(str);
	
	UART_voidSendStr("CE Pin State		=	");
	if(DIO_u8GetPinValue(N->CEPinNumber,N->CEPortID))
		UART_voidSendStr("HIGH\n");
	else
		UART_voidSendStr("LOW\n");
	
}

u8 HNRF24_u8ReadCarrier(NRF24_t*N){
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_RPD,&RegVal,1);
	return GET_BIT(RegVal,0);
}

void HNRF24_voidStartConstCarrier(NRF24_t*N, u8 ChannelNum){
	u8 RegVal;
	PNRF24_voidReadRegister(N,NRF_REG_CONFIG,&RegVal,1);
	SET_BIT(RegVal,1);
	CLR_BIT(RegVal,0);
	PNRF24_voidWriteRegister(N,NRF_REG_CONFIG,&RegVal,1);
	
	_delay_ms(5);
	
	PNRF24_voidReadRegister(N,NRF_REG_RF_SETUP,&RegVal,1);
	RegVal |= (1<<7)|(1<<4)|(3<<1);
	PNRF24_voidWriteRegister(N,NRF_REG_RF_SETUP,&RegVal,1);
	
	PNRF24_voidWriteRegister(N,NRF_REG_RF_CH,&ChannelNum,1);
	
	DIO_voidSetPinValue(N->CEPinNumber,N->CEPortID,HIGH);
}

void HNRF24_voidStopConstCarrier(NRF24_t*N, u8 ChannelNum){
	
	DIO_voidSetPinValue(N->CEPinNumber,N->CEPortID,LOW);
	
	u8 RegVal;
	//PNRF24_voidReadRegister(N,NRF_REG_CONFIG,&RegVal,1);
	//SET_BIT(RegVal,1);
	//CLR_BIT(RegVal,0);
	//PNRF24_voidWriteRegister(N,NRF_REG_CONFIG,&RegVal,1);
	
	_delay_ms(5);
	
	PNRF24_voidReadRegister(N,NRF_REG_RF_SETUP,&RegVal,1);
	RegVal &= ~((1<<7)|(1<<4)|(3<<1));
	PNRF24_voidWriteRegister(N,NRF_REG_RF_SETUP,&RegVal,1);
	
	//PNRF24_voidWriteRegister(N,NRF_REG_RF_CH,&ChannelNum,1);
	
}