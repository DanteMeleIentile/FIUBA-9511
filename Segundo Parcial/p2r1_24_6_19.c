#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



/* EJERCICIO 3 */


#define MAX_CADENA 20
#define MAX_NUMEROS 20


typedef struct{
    char referencia[MAX_CADENA];
    unsigned long int numero;
} numero_t;

typedef struct{
    char nombre[MAX_CADENA];
    numero_t vector[MAX_NUMEROS];
} contacto_t;

bool numero_en_contacto(const contacto_t *c, unsigned long numero){
    for (size_t i = 0; i < MAX_NUMEROS; i++){
        if ((c->vector[i]).numero == numero){
            return true;
        }
    }
    return false;
}

/* EJERCICIO 1 */

char *join(char *strs[], size_t n, char delim){
    size_t len_tot = 0;

    for (size_t i = 0; i < n; i++){
        len_tot += strlen(strs[i]);
    }

    len_tot = len_tot + (n-1) + 1; //agrego espacios para los n 'delim's y un espacio para el \0

    char *cadena = malloc(sizeof(char) * len_tot);
    if (cadena == NULL){
        return NULL;
    }
    
    size_t i;
    
    for (i = 0; i < (len_tot - 1); i++){
        cadena[i] = *strs[i];   
        if((i = (strlen(strs[i]) + 1))){
            cadena[i] = delim;
        }
    }

    cadena[i] = '\0';
    
    return cadena;
}


int main(void){
    /* char s;
    char strs[] = {"hola", "que", "tal"};
    s = join(strs , 3, ' ');
    puts(s); */

    char *s;
    char *strs[] = {"Hola", "que", "tal"};
    if((s = join(strs, 3, '|')) == NULL){
        printf("Error de memoria\n");
        free(s);
        return 1;
    }

    puts(s);
    free(s);

    /* EJERCICIO 3 */
    contacto_t dad =
    {"dad",
        {
        {"numero_1", 12345},
        {"numero_2", 12345},
        {"numero_3", 12345},
        {"numero_3", 123445},
        },
    };
    
    unsigned long int numero = 1445;

    if(!(numero_en_contacto(&dad, numero))){
        printf ("EL NUMERO NO ESTÁ\n");
        return 0;
    }

    printf ("ESTÁ\n");

    return 0;
}