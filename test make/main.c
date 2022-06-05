#include <stdio.h>
#include <stdbool.h>

#include "color.h"
#include "figura.h"
#include "polilineas.h"
#include "lectura.h"



int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if(f == NULL) {
        fprintf(stderr, "No pudo abrirse \"%s\"\n", argv[1]);
        return 1;
    }

    int figura = 0;
    while(1) {
        figura++;

        char nombre[20];
        bool infinito;
        figura_tipo_t tipo;
        size_t cantidad_polilineas;

        if(! leer_encabezado_figura(f, nombre, &tipo, &infinito, &cantidad_polilineas))
            break;

        printf("FIGURA \"%s\", TIPO: %s, INFINITO: %d, POLILINEAS: %zd\n", nombre, figura_tipo_a_cadena(tipo), infinito, cantidad_polilineas);

        for(size_t i = 0; i < cantidad_polilineas; i++) {
            polilinea_t *p = leer_polilinea(f);
            if(p == NULL) {
                fprintf(stderr, "Error en el archivo");
                fclose(f);
                return 1;
            }
            polilinea_destruir(p);
        }
    }

    fclose(f);

    return 0;
}