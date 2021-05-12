project = guia
execname = pruebas
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror 


all: compile

docker:
	docker build -t $(project) .
	docker run --rm -it $(project)
memcheck: compile
	valgreen --leak-check=full --track-origins=yes --show-reachable=yes ./$(execname)	
compile:
	$(CC) $(CFLAGS) -o $(execname) *.c
	./pruebas
clean:
	docker 2>/dev/null 1>&2 rmi $(project) || true
	rm $(execname) || true
	rm -r ./*.dSYM || true
	echo "\033[0;34m Limpio \033[0m"
