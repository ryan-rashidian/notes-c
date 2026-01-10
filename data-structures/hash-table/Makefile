CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -std=c99

TARGET = demo
OBJS = main.o hashtable.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c hashtable.h
	$(CC) $(CFLAGS) -c main.c

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) -c hashtable.c

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

