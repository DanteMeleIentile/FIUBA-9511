#include <math.h>
#include <stdio.h>

float s_time(int a, int b, int c){
    int s; //Varible de segundos
    s = 0;
    
    a *=3600;
    b *=60;
    s = a + b + c;
    return s;
}
int main(){
    printf("EJERCICIO 4 - GUIA 1\n");
    printf("El resultado es: %f \n", s_time(2, 30, 30));
    return 0;
}