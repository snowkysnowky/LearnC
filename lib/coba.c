//register for atmega16
#include <stdio.h>
#include "gpio.c"

double FCPU;
void T0delay();
void delayms();

//========Main Program=============
int main(void){
	FCPU = 1; //in MHz
	DDRA = (_BV(0)); //give initial value 1 to DDRA bit0, configure as output
	DDRA |= (_BV(7)); //give value 1 to DDRA bit7, without destructing previous value of DDRA, configure as output
	
    for(;;) //do infinite loop
    {
        PORTA ^= (_BV(0)); //give value 1 to bit0, toggles the state of that pin every 5 ms (if previous value is 1, then next value is 0 and so on)
        delayms(1000);
    }
	
	return 0;
}
//========End of Main Program=============

#include "timer.c"

//compile : avr-gcc -o coba.elf coba.c

