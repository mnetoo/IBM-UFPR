# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra

# Nome do executável
TARGET = EXE1

# Diretório de saída
OUTPUT_DIR = ./outputs

# Arquivos de código-fonte
SRCS = exe1.c grafos.c

# Arquivos de cabeçalho
HDRS = grafos.h

# Lista de arquivos-objeto a serem criados dentro do diretório de saída
OBJS = $(patsubst %.c,$(OUTPUT_DIR)/%.o,$(SRCS))

# O caminho completo para o executável final
TARGET_EXEC = $(OUTPUT_DIR)/$(TARGET)

# Regra padrão: o que é executado ao rodar "make"
all: $(TARGET_EXEC)

# Regra para lincar os arquivos-objeto e criar o executável final
# O alvo aqui é o caminho completo do executável
$(TARGET_EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar cada arquivo .c em seu respectivo .o dentro do diretório de saída
# O | $(OUTPUT_DIR) é uma "order-only prerequisite". Garante que o diretório seja
# criado antes de tentar compilar os objetos, mas não causa recompilação se
# o diretório for modificado.
$(OUTPUT_DIR)/%.o: %.c $(HDRS) | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o diretório de saída
$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(OUTPUT_DIR)

# Evita conflitos com arquivos que possam ter o mesmo nome das regras
.PHONY: all clean