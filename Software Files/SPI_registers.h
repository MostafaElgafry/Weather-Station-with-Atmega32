/*
*Author     : Group T9 communications Engineering
*Date       : 27 AUG 2021
*Version    : V01
*/



#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_

#define SPCR		(*(volatile u8*)(0x2D))
#define SPSR		(*(volatile u8*)(0x2E))
#define SPDR		(*(volatile u8*)(0x2F))


#endif /* SPI_REGISTERS_H_ */