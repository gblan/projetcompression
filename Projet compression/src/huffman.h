/*
 * huffman.h
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

void openFileToCompress(char *path);
void huffman(FILE** file, int *intTab, char *charTab, float* tabProba);
int isInTab(char c, char* charTab);
int sumTab(int* tabInt, int tailleTab);
void creatTabProba(float* tabProba, int* tabInt, int tailleTab, int sumTab);

#endif /* HUFFMAN_H_ */
