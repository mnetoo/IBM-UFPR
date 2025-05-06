CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o avl.o
TARGET = avl

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c avl.h
	$(CC) $(CFLAGS) -c main.c

avl.o: avl.c avl.h
	$(CC) $(CFLAGS) -c avl.c

clean:
	rm -f *.o $(TARGET)