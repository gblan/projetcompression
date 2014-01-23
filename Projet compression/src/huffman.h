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
void createHuffmanTree();
void createChainedList(elementListe** elemL, char tabChar, int tabInt);
void deleteTwoFirstElements(elementListe** elemL);
void linkElementWithChaindList(elementListe* elemL, elementListe* element);
void insertNewNodeInChainedList(elementListe* elemL);
void visiteNoeud(noeud* huffmanTree, int* tabChar, char** tabHuffCode, char* currentCode, int *tailleTab);
void infixeHuffmanTree(noeud* huffmanTree, char* tabChar, char** tabHuffCode, char* currentCode, int *tailleTab);
void huffman(FILE** file, int *intTab, char *charTab, char* archiveName);

#endif /* HUFFMAN_H_ */
