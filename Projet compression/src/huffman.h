/*
 * huffman.h
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

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

void openFileToCompress(char *path);
int isInTab(char c, char* charTab);
int sumTab(int* tabInt, int tailleTab);
void createTabProba(float* tabProba, int* tabInt, int tailleTab, int sumTab);
void createChainedList(elementListe** elemL, char charToAdd, int intToAdd);
void deleteTwoFirstElements(elementListe** elemL);
void linkElementWithChaindList(elementListe** elemL, elementListe* element);
void insertNewNodeInChainedList(elementListe** elemL);
void prefixeHuffmanTree(noeud *n, char *s, int len);
void freeHuffmanTree(noeud *n);
void huffman(FILE** file, FILE** ptFileOutput, char* fileInputName);
void decodeHuffmanTree(const char *bufferToDecode, noeud *noeudRacine,
		FILE** ptFileOutput);
void decompressHuffman(FILE** file, FILE** ptFileOutput, char* fileInputName);

#endif /* HUFFMAN_H_ */

