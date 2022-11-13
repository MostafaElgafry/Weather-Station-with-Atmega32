/*
*Author     : Group T9 communications Engineering
*Date       : 3 SEP 2021
*Version    : V01
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include <stdio.h>

#include "DIO_interface.h"

#include "DHT22_interface.h"
#include "DHT22_config.h"
#include "CLOCK_interface.h"
#include "LCD_interface.h"

#include "Payload.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "util/delay.h"

int ExtractTemperature(u8 Data2, u8 Data3);
int ExtractHumidity(u8 Data0, u8 Data1);
void DHT_ReadRaw(u8 Data[]);

void DHT_voidRead(int *Temperature, int *Humidity)
{
	u8 data[4] = { 0, 0, 0, 0 };
	
	//Read data
	DHT_ReadRaw(data);
	

	//Calculate values

	*Temperature = ExtractTemperature( data[2], data[3]);
	SensorsPayload[2] = *Temperature; 
	*Humidity = ExtractHumidity(data[0], data[1]);
	SensorsPayload[3] = *Humidity; 

}
void DHT22()
{
	int Temperature;
	int Humidity;
	DHT_voidRead(&Temperature , &Humidity);
	char value[20];
	sprintf(value, "T = %d", Temperature);
	LCD_voidSetCursorPosition(0x00);
	LCD_voidSendString(value);
	sprintf(value, "H = %d", Humidity);
	LCD_voidSetCursorPosition(0x40);
	LCD_voidSendString(value);
}
void DHT_ReadRaw(u8 Data[4])
{
	u8 buffer[5] = {0, 0, 0, 0, 0};
	int retries, i;
	int j;
	retries = i = j = 0;

	//----- Step 1 - Start communication -----
	
		//Request data
		DIO_voidSetPinDirection(DHT_SDA,OUTPUT);
		DIO_voidSetPinValue(DHT_SDA,LOW);	//DHT_PIN = 0

		_delay_us(900);

		//Setup DHT_PIN as input with pull-up resistor so as to read data
		DIO_voidSetPinValue(DHT_SDA,HIGH);	//DHT_PIN = 1 (Pull-up resistor)
		DIO_voidSetPinDirection(DHT_SDA,INPUT); //DHT_PIN = Input

		//Wait for response for 20-40us
		retries = 0;
		
		while (DIO_u8GetPinValue(DHT_SDA))
		{
			_delay_us(2);
			retries += 2;
			if (retries > 60)
			{
				
				//Timeout error
				break;
			}
		}
	
	//----------------------------------------

	//----- Step 2 - Wait for response -----


		//Response sequence began
		//Wait for the first response to finish (low for ~80us)
		retries = 0;
		while (!DIO_u8GetPinValue(DHT_SDA))
		{
			_delay_us(2);
			retries += 2;
			if (retries > 100)
			{
				//Timeout error
				break;
			}
		}
		//Wait for the last response to finish (high for ~80us)
		retries = 0;
		while(DIO_u8GetPinValue(DHT_SDA))
		{
			_delay_us(2);
			retries += 2;
			if (retries > 100)
			{
				//Timeout error
				break;
			}
		}

	//--------------------------------------

	//----- Step 3 - Data transmission -----
		//Reading 5 bytes, bit by bit
		for (i = 0 ; i < 5 ; i++)
		{
			//LCD_voidSendString("4");
			for (j = 7 ; j >= 0 ; j--)
			{
				//There is always a leading low level of 50 us
				retries = 0;
				while(!DIO_u8GetPinValue(DHT_SDA))
				{
					_delay_us(2);
					retries += 2;
					if (retries > 70)
					{
						//Timeout error
						j = -1;								//Break inner for-loop
						i = 5;								//Break outer for-loop
						break;								//Break while loop
						
					}
				}
				
				//We read data bit || 26-28us means '0' || 70us means '1'
				_delay_us(35);							//Wait for more than 28us
				if (DIO_u8GetPinValue(DHT_SDA))				//If HIGH
				SET_BIT(buffer[i], j);				//bit = '1'

				retries = 0;
				while(DIO_u8GetPinValue(DHT_SDA))
				{
					_delay_us(2);
					retries += 2;
					if (retries > 100)
					{
						//Timeout error
						break;
						
					}
					
				}
			
			}

		}
		//--------------------------------------
		

		//----- Step 4 - Check checksum and return data -----
		if (((u8)(buffer[0] + buffer[1] + buffer[2] + buffer[3])) != buffer[4])
		{
				//Checksum error
		}
		else
		{
			//Build returning array
			//data[0] = Humidity		(int)
			//data[1] = Humidity		(dec)
			//data[2] = Temperature		(int)
			//data[3] = Temperature		(dec)
			//data[4] = Checksum
			for (i = 0 ; i < 4 ; i++)
			Data[i] = buffer[i];
		}
}
	//---------------------------------------------------

	
int ExtractTemperature(u8 Data2, u8 Data3)
{
	double temp = 0.0;
	//(Integral<<8 + Decimal) / 10
	temp = (GET_BIT(Data2, 7) ? ((((Data2 & 0x7F) << 8) | Data3) / (-10.0)) : (((Data2 << 8) | Data3) / 10.0));

	return temp;
}

int ExtractHumidity(u8 Data0, u8 Data1)
{
	double hum = 0.0;
	
	//(Integral<<8 + Decimal) / 10
	hum = ((Data0<<8) | Data1) / 10.0;

	return hum;
}
