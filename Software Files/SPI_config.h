/*
*Author     : Group T9 communications Engineering
*Date       : 27 AUG 2021
*Version    : V01
*/


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_
/*Select Mode For the SPI:
	(a) SPI_MASTER_MODE
	(b) SPI_SLAVE_MODE	*/	
#define SPI_MODE					SPI_MASTER_MODE

/*Select SPI prescalar:
	SPI_DEV_4	
	SPI_DEV_16	
	SPI_DEV_64	
	SPI_DEV_128	*/

#define SPI_PRESCALAR				SPI_DEV_4


/*Options:
	SPI_ENABLE
	SPI_DISABLE	*/
#define SPI_DOUBLE_SPEED			SPI_DISABLE

/*Options:
	SPI_IDLE_LOW
	SPI_IDLE_HIGH	*/
#define SPI_CLOCK_POLARITY			SPI_IDLE_LOW

/*Options:
	SPI_SAMPLE_ON_FALLING_EDGE
	SPI_SAMPLE_ON_RISING_EDGE	*/
#define SPI_CLOCK_PHASE				SPI_SAMPLE_ON_RISING_EDGE

/*Options:
	SPI_ENABLE
	SPI_DISABLE	*/
#define SPI_INTERRUPT				SPI_DISABLE

/*Options:
	SPI_MSB_FIRST
    SPI_LSB_FIRST	*/
#define SPI_DATA_ORDER				SPI_MSB_FIRST





#endif /* SPI_CONFIG_H_ */