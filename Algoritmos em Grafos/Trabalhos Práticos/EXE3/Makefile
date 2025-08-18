CC     = gcc
CFLAGS = -std=c11
LFLAGS = -Wall

OBJ = lista.o grafo.o testa_grafos.o
PROG = testa_grafos

.PHONY: clean purge all

%.o: %.c lista.h grafo.h
	$(CC) -c $(CFLAGS) $<

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -rf bin obj *.layout *.depend
	@rm -f *.dat *.o core a.out
	@rm -f $(PROG)
