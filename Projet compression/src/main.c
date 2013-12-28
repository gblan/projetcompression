/*
 * main.c
 *
 *  Created on: 11 oct. 2013
 *      Author: Guillaume
 */

#include <stdio.h>
#include <string.h>
#include "lzw.h"
#include "huffman.h"
#include "general.h"
/*timeMethodLogging*/

int main(int argc, char *argv[]) {
/*
	int Comp = 0;
	int UnComp = 0;

	if (argc != 3) {
		printf("##### Missing parameters");
		return 1;
	} else {

		Comp = strcmp(argv[1], "-c");
		UnComp = strcmp(argv[1], "-u");

		if (Comp == 0) {
			printf("##### Compression\n\n");

			if (choiceCompression() == 1) {
				huffmanCompression(argv[2]);
			} else if (choiceCompression() == 2) {
				LZWCompression(argv[2]);

			}
		} else if (UnComp == 0) {
			printf("##### UnCompression\n");

		} else {
			printf("!!!!! Wrong parameter");
		}

		return 0;
	}*/
	FILE* fichier = NULL;
	FILE** file = &fichier;
	int intTab[100];
	char* charTab[100];
	fileOpen("test.txt", file);

/*	charTab = "TotoTataTitiTutu";
	printf("T : %d\n",isInTab('T',charTab));
	printf("a : %d\n",isInTab('a',charTab));
	printf("t : %d\n",isInTab('t',charTab));
	printf("b : %d\n",isInTab('b',charTab));
	printf("i : %d\n",isInTab('i',charTab));
	printf("p : %d\n",isInTab('p',charTab));*/

	copyFile(file, intTab, *charTab);
	fileClose(file);
	return 0;
}
