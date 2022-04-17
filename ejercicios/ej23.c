#include <stdio.h>
#include <math.h>

#define X 23
#define Y 23

int x_mayor_y (int x, int y){
    if (x > y){
        return printf ("x es mayor que y\n");
    } else if (x == y){
        return printf ("x es igual a y\n");
    } else{
        return printf ("x es menor a y\n");
    }
}

int main (void){
    x_mayor_y(X, Y);
    return 0;
}