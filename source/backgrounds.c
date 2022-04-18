
#include "../include/libnds/nds.h"
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "backgrounds.h"
#include "engine.h"
#include "Puerta.h"
#include "PuertaAbierta.h"
#include "MatrixBackground.h"
#include "MatrixBackground2.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarPuerta() {

	dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPuertaAbierta() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaAbiertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaAbiertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

// Hacer una función únicamente, que reciba
// como parámetro el nombre del fondo y haga el resto.
// Revisar X Macros para ello, para buildear los nombres
// de variables.
void background_SetMatrixBackground() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackgroundBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     MatrixBackgroundBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void background_SetMatrixBackground2() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackground2Bitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     MatrixBackground2BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

//IMPORTANTE: Actualizar cada vez que se añada un nuevo background
void background_setBackground(Backgrounds bg){
    switch (bg) {
        case BG_PUERTA:
            visualizarPuerta();
            break;
        case BG_PUERTAABIERTA:
            visualizarPuertaAbierta();
            break;
        case BG_MATRIX:
            background_SetMatrixBackground();
            break;
        case BG_MATRIX2:
            background_SetMatrixBackground2();
            break;
        default:
            printf("Algo has hecho mal, TOLAI"); //Quitar luego, es para evitar despistes
            break;
    }
}