/*
 * huffman.h
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

void huffmanCompression(char *path);
void openFileToCompress(char *path);
void tableAppearance(char *str, int **tabApp);
void huffmanTableSort(int *tabApp, char *tabChar);
void printTabAppearance(int **tab, int a);

#endif /* HUFFMAN_H_ */
