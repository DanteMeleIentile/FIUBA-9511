#include <SDL2/SDL.h>
#include <stdbool.h>

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



//SI DISPARO_LEIDO SE VUELVE FALSE, HUBO UN ERROR EN LA MEMORIA
float computar_escala_nivel(figura_t *figura){

    float planeta_ancho = figura_get_extremo_x(figura, true) - figura_get_extremo_x(figura, false);
    float planeta_alto = figura_get_extremo_y(figura, true) - figura_get_extremo_y(figura, false);

    float escala_no_infinito = VENTANA_ALTO * 1.0 / planeta_alto;

    if(VENTANA_ANCHO * 1.0 / (planeta_ancho - figura_get_extremo_x(figura, false)) < escala_no_infinito)
        escala_no_infinito = VENTANA_ANCHO * 1.0 / planeta_ancho;
    
    printf("ESCALA: %f\n", escala_no_infinito);

    return escala_no_infinito;
}

void main_disparo_en_pantalla(SDL_Renderer *renderer, lista_t *lista_disparos, figura_t *disparo_leido, double escala){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);

    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        
        if(disparo_get_tiempo(disp_act) > TIEMPO_MAX_DISPAROS){
            disparo_destruir(disp_act);
            lista_iter_borrar(iter);
            continue;
        }

        if(!disparo_act_figura(disp_act, disparo_leido)){
            fprintf(stderr, "Error en memoria\n");
            disparo_leido = NULL;
        }

        disparo_aumentar_tiempo(disp_act, DT);

        disparo_avanzar(disp_act, DT);
        
            disparo_imprimir(renderer, disp_act, escala);
            lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

bool main_disparo_pego(lista_t *lista_disparos, figura_t *figura, double dmin, bool friendly){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);

    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        if((disparo_friendly(disp_act) && !friendly) || (!disparo_friendly(disp_act) && friendly)){
            if(distancia_punto_a_figura(figura, disparo_get_pos_x(disp_act), disparo_get_pos_y(disp_act)) <= dmin){
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

void main_nivel_disparo_impacto(lista_t *lista_disparos, nivel_t *nivel, double dmin){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);
    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        if(distancia_punto_a_figura(nivel_get_figura(nivel), disparo_get_pos_x(disp_act), disparo_get_pos_y(disp_act)) <= dmin){
            disparo_destruir(disp_act);
            lista_iter_borrar(iter);
            break;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

//Itera dentro de la lista enlazada de combustibles
bool lista_iterar_combustibles(SDL_Renderer *renderer, lista_t *lista_combustible, nave_t *nave, double escala, figura_t *combustible_leido, bool escudo){
    lista_iter_t *iter = lista_iter_crear(lista_combustible);
    bool absorbido = false;
    if(iter == NULL){
        fprintf(stderr, "Error en memoria\n");
        combustible_leido = NULL;
        return false;
    }
    for(size_t i = 0; i < lista_largo(lista_combustible); i++){
        combustible_t *comb_act = lista_iter_ver_actual(iter);
        if(comb_act == NULL){
            fprintf(stderr, "Error en memoria\n");
            combustible_leido = NULL;
            lista_iter_destruir(iter);
            return false;
        }
        if(distancia_entre_puntos(nave_get_pos_x(nave), nave_get_pos_y(nave), combustible_get_pos_x(comb_act), combustible_get_pos_y(comb_act)) <= escala * 50 && escudo){
            lista_iter_borrar(iter);
            absorbido = true;
        } 
        if(!combustible_act_figura(comb_act, combustible_leido)){
            fprintf(stderr, "Error en memoria\n");
            combustible_leido = NULL;
            return false;
        }
        combustible_imprimir(renderer, comb_act, escala);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return absorbido;
}


void lista_iterar_torretas(SDL_Renderer *renderer, lista_t *lista_torreta, lista_t *lista_disparos, float movil_x, float movil_y, float escala, figura_t *torreta_fig, figura_t *torreta_disparo_fig, int *score){
    lista_iter_t *iter = lista_iter_crear(lista_torreta);
    for(size_t i = 0; i < lista_largo(lista_torreta); i++){
        torreta_t *torreta_act = lista_iter_ver_actual(iter);
        if(main_disparo_pego(lista_disparos, torreta_get_figura_principal(torreta_act), 15, false)){
            torreta_destruir(torreta_act);
            lista_iter_borrar(iter);
            score[0] += 250;
            score[1] -= 250;
            continue;
        } 
        torreta_act_figura(torreta_act, torreta_fig, torreta_disparo_fig);

        if(torreta_get_cooldown(torreta_act) <= 0 && torreta_apuntar(torreta_act, movil_x, movil_y)){
            double a = (VEL_DISPARO * cos(torreta_get_angulo_apuntado(torreta_act)));
            double b = (VEL_DISPARO * sin(torreta_get_angulo_apuntado(torreta_act)));
            lista_insertar_ultimo(lista_disparos, disparo_crear(torreta_get_pos_x(torreta_act)+20*sin(torreta_get_angulo(torreta_act)), torreta_get_pos_y(torreta_act)+20*cos(torreta_get_angulo(torreta_act)), a, b, torreta_get_angulo_apuntado(torreta_act), false));
            torreta_set_cooldown(torreta_act, COOLDOWN_TORRETA);

        } else if(torreta_get_cooldown(torreta_act) <= 7*COOLDOWN_TORRETA/8) torreta_imprimir(renderer, torreta_act, escala, false);
        torreta_imprimir(renderer, torreta_act, escala, true);

        torreta_restar_cooldown(torreta_act, DT);

        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void main_nivel_en_pantalla(SDL_Renderer *renderer, nivel_t *nivel, nave_t *nave, lista_t *lista_disparos, double escala, figura_t *torreta, figura_t *torreta_disparo, figura_t *combustible, int *score, bool escudo){
    main_nivel_disparo_impacto(lista_disparos, nivel, 7);

    lista_iterar_torretas(renderer, nivel_get_lista_torretas(nivel), lista_disparos, nave_get_pos_x(nave), nave_get_pos_y(nave), 1, torreta, torreta_disparo, score);
    if(lista_iterar_combustibles(renderer, nivel_get_lista_combustibles(nivel), nave, 1, combustible, escudo)){
        nave_sumar_combustible(nave, 3000);
    }
    if(lista_largo(nivel_get_lista_torretas(nivel)) == 0){
        score[0] += nivel_get_bonus(nivel);
        score[1] -= nivel_get_bonus(nivel);
    }
    
    nivel_imprimir(renderer, nivel, escala);
}

//Inicializo cada una de las torretas y combustibles en cada lista enlazada de cada nivel
void crear_listas_nivel(nivel_t *nivel, size_t numero){
    if(numero == 1){
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 916, 75, -0.66));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 1425, 159, 0.66));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(1064, 13, 0));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(1685, 113, 0));
    }
    if(numero == 2){
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 423, 195, -0.66));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 806, 215, -0.33));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 1254, 153, 0.66));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 1587, 223, 2.23));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(482, 94, 0));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(1751, 247, 0));
    }
    if(numero == 3){
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 70, 46, 0));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 506, 12, 0));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 985, 565, 0));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 1385, 12, 0));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 757, 210, 3.14));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 1161, 210, 3.14));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(820, 46, 0));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(1196, 68, 0));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(1602, 46, 0));
    }
    if(numero == 4){
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 257, 440, 0.66));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 719, 674, 2.23));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 985, 565, 0));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 1125, 417, 3.8));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 862, 163, 3.8));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 626, 323, 2.23));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 505, 331, 3.8));
        lista_insertar_ultimo(nivel_get_lista_torretas(nivel), torreta_crear(COOLDOWN_TORRETA, 378, 296, 2.23));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(188, 429, 0));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(667, 600, 0));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(1054, 404, 3.14));
        lista_insertar_ultimo(nivel_get_lista_combustibles(nivel), combustible_crear(574, 344, 3.14));
    }
}

figura_t *encontrar_figura(char *nombre, figura_t **vector_figuras, size_t n){ // Esta funcion como que ya está clonando
    figura_t *fig;
    for (size_t i = 0; i < n; i++){
        if(strcmp(nombre, vector_figuras[i]->nombre) == 0){
            fig = vector_figuras[i];
            break;
        }
    } 
    return fig;
}

int main() {
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno

//----------------------------------------------------------------------------------------------------------------------
//CREACIÓN DE ESTRUCTURA DE LECTURA


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

    for(size_t i = 0; leer_encabezado_figura(f1, nombre, &tipo, &infinito, &cant_polilineas); i++){
        if(i != 0){
            vector_figuras = realloc(vector_figuras, (i + 1) * sizeof(figura_t*)); //Agrega una componente a "vector_figuras" hasta que no pueda leer mas figuras
            if(vector_figuras == NULL){
                fclose(f1);
                return 1;
            }
        }
        vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas); //Iguala cada componente a la figura leida del archivo

        if(vector_figuras[i] == NULL){
            if(i >= 1){
                for(size_t m = 0; m < i; m++){
                    figura_destruir(vector_figuras[m]);
                }
                fclose(f1);
                return 1;
            }
        }

        polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * cant_polilineas); //Creamos un puntero que apunta a un vector "vector_polilineas" de "cant_polilineas"z polilinea_t

        if(vector_polilineas == NULL){
            fprintf(stderr, "Error de memoria");
            free(vector_figuras);
            fclose(f1);
            return 1;
        }

        for(size_t j = 0; j < cant_polilineas; j++){
            vector_polilineas[j] = leer_polilinea(f1); //Iguala cada componente de las polilineas de cada figura leida del archivo
            if(vector_polilineas[j] == NULL){
                if(j >= 1){
                    for(size_t l = 0; l < j; l++){
                        polilinea_destruir(vector_polilineas[l]);
                    }
                }
                free(vector_polilineas);
                free(vector_figuras);
                fclose(f1);
                return 1;
            }
        }

        if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas)){
            fprintf(stderr, "ERROR");
            return 1; // ERROR 
        }

        cant++;
    }

    const size_t cant_figuras = cant;

    fclose(f1);

//Creación de entidades (Creamos referencias a las figuras del vector_figuras para no buscarlas nuevamente por cada dt)

    figura_t *nave_leida = encontrar_figura("NAVE", vector_figuras, cant_figuras);
    figura_t *nave_mas_chorro_leida = encontrar_figura("NAVE+CHORRO", vector_figuras, cant_figuras);
    figura_t *escudo_leido = encontrar_figura("ESCUDO", vector_figuras, cant_figuras);
    figura_t *escudo2_leido = encontrar_figura("ESCUDO2", vector_figuras, cant_figuras);

    figura_t *combustible_leido = encontrar_figura("COMBUSTIBLE", vector_figuras, cant_figuras);

    figura_t *disparo_leido = encontrar_figura("DISPARO", vector_figuras, cant_figuras);

    figura_t *nivel1_leido = encontrar_figura("NIVEL1NE", vector_figuras, cant_figuras);
    figura_t *nivel2_leido = encontrar_figura("NIVEL1SE", vector_figuras, cant_figuras);
    figura_t *nivel3_leido = encontrar_figura("NIVEL1SW", vector_figuras, cant_figuras);
    figura_t *nivel4_leido = encontrar_figura("NIVEL1NW", vector_figuras, cant_figuras);
    figura_t *nivel5_leido = encontrar_figura("NIVEL1R", vector_figuras, cant_figuras);

    figura_t *torreta_leida = encontrar_figura("TORRETA", vector_figuras, cant_figuras);

    figura_t *torreta_disparo_leida = encontrar_figura("TORRETA+DISPARO", vector_figuras, cant_figuras);

    figura_t *reactor_leido = encontrar_figura("REACTOR", vector_figuras, cant_figuras);

    planeta_t base = planeta_crear(encontrar_figura("BASE", vector_figuras, cant_figuras), 388, 218);
    planeta_t estrella = planeta_crear(encontrar_figura("ESTRELLA", vector_figuras, cant_figuras), 457, 364);
    planeta_t planeta1 = planeta_crear(encontrar_figura("PLANETA1", vector_figuras, cant_figuras), 663, 473);
    planeta_t planeta2 = planeta_crear(encontrar_figura("PLANETA2", vector_figuras, cant_figuras), 671, 145);
    planeta_t planeta3 = planeta_crear(encontrar_figura("PLANETA3", vector_figuras, cant_figuras), 110, 79);
    planeta_t planeta4 = planeta_crear(encontrar_figura("PLANETA4", vector_figuras, cant_figuras), 204, 455);
    planeta_t planeta5 = planeta_crear(encontrar_figura("PLANETA5", vector_figuras, cant_figuras), 111, 307);

    nave_t *nave = nave_crear(10000);
    if(nave == NULL){
        fprintf(stderr, "Error de memoria");
        return 1;
    }
    
//Creación de niveles

    nivel_t *nivel_1 = nivel_crear(nivel1_leido, NULL, 2000);
    if(nivel_1 == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }
    crear_listas_nivel(nivel_1, 1);

    nivel_t *nivel_2 = nivel_crear(nivel2_leido, NULL, 4000);
    if(nivel_2 == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }
    crear_listas_nivel(nivel_2, 2);

    nivel_t *nivel_3 = nivel_crear(nivel3_leido, NULL, 6000);
    if(nivel_3 == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }
    crear_listas_nivel(nivel_3, 3);

    nivel_t *nivel_4 = nivel_crear(nivel4_leido, NULL, 8000);
    if(nivel_4 == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }
    crear_listas_nivel(nivel_4, 4);

    reactor_t *reactor_5 = reactor_crear(reactor_leido, 815, 309, 0);

    nivel_t *nivel_5 = nivel_crear(nivel5_leido, reactor_5, 9000);
    if(nivel_5 == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    nivel_t *nivel_actual;

    //Creación de listase e iteradores para elementos repetidos.
    lista_t *lista_disparos = lista_crear();
    if(lista_disparos == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    float escala_no_infinito = 0.62;//computar_escala_nivel(nivel4_leido);

//----------------------------------------------------------------------------------------------------------------------
    //Boleeanos de estado
    bool chorro_prendido = false;
    bool escudo_prendido = false;

    bool disparo = false;
    double tiempo_para_disparar = COOLDOWN_NAVE;
    bool listo_para_disparar = true;
    
    //Boleeanos de movimiento
    bool rotacion_horaria = false;
    bool rotacion_antihoraria = false;
    bool avanzar = false;

    size_t nivel = 0;
    int vidas = 5;
    int score[2] = {0, SCORE_NEXT_SHIP};

    double tiempo_reactor = TIEMPO_REACTOR;

    double f = 1;
    
    bool spawn = true;

    //Tiempo combustible

        float a = 1;

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        a = a + 0.3;

                        avanzar = true;
                        chorro_prendido = true;
                        break;

                    case SDLK_DOWN:
                        a = a -  0.3;
                        nave_setear_velocidad(nave, 0, 0);
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

                    case SDLK_w:
                        f++;
                        break;

                    case SDLK_s:
                        f--;
                        break;

                    case SDLK_0:
                        nivel = 0;
                        nivel_actual = NULL;
                        spawn = true;
                        break;
                    case SDLK_1:
                        nivel = 1;
                        nivel_actual = nivel_1;
                        spawn = true;
                        break;
                    case SDLK_2:
                        nivel = 2;
                        nivel_actual = nivel_2;
                        spawn = true;
                        break;
                    case SDLK_3:
                        nivel = 3;
                        nivel_actual = nivel_3;
                        spawn = true;
                        break;
                    case SDLK_4:
                        nivel = 4;
                        nivel_actual = nivel_4;
                        spawn = true;
                        break;
                    case SDLK_5:
                        nivel = 5;
                        nivel_actual = nivel_5;
                        spawn = true;
                        break;                    
                    case SDLK_ESCAPE:
                        return 0;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
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
            // END código del alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno

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

        nave_act_figura(nave, nave_leida, nave_mas_chorro_leida, escudo_leido, escudo2_leido);
        nave_apagar(nave, true, true, true);

        if(spawn){
            lista_destruir(lista_disparos, (void (*)(void*))disparo_destruir);
            lista_disparos = lista_crear();
            if(lista_disparos == NULL){
                fprintf(stderr, "Error en la memoria");
                return 1;
            }
        }

        if(nivel == 0){
            if(spawn){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, planeta_get_pos_x(base), planeta_get_pos_y(base), 0);
                spawn = false;
            }
            
            planeta_dibujar(renderer, base);
            planeta_dibujar(renderer, estrella);
            planeta_dibujar(renderer, planeta1);
            planeta_dibujar(renderer, planeta2);
            planeta_dibujar(renderer, planeta3);
            planeta_dibujar(renderer, planeta4);
            planeta_dibujar(renderer, planeta5);

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

            if(distancia_a_planeta(estrella, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                vidas--;
                spawn = true;
            }

            if(distancia_a_planeta(planeta1, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA1\n");
                nivel_actual = nivel_1;
                nivel = 1;
                continue;
            }
            if(distancia_a_planeta(planeta2, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA2\n");
                nivel_actual = nivel_2;
                nivel = 2;
                continue;
            }
            if(distancia_a_planeta(planeta3, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA3\n");
                nivel_actual = nivel_3;
                nivel = 3;
                continue;
            }

            if(distancia_a_planeta(planeta4, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA4\n");
                nivel_actual = nivel_4;
                nivel = 4;
                continue;
            }
            
            if(distancia_a_planeta(planeta5, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA5\n");
                nivel_actual = nivel_5;
                nivel = 5;
                continue;
            }
        }

        if(nivel == 1){
            if(spawn == true){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, VENTANA_ANCHO/2, 500, 0);
                spawn = false;
            }

            main_nivel_en_pantalla(renderer, nivel_actual, nave, lista_disparos, 1, torreta_leida, torreta_disparo_leida, combustible_leido, score, escudo_prendido);
        }

        if(nivel == 2){
            if(spawn == true){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, VENTANA_ANCHO/2, 500, 0);
                spawn = false;
            }

            main_nivel_en_pantalla(renderer, nivel_actual, nave, lista_disparos, 1, torreta_leida, torreta_disparo_leida, combustible_leido, score, escudo_prendido);
        }

        if(nivel == 3){
            if(spawn == true){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, VENTANA_ANCHO/2, 500, 0);
                spawn = false;
            }

            main_nivel_en_pantalla(renderer, nivel_actual, nave, lista_disparos, 1, torreta_leida, torreta_disparo_leida, combustible_leido, score, escudo_prendido);
        }

        if(nivel == 4){

            if(spawn){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, VENTANA_ANCHO/2, 500, 0);
                spawn = false;
            }

            main_nivel_en_pantalla(renderer, nivel_actual, nave, lista_disparos, 1, torreta_leida, torreta_disparo_leida, combustible_leido, score, escudo_prendido);

            if(nave_get_pos_x(nave) < 0){
                nave_setear_posicion(nave, VENTANA_ANCHO, nave_get_pos_y(nave), nave_get_angulo(nave));
            }
            if(nave_get_pos_x(nave) > VENTANA_ANCHO){
                nave_setear_posicion(nave, 0, nave_get_pos_y(nave), nave_get_angulo(nave));
            }
            if(nave_get_pos_y(nave) < 0){
                nave_invertir_vel_y(nave);
            }
        }

        if(nivel == 5){
            
            if(spawn){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, VENTANA_ANCHO/2, VENTANA_ALTO/2, 0);
                tiempo_reactor = TIEMPO_REACTOR;
                spawn = false;
            }
            
            entero_imprimir_centrado(renderer, (int)tiempo_reactor + 1, VENTANA_ANCHO/2, 32*VENTANA_ALTO/40, 2.5, color_crear(false, true, true));

            nivel_imprimir(renderer, nivel_5, 1);

            if(main_disparo_pego(lista_disparos, reactor_get_figura(reactor_5), 10, false)){
                nivel_reactor_destruir(nivel_5);
                spawn = true;
                score[0] += nivel_get_bonus(nivel_actual);
                score[1] -= nivel_get_bonus(nivel_actual);
                nivel = 0;
            }

            if((tiempo_reactor-= DT) <= 0){
                vidas--;
                tiempo_reactor = TIEMPO_REACTOR;
                spawn = true;
                nivel = 0;
            }
        }

        if(rotacion_antihoraria){
            nave_rotar(nave, + NAVE_ROTACION_PASO);
        } 

        if(rotacion_horaria){
            nave_rotar(nave, - NAVE_ROTACION_PASO);
        } 

        if(avanzar){
            nave_avanzar(nave, NAVE_ACELERACION, DT);
        }else{
            nave_avanzar(nave, 0, DT);
        }

        if(nivel != 0){
            printf("%f\n", distancia_punto_a_figura(nivel_get_figura(nivel_actual), nave_get_pos_x(nave), nave_get_pos_y(nave)));
            if(distancia_punto_a_figura(nivel_get_figura(nivel_actual), nave_get_pos_x(nave), nave_get_pos_y(nave)) < 7){
                vidas--;
                spawn = true;
                continue;
            }
            if(nivel_es_infinito(nivel_actual)){
                nave_escudo_setear_angulo(nave, 0);
            } else {
                if(nave_get_pos_y(nave) < VENTANA_ALTO/3){
                    nave_escudo_setear_angulo(nave, PI);
                } else if(nave_get_pos_y(nave) > 2*VENTANA_ALTO/3){
                    nave_escudo_setear_angulo(nave, 0);
                } else if(nave_get_pos_x(nave) < VENTANA_ANCHO/3){
                    nave_escudo_setear_angulo(nave, PI/2);
                } else if(nave_get_pos_x(nave) > 2*VENTANA_ANCHO/3){
                    nave_escudo_setear_angulo(nave, -PI/2);
                }
            }
            if(nave_get_pos_y(nave) > VENTANA_ALTO * 1.25){
                nivel = 0;
                spawn = true;
                continue;
            }
        }
        if(nivel != 5 && nivel != 0) nave_acercar_direccion(nave, G, -PI/2, DT);

        if(chorro_prendido){
            nave_prender(nave, true, false, false);
            nave_sumar_combustible(nave, -JUEGO_COMBUSTIBLE_POT_X_SEG * DT);
        }

        if(escudo_prendido && (nivel != 0 && nivel != 5)){
            nave_prender(nave, false, false, true);
            nave_sumar_combustible(nave, -JUEGO_COMBUSTIBLE_ESC_X_SEG * DT);
        } else if(escudo_prendido){
            nave_prender(nave, false, true, false);
            nave_sumar_combustible(nave, -JUEGO_COMBUSTIBLE_ESC_X_SEG * DT);
        }

        if(vidas == 0) break;
        if(nave_get_combustible(nave) <= 0) break;

        nave_imprimir(renderer, nave, f);

        main_disparo_en_pantalla(renderer, lista_disparos, disparo_leido, f);
        if(disparo_leido == NULL){
            fprintf(stderr, "Error en la memoria");
            break;
        }
        if(!nave_estado_escudo(nave) && nivel != 0){
            if(main_disparo_pego(lista_disparos, nave_get_figura_principal(nave), 5, true)){
                vidas--;
                spawn = true;
                continue;
            }
        }

        if(disparo && listo_para_disparar){
            double c = (VEL_DISPARO * cos(nave_get_angulo(nave)));
            double d = VEL_DISPARO * sin(nave_get_angulo(nave));
            lista_insertar_ultimo(lista_disparos, disparo_crear(nave_get_pos_x(nave), nave_get_pos_y(nave), c, d, nave_get_angulo(nave), true));
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

        if(torreta_leida == NULL){
            fprintf(stderr, "Error de memoria");
            break;
        }
        if(combustible_leido == NULL){
            fprintf(stderr, "Error de memoria");
            break;
        }

        // END código del alumno

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

    // BEGIN código del alumno


    // No tengo nada que destruir.


    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

