CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -O2
SDL_CFLAGS = $(shell pkg-config --cflags sdl3)
LIBS   = $(shell pkg-config --libs sdl3) -lm

TARGET = demo
OBJS = main.o square.o window.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $@ $(OBJS) $(LIBS)

main.o: main.c square.h window.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c main.c $(LIBS)

square.o: square.c window.h config.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c square.c $(LIBS)

window.o: window.c square.h window.h config.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c window.c $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
