#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"

void addMemSlot(int address, char value) {
    memSlot *new = malloc(sizeof(memSlot)), *element = MEMORY, *prev = MEMORY;
    int stop = 0;

    if (new == NULL) {
        printf("RT");

    } else {
        new->address = address;
        new->value = value;

        while (element != NULL && !stop) {
            if (element->address == address) {
                element->value = value;
                stop = 1;

            } else if (element->address > address) {
                new->next = prev->next;
                prev->next = new;
    
                stop = 1;
            }
    
            prev = element;
            element = element->next;
        }

        if (!stop) {
            new->next = NULL;
            printf("salut %d %d\n", MEMORY, prev);
            if (element == MEMORY) MEMORY = new;
            else prev->next = new;
        }
    }
}

void delMemSlot(int address) {
    memSlot *element = MEMORY, *prev = MEMORY;
    int stop = 0;

    while (element != NULL && !stop) {
        if (element->address == address) {
            if (element == MEMORY) MEMORY = element->next;
            else prev->next = element->next;
            free(element);

            stop = 1;
        
        } else {
            prev = element;
            element = element->next;
        }
    }
}

void emptyMemory() {
    while (MEMORY != NULL) {
        delMemSlot(MEMORY->address);
    }
}

/*memSlot *findMemSlot(int address) {

}

uint8_t readMemory(uint32_t address) {

}

int writeMemory(uint32_t address, int8_t value) {

}*/

void printMemory(void) {
    memSlot *element = MEMORY;

    if (element == NULL) {
        printf("La mémoire est vide.\n");

    } else {
        printf("========== Memory Dump ===========\n");

        while (element != NULL) {
            printf("@%08X : %u\n", element->address, element->value);
            element = element->next;
        }
    
        printf("==================================\n");
    }
}