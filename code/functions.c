#include <stdio.h>
#include "files.h"
#define SIZE 8

/* Retourne l'index du premier mot-clé trouvé */
int wordIndex(char *ins) {
    int i = 0;

    while (ins[i] == ' ' || ins[i] == ',' || ins[i] == '$') {
        i++;
    }

    return i;
}

/* Retourne la longueur du premier mot-clé trouvé */
int wordLength(char *ins) {
    int i = 0;

    while (ins[i] != ' ' && ins[i] != ',' && ins[i] != '#' && ins[i] != '\0') {
        i++;
    }

    return i;
}

void MIPStoHex(char *ins, char hex[SIZE]) {
    int *shiftedIns = ins,
        i = 0,
        index, length = 1,
        indexes[4], lengths[4];

    while (length != 0) { /* Isolation des mots-clés */
        index = wordIndex(shiftedIns);
        length = wordLength(shiftedIns);
        shiftedIns += index + length;

        if (*(shiftedIns) != ':') { /* label */
            indexes[i] = index;
            lengths[i] = length;
            i++;
        }
    }

    printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);
}