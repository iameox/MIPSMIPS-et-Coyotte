#include <stdio.h>
#include <stdlib.h>
#include "files.h"

/*Fonction qui ouvre un fichier ou quitte avec un message d'erreur si il y a un problème*/
FILE * openFile(const char *nom, const char *mode){
	FILE * fd = fopen(nom,mode);

	if(NULL == fd){
		fprintf(stderr,"Erreur ouverture fichier %s :\n", nom);
		perror("");
		fprintf(stderr,"ARRET\n");
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
