# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra

# Nome do executável
TARGET = vina

# Diretório de saída
OUTPUT_DIR := msarn24

# Arquivos fonte
SRCS = vinac.c membro.c functions.c lz.c

# Arquivos cabeçalho
HDRS = membro.h functions.h lz.h

# Arquivos objeto (gerados a partir dos .c)
OBJS = $(SRCS:.c=.o)

# Regra padrão - compila o executável
all: $(OUTPUT_DIR)/$(TARGET)

# Cria o diretório de saída se não existir
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Regra para construir o executável no diretório especificado
$(OUTPUT_DIR)/$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Regra para compilar cada arquivo .c em um .o
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/$(TARGET)
	rmdir $(OUTPUT_DIR) 2>/dev/null || true

# Para evitar conflitos com arquivos de mesmo nome
.PHONY: all clean info