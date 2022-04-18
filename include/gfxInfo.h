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
extern uint8 gfxGUID; // Global Unique Identifier

extern void gfxInfo_setGfx(uint8 guid, GfxID gfxId, SpriteSize size, bool overwrite);
extern void gfxInfo_init();
extern void gfxInfo_initMatrix();
extern void gfxInfo_overwriteGfx(uint8 index);
extern void gfxInfo_overwriteMatrixGfx(uint8 i, uint8 j, Binary digit);
extern void gfxInfo_freeMemory();
#endif //INATRIX_OVERFLOW_GFX_BITMAPS_H
