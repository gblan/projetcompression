#include <stdio.h>
#include <string.h>

int choiceCompression() {
	int result = 0;

	do {
		printf("Wich compression did you want to use :\n");
		printf("\t1 - Huffman\n\t2 - Lempel-Ziv-Welch\n");
		scanf("%d", &result);
		printf("### %d ###",result);
	} while (result != 1 && result != 2);

	return result;
}

int checkExtention(char* fileName) {
	int result = 0;

	return result;
}
