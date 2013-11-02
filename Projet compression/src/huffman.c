/*
 * huffman.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	unsigned char key;
	struct node *left;
	struct node *right;
} node;

typedef struct table {
	unsigned char character;
	unsigned int nbApp;
	struct table *next;
} table;

void huffmanTree() {
	node;
}

void openFileToCompress(char *path) {
	FILE* fichier = NULL;
	fichier = fopen(path, "r");
	char* read;

	if (fichier != NULL) {
		while (fgets(read, 1000, fichier) != NULL) {
			printf("%s", read);
		}
		fclose(fichier);
	}

}

void tableAppearance(char *str, int *tabApp, char *tabChar) {
	/*création de la table d'apparence a partir du fichier d'entrée*/
	int i = 0;
	int j = 0;
	int strLength = strlen(str);
	char c;
	while (c != '\0') {
		c = str[i];
		/*if(tabChar[0][j]==c){
		 } else {
		 }*/
	}
}

void huffmanTableSort(int *tabApp, char *tabChar) {
	/*tri de la table de probabilité*/

}

void printTabAppearance(int **tab, int a) {
	/* affichage de la table de correspondance caractère/nombre*/
}
