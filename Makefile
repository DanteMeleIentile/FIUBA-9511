PROGRAM = Gravitar
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
SDLFLAGS = -lSDL2 -lm

all: $(PROGRAM)

$(PROGRAM): main.o color.o figura.o lectura.o polilinea.o lista.o fisicas.o planeta.o nave.o
	$(CC) $(CFLAGS) main.o color.o figura.o lectura.o polilinea.o lista.o fisicas.o planeta.o nave.o $(SDLFLAGS) -o $(PROGRAM)

main.o: main.c color.h figura.h polilinea.h lectura.h config.h lista.h fisicas.h planeta.h nave.h
	$(CC) $(CFLAGS) -c main.c
	
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

fisicas.o: fisicas.h polilinea.h
	$(CC) $(CFLAGS) -c fisicas.c

planeta.o: planeta.h figura.h
	$(CC) $(CFLAGS) -c planeta.c

nave.o: nave.h figura.h
	$(CC) $(CFLAGS) -c nave.c


clean:
	rm -vf *.o main

exe:
	./$(PROGRAM)

valgrind:
	valgrind --suppressions=suppressions_20221_tp1.supp --track-origins=yes ./$(PROGRAM)