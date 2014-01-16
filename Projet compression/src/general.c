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

void bubbleSort(int min, int max, char* charTab, int* tabInt) {
	int bool, i, tmp;
	int n = max - 1;
	char ctmp;

	/* on fait des permutations, jusqu'a ce qu'on ait effectué un parcours du tableau sans permutation*/
	do {
		bool = 0;
		for (i = min; i < max; i++) {
			if (tabInt[i] < tabInt[i + 1]) {
				tmp = tabInt[i + 1];
				tabInt[i + 1] = tabInt[i];
				tabInt[i] = tmp;
				ctmp = charTab[i + 1];
				charTab[i + 1] = charTab[i];
				charTab[i] = ctmp;

				bool = 1;
			}
		}
		n--;
	} while (bool != 0);
}

void bubbleSortchar(int min, int max, char* charTab, int* tabInt) {
	int bool, i, tmp;
	int n = max - 1;
	char ctmp;

	/* on fait des permutations, jusqu'a ce qu'on ait effectué un parcours du tableau sans permutation*/
	do {
		bool = 0;
		for (i = min; i < max; i++) {
			if (charTab[i] < charTab[i + 1]) {
				tmp = tabInt[i + 1];
				tabInt[i + 1] = tabInt[i];
				tabInt[i] = tmp;
				ctmp = charTab[i + 1];
				charTab[i + 1] = charTab[i];
				charTab[i] = ctmp;

				bool = 1;
			}
		}
		n--;
	} while (bool != 0);
}

void tri(char* charTab, int* intTab, int tabLength) {
	int i, j = 0;
	bubbleSort(0, tabLength, charTab, intTab);

	for (i = 0; i < tabLength; i++) {
		j = 0;
		if (intTab[i] == intTab[i + 1]) {
			j = i + 1;
			while (intTab[i] == intTab[j + 1]) {
				j++;
			}
			bubbleSortchar(i, j, charTab, intTab);
		}
	}
}
