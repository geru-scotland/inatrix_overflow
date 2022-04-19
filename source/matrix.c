//
// Created by Eideann on 18/4/22.
//

#include "../include/matrix.h"
#include "../include/gfxInfo.h"

MatrixElement* matrix[MATRIX_SIZE][MATRIX_SIZE];
MatrixPivot* pivot; // Quizá hacer un pivotLocked para entre eventos, evitar updates.

Binary baseMatrix[MATRIX_SIZE][MATRIX_SIZE] = {

        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 }

};

void matrix_initSystem(){
    //gfxInfo_initMatrix();
    pivot = malloc(sizeof(MatrixPivot));
}

void matrix_showMatrix(){

    for(int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            sprites_displaySprite(matrix[i][j]->sprite->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  false);
}

/*
*********************
*********************
***** EFFECTS *******
*********************
*********************
*/

bool matrix_destroyMatrixEffect(){

    for(int i = 0; i < MATRIX_SIZE; i++)
        for(int j = 0; j < MATRIX_SIZE; j++)
            if((matrix[i][j]->sprite != NULL) && (matrix[i][j]->sprite->spriteEntry->y <= WINDOW_HEIGHT))
                matrix[i][j]->sprite->spriteEntry->y +=1;

    return (matrix[MATRIX_FIRST][MATRIX_FIRST]->sprite->spriteEntry->y <= WINDOW_HEIGHT) ? true : false;
}

/**
 * Hacer esto con puntero a función y reducir código
 * @param center
 */

bool matrix_dropBitBlockEffect(){

    // Hacer checks correspondientes a las diferentes posibilidades
    // Extremos de la matriz etc.
    int out = 0;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            if(matrix[pivot->i + i][pivot->j + j]->sprite->spriteEntry->y >= WINDOW_HEIGHT)
                out++;
            else
                matrix[pivot->i + i][pivot->j + j]->sprite->spriteEntry->y +=1;
    return out != MATRIX_BLOCK;
}

bool matrix_bitConjuctionEffect(){

    return true;
}

/*
*********************
*********************
*** REGENERATIONS ***
*********************
*********************
*/

/**
 * Lo replica en la matrix de GFX
 * Hacer checks seguridad de index acceso.
 */
void matrix_regenerateBitBlock(){
    // Cambiar en matrix[i][j] también.
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            gfxInfo_replicateMatrixGfx(pivot->i + i, pivot->j + j, BIT_ONE); // Generar random, claro.
}

/**
 * Generar random. Por ahora para tests,
 * tiro de la base.
 *
 */
void matrix_regenerateMatrix(){
    for(int i = 0; i < MATRIX_SIZE; i++)
        for(int j = 0; j < MATRIX_SIZE; j++)
            gfxInfo_replicateMatrixGfx(i, j, matrix[i][j]); // Test. Generar random, claro.
}


/*
*********************
*********************
****** HELPERS ******
*********************
*********************
*/

void matrix_updatePivot(uint8 i, uint8 j){
    pivot->i = i;
    pivot->j = j;
}

// Hacer puntero a función
uint8 matrix_getPositionX(uint8 axis){
    return  MATRIX_X_POS + (axis * MATRIX_X_PADDING);
}

uint8 matrix_getPositionY(uint8 axis){
    return  MATRIX_Y_POS + (axis * MATRIX_Y_PADDING);
}