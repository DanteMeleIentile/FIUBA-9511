/*EJERCICIO 6
 Teniendo el radio de un cilindro y su altura escribir funciones que calculen:

    El diámetro del cilindro.

    La circunferencia.

    El área de la base.

    El volumen del cilindro.

    El área del cilindro.
 */

#include <math.h>
#include <stdio.h>

#define PI 3.14159
#define VALOR_RADIO 3
#define VALOR_ALTURA 3

float diametro (float radio);
float circunferencia (float radio);
/*float area (float radio); */
float volumen (float radio, float altura);
float area_cilindro(float radio, float altura);

int main(){
    float i_radio = VALOR_RADIO;
    float i_altura = VALOR_ALTURA;
    printf("EJERCICIO 6 - GUIA 1\n");
    printf("El resultado es: %f \n", diametro(i_radio));
    printf("El resultado es: %f \n", circunferencia(i_radio));
    printf("El resultado es: %f \n", circunferencia(i_altura));
    
    return 0;
}

float diametro(float radio){
    return 2 * radio;
}

float volumen(float radio, float altura){
    return PI * pow(radio, 2) * altura;
}

float area_cilindro(float radio, float altura){
    /* return 2 * PI * radio * altura + 2 * PI * pow(radio, 2); */
    return circunferencia(radio) * altura + 2 * PI * pow(radio, 2);
}

float circunferencia(float radio){
    return 2 * PI * radio;
}