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
memSlot *findMemSlot(memSlot **mem, uint32_t address);
int8_t readByte(memSlot **mem, uint32_t address);
int32_t readMemory(memSlot **mem, uint32_t address);
void writeByte(memSlot **mem, uint32_t address, int8_t value);
void writeMemory(memSlot **mem, uint32_t address, int32_t value);
void printMemory(memSlot **mem);