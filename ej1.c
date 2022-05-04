#include <stdio.h>

int main (void){
    float *pfloat, manzana = 40.0, pera = 35.0;

    printf("&pfloat: %p\n", &pfloat);
    printf("&manzana: %p\n", &manzana);
    printf("&pera: %p\n", &pera);

    printf("pfloat: %p\n", pfloat);

    pfloat = &manzana;
    printf("pfloat: %p\n", pfloat);
    printf("*pfloat: %f\n", *pfloat);

    pfloat = &pera;
    printf("pfloat: %p\n", pfloat);
    printf("*pfloat: %f\n", *pfloat);

    return 0;
}