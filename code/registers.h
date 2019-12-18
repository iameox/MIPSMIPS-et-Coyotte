#include <stdint.h>
#define REGISTERS_NUMBERS 32

int32_t REGISTERS[REGISTERS_NUMBERS];
int32_t PC, HI, LO;

void initRegisters(void);
int32_t readRegister(int index);
int writeRegister(int index, int32_t value);
void printRegisters(void);