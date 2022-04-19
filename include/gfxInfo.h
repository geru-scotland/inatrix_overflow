//
// Created by Geru on 14/4/22.
//

#ifndef INATRIX_OVERFLOW_GFX_BITMAPS_H
#define INATRIX_OVERFLOW_GFX_BITMAPS_H

#include "nds.h"
#include "defines.h"
#include "matrix.h"

#define GFX_SIZE 4 + (MATRIX_SIZE * MATRIX_SIZE)
#define BITMAP_SIZE 4

extern GfxData* gfxList[GFX_SIZE];
extern u8* gfxBitmaps[BITMAP_SIZE];
static uint8 gfxGUID; // Global Unique Identifier

extern void gfxInfo_setGfx(GfxID gfxId, SpriteSize size);
extern void gfxInfo_init();
extern void gfxInfo_initMatrix();
extern void gfxInfo_initBitBlockPlaceholder();
extern void gfxInfo_allocateMatrixElement(GfxID gfxId);
extern void gfxInfo_linkToMatrix(uint8 i, uint8 j, Binary digit);
extern void gfxInfo_linkToPlaceHolder();
extern void gfxInfo_freeMemory();
#endif //INATRIX_OVERFLOW_GFX_BITMAPS_H
