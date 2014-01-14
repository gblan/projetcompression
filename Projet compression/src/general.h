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

#endif /* PRINT_H_ */