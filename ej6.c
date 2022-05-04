#include <stdio.h>
#include <stdlib.h>


void swap (int * a, int * b){
    int t = *a;
    *a = *b;
    *b = t;
}

int main (void){

    int a = 3;
    int b = 8;
    printf("1 el valor de a es = %d, el valor de b es = %d\n", a, b);
    swap(&a, &b);
    printf("2 el valor de a es = %d, el valor de b es = %d\n", a, b);
    return 0;
}