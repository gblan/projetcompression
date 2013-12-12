#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 1000

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

void fileOpen(char* filename, FILE** fichier) {
	*fichier = fopen(filename, "r+");

	if (*fichier != NULL) {
		printf("Open OK\n");

	} else {
		printf("Open KO\n");
	}
}

void fileClose(FILE** fichier) {
	if (fichier != NULL) {
		fclose(*fichier);
		printf("Close OK\n");
	} else {
		printf("Close KO\n");
	}
}

void readFile(FILE** file) {
	char str[TAILLE_MAX] = "";

	while (fgets(str, TAILLE_MAX, *file) != NULL) {
		printf("%s", str);
	}
	printf("\n");
}
