# Nome do executável final
TARGET = heap

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Arquivos fonte e objetos
SRCS = main.c heap.c heap.h
OBJS = $(SRCS:.c=.o)

# Regra padrão: compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compila arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)
