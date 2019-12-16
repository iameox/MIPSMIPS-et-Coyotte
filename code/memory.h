#include <stdint.h>
#define MEMORY_MAX_ADDRESS 0xFFFFFFFF

typedef struct memSlot {
	uint32_t address;
	uint8_t value;
	struct memSlot *next;
} memSlot;

memSlot *MEMORY;

void emptyMemory();
uint8_t readMemory(uint32_t address);
void writeMemory(uint32_t address, int8_t value);
void printMemory(void);