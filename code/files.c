#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "functions.h"

/*Fonction qui ouvre un fichier ou quitte avec un message d'erreur si il y a un problème*/
FILE * openFile(const char *nom, const char *mode){
	FILE * fd = fopen(nom,mode);

	if(NULL == fd){
		fprintf(stderr,"Erreur ouverture fichier %s :\n", nom);
		perror("");
		exit(EXIT_FAILURE);
	}
	return fd;
}

/*Fonction qui ferme un fichier ou quitte avec un message d'erreur si il y a un problème*/
void closeFile(const char *nom, FILE * fd){
	if(EOF == fclose(fd)){
		fprintf(stderr,"Erreur fermeture du fichier %s :", nom);
		perror("");
		exit(EXIT_FAILURE);
	}
}


int readLine(FILE * sourceFile, char *sourceLine) {
	int i = 0;
	char c = fgetc(sourceFile);
	
	while (c != '\n' && c != '\r' && !feof(sourceFile)) {
		sourceLine[i] = c;

		c = fgetc(sourceFile);
		i++;
	}

	return i;
}

void writeLine(FILE * resultFile, char * resultLine) {
	int i;
	for(i = 0 ; i < SIZE ; i++) {
    	if (i % 4 == 0 && i != 0) fputc(' ', resultFile);
		fputc(resultLine[i], resultFile);
	}

	fputc('\n', resultFile);
}