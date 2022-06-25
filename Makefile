PROGRAM = EJ4
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g

all: $(PROGRAM)

$(PROGRAM): main.o color.o figura.o lectura.o polilinea.o
	$(CC) $(CFLAGS) main.o color.o figura.o lectura.o polilinea.o -o $(PROGRAM)

main.o: main.c color.h figura.h polilinea.h lectura.h
	$(CC) $(CFLAGS) -c main.c
	
color.o: color.c color.h 
	$(CC) $(CFLAGS) -c color.c

figura.o: figura.c figura.h 
	$(CC) $(CFLAGS) -c figura.c

lectura.o: lectura.c polilinea.h
	$(CC) $(CFLAGS) -c lectura.c

polilinea.o: polilinea.c color.h
	$(CC) $(CFLAGS) -c polilinea.c

clean:
	rm -vf *.o main