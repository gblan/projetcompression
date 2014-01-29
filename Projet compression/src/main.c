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
	FILE* fileInput = NULL;
	FILE** ptFileInput = &fileInput;
	FILE* fileOutput = NULL;
	FILE** ptFileOutput = &fileOutput;

	if (argc != 3) {
		printf("##### Nombre de parametres incorrect\n");
		printf(
				"##### Ecrire de la forme : nomprogramme c/d nomdufichiera(de)compresser\n");
		return 1;

	} else {
		Comp = strcmp(argv[1], "c");
		UnComp = strcmp(argv[1], "d");

		if (Comp == 0) {
			printf("##### Compression\n");

			if (openFile(argv[2], ptFileInput, "r+") != 0) {
				printf("Erreur d'ouverture du fichier\n");
				return -1;
			}

			huffman(ptFileInput, ptFileOutput, argv[2]);

			closeFile(ptFileInput);

		} else if (UnComp == 0) {
			printf("##### DeCompression\n");

			if (openFile(argv[2], ptFileInput, "r+") != 0) {
				printf("Erreur d'ouverture du fichier\n");
				return -1;
			}

			decompressHuffman(ptFileInput, ptFileOutput, argv[2]);

			closeFile(ptFileInput);

		} else {
			printf("!!!!! Mauvais parametres,\n");
			printf(
					"##### Ecrire de la forme : nomprogramme c/d nomdufichier\n");
		}
	}
	return 0;
}
