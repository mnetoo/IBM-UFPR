CC = gcc
CFLAGS = -Wall -Wextra
OBJ = main.o pilha.o
EXEC = PILHA

# Regra principal: compila o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compila main.c
main.o: main.c pilha.h
	$(CC) $(CFLAGS) -c main.c

# Compila pilha.c
pilha.o: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

# Limpa arquivos compilados
clean:
	rm -f $(OBJ) $(EXEC)
