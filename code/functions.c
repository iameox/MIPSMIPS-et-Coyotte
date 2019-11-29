#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "files.h"
#include "instructions.h"

void afficherN(char *c, int n) {
    int i;

    printf("'");
    for (i = 0; i < n; i++) {
        printf("%c", c[i]);
    }

    printf("'\n");
}

/* Retourne l'index du premier mot-clé trouvé */
int wordIndex(char *ins, char *delimiters) {
    int i = 0, stop = 0, j;
    
    while (ins[i] != '\n' && ins[i] != '\0' && !stop) {
        stop = 1;
        j = 0;

        while (delimiters[j] != '\0' && stop) {
            if (ins[i] == delimiters[j]) stop = 0;
            j++;
        }

        i++;
    }

    return stop ? i - 1 : i;
}

/* Retourne la longueur du premier mot-clé trouvé */
int wordLength(char *ins, char *delimiters) {
    int i = 0, stop = 0, j;
    
    while (ins[i] != '\n' && ins[i] != '\0' && !stop) {
        j = 0;

        while (delimiters[j] != '\0' && !stop) {
            if (ins[i] == delimiters[j]) stop = 1;
            j++;
        }

        i++;
    }

    return stop ? i - 1 : i;
}

int papattesdechat(int * args, int * size, int n) {
    int result = 0, i;

    for (i = 0; i < n; i++) {
        result = (result << size[i]) + args[i];
    }

    return result;
}

int papattesdechatTypeR(int opcode, int rs, int rt, int rd, int sa, int function) {
    int args[] = {opcode, rs, rt, rd, sa, function};
    int size[] = {6, 5, 5, 5, 5, 6};

    return papattesdechat(args, size, 6);
}

int papattesdechatTypeI(int opcode, int rs, int rt, int immediate) {
    int args[] = {opcode, rs, rt, immediate};
    int size[] = {6, 5, 5, 16};

    return papattesdechat(args, size, 4);
}

int papattesdechatTypeJ(int opcode, int target) {
    int args[] = {opcode, target};
    int size[] = {6, 26};

    return papattesdechat(args, size, 2);
}

int tafonctionpetee(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char *name = ins + indexes[0];
    int arg1 = anous(ins + indexes[1], lengths[1]);
    int arg2 = anous(ins + indexes[2], lengths[2]);
    int arg3 = anous(ins + indexes[3], lengths[3]);

    char *names[] = INS_NAMES;
    int (*functions[])(int, int, int) = INS_POINTERS;
    int i = 0, write = 0;
    int result;

    while (i < INS_NUMBER && !write) {
        if (!strncmp(name, names[i], lengths[0])) {
            write = 1;

            result = (functions[i])(arg1, arg2, arg3);
            sprintf(hex, "%.8x", result);
        }

        i++;
    }

    return write;
}

int MIPStoHex(char *ins, char hex[SIZE]) {
    int index = wordIndex(ins, " \t");
    int length = wordLength(ins + index, " \t#");
    int i = index + length, j = 1;

    int indexes[4] = {index};
    int lengths[4] = {length};

    while (j < 4 && length != 0) {
        index = wordIndex(ins + i, " \t,(");
        length = wordLength(ins + i + index, " \t,()#");

        indexes[j] = i + index;
        lengths[j] = length;

        i += index + length;
        j++;
    }

    /*printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);

    afficherN(ins + indexes[0], lengths[0]);
    afficherN(ins + indexes[1], lengths[1]);
    afficherN(ins + indexes[2], lengths[2]);
    afficherN(ins + indexes[3], lengths[3]);*/

    return tafonctionpetee(ins, indexes, lengths, hex);
}