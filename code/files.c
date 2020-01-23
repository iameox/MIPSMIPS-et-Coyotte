#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "functions.h"

/* Ouvre un fichier ou quitte avec un message d'erreur s'il y a un problème */
FILE *openFile(const char *name, const char *mode) {
	FILE * fd = fopen(name, mode);

	if (fd == NULL) {
		fprintf(stderr, "Erreur lors de l'ouverture fichier %s :\n", name);
		perror("");
		exit(EXIT_FAILURE);
	}
	return fd;
}

/* Ferme un fichier ou quitte avec un message d'erreur s'il y a un problème */
void closeFile(const char *name, FILE *fd) {
	if (fclose(fd) == EOF) {
		fprintf(stderr, "Erreur lors de la fermeture du fichier %s :", name);
		perror("");
		exit(EXIT_FAILURE);
	}
}

/* Lit une ligne d'un fichier */
int readLine(FILE *sourceFile, char *sourceLine) {
	int i = 0;
	char c = fgetc(sourceFile);
	
	while (i < MAXLEN && c != '\n' && c != '\r' && !feof(sourceFile)) {
		sourceLine[i] = c;

		c = fgetc(sourceFile);
		i++;
	}

	return i;
}

/* Écrit une ligne à la fin d'un fichier */
void writeLine(FILE *resultFile, int32_t resultLine) {
	int i;
	char hex[SIZE];
	
	sprintf(hex, "%08x", resultLine);
	
	for(i = 0; i < SIZE; i++) {
    	if (i % 4 == 0 && i != 0) fputc(' ', resultFile);
		fputc(hex[i], resultFile);
	}

	fputc('\n', resultFile);
}