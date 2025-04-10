# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -O2 -std=c99

# Nome do executável
TARGET = SIMPLES_CIRCULAR

# Arquivos fonte
SRCS = main.c lista_circular.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar cada arquivo .c em um arquivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para recompilar tudo
rebuild: clean all