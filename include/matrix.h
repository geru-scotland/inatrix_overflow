//
// Created by Eideann on 18/4/22.
//

#ifndef INATRIX_OVERFLOW_MATRIX_H
#define INATRIX_OVERFLOW_MATRIX_H
#include <stdbool.h>

#include "defines.h"

#define MATRIX_SIZE 10
#define MATRIX_FIRST 0
#define MATRIX_X_POS 35
#define MATRIX_Y_POS 10
#define MATRIX_X_PADDING 18
#define MATRIX_Y_PADDING 15

#define MATRIX_BLOCK 9

typedef bool Binary;

typedef struct{
    uint8 i;
    uint8 j;
} MatrixPivot;

typedef struct{
    Sprite* sprite;
    Binary digit;
} MatrixElement;


extern void matrix_initSystem();
extern void matrix_showMatrix();
extern bool matrix_destroyMatrixEffect();
extern void matrix_updatePivot(uint8 i, uint8 j);
extern bool matrix_dropBitBlockEffect();
extern void matrix_regenerateBitBlock();
extern void matrix_regenerateMatrix();
extern uint8 matrix_getPositionX(uint8 axis);
extern uint8 matrix_getPositionY(uint8 axis);

extern Binary baseMatrix[MATRIX_SIZE][MATRIX_SIZE];
extern MatrixElement* matrix[MATRIX_SIZE][MATRIX_SIZE];
extern MatrixPivot* pivot;
#endif //INATRIX_OVERFLOW_MATRIX_H
