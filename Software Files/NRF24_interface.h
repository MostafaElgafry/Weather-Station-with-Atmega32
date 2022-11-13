/*
*Author     : Group T9 communications Engineering
*Date       : 10 SEP 2021
*Version    : V01
*/

#ifndef NRF24_INTERFACE_H_
#define NRF24_INTERFACE_H_


typedef struct{
	u8 CEPinNumber;
	u8 CEPortID;
	u8 CSNPinNumber;
	u8 CSNPortID;
	u8 IRQPinNumber;
	u8 IRQPortNumber;
}NRF24_t;

/*Mode Options*/
#define NRF_MODE_TRANSMETTER						0
#define NRF_MODE_RECEIVER							1
//#define NRF_MODE_TRANSCEIVER						2

/*bitRate Options*/
#define NRF_BIT_RATE_1MBPS							0
#define NRF_BIT_RATE_2MBPS							1
#define NRF_BIT_RATE_250KBPS						4

/*Transmitter Power Options*/
#define NRF_POWER_N18DB								0
#define NRF_POWER_N12DB								1
#define NRF_POWER_N6DB								2
#define NRF_POWER_0DB								3

/*Transmission States*/
#define NRF_TRANS_STATE_SUCCEED						1
#define NRF_TRANS_STATE_MAX_RT						2

/*Enable or Disable*/
#define NRF_ENABLE									0
#define NRF_DISABLE									1

void HNRF24_voidInit(NRF24_t* N);

void HNRF24_voidConfigureRF(NRF24_t* N, u8 bitRate, u8 TransmitterPower);

void HNRF24_voidSetChannel(NRF24_t* N, u8 ChannelNumber);

u8 HNRF24_u8Listen(NRF24_t* N);

u8 HNRF24_u8IsPacketTransmitted(NRF24_t* N);

///
//void HNRF24_voidSetPrimaryPipe(NRF24_t* N, u8* Address, u8 DynamicLenEnable);

///
void HNRF24_voidSetReceive(NRF24_t* N, u8 PipeNum,  u8* Address, u8 DynamicLenEnable);

void HNRF24_voidDisableAutoAck(NRF24_t* N, u8 PipeNum);

void HNRF24_voidConfigureAutoRetransmission(NRF24_t* N, u8 RetryNumber, u8 AckDuration);

///
void HNRF24_voidDisablePipe(NRF24_t* N,u8 PipeNum);

u8 HNRF24_u8GetAvailableBytes(NRF24_t* N, u8 PipeNum);

void HNRF24_voidReadReceivedData(NRF24_t* N, u8* Buffer, u8 BuffLen);

u8 HNRF24_u8TransmitPacket(NRF24_t* N, u8* Address, u8* Packet, u8 PacketLen);

u8 HNRF24_u8ReceivePacket(NRF24_t* N, u8* Packet, u8* PacketLen, u8* ReceivePipeNum);

void HNRF24_voidPrintDetails(NRF24_t* N);

u8 HNRF24_u8ReadCarrier(NRF24_t*N);

void HNRF24_voidStartConstCarrier(NRF24_t*N, u8 ChannelNum);

void HNRF24_voidStopConstCarrier(NRF24_t*N, u8 ChannelNum);


#endif /* NRF24_INTERFACE_H_ */