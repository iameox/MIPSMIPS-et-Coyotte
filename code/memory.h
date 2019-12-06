#include <stdlib.h>
#include <stdio.h>

typedef struct memSlot {
	int adress;
	char value;
	struct memSlot *next;
} memSlot;

memSlot *MEMORY;

/*memSlot *addMemSlot(memSlot *head, int adress, char value);
memSlot *delMemSlot(memSlot *head, int adress);
void emptyMemory(memSlot *head);
memSlot *findMemSlot(memSlot *head, int adress);*/

char readMemory(int adress);
int writeMemory(int adress, char value);
void printMemory(void);