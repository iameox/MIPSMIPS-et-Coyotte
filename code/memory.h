#include <stdlib.h>
#include <stdio.h>

typedef struct memSlot {
	uint32_t adress;
	uint8_t value;
	struct memSlot *next;
} memSlot;

memSlot *MEMORY;

/*memSlot *addMemSlot(memSlot *head, int adress, char value);
memSlot *delMemSlot(memSlot *head, int adress);
void emptyMemory(memSlot *head);
memSlot *findMemSlot(memSlot *head, int adress);*/

uint8_t readMemory(uint32_t adress);
int writeMemory(uint32_t adress, int8_t value);
void printMemory(void);