#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>



#define N 3

/*  //EJERCICIO 1

void reemplazar_caracter(char destino[], const char origen[], char viejo, char nuevo){
    int i = 0;
    for (i = 0; origen [i]; i++){
        destino [i] = origen [i];
        if (origen[i] == viejo){
            destino [i] = nuevo;
        }
    }
    destino [i] = '\0';
}
 */

//EJERCICIO 2

bool es_triangular_superior(float m[][N]){
    for (int i = 1; i < N; i++){ //evaluar quitar el 1
        if ((m[i][0] != 0) || (m[i-1][i-1] == 0)){
            return false;
        }
    }
    return true;
}

//EJERCICIO 3

bool entrada_ok(char c[]){
    if (!(atof(c) >= 0) || !(c[0] >= '0' && c[0] <= '9')){
        return false;
    } else 
        return true;
}

double raiz(float n){
    return sqrt(n);
}




int main(void){
    
    /* //EJERCICIO 1
    const char origen[] = {"Los Alumnos"};
    char destino[100];
    reemplazar_caracter(destino, origen, 'o', 'e');
    size_t n = sizeof(origen);
    for (int i = 0; i < n; i++){
        printf ("%c", destino[i]);
    }
    printf ("\n"); */


    //EJERCICIO 2
    float m[][N] = {
        {1, 2, 3},
        {0, 1, 2},
        {0, 1, 1},
    };
    
    if (!es_triangular_superior(m)){
        printf("NO\n");
    } else
        printf("Sí\n");

    /* //EJERCICIO 3
    char c[100];
    printf("Ingrese un numero para calcular raiz\n");
    fgets(c, 100, stdin);
    if (!(entrada_ok(c))){
        printf("MAL");
        return 1;
    }
    printf("el valor de la raiz es %f\n", raiz(atof(c)));

    return 0; */
}