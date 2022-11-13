/*
* Weather Station.c
* Author     : Group T9 communications Engineering
* Date       : 11 SEP 2021
* Version    : V01
*/
#include <string.h>
#include <stdio.h>
#include "CLOCK_interface.h"


/*******************LIBRARY LAYER*******************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*******************MCAL LAYER*******************************/
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"
#include "UART_interface.h"

/*******************HAL LAYER*******************************/
#include "LCD_interface.h"
#include "NRF24_interface.h"
#include "DHT22_interface.h"
#include "LDR_interface.h"
#include "WaterSensor_interface.h"
#include "Payload.h"

void TX_LED(void)
{
	DIO_voidSetPinDirection(5,PORTD,OUTPUT);
	DIO_voidSetPinValue(5,PORTD,HIGH);
	my_delay_ms(1000);
	DIO_voidSetPinValue(5,PORTD,LOW);	
}

int main(void)
{
    /*******************LCD initialization*******************************/
    DIO_voidSetPinDirection(6,PORTC,OUTPUT);  //LCD_RS
    DIO_voidSetPinDirection(5,PORTC,OUTPUT);  //LCD_RW
    DIO_voidSetPinDirection(4,PORTC,OUTPUT);  //LCD_E
	
    DIO_voidSetPinDirection(3,PORTC,OUTPUT);  //D4
    DIO_voidSetPinDirection(2,PORTC,OUTPUT);  //D5
    DIO_voidSetPinDirection(1,PORTC,OUTPUT);  //D6
    DIO_voidSetPinDirection(0,PORTC,OUTPUT);  //D7

    LCD_voidInit();
    LCD_voidClear();
    LCD_voidSetCursorPosition(0x00);
	
	/*******************ADC initialization*******************************/
	 ADC_voidInit();
	
	/*******************External interrupt2 initialization*******************************/
	 DIO_voidSetPinDirection(2,PORTB,INPUT_PULL_UP); //IRQ PIN
	 EXTI_voidEnableInterrupt(EXTI2);
	 EXTI2_voidSetCallBack(TX_LED); 
	/*******************NRF initialization*******************************/
	 DIO_voidSetPinDirection(3,PORTB,OUTPUT);  //CE
	 DIO_voidSetPinDirection(4,PORTB,OUTPUT);  //CSN
	 DIO_voidSetPinDirection(5,PORTB,OUTPUT);  //MOSI
	 DIO_voidSetPinDirection(6,PORTB,INPUT);  //MISO
	 DIO_voidSetPinDirection(7,PORTB,OUTPUT);  //SCK
	 
	 
	 DIO_voidSetPinValue(3,PORTB,LOW); //CE LOW
	 DIO_voidSetPinValue(4,PORTB,HIGH); //CSN HIGH 	
	 
	 NRF24_t N = {3,PORTB,4,PORTB,2,PORTB}; //NRF_PINS
		 
	 u8 Address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};  //Receiver Address
	 HNRF24_voidInit(&N);
	 HNRF24_voidConfigureRF(&N, 0, 0);
	 HNRF24_voidSetChannel(&N, 76); //set the receiver channel 
	 HNRF24_voidPrintDetails(&N);
	 
	 /*******************SPI initialization*******************************/
	 SPI_voidInit();
	 
	  /*******************UART initialization for Debugging*******************************/
	 UART_voidInit();
	 UART_voidSendStr("Uart Initiated\n");
	 
	
    while (1)
	{
		WaterSensor();
		LDR();
		DHT22();
		HNRF24_u8TransmitPacket(&N,Address,SensorsPayload,5);
		my_delay_ms(2000);
		LCD_voidClear();
    }
}

