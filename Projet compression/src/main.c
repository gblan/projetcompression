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
	int* intTab;
	char* charTab;
	char* archiveName = NULL;

	if (argc != 3) {
		printf("##### Missing parameters\n");
		return 1;

	} else {
		Comp = strcmp(argv[1], "-c");
		UnComp = strcmp(argv[1], "-u");

		if (Comp == 0) {
			printf("##### Compression\n");
			intTab = calloc(1, sizeof(int));
			charTab = calloc(1, sizeof(char));

			if (openFile(argv[2], ptFileInput, "r+") != 0) {
				printf("Erreur d'ouverture du fichier\n");
				return -1;

			}

			huffman(ptFileInput, intTab, charTab, archiveName);

			/*createBinaryFile(argv[2],ptFileOutput, archiveName);
			 */
			closeFile(ptFileInput);

		} else if (UnComp == 0) {
			printf("##### UnCompression\n");

		} else {
			printf("!!!!! Wrong parameter\n");
		}
	}
	return 0;
}
