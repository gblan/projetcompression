#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

int checkExtention(char* fileName) {
	int result = 0;
	printf("filename : %s\n", fileName);
	return result;
}

int fileOpen(char* filename, FILE** fichier) {
	*fichier = fopen(filename, "r+");

	if (*fichier != NULL) {
		printf("Open OK\n");
		return 0;

	} else {
		printf("Open KO\n");
		return -1;
	}
}

void fileClose(FILE** fichier) {
	if (fichier != NULL) {
		fclose(*fichier);
		printf("Close OK\n");
	} else {
		printf("Close KO\n");
	}
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
