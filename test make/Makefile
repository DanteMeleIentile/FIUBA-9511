PROGRAM = test_make
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g
LDFLAGS = -lm

all: $(PROGRAM)

$(PROGRAM): main.o color.o figura.o lectura.o polilineas.o
	$(CC) $(CFLAGS) main.o color.o figura.o lectura.o polilineas.o -o $(PROGRAM)

main.o: main.c color.h figura.h polilineas.h lectura.h
	$(CC) $(CFLAGS) -c main.c
	
color.o: color.c color.h 
	$(CC) $(CFLAGS) -c color.c

figura.o: figura.c figura.h 
	$(CC) $(CFLAGS) -c figura.c

lectura.o: lectura.c polilineas.h
	$(CC) $(CFLAGS) -c lectura.c

polilineas.o: polilineas.c color.h
	$(CC) $(CFLAGS) -c polilineas.c
