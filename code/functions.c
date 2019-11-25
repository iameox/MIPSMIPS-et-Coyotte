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

/*
    Retourne un masque composé des n premiers bits à 1, les suivants à 0.
*/
int mask(int n) {
    int result = 0, i;
    
    for (i = 0; i < n; i++) {
        result = (result << 1) + 1;
    }
    
    return result;
}

/*
   Calcule et retourne la valeur d'un quartet composé de 2 variables.
   x : variable à mettre en début de quartet.
   y : variable à mettre en fin de quartet.
   sy : taille en bits de y.
   ny : nombre de bits de poids fort de y conservés. (4 - ny) est le nombre de bits de poids faible de x conservés.
*/
int nibble(int x, int y, int sy, int ny) {
    return ((x & mask(4 - ny)) << ny) + (y >> (sy - ny));
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
    char *instruction = ins + indexes[0];
    int rs = atoi(ins + indexes[1]);
    int rt = atoi(ins + indexes[2]);
    int rd = atoi(ins + indexes[3]);

    if (!strncmp(instruction, "ADD", lengths[0])) {
        hex[0] = nibble(0, 0, 0, 0);
        hex[1] = nibble(0, rs, 5, 2);
        hex[2] = nibble(rs, rt, 5, 1);
        hex[3] = nibble(rt, 0, 5, 0);
        hex[4] = nibble(0, rd, 5, 4);
        hex[5] = nibble(0, rt, 5, 4);
        hex[6] = nibble(0, 100000, 6, 2);
        hex[7] = nibble(0, 0, 0, 0);
    }
}

/*
int main()
{
    int x = 0, i = 0;
    int rs = 0b00101, rt = 0b11000, rd = 0b01010;
    int opcode = 0b110010;
    int sa = 0b11001;
    int function = 0b101010;
    
    int k[] = {0, opcode, rs, rt, rd, sa, function, 0};
    int s[] = {6, 5, 5, 5, 5, 6, 0};
    int j = min(4, s[i]);
    
    for(i = 0; i < 7; i++) {
        x = (x << 4) + nibble(k[i], k[i+1], s[i], j);
        
        if (j == 0) {
            if (i + 1 < 7) i--;
            j = min(4, s[i]);
        }
        else j = 4 - s[i] + j;
    }
    
    x = (x << 4) + nibble(0, opcode, 6, 4);
    x = (x << 4) + nibble(opcode, rs, 5, 2);
    x = (x << 4) + nibble(rs, rt, 5, 1);
    x = (x << 4) + nibble(rt, rd, 5, 0);
    x = (x << 4) + nibble(rt, rd, 5, 4);
    x = (x << 4) + nibble(rd, sa, 5, 3);
    x = (x << 4) + nibble(sa, function, 6, 2);
    x = (x << 4) + nibble(function, 0, 0, 0);
    
    printf("%x\n",x);
    
}

*/