CC = gcc
CFLAGS = -Wall -Wextra -pthread -O2

all: main

main: main.o primitives.o
	$(CC) $(CFLAGS) -o main main.o primitives.o

main.o: main.c shared.h
	$(CC) $(CFLAGS) -c main.c

primitives.o: primitives.c shared.h
	$(CC) $(CFLAGS) -c primitives.c

clean:
	rm -f *.o main