#include <stdio.h>



int main (void){
    int *p, a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int var;
    p = a;
    var = *(p++);
    var = *p++;
    var = *(++p);
    var = *++p;
}