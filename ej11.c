#include <stdio.h>

size_t strlen_(const char cadena[]){
    int i;
    //while (cadena [i] != '\0'){
    for (i = 0; cadena [i] != '\0'; i++);
    return i;
}

char * strcpy_(char * dest, const char * orig){
    int i = 0;
    while (orig [i] != '\0'){
        dest[i] = orig[i];
        i++;
    }
    return dest;
}

char * strncpy_(char * dest, const char * orig, size_t n){
    for (int i = 0; i < n; i++){
        dest[i] = orig[i];
    }
    return dest;
}

int strcmp_(const char * s1, const char * s2){
    int i;
    for (i = 0; (s1[i] || s2[i]) && (s1[i] == s2[i]) ; i++);
    return s1[i] - s2[i];
}

char * strcat_(char * dest, const char * orig){
    int i;
    int j;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; orig[j] != '\0'; j++){
        dest[i + j] = orig[j];
    }
    dest [i + j + 1] = '\0';
    return dest;
}


int main(void){
    //char cadena[] = {"cadena ingresada"};
    //printf ("la candena ingresada tiene %zd digitos\n", strlen_(cadena));


    //char orig[] = {"hola123"};
    //char dest[100];
    //strcpy_(dest, orig);
    //printf ("la cedena destino %s\n", strcpy_(dest, orig));
    //size_t n = 2;
    //strncpy_(dest, orig, n);
    //printf ("la cedena destino %s\n", strncpy_(dest, orig, n));
    

    /* char s1[] = {"hola"};
    char s2[] = {"zla"};
    printf ("la diferencia entre cadenas es %d\n", strcmp_(s1, s2)); */
    
    /* char orig[] = "como";
    char dest[100] = "hola";
    printf ("la cadena concatenada es: %s\n", strcat_(dest, orig)); */

    


    return 0;
}

