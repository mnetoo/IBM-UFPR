CC     = gcc
CFLAGS = -std=c11 -Wall
OBJ    = lista.o grafo.o testa_grafos.o
PROG   = testa_grafos

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