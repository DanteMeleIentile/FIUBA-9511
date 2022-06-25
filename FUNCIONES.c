

/**************** FIGURAS ************************/
/* 
** Etiquetas para cada tipo de figura
*/
typedef enum figura_tipo_t {
    FIGURA_ICONO = 0,
    FIGURA_NIVEL = 1,
    FIGURA_SPRITE = 2,
    FIGURA_PLANETA = 3,
    FIGURA_BASE = 4,
    FIGURA_COMBUSTIBLE = 5,
    FIGURA_TORRETA = 6,
    FIGURA_REACTOR = 7,
} figura_tipo_t;

/* 
** Devuelve el nombre de la figura
*/
const char* figura_tipo_a_cadena(figura_tipo_t figura);


/************************* LECTURA ********************/
/*
** Recibe un archivo "f" y, de ser posible, devuelve el "nombre", el "tipo", si es de tipo infinito y la cantidad de polilíneas asociadas a una figura junto con un "true" que indica el exito de la lectura. Caso contrario, devuelve "false".
*/
bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);

/*
** Lee un archivo "f" y devuelva una polilínea con lo parámetros indicados. En caso de error devuelve "NULL".
*/
polilinea_t *leer_polilinea(FILE *f);



/***************** MANEJO DE COLOR *********************/

/*
** Se almacenan los colores en 1 byte<
*/
typedef uint8_t color_t;

/*
** Crear un color_t según las componentes RGB "r", "g" y "b".
*/
color_t color_crear(bool r, bool g, bool b);

/*
** Obtiene de un color_t "c" sus componentes RGB "r", "g" y "b".
*/
void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b);



/******************** POLILINEA **************************/
/*
** La estructura que se define para las polilineas es de tipo:
**
** +--------+
** | PUNTOS | -> Puntos de la polilinea
** +--------+
** |   N    | -> Cantidad de puntos de la polilinea
** +--------+
*/
typedef struct polilinea polilinea_t;

/*
** Crea una polilinea de n sin inicializar las coordenadas
*/
polilinea_t *polilinea_crear_vacia(size_t n);

/*
** Destruye una polilinea creada mediante "polilinea_crear_vacia". Devuelve NULL en caso de falla.
*/
void polilinea_destruir(polilinea_t *polilinea);

/*
** De ser posible, asigna un punto de coordenadas "x" e "y" en la posición "pos" de la polilinea "polilinea". Caso contrario devuelve false;
*/
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

/*
** De ser posible, asigna un color "color" a la polilinea "polilinea". Caso contrario devuelve false;
*/
bool polilinea_setear_color(polilinea_t *polilinea, color_t color);


/*
Crea una nueva polilínea con n puntos sin inicializar. Devuelve la polilínea creada o NULL en caso de falla.
*/
polilinea_t *polilinea_crear_vacia(size_t n);


/*
Crea una nueva polilínea según los n puntos recibidos. Devuelve la polilínea creada en memoria nueva o NULL en caso de falla.
*/
polilinea_t *polilinea_crear(const float puntos[][2], size_t n);

/*
Devuelve una copia de una polilinea dada en memoria nueva.
*/
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);


void polilinea_destruir(polilinea_t *polilinea);