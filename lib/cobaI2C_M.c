#include <stdio.h>
#include "gpio.c"

double FCPU;
void I2C_Init();
uint8_t I2C_Start(char write_address);
uint8_t I2C_Write(char data);
void I2C_Stop();
void delayms();
void Timer0delay();

int main(){
	FCPU = 8;			//Frekuensi 8Mhz
	int a = 0;			
	DDRA = 0x00;		//Set DDRA sebagai Input
	PORTA = 0x03;		//Set PA0 dan PA1 pull-up resistor
	I2C_Init();			//set I2C kondisi start
	I2C_Start(0xA0);	//set addres slave	

	while(1)
	{
		if(bit_is_clear(PINA,PINA0))	//button 1 ditekan
		{
			a = a + 1;					
			if(a == 100)				//a = 100 maka a dikebalikan menjadi 0
			{
				a = 0;
			}
			I2C_Write(a);				//kirim data a ke slave
			I2C_Stop();					//selesai kirim data
			I2C_Start(0xA0);			//set addres slave
			
			delayms(1000);
		}
		if (a > 0){
			if(bit_is_clear(PINA,PINA1))	//button 2 ditekan
			{
				a = a - 1;
				I2C_Write(a);			//kirim data ke slave
				I2C_Stop();				//selesai kirim data
				I2C_Start(0xA0);			//set addres slave
				
				delayms(1000);
			}
		}
	}
}

#include "timer.c"
#include "I2C.c"
