#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"

/* Ajoute un emplacement de valeur donnée à l'adresse indiquée.
   La mémoire est une liste chaînée ordonnée suivant les adresses. */
void addMemSlot(memSlot **mem, uint32_t address, int8_t value) {
    memSlot *new = malloc(sizeof(memSlot)), *element = *mem, *prev = *mem;
    int stop = 0;

    if (new == NULL) {
        printf("ERREUR : allocation mémoire impossible.");

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

/* Recherche et renvoie l'emplacement mémoire d'adresse indiquée, ou NULL s'il n'existe pas (vaut 0) */
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

/* Modifie la valeur de l'emplacement mémoire d'adresse indiquée, s'il existe. */
void changeMemSlot(memSlot **mem, uint32_t address, int8_t value) {
    memSlot *element = findMemSlot(mem, address);
    if (element != NULL) element->value = value;
}

/* Supprime l'emplacement mémoire d'adresse indiquée et libère la mémoire. */
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

/* Vide l'intégralité de la mémoire. */
void emptyMemory(memSlot **mem) {
    while (*mem != NULL) {
        delMemSlot(mem, (*mem)->address);
    }
}

/* Renvoie la valeur d'un emplacement mémoire (1 octet) d'adresse donnée ou 0 s'il n'existe pas. */
int8_t readByte(memSlot **mem, uint32_t address) {
    memSlot *element = findMemSlot(mem, address);

    return element != NULL ? element->value : 0;
}

/* Renvoie la valeur des 4 emplacements mémoire successifs (4 octets) à partir d'une adresse donnée. */
int32_t readMemory(memSlot **mem, uint32_t address) {
    int32_t result = 0;
    int i;

    for (i = 0; i < 4; i++) {
        result += (readByte(mem, address) & 0xff) << (8 * i);
        address++;
    }

    return result;
}

/* Écrit la valeur donnée (1 octet) à un emplacement mémoire d'adresse donné.
   Cette fonction crée l'emplacement s'il n'existe pas, le modifie s'il existe ou le supprime si la valeur à écrire est 0. */
void writeByte(memSlot **mem, uint32_t address, int8_t value) {
    memSlot *element = findMemSlot(mem, address);

    if (value == 0) delMemSlot(mem, address);
    else if (element == NULL) addMemSlot(mem, address, value);
    else changeMemSlot(mem, address, value);
}

/* Écrit la valeur donnée (4octet) dans les 4 emplacements mémoire successifs à partir d'une adresse donné. */
void writeMemory(memSlot **mem, uint32_t address, int32_t value) {
    int i;

    for (i = 0; i < 4; i++) {
        writeByte(mem, address + i, value);
        value >>= 8;
    }
}

/* Affiche le contenu de la mémoire. */
void printMemory(memSlot **mem, int isDataMemory) {
    memSlot *element = *mem;
    int i = 0;

    char *dataUpperName = "= MEMOIRE DE DONNEES =",
         *progUpperName = " MEMOIRE DE PROGRAMME ",
         *dataLowerName = "données",
         *progLowerName = "programme";

    char *uppername, *lowername;

    if (isDataMemory) {
        uppername = dataUpperName;
        lowername = dataLowerName;

    } else {
        uppername = progUpperName;
        lowername = progLowerName;
    }

    if (element == NULL) {
        printf("La mémoire de %s est vide.\n", lowername);

    } else {
        printf("===============================%s===============================", uppername);

        while (element != NULL) {
            if (i == 0) printf("\n ");

            printf("@%08X : %02hhx   ", element->address, element->value);
            element = element->next;

            i = (i + 1) % 5;
        }
    
        printf("\n====================================================================================\n");
    }
}