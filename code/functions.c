#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

    printf("' ");
}

/* Retourne l'index du premier mot-clé trouvé */
int wordIndex(char *ins, int n, char *delimiters) {
    int i = 0, stop = 0, j;
    
    while (i < n && ins[i] != '\n' && ins[i] != '\r' && ins[i] != '\0' && !stop) {
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
int wordLength(char *ins, int n, char *delimiters) {
    int i = 0, stop = 0, j;
    
    while (i < n && ins[i] != '\n' && ins[i] != '\r' && ins[i] != '\0' && !stop) {
        j = 0;

        while (delimiters[j] != '\0' && !stop) {
            if (ins[i] == delimiters[j]) stop = 1;
            j++;
        }

        i++;
    }

    return stop ? i - 1 : i;
}

int power(int a, int b) {
    int i, result = 1;
    for(i = 0 ; i < b ; i++) result *= a;
    return result;
}

int amoi(char *str, int size, int base) {
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
        value += digit*power(base ,size - i-1);
    }
    return value;
}

/* Determine la valeur correspondante du charactère, ainsi que les registres spéciaux (sp, fp, ra) et gère la notation hexdécimale*/
int anous(char * argStr, int size) {
    int operandValue = 0;
    char * registerStr = argStr+1;

    if (size > 2 && registerStr[0] == '0' && registerStr[1] == 'x') { /* écriture hexa*/
        operandValue = amoi(registerStr+2, size -2, 16);
    } else if( argStr[0] == '$' ) {
        if(isalpha(registerStr[0])) { /*registres spéciaux*/
            if(!strncmp(registerStr, "zero", size)) {
                operandValue = 0;
            }
            if(!strncmp(registerStr, "at", size)) {
                operandValue = 1;
            }
            if(registerStr[0] == 'v' && isdigit(registerStr[1])) {
                operandValue = 2 + amoi(registerStr + 1, size - 2, 10);
            }
            if(registerStr[0] == 'a' && isdigit(registerStr[1])) {
                operandValue = 4 + amoi(registerStr + 1, size - 2, 10);
            }
            if(registerStr[0] == 't' && isdigit(registerStr[1])) {
                if(atoi(registerStr + 1) < 8) {
                    operandValue = 8 + amoi(registerStr + 1, size - 2, 10);
                } 
                else {
                    operandValue = 16 + amoi(registerStr + 1, size - 2, 10);
                } 
            }
            if(registerStr[0] == 's' && isdigit(registerStr[1])) {
                operandValue = 16 + amoi(registerStr + 1, size - 2, 10);
            }
            if(registerStr[0] == 'k' && isdigit(registerStr[1])) {
                operandValue = 26 + amoi(registerStr + 1, size - 2, 10);
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
            operandValue = amoi(registerStr, size - 1, 10);
        }
    } else {
        if (argStr[0] == '-') {
            operandValue = -amoi(argStr + 1, size - 1, 10);
        } else {
            operandValue = amoi(argStr, size, 10);
        }
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

int tafonctionpetee(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char *name = ins + indexes[0];
    int arg1 = anous(ins + indexes[1], lengths[1]);
    int arg2 = anous(ins + indexes[2], lengths[2]);
    int arg3 = anous(ins + indexes[3], lengths[3]);

    printf("%d\n", arg2);

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

int MIPStoHex(char *ins, int n, char hex[SIZE]) {
    int index = wordIndex(ins, n, " \t");
    int length = wordLength(ins + index, n - index, " \t#");
    int i = index + length, j = 1;

    int indexes[4] = {index};
    int lengths[4] = {length};

    while (j < 4 && i < n) {
        index = wordIndex(ins + i, n - i, " \t,(");
        length = wordLength(ins + i + index, n - i - index, " \t,()#");

        indexes[j] = i + index;
        lengths[j] = length;

        i += index + length;
        j++;
    }

    //printf("index : %d %d %d %d\n", indexes[0], indexes[1], indexes[2], indexes[3]);
    //printf("taille : %d %d %d %d\n", lengths[0], lengths[1], lengths[2], lengths[3]);

    /*afficherN(ins + indexes[0], lengths[0]);
    afficherN(ins + indexes[1], lengths[1]);
    afficherN(ins + indexes[2], lengths[2]);
    afficherN(ins + indexes[3], lengths[3]);
    printf("\n");*/

    return lengths[0] != 0 ? tafonctionpetee(ins, indexes, lengths, hex) : 0;
}