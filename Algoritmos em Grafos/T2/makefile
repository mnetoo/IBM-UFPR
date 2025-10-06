CC     = gcc
CFLAGS = -Wall
OBJ    = lista.o grafo.o main.o
PROG   = analise

.PHONY: clean purge all

%.o: %.c lista.h grafo.h
	$(CC) -c $(CFLAGS) $<

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *~ *.bak *.o core a.out $(PROG)

purge: clean
	@rm -rf bin obj *.layout *.depend
	@rm -f *.dat