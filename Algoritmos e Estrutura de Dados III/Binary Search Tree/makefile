# Nome do compilador
CC = gcc

# Flags de compilação (avisos e depuração)
CFLAGS = -Wall -Wextra

# Nome do executável final
EXEC = ARVORE

# Arquivos-fonte
SRC = main.c Árvore.c

# Arquivos objeto (substituindo .c por .o)
OBJ = $(SRC:.c=.o)

# Regra padrão: compilar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f *.o $(EXEC)
