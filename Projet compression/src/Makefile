WALL=-Wextra -Wall -ansi -pedantic -g -std=c99 -D_GNU_SOURCE

ProjetCompressionSansPerte: lzw.o huffman.o general.o main.o
	gcc -o ProjetCompressionSansPerte lzw.o huffman.o general.o main.o
	rm -rf *.o
main.o: main.c
	gcc -c main.c $(WALL)

general.o: general.c general.h
	gcc -c general.c $(WALL)

huffman.o: huffman.c huffman.h
	gcc -c huffman.c $(WALL)
	
lzw.o: lzw.c lzw.h
	gcc -c lzw.c $(WALL)