#include <stdint.h>

uint32_t REGISTERS[32];

void initRegisters(void);
int readRegister(int index);
int writeRegister(int index, int value);
void printRegisters(void);