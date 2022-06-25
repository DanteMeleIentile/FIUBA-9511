CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -lSDL2 -lm

tp: main.o color.o figura.o polilinea.o lectura.o
	$(CC) main.o color.o figura.o polilinea.o lectura.o -o tp $(CFLAGS)
	
main.o: main.c color.h figura.h polilinea.h lectura.h
	$(CC) main.c -c $(CFLAGS)

color.o: color.c color.h
	$(CC) color.c -c $(CFLAGS)

figura.o: figura.c figura.h polilinea.h
	$(CC) figura.c -c $(CFLAGS)

polilinea.o: polilinea.c polilinea.h color.h
	$(CC) polilinea.c -c $(CFLAGS)

lectura.o: lectura.c lectura.h polilinea.h figura.h color.h
	$(CC) lectura.c -c $(CFLAGS)

exe:
	valgrind ./tp figuras_in.bin > figuras_out2.txt

clean:
	rm -vf *o
