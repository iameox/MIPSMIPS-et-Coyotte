#include <stdint.h>
#define REGISTERS_NUMBERS 32

uint32_t REGISTERS[REGISTERS_NUMBERS];

void initRegisters(void);
int readRegister(int index);
int writeRegister(int index, uint32_t value);
void printRegisters(void);