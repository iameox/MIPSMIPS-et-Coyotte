#define MEMORY_MAX_ADDRESS 0xFFFFFFFF

typedef struct memSlot {
	uint32_t adress;
	uint8_t value;
	struct memSlot *next;
} memSlot;

memSlot *MEMORY;

memSlot *addMemSlot(int adress, char value); 
void delMemSlot(int adress);
void emptyMemory();
memSlot *findMemSlot(int adress);

uint8_t readMemory(uint32_t adress);
int writeMemory(uint32_t adress, int8_t value);
void printMemory(void);