program = tp0
execname = pruebas
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror


all: compile

compile:
	$(CC) $(CFLAGS) -o pruebas heap.c heapif.c
	./pruebas
clean:
	rm *.o
