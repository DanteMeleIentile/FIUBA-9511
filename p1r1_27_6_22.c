#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 5
#define M 4

/* //EJERCICIO 1
int contar_mayusculas(const char cadena[]){
    int i = 0;
    int cant = 0;
    for (i = 0; cadena[i]; i++){
        if (isupper(cadena[i])){
            cant ++;
        }
    }
    return cant;
} */

//EJERCICIO 2
bool es_nonegativa(const float m[][M]){
    int i = 0;
    for (i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (m[i][j] < 0){
                return false;
            }
        }
    }
    return true;
}


/* //EJERCICIO 3
bool ingreso_valido(const char s[]){
    if (!((s[0] >= '0' && s[0] <= '9') || (s[0] == '-'))){
        return false;
    }
    return true;
}
float n_mayor(float a, float b){
    if (a > b){
        return 1;
    } else if (a < b){
        return -1;
    } else 
    return 0;
} */

int main (void){
    /*//EJERCICIO 1
    const char cadena[] = {"Algoritmos y Programación I"};
    printf("la cant de mayus es: %d\n", contar_mayusculas(cadena));*/

    //EJERCICIO 2
    const float m[N][M] = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 0},
        {1, 2, 3, 2},
        {1, 2, 3, 4}
    };
    if (es_nonegativa(m)){
        printf("TA TODO BIEn\n");
    } else{
        printf("ES NEGATIVA\n");
    }


    /* //EJERCICIO 3
    char s[100];
    printf ("ingrese el primer numero: \n");
    fgets(s, 100, stdin);
    if (!(ingreso_valido(s))){
        printf("numero no valido\n");
        return 1;
    }
    float a = atof(s);
    printf ("ingrese el segundo numero: \n");
    fgets(s, 100, stdin);
    if (!(ingreso_valido(s))){
        printf("numero no valido\n");
        return 1;
    }
    float b = atof(s);
    if (n_mayor(a, b) == 1){
        printf(" el numero mayor es %f\n", a);
    }
    if (n_mayor(a, b) == -1){
        printf(" el numero mayor es %f\n", b);
    }
    if (n_mayor(a, b) == 0){
        printf("Los numeros son iguales\n");
    } */

    return 0;
}