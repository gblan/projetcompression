/*
 * huffman.h
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

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

/*  Fonction: isInTab
 *  Entrees: - caractere
 *  		- chaine de caractere
 *  Sorties: - entier
 *
 *  si le caractere est dans le tableau, alors on retourne sa position
 *  sinon on retourne -1
 */
int isInTab(char c, char* charTab);

/*  Fonction: createChainedList
 *  Entrees: - pointeur sur le premier element de la liste chainee
 *  		- caractere a ajouter
 *  		- frequence correspondante
 *
 *  on cree un nouvel element qu'on ajoute au debut de la liste chainee
 */
void createChainedList(elementListe** elemL, char charToAdd, int intToAdd);

/*  Fonction: deleteTwoFirstElements
 *  Entrees: - pointeur sur la liste chainee

 * on supprime les 2 premiers elements de la liste chainee
 */
void deleteTwoFirstElements(elementListe** elemL);

/*  Fonction: linkElementWithChaindList
 *  Entrees: - pointeur sur la liste chainee
 *  		- element de liste chainee
 *  Sorties: - entier
 *
 *  on ajoute l'element passe en parametre dans la liste chainee
 *  si la probabilite existe deja dans la liste chainee,
 *  alors on ajoute l'element après ceux de même probabilité
 */
void linkElementWithChaindList(elementListe** elemL, elementListe* element);

/*  Fonction: insertNewNodeInChainedList
 *  Entrees: - pointeur sur la liste chainee
 *
 *  on prend les 2 premiers elements de la chaine, et on les met dans des noeuds d'arbre
 *  les eventuels noeuds intermédiaires sont donc ajoutés
 */
void insertNewNodeInChainedList(elementListe** elemL);

/*  Fonction: prefixeHuffmanTree
 *  Entrees: - noeud racine
 *  		- chaine de caractere
 *  		- longueur du code courrant
 *
 *  C'est ici qu'on fait un parcours recursif de l'arbre
 *  on affecte a chaque noeud terminal une chaine de caractere
 *  correspondant a une suite de 0&1
 *  qu'on ecrira dans la variable globale char* code[];
 */
void prefixeHuffmanTree(noeud *n, char *s, int len);

/*  Fonction: freeHuffmanTree
 *  Entrees: - noeud racine
 *
 *  parcours recursif du tableau
 *  qui permet de liberer dynamiquement les noeuds uns a uns (free)
 */
void freeHuffmanTree(noeud *n);

/*  Fonction: huffman
 *  Entrees: - pointeur sur le fichier d'entree
 *  		- pointeur sur le fichier de sortie
 *  		- nom du fichier d'entree
 *
 *  appel a toutes les methodes qui font que l'algo d'huffman est realisé correctement
 */
void huffman(FILE** file, FILE** ptFileOutput, char* fileInputName);

/*  Fonction: decodeHuffmanTree
 *  Entrees: - buffer de 0&1 du fichier compressé
 *  		- noeud racine
 *  		- pointeur sur le fichier de sortie
 *
 *  on parcourt l'arbre pour écrire le code correspondant au code courant du buffer
 */
void decodeHuffmanTree(const char *bufferToDecode, noeud *noeudRacine,
		FILE** ptFileOutput);

/*  Fonction: decompressHuffman
 *  Entrees: - pointeur sur le fichier d'entree (encodé)
 *  		- pointeur sur le fichier de sortie
 *  		- nom du fichier d'entree
 *
 *  appel a toutes les methodes qui font que le décodage est realisé correctement
 */
void decompressHuffman(FILE** file, FILE** ptFileOutput, char* fileInputName);

#endif /* HUFFMAN_H_ */

