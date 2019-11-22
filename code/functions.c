#include <stdio.h>
#include "functions.h"
#include "files.h"

void afficherN(char *c, int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%c", c[i]);
    }

    printf("\n");
}

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
    int i = 0, stop = 0;

    while (ins[i] != ' ' && ins[i] != ',' && ins[i] != '#' && ins[i] != '\0' && !stop) {
        if (ins[i] == ':') {
            stop = 1;
        }

        i++;
    }

    return i;
}

void MIPStoHex(char *ins, char hex[SIZE]) {
    int i = 0,
        index = 0, length = 1,
        indexes[4], lengths[4];

    while (length != 0 && i < 4) { /* Isolation des mots-clés */
        index += wordIndex(ins + index);
        length = wordLength(ins + index);

        if (length != 0 && *(ins + index + length - 1) != ':') { /* label */
            indexes[i] = index;
            lengths[i] = length;
            i++;
        }

        index += length;
    }

    printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);

    afficherN(ins + indexes[0], lengths[0]);
    afficherN(ins + indexes[1], lengths[1]);
    afficherN(ins + indexes[2], lengths[2]);
    afficherN(ins + indexes[3], lengths[3]);
}