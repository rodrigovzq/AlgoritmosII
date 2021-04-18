FROM ubuntu:latest

 COPY . /usr/src/
 
 WORKDIR /usr/src/ 
 
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y gcc
RUN apt-get install -y valgrind
RUN apt-get install make
 
RUN gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c

RUN valgrind ./pruebas
 
CMD ["bash"]
 