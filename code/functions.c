#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "files.h"
#include "translation.h"
#include "memory.h"
#include "registers.h"

/* Retourne le nombre de caractères comptés jusqu'au dernier délimiteur trouvé inclus */
int wordIndex(char *ins, int n, char *delimiters) {
    int i = 0, stop = 0, j;
    
    while (i < n && ins[i] != '\n' && ins[i] != '\r' && ins[i] != '\0' && !stop) {
        stop = 1;
        j = 0;

        while (delimiters[j] != '\0' && stop) { /* Parcourt la liste des délimiteurs */
            if (ins[i] == delimiters[j]) stop = 0;
            j++;
        }

        i++;
    }

    return stop ? i - 1 : i; /* Si stop est à 1 le dernier caractère n'est pas un délimiteur, on l'enlève de la chaîne */
}

/* Retourne le nombre de caractères comptés jusqu'au premier délimiteur trouvé exclus */
int wordLength(char *ins, int n, char *delimiters) {
    int i = 0, stop = 0, j;
    
    while (i < n && ins[i] != '\n' && ins[i] != '\r' && ins[i] != '\0' && !stop) {
        j = 0;

        while (delimiters[j] != '\0' && !stop) { /* Parcourt la liste des délimiteurs */
            if (ins[i] == delimiters[j]) stop = 1;
            j++;
        }

        i++;
    }

    return stop ? i - 1 : i; /* Si un délimiteur est trouvé, on l'enlève de la chaîne */
}

/* Fonction puissance */
int power(int a, int b) {
    int i, result = 1;

    for (i = 0; i < b; i++) result *= a;
    return result;
}

/* Convertit un caractère ascii en sa valeur numérique, en prenant en compte la base */
int asciiToInt(char *str, int size, int base) {
    int i, digit, value = 0;

    for(i = 0; i < size; i++) {
        if (base > 10 && str[i] >= 'a' && str[i] < 'a' - 10 + base) { /* Detection des digits plus grands que 10, majuscules non supportées */
            digit = str[i] - ASCII_TO_HEX_OFFSET; /* Décalage par rapport à la table ASCII pour passer d'un caractère alphabétique à sa valeur hexadécimale */
        
        } else {
            digit = str[i] - ASCII_TO_DEC_OFFSET; /* Décalage par rapport à la table ASCII pour passer d'un caractère numérique à sa valeur décimale */
        }

        value += digit * power(base, size - i - 1);
    }
    return value;
}

/* Determine la valeur correspondante d'un argument en prenant en compte les différents modes (immédiat, registres spéciaux ou non, hexadécimal) */
int convertArgument(char * argStr, int size) {
    int operandValue = 0;
    char *registerStr = argStr + 1;

    if (size > 2 && argStr[0] == '0' && argStr[1] == 'x') { /* Hexadécimal */
        operandValue = asciiToInt(argStr+2, size -2, 16);

    } else if (argStr[0] == '$') { /* Registres */
        if (isalpha(registerStr[0])) { /* Registres spéciaux */
            if (!strncmp(registerStr, "zero", size-1)) {
                operandValue = 0;
            
            } else if (!strncmp(registerStr, "at", size-1)) {
                operandValue = 1;
            
            } else if (registerStr[0] == 'v' && isdigit(registerStr[1])) {
                operandValue = 2 + asciiToInt(registerStr + 1, size - 2, 10);
            
            } else if (registerStr[0] == 'a' && isdigit(registerStr[1])) {
                operandValue = 4 + asciiToInt(registerStr + 1, size - 2, 10);
            
            } else if (registerStr[0] == 't' && isdigit(registerStr[1])) {
                if (asciiToInt(registerStr + 1, size - 2 , 10) < 8) {
                    operandValue = 8 + asciiToInt(registerStr + 1, size - 2, 10);
                
                } else {
                    operandValue = 16 + asciiToInt(registerStr + 1, size - 2, 10);
                } 
            
            } else if (registerStr[0] == 's' && isdigit(registerStr[1])) {
                operandValue = 16 + asciiToInt(registerStr + 1, size - 2, 10);
            
            } else if (registerStr[0] == 'k' && isdigit(registerStr[1])) {
                operandValue = 26 + asciiToInt(registerStr + 1, size - 2, 10);
            
            } else if (!strncmp(registerStr, "gp", size-1)) {
                operandValue = 28;
            
            } else if (!strncmp(registerStr, "sp", size-1)) {
                operandValue = 29;
            
            } else if (!strncmp(registerStr, "fp", size-1)) {
                operandValue = 30;
            
            } else if (!strncmp(registerStr, "ra", size-1)) {
                operandValue = 31;
            }

        } else { /* Registre classique */
            operandValue = asciiToInt(registerStr, size - 1, 10);
        }

    } else { /* Cas classique */
        if (argStr[0] == '-') { /* Opérande négatif */
            operandValue = -asciiToInt(argStr + 1, size - 1, 10);
        
        } else {
            operandValue = asciiToInt(argStr, size, 10);
        }
    }

    return operandValue;
}

/* Génère un mot machine de 32 bits sous forme de nombre */
int getWord(int * args, int * size, int n) {
    int result = 0, i;

    for (i = 0; i < n; i++) { /* Parcourt chaque champ donné, décale la valeur actuelle du mot vers la gauche et ajoute la valeur du champ */
        result = (result << size[i]) + args[i];
    }

    return result;
}

/* Génère un mot machine pour les instructions de type R */
int getTypeRWord(int opcode, int rs, int rt, int rd, int sa, int function) {
    int args[] = {opcode, rs, rt, rd, sa, function};
    int size[] = {6, 5, 5, 5, 5, 6};

    return getWord(args, size, 6);
}

/* Génère un mot machine pour les instructions de type I */
int getTypeIWord(int opcode, int rs, int rt, int immediate) {
    int args[] = {opcode, rs, rt, immediate};
    int size[] = {6, 5, 5, 16};

    return getWord(args, size, 4);
}

/* Génère un mot machine pour les instructions de type J */
int getTypeJWord(int opcode, int target) {
    int args[] = {opcode, target};
    int size[] = {6, 26};

    return getWord(args, size, 2);
}

/* Détermine le code machine d'une instruction assembleur et l'écrit en hexadécimal dans la chaîne hex
   Retourne 1 si l'instruction existe et doit être écrite, 0 si elle n'existe pas */
int mapInstruction(char *ins, int indexes[4], int lengths[4], char hex[SIZE]) {
    char *name = ins + indexes[0], *names[] = INS_NAMES;

    int arg1 = convertArgument(ins + indexes[1], lengths[1]);
    int arg2 = convertArgument(ins + indexes[2], lengths[2]);
    int arg3 = convertArgument(ins + indexes[3], lengths[3]);

    int (*functions[])(int, int, int) = INS_POINTERS;
    int i = 0, write = 0;
    int result;

    while (i < INS_NUMBER && !write) { /* Parcourt les noms d'instruction disponibles pour trouver une correspondance */
        if (!strncmp(name, names[i], lengths[0])) {
            write = 1;

            result = (functions[i])(arg1, arg2, arg3); /* Exécute la fonction correspondant au nom */
            sprintf(hex, "%.8x", result); /* Écrit le résultat de la traduction en hexadécimal */
        }

        i++;
    }

    return write;
}


/* Execute le code 
Retourne 1 en cas de succès, 0 si une erreur */
int executeProgram(void) {
    int32_t instruction = readMemory(&PROG_MEMORY, PC);
    int8_t special, function;
    memSlot * check = findMemSlot(&PROG_MEMORY, PC);
    int success = 1;

    while (check != NULL) {
        instruction = readMemory(&PROG_MEMORY, PC);
        special = instruction & INS_SPECIAL_MASK;
        function = instruction & INS_FUNCTION_MASK;

        if(special != 0) {
            printf("INS_SPECIAL\n"); 
        } else if(function == 2) {
            printf("regarder le bit R : 1 => ROTR, SRR sinon\n");
        } else {
            printf("INS_FUNCTION\n");
        }
            

        PC += 4;
        check = findMemSlot(&PROG_MEMORY, PC);
    }

    return success;
}


/* Convertit une ligne assembleur en hexadécimal et l'écrit dans la chaîne hex
   Retourne 1 si l'instruction existe, 0 sinon */
int MIPStoHex(char *ins, int n, char hex[SIZE]) {
    int index = wordIndex(ins, n, " \t");
    int length = wordLength(ins + index, n - index, " \t#");
    int i = index + length, j = 1;

    int indexes[4] = {index};
    int lengths[4] = {length};

    while (j < 4 && i < n) { /* Détermine la position et la taille des opérandes dans la ligne */
        index = wordIndex(ins + i, n - i, " \t,(");
        length = wordLength(ins + i + index, n - i - index, " \t,()#");

        indexes[j] = i + index;
        lengths[j] = length;

        i += index + length;
        j++;
    }

    return lengths[0] != 0 ? mapInstruction(ins, indexes, lengths, hex) : 0;
}