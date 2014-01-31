#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
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

int openFile(char* filename, FILE** fichier, char* mode) {
	*fichier = fopen(filename, mode);

	if (*fichier != NULL) {
		/*printf("Open \"%s\" OK\n", filename);*/
		return 0;

	} else {
		printf("Open \"%s\" KO\n", filename);
		exit(-1);
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

void writeFile(FILE** fichier, char* stringToWrite) {
	fprintf(*fichier,"%s", stringToWrite);
}

void readFile(FILE** file) {
	char str[TAILLE_MAX] = "";
	/* V�rifier la taille du fichier avant de l'ouvrir*/
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

	/* on fait des permutations, jusqu'a ce qu'on ait effectu� un parcours du tableau sans permutation*/
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

	/* on fait des permutations, jusqu'a ce qu'on ait effectu� un parcours du tableau sans permutation*/
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

char* createBinaryFile(char* fileName, FILE** ptFileOutput, char* archiveName) {
	int longueurNomFichier = 0;

	longueurNomFichier = strlen(fileName);
	archiveName = calloc((longueurNomFichier + 8), sizeof(char));
	if (archiveName == NULL) {
		printf("Erreur d'allocation archiveName.\n");
		exit(-1);
	}
	strcat(archiveName, fileName);
	strcat(archiveName, ".huffman");
	openFile(archiveName, ptFileOutput, "ab");
	closeFile(ptFileOutput);

	return archiveName;
}

char* createDecodedFile(char* fileName, FILE** ptFileOutput,
		char* decodedFileName) {
	int longueurNomFichier = 0;

	longueurNomFichier = strlen(fileName);
	decodedFileName = calloc((longueurNomFichier + 8), sizeof(char));
	if (decodedFileName == NULL) {
		printf("Erreur d'allocation decodedFileName.\n");
		exit(-1);
	}
	strcat(decodedFileName, fileName);
	strcat(decodedFileName, ".decoded");
	openFile(decodedFileName, ptFileOutput, "ab");
	closeFile(ptFileOutput);

	return decodedFileName;
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

	/*for (i = 0; i < 7; i++) {
	 if (octet[i] == '-') {
	 octet[i] = '1';
	 }
	 }*/
}
