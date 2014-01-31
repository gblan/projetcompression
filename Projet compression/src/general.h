/*
 * print.h
 *
 *  Created on: 4 déc. 2013
 *      Author: Guillaume
 */

#ifndef GENERAL_H_
#define GENERAL_H_

/*  Fonction: openFile
 *  Entrees: - nom du fichier
 *  		- pointeur sur le fichier
 *  		- mode d'ouverture
 *  Sorties: - entier representant la reussite ou l'echec de
 *  		l'ouverture du fichier
 *
 *  ouvre le fichier avec le mode voulu
 */
int openFile(char* filename, FILE** fichier, char* mode);

/*  Fonction: closeFile
 *  Entrees: - pointeur sur le fichier

 *  ferme le fichier ouvert precedemment
 */
void closeFile(FILE** fichier);

/*  Fonction: createFile
 *  Entrees: - nom du fichier
 *  Sorties: - pointeur sur le fichier cree
 *
 *  cree le fichier avec le nom passe en parametre
 */
FILE* createFile(char* fileName);

/*  Fonction: bubbleSort
 *  Entrees: - indice min de recherche
 *  		- indice max de recherche
 *  		- tableau de caracteres
 *  		- tableau d'entiers
 *  		-taille des 2 tableaux
 *
 *  trie les 2 tableaux dans l'ordre croissants
 */
void bubbleSort(int min, int max, char* charTab, int* tabInt);

/*  Fonction: bubbleSortchar
 *  Entrees: - indice min de recherche
 *  		- indice max de recherche
 *  		- tableau de caracteres
 *  		- tableau d'entiers
 *  		-taille des 2 tableaux
 *
 *  trie les 2 tableaux dans l'ordre des caracteres choisis
 */
void bubbleSortchar(int min, int max, char* charTab, int* tabInt);

/*  Fonction: tri
 *  Entrees: - tableau de caracteres
 *  		- tableau d'entiers
 *  		- taille des tableaux
 *
 *  trie les tableaux d'entiers par frequence,
 *  puis pour les frequences identiques par caractere
 */
void tri(char* charTab, int* intTab, int tabLength);

/*  Fonction: createBinaryFile
 *  Entrees: - nom du fichier d'entree
 *  Sorties: - pointeur sur le fichier cree
 *
 *  cree le fichier d'archive, dont le nom est composé
 *  du nom du fichier source + l'extension .huffman
 */
char* createBinaryFile(char* fileName, FILE** ptFileOutput, char* archiveName);

/*  Fonction: createDecodedFile
 *  Entrees: - nom du fichier d'entree
 *  Sorties: - pointeur sur le fichier cree
 *
 *  cree le fichier decodé, dont le nom est composé
 *  du nom du fichier source(.huffman) + l'extension .decoded
 */
char* createDecodedFile(char* fileName, FILE** ptFileOutput,
		char* decodedFileName);

/*  Fonction: binaryToDecimal
 *  Entrees: - chaine de 7 caracteres (0&1)
 *  Sorties: - entier
 *
 *  convertit la valeur binaire en decimal
 */
int binaryToDecimal(char* subString);

/*  Fonction: decimalToBinary
 *  Entrees: - entier = valeur decimale du caractere
 *  		- pointeur sur chaine de 7 caractere
 *
 *  ecrit la valeur binaire du caractere correspondant
 *  avec des 0 a gauche pour completer (7bits au total)
 */
void decimalToBinary(int decimal, char* octet);

#endif /* PRINT_H_ */
