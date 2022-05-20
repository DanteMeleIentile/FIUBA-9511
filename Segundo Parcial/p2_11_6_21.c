#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


/* PUNTO 1 */

#define MASK_1_BYTE 0xF0
#define MASK_2_BYTE 0xC0
#define MASK_3_BYTE 0xC0

/* PUNTO 1 A */

bool es_utf8_3_bytes_valido(const unsigned char bytes [3]){
    if (!((bytes[0] & MASK_1_BYTE) == (0xE0))){
        return false;
    }

    if (!((bytes[1] & MASK_2_BYTE) == (0x80))){
        return false;
    }
    
    if (!((bytes[2] & MASK_3_BYTE) == (0x80))){
        return false;
    }

    return true;
}

/* PUNTO 1 B */

unsigned int es_utf8_3bytes_a_codepoint(const unsigned char bytes [3]){
    unsigned int codepoint = (bytes[0] & ~(MASK_1_BYTE));
    codepoint <<= 6;

    codepoint |= (bytes[1] & ~(MASK_2_BYTE));
    codepoint <<= 6;

    codepoint |= (bytes[2] & ~(MASK_3_BYTE));

    return codepoint;
}

/* PUNTO 2 */

void matriz_destruir (float **matriz, size_t filas, size_t columnas){
    for (size_t i = 0; i < filas; i++){
        free (matriz[i]);
    }
    free(matriz);
}

float **matriz_crear(size_t filas, size_t columnas){
    float **matriz = malloc(sizeof(float *) * filas);
    if (matriz == NULL){
        return NULL;
    }
    
    for (int i = 0; i < filas; i++){
        matriz[i] = malloc (sizeof (float) * columnas);
        if (matriz[i] == NULL)
            matriz_destruir(matriz, filas, columnas);
        return NULL;
    }
    
    return matriz;
}   


typedef struct{
    char *c;
    size_t n;
} cadena_t;


int main(void){
    /* EJERCICIO 1 A Y B */

    unsigned char bytes [3] = {0xE2, 0x82, 0xAC};

    if (!es_utf8_3_bytes_valido(bytes)){
        printf ("NOOO, TA TODO MAL\n");
    }
    printf ("Re piola papu, ta todo bien\n");

    printf ("El valor que me mandaste es 0x%x \n", es_utf8_3bytes_a_codepoint(bytes));

    return 0;
}