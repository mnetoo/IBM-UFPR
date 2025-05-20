# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra

# Nome do executável
TARGET = vina

# Arquivos fonte
SRCS = vinac.c membro.c functions.c lz.c

# Arquivos cabeçalho
HDRS = membro.h functions.h lz.h

# Arquivos objeto (gerados a partir dos .c)
OBJS = $(SRCS:.c=.o)

# Regra padrão - compila o executável
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar cada arquivo .c em um .o
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Para evitar conflitos com arquivos de mesmo nome
.PHONY: all clean