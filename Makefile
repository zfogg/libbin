all:
	gcc -Wall -O3 "main.c" -o main

run: main
	./main

clean: main
	rm main

recompile: main
	make clean
	make
