PROGRAM = Gravitar
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -lm
SDLFLAGS = -lSDL2

all: $(PROGRAM)

$(PROGRAM): main.o color.o figura.o lectura.o polilinea.o
	$(CC) $(CFLAGS) main.o color.o figura.o lectura.o polilinea.o $(SDLFLAGS) -o $(PROGRAM)

main.o: main.c color.h figura.h polilinea.h lectura.h config.h
	$(CC) $(CFLAGS) -c main.c
	
color.o: color.c color.h 
	$(CC) $(CFLAGS) -c color.c

polilinea.o: polilinea.c color.h
	$(CC) $(CFLAGS) -c polilinea.c

lectura.o: lectura.c polilinea.h
	$(CC) $(CFLAGS) -c lectura.c

figura.o: figura.c figura.h polilinea.h
	$(CC) $(CFLAGS) -c figura.c

clean:
	rm -vf *.o main