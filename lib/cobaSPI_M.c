#include <stdio.h>
#include "gpio.c"

double FCPU;
void SPI_Master_Init();
void SPI_Write(char data);
void SS_ENABLE();
void delayms();
char decimal_to_bcd(unsigned char value);
unsigned char SPI_Tranceiver (unsigned char data);


int main()
{
	FCPU = 8;
	SPI_Master_Init();
	char a = 0;		
	char data;	
	DDRD = 0x00;
	DDRC = 0xff;		//Set DDRA sebagai Input
	PORTD = 0x03;		//Set PA0 dan PA1 pull-up resistor
	SS_ENABLE();
	
	
	while(1)
	{
		if(bit_is_clear(PIND,PIND0))	//button 1 ditekan
		{
			a = a + 1;					
			if(a == 100)				//a = 100 maka a dikebalikan menjadi 0
			{
				a = 0;
			}
			
			data = SPI_Tranceiver(a);
			
			PORTC = decimal_to_bcd(data);
			delayms(1000);
		}
		if (a > 0){
			if(bit_is_clear(PIND,PIND1))	//button 2 ditekan
			{
				a = a - 1;
			
			data = SPI_Tranceiver(a);
			PORTC = decimal_to_bcd(data);
				delayms(1000);
			}
		}
	}
	
}
#include "timer.c"
#include "SPI.c"
#include "I2C.c"
