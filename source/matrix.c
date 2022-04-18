//
// Created by Eideann on 18/4/22.
//

#include "../include/matrix.h"
#include "../include/gfxInfo.h"

Binary matrix[MATRIX_SIZE][MATRIX_SIZE] = {

        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
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

    for(int i = 0; i < MATRIX_SIZE; i++){
        for (int j = 0; j < MATRIX_SIZE; j++){
            sprites_displaySprite(spriteMatrix[i][j]->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  false);
        }
    }
}

/**
 * Cada vez que haya cambios.
 */
void matrix_replicateMatrixToGfx(){
    // Tests.
    gfxInfo_overwriteMatrixGfx(9,9,BINARY_ONE);
    gfxInfo_overwriteMatrixGfx(1,0, BINARY_ZERO);
}