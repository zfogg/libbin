all:
	clang -std=c99 -Wall -O3 "main.c" -o main

clean:
	rm main

recompile:
	make clean
	make
