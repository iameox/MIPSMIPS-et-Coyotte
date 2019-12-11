typedef struct memSlot {
	uint32_t adress;
	uint8_t value;
	struct memSlot *next;
} memSlot;

memSlot *MEMORY;

uint8_t readMemory(uint32_t adress);
int writeMemory(uint32_t adress, int8_t value);
void printMemory(void);