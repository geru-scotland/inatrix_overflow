//
// Created by Eideann on 18/4/22.
//

#include "../include/matrix.h"
#include "../include/gfxInfo.h"

Binary matrix[MATRIX_SIZE][MATRIX_SIZE] = {

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

Sprite* spriteMatrix[MATRIX_SIZE][MATRIX_SIZE];

void matrix_initSystem(){
    gfxInfo_initMatrix();
}

void matrix_showMatrix(){

    for(int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            sprites_displaySprite(spriteMatrix[i][j]->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  false);


}

void matrix_destroyMatrix(){

    for(int i = 0; i < MATRIX_SIZE; i++)
        for(int j = 0; j < MATRIX_SIZE; j++)
            if((spriteMatrix[i][j] != NULL) && (spriteMatrix[i][j]->spriteEntry->y <= WINDOW_HEIGHT))
                spriteMatrix[i][j]->spriteEntry->y +=1;
}

/**
 * Hacer esto con puntero a función y reducir código
 * @param center
 */

bool matrix_destroyBitBlock(uint8 pivotR, uint8 pivotC){

    // Hacer checks correspondientes a las diferentes posibilidades
    // Extremos de la matriz etc.
    int out = 0;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            if(spriteMatrix[pivotR + i][pivotC + j]->spriteEntry->y >= WINDOW_HEIGHT)
                out++;
            else
                spriteMatrix[pivotR + i][pivotC + j]->spriteEntry->y +=1;
    return out != MATRIX_BLOCK;
}
/**
 * Cada vez que haya cambios.
 */
void matrix_replicateMatrixToGfx(){
    // Tests.
    gfxInfo_overwriteMatrixGfx(9,9, BIT_ONE);
    gfxInfo_overwriteMatrixGfx(1,0, BIT_ZERO);
}