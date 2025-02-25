# Makefile de exemplo (Manual do GNU Make)

CFLAGS = -Wall -Wextra -g -std=c99 # flags de compilacao
CC = gcc

# gera o executável
all: tp2.o racional.o
	$(CC) -o tp2 tp2.o racional.o

# compila racional.c
racional.o: racional.c racional.h
	$(CC) -c $(CFLAGS) racional.c

# compila tp2.c
tp2.o: tp2.c racional.h
	$(CC) -c $(CFLAGS) tp2.c

clean:
	rm -f *.o *~ tp2
