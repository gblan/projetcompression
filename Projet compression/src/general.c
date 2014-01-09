#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

/* si le caractere est dans le tableau, alors on retourne sa position
 * sinon on retourne -1 */
int isInTab(char c, char* charTab) {
	int i = 0;

	while (charTab[i] != '\0') {
		if (charTab[i] == c) {
			return i;
		}
		i++;
	}
	return -1;
}

void copyFile(FILE** file, int *intTab, char *charTab) {
	char c;
	int i = 0;
	int positionChar = 0;
	int tailleTab = 0;
	/* Vérifier la taille du fichier avant de l'ouvrir*/
	while ((c = fgetc(*file)) != EOF) {
		printf("%c", c);

		if (isInTab(c, charTab) == -1) {
			intTab = realloc(intTab,sizeof(int)*tailleTab+1);
			charTab = realloc(charTab,sizeof(char)*tailleTab+1);

			intTab[tailleTab] = 1;
			charTab[tailleTab] = c;
			tailleTab++;


		} else {
			positionChar = isInTab(c, charTab);
			intTab[positionChar]++;
		}
	}
	printf("\n");

	for(i=0;i<tailleTab;i++) {
	 printf(" %c    %d\n", charTab[i], intTab[i]);
	}

	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;
}

