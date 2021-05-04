FROM rodrigovzq/algotronicos:latest

COPY . /usr/src/
 
WORKDIR /usr/src/ 

RUN gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c

RUN valgreen ./pruebas
 
CMD ["bash"]
 