#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


typedef enum{
    ICONO,
    NIVEL,
    SPRITE,
} figura_tipo_t;

char *nombre_icono[] = {
    [ICONO] = "Icono",
    [NIVEL] = "Nivel",
    [SPRITE] = "Sprite",
};

const char* figura_tipo_a_cadena(figura_tipo_t figura){
    return nombre_icono[figura];
}

// ---------------------- COLORES ----------------------
typedef uint8_t color_t;

color_t color_crear(bool r, bool g, bool b){
    return ( (r << 2) | (g << 1) | (b) ); // CAMBIAR A MASCARA
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b){
    *r = ((c >> 2) & 1) * 255; 
    *g = ((c >> 1) & 1) * 255; 
    *b = (c & 1) * 255; // CAMBIAR A MASCARA
}

// ---------------------- COLORES ---------------------- //

#define MASK_TIPO 0x07  // 0000 0111

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas){
    if (fread(nombre, 1, 20, f) != 20){
        return false;
    } 

    uint8_t aux;
    if (fread(&aux, 1, 1, f) != 1){
        return false;
    }

    *tipo = ((aux >> 1) & MASK_TIPO);
    
    *infinito = aux >> 6;
    

    if (fread(cantidad_polilineas, sizeof(uint16_t), 1, f) != 1){
        return false;
    }

    return true;
}





//---------------------------------POLILINEA------------------------
struct polilinea;
typedef struct polilinea polilinea_t;

struct polilinea {
    int x;
};

polilinea_t *polilinea_crear_vacia(size_t n) {
    printf("POLILINEA N=%zd\n", n);
    static polilinea_t x;
    return &x;
}

void polilinea_destruir(polilinea_t *polilinea) {}

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y) {
    printf("POLILINEA[%zd] = (%.2f, %.2f)\n", pos, x, y);
    return true;
}

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    uint8_t r, g, b;
    color_a_rgb(color, &r, &g, &b);
    printf("POLILINEA COLOR: (%d, %d, %d)\n", r, g, b);
    return true;
}


//---------------------------------POLILINEA------------------------






#define MASK_CANT_PUNTOS_POLI 0x03ff // 0000 0011 1111 1111
#define MASK_COLOR_POLI 0xe000 // 1110 0000 0000 0000



polilinea_t *leer_polilinea(FILE *f){
    polilinea_t *p;
    
    size_t a; 
    size_t n; // Corresponde a cantidad de puntos de la poli

    color_t c; // Correponde a los 3 bits del color de la poli


//    fread(&a, sizeof(uint16_t), 1, f);
    fread(&a, 2, 1, f);

    //agarro n del archivo para crear la poli de n puntos

    
    c = (a & MASK_COLOR_POLI) >> 13; // obtengo valores de color de encabezado
    //printf("\nEL COLOR ES %d\n", c);
    

    n = (a & MASK_CANT_PUNTOS_POLI);// obtengo valores de cantidad de puntos de encabezado
    if ((p = polilinea_crear_vacia(n)) == NULL){ // Creo la polilinea según cantidad de puntos obtendido. OPCIONAL: + 2 bytes (16 bits) que corresponden al encabezado
        return NULL;
    }


    //agarro color del archivo para settear color 
    if (polilinea_setear_color (p, c) == false){
        return NULL;
    }


    //agarro un punto, lea cada mitad y la meto en x e y de la funcion poli settear punto. Además la posición va a ser la variable a iterar


    float x; // Corresponde a la coordenada x de cada punto de la poli
    float y; // Corresponde a la coordenada y de cada punto de la poli

    for (size_t i = 0; i < n; i++){
        fread(&x, sizeof(float), 1, f);
        fread(&y, sizeof(float), 1, f);

        if (polilinea_setear_punto(p, i, x, y) == false){
            polilinea_destruir(p);
            return NULL;
        }
    }

    return p;

}




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



