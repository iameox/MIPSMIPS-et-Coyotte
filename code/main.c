#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "files.h"

int main(int argc, char *argv[]) {
    FILE *sourceFile, *resultFile;
    char *sourceName = NULL, *resultName = NULL;
    char sourceLine[MAXLEN], resultLine[SIZE];
    int i = 0, step_mode = 0, lineSize, write;

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
                write = MIPStoHex(sourceLine, lineSize, resultLine);

                if (write) {
                    writeLine(resultFile, resultLine);
                }
            }
        }

        closeFile(sourceName, sourceFile);
        closeFile(resultName, resultFile);

        printf("EXECUTION DU PROGRAMME\n");
        executeProgram();

    }

    return 1;
}