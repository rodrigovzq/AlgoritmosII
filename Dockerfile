#Crea imagen ALGOTRONICOS con estos comandos
# >> docker build -t rodrigovzq/algotronicos . 
# se pushea a repo con:
# >> docker push rodrigovzq/algotronicos:latest

FROM ubuntu:latest

 
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y gcc
RUN apt-get install -y valgrind
RUN apt-get install make
RUN apt-get install -y python3-pip
RUN pip3 install valgreen
 

 