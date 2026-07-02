# makefile generico para os TADs
# Carlos Maziero - DINF/UFPR

CC     = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIB    = fprio
BIN    = testa-fprio

$(BIN):   $(BIN).o $(LIB).o
$(BIN).o: $(BIN).c $(LIB).h
$(LIB).o: $(LIB).c $(LIB).h

teste: $(BIN)
	./$(BIN)

valgrind: $(BIN)
	valgrind --leak-check=full --track-origins=yes ./$(BIN)

clean:
	rm -f *.o *~ $(BIN)
