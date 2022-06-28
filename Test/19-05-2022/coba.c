//register for atmega16
#include "gpio.c"

//========Main Program=============
int main(void){
	
	DDRA |= (_BV(PINA0)); //give initial value 1 to DDRA bit0, configure as output
	DDRB = 0x00;
	PORTB |= (1 << PINB0);
	while(1){
	if(bit_is_clear(PINB,PINB0)){
	PORTA = (1 << (bit0));
	}else {
		PORTA = 0x00;
	}
}
	
    
	
	return 0;
}
//========End of Main Program=============



//compile : avr-gcc -o tes.elf tes.c

