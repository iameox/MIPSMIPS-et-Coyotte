#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

memSlot *addMemSlot(MEMORY mem, int adress, char value) {
    if (address > 0xFFFFFFFF) {
        printf("RT");

    } else {
        memSlot *element = malloc(sizeof(memSlot)), *prev = mem, stop = 0;

        if (element == NULL) {
            printf("RT");

        } else {
            while (prev != NULL && !stop) {
                if (prev->next.address > address) {
                    prev->next = element;

                    stop = 1;
                }

                prev = prev->next;
            }
        }
    }
}

void delMemSlot(MEMORY mem, int adress) {
    memSlot *element = mem, *prev = mem, stop = 0;

    while (element->next != NULL && !stop) {
        if (element->next.address == address) {
            prev->next = element->next;
            free(element);

            stop = 1;
        
        } else {
            prev = element;
            element = element->next;
        }
    }
}

void emptyMemory(MEMORY mem) {
    while (mem->next != NULL) {
        delMemSlot(mem, mem->next.address);
    }
}

memSlot *findMemSlot(MEMORY mem, int adress) {

}

uint8_t readMemory(uint32_t adress) {

}

int writeMemory(uint32_t adress, int8_t value) {

}

void printMemory(void) {

}