CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -lSDL2 -lm

tp: main.o color.o figura.o polilinea.o
	$(CC) main.o color.o figura.o polilinea.o -o tp $(CFLAGS)
	
main.o: main.c color.h figura.h polilinea.h
	$(CC) main.c -c $(CFLAGS)

color.o: color.c color.h
	$(CC) color.c -c $(CFLAGS)

figura.o: figura.c figura.h
	$(CC) figura.c -c $(CFLAGS)

polilinea.o: polilinea.c polilinea.h color.h
	$(CC) polilinea.c -c $(CFLAGS)

exe:
	valgrind ./tp figuras_in.bin > figuras_out2.txt

clean:
	rm -vf *o
