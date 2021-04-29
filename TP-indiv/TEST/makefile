project= tp0test
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

all: docker

docker:
	docker build -t $(project) .
	docker run --rm -it $(project)
compile:
	$(CC) $(CFLAGS) -o pruebas *.c
clean:
	rm *.o