#include <stdio.h>
#include "gpio.c"

double FCPU;
void I2C_Slave_Init(uint8_t slave_address);
int8_t I2C_Slave_Listen();
char decimal_to_bcd(unsigned char value);
char I2C_Read_Ack()	;

int main(){
	FCPU = 8;				//Frekuensi 8MHz
	DDRA = 0xff;			//Set DDRA sebagai output
	PORTA = 0x00;			//set pull-up resistor
	char a;					
	I2C_Slave_Init(0xA0);	//set addres slave
	
	while(1)
	{
		I2C_Slave_Listen();	//set posisi listen 
		a = I2C_Read_Ack();	//baca data lalu masukkan ke a
		
		PORTA = decimal_to_bcd(a);	//PORTA bcd dari a
	}

}

#include "I2C.c"

