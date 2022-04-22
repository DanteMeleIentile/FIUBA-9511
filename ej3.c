#include <stdio.h>
#include <math.h>
//DIMENTSION -1

/* double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, float px, float py);{

} */


void resta_vectores (double resta[2], double v1[], double v2[], int n){
    for (int i = 0; i < n; i++){
        resta[i] = v1[i] - v2[i];
    }
}

double prod_interno (double ax, double ay, double bx, double by){
    return (ax * bx) + (ay * by);
}

double norma(double ax, double ay, double bx, double by){
    double resta_x = ax - bx;
    double resta_y = bx - by;;
    return sqrt(pow(resta_x, 2) + pow(resta_y, 2));
}

double computar_escalar(double px, double py, double ax, double ay, double bx, double by){
    
    return prod_interno(px-ax, py-ay, bx-ax, by-ay) / pow (norma (bx, by, ax, ay));
    
    double resta_1[2];
    double resta_2[2];

    resta_vectores (resta_1, p, v1, 2);
    resta_vectores (resta_2, v2, v1, 2);
    

    return prod_interno(resta_1, resta_2) / pow (norma (v2, v1) ,2);

/* DEBUGIN CON PRINTS */
    //printf("%f, %f\n", resta_![0], resta[1]);
    //printf("%f\n", prod_interno(resta_1, resta_2));
    //printf("%f\n", prod_interno(resta_1, resta_2) / pow (norma (v2, v1) ,2));

}

int main (void){
    //float polilinea[][2] = {{0, 1}, {1, 3}, {1, 5}};
   // int n = sizeof(polilinea)/sizeof (polilinea[0]); //debe dar 3=3
    double v1[] = {0, 1};0
    double v2[] = {1, 3};

    const float polilinea[][2] = {
        {0, 1}, 
        {1, 3}, 
        {1, 5}, 
        {2, 5}, 
        {3, 4}, 
        {4, 4}, 
        {5, 3}, 
        {4, 2}, 
        {5, 1}, 
        {2, 0}
    };




    double p[] = {0, 0};
    
    //computar_escalar(p, v2, v1, 2);

/* DEBUGIN CON PRINTS */
    
    //printf("%f, %f\n", resta[0], resta[1]);
    //printf("%f\n", prod_interno(v1, v2));
    //printf("%f\n", norma(v2, v1));
    printf("%f\n", computar_escalar(p, v2, v1, 2));
    
/* CONDICIONES ALPAH */
    double resta_3[2];
    if (computar_escalar(p, v2, v1, 2) <= 0){
        norma (p, v1);
        printf("%f\n", norma(p, v1));

    } else if (computar_escalar(p, v2, v1, 2) >= 1){
        norma (p, v2);
        printf("%f\n", norma(p, v2));

    } else{
        resta_vectores (resta_3, p, v1, 2);
        double vd[2];
        vd[0] = v1[0] + computar_escalar(p, v2, v1, 2) * resta_3[0];
        vd[1] = v1[1] + computar_escalar(p, v2, v1, 2) * resta_3[1];
        
/* DEBUGIN CON PRINTS dentro del ELSE */
        //punto d e recta en condición de que el punto esté en el medio
        printf("%f, %f\n", vd[0], vd[1]);

        //impresión de norma 
        printf("%f\n", norma(p, vd));
    }
}

