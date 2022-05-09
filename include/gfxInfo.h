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
 * @author Geru-Scotland.
 * @file gfxInfo.h
 */

#ifndef INATRIX_OVERFLOW_GFX_BITMAPS_H
#define INATRIX_OVERFLOW_GFX_BITMAPS_H

#include "nds.h"
#include "defines.h"
#include "matrix.h"

#define GFX_NUMBER 5
#define GFX_SIZE GFX_NUMBER + (MATRIX_SIZE * MATRIX_SIZE) + (BITBLOCK_SIZE * BITBLOCK_SIZE)
#define BITMAP_SIZE 7

extern GfxData* gfxList[GFX_SIZE];
extern u8* gfxBitmaps[BITMAP_SIZE];
extern uint8 gfxGUID;

extern void gfxInfo_setGfx(GfxID gfxId, SpriteSize size);
extern void gfxInfo_init();
extern void gfxInfo_initMatrix(Binary *base, uint8 size);
extern void gfxInfo_allocateMatrixElement(GfxID gfxId);
extern void gfxInfo_linkToMatrix(uint8 size, uint8 i, uint8 j, Binary digit);
extern void gfxInfo_freeMemory();
#endif //INATRIX_OVERFLOW_GFX_BITMAPS_H
