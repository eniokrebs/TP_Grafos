main: funcoes.c main.c
	gcc -O3 funcoes.c main.c -o main

clean :
	rm main
