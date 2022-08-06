#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "fisicas.h"
#include "config.h"
#include "disparo.h"
#include "nave.h"
#include "planeta.h"
#include "nivel.h"
#include "torreta.h"
#include "caracteres.h"
#include "combustible.h"
#include "reactor.h"

typedef enum tabla_niveles{
    NIVEL1,
    NIVEL2,
    NIVEL3,
    NIVEL4,
    NIVEL5,
};

const int tabla_bonus[] = {
    [NIVEL1] = 2000,
    [NIVEL2] = 4000,
    [NIVEL3] = 6000,
    [NIVEL4] = 8000,
    [NIVEL5] = 9000,
};

const size_t tabla_cant_torretas[] = {
    [NIVEL1] = 2,
    [NIVEL2] = 4,
    [NIVEL3] = 6,
    [NIVEL4] = 8,
    [NIVEL5] = 0,
};

const size_t tabla_cant_combustibles[] = {
    [NIVEL1] = 2,
    [NIVEL2] = 2,
    [NIVEL3] = 3,
    [NIVEL4] = 4,
    [NIVEL5] = 0,
};

const float tabla_ubicacion_torretas[][3] = {
    {916, 75, -0.66},
    {1425, 159, 0.66},

    {423, 195, -0.66},
    {806, 215, -0.33},
    {1254, 153, 0.66},
    {1587, 223, 2.23},

    {70, 46, 0},
    {506, 12, 0},
    {952, 12, 0},
    {1385, 12, 0},
    {757, 210, 3.14},
    {1161, 210, 3.14},

    {257, 440, 0.66},
    {719, 674, 2.23},
    {985, 565, 0},
    {1125, 417, 3.8},
    {862, 163, 3.8},
    {626, 323, 2.23}, 
    {505, 331, 3.8},
    {378, 296, 2.23},

};

const float tabla_ubicacion_combustibles[][3] = {
    {1064, 13, 0},
    {1685, 113, 0},

    {482, 94, 0},
    {1751, 247, 0},

    {820, 46, 0},
    {1196, 68, 0},
    {1602, 46, 0},

    {188, 429, 0},
    {667, 600, 0},
    {1054, 404, 3.14},
    {574, 344, 3.14},
};




//Dado un vector, su longitud y un nombre, encuentra la figura de ese nombre. Si no la encuentra devuelve NULL.
figura_t *encontrar_figura(char *nombre, figura_t **vector_figuras, size_t n){
    figura_t *fig = NULL;
    for (size_t i = 0; i < n; i++){
        if(strcmp(nombre, figura_get_nombre(vector_figuras[i])) == 0){
            fig = vector_figuras[i];
            break;
        }
    } 
    return fig;
}

//Dado un vector, su longitud y un tipo, devuelve un vector con todas las figuras de ese tipo. En caso de error devuelve NULL.
figura_t **vector_tipo_figura(figura_tipo_t tipo, const figura_t **vector_figuras, size_t n, size_t *cant){
    size_t cant_buf = 0;
    figura_t **vector = malloc(sizeof(figura_t*) * 1);
    if(vector == NULL) return NULL;

    for (size_t i = 0; i < n; i++){
        if(figura_get_tipo(vector_figuras[i]) == tipo){
            if(i >= 1){
                figura_t **aux = realloc(vector, sizeof(figura_t*) * (i + 1));
                if(aux == NULL){
                    free(vector);
                    return NULL;
                } 
            }
            vector[i] = vector_figuras[i];
            cant_buf++;
        }
    } 
    *cant = cant_buf;
    return vector;
}

//Función para crear torretas y combustibles en el nivel elegido y en su respectiva posicion y angulo
bool inicializar_listas_nivel(lista_t *lista_niveles, const figura_t *torreta, const figura_t *torreta_disparo, const figura_t *combustible){
    size_t cant_torretas_actual = 0;
    size_t cant_combustibles_actual = 0;
    lista_iter_t *iter = lista_iter_crear(lista_niveles);
    if(iter == NULL) return false;
    for(size_t i = 0; i < lista_largo(lista_niveles); i++){
        nivel_t *nivel_actual = lista_iter_ver_actual(iter);
        nivel_set_bonus(nivel_actual, tabla_bonus[i]);

        for(size_t j = cant_torretas_actual; j < cant_torretas_actual + tabla_cant_torretas[i]; j++){
            torreta_t *torreta_buf = torreta_crear(torreta, torreta_disparo, COOLDOWN_TORRETA, tabla_ubicacion_torretas[j][X], tabla_ubicacion_torretas[j][Y], tabla_ubicacion_torretas[j][ANG]);
            if(torreta_buf == NULL || !lista_insertar_ultimo(nivel_get_lista_torretas(nivel_actual), torreta_buf)){
                lista_iter_destruir(iter);
                return false;
            }
        }

        for(size_t j = cant_combustibles_actual; j < cant_combustibles_actual + tabla_cant_combustibles[i]; j++){
            combustible_t *combustible_buf = combustible_crear(combustible, tabla_ubicacion_combustibles[j][X], tabla_ubicacion_combustibles[j][Y], tabla_ubicacion_combustibles[j][ANG]);
            if(combustible_buf == NULL || !lista_insertar_ultimo(nivel_get_lista_torretas(nivel_actual), combustible_buf)){
                lista_iter_destruir(iter);
                return false;
            }
        }

        cant_torretas_actual += tabla_cant_torretas[i];
        cant_combustibles_actual += tabla_cant_combustibles[i];
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return true;

}

//Indica si hay un disparo en pantalla.
bool disparo_en_pantalla(SDL_Renderer *renderer, lista_t *lista_disparos, const figura_t *disparo_fig, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);
    
    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        
        if(disparo_get_tiempo(disp_act) > TIEMPO_MAX_DISPAROS){
            disparo_destruir(disp_act);
            lista_iter_borrar(iter);
            continue;
        }
        if(!disparo_act_figura(disp_act, disparo_fig)){
            return false;
        }
        disparo_aumentar_tiempo(disp_act, DT);
        disparo_avanzar(disp_act, DT);
        disparo_imprimir(renderer, disp_act, escala, escala_x, escala_y, tras_x, tras_y);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return true;
}


//Evualua el impacto de un disparo de una lista contra una figura.
bool disparo_pego(lista_t *lista_disparos, figura_t *figura, bool friendly){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);

    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        if((disparo_friendly(disp_act) && !friendly) || (!disparo_friendly(disp_act) && friendly)){
            if(distancia_punto_a_figura(figura, disparo_get_pos_x(disp_act), disparo_get_pos_y(disp_act)) <= DMIN){
                disparo_destruir(disp_act);
                lista_iter_borrar(iter);
                lista_iter_destruir(iter);
                return true;
            }
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}


//Evualua el impacto de un disparo de una lista contra un nivel.
void nivel_disparo_impacto(lista_t *lista_disparos, nivel_t *nivel){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);
    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        if(distancia_punto_a_figura(nivel_get_figura(nivel), disparo_get_pos_x(disp_act), disparo_get_pos_y(disp_act)) <= DMIN){
            disparo_destruir(disp_act);
            lista_iter_borrar(iter);
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}


//Itera dentro de la lista enlazada de combustibles
bool lista_iterar_combustibles(SDL_Renderer *renderer, lista_iter_t *iter, size_t n, nave_t *nave, const figura_t *combustible_fig, bool escudo, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    nave_escudo_setear_angulo(nave, 0);
    combustible_t *combustible_apuntado = NULL;
    
    float menor_distancia;
    float distancia;
    bool absorbido = false;

    for(size_t i = 0; i < n; i++){
        combustible_t *comb_act = lista_iter_ver_actual(iter);
        distancia = distancia_entre_puntos(nave_get_pos_x(nave), nave_get_pos_y(nave), combustible_get_pos_x(comb_act), combustible_get_pos_y(comb_act));
        if(i == 0){
            menor_distancia = distancia;
            combustible_apuntado = comb_act;
        } else if(distancia < menor_distancia){
            menor_distancia = distancia;
            combustible_apuntado = comb_act;
        }
        if(distancia_entre_puntos(nave_get_pos_x(nave), nave_get_pos_y(nave), combustible_get_pos_x(comb_act), combustible_get_pos_y(comb_act)) <= escala * DMIN_ESCUDO && escudo){
            lista_iter_borrar(iter);
            absorbido = true;
            continue;
        } 
        combustible_imprimir(renderer, comb_act, escala, escala_x, escala_y, tras_x, tras_y);
        lista_iter_avanzar(iter);
    }
    if(combustible_apuntado != NULL){
        nave_escudo_apuntar(nave, combustible_get_pos_x(combustible_apuntado), combustible_get_pos_y(combustible_apuntado));
    }

    return absorbido;
}


bool lista_iterar_torretas(SDL_Renderer *renderer, lista_t *lista_torreta, lista_t *lista_disparos, nave_t *nave, const figura_t *torreta_fig, const figura_t *torreta_disparo_fig, int *score, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    lista_iter_t *iter = lista_iter_crear(lista_torreta);
    if(iter == NULL) return false;

    for(size_t i = 0; i < lista_largo(lista_torreta); i++){
        torreta_t *torreta_act = lista_iter_ver_actual(iter);
        if(disparo_pego(lista_disparos, torreta_get_figura_principal(torreta_act), false)){
            torreta_destruir(torreta_act);
            lista_iter_borrar(iter);
            score[0] += 250;
            score[1] -= 250;
            continue;
        } 
        if(torreta_get_cooldown(torreta_act) <= 0 && torreta_apuntar(torreta_act, nave_get_pos_x(nave), nave_get_pos_y(nave)) && distancia_entre_puntos(nave_get_pos_x(nave), nave_get_pos_y(nave), torreta_get_pos_x(torreta_act), torreta_get_pos_y(torreta_act)) < (500 * escala)){
            double a = (VEL_DISPARO * cos(torreta_get_angulo_apuntado(torreta_act)));
            double b = (VEL_DISPARO * sin(torreta_get_angulo_apuntado(torreta_act)));
            disparo_t *disparo_buf = disparo_crear(torreta_get_pos_x(torreta_act)+20*cos(torreta_get_angulo(torreta_act)+PI/2), torreta_get_pos_y(torreta_act)+20*sin(torreta_get_angulo(torreta_act)+PI/2), a, b, torreta_get_angulo_apuntado(torreta_act), false);
            if(!lista_insertar_ultimo(lista_disparos, disparo_buf) || disparo_buf == NULL) return false;
            torreta_set_cooldown(torreta_act, COOLDOWN_TORRETA);
        } else if(torreta_get_cooldown(torreta_act) <= 7*COOLDOWN_TORRETA/8) torreta_imprimir(renderer, torreta_act, escala, escala_x, escala_y, tras_x, tras_y, false);
        torreta_imprimir(renderer, torreta_act, escala, escala_x, escala_y, tras_x, tras_y, true);

        torreta_restar_cooldown(torreta_act, DT);

        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return true;
}


bool nivel_en_pantalla(SDL_Renderer *renderer, nivel_t *nivel, nave_t *nave, lista_t *lista_disparos, const figura_t *torreta_fig, const figura_t *torreta_disparo_fig, const figura_t *combustible, int *score, bool escudo, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    nivel_disparo_impacto(lista_disparos, nivel);

    lista_iter_t *iter_comb = lista_iter_crear(nivel_get_lista_combustibles(nivel));

    if(iter_comb == NULL) return false;

    if(!lista_iterar_torretas(renderer, nivel_get_lista_torretas(nivel), lista_disparos, nave, torreta_fig, torreta_disparo_fig, score, escala, escala_x, escala_y, tras_x, tras_y)) return false;

    if(lista_iterar_combustibles(renderer, iter_comb, lista_largo(nivel_get_lista_combustibles(nivel)), nave, combustible, escudo, escala, escala_x, escala_y, tras_x, tras_y)){
        nave_sumar_combustible(nave, 3000);
    }

    nivel_imprimir(renderer, nivel, escala, escala_x, escala_y, tras_x, tras_y);
    lista_iter_destruir(iter_comb);
    return true;
}


void computar_escala_y_centro(nave_t *nave, float *escala_nivel, float *centro){
    float posicion_nave_x = nave_get_pos_x(nave);
    float posicion_nave_y = nave_get_pos_y(nave);

    if(posicion_nave_y > VENTANA_ALTO * MARGEN_ALTURA)
        *escala_nivel = VENTANA_ALTO * MARGEN_ALTURA / posicion_nave_y;

    if(*escala_nivel < ESCALA_MINIMA)
        *escala_nivel = ESCALA_MINIMA;
    if((posicion_nave_x - *centro) * (*escala_nivel) > VENTANA_ANCHO / 2 * MARGEN_ANCHO){
        *centro = posicion_nave_x - VENTANA_ANCHO / 2 * MARGEN_ANCHO / (*escala_nivel);
    }
    else if((*centro - posicion_nave_x) * (*escala_nivel) > VENTANA_ANCHO / 2 * MARGEN_ANCHO){
        *centro = posicion_nave_x + VENTANA_ANCHO / 2 * MARGEN_ANCHO / (*escala_nivel);
    }
}

int main() {
//----------------------------------------------------------------------------------------------------------------------
//SDL INICIALIZACIÓN
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

//----------------------------------------------------------------------------------------------------------------------
//CREACIÓN DE ESTRUCTURA DE LECTURA

    bool error_memoria = false;

    FILE *f1 = fopen("figuras.bin", "rb");
    if(f1 == NULL) {
        fprintf(stderr, "No pudo abrirse figuras.bin\n");
        return 1;
    }

    //Creamos un puntero que apunta a un vector "vector_figuras" de una (1) figura_t
    figura_t **vector_figuras = malloc(sizeof(figura_t*));
    if(vector_figuras == NULL){
        fprintf(stderr, "Error de memoria");
        fclose(f1);
        return 1;
    }

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cant_polilineas;

    size_t cant = 0;

    //Comenzamos a leer el archivo para sacar las figuras que tiene adentro
    for(size_t i = 0; leer_encabezado_figura(f1, nombre, &tipo, &infinito, &cant_polilineas); i++){
        if(i >= 1){
            figura_t **aux = realloc(vector_figuras, (i + 1) * sizeof(figura_t*)); //Agrega una componente a "vector_figuras" hasta que no pueda leer mas figuras
            if(aux == NULL){
                for(size_t j = 0; j < (i+1); j++){
                    figura_destruir(vector_figuras[j]);
                }
                free(vector_figuras);

                fprintf(stderr, "Error de memoria");
                fclose(f1);
                return 1;
            }
            vector_figuras = aux;
        }
        vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas); //Iguala cada componente a la figura leida del archivo
        if(vector_figuras[i] == NULL){
            fprintf(stderr, "Error de memoria");
            if(i >= 1){
                for(size_t j = 0; j < (i+1); j++){
                    figura_destruir(vector_figuras[j]);
                }
                free(vector_figuras);
                fclose(f1);
                return 1;
            }
            free(vector_figuras);
            fclose(f1);
            return 1;
        }

        polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * cant_polilineas); //Creamos un puntero que apunta a un vector "vector_polilineas" de "cant_polilineas" polilinea_t
        if(vector_polilineas == NULL){
            fprintf(stderr, "Error de memoria");
            for(size_t j = 0; j < (i+1); j++){
                figura_destruir(vector_figuras[j]);
            }
            free(vector_figuras);
            fclose(f1);
            return 1;
        }

        for(size_t j = 0; j < cant_polilineas; j++){
            vector_polilineas[j] = leer_polilinea(f1); //Iguala cada componente de las polilineas de cada figura leida del archivo
            if(vector_polilineas[j] == NULL){
                fprintf(stderr, "Error de memoria");
                if(j >= 1){
                    for(size_t l = 0; l < j; l++){
                        polilinea_destruir(vector_polilineas[l]);
                    }
                }
                free(vector_polilineas);

                for(size_t k = 0; k < (i+1); k++){
                    figura_destruir(vector_figuras[j]);
                }
                free(vector_figuras);

                fclose(f1);
                return 1;
            }
        }


        if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas)){
            fprintf(stderr, "Error de memoria.");

            for(size_t j = 0; j < cant_polilineas; j++){
                polilinea_destruir(vector_polilineas[j]);
            }
            free(vector_polilineas);

            for(size_t k = 0; k < i; k++){
                figura_destruir(vector_figuras[k]);
            }
            free(vector_figuras);

            return 1; 
        }

        cant++;
    }

    const size_t cant_figuras = cant;

    fclose(f1);
    
//----------------------------------------------------------------------------------------------------------------------
//CREACION DE ENTIDADES (con referencias a las figuras del vector_figuras para no buscarlas nuevamente por cada dt)

    //Creación de planetas
    planeta_t *base = planeta_crear(encontrar_figura("BASE", vector_figuras, cant_figuras), 388, 218);
    if(base == NULL) error_memoria = true;

    planeta_t *estrella = planeta_crear(encontrar_figura("ESTRELLA", vector_figuras, cant_figuras), 457, 364);
    if(estrella == NULL) error_memoria = true;

    planeta_t *planeta1 = planeta_crear(encontrar_figura("PLANETA1", vector_figuras, cant_figuras), 663, 473);
    if(planeta1 == NULL) error_memoria = true;

    planeta_t *planeta2 = planeta_crear(encontrar_figura("PLANETA2", vector_figuras, cant_figuras), 671, 145);
    if(planeta2 == NULL) error_memoria = true;
    
    planeta_t *planeta3 = planeta_crear(encontrar_figura("PLANETA3", vector_figuras, cant_figuras), 110, 79);
    if(planeta3 == NULL) error_memoria = true;

    planeta_t *planeta4 = planeta_crear(encontrar_figura("PLANETA4", vector_figuras, cant_figuras), 204, 455);
    if(planeta4 == NULL) error_memoria = true;

    planeta_t *planeta5 = planeta_crear(encontrar_figura("PLANETA5", vector_figuras, cant_figuras), 111, 307);
    if(planeta5 == NULL) error_memoria = true;

    //Creación de entidades
    reactor_t *reactor = reactor_crear(encontrar_figura("REACTOR", vector_figuras, cant_figuras), 815, 309, 0);
    if(reactor == NULL) error_memoria = true;

    nave_t *nave = nave_crear(JUEGO_COMBUSTIBLE_INICIAL);
    if(nave == NULL) error_memoria = true;

    const figura_t *nave_fig = encontrar_figura("NAVE", vector_figuras, cant_figuras);
    const figura_t *nave_chorro_fig = encontrar_figura("NAVE+CHORRO", vector_figuras, cant_figuras);
    const figura_t *escudo_fig = encontrar_figura("ESCUDO", vector_figuras, cant_figuras);
    const figura_t *escudo2_fig = encontrar_figura("ESCUDO2", vector_figuras, cant_figuras);
    const figura_t *disparo_fig = encontrar_figura("DISPARO", vector_figuras, cant_figuras);
    const figura_t *combustible_fig = encontrar_figura("COMBUSTIBLE", vector_figuras, cant_figuras);
    const figura_t *torreta_fig= encontrar_figura("TORRETA", vector_figuras, cant_figuras);
    const figura_t *torreta_disparo_fig = encontrar_figura("TORRETA+DISPARO", vector_figuras, cant_figuras);

    lista_t *lista_niveles = lista_crear();
    
    //Creación de niveles
    size_t cant_niveles = 0; 

    vector_figura_niveles = fig

    for(size_t i = 0; i < cant_niveles){
        nivel_t *nivel_buf = nivel_crear(vector_figura_niveles[i]);

        if(nivel_buf == NULL || !lista_insertar_ultimo(lista_niveles, nivel_buf)){
            error_memoria = true;
            break;
        }
    }

    if(!inicializar_listas_nivel(lista_niveles, torreta_fig, torreta_disparo_fig, combustible_fig)) error_memoria = true;

    nivel_t *nivel_actual = NULL;

    lista_t *lista_disparos = lista_crear();
    if(lista_disparos == NULL) error_memoria = true;

//--------------------------------------------------------------------------------------------------------------------------

    //Boleeanos de estado
    bool salir = false;
    bool chorro_prendido = false;
    bool escudo_prendido = false;

    bool reactor_destruido = false;

    bool disparo = false;
    double tiempo_para_disparar = COOLDOWN_NAVE;
    bool listo_para_disparar = true;
    
    //Boleeanos de movimiento
    bool rotacion_horaria = false;
    bool rotacion_antihoraria = false;
    bool avanzar = false;

    size_t nivel = 0;
    int vidas = JUEGO_VIDAS;
    int score[2] = {0, SCORE_NEXT_SHIP};
    
    double tiempo_reactor = TIEMPO_REACTOR;
    
    bool spawn = true;

    //Valores de impresión
    float escala_nivel = 1;
    float centro = 0;

    float ancho_nivel_x = 0;
    float alto_nivel_y = 0;

    float margen_nivel_x = 0;
    float margen_nivel_y = 0;

    unsigned int ticks = SDL_GetTicks();

    while(!error_memoria) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        avanzar = true;
                        chorro_prendido = true;
                        break;

                    case SDLK_RIGHT:
                        rotacion_horaria = true;
                        break;

                    case SDLK_LEFT:
                        rotacion_antihoraria = true;
                        break;

                    case SDLK_SPACE:
                        disparo = true;
                        break;
                    
                    case SDLK_LALT:
                        escudo_prendido = true;
                        break;
                        
                    case SDLK_ESCAPE:
                        salir = true;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        avanzar = false;
                        chorro_prendido = false;
                        break;
                    case SDLK_RIGHT:
                        rotacion_horaria = false;
                        break;
                    case SDLK_LEFT:
                        rotacion_antihoraria = false;
                        break;
                    case SDLK_SPACE:
                        disparo = false;
                        break;
                    case SDLK_LALT:
                        escudo_prendido = false;
                        break;
                }
            }
            continue;
        }

        if(salir){
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno en while

        char cadena[15];
        sprintf(cadena, "%d", nave_get_combustible(nave));
        cadena_imprimir_centrado(renderer, cadena, VENTANA_ANCHO/4, 36*VENTANA_ALTO/40, 2.5, color_crear(false, true, false));
        cadena_imprimir_centrado(renderer, "FUEL", VENTANA_ANCHO/2, 36*VENTANA_ALTO/40, 2.5, color_crear(false, true, true));
        sprintf(cadena, "%d", score[0]);
        cadena_imprimir_centrado(renderer, cadena, 3*VENTANA_ANCHO/4, 38*VENTANA_ALTO/40, 2.5, color_crear(false, true, false));
        cadena_imprimir_centrado(renderer, "SCORE", VENTANA_ANCHO/2, 38*VENTANA_ALTO/40, 2.5, color_crear(false, true, true));

        char next_c[15] = "NEXT SHIP";
        sprintf(cadena, "%d", score[1]);
        cadena_imprimir_centrado(renderer, next_c, 3*VENTANA_ANCHO/7, 34*VENTANA_ALTO/40, 2.5, color_crear(false, true, true));
        cadena_imprimir_centrado(renderer, cadena, 4*VENTANA_ANCHO/7, 34*VENTANA_ALTO/40, 2.5, color_crear(false, true, false));

        for(size_t i = 0; i < vidas; i++){
            cadena_imprimir(renderer, "n", VENTANA_ANCHO/20 + 20*i, 38*VENTANA_ALTO/40, 1.40, color_crear(true, false, false));
        }

        if(!nave_act_figura(nave, nave_fig, nave_chorro_fig, escudo_fig, escudo2_fig)){
            error_memoria = true;
            break;
        }
        
        nave_apagar(nave, true, true, true);

        if(nivel != 0 && nivel != 5){
            nave_prender(nave, chorro_prendido, false, escudo_prendido);
        } else {
            nave_prender(nave, chorro_prendido, escudo_prendido, false);
        }

        if(chorro_prendido){
            nave_sumar_combustible(nave, -JUEGO_COMBUSTIBLE_POT_X_SEG * DT);
        }   
        if(escudo_prendido){
            nave_sumar_combustible(nave, -JUEGO_COMBUSTIBLE_ESC_X_SEG * DT);
        }

        if(rotacion_antihoraria){
            nave_rotar(nave, + NAVE_ROTACION_PASO * DT); //Depende de DT pues se comporta como una velocidad ángular
        }

        if(rotacion_horaria){
            nave_rotar(nave, - NAVE_ROTACION_PASO * DT); //Depende de DT pues se comporta como una velocidad ángular    
        } 

        if(avanzar){
            nave_avanzar(nave, NAVE_ACELERACION, DT);
        }else{
            nave_avanzar(nave, 0, DT);
        }

        if(spawn){
            lista_destruir(lista_disparos, (void (*)(void*))disparo_destruir);
            lista_disparos = lista_crear();
            if(lista_disparos == NULL){
                error_memoria = true;
                break;
            }
        }

        if(nivel == 0){
            if(spawn){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, planeta_get_pos_x(base), planeta_get_pos_y(base), 0);
                spawn = false;
                lista_destruir(lista_disparos, (void (*)(void*))disparo_destruir);
                lista_disparos = lista_crear();
                if(lista_disparos == NULL){
                    error_memoria = true;
                    break;
                }
            }

            planeta_imprimir(renderer, base, ESCALA_NIVEL_0, planeta_get_pos_x(base), planeta_get_pos_y(base), 0, 0);
            planeta_imprimir(renderer, estrella, ESCALA_NIVEL_0, planeta_get_pos_x(estrella), planeta_get_pos_y(estrella), 0, 0);
            planeta_imprimir(renderer, planeta1, ESCALA_NIVEL_0, planeta_get_pos_x(planeta1), planeta_get_pos_y(planeta1), 0, 0);
            planeta_imprimir(renderer, planeta2, ESCALA_NIVEL_0, planeta_get_pos_x(planeta2), planeta_get_pos_y(planeta2), 0, 0);
            planeta_imprimir(renderer, planeta3, ESCALA_NIVEL_0, planeta_get_pos_x(planeta3), planeta_get_pos_y(planeta3), 0, 0);
            planeta_imprimir(renderer, planeta4, ESCALA_NIVEL_0, planeta_get_pos_x(planeta4), planeta_get_pos_y(planeta4), 0, 0);
            planeta_imprimir(renderer, planeta5, ESCALA_NIVEL_0, planeta_get_pos_x(planeta5), planeta_get_pos_y(planeta5), 0, 0);
            
            cadena_imprimir_centrado(renderer, "2000", 663 + 40, 473 + 20, 1.5, color_crear(false, true, true));
            cadena_imprimir_centrado(renderer, "4000", 671 + 40, 145 - 30, 1.5, color_crear(false, true, true));
            cadena_imprimir_centrado(renderer, "6000", 110 - 0, 79 - 30, 1.5, color_crear(false, true, true));
            cadena_imprimir_centrado(renderer, "8000", 204 - 40, 455 + 20, 1.5, color_crear(false, true, true));
            cadena_imprimir_centrado(renderer, "9000", 111 - 40, 307 - 15, 1.5, color_crear(false, true, true));

            if(nave_get_pos_x(nave) < 0 || nave_get_pos_x(nave) > VENTANA_ANCHO){
                nave_invertir_vel_x(nave);
            }
            if(nave_get_pos_y(nave) < 0 || nave_get_pos_y(nave) > VENTANA_ALTO){
                nave_invertir_vel_y(nave);
            }

            nave_acercar(nave, G, planeta_get_pos_x(estrella), planeta_get_pos_y(estrella), DT);

            if(distancia_a_planeta(estrella, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 5){
                vidas--;
                spawn = true;
                continue;
            }
            if(distancia_a_planeta(planeta1, nave_get_pos_x(nave), nave_get_pos_y(nave)) < DMIN){
                spawn = true;
                nivel_actual = nivel_1;
                nivel = 1;
                continue;
            }
            if(distancia_a_planeta(planeta2, nave_get_pos_x(nave), nave_get_pos_y(nave)) < DMIN){
                spawn = true;
                nivel_actual = nivel_2;
                nivel = 2;
                continue;
            }
            if(distancia_a_planeta(planeta3, nave_get_pos_x(nave), nave_get_pos_y(nave)) < DMIN){
                spawn = true;
                nivel_actual = nivel_3;
                nivel = 3;
                continue;
            }
            if(distancia_a_planeta(planeta4, nave_get_pos_x(nave), nave_get_pos_y(nave)) < DMIN){
                spawn = true;
                nivel_actual = nivel_4;
                nivel = 4;
                continue;
            }
            if(distancia_a_planeta(planeta5, nave_get_pos_x(nave), nave_get_pos_y(nave)) < DMIN){
                spawn = true;
                nivel_actual = nivel_5;
                nivel = 5;
                continue;
            }
            if(!disparo_en_pantalla(renderer, lista_disparos, disparo_fig, ESCALA_NIVEL_0, nave_get_pos_x(nave), nave_get_pos_y(nave), 0, 0)){
                error_memoria = true;
                break;
            }
            nave_imprimir(renderer, nave, ESCALA_NIVEL_0, nave_get_pos_x(nave), nave_get_pos_y(nave), 0, 0);
        }

        if(nivel_actual != NULL && nivel_get_infinito(nivel_actual)){
            ancho_nivel_x = nivel_get_extremo_x(nivel_actual, true) - nivel_get_extremo_x(nivel_actual, false);

            if(spawn == true){
                centro = ancho_nivel_x/2;
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, ancho_nivel_x/2, 1000, -PI/2);
                spawn = false;
                lista_destruir(lista_disparos, (void (*)(void*))disparo_destruir);
                lista_disparos = lista_crear();
                if(lista_disparos == NULL){
                    error_memoria = true;
                    break;
                }
            }

            computar_escala_y_centro(nave, &escala_nivel, &centro);

            if(nave_get_pos_x(nave) > nivel_get_extremo_x(nivel_actual, true)){
                nave_setear_posicion(nave, nivel_get_extremo_x(nivel_actual, false), nave_get_pos_y(nave), nave_get_angulo(nave));
                centro -= ancho_nivel_x;
            }

            if(nave_get_pos_x(nave) < nivel_get_extremo_x(nivel_actual, false)){
                nave_setear_posicion(nave, nivel_get_extremo_x(nivel_actual, true), nave_get_pos_y(nave), nave_get_angulo(nave));
                centro += ancho_nivel_x;
            }

            if(!disparo_en_pantalla(renderer, lista_disparos, disparo_fig, escala_nivel, 0, 0, (-centro + VENTANA_ANCHO/2/escala_nivel) * escala_nivel, 0)){
                error_memoria = true;
                break;
            }
            if(!nivel_en_pantalla(renderer, nivel_actual, nave, lista_disparos, torreta_fig, torreta_disparo_fig, combustible_fig, score, escudo_prendido, escala_nivel, 0, 0, (-centro + VENTANA_ANCHO/2/escala_nivel) * escala_nivel, 0)){
                error_memoria = true;
                break;
            }
            nave_acercar_direccion(nave, G, -PI/2, DT);
            nave_imprimir(renderer, nave, escala_nivel, 0, 0, (-centro + VENTANA_ANCHO/2/escala_nivel) * escala_nivel, 0);
        }

        if(nivel_actual != NULL && !nivel_get_infinito(nivel_actual)){
            
            ancho_nivel_x = nivel_get_extremo_x(nivel_actual, true);    //contempla el margen izquierdo
            alto_nivel_y = nivel_get_extremo_y(nivel_actual, true);     //contempla el margen inferior

            margen_nivel_x = nivel_get_extremo_x(nivel_actual, false);
            margen_nivel_y = nivel_get_extremo_y(nivel_actual, false);

            escala_nivel = VENTANA_ALTO * 1.0 / alto_nivel_y;
            
            if(VENTANA_ANCHO * 1.0 / (ancho_nivel_x + margen_nivel_x) < escala_nivel)
                escala_nivel = VENTANA_ANCHO * 1.0 / (ancho_nivel_x + margen_nivel_x);

            nave_acercar_direccion(nave, G, -PI/2, DT);
            
            if(nivel == 4){
                if(spawn){
                    nave_setear_velocidad(nave, 0, 0);
                    nave_setear_posicion(nave, (ancho_nivel_x + margen_nivel_x)/4, (alto_nivel_y + margen_nivel_y) * 0.8, 0);
                    spawn = false;
                }
                
            }
            if(nivel == 5){
                if(spawn){
                    nave_setear_velocidad(nave, 0, 0);
                    nave_setear_posicion(nave, 2*(ancho_nivel_x + margen_nivel_x)/6, (alto_nivel_y + margen_nivel_y) * 0.9, 0);
                    tiempo_reactor = TIEMPO_REACTOR;
                    spawn = false;
                }
                
                if(nivel_get_bonus(nivel_actual) != 0){
                    entero_imprimir_centrado(renderer, (int)tiempo_reactor + 1, VENTANA_ANCHO/2, 32*VENTANA_ALTO/40, 2.5, color_crear(false, true, true));
                    if((tiempo_reactor-= DT) <= 0){
                        vidas--;
                        tiempo_reactor = TIEMPO_REACTOR;
                        spawn = true;
                        reactor_destruido = false;
                        continue;
                    }
                }

                if(!reactor_destruido){
                    reactor_imprimir(renderer, reactor, escala_nivel, 0, margen_nivel_y*escala_nivel, 0, 0);
                    if(disparo_pego(lista_disparos, reactor_get_figura(reactor), false)){
                        reactor_destruido = true;
                    }
                }
            }

            if(nave_get_pos_x(nave) < 0){
                nave_setear_posicion(nave, ancho_nivel_x + margen_nivel_x, nave_get_pos_y(nave), nave_get_angulo(nave));
            }
            if(nave_get_pos_x(nave) > ancho_nivel_x + margen_nivel_x){
                nave_setear_posicion(nave, 0, nave_get_pos_y(nave), nave_get_angulo(nave));
            }
            if(nave_get_pos_y(nave) <= -margen_nivel_y*escala_nivel){
                vidas--;
                spawn = true;
                continue;
            }

            if(!disparo_en_pantalla(renderer, lista_disparos, disparo_fig, escala_nivel, 0, margen_nivel_y*escala_nivel, 0, 0)){
                error_memoria = true;
                break;
            }
            if(!nivel_en_pantalla(renderer, nivel_actual, nave, lista_disparos, torreta_fig, torreta_disparo_fig, combustible_fig, score, escudo_prendido, escala_nivel, 0, margen_nivel_y*escala_nivel, 0, 0)){
                error_memoria = true;
                break;
            }
            nave_imprimir(renderer, nave, escala_nivel, 0, margen_nivel_y*escala_nivel, 0, 0);
        }

        if(nivel_actual != NULL && distancia_punto_a_figura(nivel_get_figura(nivel_actual), nave_get_pos_x(nave), nave_get_pos_y(nave)) < 7){
            vidas--;
            spawn = true;
            if(nivel == 5 && nivel_get_bonus(nivel_actual) != 0){
                reactor_destruido = false;
            }
            continue;
        }

        if(nivel_actual != NULL && nave_get_pos_y(nave) > VENTANA_ALTO/ESCALA_MINIMA){
            if(nivel !=5 && lista_largo(nivel_get_lista_torretas(nivel_actual)) == 0){
                score[0] += nivel_get_bonus(nivel_actual);
                score[1] -= nivel_get_bonus(nivel_actual);
                nivel_set_bonus(nivel_actual, 0);
            }
            if(nivel == 5 && reactor_destruido){
                score[0] += nivel_get_bonus(nivel_actual);
                score[1] -= nivel_get_bonus(nivel_actual);
                nivel_set_bonus(nivel_actual, 0);
            }
            nivel = 0;
            nivel_actual = NULL;
            spawn = true;
        }

        if(vidas == 0){
            printf("GAME OVER.\n");
            break;
        }
        if(nave_get_combustible(nave) <= 0){
            printf("GAME OVER\nTE QUEDASTE SIN COMBUSTIBLE.\n");
            break;
        }

        if(!nave_estado_escudo(nave) && nivel != 0){
            if(disparo_pego(lista_disparos, nave_get_figura_principal(nave), true)){
                vidas--;
                spawn = true;
                continue;
            }
        }

        if(disparo && listo_para_disparar){
            double coseno = cos(nave_get_angulo(nave));
            double seno = sin(nave_get_angulo(nave));
            double c = (VEL_DISPARO * coseno);
            double d = (VEL_DISPARO * seno);
            disparo_t *disparo_buf = disparo_crear(nave_get_pos_x(nave)+7*coseno, nave_get_pos_y(nave)+7*seno, c, d, nave_get_angulo(nave), true);
            if(!lista_insertar_ultimo(lista_disparos, disparo_buf) || disparo_buf == NULL){
                error_memoria = true;
                break;
            }
            listo_para_disparar = false;
        }
        tiempo_para_disparar -= DT;

        if(tiempo_para_disparar <= 0){
            tiempo_para_disparar = COOLDOWN_NAVE;
            listo_para_disparar = true;
        }

        if(score[1] <= 0){
            score[1] = SCORE_NEXT_SHIP;
            vidas++;
        }

        // END código del alumno while

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

//--------------------------------------------------------------------------------------------------------------------------
//DESTRUCCION DE ENTIDADES
    nave_destruir(nave);

    lista_destruir(lista_disparos, (void (*)(void*))combustible_destruir);

    planeta_destruir(base);
    planeta_destruir(estrella);
    planeta_destruir(planeta1);
    planeta_destruir(planeta2);
    planeta_destruir(planeta3);
    planeta_destruir(planeta4);
    planeta_destruir(planeta5);

    reactor_destruir(reactor);

    lista_destruir(lista_niveles, (void (*)(void*))nivel_destruir);

    for(size_t i = 0; i < cant_figuras; i++){
        figura_destruir(vector_figuras[i]);
    }
    free(vector_figuras);

    if(error_memoria){
        fprintf(stderr, "Error de memoria\n");
        return 1;  
    } 

    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
//FIN DEL PROGRAMA