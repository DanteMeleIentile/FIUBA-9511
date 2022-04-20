#include <stdio.h>
#include <math.h>
#include <stddef.h>

#define DISTANCIA_X 1
#define DISTANCIA_Y 1


void trasladar (float polilinea [][2], size_t n, float dx, float dy){
    for (int i = 0; i < n; i++){
        polilinea [i][0] += dx;
        polilinea [i][1] += dy;
    }
}

void rotar (float polilinea [][2], size_t n, float rad){

}

int main (void){
    
    float polilinea[][2] = {{0, 1}, {1, 3}, {1, 5}};
    int n = sizeof(polilinea)/sizeof (polilinea[0]); //debe dar 3=3
    trasladar(polilinea, n, DISTANCIA_X, DISTANCIA_Y);
    for (int i = 0; i < n; i++){
        printf ("(%f, %f)\n", polilinea[i][0], polilinea[i][1]);
        //printf ("(%d)\n", n);
    }

    trasladar(polilinea, n, angulo???);
   

    

}