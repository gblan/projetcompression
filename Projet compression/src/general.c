#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TAILLE_MAX 1000

int openFile(char* filename, FILE** fichier, char* mode) {
	*fichier = fopen(filename, mode);

	if (*fichier != NULL) {
		/*printf("Open \"%s\" OK\n", filename);*/
		return 0;

	} else {
		printf("Open \"%s\" KO\n", filename);
		return -1;
	}
}

void closeFile(FILE** fichier) {

	if (fichier != NULL) {
		fclose(*fichier);
		/*printf("Close OK\n");*/
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

void bubbleSort(int min, int max, char* charTab, int* tabInt) {
	int bool, i, tmp;
	int n = max - 1;
	char ctmp;

	/* on fait des permutations, jusqu'a ce qu'on ait effectué un parcours du tableau sans permutation*/
	do {
		bool = 0;
		for (i = min; i < max - 1; i++) {

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
		for (i = min; i < max - 1; i++) {

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

char* createBinaryFile(char* fileName, FILE** ptFileOutput, char* suffixe) {
	int longueurNomFichier = 0;
	char* fileOutputname = NULL;

	longueurNomFichier = strlen(fileName);
	fileOutputname = calloc((longueurNomFichier + 8), sizeof(char));
	if (fileOutputname == NULL) {

		printf("Erreur d'allocation archiveName.\n");
		exit(-1);
	}
	strcat(fileOutputname, fileName);
	strcat(fileOutputname, suffixe);
	openFile(fileOutputname, ptFileOutput, "ab");
	closeFile(ptFileOutput);

	return fileOutputname;
}

int binaryToDecimal(char subString[7]) {
	int binary = atoi(subString);
	int result = 0, i = 0, rem;

	while (binary != 0) {

		rem = binary % 10;
		binary /= 10;
		result += rem * pow(2, i);
		++i;

	}
	return result;
}

void decimalToBinary(int decimal, char* octet) {
	int rem, i = 1, binary = 0, charlen;
	char tmp[7];

	while (decimal != 0) {

		rem = decimal % 2;
		decimal /= 2;
		binary += rem * i;
		i *= 10;
	}

	sprintf(octet, "%d", binary);
	charlen = strlen(octet);

	/*on ajoute des 0 pour completer l'octet*/
	while (charlen < 7) {

		strcpy(tmp, octet);
		for (i = 0; i < (7 - charlen); i++) {

			octet[i] = '0';
		}
		for (i = (7 - charlen); i < 7; i++) {

			octet[i] = '\0';
		}
		strcat(octet, tmp);
		charlen = strlen(octet);
	}
}
