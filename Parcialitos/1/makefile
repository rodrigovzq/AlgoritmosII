project = parcial
execname = parcial
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror 

all: test

compilar:
	gcc -g -std=c99 -Wconversion -Wno-sign-conversion -o $(execname) *.c -DCORRECTOR
limpiar:
	clear

run:
	valgrind ./$(execname)

docker:
	docker build -t $(project) .
	docker run --rm -it $(project)
	
memcheck: compile
	leaks -atExit -- ./$(execname)	 | grep LEAK: 

compile:limpiar
	$(CC) $(CFLAGS) -o $(execname) *.c -DCORRECTOR

test:
	$(CC) $(CFLAGS) -o $(execname) repar.c pila.c
	./$(execname)
time: compilar
	./tiempos_volumen.sh ./$(execname)
clean:
	
	-docker rmi $(project)
	-rm $(execname)
	-rm *.zip
	-rm -r ./*.dSYM
