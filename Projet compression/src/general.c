#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

char* checkFileName(char* fileName, int longueurChaine) {
	char* result = NULL;
	int i;

	for (i = 0; i < longueurChaine; i++) {
		if (fileName[i] != '.') {
			result[i] = fileName[i];
		} else {
			return result;
		}
	}
	return result;
}

int openFile(char* fileName, FILE** fichier) {
	*fichier = fopen(fileName, "r+");

	if (*fichier != NULL) {
		printf("Open OK\n");
		return 0;

	} else {
		printf("Open KO\n");
		return -1;
	}
}

void closeFile(FILE** fichier) {
	if (fichier != NULL) {
		fclose(*fichier);
		printf("Close OK\n");
	} else {
		printf("Close KO\n");
	}
}

FILE* createFile(char* fileName) {
	FILE* tmp = NULL;

	if (fopen(fileName, "r") == NULL) {
		tmp = fopen(fileName, "a");
		return tmp;
	} else {
		printf("Le fichier existe deja");
		return tmp;
	}
}

void writeFile(FILE** fichier, char* stringToWrite) {
	fprintf(*fichier, stringToWrite);
}

void readFile(FILE** file) {
	char str[TAILLE_MAX] = "";
	/* Vérifier la taille du fichier avant de l'ouvrir*/
	while (fgets(str, TAILLE_MAX, *file) != NULL) {
		printf("%s", str);
	}
	printf("\n");
}

void readFilechar(FILE** file) {
	int c;
	while ((c = fgetc(*file)) != EOF) {
		printf("%c", (char) c);
	}
	printf("\n");
}
