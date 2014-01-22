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

typedef struct liste{
	int nbElements;
	struct elementListe* tete;
} liste;

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
		printf("2-%c   %d\n", p->caractere, p->frequence);
	}
}

void deleteTwoFirstElements(elementListe* liste) {
	struct elementListe* elem1 = NULL;

	/*elem1 = liste->suivant;
	liste= liste->suivant;

	elem1->suivant = NULL;
*/	free(elem1);

	elem1 = NULL;


	/*for (p = liste; p != NULL; p = p->tete->suivant) {
		printf("3-%c   %d\n", p->tete->caractere, p->tete->frequence);
	}*/
}

void linkElementWithChaindList(elementListe* elemL, elementListe* element) {

}

void insertNewNodeInChainedList(elementListe* elemL) {
	int value;
	struct elementListe* p;
	struct elementListe* nouveau;

	struct noeud* noeudRacine = NULL;
	struct noeud* noeudGauche = NULL;
	struct noeud* noeudDroit = NULL;

	p = elemL;
	value = p->frequence + p->suivant->frequence;
	nouveau = malloc(1 * sizeof(elementListe));
	nouveau->frequence = value;
	nouveau->caractere = '\0';
	nouveau->suivant = NULL;
	noeudRacine = malloc(1 * sizeof(noeud));
	noeudGauche = malloc(1 * sizeof(noeud));
	noeudDroit = malloc(1 * sizeof(noeud));

	/* on cherche le nombre de probas simillaires dans la liste chainée*/
	/* et on ajoute a la fin des mêmes probas*/

	if (p->frequence < value && p->suivant->frequence > value) {
		/* Alors on insert à cet endroit */

		if (p->noeudIntermediaire == NULL
				&& p->suivant->noeudIntermediaire == NULL) {
			/* INSERTION FACILE*/
			noeudGauche->caractere = p->caractere;
			noeudGauche->droite_1 = NULL;
			noeudGauche->gauche_0 = NULL;
			noeudDroit->caractere = p->suivant->caractere;
			noeudDroit->droite_1 = NULL;
			noeudDroit->gauche_0 = NULL;

		} else if (p->noeudIntermediaire == NULL
				&& p->suivant->noeudIntermediaire != NULL) {
			/* INSERTION UN PEU DURE*/
			noeudGauche->caractere = p->caractere;
			noeudGauche->droite_1 = NULL;
			noeudGauche->gauche_0 = NULL;
			noeudDroit = p->suivant->noeudIntermediaire;

		} else if (p->noeudIntermediaire != NULL
				&& p->suivant->noeudIntermediaire == NULL) {
			/* INSERTION UN PEU DURE ENCORE*/
			noeudGauche = p->noeudIntermediaire;
			noeudDroit->caractere = p->suivant->caractere;
			noeudDroit->droite_1 = NULL;
			noeudDroit->gauche_0 = NULL;

		} else if (p->noeudIntermediaire != NULL
				&& p->suivant->noeudIntermediaire != NULL) {
			/* INSERTION DIFFICILE */
			noeudGauche = p->noeudIntermediaire;
			noeudDroit = p->suivant->noeudIntermediaire;
		}

		noeudRacine->caractere = '\0';
		noeudRacine->gauche_0 = noeudGauche;
		noeudRacine->droite_1 = noeudDroit;
	}

	nouveau->noeudIntermediaire = noeudRacine;
	/* Liaison de l'element nouveau avec la liste chainée*/
	linkElementWithChaindList(elemL, nouveau);

	/* Suppression des 2 premiers elements avec un free*/
	deleteTwoFirstElements(p);

}

/* non testé*/
void visiteNoeud(noeud* huffmanTree, char* tabChar, char** tabHuffCode,
		char* currentCode, int tailleTab) {

	tabChar = realloc(tabChar, tailleTab * sizeof(char));
	tabHuffCode = realloc(tabHuffCode, tailleTab * sizeof(char*));

	if (huffmanTree->caractere != '\0') {
		tabChar[tailleTab] = huffmanTree->caractere;
		tabHuffCode[tailleTab] = currentCode;
		tailleTab++;
	}
}

/* non testé */
void infixeHuffmanTree(noeud* huffmanTree, char* tabChar, char** tabHuffCode,
		char* currentCode, int tailleTab) {

	if ((huffmanTree->gauche_0) != NULL) {
		currentCode = realloc(currentCode, 1 * sizeof(char));
		currentCode = strcat(currentCode, "0");
		infixeHuffmanTree(huffmanTree->gauche_0, tabChar, tabHuffCode,
				currentCode, tailleTab);
	}
	if ((huffmanTree->droite_1) != NULL) {
		currentCode = realloc(currentCode, 1 * sizeof(char));
		currentCode = strcat(currentCode, "1");
		infixeHuffmanTree(huffmanTree->droite_1, tabChar, tabHuffCode,
				currentCode, tailleTab);
	}
	visiteNoeud(huffmanTree, tabChar, tabHuffCode, currentCode, tailleTab);
}

void huffman(FILE** file, int *intTab, char *charTab, char* archiveName) {
	char c;
	int i = 0;
	int positionChar = 0;
	int tailleTab = 0;
	int nbChar;
	char* tabChar;
	char** tabHuffCode;
	char* currentCode;

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
		printf("1-%c   %d\n", charTab[i], intTab[i]);
	}

	/* Creation du tableau de probabilitees */
	nbChar = sumTab(intTab, tailleTab);

	tri(charTab, intTab, tailleTab);
	printf("\n");

	createChainedList(elemL, charTab, intTab, tailleTab);
	printf("\n");

	/* TODO A CORRIGER */
	deleteTwoFirstElements(elemL);

	/*while (elemL->suivant != NULL) {
	 insertNewNodeInChainedList(elemL);
	 }*/

	tabChar = malloc(1 * sizeof(char));
	currentCode = malloc(1 * sizeof(char));
	tabHuffCode = malloc(1 * sizeof(char*));
	/*
	 infixeHuffmanTree(elemL->noeudIntermediaire,tabChar, tabHuffCode, currentCode, 0);
	 */
	/* free tout ça */

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

}
