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
/*timeMethodLogging*/

int main(int argc, char *argv[]) {

	int i = 0;
	int Comp = 0;
	int UnComp = 0;

	if (argc != 4) {
		printf("Missing parameters");
		return 1;
	} else {
		for (i = 0; i < argc; i++) {
			printf("Parameter %d = %s\n", i, argv[i]);
		}

		Comp = strcmp(argv[1], "-c");
		UnComp = strcmp(argv[1], "-u");

		if (Comp == 0) {
			printf("Compression\n");
		} else if (UnComp == 0) {
			printf("UnCompression\n");

		} else {
			printf("Wrong parameter");
		}

		return 0;
	}
}
