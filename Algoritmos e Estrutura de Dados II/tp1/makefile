# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -lm

# Arquivos de origem e de objeto
SRC = programa.c funções.c
OBJ = programa.o funções.o

# Nome do executável
EXEC = programa

# Regra principal para compilar o executável
all: $(EXEC)

# Como construir o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -lm

# Compilação dos arquivos .o a partir dos .c
programa.o: programa.c
	$(CC) $(CFLAGS) -c programa.c

funcoes.o: funcoes.c
	$(CC) $(CFLAGS) -c funções.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)