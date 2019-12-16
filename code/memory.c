#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"

void addMemSlot(uint32_t address, int8_t value) {
    memSlot *new = malloc(sizeof(memSlot)), *element = MEMORY, *prev = MEMORY;
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

            if (element == MEMORY) MEMORY = new;
            else prev->next = new;
        }
    }
}

memSlot *findMemSlot(uint32_t address) {
    memSlot *element = MEMORY;
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

void changeMemSlot(uint32_t address, int8_t value) {
    memSlot *element = findMemSlot(address);
    element->value = value;
}

void delMemSlot(uint32_t address) {
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

int8_t readMemory(uint32_t address) {
    memSlot *element = findMemSlot(address);

    return element != NULL ? element->value : 0;
}

void writeMemory(uint32_t address, int8_t value) {
    memSlot *element = findMemSlot(address);

    if (value == 0) delMemSlot(address);
    else if (element == NULL) addMemSlot(address, value);
    else changeMemSlot(address, value);
}

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