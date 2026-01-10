# Simple Makefile example.

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -std=c99

TARGET = example
OBJS = main.o dependency.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c dependency.h
	$(CC) $(CFLAGS) -c main.c

dependency.o: dependency.c
	$(CC) $(CFLAGS) -c dependency.c

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

