#include <stdio.h>

int valor_absoluto(int n){
    if (n >= 0){
        return n;
    }
    return n * -1;
}

int main (void){
    printf ("El valor absoluto de 'n' es %d\n", valor_absoluto(-42));
    return 0;
}