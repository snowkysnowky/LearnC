#include <stdioi.h>

#define __OFFSET 0x20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define ACCES_REGISTER_ADDRESS(io_addr) _MMIO_BYTE(io_addr) + __OFFSET)

//TIMER0
