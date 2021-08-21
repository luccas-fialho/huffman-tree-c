all:
	gcc -o huffman main.c huffman.c -lm
clean:
	rm huffman