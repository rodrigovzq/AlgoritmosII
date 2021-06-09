project = tp1
execname = pruebas
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wconversion -Wtype-limits -pedantic -Werror 
LFLAGS = -lm

all: dc

docker:
	docker build -t $(project) .
	docker run --rm -it $(project)
memcheck: compile
	leaks -atExit -- ./$(execname)	 | grep LEAK: 
compile:
	$(CC) $(CFLAGS) -o $(execname) *.c
	./pruebas 
clean:
	
	-docker rmi $(project)
	-rm $(execname)
	-rm *.zip
	-rm *.o
	-rm -r ./*.dSYM

dc:  clean helper.o strutil.o  pila.o 
	$(CC) $(CFLAGS)  -o dc dc.c helper.o strutil.o pila.o $(LFLAGS)
	./dc < rpn.txt
pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -o pila.o -c pila.c
strutil.o: strutil.c strutil.h
	$(CC) $(CFLAGS) -o strutil.o -c strutil.c
helper.o: calc_helper.c calc_helper.h
	$(CC) $(CFLAGS) -o helper.o -c calc_helper.c
