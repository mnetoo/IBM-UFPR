# Nome do compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -g

# Nome do arquivo executável
EXEC = FPRIO

# Arquivos de origem
SRCS = main.c fprio.c

# Arquivos de objeto
OBJS = $(SRCS:.c=.o)

# Regra para compilar o executável
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Regra para compilar o arquivo main.o
main.o: main.c fprio.h
	$(CC) $(CFLAGS) -c main.c

# Regra para compilar o arquivo fprio.o
fprio.o: fprio.c fprio.h
	$(CC) $(CFLAGS) -c fprio.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(EXEC)

# Regra padrão
all: $(EXEC)
