#define SPCR ACCES_REGISTER_ADDRESS(0x0D)
enum{SPR0, SPR1, CPHA, CPOL, MSTR, DORD, SPE, SPIE};

#define SPSR ACCES_REGISTER_ADDRESS(0x0E)
enum{SPI2X, WCOL = 6, SPIF};

#define SPDR ACCES_REGISTER_ADDRESS(0x0F)

#define SS PORTB4
#define MOSI PORTB5
#define	MISO PORTB6
#define	SCK PORTB7

void SS_ENABLE ()
{
	PORTB &= ~(_BV(SS));
}

void SS_DISABLE () 
{
	PORTB |= _BV(SS);
}

void SPI_Master_Init()					/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	/* Make MOSI, SCK, SS 
						as Output pin */
	DDRB &= ~(1<<MISO);			/* Make MISO pin 
						as input pin */
	PORTB |= (1<<SS);			/* Make high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI in master mode
						with Fosc/16 */
	SPSR &= ~(1<<SPI2X);			/* Disable speed doubler */
}

void SPI_Write(char data)		/* SPI write data function */
{
	char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}


void SPI_Slave_Init()					/* SPI Initialize function */
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));  /* Make MOSI, SCK, SS as
 						input pins */
	DDRB |= (1<<MISO);			/* Make MISO pin as 
						output pin */
	SPCR = (1<<SPE);			/* Enable SPI in slave mode */
}

char SPI_Slave_Receive()			/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

//Function to send and receive data
unsigned char SPI_Tranceiver (unsigned char data)
{
    SPDR = data;                                  //Load data into buffer
    while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
    return(SPDR);                                 //Return received data
}
