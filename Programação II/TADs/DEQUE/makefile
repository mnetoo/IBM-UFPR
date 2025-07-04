# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -Wextra

# Nome do executável
EXEC = DEQUE

# Arquivos objeto
OBJ = main.o deque.o

# Regras para compilar o código
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c deque.h
	$(CC) $(CFLAGS) -c main.c

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c

# Limpar os arquivos compilados
clean:
	rm -f $(OBJ) $(EXEC)

# Limpar tudo, incluindo o arquivo executável
distclean: clean
	rm -f $(EXEC)