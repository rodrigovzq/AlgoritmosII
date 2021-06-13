project = tp1
execname = pruebas
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wconversion -Wtype-limits -pedantic -Werror 
LFLAGS = -lm

all: dc infix string

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
	-rm ./dc
	-rm ./infix
	-rm ./string_test
	-rm *.zip
	-rm *.o
	-rm -r ./*.dSYM
string: clean string.o testing.o
	$(CC) $(CFLAGS) -o string_test pruebas_string.c string.o testing.o
	./string_test
infixx:  clean helper.o strutil.o pila.o cola.o
	$(CC) $(CFLAGS)  -o infix infixcopy.c helper.o strutil.o pila.o cola.o 
	./infix < arith.txt
infix: clean helper.o strutil.o pila.o cola.o
	$(CC) $(CFLAGS)  -o infix infix.c helper.o strutil.o pila.o cola.o 
	./infix < arith.txt
dc:  clean helper.o strutil.o  pila.o 

	$(CC) -g -std=c11 -Wconversion -Wtype-limits    -o dc dc.c helper.o strutil.o pila.o $(LFLAGS)
	./dc < rpn.txt
pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -o pila.o -c pila.c
strutil.o: strutil.c strutil.h
	$(CC) $(CFLAGS) -o strutil.o -c strutil.c
helper.o: calc_helper.c calc_helper.h
	$(CC) $(CFLAGS) -o helper.o -c calc_helper.c
string.o: strutil.c strutil.h
	$(CC) $(CFLAGS) -o string.o -c strutil.c
testing.o: testing.c testing.h
	$(CC) $(CFLAGS) -o testing.o -c testing.c
