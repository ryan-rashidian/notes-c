CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -O2
SDL_CFLAGS = $(shell pkg-config --cflags sdl3)
SDL_LIBS   = $(shell pkg-config --libs sdl3)

TARGET = demo

all: $(TARGET)

$(TARGET): demo.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) demo.c -o $(TARGET) $(SDL_LIBS)

clean:
	rm -f $(TARGET)

