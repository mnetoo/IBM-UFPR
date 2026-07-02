# Makefile de exemplo (Manual do GNU Make)

CFLAGS = -Wall -Wextra -g -std=c99 # flags de compilacao
CC = gcc

# gera o executável
all: tp1.o racional.o
	$(CC) -o tp1 tp1.o racional.o

# compila racional.c
racional.o: racional.c racional.h
	$(CC) -c $(CFLAGS) racional.c

# compila tp1.c
tp1.o: tp1.c racional.h
	$(CC) -c $(CFLAGS) tp1.c

clean:
	rm -f *.o *~ tp1
