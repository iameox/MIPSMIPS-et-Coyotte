#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

/* Fonction puissance */
int power(int a, int b) {
    int i, result = 1;
    for(i = 0 ; i < b ; i++) result *= a;
    return result;
}


/* Convertit un caractère ascii en sa valeur numérique, en prenant en compte la base */
int asciiToInt(char *str, int size, int base) {
    int i, digit, value = 0;
    for(i = 0 ; i < size ; i++) {
        if(base > 10 && str[i] >= 'a'&& str[i] < 'a' - 10 + base) { /*Detection des digits plus grands que 10, majuscules non supportées*/
            digit = str[i] - ASCII_TO_HEX_OFFSET; /*Décalage par rapport à la table ASCII pour passer d'un caractère alphabétique à sa valeur hexadécimale*/
        } else {
            digit = str[i] - ASCII_TO_DEC_OFFSET; /*Décalage par rapport à la table ASCII pour passer d'un caractère numérique à sa valeur décimale*/
        }
        /*printf("le digit : %d\n", digit);*/
        value += digit*power(base ,size - i-1);
    }
    return value;
}

/* Determine la valeur correspondante d'un argument en prenant en compte les différents modes (immédiat, registres spéciaux ou non, hexadécimal) */
int convertArgument(char * argStr, int size) {
    int operandValue = 0;
    char * registerStr = argStr + 1;

    if (size > 2 && argStr[0] == '0' && argStr[1] == 'x') { /* écriture hexa*/
        operandValue = asciiToInt(argStr+2, size -2, 16);
    } else if( argStr[0] == '$') { /*registres*/
        if(isalpha(registerStr[0])) { /*registres spéciaux*/
            if(!strncmp(registerStr, "zero", size-1)) {
                operandValue = 0;
            }
            if(!strncmp(registerStr, "at", size-1)) {
                operandValue = 1;
            }
            if(registerStr[0] == 'v' && isdigit(registerStr[1])) {
                operandValue = 2 + asciiToInt(registerStr + 1, size - 2, 10);
            }
            if(registerStr[0] == 'a' && isdigit(registerStr[1])) {
                operandValue = 4 + asciiToInt(registerStr + 1, size - 2, 10);
            }
            if(registerStr[0] == 't' && isdigit(registerStr[1])) {
                if(asciiToInt(registerStr + 1, size - 2 , 10) < 8) {
                    operandValue = 8 + asciiToInt(registerStr + 1, size - 2, 10);
                } 
                else {
                    operandValue = 16 + asciiToInt(registerStr + 1, size - 2, 10);
                } 
            }
            if(registerStr[0] == 's' && isdigit(registerStr[1])) {
                operandValue = 16 + asciiToInt(registerStr + 1, size - 2, 10);
            }
            if(registerStr[0] == 'k' && isdigit(registerStr[1])) {
                operandValue = 26 + asciiToInt(registerStr + 1, size - 2, 10);
            }
            if(!strncmp(registerStr, "gp", size-1)) {
                operandValue = 28;
            }
            if(!strncmp(registerStr, "sp", size-1)) {
                operandValue = 29;
            }
            if(!strncmp(registerStr, "fp", size-1)) {
                operandValue = 30;
            }
            if(!strncmp(registerStr, "ra", size-1)) {
                operandValue = 31;
            }
        } else { /*Cas classique*/
            operandValue = asciiToInt(registerStr, size - 1, 10);
        }
    } else {
        if (argStr[0] == '-') {
            operandValue = -asciiToInt(argStr + 1, size - 1, 10);
        } else {
            operandValue = asciiToInt(argStr, size, 10);
        }
    }
    /*printf("Opérande : %d\n", operandValue);*/
    return operandValue;
}

int getWord(int * args, int * size, int n) {
    int result = 0, i;

    for (i = 0; i < n; i++) {
        result = (result << size[i]) + args[i];
    }

    return result;
}

int getTypeRWord(int opcode, int rs, int rt, int rd, int sa, int function) {
    int args[] = {opcode, rs, rt, rd, sa, function};
    int size[] = {6, 5, 5, 5, 5, 6};

    return getWord(args, size, 6);
}

int getTypeIWord(int opcode, int rs, int rt, int immediate) {
    int args[] = {opcode, rs, rt, immediate};
    int size[] = {6, 5, 5, 16};

    return getWord(args, size, 4);
}

int getTypeJWord(int opcode, int target) {
    int args[] = {opcode, target};
    int size[] = {6, 26};

    return getWord(args, size, 2);
}

int mapInstruction(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char *name = ins + indexes[0];
    int arg1 = convertArgument(ins + indexes[1], lengths[1]);
    int arg2 = convertArgument(ins + indexes[2], lengths[2]);
    int arg3 = convertArgument(ins + indexes[3], lengths[3]);

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

    return lengths[0] != 0 ? mapInstruction(ins, indexes, lengths, hex) : 0;
}