project = pila
execname = pruebas
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror


all: compile

docker:
	docker build -t $(project) .
	docker run --rm -it $(project)
compile:
	$(CC) $(CFLAGS) -o $(execname) *.c
clean:
	rm *.o