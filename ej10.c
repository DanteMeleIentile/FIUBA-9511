#include <stdio.h>
#include <stdbool.h>

bool son_iguales(int v1[], int v2[], size_t n, size_t j){
    if (n != j)
        return false;

    for (int i = 0; i < n; i++){
        if (v1[i] != v2[i]){
            return false;
        }
    }
    return true;
}


int main (void){
    int v1[] = {1, 2, 3, 4, 5};
    int v2[] = {1, 2, 3, 4};

    size_t n = sizeof (v1) / sizeof (v1[0]);
    size_t j = sizeof (v2) / sizeof (v2[0]);

    printf(son_iguales(v1, v2, n, j) ? "son iguales %d\n" : "son distintos %d\n", son_iguales(v1, v2, 4, 4));
}