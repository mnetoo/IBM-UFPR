TARGET = AS
SOURCES = AggressiveSquares.c Square.c Joystick.c Bullet.c Pistol.c
ALLEGRO_FLAGS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags)

all:
	gcc $(SOURCES) -o $(TARGET) $(ALLEGRO_FLAGS)
