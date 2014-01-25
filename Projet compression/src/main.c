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

	char* archiveName = NULL;

	if (argc != 3) {
		printf("##### Missing parameters\n");
		return 1;

	} else {
		Comp = strcmp(argv[1], "-c");
		UnComp = strcmp(argv[1], "-u");

		if (Comp == 0) {
			printf("##### Compression\n");

			if (openFile(argv[2], ptFileInput, "r+") != 0) {
				printf("Erreur d'ouverture du fichier\n");
				return -1;
			}

			huffman(ptFileInput, archiveName, ptFileOutput, argv[2]);

			closeFile(ptFileInput);

		} else if (UnComp == 0) {
			printf("##### DeCompression\n");

		} else {
			printf("!!!!! Wrong parameter\n");
		}
	}
	return 0;
}
