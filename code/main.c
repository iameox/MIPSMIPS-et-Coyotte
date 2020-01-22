#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "files.h"
#include "memory.h"
#include "registers.h"

int main(int argc, char *argv[]) {
    FILE *sourceFile, *resultFile;
    char *sourceName = NULL, *resultName = NULL;
    char sourceLine[MAXLEN];
    int i = 0, step_mode = 0, lineSize;
    int32_t instructionValue;
    char temp;

    for (i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-pas", 4)) {
            printf("Mode pas à pas activé.\n");
            step_mode = 1;

        } else if (sourceName == NULL) {
            sourceName = argv[i];
        
        } else {
            resultName = argv[i];
        }
    }

    if (sourceName == NULL) {
        if (step_mode) {
            printf("Arguments insuffisants.\nUsage : ./main [nom fichier source] [nom fichier résultat] [-pas]\n");

        } else {
            // MODE INTERACTIF
        	printf("MODE INTERACTIF\n");
        	sourceLine[0] = 0;
        	while(strncmp(sourceLine,"exit",4) && strncmp(sourceLine,"EXIT",4)) {
        		printf("Entrez une ligne de commande :\n");
        		scanf("%c",&temp); // temp statement to clear buffer
                scanf("%[^\n]",sourceLine);
        		printf("check = %s\n", sourceLine);

        		instructionValue = MIPStoHex(sourceLine, MAXLEN);

                if (instructionValue != 0xffffffff) {
                    executeLine(instructionValue); // A CODER ou alors utiliser executeProgramm avec une mémoire de prog à 1 seule instruction
                }

        	}
        	
        }

    } else {
        if (resultName == NULL) {
            printf("Nom du fichier résultat non trouvé : mis dans \"../tests/out.s\" par défaut\n");
            resultName = "tests/out/out.s";
        }


        sourceFile = openFile(sourceName, "rb");
        resultFile = openFile(resultName, "wb");

        /* LECTURE DE L'ASSEMBLEUR ET ECRITURE DU CODE MACHINE */
        while (!feof(sourceFile)) {
            lineSize = readLine(sourceFile, sourceLine);

            if (lineSize > 0) {
                instructionValue = MIPStoHex(sourceLine, lineSize);

                if (instructionValue != 0xffffffff) {
                    writeLine(resultFile, instructionValue);
                    writeMemory(&PROG_MEMORY, PC, instructionValue); /* Ecrit dans la mémoire de programme */
                }
            }
        }
        writeMemory(&PROG_MEMORY, PC, 0xffffffff); /* écriture d'une "sentinelle" pour la mémoire de programme*/

        closeFile(sourceName, sourceFile);
        closeFile(resultName, resultFile);

        printf("EXECUTION DU PROGRAMME\n");
        executeProgram();

    }

    return 1;
}