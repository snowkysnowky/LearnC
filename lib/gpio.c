#define __OFFSET 0x20 //memory mapped address - i/o address, eg. PORTA $1B ($3B), then 3B-1B = 20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _MMIO_2BYTE(mem_addr) (*(volatile uint16_t *)(mem_addr))
#define ACCES_REGISTER_ADDRESS(io_addr) _MMIO_BYTE((io_addr) + __OFFSET)
#define ACCES_REGISTER_ADDRESS2BYTE(io_addr) _MMIO_2BYTE((io_addr) + __OFFSET)

//Akses PORTA 
#define PORTA  ACCES_REGISTER_ADDRESS(0x1B)
#define DDRA   ACCES_REGISTER_ADDRESS(0x1A)
#define PINA   ACCES_REGISTER_ADDRESS(0x19)
enum{PINA0, PINA1, PINA2, PINA3, PINA4, PINA5, PINA6, PINA7};
enum{PORTA0, PORTA1, PORTA2, PORTA3, PORTA4, PORTA5, PORTA6, PORTA7};

//akses PORTB
#define PORTB ACCES_REGISTER_ADDRESS(0x18)
#define DDRB  ACCES_REGISTER_ADDRESS(0x17)
#define PINB ACCES_REGISTER_ADDRESS(0x16)
enum{PINB0, PINB1, PINB2, PINB3, PINB4, PINB5, PINB6, PINB7};
enum{PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5, PORTB6, PORTB7};

//akses PORTC
#define PORTC ACCES_REGISTER_ADDRESS(0x15)
#define DDRC ACCES_REGISTER_ADDRESS(0x14)
#define PINC ACCES_REGISTER_ADDRESS(0x10)
enum{PINC0, PINC1, PINC2, PINC3, PINC4, PINC5, PINC6, PINC7};
enum{PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5, PORTC6, PORTC7};

//akses PORTD
#define PORTD ACCES_REGISTER_ADDRESS(0x12)
#define DDRD ACCES_REGISTER_ADDRESS(0x11)
#define PIND ACCES_REGISTER_ADDRESS(0x10)
enum{PIND0, PIND1, PIND2, PIND3, PIND4, PIND5, PIND6, PIND7};
enum{PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6, PORTD7};


//Bitwise macro
#define _BV(nbit)  (1 << (nbit))
#define bit_is_set(byte, nbit)   ((byte) & _BV(nbit))
#define bit_is_clear(byte, nbit)   (!((byte) & _BV(nbit)))
#define bitset(byte,nbit)   ((byte) |=  (_BV(nbit)))
#define bitclear(byte,nbit) ((byte) &= ~(_BV(nbit)))
#define bitflip(byte,nbit)  ((byte) ^=  (_BV(nbit)))
#define bitcheck(byte,nbit) ((byte) &   (_BV(nbit)))

