/*
 * print.h
 *
 *  Created on: 4 déc. 2013
 *      Author: Guillaume
 */

#ifndef GENERAL_H_
#define GENERAL_H_

int choiceCompression();
int checkExtention(char* fileName);
void fileOpen(char* filename, FILE** fichier);
void fileClose(FILE** fichier);
char readFile(FILE** file);

#endif /* PRINT_H_ */
