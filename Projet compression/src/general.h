/*
 * print.h
 *
 *  Created on: 4 d�c. 2013
 *      Author: Guillaume
 */

#ifndef GENERAL_H_
#define GENERAL_H_

char* checkFileName(char* fileName, int longueurChaine);
int openFile(char* filename, FILE** fichier);
void closeFile(FILE** fichier);
FILE* createFile(char* fileName);
void writeFile(FILE** fichier, char* stringToWrite);
char readFile(FILE** file);
void readFilechar(FILE** file);
void bubbleSort(char* charTab, int* tabInt, int tabLength);
void bubbleSortchar(int min, int max, char* charTab, int* tabInt);
void tri(char* charTab, int* intTab, int tabLength);
#endif /* PRINT_H_ */
