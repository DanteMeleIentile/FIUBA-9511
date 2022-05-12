#include <stdio.h>

void s_hms(long segundostot, long * horas, long* minutos, long* segundos){
    *segundos = segundostot % 60;
    segundostot = segundostot / 60;
    *minutos = segundostot % 60;
    *horas = segundostot / 60;
}


int main (void){
    long segundostot = 36062;
    long horas = 0;
    long minutos = 0;
    long segundos  = 0;
    s_hms(segundostot, &horas, &minutos, &segundos);
    printf ("Horas: %ld\n", horas);
    printf ("minutos: %ld\n", minutos);
    printf ("minutos: %ld\n", segundos);

    return 0;
}