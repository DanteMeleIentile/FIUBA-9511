#include <stdio.h>
#include <stdbool.h>


bool extraer_coordenada(float coordenada[], const char s[]){
    int i = 0;
    while (s[i]){
        printf("ok\n");
        i++;
        if (i == 8){
            return true;
        }
    }
    return false;
}

int main (void){
    const char s[] = {"123456789"};
    extraer_coordenada (s);
    return 0;
} 