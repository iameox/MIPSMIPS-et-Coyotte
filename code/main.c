#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "files.h"

#define MAXLEN 50

int main(int argc, char *argv[]) {
	char *sourceName, *resultName;
	FILE *sourceFile, *resultFile;
	char sourceLine[MAXLEN], resultLine[SIZE];
	int lineSize, write;


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
		sourceFile = openFile(sourceName, "rb");
		resultFile = openFile(resultName, "wb");

		while(!feof(sourceFile)) {
			lineSize = readLine(sourceFile, sourceLine);

			if(lineSize > 0) {
				write = MIPStoHex(sourceLine, lineSize, resultLine);

				if (write) {
					writeLine(resultFile, resultLine);
				}
			}
		}
	}

	closeFile(sourceName, sourceFile);
	closeFile(resultName, resultFile);

    return 1;
}