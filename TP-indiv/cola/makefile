project = tpcola
execname = pruebas
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -fsanitize=address


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
	docker rmi $(project)
	rm $(execname)
	rm -r ./*.dSYM
