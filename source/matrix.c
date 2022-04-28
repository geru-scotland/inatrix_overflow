//
// Created by Eideann on 18/4/22.
//

#include "../include/matrix.h"
#include "../include/gfxInfo.h"
#include "../include/eventMgr.h"

MatrixElement* matrix[MATRIX_SIZE][MATRIX_SIZE];
MatrixElement* bitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE];
MatrixPivot* pivot; // Quizá hacer un pivotLocked para entre eventos, evitar updates.
bool isMatrixHidden = true;
bool isBufferHidden = true;

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

// Que tenga más 0s que unos
Binary baseBitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE] = {

        { 0, 0, 1 },
        { 0, 1, 0 },
        { 0, 1, 0 }

};

void matrix_initSystem(){
    gfxInfo_initMatrix(baseMatrix[0], MATRIX_SIZE);
    gfxInfo_initMatrix(baseBitBlockBuffer[0], BITBLOCK_SIZE);
    pivot = malloc(sizeof(MatrixPivot));
}

void matrix_displayMatrix(bool display){
    matrix_hideMatrix(!display);
}

void matrix_displayBitBlockBuffer(bool display){
    matrix_hideBitBlockBuffer(!display);
}

/*void matrix_genericToggle(MatrixElement* baseElement, uint8 size, bool hide){
    if(hide)
        isMatrixHidden = true;
    else
        isMatrixHidden = false;

    for(int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            sprites_displaySprite((*(&baseElement + i*size + j))->sprite->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  hide);
}*/

void matrix_hideMatrix(bool hide){

    if(hide)
        isMatrixHidden = true;
    else
        isMatrixHidden = false;

    for(int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            sprites_displaySprite(matrix[i][j]->sprite->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  hide);
}

void matrix_hideBitBlockBuffer(bool hide){

    if(hide)
        isBufferHidden = true;
    else
        isBufferHidden = false;

    for(int i = 0; i < BITBLOCK_SIZE; i++)
        for (int j = 0; j < BITBLOCK_SIZE; j++)
            sprites_displaySprite(bitBlockBuffer[i][j]->sprite->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  hide);
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
            if((matrix[i][j]->sprite != NULL)
            && (matrix[i][j]->sprite->spriteEntry->y <= WINDOW_HEIGHT))
                matrix[i][j]->sprite->spriteEntry->y +=1;

    //TODO: Cambia esto @Matxin, que te has dado cuenta tú.
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
* 1. Permutar elementos del bitBlockBuffer.
* 2. Salvar en un array temporal los MatrixElement (sprite+ digit).
* 3. Asignar referencias de elementos MatrixElement del bitBlockBuffer a la matriz (i,j).
* 4. Colocar esos elementos de matrix en las posiciones correctas (ya que son los que han caído).
* 5. Asignar las referencias guardadas en el array temporal al bitBlockBuffer.
* 6. Mostrar elementos nuevos de la matriz (en base al pivot).
*/
void matrix_regenerateBitBlock(){

    MatrixElement* tmp[BITBLOCK_SIZE][BITBLOCK_SIZE];

    // TODO: Permutar elementos de bitBlockBuffer
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            tmp[i+1][j+1] = matrix[pivot->i + i][pivot->j + j];
            matrix[pivot->i + i][pivot->i + j] = bitBlockBuffer[i+1][j+1];
            bitBlockBuffer[i+1][j+1] = tmp[i+1][j+1];
            sprites_displaySprite(matrix[pivot->i + i][pivot->i + j]->sprite->index,
                                  MATRIX_X_POS + ((pivot->j + j) * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + ((pivot->i + i) * MATRIX_Y_PADDING),
                                  false);
        }
    }
}

/**
 * Generar random. Por ahora para tests,
 * tiro de la base.
 *
 */
void matrix_regenerateMatrix(){
    // Por ahora hacer traspuesta, simplemente.
    // TODO: Implementar algún algoritmo de reordenación
    MatrixElement* tmpMatrix[MATRIX_SIZE][MATRIX_SIZE];

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            tmpMatrix[i][j] = matrix[i][j];
        }
    }

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
           matrix[i][j] = tmpMatrix[j][i];
        }
    }
}


/*
*********************
*********************
****** HELPERS ******
*********************
*********************
*/

void matrix_updatePivot(uint8 i, uint8 j){
    if((i >= 1) && (i < MATRIX_SIZE-1) && (j >= 1) && (j < MATRIX_SIZE-1)){
        pivot->i = i;
        pivot->j = j;
    }
}

// Hacer puntero a función
uint8 matrix_getPositionX(uint8 axis){
    return  MATRIX_X_POS + (axis * MATRIX_X_PADDING);
}

uint8 matrix_getPositionY(uint8 axis){
    return  MATRIX_Y_POS + (axis * MATRIX_Y_PADDING);
}