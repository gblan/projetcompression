/*
 * main.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lzw.h"
#include "huffman.h"
#include "general.h"

int main(int argc, char *argv[]) {
	int Comp = 0;
	int UnComp = 0;
	FILE* fichier = NULL;
	FILE** file = &fichier;
	int* intTab;
	char* charTab;
	float* tabProba;

	if (argc != 3) {
		printf("##### Missing parameters");
		return 1;

	} else {
		Comp = strcmp(argv[1], "-c");
		UnComp = strcmp(argv[1], "-u");

		if (Comp == 0) {
			printf("##### Compression\n\n");
			intTab = calloc(1, sizeof(int));
			charTab = calloc(1, sizeof(char));
			tabProba = calloc(1, sizeof(float));

			if (openFile(argv[2], file) != 0) {
				printf("Erreur d'ouverture du fichier");
				return -1;

			}
			huffman(file, intTab, charTab, tabProba);
			closeFile(file);

		} else if (UnComp == 0) {
			printf("##### UnCompression\n");

		} else {
			printf("!!!!! Wrong parameter");
		}
	}
	return 0;
}
