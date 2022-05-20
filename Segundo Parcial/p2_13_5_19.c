#include <stdio.h>
#include <stdbool.h>





/* EJERCICIO 1 */

#define MAX_CADENA 10

typedef struct{
    char nombre[MAX_CADENA];
    unsigned int padron;
    float promedio;
} alumno_t;

bool alumno_son_iguales(const alumno_t *a, const alumno_t *b){    
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (i = 0; a->nombre[i]; i++);
    i++;
    
    for (j = 0; b->nombre[j]; j++);
    j++;
    
    if (i != j){
        return false;
    }
    
    for (k = 0; k < i; k++){
        if (a->nombre[k] != b->nombre[k])
            return false;
    }


    if (!(a->padron == b->padron)){
        return false;
    }


    if (!(a->promedio == b->promedio)){
        return false;
    }


    return true;
}


/* EJERCICIO 2 */

typedef struct{
    float *v;
    size_t n;
} vector_t

vector_t *vector_crear(const float vals[], size_t n){
    vector_t *vector = malloc (size_t vector_t);
}






int main(void){

    /* EJERCICIO 1 */
    alumno_t a = {
        .nombre = "dante",
        .padron = 123,
        .promedio = 1.2
    };

    alumno_t b = {
        .nombre = "dante",
        .padron = 123,
        .promedio = 1.2
    };

    if (alumno_son_iguales(&a, &b)){
        printf ("SON IGUALES\n");
        return 0;        
    }

    printf ("NO SON IGUALES\n");


    return 0;
}