#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 1000

int choiceCompression() {
	int result = 0;

	do {
		printf("Wich compression did you want to use :\n");
		printf("\t1 - Huffman\n\t2 - Lempel-Ziv-Welch\n");
		scanf("%d", &result);
		printf("### %d ###", result);
	} while (result != 1 && result != 2);

	return result;
}

int checkExtention(char* fileName) {
	int result = 0;
	return result;
}

void fileOpen(char* filename, FILE** fichier) {
	*fichier = fopen(filename, "r+");

	if (*fichier != NULL) {
		printf("Open OK\n");

	} else {
		printf("Open KO\n");
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

int isInTab(char c, char* charTab) {
	int i = 0;

	while (charTab[i] != '\0') {
		if (charTab[i] == c)

		{
			return i;
		}
		i++;
	}
	return -1;
}

void copyFile(FILE** file, int *intTab, char *charTab) {
	char c;
	int i;
	int tailleTab;
	/* Vérifier la taille du fichier avant de l'ouvrir*/
	while ((c = fgetc(*file)) != EOF) {
		printf("%c", c);

		if (isInTab(c, charTab) == -1) {
			/* realloc */

			intTab[tailleTab] = 1;
			charTab[tailleTab] = c;
		} else {
			i = isInTab(c, charTab);
			intTab[i]++;
		}

	}
	printf("\n");
}

