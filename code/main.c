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

    initProcessor();

    /* Récupération des arguments de la commande */
    for (i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-pas", 4)) { /* -pas peut être placé n'importe où */
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
            printf("ERREUR : arguments insuffisants.\nUsage : ./main [nom fichier source] [nom fichier résultat] [-pas]\n");

        } else {
        	printf("Mode interactif activé.\n");
        	sourceLine[0] = 0;

        	while(strncmp(sourceLine,"exit",4) && strncmp(sourceLine,"EXIT",4)) { /* Entrer "exit" ou "EXIT" permet de sortir. */
        		printf("Entrez une instruction MIPS :\n");
                scanf("%20[^\n]",sourceLine);
                scanf("%c", &temp); /* Nécessaire pour éviter de boucler à l'infini */

        		instructionValue = MIPStoHex(sourceLine, MAXLEN);

                if (instructionValue != NO_INS) {
                    executeLine(instructionValue, 1);
                    printStatus();
                }

        	}
        	
        }

    } else { /* Cas où un fichier source est fourni */
        if (resultName == NULL) {
            printf("Nom du fichier résultat non trouvé : mis dans \"../tests/out.s\" par défaut\n");
            resultName = "tests/out/out.s";
        }

        sourceFile = openFile(sourceName, "rb");
        resultFile = openFile(resultName, "wb");

        /* Lecture de l'assembleur et écriture du code machine */
        while (!feof(sourceFile)) {
            lineSize = readLine(sourceFile, sourceLine);

            if (lineSize > 0) {
                instructionValue = MIPStoHex(sourceLine, lineSize);

                if (instructionValue != NO_INS) {
                    writeLine(resultFile, instructionValue);
                    writeMemory(&PROG_MEMORY, PC, instructionValue); /* Ecrit dans la mémoire de programme */
                    PC += 4;
                }
            }
        }
        writeMemory(&PROG_MEMORY, PC, NO_INS); /* Écriture d'une "sentinelle" en fin de mémoire de programme (les emplacements nuls ne sont pas stockés dans la liste chaînée) */

        /* Fermeture des fichiers */
        closeFile(sourceName, sourceFile);
        closeFile(resultName, resultFile);

        /* Exécution du programme à partir de la mémoire de programme */
        executeProgram(step_mode);
    }

    return 1;
}