all:
	gcc -o main main.c huffman.c -lm
clear:
	rm main