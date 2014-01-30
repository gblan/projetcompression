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

typedef struct elementCompression {
	int frequence;
	char caractere;
} elementCompression;

typedef struct arbre {
	struct noeud *racine;
} arbre;

typedef struct noeud {
	char caractere;
	struct noeud *gauche_0;
	struct noeud *droite_1;
} noeud;

const char *code[256] = { 0 };
char buf[1024];
int tailleFileInput = 0;
int tailleFileOutput = 0;

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

	if (charToAdd != '\0') {
		nouveau = calloc(1, sizeof(elementListe));
		if (nouveau == NULL) {
			printf("Erreur d'allocation nouveau.\n");
			exit(-1);
		}
		nouveau->caractere = charToAdd;
		nouveau->frequence = intToAdd;
		nouveau->suivant = *elemL;
		nouveau->noeudIntermediaire = NULL;
		*elemL = nouveau;
	}
}

void deleteTwoFirstElements(elementListe** liste) {
	struct elementListe* elem;
	int i;
	for (i = 0; i < 2; i++) {
		elem = *liste;
		*liste = (*liste)->suivant;
		elem->suivant = NULL;
		free(elem);
		elem = NULL;
	}

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
	if (nouveau == NULL) {
		printf("Erreur d'allocation nouveau noeud.\n");
		exit(-1);
	}
	nouveau->frequence = value;
	nouveau->caractere = L'\0';
	nouveau->suivant = NULL;

	noeudRacine = malloc(1 * sizeof(noeud));
	noeudGauche = malloc(1 * sizeof(noeud));
	noeudDroit = malloc(1 * sizeof(noeud));
	if ((noeudRacine == NULL) || (noeudGauche == NULL)
			|| (noeudDroit == NULL)) {
		printf("Erreur d'allocation construction arbre.\n");
		exit(-1);
	}

	/* on cherche le nombre de probas simillaires dans la liste chain�e*/
	/* et on ajoute a la fin des m�mes probas*/

	/*if (p->frequence < value && p->suivant->frequence > value) {*/
	/* Alors on insert � cet endroit */

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

	/*printf("caractere dans noeud : gauche : %lc  droit : %lc \n",
	 noeudRacine->gauche_0->caractere, noeudRacine->droite_1->caractere);*/

	/* Liaison de l'element nouveau avec la liste chain�e*/
	linkElementWithChaindList(elemL, nouveau);

	/* Suppression des 2 premiers elements avec un free*/
	deleteTwoFirstElements(elemL);

}

void prefixeHuffmanTree(noeud *n, char *s, int len) {
	static char *out = buf;
	/*int tailleCode = 0;*/

	if (n->caractere != '\0') {
		s[len] = 0;
		strcpy(out, s);
		/*tailleCode = strlen(out);*/
		code[(int) n->caractere] = out;
		out += len + 1;
		return;
	}

	s[len] = '0';
	if (n->gauche_0 != NULL) {
		prefixeHuffmanTree(n->gauche_0, s, len + 1);
	}
	s[len] = '1';
	if (n->droite_1 != NULL) {
		prefixeHuffmanTree(n->droite_1, s, len + 1);
	}
}

void freeHuffmanTree(noeud *n) {

	if (n->gauche_0 != NULL) {
		freeHuffmanTree(n->gauche_0);
	}
	if (n->droite_1 != NULL) {
		freeHuffmanTree(n->droite_1);
	}
	n->droite_1 = NULL;
	n->gauche_0 = NULL;
	free(n);
}

void huffman(FILE** file, FILE** ptFileOutput, char* fileInputName) {
	char c;
	int i = 0;
	int positionChar = 0;
	int tailleTab = 0;
	int tailleCode = 0;
	int currentChar = 0;
	char* tabChar;
	char* fileOutputName;
	int* intTab;
	char* charTab;
	char* archiveName = NULL;
	char* bufferCode;
	char charTemp[7];
	elementListe* elemL = NULL;
	elementListe** ptListe = &elemL;
	elementListe* a = NULL;

	intTab = calloc(1, sizeof(int));
	charTab = calloc(1, sizeof(char));

	if ((intTab == NULL) || (charTab == NULL)) {
		printf("Erreur d'allocation intTab ou  charTab.\n");
		exit(-1);
	}

	while ((c = fgetc(*file)) != EOF) {
		printf("%c", c);

		if (isInTab(c, charTab) == -1) {
			intTab = realloc(intTab, sizeof(int) * tailleTab + 1);
			charTab = realloc(charTab, sizeof(char) * tailleTab + 1);
			if ((intTab == NULL) || (charTab == NULL)) {
				printf("Erreur REALLOC intTab ou  charTab.\n");
				exit(-1);
			}

			intTab[tailleTab] = 1;
			charTab[tailleTab] = c;
			tailleTab++;

		} else {
			positionChar = isInTab(c, charTab);
			intTab[positionChar]++;
		}
	}
	printf("\n");

	for (i = 0; i < tailleTab; i++) {
		printf("1-%c   %d\n", charTab[i], intTab[i]);
	}

	tri(charTab, intTab, tailleTab);

	for (i = 0; i < tailleTab; i++) {
		createChainedList(ptListe, charTab[i], intTab[i]);
	}

	/* Affichage liste chain�e tri�e */
	for (a = *ptListe; a != NULL; a = a->suivant) {
		printf("2-%c   %d\n", a->caractere, a->frequence);
	}
	printf("\n");

	while ((*ptListe)->suivant != NULL) {
		insertNewNodeInChainedList(ptListe);
	}

	/* La liste ne contient plus qu'un seul element qui contiend l'arbre entier */
	tabChar = calloc(1, sizeof(char*));
	if (tabChar == NULL) {
		printf("Erreur d'allocation tabChar.\n");
		exit(-1);
	}

	/* Parcours d'arbre*/
	prefixeHuffmanTree(elemL->noeudIntermediaire, tabChar, 0);

	/* affichage caract�res cod�s */
	for (i = 0; i < 256; i++) {
		if (code[i])
			printf("'%c': %s\n", i, code[i]);
	}

	/*Ecriture de la taille de la table des fr�quences */
	fileOutputName = calloc((8 + strlen(fileInputName)), sizeof(char));
	if (fileOutputName == NULL) {
		printf("Erreur d'allocation fileOutputName.\n");
		exit(-1);
	}

	fileOutputName = createBinaryFile(fileInputName, ptFileOutput, archiveName);

	openFile(fileOutputName, ptFileOutput, "wb+");
	/*ECRITURE DANS LE FICHIER CIBLE*/

	/* on �crit la taille du dictionnaire  */

	struct elementCompression elementComp;
	/* Ecriture du dictionnaire de donnees */
	for (i = 0; i < tailleTab; i++) {
		elementComp.caractere = charTab[i];
		elementComp.frequence = intTab[i];
		fwrite(&elementComp, sizeof(elementCompression), 1, *ptFileOutput);
	}

	bufferCode = calloc(1, sizeof(char));

	/*pointeur sur le fichier initial pour un nouveau parcours (creation du code)*/
	fseek(*file, 0, SEEK_SET);

	printf("Compression en cours, veuillez patienter . . .");
	while ((c = fgetc(*file)) != EOF) {
		tailleFileInput++;
		for (i = 0; i < 256; i++) {
			if (c == (char) i) {

				tailleCode = strlen(code[i]) + strlen(bufferCode) + 1;
				bufferCode = realloc(bufferCode, tailleCode * sizeof(char));
				if (bufferCode == NULL) {
					printf("PROBLEM\n");
				}
				strcat(bufferCode, code[i]);
			}
		}
	}
	printf("\n");
	printf("%s\n", bufferCode);

	tailleCode = strlen(bufferCode);
	int nboctet = tailleCode / 7;
	tailleFileOutput = nboctet + 1;
	for (i = 0; i < nboctet; i++) {
		strncpy(charTemp, bufferCode, 7);
		currentChar = binaryToDecimal(charTemp);
		fwrite(&currentChar, 1, 1, *ptFileOutput);
		bufferCode += 7;
	}

	i = nboctet * 7;

	/* si il reste des octets */
	if (i != tailleCode) {
		strcpy(charTemp, bufferCode);
		currentChar = binaryToDecimal(charTemp);
		if (strlen(charTemp) != 7) {
			for (i = 0; i < 7; i++) {
				if (charTemp[i] == '\0') {
					charTemp[i + 1] = '\0';
					charTemp[i] = '0';
				}
			}

			fwrite(&currentChar, 1, 1, *ptFileOutput);
		}
	}
	closeFile(ptFileOutput);

	/*TODO CHECK */
	/*if (bufferCode != NULL) {
	 free(bufferCode);
	 }*/
	printf("Taux de compression : %.2f %% \n",
			(float) tailleFileOutput * 100 / (float) tailleFileInput);
	freeHuffmanTree(elemL->noeudIntermediaire);

	free(elemL);
	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;
	free(archiveName);
	archiveName = NULL;
	free(fileOutputName);
	fileOutputName = NULL;
	free(tabChar);
	tabChar = NULL;

	fseek(*ptFileOutput, 0, SEEK_SET);

	printf("tailleTab : %d\n", tailleTab);
	/*fwrite(&tailleTab,1,1,*ptFileOutput);*/

}

void decodeHuffmanTree(const char *s, noeud *t) {
	noeud *n = t;

	while (*s) {
		if (*s++ == '0') {
			n = n->gauche_0;
		} else {
			n = n->droite_1;
		}

		if (n->caractere) {
			putchar(n->caractere), n = t;
		}
	}

	putchar('\n');
	if (t != n)
		printf("garbage input\n");
}

void decompressHuffman(FILE** file, FILE** ptFileOutput, char* fileInputName) {
	char c;
	char* bufferCode;
	char currentOctet[7];
	int i = 0, tailleBuf;
	int valueChar;
	int tailleDico=0;
	int* intTab;
	char* charTab;
	struct elementCompression elementComp;
	bufferCode = calloc(1, sizeof(char));

	/* Lire la taille des structures au d�but du fichier */
	fread(&tailleDico, sizeof(int), 1, *file);

	intTab = calloc(1, sizeof(int));
	charTab = calloc(1, sizeof(char));
	/* on lit les structures unes a une et on les met dans 2 tableaux (int+char) */
	i = 0;
	while (i < tailleDico) {
		intTab = realloc(intTab, sizeof(int) * i + 1);
		charTab = realloc(charTab, sizeof(char) * i + 1);
		/*fread(elementComp, sizeof(elementCompression), 1, *file);*/
		charTab[i] = elementComp.caractere;
		intTab[i] = elementComp.frequence;
		i++;
	}

	while (!feof(*file)) {
		c = fgetc(*file);
		/*on parcours tout le fichier compresse*/
		bufferCode = realloc(bufferCode, 7 * (i + 2) * sizeof(char));
		valueChar = c;
		decimalToBinary(valueChar, currentOctet);
		strcat(bufferCode, currentOctet);
		i++;

		printf("%c", c);
	}

	/* on supprime les 8 derniers caracteres = \0 */
	tailleBuf = strlen(bufferCode);
	printf("%d\n", i);
	for (i = (tailleBuf - 8); i < tailleBuf; i++) {
		bufferCode[i] = '\0';
	}
	printf("\n");

	/* creation de liste chainee et d'arbre */
	/* decodeHuffmanTree */
	/* DONE*/

	printf("%s\n", bufferCode);

	free(bufferCode);
}
