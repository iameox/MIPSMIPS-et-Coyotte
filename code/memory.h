#include <stdint.h>
#define MEMORY_MAX_ADDRESS 0xFFFFFFFF

typedef struct memSlot {
	uint32_t address;
	uint8_t value;
	struct memSlot *next;
} memSlot;

memSlot *MEMORY;

void addMemSlot(int address, char value); 
void delMemSlot(int address);
void emptyMemory();
memSlot *findMemSlot(int address);

uint8_t readMemory(uint32_t address);
int writeMemory(uint32_t adsress, int8_t value);
void printMemory(void);