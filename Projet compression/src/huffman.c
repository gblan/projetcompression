/*
 * huffman.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct noeud {
	unsigned char key;
	struct noeud *gauche;
	struct noeud *droite;
} node;

typedef struct table {
	unsigned char character;
	unsigned int nbApp;
	struct table *next;
} table;

/*void huffmanTree() {
 node;
 }*/

void huffmanCompression(char *path) {

}

void openFileToCompress(char *path) {
	FILE* fichier = NULL;
	char* read = NULL;

	fichier = fopen(path, "r");

	if (fichier != NULL) {
		while (fgets(read, 1000, fichier) != NULL) {
			printf("%s", read);
		}
		fclose(fichier);
	}

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

int sumTab(int* tabInt, int tailleTab) {

	int i = 0, result = 0;

	for (i = 0; i < tailleTab; i++) {
		result += tabInt[i];
	}
	return result;
}

void creatTabProba(float* tabProba, int* tabInt, int tailleTab, int sumTab) {

	int i = 0;

	for (i = 0; i < tailleTab; i++) {
		tabProba[i] = ((float) tabInt[i] / (float) sumTab);
		/* Test*/
		printf("tabProba[%d] = %f , tabInt[%d] = %d \n",i,tabProba[i],i,tabInt[i]);
	}
}

void huffman(FILE** file, int *intTab, char *charTab, float* tabProba) {
	char c;
	int i = 0;
	int positionChar = 0;
	int tailleTab = 0;
	int nbChar;
	/* Vérifier la taille du fichier avant de l'ouvrir*/
	while ((c = fgetc(*file)) != EOF) {
		printf("%c", c);

		if (isInTab(c, charTab) == -1) {
			intTab = realloc(intTab, sizeof(int) * tailleTab + 1);
			charTab = realloc(charTab, sizeof(char) * tailleTab + 1);

			intTab[tailleTab] = 1;
			charTab[tailleTab] = c;
			tailleTab++;

		} else {
			positionChar = isInTab(c, charTab);
			intTab[positionChar]++;
		}
	}
	printf("\n");

	/* Affichage tableau d'apparition*/
	for (i = 0; i < tailleTab; i++) {
		printf(" %c    %d\n", charTab[i], intTab[i]);
	}

	/* Affichage tableau de probabilite */
	nbChar = sumTab(intTab, tailleTab);

	creatTabProba(tabProba, intTab, tailleTab, nbChar);

	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;
}
