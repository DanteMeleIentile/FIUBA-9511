/* SOLO EJERCICIO DE BITS */
#include <stdio.h>


#define MASK_RED 0xFF0000
#define MASK_GREEN 0x00FF00


unsigned char get_rojo(unsigned int color){
    unsigned char rojo = (color & MASK_RED) >> (4 * 4);
    return rojo;
}

void set_verde(unsigned int *color, unsigned char verde){
    *color = *color & (~MASK_GREEN);
    *color = *color | (verde << (4 * 2));
}

int main(void){
    unsigned int color = 0xAABBAA;
    printf ("El color rojo es 0x%x\n", get_rojo(0x124345));

    set_verde(&color, 0x22);
    printf ("El set verde da 0x%x\n", color);


    return 0;
}