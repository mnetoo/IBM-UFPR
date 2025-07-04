# Nome do executável final
TARGET = GAME

# Diretórios
SRC_DIR = src
INC_DIR = includes
BUILD_DIR = build

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)
LDFLAGS = -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_primitives -lm

# Lista de arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera arquivos objeto no diretório build
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Regra principal
all: $(TARGET)
	
# Linkagem
$(TARGET): $(OBJS)
	@echo "Linkando..."
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilação de arquivos .c para .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@
	

# Cria o diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpa os objetos e binário
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	

.PHONY: all clean