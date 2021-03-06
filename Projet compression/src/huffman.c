/*
 * huffman.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"general.h"

/* structure de liste chainee */
typedef struct elementListe {
	int frequence; /* frequence d'apparition du caractere */
	char caractere;
	struct elementListe* suivant; /* pointeur sur l'element suivant de la liste*/
	struct noeud* noeudIntermediaire; /* pointeur sur le noeud intermediaire*/
} elementListe;

/* structure de noeud d'arbre */
typedef struct noeud {
	char caractere; /* caractere ou \0 si on est sur un noeur qui n'est pas feuille de l'arbre*/
	struct noeud *gauche_0; /* pointeur sur le fils gauche */
	struct noeud *droite_1; /* pointeur sur le fils droit */
} noeud;

const char *code[256] = { 0 };
char buf[1024];
unsigned long long tailleFileInput = 0;
unsigned long long tailleFileOutput = 0;

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
	float longueurTotaleCode = 0;
	char* tabChar;
	char* fileOutputName;
	int* intTab;
	char* charTab;
	char* bufferCode;
	char charTemp[7];
	elementListe* elemL = NULL;
	elementListe** ptListe = &elemL;

	/* temps de traitement */
	clock_t start_time, end_time;
	start_time = clock();

	intTab = calloc(1, sizeof(int));
	charTab = calloc(1, sizeof(char));

	if ((intTab == NULL) || (charTab == NULL)) {
		printf("Erreur d'allocation intTab ou  charTab.\n");
		exit(-1);
	}

	/* parcours du fichier source et remplissage des tableaux de frequence*/
	while ((c = fgetc(*file)) != EOF) {

		/*printf("%c", c);*/
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

	/* Affichage tableau */
	/*for (i = 0; i < tailleTab; i++) {
	 printf("1-%c   %d\n", charTab[i], intTab[i]);
	 }*/

	tri(charTab, intTab, tailleTab);

	/* Affichage tableaux tri�s */
	/*for (i = 0; i < tailleTab; i++) {
	 printf("2-%c   %d\n", charTab[i], intTab[i]);
	 }*/

	for (i = 0; i < tailleTab; i++) {
		createChainedList(ptListe, charTab[i], intTab[i]);
	}
	/* Affichage liste chainee tri�e*/
	/*for (a = *ptListe;a->suivant!=NULL;a = a->suivant) {
	 printf("3-%c   %d\n", a->caractere, a->frequence);
	 }*/

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
		if (code[i]) {
			printf("'%c': %s\n", i, code[i]);
			longueurTotaleCode += strlen(code[i]);
		}
	}

	printf("Longueur moyenne d'un symbole : %.2f bits\n",
			longueurTotaleCode / tailleTab);
	printf("Compression en cours, veuillez patienter . . .\n");

	/*Ecriture de la taille de la table des fr�quences */
	fileOutputName = calloc((8 + strlen(fileInputName)), sizeof(char));
	if (fileOutputName == NULL) {
		printf("Erreur d'allocation fileOutputName.\n");
		exit(-1);
	}

	fileOutputName = createBinaryFile(fileInputName, ptFileOutput, ".huffman");

	openFile(fileOutputName, ptFileOutput, "wb");

	/*ECRITURE DANS LE FICHIER CIBLE*/
	/*------------------------------------------------------------*/

	/* on �crit la taille du dictionnaire  */
	fwrite(&tailleTab, sizeof(int), 1, *ptFileOutput);

	/* Ecriture du dictionnaire de donnees */
	for (i = 0; i < tailleTab; i++) {

		fwrite(&charTab[i], sizeof(char), 1, *ptFileOutput);
		tailleFileOutput++;
		fwrite(&intTab[i], sizeof(int), 1, *ptFileOutput);
		tailleFileOutput += 4;
	}
	/*------------------------------------------------------------*/

	bufferCode = calloc(1, sizeof(char));
	if (bufferCode == NULL) {
		printf("Erreur d'allocation bufferCode.\n");
		exit(-1);
	}
	/*pointeur sur le fichier initial pour un nouveau parcours (creation du code)*/
	fseek(*file, 0, SEEK_SET);

	while ((c = fgetc(*file)) != EOF) {
		tailleFileInput++;
		for (i = 0; i < 256; i++) {
			if (c == (char) i) {

				tailleCode = strlen(code[i]) + strlen(bufferCode) + 1;
				bufferCode = realloc(bufferCode, tailleCode * sizeof(char));
				if (bufferCode == NULL) {
					printf("Erreur reallocation bufferCode.\n");
				}
				strcat(bufferCode, code[i]);
			}
		}
	}
	printf("\n");
	/* Affichage du buffer */
	/*printf("%s\n", bufferCode);*/

	tailleCode = strlen(bufferCode);
	int nboctet = tailleCode / 7;
	tailleFileOutput += nboctet;
	for (i = 0; i < nboctet; i++) {
		strncpy(charTemp, bufferCode, 7);
		currentChar = binaryToDecimal(charTemp);
		fwrite(&currentChar, 1, 1, *ptFileOutput);
		bufferCode += 7;
	}

	i = nboctet * 7;

	/* si il reste des octets */
	if (i != tailleCode) {
		tailleFileOutput++;

		strcpy(charTemp, bufferCode);
		if (strlen(charTemp) != 7) {
			for (i = 0; i < 7; i++) {
				if (charTemp[i] == '\0') {
					charTemp[i + 1] = '\0';
					charTemp[i] = '0';
				}
			}
			currentChar = binaryToDecimal(charTemp);
			fwrite(&currentChar, 1, 1, *ptFileOutput);
		}
	}
	closeFile(ptFileOutput);

	printf("Taux de compression : %.2llu %% \n",
			100 -((tailleFileOutput) * 100 / tailleFileInput));
	freeHuffmanTree(elemL->noeudIntermediaire);

	free(elemL);
	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;
	free(fileOutputName);
	fileOutputName = NULL;
	free(tabChar);
	tabChar = NULL;

	end_time = clock();
	printf("Compression effectuee en %lu s.",
			(long) ((end_time - start_time) / CLOCKS_PER_SEC));
}

void decodeHuffmanTree(const char *bufferToDecode, noeud *noeudRacine,
		FILE** ptFileOutput) {
	noeud *ptRacine = noeudRacine;

	while (*bufferToDecode) {
		if (*bufferToDecode++ == '0') {
			ptRacine = ptRacine->gauche_0;
		} else {
			ptRacine = ptRacine->droite_1;
		}

		if (ptRacine->caractere != '\0') {
			putc(ptRacine->caractere, *ptFileOutput), ptRacine = noeudRacine;
		}
	}

	printf("\n");
	/* si il reste des caract�res dans le buffer*/
	if (noeudRacine != ptRacine) {
		fseek(*ptFileOutput, -1, SEEK_END);
		putc('\n', *ptFileOutput);
	}
}

void decompressHuffman(FILE** file, FILE** ptFileOutput, char* fileInputName) {
	char c;
	char* bufferCode;
	char currentOctet[7];
	int i = 0, tailleBuf;
	int valueChar;
	int tailleDico = 0, tailleTab;
	int* intTab;
	char* charTab;
	char* tabChar;
	char* decodedFileName;
	elementListe* elemL = NULL;
	elementListe** ptListe = &elemL;

	/* temps de traitement */
	clock_t start_time, end_time;
	start_time = clock();

	bufferCode = calloc(1, sizeof(char));
	if (bufferCode == NULL) {
		printf("Erreur d'allocation bufferCode.\n");
		exit(-1);
	}

	/* Lire la taille des structures au d�but du fichier */
	fread(&tailleDico, sizeof(int), 1, *file);
	/*printf("%d\n", tailleDico);*/

	charTab = calloc(1, sizeof(char));
	intTab = calloc(1, sizeof(int));
	if ((intTab == NULL) || (charTab == NULL)) {
		printf("Erreur d'allocation intTab ou  charTab.\n");
		exit(-1);
	}
	i = 0;

	/* Extraction du dictionnaire */
	while (i < tailleDico) {
		charTab = realloc(charTab, sizeof(char) * i + 1);
		intTab = realloc(intTab, sizeof(int) * i + 1);
		if ((intTab == NULL) || (charTab == NULL)) {
			printf("Erreur reallocation intTab ou  charTab.\n");
			exit(-1);
		}

		fread(&charTab[i], sizeof(char), 1, *file);
		fread(&intTab[i], sizeof(int), 1, *file);
		i++;
	}

	/* Affichage des caract�res */
	/*for (i = 0; i < tailleDico; i++) {
	 printf("1- %c %d\n", charTab[i], intTab[i]);
	 }*/

	tailleTab = tailleDico;

	/* Creation de liste chainee */
	for (i = 0; i < tailleTab; i++) {
		createChainedList(ptListe, charTab[i], intTab[i]);
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

	printf("Decompression en cours, veuillez patienter . . .\n");

	/* on parcours le fichier compresse */
	bufferCode = calloc(1, sizeof(char));
	if(bufferCode == NULL){
		printf("Erreur d'allocation bufferCode.\n");
		exit(-1);
	}
	while (!feof(*file)) {
		c = fgetc(*file);
		bufferCode = realloc(bufferCode, 7 * (i + 2) * sizeof(char));
		if(bufferCode == NULL){
			printf("Erreur d'allocation bufferCode.\n");
			exit(-1);
		}
		valueChar = c;
		decimalToBinary(valueChar, currentOctet);
		strcat(bufferCode, currentOctet);
		i++;

		/*printf("%c", c);*/
	}

	/* on supprime les 8 derniers caracteres = \0 */
	tailleBuf = strlen(bufferCode);
	for (i = (tailleBuf - 8); i < tailleBuf; i++) {
		bufferCode[i] = '\0';
	}

	/* Affichage du buffer */
	/*printf("%s\n", bufferCode);*/

	/*Ecriture de la taille de la table des fr�quences */
	decodedFileName = calloc((8 + strlen(fileInputName)), sizeof(char));
	if (decodedFileName == NULL) {
		printf("Erreur d'allocation fileOutputName.\n");
		exit(-1);
	}

	strcat(fileInputName, ".decoded");
	*ptFileOutput = createFile(fileInputName);
	closeFile(ptFileOutput);
	openFile(fileInputName, ptFileOutput, "wb+");

	decodeHuffmanTree(bufferCode, elemL->noeudIntermediaire, ptFileOutput);

	closeFile(ptFileOutput);

	free(decodedFileName);
	decodedFileName = NULL;
	free(bufferCode);
	free(elemL);
	elemL = NULL;
	free(intTab);
	intTab = NULL;
	free(charTab);
	charTab = NULL;
	free(tabChar);
	tabChar = NULL;

	end_time = clock();
	printf("Decompression effectuee en %lu s.\n",
			(long) ((end_time - start_time) / CLOCKS_PER_SEC));

}
