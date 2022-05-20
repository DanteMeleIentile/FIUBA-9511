#include <stdio.h>
#include <stdint.h>


#define MASK_PARTE_ALTA 0x07
#define MASK_PARTE_BAJA 0x1F

#define MASK_OBTENER_ALTA 0xE0
#define MASK_OBTENER_BAJA 0x1F


uint8_t obtener_byte(uint8_t alta, uint8_t baja){
    uint8_t num = ((alta & MASK_PARTE_ALTA) << 5);
    num = num | (baja & MASK_PARTE_BAJA);
    return num;
}

void generar_byte(uint8_t byte, uint8_t *alta, uint8_t *baja){
    *alta = ((byte & MASK_OBTENER_ALTA) >> 5);

    *baja = (byte & MASK_OBTENER_BAJA);
}

int main(void){
    uint8_t alta = 0x45;
    uint8_t baja = 0x7C;

    printf("EL numeor es = 0x%X\n", obtener_byte(alta, baja));

    uint8_t byte = 0xB9;
    uint8_t alta_uno;
    uint8_t baja_dos;
    generar_byte(byte, &alta_uno, &baja_dos);
    printf("alta = %X y baja = %X\n", alta_uno, baja_dos);

    return 0;
}