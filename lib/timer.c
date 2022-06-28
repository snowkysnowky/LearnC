double FCPU;

//TIMER0
/* Timer 0 */
#define TCNT0   ACCES_REGISTER_ADDRESS(0x32)
#define TCCR0   ACCES_REGISTER_ADDRESS(0x33)
enum{CS00, CS01, CS02, WGM01, COM00, COM01, WGM00, FOC0};

#define TIFR    ACCES_REGISTER_ADDRESS(0x38)
enum{TOV0, OCF0, TOV1, OCF1B, OCF1A, ICF1, TOV2, OCF2}; 

void Timer0delay() //Timer0, for 1MHz clock, time = i/fcpu = 1 microsecond
{
	TCNT0 = 0;  			// Load TCNT0 with initial value = 0;
	TCCR0 = 1 << CS00;  	// start Timer0, 00000001==> FOC0 = 0, WGM00 = 0 (Normal), COM01 = 0, COM00 = 0, WGM01 = 0 (Normal), CS02 = 0, CS01 = 0, CS00 = 1 (no pre-scalar)
	
	while(TIFR==0X01);  // TIFR = 00000001 ==> if TOV0 = 1 (Timer0 has overflow/going from 0xFF to 0x00), do nothing. (or,Wait for TOV0 to roll over)
	TCCR0 = 0; //stop Timer0 temporarily
	TIFR = 0x01;  // Clear TOV0 flag
}

void delayms(uint16_t deltime){
	uint16_t i = 0;
	
	double cputime_1micro;
	uint16_t cputimeMili;

	cputime_1micro = (float)(FCPU); //in microsecond
	cputimeMili = (uint16_t)(8000*cputime_1micro);
	
	while(i<deltime*cputimeMili){
		i++;
		Timer0delay();
	}
}
