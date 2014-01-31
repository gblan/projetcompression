WALL=-Wextra -Wall -ansi -lm -pedantic -std=c99 -D_GNU_SOURCE

ProjetCompressionSansPerte: huffman.o general.o main.o
	gcc -o ProjetCompressionSansPerte huffman.o general.o main.o $(WALL)
	rm -rf *.o

main.o: main.c
	gcc -c main.c $(WALL)

general.o: general.c general.h
	gcc -c general.c $(WALL)

huffman.o: huffman.c huffman.h
	gcc -c huffman.c $(WALL)