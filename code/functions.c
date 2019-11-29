#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"
#include "files.h"
#include "instructions.h"

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

int power(int a, int b) {
    int i, result = 1;
    for(i = 0 ; i < b ; i++) result *= a;
    return result;
}

int amoi(char *str, int size) {
    int i, digit, value = 0;
    for(i = 0 ; i < size ; i++) {
        switch(str[i]) {
            case 'a': digit = 10;
            break;
            case 'b': digit = 11;
            break;
            case 'c': digit = 12;
            break;
            case 'd': digit = 13;
            break;
            case 'e': digit = 14;
            break;
            case 'f': digit = 15;
            break;
            default: digit = str[i] - 48; /*Wola faut trouver un équivalent de atoi mais pour des char*/
            break;
        }
        /*printf("le digit : %d\n", digit);
        printf("la puissance de 16 : %d\n", size-i-1);
        printf("ce que je trouve pour la puissance de 16: %d\n", power(16,size - i-1));*/
        value += digit*power(16,size - i-1);
    }
    return value;
}

/* Determine la valeur correspondante du charactère, ainsi que les registres spéciaux (sp, fp, ra) et gère la notation hexdécimale*/
int anous(char * argStr, int size) {
    int operandValue = 0;
    char * registerStr = argStr+1;

    if (size > 2 && registerStr[0] == '0' && registerStr[1] == 'x') { /* écriture hexa*/
        operandValue = amoi(registerStr+2, size -2);
    } else if( argStr[0] == '$' ) {
        if(isalpha(registerStr[0])) { /*registres spéciaux*/
            if(!strncmp(registerStr, "zero", size)) {
                operandValue = 0;
            }
            if(!strncmp(registerStr, "at", size)) {
                operandValue = 1;
            }
            if(registerStr[0] == 'v' && isdigit(registerStr[1])) {
                operandValue = 2 + atoi(registerStr + 1);
            }
            if(registerStr[0] == 'a' && isdigit(registerStr[1])) {
                operandValue = 4 + atoi(registerStr + 1);
            }
            if(registerStr[0] == 't' && isdigit(registerStr[1])) {
                if(atoi(registerStr + 1) < 8) {
                    operandValue = 8 + atoi(registerStr + 1);
                } 
                else {
                    operandValue = 16 + atoi(registerStr + 1);
                } 
            }
            if(registerStr[0] == 's' && isdigit(registerStr[1])) {
                operandValue = 16 + atoi(registerStr + 1);
            }
            if(registerStr[0] == 'k' && isdigit(registerStr[1])) {
                operandValue = 26 + atoi(registerStr +1);
            }
            if(!strncmp(registerStr, "gp", size)) {
                operandValue = 28;
            }
            if(!strncmp(registerStr, "sp", size)) {
                operandValue = 29;
            }
            if(!strncmp(registerStr, "fp", size)) {
                operandValue = 30;
            }
            if(!strncmp(registerStr, "ra", size)) {
                operandValue = 31;
            }
        } else { /*Cas classique*/
            operandValue = atoi(registerStr);
        }
    } else {
        operandValue = atoi(argStr);
    }

    return operandValue;
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

void tafonctionpetee(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char *instruction = ins + indexes[0];
    int arg1 = anous(ins + indexes[1]-1,lengths[1]+1);
    int arg2 = anous(ins + indexes[2]-1,lengths[2]+1);
    int arg3 = anous(ins + indexes[3],lengths[3]);

    char *instructions[] = INS_NAMES;
    int (*functions[])(int, int, int) = INS_POINTERS;
    int i = 0, stop = 0;
    int result;

    while (i < INS_NUMBER && !stop) {
        if (!strncmp(instruction, instructions[i], lengths[0])) {
            stop = 1;

            result = (functions[i])(arg1, arg2, arg3);
        }

        i++;
    }

    sprintf(hex, "%.8x", result);
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


    /*printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);

    afficherN(ins + indexes[0], lengths[0]);
    afficherN(ins + indexes[1], lengths[1]);
    afficherN(ins + indexes[2], lengths[2]);
    afficherN(ins + indexes[3], lengths[3]);*/
}