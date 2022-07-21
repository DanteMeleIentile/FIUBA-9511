PROGRAM = Gravitar
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g3
SDLFLAGS = -lSDL2 -lm

all: $(PROGRAM)

$(PROGRAM): main_v.o color.o figura.o lectura.o polilinea.o lista.o fisicas.o planeta.o nave.o disparo.o nivel.o torreta.o combustible.o reactor.o caracteres.o
	$(CC) $(CFLAGS) main_v.o color.o figura.o lectura.o polilinea.o lista.o fisicas.o planeta.o nave.o disparo.o nivel.o torreta.o combustible.o reactor.o caracteres.o $(SDLFLAGS) -o $(PROGRAM)

main_v.o: main_v.c color.h figura.h polilinea.h lectura.h config.h lista.h fisicas.h planeta.h nave.h disparo.h nivel.h torreta.h combustible.h caracteres.h
	$(CC) $(CFLAGS) -c main_v.c
	
color.o: color.c color.h 
	$(CC) $(CFLAGS) -c color.c

polilinea.o: polilinea.c color.h
	$(CC) $(CFLAGS) -c polilinea.c

lectura.o: lectura.c polilinea.h
	$(CC) $(CFLAGS) -c lectura.c

figura.o: figura.c figura.h polilinea.h lista.h
	$(CC) $(CFLAGS) -c figura.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c

fisicas.o: fisicas.c fisicas.h polilinea.h
	$(CC) $(CFLAGS) -c fisicas.c

planeta.o: planeta.c planeta.h figura.h
	$(CC) $(CFLAGS) -c planeta.c

nave.o: nave.c nave.h figura.h fisicas.h
	$(CC) $(CFLAGS) -c nave.c

disparo.o: disparo.c disparo.h figura.h fisicas.h
	$(CC) $(CFLAGS) -c disparo.c

nivel.o: nivel.c nivel.h figura.h
	$(CC) $(CFLAGS) -c nivel.c

torreta.o: torreta.c torreta.h figura.h fisicas.h
	$(CC) $(CFLAGS) -c torreta.c

caracteres.o: caracteres.c caracteres.h color.h
	$(CC) $(CFLAGS) -c caracteres.c

combustible.o: combustible.c combustible.h figura.h
	$(CC) $(CFLAGS) -c combustible.c

reactor.o: reactor.c reactor.h figura.h nivel.h
	$(CC) $(CFLAGS) -c reactor.c

clean:
	rm -vf *.o main

exe:
	./$(PROGRAM)

valgrind-log-file:
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=error.log --suppressions=suppressions_20221_tp1.supp -s ./$(PROGRAM)

valgrind:
	valgrind --leak-check=full --suppressions=suppressions_20221_tp1.supp ./$(PROGRAM)