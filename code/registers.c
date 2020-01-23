#include <stdio.h>
#include <stdint.h>
#include "registers.h"


/* Initialise tous les registres à 0 */
void initRegisters(void) {
	int i;
	for(i = 0 ; i < REGISTERS_NUMBERS ; i++) {
		REGISTERS[i] = 0;
	}
}


/* Retourne la valeur d'un registre d'index donné. Si l'index est invalide, la valeur -1 est retournée. */
int32_t readRegister(int8_t index) {
	int32_t registerValue = -1;

	if(index > 31 || index < 0) {
		printf("ERREUR : index de registre invalide\n");
	} else {
		registerValue = REGISTERS[index];
	}

	return registerValue;
}


/* Ecrit dans un registre d'index donné une valeur d'entrée. 
Si l'index est invalide ou si on essaie d'écrire dans un registre réservé, la valeur 0 est retournée. 
En cas de succès, la valeur 1 est retournée. */
int writeRegister(int8_t index, int32_t value) {
	int success = 0;

	if(index > 31 || index < 0) {
		printf("ERREUR : index de registre invalide\n");
	} else if(index == 0){
		printf("ERREUR : tentative d'écriture dans le registre 0\n");
	} else {
		REGISTERS[index] = value;
		success = 1;
	}

	return success;
}


/* Affiche la valeur de tous les registres */
void printRegisters(void) {
	int i;

	printf("==================================== REGISTRES =====================================\n");
	printf(" PC    : %8X      HI    : %8X      LO    : %8X", PC, HI, LO);

	for(i = 0 ; i < REGISTERS_NUMBERS ; i++) {
		if (!(i % 4)) printf("\n ");

		printf("R[%02d] : %8X      ", i, REGISTERS[i]);
	}
	printf("\n====================================================================================\n");
}