#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"

void addMemSlot(int address, char value) {
    if (address > MEMORY_MAX_ADDRESS) {
        printf("RT");

    } else {
        memSlot *element = malloc(sizeof(memSlot)), *prev = MEMORY;
        int stop = 0;

        if (element == NULL) {
            printf("RT");

        } else   {
            element->address = address;
            element->value = value;

            while (prev != NULL && !stop) {
                if (prev->next->address > address) {
                    element->next = prev->next;
                    prev->next = element;

                    stop = 1;
                }

                prev = prev->next;
            }
        }
    }
}

void delMemSlot(int address) {
    memSlot *element = MEMORY, *prev = MEMORY;
    int stop = 0;

    while (element->next != NULL && !stop) {
        if (element->next->address == address) {
            prev->next = element->next;
            free(element);

            stop = 1;
        
        } else {
            prev = element;
            element = element->next;
        }
    }
}

void emptyMemory() {
    while (MEMORY->next != NULL) {
        delMemSlot(MEMORY->next->address);
    }
}

/*memSlot *findMemSlot(int address) {

}

uint8_t readMemory(uint32_t address) {

}*/

int writeMemory(uint32_t address, int8_t value) {

}

void printMemory(void) {
    memSlot *element = MEMORY;

    printf("---------- Memory Dump -----------");
    while (element->next != NULL) {
        printf("%d: %d\n", element->address, element->value);
        element = element->next;
    }

    printf("----------------------------------");
}