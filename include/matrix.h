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
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file matrix.h
 */


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

extern void matrix_initSystem();
extern void matrix_displayMatrix(bool display);
extern void matrix_displayBitBlockBuffer(bool display);
extern bool matrix_destroyMatrixEffect();
extern void matrix_updatePivot(uint8 i, uint8 j);
extern bool matrix_dropBitBlockEffect();
extern bool matrix_bitConjuctionEffect();
extern void matrix_bitShakeEffect(int8 state);
extern void matrix_bitResetPosEffect();
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
