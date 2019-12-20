#include <stdint.h>
#define MEMORY_MAX_ADDRESS 0xFFFFFFFF

typedef struct memSlot {
	uint32_t address;
	int8_t value;
	struct memSlot *next;
} memSlot;

memSlot *DATA_MEMORY;
memSlot *PROG_MEMORY;

void emptyMemory(memSlot **mem);
int8_t readMemory(memSlot **mem, uint32_t address);
void writeMemory(memSlot **mem, uint32_t address, int8_t value);
void printMemory(memSlot **mem);