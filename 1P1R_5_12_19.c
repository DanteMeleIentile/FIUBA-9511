#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define N 3 

//EJERCICIO 1 a Y b
bool es_palindromo(const char s[]){
    int i = 0;
    int contador = 0;
    for (i = 0; s[i]; i++){
        contador = i;
    }
    i = 0;
    while (i <= (contador - i)){
        if ((s[i] == s[contador - i]) && (s[i])){
            i++;
        } else{
            return false;
        }
    }
    return true;
}


/* //EJERCICIO 2 a y b
void intercambiar_columnas(float m[][N], int a, int b){
    float temp[N] = {0};
    for (int i = 0; i < N; i++){
        temp[i] = m[i][a-1];

        m[i][a-1] = m[i][b-1];
        m[i][b-1] = temp[i];
    }
} */

//EJERCICIO 3
float e_perro_humano(float e_perro){
    return 16 * log(e_perro) + 31;
}

bool validar_entrada(float e_perro){
    if (!(e_perro > 0)){
        return false;
    }
    return true;
}




int main (void){
    /* //EJERCICIO 1
    char s[] = {""};
    if (es_palindromo(s)){
        printf ("La palabra es palindroma\n");
    } else{
        printf ("La palabra NO es palindroma\n");
    } */

    /* //EJERCICIO 2
    int a = 1;
    int b = 1;
    float matriz[][N] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };
    intercambiar_columnas (matriz, a, b);
    for (int i = 0; i < N; i++){
        printf("(%f, %f, %f)\n", matriz[i][0], matriz[i][1], matriz[i][2]);
    } */

    /* //EJERCICIO 3
    char s[100];
    printf ("Ingrese edad perruna: ");
    fgets(s, 100, stdin);
    float e_perro = atof (s);
    if (!(validar_entrada (e_perro))){
        printf("No me dan las cuentas\n");
        return 1;
    }
    printf("la edad del perro en años humanos es: %f\n", e_perro_humano(e_perro)); */


    return 0;
}




