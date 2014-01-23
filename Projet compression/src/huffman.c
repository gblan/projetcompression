/*
 * huffman.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
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

char *code[256] = { 0 };
char buf[1024];

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

void createChainedList(elementListe** elemL, char charToAdd, int intToAdd) {
	struct elementListe* nouveau;

	nouveau = calloc(1, sizeof(elementListe));
	nouveau->caractere = charToAdd;
	nouveau->frequence = intToAdd;
	nouveau->suivant = *elemL;
	nouveau->noeudIntermediaire = NULL;
	*elemL = nouveau;
}

void deleteTwoFirstElements(elementListe** liste) {
	struct elementListe* elem1;
	struct elementListe* elem2;

	elem1 = *liste;
	*liste = (*liste)->suivant;
	elem1->suivant = NULL;
	free(elem1);
	elem1 = NULL;

	elem2 = *liste;
	*liste = (*liste)->suivant;
	elem2->suivant = NULL;
	free(elem2);
	elem2 = NULL;

}

void linkElementWithChaindList(elementListe** liste, elementListe* element) {
	int valueToAdd = element->frequence;
	struct elementListe* a;

	a = *liste;

	while ((a->suivant != NULL) && (a->suivant->frequence <= valueToAdd)) {
		a = a->suivant;
	}
	element->suivant = a->suivant;
	a->suivant = element;

}

void insertNewNodeInChainedList(elementListe** elemL) {
	int value;
	struct elementListe* p;
	struct elementListe* nouveau;

	struct noeud* noeudRacine;
	struct noeud* noeudGauche;
	struct noeud* noeudDroit;

	p = *elemL;
	value = p->frequence + p->suivant->frequence;
	nouveau = calloc(1, sizeof(elementListe));
	nouveau->frequence = value;
	nouveau->caractere = L'\0';
	nouveau->suivant = NULL;

	noeudRacine = malloc(1 * sizeof(noeud));
	noeudGauche = malloc(1 * sizeof(noeud));
	noeudDroit = malloc(1 * sizeof(noeud));

	/* on cherche le nombre de probas simillaires dans la liste chainée*/
	/* et on ajoute a la fin des mêmes probas*/

	/*if (p->frequence < value && p->suivant->frequence > value) {*/
	/* Alors on insert à cet endroit */

	if (p->noeudIntermediaire == NULL && p->suivant->noeudIntermediaire == NULL) {
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

	noeudRacine->caractere = L'\0';
	noeudRacine->gauche_0 = noeudGauche;
	noeudRacine->droite_1 = noeudDroit;
	/*}*/

	nouveau->noeudIntermediaire = noeudRacine;

	printf("caractere dans noeud : gauche : %lc  droit : %lc \n",
			noeudRacine->gauche_0->caractere, noeudRacine->droite_1->caractere);

	/* Liaison de l'element nouveau avec la liste chainée*/
	linkElementWithChaindList(elemL, nouveau);

	/* Suppression des 2 premiers elements avec un free*/
	deleteTwoFirstElements(elemL);

}

void prefixeHuffmanTree(noeud *n, char *s, int len) {
	static char *out = buf;
	int tailleCode = 0;

	if (n->caractere != '\0') {
		s[len] = 0;
		strcpy(out, s);
		tailleCode = strlen(out);
		code[n->caractere] = out;
		out += len + 1;
		return;
	}

	s[len] = '0';
	prefixeHuffmanTree(n->gauche_0, s, len + 1);
	s[len] = '1';
	prefixeHuffmanTree(n->droite_1, s, len + 1);
}

void huffman(FILE** file, int *intTab, char *charTab, char* archiveName,
		FILE** ptFileOutput, char* fileInputName) {
	char c;
	int i = 0;
	int positionChar = 0;
	int tailleTab = 0;
	int test = 0;
	char* tabChar;
	char* fileOutputName;

	elementListe* elemL = NULL;
	elementListe** ptListe = &elemL;
	elementListe* a = NULL;

	/* Vérifier la taille du fichier avant de l'ouvrir*/
	while ((c = fgetwc(*file)) != WEOF) {
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

	/* Affichage tableau d'apparition */
	for (i = 0; i < tailleTab; i++) {
		printf("1-%c   %d\n", charTab[i], intTab[i]);
	}

	tri(charTab, intTab, tailleTab);

	for (i = 0; i < tailleTab; i++) {
		createChainedList(ptListe, charTab[i], intTab[i]);
	}

	/* Affichage liste chainée triée */
	for (a = *ptListe; a != NULL; a = a->suivant) {
		printf("2-%c   %d\n", a->caractere, a->frequence);
	}
	printf("\n");

	while ((*ptListe)->suivant != NULL) {
		insertNewNodeInChainedList(ptListe);
	}
	/* La liste ne contient plus qu'un seul element qui contiend l'arbre entier */

	tabChar = malloc(1 * sizeof(char*));

	/* codage*/
	prefixeHuffmanTree(elemL->noeudIntermediaire, tabChar, 0);

	/* affichage caractères codés */
	for (i = 0; i < 256; i++) {
		if (code[i])
			printf("'%c': %s\n", i, code[i]);
	}

	/*Ecriture de la taille de la table des fréquences */
	fileOutputName = calloc((8+strlen(fileInputName)),sizeof(char));
	fileOutputName = createBinaryFile(fileInputName, ptFileOutput, archiveName);

	openFile(fileOutputName, ptFileOutput, "ab");
	fwrite(&tailleTab, 2, 1, *ptFileOutput);

	closeFile(ptFileOutput);


	/* Creation de l'archive */
	/*archive = createFile(archiveName);
	 writeFile(ptArchive,"CONTENU BINAIRE");
	 closeFile(ptArchive);*/

	free(elemL);
	printf("\n");
	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;

}
