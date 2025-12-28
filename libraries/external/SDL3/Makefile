CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -O2
SDL_CFLAGS = $(shell pkg-config --cflags sdl3)
SDL_LIBS   = $(shell pkg-config --libs sdl3)

all: main

main: main.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) main.c -o main $(SDL_LIBS)

clean:
	rm -f main

