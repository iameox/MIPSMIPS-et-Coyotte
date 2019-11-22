#include <stdio.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	char *sourceName, *resultName;
	FILE *sourceFile, *resultFile;


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
		sourceFile = ouvreOuQuitte(resultName, "wb");
	}

    return 1;
}