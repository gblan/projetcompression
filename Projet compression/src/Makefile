ProjetCompressionSansPerte: lzw.o huffman.o general.o main.o
	gcc -o ProjetCompressionSansPerte lzw.o huffman.o general.o main.o
	rm -rf *.o
main.o: main.c
	gcc -c main.c -Wextra -Wall -ansi -pedantic -std=c99 -D_GNU_SOURCE

general.o: general.c general.h
	gcc -c general.c -Wextra -Wall -ansi -pedantic -std=c99 -D_GNU_SOURCE

huffman.o: huffman.c huffman.h
	gcc -c huffman.c -Wextra -Wall -ansi -pedantic -std=c99 -D_GNU_SOURCE
	
lzw.o: lzw.c lzw.h
	gcc -c lzw.c -Wextra -Wall -ansi -pedantic	 -std=c99 -D_GNU_SOURCE