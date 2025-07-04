# Nome do executável
EXEC = ARVOREB

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra

# Arquivos fonte e objetos
SRCS = main.c arvore.c
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(EXEC)

# Linkagem do executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos arquivos .c para .o
%.o: %.c arvore.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f *.o $(EXEC)
