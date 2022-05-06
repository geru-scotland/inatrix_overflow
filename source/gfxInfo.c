/*
 * This file is part of the Iñatrix Overflow Project.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */


/**
 * @author Geru-Scotland
 * @file gfxInfo.c
 * @brief Se encarga de crear, inicializar y asociar los GFX a los sprites en memoría dinámica,
 * así como de escribir en el banco de memoria de la pantalla Main de la NDS todos los sprites.
 * Inicialmente están ocultos.
 */

#include "gfxInfo.h"
#include "utils.h"
#include "sprites.h"


/**
 * @var gfxList[GFX_SIZE]: Array que contiene las direcciones de memoria de todos los structs GfxData.
 * @var gfxBitmaps[BITMAP_SIZE]: Array que contiene las referencias a los arrays bitmaps.
*/

GfxData* gfxList[GFX_SIZE];
uint8 gfxGUID = 0;

/*
*********************
*********************
****** BITMAPS ******
*********************
*********************
*/

u8 redCapsule[256] = {

        0,0,0,0,0,1,1,1,
        0,0,0,0,1,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,1,1,1,1,

        1,1,1,1,0,0,0,0,
        0,0,0,0,1,0,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        1,1,1,1,1,1,0,0,

        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,0,1,1,1,1,
        0,0,0,0,0,1,1,1,

        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,0,0,0,
        1,1,1,1,0,0,0,0

};

u8 blueCapsule[256] = {

        0,0,0,0,0,5,5,5,
        0,0,0,0,5,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,5,5,5,5,

        5,5,5,5,0,0,0,0,
        0,0,0,0,5,0,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        5,5,5,5,5,5,0,0,

        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,0,5,5,5,5,
        0,0,0,0,0,5,5,5,

        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,0,0,0,
        5,5,5,5,0,0,0,0
};

u8 digitOne[256] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,

        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,

        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,

        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0


};

u8 digitZero[256] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,4,4,
        0,0,0,0,0,4,4,4,
        0,0,0,0,0,4,4,0,
        0,0,0,0,0,4,4,0,

        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        4,4,0,0,0,0,0,0,
        4,4,4,0,0,0,0,0,
        0,4,4,0,0,0,0,0,
        0,4,4,0,0,0,0,0,

        0,0,0,0,0,4,4,0,
        0,0,0,0,0,4,4,0,
        0,0,0,0,0,4,4,4,
        0,0,0,0,0,0,4,4,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,

        0,4,4,0,0,0,0,0,
        0,4,4,0,0,0,0,0,
        4,4,4,0,0,0,0,0,
        4,4,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0


};

u8 inatrix[256] = {

        0,0,0,0,9,10,10,10,
        0,0,0,11,11,9,9,9,
        0,0,11,11,11,9,9,9,
        0,0,11,11,11,17,17,17,
        0,0,11,11,11,17,17,17,
        0,0,11,11,17,6,6,17,
        0,0,0,11,17,17,17,11,
        0,17,0,0,17,17,17,17,

        10,10,10,10,0,0,0,0,
        9,9,9,9,10,0,0,0,
        9,9,9,9,9,0,0,0,
        17,17,17,0,0,0,0,0,
        17,17,17,0,0,0,0,0,
        17,6,6,0,0,0,0,0,
        11,17,17,0,0,0,0,0,
        17,17,0,0,0,0,0,0,

        0,6,0,6,6,6,6,11,
        0,0,6,6,6,6,19,19,
        0,0,0,6,6,6,19,19,
        0,0,0,10,10,10,10,9,
        0,0,0,6,11,0,0,0,
        0,0,0,6,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,

        11,6,6,0,0,0,0,0,
        19,6,6,6,6,17,0,0,
        19,19,6,0,0,0,0,0,
        9,9,10,0,0,0,0,0,
        0,6,11,0,0,0,0,0,
        0,6,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0
};

/**
 *
 * @brief
 * @param gfxId Id del @struct GfxID
 * @param size tamaño que oamMain de NDS ha de tener en cuenta.
 */
void gfxInfo_setGfx(GfxID gfxId, SpriteSize size){
    gfxList[gfxGUID] = malloc(sizeof(GfxData));
    gfxList[gfxGUID]->memAddress = NULL;
    gfxList[gfxGUID]->GUID = gfxGUID;
    gfxList[gfxGUID]->gfxId = gfxId;
    gfxList[gfxGUID]->bitmap = gfxBitmaps[gfxId];
    gfxList[gfxGUID]->size = size;
    gfxList[gfxGUID]->colorFormat = SpriteColorFormat_256Color;

    gfxGUID++;
}

/**
 * @var gfxGUID: Identificador global y único de cada GFX. El orden es importante ya que
 * las asociaciones de los sprites irán en el mismo.
 */
u8* gfxBitmaps[BITMAP_SIZE] = {
    blueCapsule,    // Blue Capsule
    redCapsule,     // Red Capsule
    inatrix,        // Inatrix_X
    inatrix,        // Inatrix_Y
    digitOne,       // Digit 1
    digitZero       // Digit 0
};

/**
 * @brief Función que permite la adición de nuevos gráficos.
 */
void gfxInfo_init(){

    /* CAPSULES */
    gfxInfo_setGfx(GFX_CAPSULE_BLUE, SpriteSize_16x16);
    gfxInfo_setGfx(GFX_CAPSULE_RED, SpriteSize_16x16);

    /* INATRIX */
    gfxInfo_setGfx(GFX_INATRIX_X, SpriteSize_16x16);
    gfxInfo_setGfx(GFX_INATRIX_Y, SpriteSize_16x16);
}

/**
 *  @brief Función que genera la Matrix de manera independiente
 * Para poder construir los sprites asociados a cada elemento de la matriz.
 * Se encarga de reservar memoria en el banco de memoria de la NDS y, una vez
 * obtenido el puntero al sprite, se vincula a su posición correspondiente en la
 * matriz.
 * @param base: Dirección de memomria del primer elemento de la matriz bidimensional.
 * @param size: Número de filas/columnas (matriz cuadrada).
 *
 * @nota: *(base + i*size + j) En memoria dinámica, C trata los arrays bidimensionales
 * como si fueran un vector, con lo que para acceder a cada elemento lo hago mediante la
 * desreferencia de la posición dada por: dirección base + número de fila*número de elementos en esa fila
 * + número de columna. De ésta manera puedo comprobar el id del GFX en esa posición.
 */
void gfxInfo_initMatrix(Binary *base, uint8 size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            gfxInfo_allocateMatrixElement(*(base + i*size + j) ? GFX_DIGIT_ONE : GFX_DIGIT_ZERO);
            gfxInfo_linkToMatrix(size, i, j, *(base + i*size + j) ? BIT_ONE : BIT_ZERO);
        }
    }
}

/**
 * @brief Reserva memoria para un elemento de la matrix.
 */
void gfxInfo_allocateMatrixElement(GfxID gfxId){
    gfxInfo_setGfx(gfxId, SpriteSize_16x16);
    sprites_memorySetup(gfxList[gfxGUID - 1]);
}

/**
 * @brief Crear en memoria dinámica un @struct MatrixElement y lo asigna
 * a la posicón indicada del Bitblock/Matriz
 * @param size: Tamaño de la matriz
 * @param i: fila
 * @param j: columna
 * @param bit: indica el valor del dígito binario del tipo @typedef Binary
 * TODO: Mejorar esta chapuza.
 */
void gfxInfo_linkToMatrix(uint8 size, uint8 i, uint8 j, Binary bit) {
    if(size == BITBLOCK_SIZE){
        bitBlockBuffer[i][j] = malloc(sizeof(MatrixElement));
        bitBlockBuffer[i][j]->sprite = sprites[gfxGUID - 1];
        bitBlockBuffer[i][j]->bit = bit;
    }else
    {
        matrix[i][j] = malloc(sizeof(MatrixElement));
        matrix[i][j]->sprite = sprites[gfxGUID - 1];
        matrix[i][j]->bit = bit;
    }
}

/**
 * @brief Liberar la memoría dinámica o heap ocupada por los GFX.
 */
void gfxInfo_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}