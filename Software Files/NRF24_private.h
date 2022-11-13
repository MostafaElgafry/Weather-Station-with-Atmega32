/*
*Author     : Group T9 communications Engineering
*Date       : 10 SEP 2021
*Version    : V01
*/

#ifndef NRF24_PRIVATE_H_
#define NRF24_PRIVATE_H_


/*** NRF Commands ***/
#define NRF_COM_R_REGESTER				0x00
#define NRF_COM_W_REGESTER				0x20

#define NRF_COM_R_RX_PAYLOAD			0x61
#define NRF_COM_W_TX_PAYLOAD			0xA0

#define NRF_COM_FLUSH_TX				0xE1
#define NRF_COM_FLUSH_RX				0xE2

#define NRF_COM_R_RX_PL_LENGTH			0x60

#define NRF_COM_W_ACK_PAYLOAD			0xA8

#define NRF_COM_W_TX_PYALOAD_NACK		0xB0

#define NRF_COM_NOP						0xFF


/*** NRF Regesters ***/

#define NRF_REG_CONFIG					0x00
#define NRF_REG_EN_AA					0x01
#define NRF_REG_EN_RXADDR				0x02
#define NRF_REG_SETUP_AW				0x03
#define NRF_REG_SETUP_RETR				0x04
#define NRF_REG_RF_CH					0x05
#define NRF_REG_RF_SETUP				0x06
#define NRF_REG_STATUS					0x07
#define NRF_REG_OBSERVE_TX				0x08
#define NRF_REG_RPD						0x09
#define NRF_REG_RX_ADDR_P0				0x0A
#define NRF_REG_RX_ADDR_P1				0x0B
#define NRF_REG_RX_ADDR_P2				0x0C
#define NRF_REG_RX_ADDR_P3				0x0D
#define NRF_REG_RX_ADDR_P4				0x0E
#define NRF_REG_RX_ADDR_P5				0x0F
#define NRF_REG_TX_ADDR					0x10
#define NRF_REG_RX_PW_P0				0x11
#define NRF_REG_RX_PW_P1				0x12
#define NRF_REG_RX_PW_P2				0x13
#define NRF_REG_RX_PW_P3				0x14
#define NRF_REG_RX_PW_P4				0x15
#define NRF_REG_RX_PW_P5				0x16
#define NRF_REG_FIFO_STATUS				0x17
#define NRF_REG_DYNPD					0x1C
#define NRF_REG_FEATURE					0x1D




/*** Private Functions ***/
void PNRF24_voidWritePayload(NRF24_t* N, u8* Payload, u8 PayloadLen);

void PNRF24_voidWriteCommand(NRF24_t* N, u8 Command,u8* Buffer, u8 BuffLen);

void PNRF24_voidFlipBuffer(u8* Buffer, u8 BuffLen);

void PNRF24_voidWriteRegister(NRF24_t* N, u8 Register, u8* Data, u8 DataLength);

void PNRF24_voidReadRegister(NRF24_t* N, u8 Register, u8* ReceivedData, u8 DataLength);


#endif /* NRF24_PRIVATE_H_ */