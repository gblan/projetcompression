/*
 * huffman.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"general.h"

typedef struct elementListe {
	int frequence;
	char caractere;
	struct elementListe* suivant;
	struct noeud* noeudIntermediaire;
} elementListe;

typedef struct arbre {
	struct noeud *racine;
} arbre;

typedef struct noeud {
	char caractere;
	struct noeud *gauche_0;
	struct noeud *droite_1;
} noeud;

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

void createTabProba(float* tabProba, int* tabInt, int tailleTab, int sumTab) {

	int i = 0;

	for (i = 0; i < tailleTab; i++) {
		tabProba[i] = ((float) tabInt[i] / (float) sumTab);
		/* Test*/
		printf("tabProba[%d] = %f , tabInt[%d] = %d \n", i, tabProba[i], i,
				tabInt[i]);
	}
}

void createHuffmanTree() {
	struct noeud racine;
	struct noeud* test = &racine;

	racine.droite_1 = test;
	struct noeud* test2 = NULL;
	test->droite_1 = test2;
}

void createChainedList(elementListe* elemL, char* tabChar, int* tabInt,
		int tabLength) {
	int i;
	struct elementListe* p;
	struct elementListe* nouveau;

	for (i = 0; i < tabLength; i++) {
		nouveau = malloc(1 * sizeof(elementListe));
		nouveau->caractere = tabChar[i];
		nouveau->frequence = tabInt[i];
		nouveau->suivant = elemL;
		nouveau->noeudIntermediaire = NULL;
		elemL = nouveau;
	}

	for (p = elemL; p != NULL; p = p->suivant) {
		printf("%c  %d\n", p->caractere, p->frequence);
	}

}

void insertNewNodeInChainedList(elementListe* elemL) {
	int value;
	struct elementListe* p;
	struct elementListe* pt2;

	struct elementListe* nouveau;
	struct noeud* noeudRacine;
	struct noeud* noeudGauche;
	struct noeud* noeudDroit;

	for (p = elemL; p->suivant != NULL; p = p->suivant) {

		nouveau = malloc(1*sizeof(elementListe));
		value = p->frequence + p->suivant->frequence;
		nouveau->frequence = value;
		nouveau->caractere = '\0';

		for (pt2 = p->suivant; pt2->suivant != NULL; pt2 = pt2->suivant) {

		}

	if (elemL->frequence < value && elemL->suivant->frequence > value) {
		/* Alors on insert à cet endroit */

		/* INSERTION DIFFICILE */
		if(elemL->noeudIntermediaire!=NULL && elemL->suivant->noeudIntermediaire != NULL){

		} else if(elemL->noeudIntermediaire==NULL && elemL->suivant->noeudIntermediaire != NULL){

		} else if(elemL->noeudIntermediaire!=NULL && elemL->suivant->noeudIntermediaire == NULL){

		} else if(elemL->noeudIntermediaire==NULL && elemL->suivant->noeudIntermediaire == NULL){
			/* INSERTION FACILE*/
		}
	}
	}
}

void huffman(FILE** file, int *intTab, char *charTab, float* tabProba,
		char* archiveName) {
	char c;
	int i = 0;
	int positionChar = 0;
	int tailleTab = 0;
	int nbChar;
	FILE* archive;
	FILE** ptArchive = &archive;

	elementListe* elemL = NULL;
	elementListe* p;

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

	/* Creation du tableau de probabilitees */
	nbChar = sumTab(intTab, tailleTab);

	tri(charTab, intTab, tailleTab);

	createChainedList(elemL, charTab, intTab, tailleTab);

	/*tabProba = realloc(tabProba, sizeof(float) * tailleTab + 1);
	 createTabProba(tabProba, intTab, tailleTab, nbChar);*/

	/* Creation de l'archive */
	/*archive = createFile(archiveName);
	 writeFile(ptArchive,"CONTENU BINAIRE");
	 closeFile(ptArchive);*/

	for (p = elemL; p != NULL; p = p->suivant) {
		free(elemL);
	}
	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;
	free(tabProba);
	tabProba = NULL;

}
