/*
 * print.h
 *
 *  Created on: 4 d�c. 2013
 *      Author: Guillaume
 */

#ifndef GENERAL_H_
#define GENERAL_H_

int choiceCompression();
int checkExtention(char* fileName);
void fileOpen(char* filename, FILE** fichier);
void fileClose(FILE** fichier);
char readFile(FILE** file);
void readFilechar(FILE** file);
void copyFile(FILE** file, int *intTab, char *charTab);
int isInTab(char c, char* charTab);

#endif /* PRINT_H_ */
