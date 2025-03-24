CC = gcc
CFLAGS = -Wall -Wextra
OBJ = fila.o main.o
EXEC = FILA

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

main.o: main.c fila.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ) $(EXEC)
