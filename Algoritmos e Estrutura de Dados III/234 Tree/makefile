CC = gcc
CFLAGS = -Wall -Wextra -lm
OBJ = main.o 234.o
TARGET = 234

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm
main.o: main.c 234.h
	$(CC) $(CFLAGS) -c main.c

234.o: 234.c 234.h
	$(CC) $(CFLAGS) -c 234.c

clean:
	rm -f *.o $(TARGET)
