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

int papattesdechatSysCall(int code) {
    int args[] = {0, code, 0xC};
    int size[] = {6, 20, 6};

    return papattesdechat(args, size, 3);
}

void tafonctionpetee(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char *instruction = ins + indexes[0];
    /*int rs = atoi(ins + indexes[1]);
    int rt = atoi(ins + indexes[2]);
    int rd = atoi(ins + indexes[3]);*/

    if (!strncmp(instruction, "ADD", lengths[0])) {
        /* Pas ouf*/
        /*tafonctionpetee(ins, indexes, lengths, hex);*/
        
        /* Marche mieux */
        int opcode = 0b001000;
        int rs = 8;
        int rt = 8;
        /*int rd = 1;
        int sa = 0;
        int function = 0x20;*/
        int immediate = 1;
        int x = papattesdechatTypeI(opcode, rs, rt, immediate);

        printf("%x\n", x);
    }
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


    /*printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);

    afficherN(ins + indexes[0], lengths[0]);
    afficherN(ins + indexes[1], lengths[1]);
    afficherN(ins + indexes[2], lengths[2]);
    afficherN(ins + indexes[3], lengths[3]);*/
}