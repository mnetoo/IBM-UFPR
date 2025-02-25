# makefile generico para os TADs
# Carlos Maziero - DINF/UFPR

CC     = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIB    = lista
BIN    = tp4
OUT    = saida.txt

# gera o arquivo executável
$(BIN):   $(BIN).o $(LIB).o

# gera os arquivos-objeto
$(BIN).o: $(BIN).c $(LIB).h
$(LIB).o: $(LIB).c $(LIB).h

# teste de execução
teste: $(BIN)
	./$(BIN) > $(OUT)
	@echo "Diferenças entre saida esperada e gerada:"
	@diff $(BIN).txt $(OUT)

# verificação de memória
valgrind: $(BIN)
	valgrind --leak-check=full --track-origins=yes ./$(BIN)

# limpeza
clean:
	rm -f *.o *~ $(BIN) $(OUT)
