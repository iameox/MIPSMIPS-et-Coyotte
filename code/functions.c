#include <stdio.h>
#include "functions.h"
#include "files.h"
#include <string.h>

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

    while (ins[i] == ' ' || ins[i] == ',' || ins[i] == '$' || ins[i] == '(') {
        i++;
    }

    return i;
}

/* Retourne la longueur du premier mot-clé trouvé */
int wordLength(char *ins) {
    int i = 0, stop = 0;

    while (ins[i] != ' ' && ins[i] != ',' && ins[i] != '#' && ins[i] != '(' && ins[i] != ')' && ins[i] != '\0' && !stop) {
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

    tafonctionpetee(ins, indexes, lengths, hex);


    printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);

    afficherN(ins + indexes[0], lengths[0]);
    afficherN(ins + indexes[1], lengths[1]);
    afficherN(ins + indexes[2], lengths[2]);
    afficherN(ins + indexes[3], lengths[3]);
}



void tafonctionpetee(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char * instruction = ins + indexes[0];
    char * rs = ins + indexes[1];
    char * rt = ins + indexes[2];
    char * rd = ins + indexes[3];


    if( !strncmp(instruction,"ADD",lengths[0]) ){
        hex[0] = '0';
        hex[1] = hex(strToBinary(rs, length[1]) >> 3);
        hex[2] = hex((strToBinary(rs, length[1]) & 7) | strToBinary(rt, length[1]) >> 4 );
        hex[3] = '0-15';
        hex[4] = '0-15';
        hex[5] = '0-14';
        hex[6] = '2';
        hex[7] = '0';
    }
}