#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"

void addMemSlot(memSlot **mem, uint32_t address, int8_t value) {
    memSlot *new = malloc(sizeof(memSlot)), *element = *mem, *prev = *mem;
    int stop = 0;

    if (new == NULL) {
        printf("Erreur lors de l'allocation mémoire.");

    } else {
        new->address = address;
        new->value = value;

        while (element != NULL && !stop) {
            if (element->address > address) {
                new->next = prev->next;
                prev->next = new;
    
                stop = 1;
            }
    
            prev = element;
            element = element->next;
        }

        if (!stop) {
            new->next = NULL;

            if (element == *mem) *mem = new;
            else prev->next = new;
        }
    }
}

memSlot *findMemSlot(memSlot **mem, uint32_t address) {
    memSlot *element = *mem;
    int stop = 0;

    while (element != NULL && !stop) {
        if (element->address == address) {
            stop = 1;
        
        } else {
            element = element->next;
        }
    }

    return element;
}

void changeMemSlot(memSlot **mem, uint32_t address, int8_t value) {
    memSlot *element = findMemSlot(mem, address);
    element->value = value;
}

void delMemSlot(memSlot **mem, uint32_t address) {
    memSlot *element = *mem, *prev = *mem;
    int stop = 0;

    while (element != NULL && !stop) {
        if (element->address == address) {
            if (element == *mem) *mem = element->next;
            else prev->next = element->next;

            free(element);
            stop = 1;
        
        } else {
            prev = element;
            element = element->next;
        }
    }
}

void emptyMemory(memSlot **mem) {
    while (*mem != NULL) {
        delMemSlot(mem, (*mem)->address);
    }
}

int8_t readMemory(memSlot **mem, uint32_t address) {
    memSlot *element = findMemSlot(mem, address);

    return element != NULL ? element->value : 0;
}

void writeByte(memSlot **mem, uint32_t address, int8_t value) {
    memSlot *element = findMemSlot(mem, address);

    if (value == 0) delMemSlot(mem, address);
    else if (element == NULL) addMemSlot(mem, address, value);
    else changeMemSlot(mem, address, value);
}

void writeMemory(memSlot **mem, uint32_t address, int32_t value) {
    int i;

    for (i = 0; i < 4; i++) {
        writeByte(mem, address, value);
        value <<= 4;
    }
}

void printMemory(memSlot **mem) {
    memSlot *element = *mem;

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