//
// Created by Eideann on 18/4/22.
//

#ifndef INATRIX_OVERFLOW_MATRIX_H
#define INATRIX_OVERFLOW_MATRIX_H
#include <stdbool.h>

#include "defines.h"

#define MATRIX_SIZE 10
#define MATRIX_X_POS 35
#define MATRIX_Y_POS 10
#define MATRIX_X_PADDING 18
#define MATRIX_Y_PADDING 15

#define MATRIX_BLOCK 9

typedef struct{
    uint8 i;
    uint8 j;
} MatrixPivot;

typedef bool Binary;
extern void matrix_initSystem();
extern void matrix_showMatrix();
extern void matrix_destroyMatrix();
extern bool matrix_dropBitBlock(MatrixPivot* pivot);
extern void matrix_regenerateBitBlock();
extern void matrix_regenerateMatrix();
extern void matrix_replicateMatrixToGfx();
extern void matrix_updatePivot(uint8 i, uint8 j);

extern Binary matrix[MATRIX_SIZE][MATRIX_SIZE];
extern Sprite* spriteMatrix[MATRIX_SIZE][MATRIX_SIZE]; // Replica de Matrix
extern MatrixPivot* pivot;
#endif //INATRIX_OVERFLOW_MATRIX_H
