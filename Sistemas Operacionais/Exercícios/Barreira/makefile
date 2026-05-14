CC = gcc
CFLAGS = -Wall -pthread
TARGET = barreira_processos

all: $(TARGET)

$(TARGET): barrier.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) barrier.o main.o

barrier.o: barrier.c barrier.h
	$(CC) $(CFLAGS) -c barrier.c

main.o: main.c barrier.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET) 4