#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "files.h"

#define MAXLEN 50

int main(int argc, char *argv[]) {
	char *sourceName, *resultName;
	FILE *sourceFile, *resultFile;
	char c, *sourceLine = malloc(MAXLEN*sizeof(char)), resultLine[SIZE];
	int i;


	if(argc <= 1) {
		printf("Arguments insuffisants.\nUsage : ./main [nom fichier source] [nom fichier résultat]\n");
	} else { 
		if (argc == 2) {
			printf("Nom du fichier résultat non trouvé : mis dans \"out.s\" par défaut\n");
			resultName = "out.s";
		} else {
			resultName = argv[2];
		}
		
		sourceName = argv[1];
		sourceFile = ouvreOuQuitte(sourceName, "rb");
		resultFile = ouvreOuQuitte(resultName, "wb");

		while(!feof(sourceFile)) {
			i = 0;
			
			do {
				c = fgetc(sourceFile);
				sourceLine[i] = c;
				i++;
			} while(c != '\n' && !feof(sourceFile));
			sourceLine[i-1] = 0; /*On écrase le newline par une sentinelle pour créer la ligne*/

			printf("**%s**\n", sourceLine);

			if(strlen(sourceLine) > 0) {
				MIPStoHex(sourceLine, resultLine);

				for(i = 0 ; i < SIZE ; i++) {
                    if (i % 4 == 0 && i != 0) fputc(' ', resultFile);
					fputc(resultLine[i], resultFile);
				}

                fputc('\n', resultFile);
			}
		}
	}

    return 1;
}