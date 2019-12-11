#include <stdio.h>
#include "registers.h"

void initRegisters(void);
int readRegister(int index);
int writeRegister(int index, int value);
void printRegisters(void);