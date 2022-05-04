//
// Created by Gerun on 18/4/22.
//

#ifndef INATRIX_OVERFLOW_MATRIX_H
#define INATRIX_OVERFLOW_MATRIX_H
#include <stdbool.h>

#include "defines.h"

#define MATRIX_SIZE 10
#define MATRIX_FIRST 0
#define MATRIX_X_POS 50
#define MATRIX_Y_POS 5
#define MATRIX_X_PADDING 16
#define MATRIX_Y_PADDING 15

#define MATRIX_BLOCK 9
#define BITBLOCK_SIZE 3

#define OVERFLOW_NM 9
#define OVERFLOW_HM 15

typedef bool Binary;

typedef struct{
    uint8 i;
    uint8 j;
} MatrixPivot;

typedef struct{
    Sprite* sprite;
    Binary bit;
} MatrixElement;

void matrix_hideMatrix(bool hide);
void matrix_hideBitBlockBuffer(bool hide);
//void matrix_genericToggle(MatrixElement* baseElement, uint8 size, bool hide);

extern void matrix_initSystem();
extern void matrix_displayMatrix(bool display);
extern void matrix_displayBitBlockBuffer(bool display);
extern bool matrix_destroyMatrixEffect();
extern void matrix_updatePivot(uint8 i, uint8 j);
extern bool matrix_dropBitBlockEffect();
extern bool matrix_bitConjuctionEffect();
extern void matrix_bitShakeEffect(int8 state);
extern void matrix_bitResetPosEffect();
extern void matrix_deactivatePivot();
extern void matrix_activatePivot();
extern void matrix_regenerateBitBlock();
extern void matrix_regenerateMatrix();
extern uint8 matrix_getOverflowLimit();
extern uint8 matrix_getPositionX(uint8 axis);
extern uint8 matrix_getPositionY(uint8 axis);
extern void matrix_transposeMainMatrix();
extern void matrix_permuteMatrix(MatrixElement* matrix[]);
extern bool matrix_evalBitBlockOverflow();

extern Binary baseMatrix[MATRIX_SIZE][MATRIX_SIZE];
extern Binary baseBitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE];

extern MatrixElement* matrix[MATRIX_SIZE][MATRIX_SIZE];
extern MatrixElement* bitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE];

extern MatrixPivot* pivot;
extern bool isMatrixHidden;
extern bool isBufferHidden;
extern double binaryBase;
#endif //INATRIX_OVERFLOW_MATRIX_H
