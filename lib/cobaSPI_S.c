
#include <stdio.h>
#include "gpio.c"


void SPI_Slave_Init();
char decimal_to_bcd(unsigned char value);
char SPI_Slave_Receive();
unsigned char SPI_Tranceiver (unsigned char data);

int main(){
	DDRC = 0xff;			//Set DDRC sebagai output
	PORTC = 0x00;			//set pull-up resistor
	SPI_Slave_Init();
	char a, b = 0;					
	
	while(1)
	{
			if(b == 100)				//b = 100 maka a dikebalikan menjadi 0
			{
				b = 0;
			}
			
		a = SPI_Tranceiver(++b);	//baca data lalu dan kirim data
	
		PORTC = decimal_to_bcd(a);	//PORTC bcd dari a
	}

}

#include "SPI.c"
#include "I2C.c"

