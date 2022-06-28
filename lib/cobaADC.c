#include <stdio.h>
#include "adc.c"
#include "gpio.c"

double FCPU;
void ADC_init(); 
int ADC_read();
void ADC_convert();
void T0delay();
void delayms();

int main(void) {
	//inisialisasi
	FCPU = 1;	// 1MHz
	ADC_init(); // Setting ADC
	DDRD = 0xff; //port D full output semua
	while (1) {
	ADC_convert();
	}
	return (0);
}

void ADC_init(void) {
	ADMUX |= (1 << REFS0); //VRef menggunakan AVCC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1); //Ck/64, ADC Clock sebesar 125KHz
	ADCSRA |= (1 << ADEN); //enable ADC
}

int ADC_read(){
	int Ain,AinLow;
	
	ADMUX |= _BV(0);		/* set input channel to read */
	ADCSRA |= (1<<ADSC);		/* start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/*monitor end of conversion interrupt flag */
	
	AinLow = (int)ADCL;				/*read lower byte*/
	Ain = (int)ADCH*256;			/*read higher 2 bits, Multiply with weightage*/
	Ain = Ain + AinLow;				
	return Ain; 
}

void ADC_convert(){
	int ledValue;
	int adcValue;
	int i;
	
	adcValue = ADC_read(); //assign hasilnya ke adcValue
	ledValue = (adcValue >> 7);
	PORTD = 0; //mematikan semua LED
	for (i = 0; i <= ledValue; i++) {
	PORTD |= (1 << i); //menyalakan led sesuai ledValue
	}
	delayms(5);
}

#include "timer.c"



