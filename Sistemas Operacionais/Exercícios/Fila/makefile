CC = gcc
CFLAGS = -Wall -pthread
OBJ = fifoq.o main.o
TARGET = programa_fifo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

fifoq.o: fifoq.c fifoq.h
	$(CC) $(CFLAGS) -c fifoq.c

main.o: main.c fifoq.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET)